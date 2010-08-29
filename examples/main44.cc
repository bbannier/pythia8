// main44.cc is a part of the PYTHIA event generator.
// Copyright (C) 2010 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// Test of the creation of and linking to an external PDF set,
// and thereafter resetting to different PDF's, internal and external.

#include "Pythia.h"
using namespace Pythia8; 
 
//==========================================================================

// A simple scaling PDF. Not realistic; only to check that it works.

class Scaling : public PDF {

public:

  // Constructor.
  Scaling(int idBeamIn = 2212) : PDF(idBeamIn) {}

private:

  // Update PDF values.
  void xfUpdate(int id, double x, double Q2);

};

//--------------------------------------------------------------------------

// No dependence on Q2, so leave out name for last argument.

void Scaling::xfUpdate(int id, double x, double ) {

  // Valence quarks, carrying 60% of the momentum.
  double dv  = 4. * x * pow3(1. - x);
  double uv  = 2. * dv;

  // Gluons and sea quarks carrying the rest.
  double gl  = 2.  * pow5(1. - x);
  double sea = 0.4 * pow5(1. - x); 
 
  // Update values
  xg    = gl;
  xu    = uv + 0.18 * sea;
  xd    = dv + 0.18 * sea; 
  xubar = 0.18 * sea; 
  xdbar = 0.18 * sea;
  xs    = 0.08 * sea;
  xc    = 0.04 * sea;
  xb    = 0.02 * sea;

  // Subdivision of valence and sea.
  xuVal = uv;
  xuSea = xubar;
  xdVal = dv;
  xdSea = xdbar;

  // idSav = 9 to indicate that all flavours reset. id change dummy. 
  idSav = 9;
  id   = 0;

} 

//==========================================================================

int main() {

  // Generator. Extreme process selection to enhance p/pbar difference.
  Pythia pythia;
  pythia.readString("WeakSingleBoson:ffbar2gmZ = on");    
  pythia.readString("PhaseSpace:mHatMin = 1200."); 

  // Only interested in cross section so switch off the rest.
  pythia.readString("PartonLevel:all = off");    

  // Create new PDF's using above simple class.
  PDF* pdfAPtr  = new Scaling(2212);
  PDF* pdfB2Ptr = new Scaling(-2212);
  PDF* pdfB3Ptr = new Scaling(2212);

  // Loop over six subruns. 
  for (int iBeam = 0; iBeam < 6; ++iBeam) {
    cout << "\n Now begin subrun number " << iBeam << endl;

    // Flip back and forth between internal and external PDF's.
    if (iBeam == 2) pythia.setPDFPtr( pdfAPtr, pdfB2Ptr);
    if (iBeam == 3) pythia.setPDFPtr( pdfAPtr, pdfB3Ptr);
    if (iBeam == 4) pythia.setPDFPtr( 0, 0);

    // Flip between ppbar and pp - should give different cross section.
    if (iBeam%2 == 0) pythia.init( 2212, -2212, 1960.);
    else              pythia.init( 2212,  2212, 1960.);

    // Generate events.
    for (int iEvent = 0; iEvent < 1000; ++iEvent) pythia.next();

    // Statistics. 
    pythia.statistics();

  // End of subrun loop. Done.
  }

  return 0;
}
