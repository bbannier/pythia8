// SigmaCompositeness.cc is a part of the PYTHIA event generator.
// Copyright (C) 2010 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// Function definitions (not found in the header) for the 
// compositeness simulation classes. 

#include "SigmaCompositeness.h"

namespace Pythia8 {

//==========================================================================

// Sigma1qg2qStar class.
// Cross section for q g -> q^* (excited quark state). 
// Note: for simplicity decay is assumed isotropic.

//--------------------------------------------------------------------------

// Initialize process. 
  
void Sigma1qg2qStar::initProc() {

  // Set up process properties from the chosen quark flavour.
  idRes         = 4000000 + idq;
  codeSave      = 4000 + idq;
  if      (idq == 1) nameSave = "d g -> d^*";
  else if (idq == 2) nameSave = "u g -> u^*";
  else if (idq == 3) nameSave = "s g -> s^*";
  else if (idq == 4) nameSave = "c g -> c^*";
  else               nameSave = "b g -> b^*";

  // Store q* mass and width for propagator. 
  mRes          = particleDataPtr->m0(idRes);
  GammaRes      = particleDataPtr->mWidth(idRes);
  m2Res         = mRes*mRes;
  GamMRat       = GammaRes / mRes;

  // Locally stored properties and couplings.
  Lambda        = settingsPtr->parm("ExcitedFermion:Lambda");
  coupFcol      = settingsPtr->parm("ExcitedFermion:coupFcol");

  // Set pointer to particle properties and decay table.
  qStarPtr      = particleDataPtr->particleDataEntryPtr(idRes);

} 

//--------------------------------------------------------------------------

// Evaluate sigmaHat(sHat), part independent of incoming flavour. 

void Sigma1qg2qStar::sigmaKin() { 

  // Incoming width for correct quark.
  widthIn  = pow3(mH) * alpS * pow2(coupFcol) / (3. * pow2(Lambda)); 

  // Set up Breit-Wigner.
  sigBW    = M_PI/ ( pow2(sH - m2Res) + pow2(sH * GamMRat) );  

}

//--------------------------------------------------------------------------

// Evaluate sigmaHat(sHat) for specific incoming flavours.

double Sigma1qg2qStar::sigmaHat() { 

  // Identify whether correct incoming flavours.
  int idqNow = (id2 == 21) ? id1 : id2;
  if (abs(idqNow) != idq) return 0.;

  // Outgoing width and total sigma. Done.
  return widthIn * sigBW * qStarPtr->resWidthOpen(idqNow, mH);    

}

//--------------------------------------------------------------------------

// Select identity, colour and anticolour.

void Sigma1qg2qStar::setIdColAcol() {

  // Flavours.
  int idqNow = (id2 == 21) ? id1 : id2;
  int idqStar = (idqNow > 0) ? idRes : -idRes;
  setId( id1, id2, idqStar);

  // Colour flow topology.
  if (id1 == idqNow) setColAcol( 1, 0, 2, 1, 2, 0);
  else               setColAcol( 2, 1, 1, 0, 2, 0);
  if (idqNow < 0) swapColAcol();

}

//--------------------------------------------------------------------------

// Evaluate weight for q* decay angle. 
  
double Sigma1qg2qStar::weightDecay( Event& process, int iResBeg, 
  int iResEnd) {

  // q* should sit in entry 5. Sequential Z/W decay assumed isotropic.
  if (iResBeg != 5 || iResEnd != 5) return 1.; 
   
  // Sign of asymmetry.
  int sideIn    = (process[3].idAbs() < 20) ? 1 : 2;
  int sideOut   = (process[6].idAbs() < 20) ? 1 : 2;
  double eps    = (sideIn == sideOut) ? 1. : -1.;

  // Phase space factors.
  double mr1    = pow2(process[6].m()) / sH;
  double mr2    = pow2(process[7].m()) / sH;
  double betaf  = sqrtpos( pow2(1. - mr1 - mr2) - 4. * mr1 * mr2); 

  // Reconstruct decay angle. Default isotropic decay.
  double cosThe = (process[3].p() - process[4].p()) 
    * (process[7].p() - process[6].p()) / (sH * betaf);
  double wt     = 1.; 
  double wtMax  = 1.;

  // Decay q* -> q (g/gamma) or q (Z^0/W^+-).
  int idBoson   = (sideOut == 1) ? process[7].idAbs() : process[6].idAbs();
  if (idBoson == 21 || idBoson == 22) {
    wt          = 1. + eps * cosThe;
    wtMax       = 2.;
  } else if (idBoson == 23 || idBoson == 24) {
    double mrB  = (sideOut == 1) ? mr2 : mr1;
    double ratB = (1. - 0.5 * mrB) / (1 + 0.5 * mrB);
    wt          = 1. + eps * cosThe * ratB;
    wtMax       = 1. + ratB;
  } 

  // Done.
  return (wt / wtMax);

}

//==========================================================================

// Sigma1lgm2lStar class.
// Cross section for l gamma -> l^* (excited lepton state). 
// Note: for simplicity decay is assumed isotropic.

//--------------------------------------------------------------------------

// Initialize process. 
  
void Sigma1lgm2lStar::initProc() {

  // Set up process properties from the chosen lepton flavour.
  idRes         = 4000000 + idl;
  codeSave      = 4000 + idl;
  if      (idl == 11) nameSave = "e gamma -> e^*";
  else if (idl == 13) nameSave = "mu gamma -> mu^*";
  else                nameSave = "tau gamma -> tau^*";

  // Store l* mass and width for propagator. 
  mRes          = particleDataPtr->m0(idRes);
  GammaRes      = particleDataPtr->mWidth(idRes);
  m2Res         = mRes*mRes;
  GamMRat       = GammaRes / mRes;

  // Locally stored properties and couplings.
  Lambda        = settingsPtr->parm("ExcitedFermion:Lambda");
  double coupF  = settingsPtr->parm("ExcitedFermion:coupF");
  double coupFp = settingsPtr->parm("ExcitedFermion:coupFprime");
  coupChg       = -0.5 * coupF - 0.5 * coupFp;

  // Set pointer to particle properties and decay table.
  qStarPtr      = particleDataPtr->particleDataEntryPtr(idRes);

} 

//--------------------------------------------------------------------------

// Evaluate sigmaHat(sHat), part independent of incoming flavour. 

void Sigma1lgm2lStar::sigmaKin() { 

  // Incoming width for correct lepton.
  widthIn  = pow3(mH) * alpEM * pow2(coupChg) / pow2(Lambda); 

  // Set up Breit-Wigner.
  sigBW    = M_PI/ ( pow2(sH - m2Res) + pow2(sH * GamMRat) );  

}

//--------------------------------------------------------------------------

// Evaluate sigmaHat(sHat) for specific incoming flavours.

double Sigma1lgm2lStar::sigmaHat() { 

  // Identify whether correct incoming flavours.
  int idlNow = (id2 == 22) ? id1 : id2;
  if (abs(idlNow) != idl) return 0.;

  // Outgoing width and total sigma. Done.
  return widthIn * sigBW * qStarPtr->resWidthOpen(idlNow, mH);    

}

//--------------------------------------------------------------------------

// Select identity, colour and anticolour.

void Sigma1lgm2lStar::setIdColAcol() {

  // Flavours.
  int idlNow = (id2 == 22) ? id1 : id2;
  int idlStar = (idlNow > 0) ? idRes : -idRes;
  setId( id1, id2, idlStar);

  // No colour flow.
  setColAcol( 0, 0, 0, 0, 0, 0);

}

//--------------------------------------------------------------------------

// Evaluate weight for l* decay angle. 
  
double Sigma1lgm2lStar::weightDecay( Event& process, int iResBeg, 
  int iResEnd) {

  // l* should sit in entry 5. Sequential Z/W decay assumed isotropic.
  if (iResBeg != 5 || iResEnd != 5) return 1.; 
   
  // Sign of asymmetry.
  int sideIn    = (process[3].idAbs() < 20) ? 1 : 2;
  int sideOut   = (process[6].idAbs() < 20) ? 1 : 2;
  double eps    = (sideIn == sideOut) ? 1. : -1.;

  // Phase space factors.
  double mr1    = pow2(process[6].m()) / sH;
  double mr2    = pow2(process[7].m()) / sH;
  double betaf  = sqrtpos( pow2(1. - mr1 - mr2) - 4. * mr1 * mr2); 

  // Reconstruct decay angle. Default isotropic decay.
  double cosThe = (process[3].p() - process[4].p()) 
    * (process[7].p() - process[6].p()) / (sH * betaf);
  double wt     = 1.; 
  double wtMax  = 1.;

  // Decay l* -> l gamma or l (Z^0/W^+-).
  int idBoson   = (sideOut == 1) ? process[7].idAbs() : process[6].idAbs();
  if (idBoson == 22) {
    wt          = 1. + eps * cosThe;
    wtMax       = 2.;
  } else if (idBoson == 23 || idBoson == 24) {
    double mrB  = (sideOut == 1) ? mr2 : mr1;
    double ratB = (1. - 0.5 * mrB) / (1 + 0.5 * mrB);
    wt          = 1. + eps * cosThe * ratB;
    wtMax       = 1. + ratB;
  } 

  // Done.
  return (wt / wtMax);

}

//==========================================================================

// Sigma2qq2qStarq class.
// Cross section for q q' -> q^* q' (excited quark state). 
// Note: for simplicity decay is assumed isotropic.

//--------------------------------------------------------------------------

// Initialize process. 
  
void Sigma2qq2qStarq::initProc() {

  // Set up process properties from the chosen quark flavour.
  idRes         = 4000000 + idq;
  codeSave      = 4020 + idq;
  if      (idq == 1) nameSave = "q q -> d^* q";
  else if (idq == 2) nameSave = "q q -> u^* q";
  else if (idq == 3) nameSave = "q q -> s^* q";
  else if (idq == 4) nameSave = "q q -> c^* q";
  else               nameSave = "q q -> b^* q";

  // Locally stored properties and couplings.
  Lambda        = settingsPtr->parm("ExcitedFermion:Lambda");
  preFac        = M_PI / pow4(Lambda);

  // Secondary open width fractions.
  openFracPos = particleDataPtr->resOpenFrac( idRes);
  openFracNeg = particleDataPtr->resOpenFrac(-idRes);

} 

//--------------------------------------------------------------------------

// Evaluate sigmaHat(sHat), part independent of incoming flavour. 

void Sigma2qq2qStarq::sigmaKin() { 

  // Two possible expressions, for like or unlike sign.
  sigmaA = preFac * (1. - s3 / sH);
  sigmaB = preFac * (-uH) * (sH + tH) / sH2;  

}

//--------------------------------------------------------------------------

// Evaluate sigmaHat(sHat) for specific incoming flavours.

double Sigma2qq2qStarq::sigmaHat() { 

  // Identify different allowed incoming flavour combinations.
  int id1Abs   = abs(id1);
  int id2Abs   = abs(id2);
  double open1 = (id1 > 0) ? openFracPos : openFracNeg;
  double open2 = (id2 > 0) ? openFracPos : openFracNeg;
  double sigma = 0.;
  if (id1 * id2 > 0) {
    if (id1Abs == idq) sigma += (4./3.) * sigmaA * open1;
    if (id2Abs == idq) sigma += (4./3.) * sigmaA * open2;
  } else if (id1Abs == idq && id2 == -id1) 
    sigma = (8./3.) * sigmaB * (open1 + open2);
  else if (id2 == -id1) sigma = sigmaB * (open1 + open2);
  else if (id1Abs == idq) sigma = sigmaB * open1;
  else if (id2Abs == idq) sigma = sigmaB * open2;

  // Done.
  return sigma;
 
}

//--------------------------------------------------------------------------

// Select identity, colour and anticolour.

void Sigma2qq2qStarq::setIdColAcol() {

  // Flavours: either side may have been excited.
  double open1 = 0.;
  double open2 = 0.; 
  if (abs(id1) == idq) open1 = (id1 > 0) ? openFracPos : openFracNeg;
  if (abs(id2) == idq) open2 = (id2 > 0) ? openFracPos : openFracNeg;
  if (open1 == 0. && open2 == 0.) {
    open1  = (id1 > 0) ? openFracPos : openFracNeg;
    open2  = (id2 > 0) ? openFracPos : openFracNeg;
  }
  bool excite1 = (open1 > 0.);
  if (open1 > 0. && open2 > 0.) excite1 
    = (rndmPtr->flat() * (open1 + open2) < open1);

  // Always excited quark in slot 3 so colour flow flipped or not.
  if (excite1) {  
    id3    = (id1 > 0) ? idq : -idq;
    id4    = id2;
    if (id1 * id2 > 0) setColAcol( 1, 0, 2, 0, 1, 0, 2, 0);
    else               setColAcol( 1, 0, 0, 2, 1, 0, 0, 2);
    if (id1 < 0) swapColAcol();
  } else {     
    id3    = (id2 > 0) ? idq : -idq;
    id4    = id1;
    swapTU = true;
    if (id1 * id2 > 0) setColAcol( 1, 0, 2, 0, 2, 0, 1, 0);
    else               setColAcol( 1, 0, 0, 2, 0, 2, 1, 0);
    if (id1 < 0) swapColAcol();
  }
  setId( id1, id2, id3, id4);

}

//==========================================================================

// Sigma2qqbar2lStarlbar class.
// Cross section for q qbar -> l^* lbar (excited lepton state). 
// Note: for simplicity decay is assumed isotropic.

//--------------------------------------------------------------------------

// Initialize process. 
  
void Sigma2qqbar2lStarlbar::initProc() {

  // Set up process properties from the chosen lepton flavour.
  idRes         = 4000000 + idl;
  codeSave      = 4020 + idl;
  if      (idl == 11) nameSave = "q qbar -> e^*+- e^-+";
  else if (idl == 12) nameSave = "q qbar -> nu_e^* nu_ebar"; 
  else if (idl == 13) nameSave = "q qbar -> mu^*+- mu^-+"; 
  else if (idl == 14) nameSave = "q qbar -> nu_mu^* nu_mubar"; 
  else if (idl == 15) nameSave = "q qbar -> tau^*+- tau^-+"; 
  else                nameSave = "q qbar -> nu_tau^* nu_taubar";

  // Secondary open width fractions.
  openFracPos = particleDataPtr->resOpenFrac( idRes);
  openFracNeg = particleDataPtr->resOpenFrac(-idRes);

  // Locally stored properties and couplings.
  Lambda        = settingsPtr->parm("ExcitedFermion:Lambda");
  preFac        = (M_PI / pow4(Lambda)) * (openFracPos + openFracNeg) / 3.;

} 

//--------------------------------------------------------------------------

// Evaluate sigmaHat(sHat), part independent of incoming flavour. 

void Sigma2qqbar2lStarlbar::sigmaKin() { 

  // Only one possible expressions
  sigma = preFac * (-uH) * (sH + tH) / sH2;  

}

//--------------------------------------------------------------------------

// Select identity, colour and anticolour.

void Sigma2qqbar2lStarlbar::setIdColAcol() {

  // Flavours: either lepton or antilepton may be excited.
  if (rndmPtr->flat() * (openFracPos + openFracNeg) < openFracPos) {
    setId( id1, id2, idRes, -idl);
    if (id1 < 0) swapTU = true; 
  } else {
    setId( id1, id2, -idRes, idl);
    if (id1 > 0) swapTU = true;
  }  

  // Colour flow trivial.
  if (id1 > 0) setColAcol( 1, 0, 0, 1, 0, 0, 0, 0);
  else         setColAcol( 0, 1, 1, 0, 0, 0, 0, 0);

}

//==========================================================================

// Sigma2QCqq2qq class.
// Cross section for q q -> q q (quark contact interactions).

//--------------------------------------------------------------------------

// Initialize process. 
  
void Sigma2QCqq2qq::initProc() {

  m_Lambda2  = settingsPtr->parm("ContactInteractions:Lambda");
  m_etaLL    = settingsPtr->mode("ContactInteractions:etaLL");;
  m_etaRR    = settingsPtr->mode("ContactInteractions:etaRR");;
  m_etaLR    = settingsPtr->mode("ContactInteractions:etaLR");;
  m_Lambda2 *= m_Lambda2; 

}

//--------------------------------------------------------------------------

// Evaluate d(sigmaHat)/d(tHat), part independent of incoming flavour. 

void Sigma2QCqq2qq::sigmaKin() { 

  // Calculate kinematics dependence for different terms.
  sigT   = (4./9.) * (sH2 + uH2) / tH2;
  sigU   = (4./9.) * (sH2 + tH2) / uH2;
  sigTU  = - (8./27.) * sH2 / (tH * uH);
  sigST  = - (8./27.) * uH2 / (sH * tH);
  
  sigQCSTU = sH2 * (1 / tH + 1 / uH);
  sigQCUTS = uH2 * (1 / tH + 1 / sH);

}

//--------------------------------------------------------------------------

// Evaluate d(sigmaHat)/d(tHat), including incoming flavour dependence. 

double Sigma2QCqq2qq::sigmaHat() {  

  // Terms from QC contact interactions.
  double sigQCLL = 0;
  double sigQCRR = 0;
  double sigQCLR = 0;

  // Combine cross section terms; factor 1/2 when identical quarks.
  // q q -> q q
  if (id2 ==  id1) {         

    sigSum = 0.5 * (sigT + sigU + sigTU); // SM terms.
    
    // Contact terms.
    sigQCLL = (8./9.) * alpS * (m_etaLL/m_Lambda2) * sigQCSTU 
            + (8./3.) * pow2(m_etaLL/m_Lambda2) * sH2;
    sigQCRR = (8./9.) * alpS * (m_etaRR/m_Lambda2) * sigQCSTU 
            + (8./3.) * pow2(m_etaRR/m_Lambda2) * sH2;
    sigQCLR = 2. * (uH2 + tH2) * pow2(m_etaLR/m_Lambda2);

    sigQCLL /= 2;
    sigQCRR /= 2;
    sigQCLR /= 2;

  // q qbar -> q qbar, without pure s-channel term.
  } else if (id2 == -id1) {  

    sigSum = sigT + sigST; // SM terms.

    // Contact terms, minus the terms included in qqbar2qqbar.
    sigQCLL = (8./9.) * alpS * (m_etaLL/m_Lambda2) * sigQCUTS 
            + (5./3.) * pow2(m_etaLL/m_Lambda2) * uH2;
    sigQCRR = (8./9.) * alpS * (m_etaRR/m_Lambda2) * sigQCUTS 
            + (5./3.) * pow2(m_etaRR/m_Lambda2) * uH2;
    sigQCLR = 2. * sH2 * pow2(m_etaLR/m_Lambda2);

  // q q' -> q q' or q qbar' -> q qbar'
  } else {                   

    sigSum = sigT; // SM terms.

    // Contact terms.
    if (id1 * id2 > 0) {
      sigQCLL = pow2(m_etaLL/m_Lambda2) * sH2;
      sigQCRR = pow2(m_etaRR/m_Lambda2) * sH2;
      sigQCLR = 2 * pow2(m_etaLR/m_Lambda2) * uH2;
    } else {
      sigQCLL = pow2(m_etaLL/m_Lambda2) * uH2;
      sigQCRR = pow2(m_etaRR/m_Lambda2) * uH2;
      sigQCLR = 2 * pow2(m_etaLR/m_Lambda2) * sH2;
    }
  }

  // Answer.
  double sigma = (M_PI/sH2) * ( pow2(alpS) * sigSum 
               + sigQCLL + sigQCRR + sigQCLR );
  return sigma;  

}

//--------------------------------------------------------------------------

// Select identity, colour and anticolour.

void Sigma2QCqq2qq::setIdColAcol() {

  // Outgoing = incoming flavours.
  setId( id1, id2, id1, id2);

  // Colour flow topologies. Swap when antiquarks.
  if (id1 * id2 > 0)  setColAcol( 1, 0, 2, 0, 2, 0, 1, 0);
  else                setColAcol( 1, 0, 0, 1, 2, 0, 0, 2);
  if (id2 == id1 && (sigT + sigU) * rndmPtr->flat() > sigT)
                      setColAcol( 1, 0, 2, 0, 1, 0, 2, 0);
  if (id1 < 0) swapColAcol();

}

//==========================================================================

// Sigma2QCqqbar2qqbar class.
// Cross section for q qbar -> q' qbar' (quark contact interactions).

//--------------------------------------------------------------------------

// Initialize process. 
  
void Sigma2QCqqbar2qqbar::initProc() {

  m_nQuarkNew = settingsPtr->mode("ContactInteractions:nQuarkNew");
  m_Lambda2   = settingsPtr->parm("ContactInteractions:Lambda");
  m_etaLL     = settingsPtr->mode("ContactInteractions:etaLL");
  m_etaRR     = settingsPtr->mode("ContactInteractions:etaRR");
  m_etaLR     = settingsPtr->mode("ContactInteractions:etaLR");
  m_Lambda2  *= m_Lambda2; 

}

//--------------------------------------------------------------------------

// Evaluate d(sigmaHat)/d(tHat) - no incoming flavour dependence. 

void Sigma2QCqqbar2qqbar::sigmaKin() { 

  // Pick new flavour.
  idNew = 1 + int( m_nQuarkNew * rndmPtr->flat() ); 
  mNew  = particleDataPtr->m0(idNew);
  m2New = mNew*mNew;

  // Calculate kinematics dependence.
  double sigQC              = 0.;
  sigS                      = 0.;
  if (sH > 4. * m2New) {
    sigS = (4./9.) * (tH2 + uH2) / sH2; 
    sigQC = pow2(m_etaLL/m_Lambda2) * uH2
          + pow2(m_etaRR/m_Lambda2) * uH2
          + 2 * pow2(m_etaLR/m_Lambda2) * tH2;
  }

  // Answer is proportional to number of outgoing flavours.
  sigma = (M_PI / sH2) * m_nQuarkNew * ( pow2(alpS) * sigS + sigQC);  

}

//--------------------------------------------------------------------------

// Select identity, colour and anticolour.

void Sigma2QCqqbar2qqbar::setIdColAcol() {

  // Set outgoing flavours ones.
  id3 = (id1 > 0) ? idNew : -idNew;
  setId( id1, id2, id3, -id3);

  // Colour flow topologies. Swap when antiquarks.
  setColAcol( 1, 0, 0, 2, 1, 0, 0, 2);
  if (id1 < 0) swapColAcol();

}

//==========================================================================

} // end namespace Pythia8
