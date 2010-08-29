// ProcessLevel.cc is a part of the PYTHIA event generator.
// Copyright (C) 2010 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// Function definitions (not found in the header) for the ProcessLevel class.

#include "ProcessLevel.h"

namespace Pythia8 {
 
//==========================================================================

// The ProcessLevel class.

//--------------------------------------------------------------------------

// Constants: could be changed here if desired, but normally should not.
// These are of technical nature, as described for each.

// Allow a few failures in final construction of events.
const int ProcessLevel::MAXLOOP = 5;

//--------------------------------------------------------------------------
  
// Destructor.

ProcessLevel::~ProcessLevel() { 

  // Run through list of first hard processes and delete them.
  for (int i = 0; i < int(containerPtrs.size()); ++i)
    delete containerPtrs[i];

  // Run through list of second hard processes and delete them.
  for (int i =0; i < int(container2Ptrs.size()); ++i)
    delete container2Ptrs[i];

} 

//--------------------------------------------------------------------------

// Main routine to initialize generation process.

bool ProcessLevel::init( Info* infoPtrIn, Settings& settings, 
  ParticleData* particleDataPtrIn, Rndm* rndmPtrIn, 
  BeamParticle* beamAPtrIn, BeamParticle* beamBPtrIn, CoupSM* coupSMPtrIn,
  SigmaTotal* sigmaTotPtrIn, bool doLHA, SusyLesHouches* slhaPtrIn, 
  UserHooks* userHooksPtrIn, vector<SigmaProcess*>& sigmaPtrs, ostream& os) {

  // Store input pointers for future use. 
  infoPtr         = infoPtrIn;
  particleDataPtr = particleDataPtrIn;
  rndmPtr         = rndmPtrIn;
  beamAPtr        = beamAPtrIn;
  beamBPtr        = beamBPtrIn;
  coupSMPtr       = coupSMPtrIn;
  sigmaTotPtr     = sigmaTotPtrIn;
  userHooksPtr    = userHooksPtrIn;
  slhaPtr         = slhaPtrIn;

  // Send on some input pointers.
  resonanceDecays.init( infoPtr, particleDataPtr, rndmPtr);

  // Set up SigmaTotal. Store sigma_nondiffractive for future use.
  sigmaTotPtr->init( infoPtr, settings, particleDataPtr);
  int    idA = infoPtr->idA();
  int    idB = infoPtr->idB();
  double eCM = infoPtr->eCM();
  sigmaTotPtr->calc( idA, idB, eCM);
  sigmaND = sigmaTotPtr->sigmaND();

  // Options to allow second hard interaction and resonance decays.
  doSecondHard  = settings.flag("SecondHard:generate");
  doSameCuts    = settings.flag("PhaseSpace:sameForSecond");
  doResDecays   = settings.flag("ProcessLevel:resonanceDecays");
  startColTag   = settings.mode("Event:startColTag");

  // Mass and pT cuts for two hard processes.
  mHatMin1      = settings.parm("PhaseSpace:mHatMin");
  mHatMax1      = settings.parm("PhaseSpace:mHatMax");
  if (mHatMax1 < mHatMin1) mHatMax1 = eCM;
  pTHatMin1     = settings.parm("PhaseSpace:pTHatMin");
  pTHatMax1     = settings.parm("PhaseSpace:pTHatMax");
  if (pTHatMax1 < pTHatMin1) pTHatMax1 = eCM;
  mHatMin2      = settings.parm("PhaseSpace:mHatMinSecond");
  mHatMax2      = settings.parm("PhaseSpace:mHatMaxSecond");
  if (mHatMax2 < mHatMin2) mHatMax2 = eCM;
  pTHatMin2     = settings.parm("PhaseSpace:pTHatMinSecond");
  pTHatMax2     = settings.parm("PhaseSpace:pTHatMaxSecond");
  if (pTHatMax2 < pTHatMin2) pTHatMax2 = eCM;
  
  // Check whether mass and pT ranges agree or overlap.
  cutsAgree     = doSameCuts;
  if (mHatMin2 == mHatMin1 && mHatMax2 == mHatMax1 && pTHatMin2 == pTHatMin1 
      && pTHatMax2 == pTHatMax1) cutsAgree = true; 
  cutsOverlap   = cutsAgree; 
  if (!cutsAgree) {
    bool mHatOverlap = (max( mHatMin1, mHatMin2)
                      < min( mHatMax1, mHatMax2));
    bool pTHatOverlap = (max( pTHatMin1, pTHatMin2) 
                       < min( pTHatMax1, pTHatMax2));
    if (mHatOverlap && pTHatOverlap) cutsOverlap = true;
  }

  // Initialize SUSY Les Houches Accord data
  if (!initSLHA(settings)) return false;

  // Set up containers for all the internal hard processes.
  SetupContainers setupContainers;
  setupContainers.init(containerPtrs, settings, particleDataPtr, coupSUSY);

  // Append containers for external hard processes, if any.
  if (sigmaPtrs.size() > 0) {
    for (int iSig = 0; iSig < int(sigmaPtrs.size()); ++iSig)
      containerPtrs.push_back( new ProcessContainer(sigmaPtrs[iSig],
      true) );
  } 

  // Append single container for Les Houches processes, if any.
  if (doLHA) {
    SigmaProcess* sigmaPtr = new SigmaLHAProcess();
    containerPtrs.push_back( new ProcessContainer(sigmaPtr) );

    // Store location of this container, and send in LHA pointer.
    iLHACont = containerPtrs.size() - 1;
    containerPtrs[iLHACont]->setLHAPtr(lhaUpPtr);
  }     

  // If no processes found then refuse to do anything.
  if ( int(containerPtrs.size()) == 0) {
    infoPtr->errorMsg("Error in ProcessLevel::init: "
      "no process switched on"); 
    return false;
  }

  // Check that SUSY couplings were indeed initialized where necessary.
  bool hasSUSY = false;
  for (int i = 0; i < int(containerPtrs.size()); ++i)
    if (containerPtrs[i]->isSUSY()) hasSUSY = true;
  if (hasSUSY && !coupSUSY.isInit) coupSUSY.init(slhaPtr, &settings, 
    particleDataPtr, coupSMPtr); 

  // Initialize each process. 
  int numberOn = 0;
  for (int i = 0; i < int(containerPtrs.size()); ++i)
    if (containerPtrs[i]->init(true, infoPtr, settings, particleDataPtr, 
      rndmPtr, beamAPtr, beamBPtr, coupSMPtr, sigmaTotPtr, &coupSUSY, 
      &resonanceDecays, slhaPtr, userHooksPtr)) ++numberOn;

  // Sum maxima for Monte Carlo choice.
  sigmaMaxSum = 0.;
  for (int i = 0; i < int(containerPtrs.size()); ++i)
    sigmaMaxSum += containerPtrs[i]->sigmaMax();

  // Option to pick a second hard interaction: repeat as above.
  int number2On = 0;
  if (doSecondHard) {
    setupContainers.init2(container2Ptrs, settings);
    if ( int(container2Ptrs.size()) == 0) {
      infoPtr->errorMsg("Error in ProcessLevel::init: "
        "no second hard process switched on"); 
      return false;
    }
    for (int i2 = 0; i2 < int(container2Ptrs.size()); ++i2)
      if (container2Ptrs[i2]->init(false, infoPtr, settings, particleDataPtr, 
        rndmPtr, beamAPtr, beamBPtr, coupSMPtr, sigmaTotPtr, &coupSUSY, 
        &resonanceDecays, slhaPtr, userHooksPtr)) ++number2On;
    sigma2MaxSum = 0.;
    for (int i2 = 0; i2 < int(container2Ptrs.size()); ++i2)
      sigma2MaxSum += container2Ptrs[i2]->sigmaMax();
  }

  // Construct string with incoming beams and for cm energy.
  string collision = "We collide " + particleDataPtr->name(idA)
    + " with " + particleDataPtr->name(idB) + " at a CM energy of "; 
  string pad( 51 - collision.length(), ' ');

  // Print initialization information: header.
  os << "\n *-------  PYTHIA Process Initialization  ---------"
     << "-----------------*\n"
     << " |                                                   "
     << "               |\n" 
     << " | " << collision << scientific << setprecision(3)<< setw(9) << eCM 
     << " GeV" << pad << " |\n"
     << " |                                                   "
     << "               |\n"
     << " |---------------------------------------------------"
     << "---------------|\n"
     << " |                                                   "
     << " |             |\n"
     << " | Subprocess                                    Code"
     << " |   Estimated |\n" 
     << " |                                                   "
     << " |    max (mb) |\n"
     << " |                                                   "
     << " |             |\n"
     << " |---------------------------------------------------"
     << "---------------|\n"
     << " |                                                   "
     << " |             |\n";


  // Loop over existing processes: print individual process info.
  for (int i = 0; i < int(containerPtrs.size()); ++i) 
  os << " | " << left << setw(45) << containerPtrs[i]->name() 
     << right << setw(5) << containerPtrs[i]->code() << " | " 
     << scientific << setprecision(3) << setw(11)  
     << containerPtrs[i]->sigmaMax() << " |\n";

  // Loop over second hard processes, if any, and repeat as above.
  if (doSecondHard) {
    os << " |                                                   "
       << " |             |\n"
       << " |---------------------------------------------------"
       <<"---------------|\n"
       << " |                                                   "
       <<" |             |\n";
    for (int i2 = 0; i2 < int(container2Ptrs.size()); ++i2) 
    os << " | " << left << setw(45) << container2Ptrs[i2]->name() 
       << right << setw(5) << container2Ptrs[i2]->code() << " | " 
       << scientific << setprecision(3) << setw(11)  
       << container2Ptrs[i2]->sigmaMax() << " |\n";
  }

  // Listing finished.
  os << " |                                                     "
     << "             |\n" 
     << " *-------  End PYTHIA Process Initialization ----------"
     <<"-------------*" << endl;

  // If sum of maxima vanishes then refuse to do anything.
  if ( numberOn == 0  || sigmaMaxSum <= 0.) {
    infoPtr->errorMsg("Error in ProcessLevel::init: "
      "all processes have vanishing cross sections"); 
    return false;
  }
  if ( doSecondHard && (number2On == 0  || sigma2MaxSum <= 0.) ) {
    infoPtr->errorMsg("Error in ProcessLevel::init: "
      "all second hard processes have vanishing cross sections"); 
    return false;
  }
  
  // If two hard processes then check whether some (but not all) agree.
  allHardSame  = true;
  noneHardSame = true;
  if (doSecondHard) {
    bool foundMatch = false;
    
    // Check for each first process if matched in second.
    for (int i = 0; i < int(containerPtrs.size()); ++i) {
      foundMatch = false;
      if (cutsOverlap)
      for (int i2 = 0; i2 < int(container2Ptrs.size()); ++i2) 
        if (container2Ptrs[i2]->code() == containerPtrs[i]->code()) 
          foundMatch = true;
      containerPtrs[i]->isSame( foundMatch );
      if (!foundMatch)  allHardSame = false;
      if ( foundMatch) noneHardSame = false; 
    }

    // Check for each second process if matched in first.
    for (int i2 = 0; i2 < int(container2Ptrs.size()); ++i2) {
      foundMatch = false;
      if (cutsOverlap)
      for (int i = 0; i < int(containerPtrs.size()); ++i) 
        if (containerPtrs[i]->code() == container2Ptrs[i2]->code()) 
          foundMatch = true;
      container2Ptrs[i2]->isSame( foundMatch );
      if (!foundMatch)  allHardSame = false;
      if ( foundMatch) noneHardSame = false;   
    }
  }

  // Concluding classification, including cuts.
  if (!cutsAgree) allHardSame = false;
  someHardSame = !allHardSame && !noneHardSame;

  // Reset counters for average impact-parameter enhancement.
  nImpact       = 0;
  sumImpactFac  = 0.;
  sum2ImpactFac = 0.;

  // Statistics for LHA events.
  codeLHA.resize(0);
  nEvtLHA.resize(0);

  // Done.
  return true;
}

//--------------------------------------------------------------------------

// Main routine to generate the hard process.

bool ProcessLevel::next( Event& process) {

  // Generate the next event with two or one hard interactions. 
  bool physical = (doSecondHard) ? nextTwo( process) : nextOne( process);

  // Check that colour assignments make sense.
  if (physical) physical = checkColours( process);

  // Done.
  return physical;
}

//--------------------------------------------------------------------------

// Accumulate and update statistics (after possible user veto).
  
void ProcessLevel::accumulate() {

  // Increase number of accepted events.
  containerPtrs[iContainer]->accumulate();

  // Provide current generated cross section estimate.
  long   nTrySum    = 0; 
  long   nSelSum    = 0; 
  long   nAccSum    = 0;
  double sigmaSum   = 0.;
  double delta2Sum  = 0.;
  double sigSelSum  = 0.;
  for (int i = 0; i < int(containerPtrs.size()); ++i) 
  if (containerPtrs[i]->sigmaMax() != 0.) {
    nTrySum        += containerPtrs[i]->nTried();
    nSelSum        += containerPtrs[i]->nSelected();
    nAccSum        += containerPtrs[i]->nAccepted();
    sigmaSum       += containerPtrs[i]->sigmaMC();
    delta2Sum      += pow2(containerPtrs[i]->deltaMC()); 
    sigSelSum      += containerPtrs[i]->sigmaSelMC();
  }

  // For Les Houches events find subprocess type and update counter.
  if (infoPtr->isLHA()) {
    int codeLHANow = infoPtr->codeSub();
    int iFill = -1;
    for (int i = 0; i < int(codeLHA.size()); ++i)
      if (codeLHANow == codeLHA[i]) iFill = i;
    if (iFill >= 0) ++nEvtLHA[iFill];

    // Add new process when new code and then arrange in order. 
    else {
      codeLHA.push_back(codeLHANow);
      nEvtLHA.push_back(1);
      for (int i = int(codeLHA.size()) - 1; i > 0; --i) {
        if (codeLHA[i] < codeLHA[i - 1]) { 
          swap(codeLHA[i], codeLHA[i - 1]);
          swap(nEvtLHA[i], nEvtLHA[i - 1]);
	} 
        else break;
      }
    }
  }

  // Normally only one hard interaction. Then store info and done.
  if (!doSecondHard) {
    double deltaSum = sqrtpos(delta2Sum);
    infoPtr->setSigma( nTrySum, nSelSum, nAccSum, sigmaSum, deltaSum); 
    return;
  }

  // Increase counter for a second hard interaction.
  container2Ptrs[i2Container]->accumulate();

  // Update statistics on average impact factor.
  ++nImpact;
  sumImpactFac     += infoPtr->enhanceMI();
  sum2ImpactFac    += pow2(infoPtr->enhanceMI());

  // Cross section estimate for second hard process.
  double sigma2Sum  = 0.;
  double sig2SelSum = 0.;
  for (int i2 = 0; i2 < int(container2Ptrs.size()); ++i2) 
  if (container2Ptrs[i2]->sigmaMax() != 0.) {
    nTrySum        += container2Ptrs[i2]->nTried();
    sigma2Sum      += container2Ptrs[i2]->sigmaMC();
    sig2SelSum     += container2Ptrs[i2]->sigmaSelMC();
  }

  // Average impact-parameter factor and error.
  double invN       = 1. / max(1, nImpact);
  double impactFac  = max( 1., sumImpactFac * invN);
  double impactErr2 = ( sum2ImpactFac * invN / pow2(impactFac) - 1.) * invN;
     
  // Cross section estimate for combination of first and second process.
  // Combine two possible ways and take average.
  double sigmaComb  = 0.5 * (sigmaSum * sig2SelSum + sigSelSum * sigma2Sum);
  sigmaComb        *= impactFac / sigmaND;
  if (allHardSame) sigmaComb *= 0.5; 
  double deltaComb  = sqrtpos(2. / nAccSum + impactErr2) * sigmaComb;

  // Store info and done.
  infoPtr->setSigma( nTrySum, nSelSum, nAccSum, sigmaComb, deltaComb); 
 
}

//--------------------------------------------------------------------------

// Print statistics on cross sections and number of events.

void ProcessLevel::statistics(bool reset, ostream& os) {

  // Special processing if two hard interactions selected.
  if (doSecondHard) { 
    statistics2(reset, os);
    return;
  } 
    
  // Header.
  os << "\n *-------  PYTHIA Event and Cross Section Statistics  ------"
     << "-------------------------------------------------------*\n"
     << " |                                                            "
     << "                                                     |\n" 
     << " | Subprocess                                    Code |       "
     << "     Number of events       |      sigma +- delta    |\n" 
     << " |                                                    |       "
     << "Tried   Selected   Accepted |     (estimated) (mb)   |\n"
     << " |                                                    |       "
     << "                            |                        |\n"
     << " |------------------------------------------------------------"
     << "-----------------------------------------------------|\n"
     << " |                                                    |       "
     << "                            |                        |\n";

  // Reset sum counters.
  long   nTrySum   = 0; 
  long   nSelSum   = 0; 
  long   nAccSum   = 0;
  double sigmaSum  = 0.;
  double delta2Sum = 0.;

  // Loop over existing processes.
  for (int i = 0; i < int(containerPtrs.size()); ++i) 
  if (containerPtrs[i]->sigmaMax() != 0.) {

    // Read info for process. Sum counters.
    long   nTry    = containerPtrs[i]->nTried();
    long   nSel    = containerPtrs[i]->nSelected();
    long   nAcc    = containerPtrs[i]->nAccepted();
    double sigma   = containerPtrs[i]->sigmaMC();
    double delta   = containerPtrs[i]->deltaMC(); 
    nTrySum       += nTry;
    nSelSum       += nSel;
    nAccSum       += nAcc; 
    sigmaSum      += sigma;
    delta2Sum     += pow2(delta);    

    // Print individual process info.
    os << " | " << left << setw(45) << containerPtrs[i]->name() 
       << right << setw(5) << containerPtrs[i]->code() << " | " 
       << setw(11) << nTry << " " << setw(10) << nSel << " " 
       << setw(10) << nAcc << " | " << scientific << setprecision(3) 
       << setw(11) << sigma << setw(11) << delta << " |\n";

    // Print subdivision by user code for Les Houches process.
    if (containerPtrs[i]->code() == 9999) 
    for (int j = 0; j < int(codeLHA.size()); ++j)
      os << " |    ... whereof user classification code " << setw(10) 
         << codeLHA[j] << " |                        " << setw(10) 
         << nEvtLHA[j] << " |                        | \n";
  }

  // Print summed process info.
  os << " |                                                    |       "
     << "                            |                        |\n"
     << " | " << left << setw(50) << "sum" << right << " | " << setw(11) 
     << nTrySum << " " << setw(10) << nSelSum << " " << setw(10) 
     << nAccSum << " | " << scientific << setprecision(3) << setw(11) 
     << sigmaSum << setw(11) << sqrtpos(delta2Sum) << " |\n";

  // Listing finished.
  os << " |                                                            "
     << "                                                     |\n"
     << " *-------  End PYTHIA Event and Cross Section Statistics -----"
     << "-----------------------------------------------------*" << endl;

  // Optionally reset statistics contants.
  if (reset) for (int i = 0; i < int(containerPtrs.size()); ++i) 
    containerPtrs[i]->reset();

}

//--------------------------------------------------------------------------

// Initialize SUSY Les Houches Accord data.

bool ProcessLevel::initSLHA(Settings& settings) {

  // Initial and settings values.
  int    ifailLHE    = 1;
  int    ifailSpc    = 1;
  int    ifailDec    = 1;
  int    readFrom    = settings.mode("SLHA:readFrom");
  string lhefFile    = settings.word("Beams:LHEF");
  string slhaFile    = settings.word("SLHA:file");
  int    verboseSLHA = settings.mode("SLHA:verbose");

  // Option with no SLHA read-in at all.
  if (readFrom == 0) return true;  

  // First check LHEF header (if reading from LHEF)
  if (readFrom == 1 && lhefFile != "void") {
    ifailLHE = slhaPtr->readFile(lhefFile, verboseSLHA);    
  }

  // If LHEF read successful, everything needed should already be ready
  if (ifailLHE == 0) {
    ifailSpc = 0;
    ifailDec = 0;
  // If no LHEF file or no SLHA info in header, read from SLHA:file
  } else {
    lhefFile = "void";
    if ( settings.word("SLHA:file") == "none"
	 || settings.word("SLHA:file") == "void" 
	 || settings.word("SLHA:file") == "" 
	 || settings.word("SLHA:file") == " ") return true;      
    ifailSpc = slhaPtr->readFile(slhaFile,verboseSLHA);
  }

  // In case of problems, print error and fail init.
  if (ifailSpc != 0) {
    infoPtr->errorMsg("Error in ProcessLevel::initSLHA: "
      "problem reading SLHA file", slhaFile);
    return false;
  };

  /*
  // Check decays for consistency (replaced by internal Pythia check below)
  ifailDec = slhaPtr->checkDecays();
  if (ifailDec != 0) {
    infoPtr->errorMsg("Warning in ProcessLevel::initSLHA: "
		      "Problem with SLHA decay tables.");     
  }
  */
  
  // Check spectrum for consistency. Switch off SUSY if necessary.
  ifailSpc = slhaPtr->checkSpectrum();
  // ifail > 1 : no MODSEL found -> don't switch on SUSY
  if (ifailSpc == 1) {
    // no SUSY, but MASS ok
  } else if (ifailSpc >= 2) {
    // no SUSY, but problems    
    infoPtr->errorMsg("Warning in ProcessLevel::initSLHA: "
		      "Problem with SLHA MASS or QNUMBERS.");    
  }
  // ifail = 0 : MODSEL found, spectrum OK
  else if (ifailSpc == 0) {
    // Print spectrum. Done. 
    slhaPtr->printSpectrum();
  }
  else if (ifailSpc < 0) {
    infoPtr->errorMsg("Warning in ProcessLevel::initSLHA: "
		      "Problem with SLHA spectrum.", 
		      "\n Only using masses and switching off SUSY.");
    settings.flag("SUSY:all", false);
    slhaPtr->printSpectrum();
  } 

  // Import mass spectrum.
  bool   keepSM    = settings.flag("SLHA:keepSM");
  double minMassSM = settings.parm("SLHA:minMassSM");
  if (ifailSpc == 1 || ifailSpc == 0) {

    // Loop through to update particle data.
    int    id = slhaPtr->mass.first();
    for (int i = 1; i <= slhaPtr->mass.size() ; i++) {
      double mass = abs(slhaPtr->mass(id));

      // Ignore masses for known SM particles or particles with 
      // default masses < minMassSM; overwrite masses for rest.
      if (keepSM && (id < 25 || (id > 80 && id < 1000000))) ;
      else if (id < 1000000 && particleDataPtr->m0(id) < minMassSM) {
	ostringstream idCode;
	idCode << id;      
	infoPtr->errorMsg("Warning in ProcessLevel::initSLHA: "
	  "ignoring MASS entry", "for id = "+idCode.str()
	  +" (m0 < SLHA:minMassSM)", true);
      } 
      else particleDataPtr->m0(id,mass);
      id = slhaPtr->mass.next();
    };

    // Init SUSY couplings
    if (ifailSpc == 0) coupSUSY.init(slhaPtr, &settings, particleDataPtr, 
      coupSMPtr);       

  }

  // Update decay data.
  for (int iTable=0; iTable < int(slhaPtr->decays.size()); iTable++) {
    
    // Pointer to this SLHA table
    SusyLesHouches::decayTable* slhaTable=&slhaPtr->decays[iTable];
    
    // Extract ID and create pointer to corresponding particle data object
    int idRes     = slhaTable->getId();
    ParticleDataEntry* particlePtr 
      = particleDataPtr->particleDataEntryPtr(idRes);
    
    // Ignore decay channels for known SM particles or particles with 
    // default masses < minMassSM; overwrite masses for rest.
    if (keepSM && (idRes < 25 || (idRes > 80 && idRes < 1000000))) continue;
    else if (idRes < 1000000 && particleDataPtr->m0(idRes) < minMassSM) {
      ostringstream idCode;
      idCode << idRes;      
      infoPtr->errorMsg("Warning in ProcessLevel::initSLHA: "
        "ignoring DECAY table", "for id = " + idCode.str()
	+ " (m0 < SLHA:minMassSM)", true);
      continue;
    }
    
    // Extract and store total width (absolute value, neg -> switch off)
    double widRes = abs(slhaTable->getWidth());
    particlePtr->setMWidth(widRes);
    
    // Reset decay table of the particle. Allow decays.
    if (slhaTable->size() > 0) {
      particlePtr->clearChannels();
      particleDataPtr->mayDecay(idRes,true);
    }        
    
    // Reset to stable if width <= 0.0
    if (slhaTable->getWidth() <= 0.0) particleDataPtr->mayDecay(idRes,false);
    
    // Mass margin between lowest mass allowed and "average" decay channel.
    double massMargin = 1.;
    
    // Set initial minimum mass.
    double brWTsum   = 0.;
    double massWTsum = 0.;
    
    // Loop over SLHA channels, import into Pythia, treating channels
    // with negative branching fractions as having the equivalent positive
    // branching fraction, but being switched off for this run
    for (int iChannel=0 ; iChannel<slhaTable->size(); iChannel++) {
      SusyLesHouches::decayChannel slhaChannel = slhaTable->getChannel(iChannel);
      double brat      = slhaChannel.getBrat();
      vector<int> idDa = slhaChannel.getIdDa();
      if (idDa.size() >= 9) {
	infoPtr->errorMsg("Error in ProcessLevel::initSLHA: "
			  "max number of decay products is 8.");
      } else if (idDa.size() <= 1) {
	infoPtr->errorMsg("Error in ProcessLevel::initSLHA: "
			  "min number of decay products is 2.");	  
      }
      else {
	int onMode = 1;
	if (brat < 0.0) onMode = 0;
	
	// Check phase space, including margin
	double massSum = massMargin;
	for (int jDa=0; jDa<int(idDa.size()); ++jDa) 
	  massSum += particleDataPtr->m0( idDa[jDa] ); 
	if (onMode == 1 && brat > 0.0 && massSum > particleDataPtr->m0(idRes) ) {
	  // String containing decay name
	  ostringstream errCode;
	  errCode << idRes <<" ->";
	  for (int jDa=0; jDa<int(idDa.size()); ++jDa) errCode<<" "<<idDa[jDa];
	  infoPtr->errorMsg("Warning in ProcessLevel::initSLHA: "
	    "switching off decay",  errCode.str() + " (mRes - mDa < massMargin)"
            "\n       (Note: cross sections will be scaled by remaining"
	    " open branching fractions!)" , true);
	  onMode=0;
	}
	
	// Branching-ratio-weighted average mass in decay.
	brWTsum   += abs(brat);
	massWTsum += abs(brat) * massSum;
	
	// Add channel
	int id0 = idDa[0];
	int id1 = idDa[1];
	int id2 = (idDa.size() >= 3) ? idDa[2] : 0;
	int id3 = (idDa.size() >= 4) ? idDa[3] : 0;
	int id4 = (idDa.size() >= 5) ? idDa[4] : 0;
	int id5 = (idDa.size() >= 6) ? idDa[5] : 0;
	int id6 = (idDa.size() >= 7) ? idDa[6] : 0;
	int id7 = (idDa.size() >= 8) ? idDa[7] : 0;
	particlePtr->addChannel(onMode,abs(brat),101,
				      id0,id1,id2,id3,id4,id5,id6,id7);
	
      }
    }
    
    // Set minimal mass, but always below nominal one.
    if (slhaTable->size() > 0) {
      double massAvg = massWTsum / brWTsum;
      double massMin = min( massAvg, particlePtr->m0()) - massMargin;
      particlePtr->setMMin(massMin);
    }
  }
  
  return true;
  
}

//--------------------------------------------------------------------------

// Generate the next event with one interaction.
  
bool ProcessLevel::nextOne( Event& process) {
  
  // Update CM energy for phase space selection.
  double eCM = infoPtr->eCM();
  for (int i = 0; i < int(containerPtrs.size()); ++i)
    containerPtrs[i]->newECM(eCM);

  // Outer loop in case of rare failures.
  bool physical = true;
  for (int loop = 0; loop < MAXLOOP; ++loop) {
    if (!physical) process.clear();
    physical = true;

    // Loop over tries until trial event succeeds.
    for ( ; ; ) {

      // Pick one of the subprocesses.
      double sigmaMaxNow = sigmaMaxSum * rndmPtr->flat();
      int iMax = containerPtrs.size() - 1;
      iContainer = -1;
      do sigmaMaxNow -= containerPtrs[++iContainer]->sigmaMax();
      while (sigmaMaxNow > 0. && iContainer < iMax);
    
      // Do a trial event of this subprocess; accept or not.
      if (containerPtrs[iContainer]->trialProcess()) break;

      // Check for end-of-file condition for Les Houches events.
      if (infoPtr->atEndOfFile()) return false;
    }

    // Update sum of maxima if current maximum violated.
    if (containerPtrs[iContainer]->newSigmaMax()) {
      sigmaMaxSum = 0.;
      for (int i = 0; i < int(containerPtrs.size()); ++i)
        sigmaMaxSum += containerPtrs[i]->sigmaMax();
    }

    // Construct kinematics of acceptable process.
    if ( !containerPtrs[iContainer]->constructProcess( process) )
      physical = false;

    // Do all resonance decays.
    if ( physical && doResDecays 
      && !containerPtrs[iContainer]->decayResonances( process) ) 
      physical = false;

    // Add any junctions to the process event record list.
    if (physical) findJunctions( process);

    // Outer loop should normally work first time around.
    if (physical) break;
  }

  // Done.
  return physical;
}

//--------------------------------------------------------------------------

// Generate the next event with two hard interactions.
  
bool ProcessLevel::nextTwo( Event& process) {
  
  // Update CM energy for phase space selection.
  double eCM = infoPtr->eCM();
  for (int i = 0; i < int(containerPtrs.size()); ++i)
    containerPtrs[i]->newECM(eCM);
  for (int i2 = 0; i2 < int(container2Ptrs.size()); ++i2)
    container2Ptrs[i2]->newECM(eCM);

  // Outer loop in case of rare failures.
  bool physical = true;
  for (int loop = 0; loop < MAXLOOP; ++loop) {
    if (!physical) process.clear();
    physical = true;

    // Loop over both hard processes to find consistent common kinematics.
    for ( ; ; ) {
   
      // Loop internally over tries for hardest process until succeeds.
      for ( ; ; ) {

        // Pick one of the subprocesses.
        double sigmaMaxNow = sigmaMaxSum * rndmPtr->flat();
        int iMax = containerPtrs.size() - 1;
        iContainer = -1;
        do sigmaMaxNow -= containerPtrs[++iContainer]->sigmaMax();
        while (sigmaMaxNow > 0. && iContainer < iMax);
      
        // Do a trial event of this subprocess; accept or not.
        if (containerPtrs[iContainer]->trialProcess()) break;

        // Check for end-of-file condition for Les Houches events.
        if (infoPtr->atEndOfFile()) return false;
      }

      // Update sum of maxima if current maximum violated.
      if (containerPtrs[iContainer]->newSigmaMax()) {
        sigmaMaxSum = 0.;
        for (int i = 0; i < int(containerPtrs.size()); ++i)
          sigmaMaxSum += containerPtrs[i]->sigmaMax();
      }

      // Loop internally over tries for second hardest process until succeeds.
      for ( ; ; ) {

        // Pick one of the subprocesses.
        double sigma2MaxNow = sigma2MaxSum * rndmPtr->flat();
        int i2Max = container2Ptrs.size() - 1;
        i2Container = -1;
        do sigma2MaxNow -= container2Ptrs[++i2Container]->sigmaMax();
        while (sigma2MaxNow > 0. && i2Container < i2Max);
    
        // Do a trial event of this subprocess; accept or not.
        if (container2Ptrs[i2Container]->trialProcess()) break;
      }

      // Update sum of maxima if current maximum violated.
      if (container2Ptrs[i2Container]->newSigmaMax()) {
        sigma2MaxSum = 0.;
        for (int i2 = 0; i2 < int(container2Ptrs.size()); ++i2)
          sigma2MaxSum += container2Ptrs[i2]->sigmaMax();
      }

      // Check whether common set of x values is kinematically possible.
      double xA1      = containerPtrs[iContainer]->x1();
      double xB1      = containerPtrs[iContainer]->x2();
      double xA2      = container2Ptrs[i2Container]->x1();
      double xB2      = container2Ptrs[i2Container]->x2();    
      if (xA1 + xA2 >= 1. || xB1 + xB2 >= 1.) continue;

      // Reset beam contents. Naive parton densities for second interaction.
      // (Subsequent procedure could be symmetrized, but would be overkill.)
      beamAPtr->clear();    
      beamBPtr->clear();    
      int    idA1     = containerPtrs[iContainer]->id1();
      int    idB1     = containerPtrs[iContainer]->id2();
      int    idA2     = container2Ptrs[i2Container]->id1();
      int    idB2     = container2Ptrs[i2Container]->id2();
      double Q2Fac1   = containerPtrs[iContainer]->Q2Fac();
      double Q2Fac2   = container2Ptrs[i2Container]->Q2Fac();
      double pdfA2Raw = beamAPtr->xf( idA2, xA2,Q2Fac2);
      double pdfB2Raw = beamBPtr->xf( idB2, xB2,Q2Fac2);

      // Remove partons in first interaction from beams. 
      beamAPtr->append( 3, idA1, xA1);
      beamAPtr->xfISR( 0, idA1, xA1, Q2Fac1);
      beamAPtr->pickValSeaComp(); 
      beamBPtr->append( 4, idB1, xB1);
      beamBPtr->xfISR( 0, idB1, xB1, Q2Fac1);
      beamBPtr->pickValSeaComp(); 

      // Reevaluate pdf's for second interaction and weight by reduction.
      double pdfA2Mod = beamAPtr->xfMI( idA2, xA2,Q2Fac2);
      double pdfB2Mod = beamBPtr->xfMI( idB2, xB2,Q2Fac2);
      double wtPdfMod = (pdfA2Mod * pdfB2Mod) / (pdfA2Raw * pdfB2Raw); 
      if (wtPdfMod < rndmPtr->flat()) continue;

      // Reduce by a factor of 2 for identical processes when others not,
      // and when in same phase space region.
      bool toLoop = false;
      if ( someHardSame && containerPtrs[iContainer]->isSame() 
        && container2Ptrs[i2Container]->isSame()) {
        if (cutsAgree) {
          if (rndmPtr->flat() > 0.5) toLoop = true;
        } else {
        double mHat1 = containerPtrs[iContainer]->mHat();
        double pTHat1 = containerPtrs[iContainer]->pTHat();
        double mHat2 = container2Ptrs[i2Container]->mHat();
        double pTHat2 = container2Ptrs[i2Container]->pTHat();
        if (mHat1 > mHatMin2 && mHat1 < mHatMax2 
           && pTHat1 > pTHatMin2 && pTHat1 < pTHatMax2
           && mHat2 > mHatMin1 && mHat2 < mHatMax1 
	   && pTHat2 > pTHatMin1 && pTHat2 < pTHatMax1
           && rndmPtr->flat() > 0.5) toLoop = true;
        }
      }
      if (toLoop) continue;    

      // If come this far then acceptable event.
      break;
    }

    // Construct kinematics of acceptable processes.
    Event process2;
    process2.init( "(second hard)", particleDataPtr, startColTag);
    process2.initColTag();
    if ( !containerPtrs[iContainer]->constructProcess( process) ) 
      physical = false;
    if (physical && !container2Ptrs[i2Container]->constructProcess( process2, 
      false) ) physical = false;

    // Do all resonance decays.
    if ( physical && doResDecays 
      &&  !containerPtrs[iContainer]->decayResonances( process) ) 
      physical = false;
    if ( physical && doResDecays 
      &&  !container2Ptrs[i2Container]->decayResonances( process2) ) 
      physical = false;

    // Append second hard interaction to normal process object.
    if (physical) combineProcessRecords( process, process2);

    // Add any junctions to the process event record list.
    if (physical) findJunctions( process);

    // Outer loop should normally work first time around.
    if (physical) break;
  }

  // Done.
  return physical;
}

//--------------------------------------------------------------------------

// Append second hard interaction to normal process object.
// Complication: all resonance decay chains must be put at the end.

void ProcessLevel::combineProcessRecords( Event& process, Event& process2) {

  // Find first event record size, excluding resonances.
  int nSize = process.size();
  int nHard = 5;
  while (nHard < nSize && process[nHard].mother1() == 3) ++nHard;

  // Save resonance products temporarily elsewhere. 
  vector<Particle> resProd;
  if (nSize > nHard) {
    for (int i = nHard; i < nSize; ++i) resProd.push_back( process[i] );
    process.popBack(nSize - nHard);
  }

  // Find second event record size, excluding resonances.
  int nSize2 = process2.size();
  int nHard2 = 5;
  while (nHard2 < nSize2 && process2[nHard2].mother1() == 3) ++nHard2;

  // Find amount of necessary position and colour offset for second process.
  int addPos  = nHard  - 3;
  int addCol  = process.lastColTag() - startColTag;

  // Loop over all particles (except beams) from second process.
  for (int i = 3; i < nSize2; ++i) {

    // Offset mother and daughter pointers and colour tags of particle.
    process2[i].offsetHistory( 2, addPos, 2, addPos);
    process2[i].offsetCol( addCol);

    // Append hard-process particles from process2 to process.
    if (i < nHard2) process.append( process2[i] );
  }

  // Reinsert resonance decay chains of first hard process.
  int addPos2 = nHard2 - 3;
  if (nHard < nSize) {

    // Offset daughter pointers of unmoved mothers.
    for (int i = 5; i < nHard; ++i) 
      process[i].offsetHistory( 0, 0, nHard - 1, addPos2); 
    
    // Modify history of resonance products when restoring. 
    for (int i = 0; i < int(resProd.size()); ++i) {
      resProd[i].offsetHistory( nHard - 1, addPos2, nHard - 1, addPos2);
      process.append( resProd[i] );
    } 
  }   

  // Insert resonance decay chains of second hard process.
  if (nHard2 < nSize2) {
    int nHard3  = nHard + nHard2 - 3;
    int addPos3 = nSize - nHard;

    // Offset daughter pointers of second-process mothers.
    for (int i = nHard + 2; i < nHard3; ++i) 
      process[i].offsetHistory( 0, 0, nHard3 - 1, addPos3); 
    
    // Modify history of second-process resonance products and insert. 
    for (int i = nHard2; i < nSize2; ++i) {
      process2[i].offsetHistory( nHard3 - 1, addPos3, nHard3 - 1, addPos3);
      process.append( process2[i] );
    } 
  }

  // Store PDF scale for second interaction.
  process.scaleSecond( process2.scale() );   

}

//--------------------------------------------------------------------------

// Add any junctions to the process event record list.
// First try, so still incomplete. ?? 
// Also check that do not doublebook if called repeatedly.

void ProcessLevel::findJunctions( Event& junEvent) {

  // Loop though event; isolate all uncoloured particles.
  for (int i = 0; i < junEvent.size(); ++i) 
  if ( junEvent[i].col() == 0 && junEvent[i].acol() == 0) {

    // Find all daughters and store daughter colours and anticolours.
    vector<int> daughters = junEvent.daughterList(i);
    // Debug??
    if (junEvent.size() == 3 && daughters.size() > 0) {
      cout << " warning: daughtersize = " << daughters.size() << endl;
      junEvent.list();
    } 
    // End debug???
    vector<int> cols, acols;
    for (int j = 0; j < int(daughters.size()); ++j) {
      int colDau  = junEvent[ daughters[j] ].col();
      int acolDau = junEvent[ daughters[j] ].acol();
      if (colDau > 0)  cols.push_back( colDau);      
      if (acolDau > 0) acols.push_back( acolDau);      
    }

    // Remove all matching colour-anticolour pairs.
    bool foundPair = true;
    while (foundPair && cols.size() > 0 && acols.size() > 0) {
      foundPair = false;
      for (int j = 0; j < int(cols.size()); ++j) {
        for (int k = 0; k < int(acols.size()); ++k) {
	  if (acols[k] == cols[j]) { 
            cols[j]  = cols.back();  
            cols.pop_back();     
            acols[k] = acols.back(); 
            acols.pop_back();     
            foundPair = true; 
            break;
	  }
	} if (foundPair) break;
      }
    } 

    // Store an (anti)junction when three (anti)coloured daughters.
    // But first check that junction not already exists.
    if (cols.size() == 3 && acols.size() == 0) {
      bool foundMatch = false;
      for (int iJun = 0; iJun < junEvent.sizeJunction(); ++iJun) 
      if (junEvent.kindJunction(iJun) == 1) {
        int nMatch = 0;
        for (int j = 0; j < 3; ++j) { 
          int colNow = junEvent.colJunction(iJun, j); 
          if (colNow == cols[0] || colNow == cols[1] 
            || colNow == cols[2]) ++nMatch;
        } 
        if (nMatch == 3) foundMatch = true;
      }
      if (!foundMatch)
        junEvent.appendJunction( 1, cols[0], cols[1], cols[2]);
    }
    if (acols.size() == 3 && cols.size() == 0) {
      bool foundMatch = false;
      for (int iJun = 0; iJun < junEvent.sizeJunction(); ++iJun) 
      if (junEvent.kindJunction(iJun) == 2) {
        int nMatch = 0;
        for (int j = 0; j < 3; ++j) { 
          int colNow = junEvent.colJunction(iJun, j); 
          if (colNow == acols[0] || colNow == acols[1] 
            || colNow == acols[2]) ++nMatch;
        } 
        if (nMatch == 3) foundMatch = true;
      }
      if (!foundMatch)
      junEvent.appendJunction( 2, acols[0], acols[1], acols[2]);
    }
  }

  // Done.
}

//--------------------------------------------------------------------------

// Check that colours match up.

bool ProcessLevel::checkColours( Event& process) {

  // Variables and arrays for common usage.
  bool physical = true;
  bool match;
  int colType, col, acol, iPos, iNow, iNowA;
  vector<int> colTags, colPos, acolPos;

  // Check that each particle has the kind of colours expected of it.
  for (int i = 0; i < process.size(); ++i) {
    colType = process[i].colType();
    col     = process[i].col();
    acol    = process[i].acol();
    if      (colType ==  0 && (col != 0 || acol != 0)) physical = false;
    else if (colType ==  1 && (col <= 0 || acol != 0)) physical = false;
    else if (colType == -1 && (col != 0 || acol <= 0)) physical = false;
    else if (colType ==  2 && (col <= 0 || acol <= 0)) physical = false;
    else if (colType < -1 || colType > 2)              physical = false; 

    // Add to the list of colour tags.
    if (col > 0) {
      match = false;
      for (int ic = 0; ic < int(colTags.size()) ; ++ic)
        if (col == colTags[ic]) match = true;
      if (!match) colTags.push_back(col);
    } else if (acol > 0) {
      match = false;
      for (int ic = 0; ic < int(colTags.size()) ; ++ic)
        if (acol == colTags[ic]) match = true;
      if (!match) colTags.push_back(acol);
    }
  }

  // Warn and give up if particles did not have the expected colours.
  if (!physical) {
    infoPtr->errorMsg("Error in ProcessLevel::checkColours: "
      "incorrect colour assignment"); 
    return false;
  }

  // Remove (anti)colours coming from an (anti)junction.
  // Temporary solution; only relevant for some cases??
  for (int iJun = 0; iJun < process.sizeJunction(); ++iJun)  
  if ( process.kindJunction(iJun) == 1 
    || process.kindJunction(iJun) == 2) {
    for (int j = 0; j < 3; ++j) { 
      int colJun = process.colJunction(iJun, j);
      for (int ic = 0; ic < int(colTags.size()) ; ++ic)
      if (colJun == colTags[ic]) {
        colTags[ic] = colTags[colTags.size() - 1]; 
        colTags.pop_back();
        break;
      } 
    }
  }

  // Loop through all colour tags and find their positions (by sign). 
  for (int ic = 0; ic < int(colTags.size()); ++ic) {
    col = colTags[ic];
    colPos.resize(0);
    acolPos.resize(0);
    for (int i = 0; i < process.size(); ++i) {
      if (process[i].col() == col) colPos.push_back(i); 
      if (process[i].acol() == col) acolPos.push_back(i); 
    }

    // Trace colours back through decays; remove daughters.
    while (colPos.size() > 1) {
      iPos = colPos.size() - 1; 
      iNow = colPos[iPos]; 
      if ( process[iNow].mother1() == colPos[iPos - 1]
        && process[iNow].mother2() == 0) colPos.pop_back();
      else break;
    }           
    while (acolPos.size() > 1) {
      iPos = acolPos.size() - 1; 
      iNow = acolPos[iPos]; 
      if ( process[iNow].mother1() == acolPos[iPos - 1]
        && process[iNow].mother2() == 0) acolPos.pop_back();
      else break;
    } 

    // Now colour should exist in only 2 copies.
    if (colPos.size() + acolPos.size() != 2) physical = false;

    // If both colours or both anticolours then one mother of the other.
    else if (colPos.size() == 2) {
      iNow = colPos[1];
      if ( process[iNow].mother1() != colPos[0] 
        && process[iNow].mother2() != colPos[0] ) physical = false;
    }
    else if (acolPos.size() == 2) {
      iNowA = acolPos[1];
      if ( process[iNowA].mother1() != acolPos[0] 
        && process[iNowA].mother2() != acolPos[0] ) physical = false;
    }
    
    // If one of each then should have same mother(s), or point to beams.
    else {
      iNow  = colPos[0];
      iNowA = acolPos[0];
      if ( process[iNow].status() == -21 &&  process[iNowA].status() == -21 );
      else if ( (process[iNow].mother1() != process[iNowA].mother1()) 
             || (process[iNow].mother2() != process[iNowA].mother2()) ) 
             physical = false;
    }

  }

  // Error message if problem found. Done.
  if (!physical) infoPtr->errorMsg("Error in ProcessLevel::checkColours: "
    "unphysical colour flow"); 
  return physical;

}

//--------------------------------------------------------------------------

// Print statistics when two hard processes allowed.

void ProcessLevel::statistics2(bool reset, ostream& os) {

  // Average impact-parameter factor and error.
  double invN          = 1. / max(1, nImpact);
  double impactFac     = max( 1., sumImpactFac * invN);
  double impactErr2    = ( sum2ImpactFac * invN / pow2(impactFac) - 1.) * invN;

  // Derive scaling factor to be applied to first set of processes.
  double sigma2SelSum  = 0.;
  int    n2SelSum      = 0;
  for (int i2 = 0; i2 < int(container2Ptrs.size()); ++i2) {
    sigma2SelSum      += container2Ptrs[i2]->sigmaSelMC();
    n2SelSum          += container2Ptrs[i2]->nSelected();
  }
  double factor1       = impactFac * sigma2SelSum / sigmaND;  
  double rel1Err       = sqrt(1. / max(1, n2SelSum) + impactErr2);    
  if (allHardSame) factor1 *= 0.5;

  // Derive scaling factor to be applied to second set of processes.
  double sigma1SelSum  = 0.;
  int    n1SelSum      = 0;
  for (int i = 0; i < int(containerPtrs.size()); ++i) {
    sigma1SelSum      += containerPtrs[i]->sigmaSelMC();
    n1SelSum          += containerPtrs[i]->nSelected();
  }
  double factor2       = impactFac * sigma1SelSum / sigmaND;       
  if (allHardSame) factor2 *= 0.5;
  double rel2Err       = sqrt(1. / max(1, n1SelSum) + impactErr2);    
    
  // Header.
  os << "\n *-------  PYTHIA Event and Cross Section Statistics  ------"
     << "--------------------------------------------------*\n"
     << " |                                                            "
     << "                                                |\n" 
     << " | Subprocess                               Code |            "
     << "Number of events       |      sigma +- delta    |\n" 
     << " |                                               |       Tried"
     << "   Selected   Accepted |     (estimated) (mb)   |\n"
     << " |                                               |            "
     << "                       |                        |\n"
     << " |------------------------------------------------------------"
     << "------------------------------------------------|\n"
     << " |                                               |            "
     << "                       |                        |\n"
     << " | First hard process:                           |            "
     << "                       |                        |\n"
     << " |                                               |            "
     << "                       |                        |\n";

  // Reset sum counters.
  long   nTrySum   = 0; 
  long   nSelSum   = 0; 
  long   nAccSum   = 0;
  double sigmaSum  = 0.;
  double delta2Sum = 0.;

  // Loop over existing first processes.
  for (int i = 0; i < int(containerPtrs.size()); ++i) 
  if (containerPtrs[i]->sigmaMax() != 0.) {

    // Read info for process. Sum counters.
    long   nTry    = containerPtrs[i]->nTried();
    long   nSel    = containerPtrs[i]->nSelected();
    long   nAcc    = containerPtrs[i]->nAccepted();
    double sigma   = containerPtrs[i]->sigmaMC() * factor1;
    double delta2  = pow2( containerPtrs[i]->deltaMC() * factor1 );
    nTrySum       += nTry;
    nSelSum       += nSel;
    nAccSum       += nAcc; 
    sigmaSum      += sigma;
    delta2Sum     += delta2; 
    delta2        += pow2( sigma * rel1Err );   

    // Print individual process info.
    os << " | " << left << setw(40) << containerPtrs[i]->name() 
       << right << setw(5) << containerPtrs[i]->code() << " | " 
       << setw(11) << nTry << " " << setw(10) << nSel << " " 
       << setw(10) << nAcc << " | " << scientific << setprecision(3) 
       << setw(11) << sigma << setw(11) << sqrtpos(delta2) << " |\n";
  }

  // Print summed info for first processes.
  delta2Sum       += pow2( sigmaSum * rel1Err ); 
  os << " |                                               |            "
     << "                       |                        |\n"
     << " | " << left << setw(45) << "sum" << right << " | " << setw(11) 
     << nTrySum << " " << setw(10) << nSelSum << " " << setw(10) 
     << nAccSum << " | " << scientific << setprecision(3) << setw(11) 
     << sigmaSum << setw(11) << sqrtpos(delta2Sum) << " |\n";

 
  // Separation lines to second hard processes.
  os << " |                                               |            "
     << "                       |                        |\n"
     << " |------------------------------------------------------------"
     << "------------------------------------------------|\n"
     << " |                                               |            "
     << "                       |                        |\n"
     << " | Second hard process:                          |            "
     << "                       |                        |\n"
     << " |                                               |            "
     << "                       |                        |\n";

  // Reset sum counters.
  nTrySum   = 0; 
  nSelSum   = 0; 
  nAccSum   = 0;
  sigmaSum  = 0.;
  delta2Sum = 0.;

  // Loop over existing second processes.
  for (int i2 = 0; i2 < int(container2Ptrs.size()); ++i2)
  if (container2Ptrs[i2]->sigmaMax() != 0.) {

    // Read info for process. Sum counters.
    long   nTry    = container2Ptrs[i2]->nTried();
    long   nSel    = container2Ptrs[i2]->nSelected();
    long   nAcc    = container2Ptrs[i2]->nAccepted();
    double sigma   = container2Ptrs[i2]->sigmaMC() * factor2;
    double delta2  = pow2( container2Ptrs[i2]->deltaMC() * factor2 );
    nTrySum       += nTry;
    nSelSum       += nSel;
    nAccSum       += nAcc; 
    sigmaSum      += sigma;
    delta2Sum     += delta2;    
    delta2        += pow2( sigma * rel2Err );   

    // Print individual process info.
    os << " | " << left << setw(40) << container2Ptrs[i2]->name() 
       << right << setw(5) << container2Ptrs[i2]->code() << " | " 
       << setw(11) << nTry << " " << setw(10) << nSel << " " 
       << setw(10) << nAcc << " | " << scientific << setprecision(3) 
       << setw(11) << sigma << setw(11) << sqrtpos(delta2) << " |\n";
  }

  // Print summed info for second processes.
  delta2Sum       += pow2( sigmaSum * rel2Err ); 
  os << " |                                               |            "
     << "                       |                        |\n"
     << " | " << left << setw(45) << "sum" << right << " | " << setw(11) 
     << nTrySum << " " << setw(10) << nSelSum << " " << setw(10) 
     << nAccSum << " | " << scientific << setprecision(3) << setw(11) 
     << sigmaSum << setw(11) << sqrtpos(delta2Sum) << " |\n";

  // Print information on how the two processes were combined.
  os << " |                                               |            "
     << "                       |                        |\n"
     << " |------------------------------------------------------------"
     << "------------------------------------------------|\n"
     << " |                                                            "
     << "                                                |\n"
     << " | Uncombined cross sections for the two event sets were " 
     << setw(10) << sigma1SelSum << " and " << sigma2SelSum << " mb, "
     << "respectively, combined  |\n"
     << " | using a sigma(nonDiffractive) of " << setw(10) << sigmaND 
     << " mb and an impact-parameter enhancement factor of "
     << setw(10) << impactFac << ".   |\n";

  // Listing finished.
  os << " |                                                            "
     << "                                                |\n"
     << " *-------  End PYTHIA Event and Cross Section Statistics -----"
     << "------------------------------------------------*" << endl;

  // Optionally reset statistics contants.
  if (reset) {
    for (int i = 0; i < int(containerPtrs.size()); ++i) 
      containerPtrs[i]->reset();
    for (int i2 = 0; i2 < int(container2Ptrs.size()); ++i2)
      container2Ptrs[i2]->reset();
  }
     
}

//==========================================================================

} // end namespace Pythia8
