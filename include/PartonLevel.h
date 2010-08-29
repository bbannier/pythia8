// PartonLevel.h is a part of the PYTHIA event generator.
// Copyright (C) 2010 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// This file contains the main class for parton-level event generation
// PartonLevel: administrates showers, multiple interactions and remnants.

#ifndef Pythia8_PartonLevel_H
#define Pythia8_PartonLevel_H

#include "Basics.h"
#include "BeamParticle.h"
#include "BeamRemnants.h"
#include "Event.h"
#include "Info.h"
#include "MultipleInteractions.h"
#include "ParticleData.h"
#include "PartonSystems.h"
#include "PythiaStdlib.h"
#include "Settings.h"
#include "SigmaTotal.h"
#include "SpaceShower.h"
#include "StandardModel.h"
#include "TimeShower.h"
#include "UserHooks.h"

namespace Pythia8 {
 
//==========================================================================

// The PartonLevel class contains the top-level routines to generate
// the partonic activity of an event.

class PartonLevel {

public:

  // Constructor. 
  PartonLevel() : userHooksPtr(0) {} 
 
  // Initialization of all classes at the parton level.
  bool init( Info* infoPtrIn, Settings& settings,
    ParticleData* particleDataPtrIn, Rndm* rndmPtrIn, 
    BeamParticle* beamAPtrIn, BeamParticle* beamBPtrIn, 
    BeamParticle* beamPomAPtrIn, BeamParticle* beamPomBPtrIn, 
    CoupSM* coupSMPtrIn, PartonSystems* partonSystemsPtrIn, 
    SigmaTotal* sigmaTotPtr, TimeShower* timesDecPtrIn, 
    TimeShower* timesPtrIn, SpaceShower* spacePtrIn, 
    UserHooks* userHooksPtrIn);
 
  // Generate the next parton-level process.
  bool next( Event& process, Event& event); 

  // Tell whether failure was due to vetoing.
  bool hasVetoed() const {return doVeto;}

  // Accumulate and print statistics.
  void accumulate() {multiPtr->accumulate();}
  void statistics(bool reset = false) {
    if (doMI) multiMB.statistics(reset);}
    // For now no separate statistics for diffraction??
    //if (doMISDA && doDiffraction) multiSDA.statistics(reset); 
    //if (doMISDB && doDiffraction) multiSDB.statistics(reset);}

private: 

  // Constants: could only be changed in the code itself.
  static const int NTRY;

  // Initialization data, mainly read from Settings.
  bool   doMinBias, doDiffraction, doMI, doMIMB, doMISDA, doMISDB, doMIinit, 
         doISR, doFSRduringProcess, doFSRafterProcess,  doFSRinResonances, 
         doRemnants, doSecondHard, hasLeptonBeams, hasPointLeptons, 
         canVetoPT, canVetoStep, canVetoMIStep, canSetScale;
  double mMinDiff, mWidthDiff;

  // Event generation strategy. Number of steps. Maximum pT scales.
  bool   doVeto;
  int    nMI, nISR, nFSRinProc, nFSRinRes, nISRhard, nFSRhard, 
         typeLatest, nVetoStep, typeVetoStep, nVetoMIStep, iSysNow;
  double pTsaveMI, pTsaveISR, pTsaveFSR, pTvetoPT;

  // Current event properties.
  bool   isMinBias, isDiffA, isDiffB, isDiff, isSingleDiff, isDoubleDiff, 
         isResolved, isResolvedA, isResolvedB;
  int    sizeProcess, sizeEvent;
  double eCMsave; 

  // Pointer to various information on the generation.
  Info*          infoPtr;

  // Pointer to the particle data table.
  ParticleData*  particleDataPtr;

  // Pointer to the random number generator.
  Rndm*          rndmPtr;

  // Pointers to the two incoming beams.
  BeamParticle*  beamAPtr;
  BeamParticle*  beamBPtr;

  // Spare copies of normal pointers. Pointers to Pomeron beam-inside-beam.
  BeamParticle*  beamHadAPtr;  
  BeamParticle*  beamHadBPtr;  
  BeamParticle*  beamPomAPtr;
  BeamParticle*  beamPomBPtr;

  // Pointers to Standard Model couplings.
  CoupSM*        coupSMPtr;
  
  // Pointer to information on subcollision parton locations.
  PartonSystems* partonSystemsPtr;

  // Pointer to userHooks object for user interaction with program.
  UserHooks*     userHooksPtr;

  // Pointers to timelike showers for resonance decays and the rest.
  TimeShower*    timesDecPtr;
  TimeShower*    timesPtr;

  // Pointer to spacelike showers.
  SpaceShower*   spacePtr;

  // The generator classes for multiple interactions.
  MultipleInteractions  multiMB;
  MultipleInteractions  multiSDA;
  MultipleInteractions  multiSDB;
  MultipleInteractions* multiPtr;

  // The generator class to construct beam-remnant kinematics. 
  BeamRemnants remnants;

  // Resolved diffraction: find how many systems should have it.
  int decideResolvedDiff( Event& process);

  // Set up an unresolved process, i.e. elastic or diffractive.
  bool setupUnresolvedSys( Event& process, Event& event);

  // Set up the hard process, excluding subsequent resonance decays.
  void setupHardSys( int iHardLoop, Event& process, Event& event);
  // Keep track of how much of hard process has been handled.
  int nHardDone;

  // Resolved diffraction: pick whether to have it and set up for it.
  void setupResolvedDiff( int iHardLoop, Event& process);

  // Resolved diffraction: restore normal behaviour.
  void leaveResolvedDiff( int iHardLoop, Event& event);

  // Perform showers in resonance decay chains.
  bool resonanceShowers( Event& process, Event& event); 

  // Position in main event record of hard partons before showers.
  vector<int> iPosBefShow;
  
};

//==========================================================================

} // end namespace Pythia8

#endif // Pythia8_PartonLevel_H
