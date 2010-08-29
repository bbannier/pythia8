// HepMCInterface.cc is a part of the PYTHIA event generator.
// Copyright (C) 2010 Mikhail Kirsanov, Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// Function definitions (not found in the header) for the I_Pythia8 class, 
// which converts a PYTHIA event record to the standard HepMC format.

// Mikhail.Kirsanov@cern.ch
//
// Modified 17.12.2007: beam particles (# 1 and 2) are put in the record;
//                      possibility to momentum-energy convert to MeV
//          19.10.2009: optionally set cross-section info

#include "HepMCInterface.h"
#include "HepMC/GenEvent.h"

namespace HepMC {

//==========================================================================

// Constructor and destructor.

  I_Pythia8::I_Pythia8(): m_trust_mothers_before_daughters(1),
                          m_trust_both_mothers_and_daughters(0),
                          m_print_inconsistency_errors(1),
                          m_internal_event_number(0),
                          m_crash_on_problem(false),
                          m_convert_to_mev(false),
                          m_mom_scale_factor(1.),
                          m_freepartonwarnings(true)
  {;}

  I_Pythia8::~I_Pythia8()
  {;}

//--------------------------------------------------------------------------

// Main method for conversion from PYTHIA event to HepMC event.

  bool I_Pythia8::fill_next_event( Pythia8::Event& pyev, GenEvent* evt,
                                   int ievnum )
  {
    // read one event from the Pythia8 and fill GenEvent
    // return T/F =success/failure
    // this method also fills PDF and cross-section info
    //
    if ( !evt ) {
      std::cerr << "I_Pythia8::fill_next_event error - passed null event." 
                << std::endl;
      return 0;
    }

    if( ievnum >= 0 ) {
      evt->set_event_number(ievnum);
      m_internal_event_number = ievnum;
    }
    else {
      evt->set_event_number(m_internal_event_number);
      m_internal_event_number++;
    }

	// 2. create a particle instance for each entry and fill a map
	//    create a vector which maps from the particle index to the 
	//    GenParticle address.
	std::vector<GenParticle*> hepevt_particles( pyev.size() );
    int i, istatus;
    for ( i = 1; i < pyev.size(); ++i ) {
      // The new HepMC status codes of February 2009 are now used by 
      // default. If you want to recover the previous simpler behaviour
      // comment out the next line and uncomment the following one. 
      istatus = pyev.statusHepMC(i);
      // istatus = (pyev[i].status() > 0) ? 1 : 2;
      hepevt_particles[i] = new GenParticle(
              FourVector( m_mom_scale_factor*pyev[i].p().px(),
                          m_mom_scale_factor*pyev[i].p().py(),
                          m_mom_scale_factor*pyev[i].p().pz(),
                          m_mom_scale_factor*pyev[i].p().e()  ),
        pyev[i].id(), istatus                );
      hepevt_particles[i]->suggest_barcode(i);
    }

    //
    // Here we assume that the first two particles in the list
    // are the incoming beam particles.
    evt->set_beam_particles( hepevt_particles[1], hepevt_particles[2] );
    //
    // 3.+4. loop over particles AGAIN, this time creating vertices
    for ( i = 1; i < pyev.size(); ++i ) {
      // We go through and build EITHER the production or decay
      // vertex for each entry in hepevt, depending on the switch
      // m_trust_mothers_before_daughters (new 2001-02-28)
      // Note: since the HEPEVT pointers are bi-directional, it is
      ///      sufficient to do one or the other.
      //
      // 3. Build the production_vertex (if necessary)
      if ( m_trust_mothers_before_daughters ||
           m_trust_both_mothers_and_daughters ) {
        // for particle with index i, build a production vertex
        // if appropriate, and add that vertex to the event
        GenParticle* p = hepevt_particles[i];
        // a. search to see if a production vertex already exists
        std::vector<int> mothers = pyev.motherList(i);
        unsigned int imother = 0;
        int mother = -1; // note that in Pythia8 there is a particle number 0!
        if ( !mothers.empty() ) mother = mothers[imother];
        GenVertex* prod_vtx = p->production_vertex();
        while ( !prod_vtx && mother > 0 ) {
          prod_vtx = hepevt_particles[mother]->end_vertex();
          if ( prod_vtx ) prod_vtx->add_particle_out( p );
          // increment mother for next iteration
          //if ( ++mother > pyev[i].mother2() ) mother = 0; // HEPEVT variant
          //while( ( pyev[mother].daughter1() > i       ||  // variant 0
          //         ( pyev[mother].daughter2() != 0 &&
          //           pyev[mother].daughter2() < i   ) ||
          //         ( pyev[mother].daughter1() != i &&
          //           pyev[mother].daughter2() == 0  )  )  &&
          //       mother <= pyev[i].mother2() ) {
          //  mother++;
          // }
          imother++;                                // variant with motherList
          if ( imother < mothers.size() ) {
            mother = mothers[imother];
          } else {
            mother = -1;
          }
        }
        // b. if no suitable production vertex exists - and the particle
        // has at least one mother or position information to store -
        // make one
              FourVector prod_pos( pyev[i].xProd(), pyev[i].yProd(),
                                   pyev[i].zProd(), pyev[i].tProd() );
        unsigned int nparents = mothers.size();
        if ( !prod_vtx && ( nparents > 0 ||
                                  prod_pos != FourVector() ) ) {
           prod_vtx = new GenVertex();
           prod_vtx->add_particle_out( p );
           evt->add_vertex( prod_vtx );
        }
        // c. if prod_vtx doesn't already have position specified, fill it
        if ( prod_vtx && prod_vtx->position()==FourVector() )
          prod_vtx->set_position( prod_pos );
        // d. loop over mothers to make sure their end_vertices are
        //     consistent
        imother = 0;
        mother = -1;
        if ( !mothers.empty() ) mother = mothers[imother];
        while ( prod_vtx && mother > 0 ) {
          if ( !hepevt_particles[mother]->end_vertex() ) {
            // if end vertex of the mother isn't specified, do it now
            prod_vtx->add_particle_in( hepevt_particles[mother] );
          } else if (hepevt_particles[mother]->end_vertex() != prod_vtx ) {
            // problem scenario --- the mother already has a decay
            // vertex which differs from the daughter's produciton
            // vertex. This means there is internal
            // inconsistency in the HEPEVT event record. Print an
            // error
            // Note: we could provide a fix by joining the two
            //       vertices with a dummy particle if the problem
            //       arrises often with any particular generator.
            if ( m_print_inconsistency_errors )
              std::cerr
              << "HepMC::I_Pythia8: inconsistent mother/daugher "
              << "information in Pythia8 event " << std::endl
              << "i= " << i << " mother = " << mother
              << "\n This warning can be turned off with the "
              << "I_Pythia8::print_inconsistency_errors switch."
              << std::endl;
          }
          imother++;                                // variant with motherList
          if ( imother < mothers.size() ) {
            mother = mothers[imother];
          } else {
            mother = -1;
          }
        }
      }
      else {
        std::cerr << "trust_daughters_before_mothers not implemented"
                  << std::endl;
        return 0;
      }
    }

    // 5.             01.02.2000
    // handle the case of particles in which come from nowhere -
    //  i.e. particles without mothers or daughters.
    //  These particles need to be attached to a vertex, or else they
    //  will never become part of the event. Check for this situation
    for ( i = 1; i < pyev.size(); ++i ) {
      if ( !hepevt_particles[i]->end_vertex() &&
           !hepevt_particles[i]->production_vertex() ) {
//        if ( i ) std::cerr << "hanging particle " << i << std::endl;
        std::cerr << "hanging particle " << i << std::endl;
        GenVertex* prod_vtx = new GenVertex();
        prod_vtx->add_particle_out( hepevt_particles[i] );
        evt->add_vertex( prod_vtx );
      }
      if( m_freepartonwarnings ) {
        if ( hepevt_particles[i]->pdg_id() == 21 &&
             !hepevt_particles[i]->end_vertex()     ) {
          std::cerr << "gluon without end vertex " << i << std::endl;
          if ( m_crash_on_problem ) exit(1);
        }
        if ( abs(hepevt_particles[i]->pdg_id()) <= 6 &&
             !hepevt_particles[i]->end_vertex()         ) {
          std::cerr << "quark without end vertex " << i << std::endl;
          if ( m_crash_on_problem ) exit(1);
        }
      }
    }

	return 1;
  }

//--------------------------------------------------------------------------

// Conversion from PYTHIA event to HepMC event, with PDF info included.

