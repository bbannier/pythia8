// main71.cc is a part of the PYTHIA event generator.
// Copyright (C) 2010 Richard Corke, Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// Test program that illustrates how a Les Houches Event File
// written by POWHEG-hvq (top pair production) can processed with
// PYTHIA. For both initial- and final-state radiation, the parton
// showers are started at the kinematical limit, and emissions
// above the POWHEG scale are vetoed.
// For a detailed physics discussion see R. Corke and T. Sjostrand, 
// LU-TP-10-07, MCNET-10-04, arXiv:1003.2384 [hep-ph]. 

#include "Pythia.h"
using namespace Pythia8; 

//==========================================================================

// pT of emissions and vetoing if necessary.

class MyUserHooks : public UserHooks {

public:  

   // Constructor and destructor.
   MyUserHooks() : firstNoRad(true) { }
  ~MyUserHooks() { }

  // Use VetoMIStep to analyse the incoming LHEF event and
  // extract the veto scale
  bool canVetoMIStep()    { return true; }
  int  numberVetoMIStep() { return 1; }
  bool doVetoMIStep(int, const Event &e) {
    // Check that partons 5 and 6 are the t/tbar pair
    if (e[5].id() != 6 || e[6].id() != -6) {
      cout << "Error: could not find t/tbar pair" << endl;
      e.list();
      exit(1);
    }

    // Some events may not have radiation from POWHEG
    switch (e.size()) {
    case 7:
      // No radiation - veto scale is given by the factorisation scale
      pTpowheg = -1.;
      pTveto   = infoPtr->QFac();
      noRad    = true;

      // If this is the first no radiation event, then print scale
      if (firstNoRad) {
        cout << "Info: no POWHEG radiation, Q = " << pTveto
             << " GeV" << endl;
        firstNoRad = false;
      }
      break;

    case 8:
      // Radiation is parton 7 - first check that it is as expected
      if (e[7].id() != 21 && e[7].idAbs() > 5) {
        cout << "Error: jet is not quark/gluon" << endl;
        e.list();
        exit(1);
      }
      // Veto scale is given by jet pT
      pTveto = pTpowheg = e[7].pT();
      noRad  = false;
      break;
    }

    // Initialise other variables
    nISRveto = nFSRveto = 0;
    pTshower = -1.;

    // Do not veto the event
    return false;
  }

  // For subsequent ISR/FSR emissions, find the pT of the shower
  // emission and veto as necessary
  bool canVetoISREmission() { return true; }
  bool doVetoISREmission(int, const Event &e) {
    // ISR - next shower emission is given status 43
    int i;
    for (i = e.size() - 1; i > 6; i--)
      if (e[i].isFinal() && e[i].status() == 43) break;
    if (i == 6) {
      cout << "Error: couldn't find ISR emission" << endl;
      e.list();
      exit(1);
    }

    // Veto if above the POWHEG scale
    if (e[i].pT() > pTveto) {
      nISRveto++;
      return true;
    }
    // Store the first shower emission pT
    if (pTshower < 0.) pTshower = e[i].pT();

    return false;
  }

  bool canVetoFSREmission() { return true; }
  bool doVetoFSREmission(int, const Event &e) {
    // FSR - shower emission will have status 51 and not be t/tbar
    int i;
    for (i = e.size() - 1; i > 6; i--)
      if (e[i].isFinal() && e[i].status() == 51 &&
          e[i].idAbs() != 6) break;
    if (i == 6) {
      cout << "Error: couldn't find FSR emission" << endl;
      e.list();
      exit(1);
    }

    // Veto if above the POWHEG scale
    if (e[i].pT() > pTveto) {
      nFSRveto++;
      return true;
    }
    // Store the first shower emission pT
    if (pTshower < 0.) pTshower = e[i].pT();

    return false;
  }

  // Functions to return information
  double getPTpowheg() { return pTpowheg; }
  double getPTshower() { return pTshower; }
  int    getNISRveto() { return nISRveto; }
  int    getNFSRveto() { return nFSRveto; }
  bool   getNoRad()    { return noRad;    }

private:

  double pTveto, pTpowheg, pTshower;
  int    nISRveto, nFSRveto;
  bool   noRad, firstNoRad;
};

//==========================================================================

int main(int, char **) {

  // Generator
  Pythia pythia;

  // Set the starting shower scales to the kinematic limit
  pythia.readString("SpaceShower:pTmaxMatch = 2");
  pythia.readString("TimeShower:pTmaxMatch  = 2");

  // Turn off MPI, hadronisation and top decays
  // To be commented-out for complete run!
  pythia.readString("PartonLevel:MI = off"); 
  pythia.readString("HadronLevel:All = off"); 
  pythia.particleData.readString("6:mayDecay = off"); 

  // Add in user hooks for shower vetoing
  MyUserHooks *myUserHooks = new MyUserHooks();
  UserHooks* pythiaUserHooks = myUserHooks;
  pythia.setUserHooksPtr(pythiaUserHooks);

  // Initialize Les Houches Event File run.
  pythia.init("powheg-hvq.lhe");
  // List initialization information.
  pythia.settings.listChanged();

  // Histograms
  Hist pTpowhegH("pT of POWHEG emission", 100, 0., 100.);
  Hist pTshowerH("pT of first shower emission", 100, 0., 100.);

  // Counters for events with no POWHEG radiation and number of
  // ISR/FSR emissions vetoed
  int nNoRad = 0, nISRveto = 0, nFSRveto = 0;

  // Begin event loop; generate until none left in input file
  int iEvent = 0;
  while (true) {
    if (iEvent % 10 == 0)
      cout << "Begin event " << iEvent << endl;

    if (!pythia.next()) {
      // If failure because reached end of file then exit event loop
      if (pythia.info.atEndOfFile()) {
        cout << "Info: end of Les Houches file reached" << endl;
        break; 
      }
      cout << "Warning: event " << iEvent << "failed" << endl;
      continue;
    }
  
    // List first event: Les Houches, hard process and complete
    if (iEvent < 1) {
      pythia.LHAeventList();
      pythia.info.list();
      pythia.process.list();
      pythia.event.list();
    }

    // Fill in histograms with information from the UserHooks class
    double pTpowheg = myUserHooks->getPTpowheg();
    if (pTpowheg > 0.)
      pTpowhegH.fill(pTpowheg);

    double pTshower = myUserHooks->getPTshower();
    if (pTshower > 0.)
      pTshowerH.fill(pTshower);

    // Other information from the UserHooks class
    if (myUserHooks->getNoRad() == true) nNoRad++;
    nISRveto += myUserHooks->getNISRveto();
    nFSRveto += myUserHooks->getNFSRveto();

    ++iEvent;
  } // End of event loop.        

  // Statistics, histograms and veto information
  pTpowhegH /= double(iEvent);
  pTshowerH /= double(iEvent);
  pythia.statistics();
  cout << pTpowhegH << pTshowerH << endl;
  cout << "Number of events with no POWHEG radiation: "
       << nNoRad << endl;
  cout << "Number of ISR emissions vetoed: " << nISRveto << endl;
  cout << "Number of FSR emissions vetoed: " << nFSRveto << endl;
  cout << endl;

  // Done.                           
  return 0;
}
