// main10.cc is a part of the PYTHIA event generator.
// Copyright (C) 2010 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// Example how you can use UserHooks to trace pT spectrum through program,
// and veto undesirable jet multiplicities. 

#include "Pythia.h"
using namespace Pythia8; 

//==========================================================================

// Put histograms here to make them global, so they can be used both 
// in MyUserHooks and in the main program.

Hist pTtrial("trial pT spectrum", 100, 0., 400.);
Hist pTselect("selected pT spectrum (before veto)", 100, 0., 400.);
Hist pTaccept("accepted pT spectrum (after veto)", 100, 0., 400.);
Hist nPartonsB("number of partons before veto", 20, -0.5, 19.5);
Hist nJets("number of jets before veto", 20, -0.5, 19.5);
Hist nPartonsA("number of partons after veto", 20, -0.5, 19.5);
Hist nFSRatISR("number of FSR emissions at first ISR emission", 
  20, -0.5, 19.5);

//==========================================================================

// Write own derived UserHooks class.

class MyUserHooks : public UserHooks {

public:

  // Constructor creates cone-jet finder with (etaMax, nEta, nPhi).
  MyUserHooks() { coneJet = new CellJet(5., 100, 64); }

  // Destructor deletes cone-jet finder.
  ~MyUserHooks() {delete coneJet;}

  // Allow process cross section to be modified...
  virtual bool canModifySigma() {return true;}
  
  // ...which gives access to the event at the trial level, before selection.
  virtual double multiplySigmaBy(const SigmaProcess* sigmaProcessPtr,
    const PhaseSpace* phaseSpacePtr, bool inEvent) {

    // All events should be 2 -> 2, but kill them if not.
    if (sigmaProcessPtr->nFinal() != 2) return 0.; 
        
    // Extract the pT for 2 -> 2 processes in the event generation chain
    // (inEvent = false for initialization).
    if (inEvent) { 
      pTHat = phaseSpacePtr->pTHat();
      // Fill histogram of pT spectrum.
      pTtrial.fill( pTHat );
    }
    
    // Here we do not modify 2 -> 2 cross sections.
    return 1.;    
  }

  // Allow a veto for the interleaved evolution in pT.
  virtual bool canVetoPT() {return true;}  

  // Do the veto test at a pT scale of 5 GeV.
  virtual double scaleVetoPT() {return 5.;} 

  // Access the event in the interleaved evolution.
  virtual bool doVetoPT(int iPos, const Event& event) {

    // iPos <= 3 for interleaved evolution; skip others.
    if (iPos > 3) return false;

    // Fill histogram of pT spectrum at this stage.
    pTselect.fill(pTHat);

    // Extract a copy of the partons in the hardest system.
    subEvent(event);
    nPartonsB.fill( workEvent.size() );

    // Find number of jets with eTjet > 10 for R = 0.7.
    coneJet->analyze(event, 10., 0.7);
    int nJet = coneJet->size();      
    nJets.fill( nJet );

    // Veto events which do not have exactly three jets.
    if (nJet != 3) return true;

    // Statistics of survivors.
    nPartonsA.fill( workEvent.size() );
    pTaccept.fill(pTHat);

    // Do not veto events that got this far.
    return false;

  }

  // Allow a veto after (by default) first step.
  virtual bool canVetoStep() {return true;}

  // Access the event in the interleaved evolution after first step.
  virtual bool doVetoStep( int iPos, int nISR, int nFSR, const Event& ) {

    // Only want to study what happens at first ISR emission
    if (iPos == 2 && nISR == 1) nFSRatISR.fill( nFSR );

    // Not intending to veto any events here.
    return false;
  } 

private:

  // The cone-jet finder.
  CellJet* coneJet;

  // Save the pThat scale.
  double pTHat;

};

//==========================================================================

int main() {

  // Generator.
  Pythia pythia;

  //  Process selection. No need to study hadron level.
  pythia.readString("HardQCD:all = on");  
  pythia.readString("PhaseSpace:pTHatMin = 50.");  
  pythia.readString("HadronLevel:all = off");  

  // Set up to do a user veto and send it in.
  MyUserHooks* myUserHooks = new MyUserHooks();
  pythia.setUserHooksPtr( myUserHooks);
 
  // Tevatron initialization. 
  pythia.init( 2212, -2212, 1960.);
   
  // Begin event loop.
  for (int iEvent = 0; iEvent < 1000; ++iEvent) {

    // Generate events. 
    pythia.next();

  // End of event loop.
  }

  // Statistics. Histograms.
  pythia.statistics();
  cout << pTtrial << pTselect << pTaccept 
       << nPartonsB << nJets << nPartonsA 
       << nFSRatISR;

  // Done.
  return 0;
}