  bool I_Pythia8::fill_next_event( Pythia8::Pythia& pythia, GenEvent* evt,
                                   int ievnum, bool convertGluonTo0 )
  {
    // read one event from the Pythia8 and fill GenEvent
    // return T/F =success/failure
    // this method fills also PDF info
    //

    bool doHadr = pythia.flag("HadronLevel:all") &&
                  pythia.flag("HadronLevel:Hadronize");
    if(!doHadr) m_freepartonwarnings = false;

    bool result = fill_next_event( pythia.event, evt, ievnum );
    if( result ) {
      put_pdf_info(evt, pythia, convertGluonTo0 );
      // HepMC 2.05 supports cross-section information in pb:
#ifdef HEPMC_HAS_CROSS_SECTION
      HepMC::GenCrossSection xsec;
      xsec.set_cross_section( pythia.info.sigmaGen() * 1e9, 
        pythia.info.sigmaErr() * 1e9);
      evt->set_cross_section(xsec);
#endif
    }
    return result;
  }

//--------------------------------------------------------------------------

// Conversion of PDF info.

  void I_Pythia8::put_pdf_info( GenEvent* evt, Pythia8::Pythia& pythia,
                                bool convertGluonTo0 )
  {
    int id1 = pythia.info.id1();
    int id2 = pythia.info.id2();
    if ( convertGluonTo0 ) {
      if ( id1 == 21 ) id1 = 0;
      if ( id2 == 21 ) id2 = 0;
    }
    double x1 = pythia.info.x1();
    double x2 = pythia.info.x2();
    double Q  = pythia.info.QRen();
    double pdf1 = pythia.info.pdf1();
    double pdf2 = pythia.info.pdf2();
    // here xf(x) is put as a pdf density, not f(x)!
    evt->set_pdf_info( PdfInfo(id1,id2,x1,x2,Q,pdf1,pdf2) ) ;
  }

//==========================================================================

} // end namespace HepMC
