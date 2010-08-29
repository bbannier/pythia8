// SigmaExtraDim.cc is a part of the PYTHIA event generator.
// Copyright (C) 2010 Torbjorn Sjostrand.
// Copyright (C) 2010 Stefan Ask for the *LED* routines.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// Function definitions (not found in the header) for the 
// extra-dimensional simulation classes. 

#include "SigmaExtraDim.h"

namespace Pythia8 {

//==========================================================================

// Sigma1gg2GravitonStar class.
// Cross section for g g -> G* (excited graviton state). 

//--------------------------------------------------------------------------

// Initialize process. 
  
void Sigma1gg2GravitonStar::initProc() {

  // Store G* mass and width for propagator. 
  idGstar  = 5100039;
  mRes     = particleDataPtr->m0(idGstar);
  GammaRes = particleDataPtr->mWidth(idGstar);
  m2Res    = mRes*mRes;
  GamMRat  = GammaRes / mRes;

  // SMinBulk = off/on, use universal coupling (kappaMG) 
  // or individual (Gxx) between graviton and SM particles.
  m_smbulk   = settingsPtr->flag("ExtraDimensionsG*:SMinBulk");
  kappaMG    = settingsPtr->parm("ExtraDimensionsG*:kappaMG");
  for (int i = 0; i < 26; ++i) m_coupling[i] = 0.;
  double tmp_coup = settingsPtr->parm("ExtraDimensionsG*:Gqq");
  for (int i = 1; i <= 4; ++i)  m_coupling[i] = tmp_coup;
  m_coupling[5] = settingsPtr->parm("ExtraDimensionsG*:Gbb"); 
  m_coupling[6] = settingsPtr->parm("ExtraDimensionsG*:Gtt");
  tmp_coup = settingsPtr->parm("ExtraDimensionsG*:Gll");
  for (int i = 11; i <= 16; ++i) m_coupling[i] = tmp_coup;
  tmp_coup = settingsPtr->parm("ExtraDimensionsG*:GVV");
  for (int i = 21; i <= 24; ++i) m_coupling[i] = tmp_coup; 

  // Set pointer to particle properties and decay table.
  gStarPtr = particleDataPtr->particleDataEntryPtr(idGstar);

} 

//--------------------------------------------------------------------------

// Evaluate sigmaHat(sHat), part independent of incoming flavour. 

void Sigma1gg2GravitonStar::sigmaKin() { 

  // Incoming width for gluons.
  double widthIn  = mH / (160. * M_PI);

  // RS graviton coupling
  if (m_smbulk) widthIn *= 2. * pow2(m_coupling[21] * mH);  
  else          widthIn *= pow2(kappaMG);

  // Set up Breit-Wigner. Width out only includes open channels. 
  double sigBW    = 5. * M_PI/ ( pow2(sH - m2Res) + pow2(sH * GamMRat) );    
  double widthOut = gStarPtr->resWidthOpen(idGstar, mH);

  // Modify cross section in wings of peak. Done.
  sigma           = widthIn * sigBW * widthOut * pow2(sH / m2Res);    

}

//--------------------------------------------------------------------------

// Select identity, colour and anticolour.

void Sigma1gg2GravitonStar::setIdColAcol() {

  // Flavours trivial.
  setId( 21, 21, idGstar);

  // Colour flow topology.
  setColAcol( 1, 2, 2, 1, 0, 0);

}

//--------------------------------------------------------------------------

// Evaluate weight for G* decay angle.
  
double Sigma1gg2GravitonStar::weightDecay( Event& process, int iResBeg, 
  int iResEnd) {

  // Identity of mother of decaying reseonance(s).
  int idMother = process[process[iResBeg].mother1()].idAbs();

  // For top decay hand over to standard routine.
  if (idMother == 6) 
    return weightTopDecay( process, iResBeg, iResEnd);

  // G* should sit in entry 5.
  if (iResBeg != 5 || iResEnd != 5) return 1.;

  // Phase space factors. Reconstruct decay angle.
  double mr1    = pow2(process[6].m()) / sH;
  double mr2    = pow2(process[7].m()) / sH;
  double betaf  = sqrtpos( pow2(1. - mr1 - mr2) - 4. * mr1 * mr2); 
  double cosThe = (process[3].p() - process[4].p()) 
    * (process[7].p() - process[6].p()) / (sH * betaf);

  // Default is isotropic decay.
  double wt     = 1.;

  // Angular weight for g + g -> G* -> f + fbar.
  if (process[6].idAbs() < 19) wt = 1. - pow4(cosThe);

  // Angular weight for g + g -> G* -> g + g or gamma + gamma.
  else if (process[6].id() == 21 || process[6].id() == 22)
    wt = (1. + 6. * pow2(cosThe) + pow4(cosThe)) / 8.;
 
  // Done.
  return wt;

}

//==========================================================================

// Sigma1ffbar2GravitonStar class.
// Cross section for f fbar -> G* (excited graviton state). 

//--------------------------------------------------------------------------

// Initialize process. 
  
void Sigma1ffbar2GravitonStar::initProc() {

  // Store G* mass and width for propagator. 
  idGstar  = 5100039;
  mRes     = particleDataPtr->m0(idGstar);
  GammaRes = particleDataPtr->mWidth(idGstar);
  m2Res    = mRes*mRes;
  GamMRat  = GammaRes / mRes;

  // SMinBulk = off/on, use universal coupling (kappaMG) 
  // or individual (Gxx) between graviton and SM particles.
  m_smbulk   = settingsPtr->flag("ExtraDimensionsG*:SMinBulk");
  kappaMG    = settingsPtr->parm("ExtraDimensionsG*:kappaMG");
  for (int i = 0; i < 26; ++i) m_coupling[i] = 0.;
  double tmp_coup = settingsPtr->parm("ExtraDimensionsG*:Gqq");
  for (int i = 1; i <= 4; ++i)  m_coupling[i] = tmp_coup;
  m_coupling[5] = settingsPtr->parm("ExtraDimensionsG*:Gbb"); 
  m_coupling[6] = settingsPtr->parm("ExtraDimensionsG*:Gtt");
  tmp_coup = settingsPtr->parm("ExtraDimensionsG*:Gll");
  for (int i = 11; i <= 16; ++i) m_coupling[i] = tmp_coup;
  tmp_coup = settingsPtr->parm("ExtraDimensionsG*:GVV");
  for (int i = 21; i <= 24; ++i) m_coupling[i] = tmp_coup; 

  // Set pointer to particle properties and decay table.
  gStarPtr = particleDataPtr->particleDataEntryPtr(idGstar);

} 

//--------------------------------------------------------------------------

// Evaluate sigmaHat(sHat), part independent of incoming flavour. 

void Sigma1ffbar2GravitonStar::sigmaKin() { 

  // Incoming width for fermions, disregarding colour factor.
  double widthIn  = mH / (80. * M_PI);

  // Set up Breit-Wigner. Width out only includes open channels. 
  double sigBW    = 5. * M_PI/ ( pow2(sH - m2Res) + pow2(sH * GamMRat) );    
  double widthOut = gStarPtr->resWidthOpen(idGstar, mH);

  // Modify cross section in wings of peak. Done.
  sigma0          = widthIn * sigBW * widthOut * pow2(sH / m2Res);    

}

//--------------------------------------------------------------------------

// Evaluate sigmaHat(sHat), part dependent of incoming flavour.

double Sigma1ffbar2GravitonStar::sigmaHat() {
  
  double sigma = sigma0;

  // RS graviton coupling
  if (m_smbulk) sigma *= 2. * pow2(m_coupling[min( abs(id1), 25)] * mH);  
  else          sigma *= pow2(kappaMG);

  // If initial quarks, 1/N_C
  if (abs(id1) < 9) sigma /= 3.;     
  
  return sigma;
}

//--------------------------------------------------------------------------

// Select identity, colour and anticolour.

void Sigma1ffbar2GravitonStar::setIdColAcol() {

  // Flavours trivial.
  setId( id1, id2, idGstar);

  // Colour flow topologies. Swap when antiquarks.
  if (abs(id1) < 9) setColAcol( 1, 0, 0, 1, 0, 0);
  else              setColAcol( 0, 0, 0, 0, 0, 0);
  if (id1 < 0) swapColAcol();

}

//--------------------------------------------------------------------------

// Evaluate weight for G* decay angle.
  
double Sigma1ffbar2GravitonStar::weightDecay( Event& process, int iResBeg, 
  int iResEnd) {

  // Identity of mother of decaying reseonance(s).
  int idMother = process[process[iResBeg].mother1()].idAbs();

  // For top decay hand over to standard routine.
  if (idMother == 6) 
    return weightTopDecay( process, iResBeg, iResEnd);

  // G* should sit in entry 5.
  if (iResBeg != 5 || iResEnd != 5) return 1.;

  // Phase space factors. Reconstruct decay angle.
  double mr1    = pow2(process[6].m()) / sH;
  double mr2    = pow2(process[7].m()) / sH;
  double betaf  = sqrtpos( pow2(1. - mr1 - mr2) - 4. * mr1 * mr2); 
  double cosThe = (process[3].p() - process[4].p()) 
    * (process[7].p() - process[6].p()) / (sH * betaf);

  // Default is isotropic decay.
  double wt     = 1.;

  // Angular weight for f + fbar -> G* -> f + fbar.
  if (process[6].idAbs() < 19)
    wt = (1. - 3. * pow2(cosThe) + 4. * pow4(cosThe)) / 2.;

  // Angular weight for f + fbar -> G* -> g + g or gamma + gamma.
  else if (process[6].id() == 21 || process[6].id() == 22)
    wt = 1. - pow4(cosThe);
 
  // Done.
  return wt;

}

//==========================================================================

// Sigma1qqbar2KKgluonStar class.
// Cross section for q qbar -> KK-gluon^* (excited KK-gluon state).

//--------------------------------------------------------------------------

// Initialize process. 
  
void Sigma1qqbar2KKgluonStar::initProc() {

  // Store kk-gluon* mass and width for propagator. 
  idKKgluon = 5100021;
  mRes      = particleDataPtr->m0(idKKgluon);
  GammaRes  = particleDataPtr->mWidth(idKKgluon);
  m2Res     = mRes*mRes;
  GamMRat   = GammaRes / mRes;

  // KK-gluon couplings.
  for (int i = 0; i < 10; ++i) m_coupling[i] = 0.;
  double tmp_coup = settingsPtr->parm("ExtraDimensionsG*:KKgqq");
  for (int i = 1; i <= 4; ++i)  m_coupling[i] = tmp_coup;
  m_coupling[5] = settingsPtr->parm("ExtraDimensionsG*:KKgbb"); 
  m_coupling[6] = settingsPtr->parm("ExtraDimensionsG*:KKgtt");

  // Set pointer to particle properties and decay table.
  gStarPtr = particleDataPtr->particleDataEntryPtr(idKKgluon);

} 

//--------------------------------------------------------------------------

// Evaluate sigmaHat(sHat), part independent of incoming flavour. 

void Sigma1qqbar2KKgluonStar::sigmaKin() { 

  // Incoming width for fermions, disregarding colour factor.
  double widthIn  = alpS * mH * 4 / 27; 

  // Set up Breit-Wigner. Width out only includes open channels. 
  double sigBW    = 12. * M_PI / ( pow2(sH - m2Res) + pow2(sH * GamMRat) );    
  double widthOut = gStarPtr->resWidthOpen(idKKgluon, mH);

  // Do not modify cross section in wings of peak, to be understood!
  sigma0          = widthIn * sigBW * widthOut; // * pow2(sH / m2Res);

}

//--------------------------------------------------------------------------

// Evaluate sigmaHat(sHat), part dependent of incoming flavour.

double Sigma1qqbar2KKgluonStar::sigmaHat() {

  // RS graviton coupling.
  double sigma = sigma0 * pow2(m_coupling[min(abs(id1), 9)]);

  return sigma;
}

//--------------------------------------------------------------------------

// Select identity, colour and anticolour.

void Sigma1qqbar2KKgluonStar::setIdColAcol() {

  // Flavours trivial.
  setId( id1, id2, idKKgluon);

  // Colour flow topologies. Swap when antiquarks.
  setColAcol( 1, 0, 0, 2, 1, 2);
  if (id1 < 0) swapColAcol();

}

//--------------------------------------------------------------------------

// Evaluate weight for KK-gluon* decay angle.
  
double Sigma1qqbar2KKgluonStar::weightDecay( Event& process, int iResBeg, 
  int iResEnd) {

  // Identity of mother of decaying reseonance(s).
  int idMother = process[process[iResBeg].mother1()].idAbs();

  // For top decay hand over to standard routine.
  if (idMother == 6) 
    return weightTopDecay( process, iResBeg, iResEnd);

  // G* should sit in entry 5.
  if (iResBeg != 5 || iResEnd != 5) return 1.;

  // Phase space factors. Reconstruct decay angle.
  double mr1    = pow2(process[6].m()) / sH;
  double mr2    = pow2(process[7].m()) / sH;
  double betaf  = sqrtpos( pow2(1. - mr1 - mr2) - 4. * mr1 * mr2); 
  double cosThe = (process[3].p() - process[4].p()) 
    * (process[7].p() - process[6].p()) / (sH * betaf);

  // Default is isotropic decay.
  double wt     = 1.;

  // Angular weight for f + fbar -> g* -> f + fbar.
  if (process[6].idAbs() < 19)
    wt = (1. + pow2(cosThe) + (1 - pow2(betaf)) * (1 - pow2(cosThe))) / 2.;

  // Done.
  return wt;

}

//==========================================================================

// Sigma2gg2GravitonStarg class.
// Cross section for g g -> G* g (excited graviton state). 

//--------------------------------------------------------------------------

// Initialize process. 
  
void Sigma2gg2GravitonStarg::initProc() {

  // Store G* mass and width for propagator. 
  idGstar  = 5100039;
  mRes     = particleDataPtr->m0(idGstar);
  GammaRes = particleDataPtr->mWidth(idGstar);
  m2Res    = mRes*mRes;
  GamMRat  = GammaRes / mRes;

  // Overall coupling strength kappa * m_G*.
  kappaMG  = settingsPtr->parm("ExtraDimensionsG*:kappaMG");

   // Secondary open width fraction.
  openFrac = particleDataPtr->resOpenFrac(idGstar);

} 

//--------------------------------------------------------------------------

// Evaluate sigmaHat(sHat), part independent of incoming flavour. 

void Sigma2gg2GravitonStarg::sigmaKin() { 

  //  Evaluate cross section. Secondary width for G*.
  sigma = (3. * pow2(kappaMG) * alpS) / (32. * sH * s3)
    * ( pow2(tH2 + tH * uH + uH2) / (sH2 * tH * uH) 
    + 2. * (tH2 / uH + uH2 / tH) / sH + 3. * (tH / uH + uH / tH)
    + 2. * (sH / uH + sH/tH) + sH2 / (tH * uH) );
  sigma *= openFrac;

}

//--------------------------------------------------------------------------

// Select identity, colour and anticolour.

void Sigma2gg2GravitonStarg::setIdColAcol() {

  // Flavours trivial.
  setId( 21, 21, idGstar, 21);

  // Colour flow topologies: random choice between two mirrors.
  if (rndmPtr->flat() < 0.5) setColAcol( 1, 2, 2, 3, 0, 0, 1, 3);
  else                    setColAcol( 1, 2, 3, 1, 0, 0, 3, 2);

}

//--------------------------------------------------------------------------

// Evaluate weight for decay angles: currently G* assumed isotropic.
  
double Sigma2gg2GravitonStarg::weightDecay( Event& process, int iResBeg, 
  int iResEnd) {

  // Identity of mother of decaying reseonance(s).
  int idMother = process[process[iResBeg].mother1()].idAbs();

  // For top decay hand over to standard routine.
  if (idMother == 6) 
    return weightTopDecay( process, iResBeg, iResEnd);

  // No equations for G* decay so assume isotropic.
  return 1.;

}

//==========================================================================

// Sigma2qg2GravitonStarq class.
// Cross section for q g -> G* q (excited graviton state). 

//--------------------------------------------------------------------------

// Initialize process. 
  
void Sigma2qg2GravitonStarq::initProc() {

  // Store G* mass and width for propagator. 
  idGstar  = 5100039;
  mRes     = particleDataPtr->m0(idGstar);
  GammaRes = particleDataPtr->mWidth(idGstar);
  m2Res    = mRes*mRes;
  GamMRat  = GammaRes / mRes;

  // Overall coupling strength kappa * m_G*.
  kappaMG  = settingsPtr->parm("ExtraDimensionsG*:kappaMG");

   // Secondary open width fraction.
  openFrac = particleDataPtr->resOpenFrac(idGstar);

} 

//--------------------------------------------------------------------------

// Evaluate sigmaHat(sHat), part independent of incoming flavour. 

void Sigma2qg2GravitonStarq::sigmaKin() { 

  //  Evaluate cross section. Secondary width for G*.
  sigma = -(pow2(kappaMG) * alpS) / (192. * sH * s3)
    * ( 4. * (sH2 + uH2) / (tH * sH) + 9. * (sH + uH) / sH + sH / uH
    + uH2 / sH2 + 3. * tH * (4. + sH / uH + uH / sH) / sH
    + 4. * tH2 * (1. / uH + 1. / sH) / sH + 2. * tH2 * tH / (uH * sH2) );
  sigma *= openFrac;

}

//--------------------------------------------------------------------------

// Select identity, colour and anticolour.

void Sigma2qg2GravitonStarq::setIdColAcol() {

  // Flavour set up for q g -> H q.
  int idq = (id2 == 21) ? id1 : id2;
  setId( id1, id2, idGstar, idq);

  // tH defined between f and f': must swap tHat <-> uHat if q g in.
  swapTU = (id2 == 21); 

  // Colour flow topologies. Swap when antiquarks.
  if (id2 == 21) setColAcol( 1, 0, 2, 1, 0, 0, 2, 0);
  else           setColAcol( 2, 1, 1, 0, 0, 0, 2, 0);
  if (idq < 0) swapColAcol();

}

//--------------------------------------------------------------------------

// Evaluate weight for decay angles: currently G* assumed isotropic.
  
double Sigma2qg2GravitonStarq::weightDecay( Event& process, int iResBeg, 
  int iResEnd) {

  // Identity of mother of decaying reseonance(s).
  int idMother = process[process[iResBeg].mother1()].idAbs();

  // For top decay hand over to standard routine.
  if (idMother == 6) 
    return weightTopDecay( process, iResBeg, iResEnd);

  // No equations for G* decay so assume isotropic.
  return 1.;

}

//==========================================================================

// Sigma2qqbar2GravitonStarg class.
// Cross section for q qbar -> G* g (excited graviton state). 

//--------------------------------------------------------------------------

// Initialize process. 
  
void Sigma2qqbar2GravitonStarg::initProc() {

  // Store G* mass and width for propagator. 
  idGstar  = 5100039;
  mRes     = particleDataPtr->m0(idGstar);
  GammaRes = particleDataPtr->mWidth(idGstar);
  m2Res    = mRes*mRes;
  GamMRat  = GammaRes / mRes;

  // Overall coupling strength kappa * m_G*.
  kappaMG  = settingsPtr->parm("ExtraDimensionsG*:kappaMG");

   // Secondary open width fraction.
  openFrac = particleDataPtr->resOpenFrac(idGstar);

} 

//--------------------------------------------------------------------------

// Evaluate sigmaHat(sHat), part independent of incoming flavour. 

void Sigma2qqbar2GravitonStarg::sigmaKin() { 

  // Evaluate cross section. Secondary width for G*.
  sigma = (pow2(kappaMG) * alpS) / (72. * sH * s3)
    * ( 4. * (tH2 + uH2) / sH2 + 9. * (tH + uH) / sH 
    + (tH2 / uH + uH2 / tH) / sH + 3. * (4. + tH / uH + uH/ tH)
    + 4. * (sH / uH + sH / tH) + 2. * sH2 / (tH * uH) );
  sigma *= openFrac;

}

//--------------------------------------------------------------------------

// Select identity, colour and anticolour.

void Sigma2qqbar2GravitonStarg::setIdColAcol() {

  // Flavours trivial.
  setId( id1, id2, idGstar, 21);

  // Colour flow topologies. Swap when antiquarks.
  setColAcol( 1, 0, 0, 2, 0, 0, 1, 2);
  if (id1 < 0) swapColAcol();

}

//--------------------------------------------------------------------------

// Evaluate weight for decay angles: currently G* assumed isotropic.
  
double Sigma2qqbar2GravitonStarg::weightDecay( Event& process, int iResBeg, 
  int iResEnd) {

  // Identity of mother of decaying reseonance(s).
  int idMother = process[process[iResBeg].mother1()].idAbs();

  // For top decay hand over to standard routine.
  if (idMother == 6) 
    return weightTopDecay( process, iResBeg, iResEnd);

  // No equations for G* decay so assume isotropic.
  return 1.;

}

//==========================================================================

// NOAM: Sigma2ffbar2TEVffbar class.
// Cross section for, f fbar -> gammaKK/ZKK -> F Fbar.
// Process provided by N. Hod et al. and is described in arXiv:XXXX.YYYY

//--------------------------------------------------------------------------

// Initialize process.

void Sigma2ffbar2TEVffbar::initProc() {

  // Process name.
  nameSave                 = "f fbar -> F Fbar (s-channel gamma_KK/Z_KK)";
  if (idNew == 4) nameSave = "f fbar -> c cbar (s-channel gamma_KK/Z_KK)";
  if (idNew == 5) nameSave = "f fbar -> b bbar (s-channel gamma_KK/Z_KK)";
  if (idNew == 6) nameSave = "f fbar -> t tbar (s-channel gamma_KK/Z_KK)";
  if (idNew == 7) nameSave = "f fbar -> b' b'bar (s-channel gamma_KK/Z_KK)";
  if (idNew == 8) nameSave = "f fbar -> t' t'bar (s-channel gamma_KK/Z_KK)";
  if (idNew == 15) 
    nameSave = "f fbar -> tau+ tau- (s-channel gamma_KK/Z_KK)";
  if (idNew == 17) 
    nameSave = "f fbar -> tau'+ tau'- (s-channel gamma_KK/Z_KK)";
  if (idNew == 18) 
    nameSave   = "f fbar -> nu'_tau nu'bar_tau (s-channel gamma_KK/Z_KK)";

  // Allow to pick only gamma* or Z0 part of full gamma*/Z0 expression.
  gmZmode = settingsPtr->mode("ExtraDimensionsTEV:gmZmode");
  
  // Pick number of KK excitations
  n_excitation_max  = (int)settingsPtr->parm("ExtraDimensionsTEV:nMax");
  
  // Initialize the widths of the KK propogators.
  wgmKKFactor = 0.; // partial width of the KK photon
  wgmKKn      = 0.; // total width of the KK photon
  wZKKn       = 0.; // will be proportional to "wZ0" + ttbar addition

  // Store Z0 mass and width for propagator.
  wZ0 = particleDataPtr->mWidth(23);
  mRes  = particleDataPtr->m0(23);
  m2Res = mRes*mRes;

  // Store the top mass for the ttbar width calculations
  mTop  = particleDataPtr->m0(6);
  m2Top = mTop*mTop;

  // Store the KK mass parameter, equivalent to the mass of the first KK 
  // excitation: particleDataPtr->m0(5000023);
  mStar = (double)settingsPtr->parm("ExtraDimensionsTEV:mStar"); 
  
  // Get alphaEM - relevant for the calculation of the widths
  alphaem_fixed = settingsPtr->parm("StandardModel:alphaEM0");
  
  // initialize imaginari number
  M_I = complex(0.,1.);

  // Sum all partial widths of the KK photon except for the ttbar channel
  // which is handeled afterwards seperately
  if (gmZmode>=0 && gmZmode<=5) {
    for (int i=1 ; i<17 ; i++) {
      if (i==7) { i=11; }
      if (i==6) { continue; } // skip the ttbar decay and add its contribution later
      if (i<9) {
        wgmKKFactor += ( (alphaem_fixed / 6.) * 4. 
                    * coupSMPtr->ef(i) * coupSMPtr->ef(i) * 3. );
      }
      else {
        wgmKKFactor += (alphaem_fixed / 6.) * 4.
                    * coupSMPtr->ef(i) * coupSMPtr->ef(i);
      }
    }
  }
  
  // Get the helicity-couplings of the Z0 to all the fermions except top
  gMinusF  = ( coupSMPtr->t3f(idNew) - coupSMPtr->ef(idNew) 
           * coupSMPtr->sin2thetaW() ) 
           / sqrt( coupSMPtr->sin2thetaW()*coupSMPtr->cos2thetaW() );
  gPlusF   = -1. * coupSMPtr->ef(idNew) * coupSMPtr->sin2thetaW() 
           / sqrt( coupSMPtr->sin2thetaW() * coupSMPtr->cos2thetaW() );
  // Get the helicity-couplings of the Z0 to the top quark
  gMinusTop  = ( coupSMPtr->t3f(6) - coupSMPtr->ef(6)
             * coupSMPtr->sin2thetaW() )
             / sqrt( coupSMPtr->sin2thetaW()*coupSMPtr->cos2thetaW() );

  gPlusTop   = -1. * coupSMPtr->ef(6) * coupSMPtr->sin2thetaW()
             / sqrt( coupSMPtr->sin2thetaW() * coupSMPtr->cos2thetaW() );
  // calculate the constant factor of the unique ttbar decay width
  ttbar_wFactorA = pow2(gMinusTop) + pow2(gPlusTop);
  ttbar_wFactorB = 6.*gMinusTop*gPlusTop - pow2(gMinusTop) - pow2(gPlusTop);

  // Secondary open width fraction, relevant for top (or heavier).
  openFracPair = particleDataPtr->resOpenFrac(idNew, -idNew);
}

//--------------------------------------------------------------------------

// For improving the phase-space sampling (there can be 2 resonances)

int Sigma2ffbar2TEVffbar::resonanceB() {

  return 23;

}

//--------------------------------------------------------------------------

// For improving the phase-space sampling (there can be 2 resonances)

int Sigma2ffbar2TEVffbar::resonanceA() {

  if (gmZmode>=3) {
    phaseSpace_mHatMin  = settingsPtr->parm("PhaseSpace:mHatMin");
    phaseSpace_mHatMax  = settingsPtr->parm("PhaseSpace:mHatMax");
    double mResFirstKKMode = sqrt(pow2(particleDataPtr->m0(23)) + pow2(mStar));
    if (mResFirstKKMode/2. <= phaseSpace_mHatMax 
	|| 3*mResFirstKKMode/2. >= phaseSpace_mHatMin) { return 5000023; }
    else { return 23; }
  }
  else { return 23; } // no KK terms at all

}

//--------------------------------------------------------------------------

// Evaluate d(sigmaHat)/d(tHat), part independent of incoming flavour.

void Sigma2ffbar2TEVffbar::sigmaKin() {

  // Check that above threshold.
  isPhysical     = true;
  if (mH < m3 + m4 + MASSMARGIN) {
    isPhysical   = false;
    return;
  }

  // Define average F, Fbar mass so same beta. Phase space.
  double s34Avg  = 0.5 * (s3 + s4) - 0.25 * pow2(s3 - s4) / sH;
  mr             = s34Avg / sH;
  betaf          = sqrtpos(1. - 4. * mr);

  // Reconstruct decay angle so can reuse 2 -> 1 cross section.
  cosThe         = (tH - uH) / (betaf * sH);

}

//--------------------------------------------------------------------------

// Evaluate d(sigmaHat)/d(tHat), including incoming flavour dependence.

double Sigma2ffbar2TEVffbar::sigmaHat() {

  // Fail if below threshold.
  if (!isPhysical) return 0.;

  // Couplings for in/out-flavours.
  int idAbs = abs(id1);

  // The couplings of the Z0 to the fermions for in/out flavors
  gMinusf  = ( coupSMPtr->t3f(idAbs) - coupSMPtr->ef(idAbs) 
	       * coupSMPtr->sin2thetaW() ) 
           / sqrt( coupSMPtr->sin2thetaW()*coupSMPtr->cos2thetaW() );
  gPlusf   = -1. * coupSMPtr->ef(idAbs)*coupSMPtr->sin2thetaW() 
           / sqrt( coupSMPtr->sin2thetaW()*coupSMPtr->cos2thetaW() );

  // Initialize the some values
  helicityME2 = 0.;
  coefAngular = 0.;
  gf=0.;
  gF=0.;
  gammaProp = complex(0.,0.);
  resProp   = complex(0.,0.);
  gmPropKK  = complex(0.,0.);
  ZPropKK   = complex(0.,0.);
  totalProp = complex(0.,0.);

  // Sum all initial and final helicity states this corresponds to an 
  // unpolarized beams and unmeasured polarization final-state
  for (double helicityf=-0.5 ; helicityf<=0.5 ; helicityf++) {
    for (double helicityF=-0.5 ; helicityF<=0.5 ; helicityF++) {
	  // the couplings for the initial-final helicity configuration
      gF = (helicityF == +0.5) ? gMinusF : gPlusF;
      gf = (helicityf == +0.5) ? gMinusf : gPlusf;
      // 0=SM gmZ,  1=SM gm,  2=SM Z,  3=SM+KK gmZ,  4=KK gm,  5=KK Z
      switch(gmZmode) { 
        case 0: // SM photon and Z0 only
          gammaProp = coupSMPtr->ef(idAbs)*coupSMPtr->ef(idNew)/sH;
          resProp   = gf*gF/( sH - m2Res + M_I*sH*(wZ0/mRes) );
          break;
        case 1: // SM photon only
          gammaProp = coupSMPtr->ef(idAbs)*coupSMPtr->ef(idNew)/sH;
          break;
        case 2: // SM Z0 only
          resProp   = gf*gF/( sH - m2Res + M_I*sH*(wZ0/mRes) );
          break;
        case 3: // KK photon and Z
          gammaProp = coupSMPtr->ef(idAbs)*coupSMPtr->ef(idNew)/sH;
          resProp   = gf*gF/( sH - m2Res + M_I*sH*(wZ0/mRes) );
          ZPropKK   = complex(0.,0.);
          gmPropKK  = complex(0.,0.);
		  // Sum all KK excitations contributions
          for(int n_excitation = 1; n_excitation <= n_excitation_max; 
            n_excitation++) {
            mZKKn   = sqrt(m2Res + pow2(mStar * n_excitation));
            m2ZKKn  = m2Res + pow2(mStar * n_excitation);
            mgmKKn  = mStar * n_excitation;
            m2gmKKn = (mStar*n_excitation)*(mStar*n_excitation);
            // calculate the width of the n'th excitation of the KK Z 
	    // (proportional to the Z0 width + ttbar partial width)
            ttbar_wZKKn = 2.*(alphaem_fixed*3./6.)*mZKKn
                        * sqrt(1.-4.*m2Top/m2ZKKn)
                        * (ttbar_wFactorA+(m2Top/m2ZKKn)*ttbar_wFactorB);
            wZKKn       = 2.*wZ0*mZKKn/mRes+ttbar_wZKKn;
	    // calculate the width of the n'th excitation of the 
	    // KK photon
            ttbar_wgmKKn = 2.*(alphaem_fixed*3./6.)*mgmKKn
                         * sqrt(1.-4.*m2Top/m2gmKKn)
                         * 2.*pow2(coupSMPtr->ef(6))*(1.+2.*(m2Top/m2gmKKn));
            wgmKKn       = wgmKKFactor*mgmKKn+ttbar_wgmKKn;
	    // the propogators
            gmPropKK += (2.*coupSMPtr->ef(idAbs)*coupSMPtr->ef(idNew)) 
	              / (sH-m2gmKKn+M_I*sH*wgmKKn/mgmKKn);
            ZPropKK  += (2.*gf*gF)/(sH-m2ZKKn+M_I*sH*wZKKn/mZKKn );
          }
          break;
        case 4: // SM photon and Z0 with KK photon only
          gammaProp = coupSMPtr->ef(idAbs)*coupSMPtr->ef(idNew)/sH;
          resProp   = gf*gF/( sH - m2Res + M_I*sH*(wZ0/mRes) );
          gmPropKK  = complex(0.,0.);
          for (int n_excitation = 1; n_excitation <= n_excitation_max; 
            n_excitation++ ) {
            mgmKKn  = mStar * n_excitation;
            m2gmKKn = (mStar*n_excitation)*(mStar*n_excitation);

            ttbar_wgmKKn = 2.*(alphaem_fixed*3./6.)*mgmKKn
                           * sqrt(1.-4.*m2Top/m2gmKKn)
                           * 2.*pow2(coupSMPtr->ef(6))*(1.+2.*(m2Top/m2gmKKn));
            wgmKKn         = wgmKKFactor*mgmKKn+ttbar_wgmKKn;
            gmPropKK += (2.*coupSMPtr->ef(idAbs)*coupSMPtr->ef(idNew)) 
	              / (sH-m2gmKKn+M_I*sH*wgmKKn/mgmKKn);
          }
          break;
        case 5: // SM photon and Z0 with KK Z only
          gammaProp = coupSMPtr->ef(idAbs)*coupSMPtr->ef(idNew)/sH;
          resProp   = gf*gF/( sH - m2Res + M_I*sH*(wZ0/mRes) );
          ZPropKK   = complex(0.,0.);
          for (int n_excitation = 1; n_excitation <= n_excitation_max; 
            n_excitation++ ) {
            mZKKn   = sqrt(m2Res + pow2(mStar * n_excitation));
            m2ZKKn  = m2Res + pow2(mStar * n_excitation);

            ttbar_wZKKn = 2.*(alphaem_fixed*3./6.)*mZKKn
                          * sqrt(1.-4.*m2Top/m2ZKKn)
                          * (ttbar_wFactorA+(m2Top/m2ZKKn)*ttbar_wFactorB);
            wZKKn       = 2.*wZ0*mZKKn/mRes+ttbar_wZKKn;
            ZPropKK    += (2.*gf*gF)/(sH-m2ZKKn+M_I*sH*wZKKn/mZKKn );
          }
          break;
        default: break;
      } // end run over initial and final helicity states
	  
	  // sum all contributing amplitudes
      totalProp = gammaProp + resProp + ZPropKK + gmPropKK;
	  
	  // angular distribution for the helicity configuration
      coefAngular = 1. + 4. * helicityF * helicityf * cosThe;
	  
	  // the squared helicity matrix element
      helicityME2 += real(totalProp*conj(totalProp))*pow2(coefAngular);
    }
  }

  // calculate the coefficient of the squared helicity matrix element.
  coefTot = (2./sH) * 2*M_PI * pow2(alpEM)/(4.*sH) * pow2(sH)/4.;

  // the full squared helicity matrix element.
  double sigma = helicityME2 * coefTot;

  // Top: corrections for closed decay channels.
  sigma *= openFracPair;

  // Initial-state colour factor. Answer.
  if (idAbs < 9) sigma /= 3.;
  return sigma;
}

//--------------------------------------------------------------------------

// Select identity, colour and anticolour.

void Sigma2ffbar2TEVffbar::setIdColAcol() {

  // Set outgoing flavours.
  id3 = (id1 > 0) ? idNew : -idNew;
  setId( id1, id2, id3, -id3);

  // Colour flow topologies. Swap when antiquarks.
  if (abs(id1) < 9 && idNew < 9) setColAcol( 1, 0, 0, 1, 2, 0, 0, 2);
  else if (abs(id1) < 9)         setColAcol( 1, 0, 0, 1, 0, 0, 0, 0);
  else if (idNew < 9)            setColAcol( 0, 0, 0, 0, 1, 0, 0, 1);
  else                           setColAcol( 0, 0, 0, 0, 0, 0, 0, 0);
  if (id1 < 0) swapColAcol();

}

//--------------------------------------------------------------------------

// Evaluate weight for decay angles of W in top decay.

double Sigma2ffbar2TEVffbar::weightDecay( Event& process, int iResBeg,
  int iResEnd) {

  // For top decay hand over to standard routine, else done.
  if (idNew == 6 && process[process[iResBeg].mother1()].idAbs() == 6)
       return weightTopDecay( process, iResBeg, iResEnd);
  else return 1.;

}
		
//==========================================================================

// Sigma2gg2LEDUnparticleg class.
// Cross section for g g -> U/G g (real graviton emission in 
// large extra dimensions or unparticle emission). 

//--------------------------------------------------------------------------

void Sigma2gg2LEDUnparticleg::initProc() {
  
  // Init model parameters.
  m_idG    = 5000039;
  if (m_graviton) {
    m_spin     = (settingsPtr->flag("ExtraDimensionsLED:GravScalar")) ? 0 : 2;
    m_nGrav    = settingsPtr->mode("ExtraDimensionsLED:n");
    m_dU       = 0.5 * m_nGrav + 1;
    m_LambdaU  = settingsPtr->parm("ExtraDimensionsLED:MD");
    m_lambda   = 1;
    m_cutoff   = settingsPtr->mode("ExtraDimensionsLED:CutOffMode"); 
    m_tff      = settingsPtr->parm("ExtraDimensionsLED:t");
    m_cf       = settingsPtr->parm("ExtraDimensionsLED:c");
  } else {
    m_spin     = settingsPtr->mode("ExtraDimensionsUnpart:spinU");
    m_dU       = settingsPtr->parm("ExtraDimensionsUnpart:dU");
    m_LambdaU  = settingsPtr->parm("ExtraDimensionsUnpart:LambdaU");
    m_lambda   = settingsPtr->parm("ExtraDimensionsUnpart:lambda");
    m_cutoff   = settingsPtr->mode("ExtraDimensionsUnpart:CutOffMode"); 
  }
  
  // The A(dU) or S'(n) value.
  double tmpAdU = 0;
  if (m_graviton) { 
    tmpAdU  = 2 * M_PI * sqrt( pow(M_PI, double(m_nGrav)) ) 
            / GammaReal(0.5 * m_nGrav); 
    if (m_spin == 0) {  // Scalar graviton
      tmpAdU *= sqrt( pow(2., double(m_nGrav)) );
      m_cf   *= m_cf;
    }
  } else {
    tmpAdU = 16 * pow2(M_PI) * sqrt(M_PI) / pow(2. * M_PI, 2. * m_dU)
      * GammaReal(m_dU + 0.5) / (GammaReal(m_dU - 1.) * GammaReal(2. * m_dU));
  }

  // Cross section related constants 
  // and ME dependent powers of lambda / LambdaU.
  double tmpExp   = m_dU - 2;
  double tmpLS    = pow2(m_LambdaU);
  m_constantTerm = tmpAdU / (2 * 16 * pow2(M_PI) * tmpLS * pow(tmpLS,tmpExp));
  if (m_graviton) { 
    m_constantTerm /= tmpLS;
  } else if (m_spin == 0) {
    m_constantTerm *= pow2(m_lambda) / tmpLS;
  } else {
    m_constantTerm = 0;
    infoPtr->errorMsg("Error in Sigma2gg2LEDUnparticleg::initProc: "
		      "Incorrect spin value (turn process off)!");
  }

} 

//--------------------------------------------------------------------------

void Sigma2gg2LEDUnparticleg::sigmaKin() { 

  // Set graviton mass.
  mG        = m3;
  mGS       = mG*mG;

  // Set mandelstam variables and ME expressions.
  if (m_graviton) {

    double A0 = 1/sH;    
    if (m_spin == 0) {  // Scalar graviton
      double tmpTerm1 = uH + tH;
      double tmpTerm2 = uH + sH;
      double tmpTerm3 = tH + sH;
      double T0 = pow(tmpTerm1,4) + pow(tmpTerm2,4) + pow(tmpTerm3,4) 
	        + 12. * sH * tH * uH * mGS;
      m_sigma0 = m_cf * A0 * T0 / (sH2 * tH * uH);
    } else {
      double xH = tH/sH;
      double yH = mGS/sH;
      double xHS = pow2(xH);
      double yHS = pow2(yH);
      double xHC = pow(xH,3);
      double yHC = pow(yH,3);
      double xHQ = pow(xH,4);
      double yHQ = pow(yH,4);
      
      double T0 = 1/(xH*(yH-1-xH));
      double T1 = 1 + 2*xH + 3*xHS + 2*xHC + xHQ;
      double T2 = -2*yH*(1 + xHC);
      double T3 = 3*yHS*(1 + xHS);
      double T4 = -2*yHC*(1 + xH);
      double T5 = yHQ;
      
      m_sigma0 = A0 * T0 *( T1 + T2 + T3 + T4 + T5 );
    }

  } else if (m_spin == 0) {
    
    double A0  = 1/pow2(sH);    
    double sHQ = pow(sH,4);
    double tHQ = pow(tH,4);
    double uHQ = pow(uH,4);

    m_sigma0 = A0 * (pow(mGS,4) + sHQ + tHQ + uHQ) / (sH * tH * uH);

  }

  // Mass measure, (m^2)^(d-2).
  double tmpExp = m_dU - 2;
  m_sigma0 *= pow(mGS, tmpExp);

  // Constants.
  m_sigma0 *= m_constantTerm;

}

//--------------------------------------------------------------------------

double Sigma2gg2LEDUnparticleg::sigmaHat() { 

  // Mass spectrum weighting.
  double sigma = m_sigma0 / runBW3;      

  // SM couplings...
  if (m_graviton) {
    sigma *= 16 * M_PI * alpS * 3 / 16;
  } else if (m_spin == 0) {
    sigma *= 6 * M_PI * alpS;
  }

  // Truncate sH region or use form factor.
  // Form factor uses either pythia8 renormScale2 
  // or E_jet in cms.
  if (m_cutoff == 1) {
    if (sH > pow2(m_LambdaU) ) { sigma *= pow(m_LambdaU,4)/pow2(sH); }
  } else if ( (m_graviton && (m_spin == 2)) 
	   && ((m_cutoff == 2) || (m_cutoff == 3)) ) {
    double tmp_mu = sqrt(Q2RenSave);
    if (m_cutoff == 3) tmp_mu = (sH + s4 - s3) / (2 * mH);
    double tmp_formfact = tmp_mu / (m_tff * m_LambdaU);
    double tmp_exp = double(m_nGrav) + 2;
    sigma *= 1 / (1 + pow(tmp_formfact, tmp_exp));
  }
  
  return sigma;  
}

//--------------------------------------------------------------------------

void Sigma2gg2LEDUnparticleg::setIdColAcol() {

 // Flavours trivial.
  setId( 21, 21, m_idG, 21);

  // Colour flow topologies: random choice between two mirrors.
  if (rndmPtr->flat() < 0.5) setColAcol( 1, 2, 2, 3, 0, 0, 1, 3);
  else                    setColAcol( 1, 2, 3, 1, 0, 0, 3, 2);

}

//==========================================================================

// Sigma2qg2LEDUnparticleq class.
// Cross section for q g -> U/G q (real graviton emission in 
// large extra dimensions or unparticle emission). 

//--------------------------------------------------------------------------

void Sigma2qg2LEDUnparticleq::initProc() {
  
  // Init model parameters.
  m_idG    = 5000039;
  if (m_graviton) {
    m_spin     = (settingsPtr->flag("ExtraDimensionsLED:GravScalar")) ? 0 : 2;
    m_nGrav    = settingsPtr->mode("ExtraDimensionsLED:n");
    m_dU       = 0.5 * m_nGrav + 1;
    m_LambdaU  = settingsPtr->parm("ExtraDimensionsLED:MD");
    m_lambda   = 1;
    m_cutoff   = settingsPtr->mode("ExtraDimensionsLED:CutOffMode"); 
    m_tff      = settingsPtr->parm("ExtraDimensionsLED:t");
    m_gf       = settingsPtr->parm("ExtraDimensionsLED:g");
    m_cf       = settingsPtr->parm("ExtraDimensionsLED:c");
  } else {
    m_spin     = settingsPtr->mode("ExtraDimensionsUnpart:spinU");
    m_dU       = settingsPtr->parm("ExtraDimensionsUnpart:dU");
    m_LambdaU  = settingsPtr->parm("ExtraDimensionsUnpart:LambdaU");
    m_lambda   = settingsPtr->parm("ExtraDimensionsUnpart:lambda");
    m_cutoff   = settingsPtr->mode("ExtraDimensionsUnpart:CutOffMode"); 
  }

  // The A(dU) or S'(n) value.
  double tmpAdU = 0;
  if (m_graviton) { 
    tmpAdU  = 2 * M_PI * sqrt( pow(M_PI, double(m_nGrav)) ) 
            / GammaReal(0.5 * m_nGrav); 
    if (m_spin == 0) {  // Scalar graviton
      tmpAdU *= 2. * sqrt( pow(2., double(m_nGrav)) );
      m_cf   *= 4. * m_cf / pow2(m_LambdaU);
      double tmpExp = 2. * double(m_nGrav) / (double(m_nGrav) + 2.);
      m_gf   *= m_gf / pow(2. * M_PI, tmpExp);
    }
  } else {
    tmpAdU = 16 * pow2(M_PI) * sqrt(M_PI) / pow(2. * M_PI, 2. * m_dU)
      * GammaReal(m_dU + 0.5) / (GammaReal(m_dU - 1.) * GammaReal(2. * m_dU));
  }

  // Cross section related constants 
  // and ME dependent powers of lambda / LambdaU.
  double tmpExp   = m_dU - 2;
  double tmpLS    = pow2(m_LambdaU);
  m_constantTerm = tmpAdU / (2 * 16 * pow2(M_PI) * tmpLS * pow(tmpLS,tmpExp));
  if (m_graviton && (m_spin == 2)) { 
    m_constantTerm /= tmpLS;
  } else if (m_spin == 1) {
    m_constantTerm *= pow2(m_lambda);
  } else if (m_spin == 0) {
    m_constantTerm *= pow2(m_lambda);
  } else {
    m_constantTerm = 0;
    infoPtr->errorMsg("Error in Sigma2qg2LEDUnparticleq::initProc: "
		      "Incorrect spin value (turn process off)!");
  }


} 

//--------------------------------------------------------------------------

void Sigma2qg2LEDUnparticleq::sigmaKin() { 

  // Set graviton mass.
  mG        = m3;
  mGS       = mG*mG;

  // Set mandelstam variables and ME expressions.
  if (m_graviton) {

    double A0 = 1/sH;    
    if (m_spin == 0) {  // Scalar graviton
      A0 /= sH; 
      double T0 = -(uH2 + pow2(mGS)) / (sH * tH);
      double T1 = -(tH2 + sH2)/ uH;
      m_sigma0 = A0 * (m_gf * T0 + m_cf * T1);
    } else {
      double xH = tH/sH;
      double yH = mGS/sH;
      double x2H = xH/(yH - 1 - xH);
      double y2H = yH/(yH - 1 - xH);
      double x2HS = pow2(x2H);
      double y2HS = pow2(y2H);
      double x2HC = pow(x2H,3);
      double y2HC = pow(y2H,3);
      
      double T0 = -(yH - 1 - xH);
      double T20 = 1/(x2H*(y2H-1-x2H));
      double T21 = -4*x2H*(1 + x2H)*(1 + 2*x2H + 2*x2HS);
      double T22 = y2H*(1 + 6*x2H + 18*x2HS + 16*x2HC);
      double T23 = -6*y2HS*x2H*(1+2*x2H);
      double T24 = y2HC*(1 + 4*x2H);
      
      m_sigma0 = A0 * T0 * T20 * ( T21 + T22 + T23 + T24 );
    }

  } else if (m_spin == 1) {
    
    double A0  = 1/pow2(sH);   
    double tmpTerm1 = tH - mGS; 
    double tmpTerm2 = sH - mGS; 

    m_sigma0 = A0 * (pow2(tmpTerm1) + pow2(tmpTerm2)) / (sH*tH);

  } else if (m_spin == 0) {
    
    double A0  = 1/pow2(sH);    

    m_sigma0 = A0 * (pow2(tH) + pow2(mGS)) / (sH*uH);  // Sign correction by Tom

  }

  // Mass measure, (m^2)^(d-2).
  double tmpExp = m_dU - 2;
  m_sigma0 *= pow(mGS, tmpExp);

  // Constants.
  m_sigma0 *= m_constantTerm;

}

//--------------------------------------------------------------------------

double Sigma2qg2LEDUnparticleq::sigmaHat() { 

  // Mass spactrum weighting.
  double sigma = m_sigma0 /runBW3;      

  // SM couplings...
  if (m_graviton) {
    sigma *= 16 * M_PI * alpS / 96;
  } else if (m_spin == 1) {
    sigma *= - 4 * M_PI * alpS / 3;
  } else if (m_spin == 0) {
    sigma *= - 2 * M_PI * alpS / 3;
  }

  // Truncate sH region or use form factor.
  // Form factor uses either pythia8 renormScale2 
  // or E_jet in cms.
  if (m_cutoff == 1) {
    if (sH > pow2(m_LambdaU) ) { sigma *= pow(m_LambdaU,4)/pow2(sH); }
  } else if ( (m_graviton && (m_spin == 2)) 
	   && ((m_cutoff == 2) || (m_cutoff == 3)) ) {
    double tmp_mu = sqrt(Q2RenSave);
    if (m_cutoff == 3) tmp_mu = (sH + s4 - s3) / (2 * mH);
    double tmp_formfact = tmp_mu / (m_tff * m_LambdaU);
    double tmp_exp = double(m_nGrav) + 2;
    sigma *= 1 / (1 + pow(tmp_formfact, tmp_exp));
  }
  
  return sigma;  
}

//--------------------------------------------------------------------------

void Sigma2qg2LEDUnparticleq::setIdColAcol() {

  // Flavour set up for q g -> G* q.
  int idq = (id2 == 21) ? id1 : id2;
  setId( id1, id2, m_idG, idq);

  // tH defined between f and f': must swap tHat <-> uHat if q g in.
  swapTU = (id2 == 21); 

  // Colour flow topologies. Swap when antiquarks.
  if (id2 == 21) setColAcol( 1, 0, 2, 1, 0, 0, 2, 0);
  else           setColAcol( 2, 1, 1, 0, 0, 0, 2, 0);
  if (idq < 0) swapColAcol();

}

//==========================================================================

// Sigma2qqbar2LEDUnparticleg class.
// Cross section for q qbar -> U/G g (real graviton emission in 
// large extra dimensions or unparticle emission). 

//--------------------------------------------------------------------------

void Sigma2qqbar2LEDUnparticleg::initProc() {
  
  // Init model parameters.
  m_idG    = 5000039;
  if (m_graviton) {
    m_spin     = (settingsPtr->flag("ExtraDimensionsLED:GravScalar")) ? 0 : 2;
    m_nGrav    = settingsPtr->mode("ExtraDimensionsLED:n");
    m_dU       = 0.5 * m_nGrav + 1;
    m_LambdaU  = settingsPtr->parm("ExtraDimensionsLED:MD");
    m_lambda   = 1;
    m_cutoff   = settingsPtr->mode("ExtraDimensionsLED:CutOffMode"); 
    m_tff      = settingsPtr->parm("ExtraDimensionsLED:t");
    m_gf       = settingsPtr->parm("ExtraDimensionsLED:g");
    m_cf       = settingsPtr->parm("ExtraDimensionsLED:c");
  } else {
    m_spin     = settingsPtr->mode("ExtraDimensionsUnpart:spinU");
    m_dU       = settingsPtr->parm("ExtraDimensionsUnpart:dU");
    m_LambdaU  = settingsPtr->parm("ExtraDimensionsUnpart:LambdaU");
    m_lambda   = settingsPtr->parm("ExtraDimensionsUnpart:lambda");
    m_cutoff   = settingsPtr->mode("ExtraDimensionsUnpart:CutOffMode"); 
  }

  // The A(dU) or S'(n) value.
  double tmpAdU = 0;
  if (m_graviton) { 
    tmpAdU  = 2 * M_PI * sqrt( pow(M_PI, double(m_nGrav)) ) 
            / GammaReal(0.5 * m_nGrav); 
    if (m_spin == 0) {  // Scalar graviton
      tmpAdU *= 2. * sqrt( pow(2., double(m_nGrav)) );
      m_cf   *= 4. * m_cf / pow2(m_LambdaU);
      double tmpExp = 2. * double(m_nGrav) / (double(m_nGrav) + 2.);
      m_gf   *= m_gf / pow(2. * M_PI, tmpExp);
    }
  } else {
    tmpAdU = 16 * pow2(M_PI) * sqrt(M_PI) / pow(2. * M_PI, 2. * m_dU)
      * GammaReal(m_dU + 0.5) / (GammaReal(m_dU - 1.) * GammaReal(2. * m_dU));
  }

  // Cross section related constants 
  // and ME dependent powers of lambda / LambdaU.
  double tmpExp   = m_dU - 2;
  double tmpLS    = pow2(m_LambdaU);
  m_constantTerm = tmpAdU / (2 * 16 * pow2(M_PI) * tmpLS * pow(tmpLS,tmpExp));
  if (m_graviton && (m_spin == 2)) { 
    m_constantTerm /= tmpLS;
  } else if (m_spin == 1) {
    m_constantTerm *= pow2(m_lambda);
  } else if (m_spin == 0) {
    m_constantTerm *= pow2(m_lambda);
  } else {
    m_constantTerm = 0;
    infoPtr->errorMsg("Error in Sigma2qqbar2LEDUnparticleg::initProc: "
		      "Incorrect spin value (turn process off)!");
  }

} 

//--------------------------------------------------------------------------

void Sigma2qqbar2LEDUnparticleg::sigmaKin() { 

  // Set graviton mass.
  mG        = m3;
  mGS       = mG*mG;

  // Set mandelstam variables and ME expressions.
  if (m_graviton) {

    double A0 = 1/sH;   
    if (m_spin == 0) {  // Scalar graviton
      A0 /= sH; 
      double tmpTerm1 = uH + tH;
      double T0 = (2. * mGS * sH + pow2(tmpTerm1)) / (uH * tH);
      double T1 = (tH2 + uH2) / sH;
      m_sigma0 = A0 * (m_gf * T0 + m_cf * T1);
    } else { 
      double xH = tH/sH;
      double yH = mGS/sH;
      double xHS = pow2(xH);
      double yHS = pow2(yH);
      double xHC = pow(xH,3);
      double yHC = pow(yH,3);
      
      double T0 = 1/(xH*(yH-1-xH));
      double T1 = -4*xH*(1 + xH)*(1 + 2*xH + 2*xHS);
      double T2 = yH*(1 + 6*xH + 18*xHS + 16*xHC);
      double T3 = -6*yHS*xH*(1+2*xH);
      double T4 = yHC*(1 + 4*xH);
      
      m_sigma0 = A0 * T0 *( T1 + T2 + T3 + T4 );
    }

  } else if (m_spin == 1) {
    
    double A0  = 1/pow2(sH);    
    double tmpTerm1 = tH - mGS;
    double tmpTerm2 = uH - mGS;

    m_sigma0 = A0 * (pow2(tmpTerm1) + pow2(tmpTerm2)) / (tH * uH);
    
  } else if (m_spin == 0) {
    
    double A0  = 1/pow2(sH);    
    
    m_sigma0 = A0 * (pow2(sH) - pow2(mGS)) / (tH * uH);
    
  }

  // Mass measure, (m^2)^(d-2).
  double tmpExp = m_dU - 2;
  m_sigma0 *= pow(mGS, tmpExp);

  // Constants.
  m_sigma0 *= m_constantTerm;

}

//--------------------------------------------------------------------------

double Sigma2qqbar2LEDUnparticleg::sigmaHat() { 

  // Mass spactrum weighting.
  double sigma = m_sigma0 /runBW3;      

  // SM couplings...
  if (m_graviton) {
    sigma *= 16 * M_PI * alpS / 36;
  } else if (m_spin == 1) {
    sigma *= 4 * M_PI * 8 * alpS / 9;
  } else if (m_spin == 0) {
    sigma *= 4 * M_PI * 4 * alpS / 9;
  }

  // Truncate sH region or use form factor.
  // Form factor uses either pythia8 renormScale2 
  // or E_jet in cms.
  if (m_cutoff == 1) {
    if (sH > pow2(m_LambdaU) ) { sigma *= pow(m_LambdaU,4)/pow2(sH); }
  } else if ( (m_graviton && (m_spin == 2)) 
	   && ((m_cutoff == 2) || (m_cutoff == 3)) ) {
    double tmp_mu = sqrt(Q2RenSave);
    if (m_cutoff == 3) tmp_mu = (sH + s4 - s3) / (2 * mH);
    double tmp_formfact = tmp_mu / (m_tff * m_LambdaU);
    double tmp_exp = double(m_nGrav) + 2;
    sigma *= 1 / (1 + pow(tmp_formfact, tmp_exp));
  }
  
  return sigma;  
}

//--------------------------------------------------------------------------

void Sigma2qqbar2LEDUnparticleg::setIdColAcol() {

  // Flavours trivial.
  setId( id1, id2, m_idG, 21);

  // Colour flow topologies. Swap when antiquarks.
  if (abs(id1) < 9) setColAcol( 1, 0, 0, 2, 0, 0, 1, 2);
  if (id1 < 0) swapColAcol();

}

//==========================================================================

// Sigma2ffbar2LEDUnparticleZ class.
// Cross section for f fbar -> U/G Z (real LED graviton or unparticle 
// emission).

//--------------------------------------------------------------------------

// Constants: could be changed here if desired, but normally should not.
// These are of technical nature, as described for each.

// FIXRATIO:
// Ratio between the two possible coupling constants of the spin-2 ME. 
// A value different from one give rise to an IR divergence which makes 
// the event generation very slow, so this values is fixed to 1 until
// investigated further.
const double Sigma2ffbar2LEDUnparticleZ::FIXRATIO = 1.;

//--------------------------------------------------------------------------

void Sigma2ffbar2LEDUnparticleZ::initProc() {

  // Init model parameters.
  m_idG        = 5000039;
  if (m_graviton) {
    m_spin     = 2;
    m_nGrav    = settingsPtr->mode("ExtraDimensionsLED:n");
    m_dU       = 0.5 * m_nGrav + 1; 
    m_LambdaU  = settingsPtr->parm("ExtraDimensionsLED:MD");
    m_lambda   = 1;
    m_cutoff   = settingsPtr->mode("ExtraDimensionsLED:CutOffMode"); 
    m_tff      = settingsPtr->parm("ExtraDimensionsLED:t");
  } else {
    m_spin     = settingsPtr->mode("ExtraDimensionsUnpart:spinU");
    m_dU       = settingsPtr->parm("ExtraDimensionsUnpart:dU");
    m_LambdaU  = settingsPtr->parm("ExtraDimensionsUnpart:LambdaU");
    m_lambda   = settingsPtr->parm("ExtraDimensionsUnpart:lambda");
    m_ratio    = FIXRATIO; 
    //         = settingsPtr->parm("ExtraDimensionsUnpart:ratio");
    m_cutoff   = settingsPtr->mode("ExtraDimensionsUnpart:CutOffMode");
  }

  // Store Z0 mass and width for propagator.
  mZ        = particleDataPtr->m0(23);
  widZ      = particleDataPtr->mWidth(23);
  mZS       = mZ*mZ;
  mwZS      = pow2(mZ * widZ);

  // Init spin-2 parameters
  if ( m_spin != 2 ){
    m_graviton = false;
    m_lambdaPrime = 0;
  } else if (m_graviton) {
    m_lambda = 1;
    m_ratio = 1;
    m_lambdaPrime = m_lambda;
  } else {
    m_lambdaPrime = m_ratio * m_lambda;
  }

  // The A(dU) or S'(n) value
  double tmpAdU = 16 * pow2(M_PI) * sqrt(M_PI) / pow(2. * M_PI, 2. * m_dU)
    * GammaReal(m_dU + 0.5) / (GammaReal(m_dU - 1.) * GammaReal(2. * m_dU));

  if (m_graviton) { 
    tmpAdU  = 2 * M_PI * sqrt( pow(M_PI, double(m_nGrav)) ) 
            / GammaReal(0.5 * m_nGrav); 
  } 

  // Standard 2 to 2 cross section related constants
  double tmpTerm1 = 1/(2 * 16 * pow2(M_PI));
  double tmpLS    = pow2(m_LambdaU);

  // Spin dependent constants from ME.
  double tmpTerm2 = 0;
  if ( m_spin == 0 ) { 
    tmpTerm2 = 2 * pow2(m_lambda);
  } else if (m_spin == 1) {
    tmpTerm2 = 4 * pow2(m_lambda);
  } else if (m_spin == 2) {
    tmpTerm2 = pow2(m_lambda)/(4 * 3 * tmpLS);
  }

  // Unparticle phase space related
  double tmpExp2 = m_dU - 2;
  double tmpTerm3 = tmpAdU / (tmpLS * pow(tmpLS, tmpExp2));

  // All in total
  m_constantTerm = tmpTerm1 * tmpTerm2 * tmpTerm3;

} 

//--------------------------------------------------------------------------

void Sigma2ffbar2LEDUnparticleZ::sigmaKin() { 

  // Set graviton mass and some powers of mandelstam variables
  mU        = m3;
  mUS       = mU*mU;

  sHS = pow2(sH);
  tHS = pow2(tH);
  uHS = pow2(uH);
  tHC = pow(tH,3);
  uHC = pow(uH,3);
  tHQ = pow(tH,4);
  uHQ = pow(uH,4);
  tHuH = tH+uH;

  // Evaluate (m**2, t, u) part of differential cross section.
  // Extra 1/sHS comes from standard 2 to 2 cross section 
  // phase space factors.

  if ( m_spin == 0 ) {
    
    double A0 = 1/sHS;
    double T1 = - sH/tH - sH/uH;
    double T2 = - (1 - mZS/tH)*(1 - mUS/tH);
    double T3 = - (1 - mZS/uH)*(1 - mUS/uH);
    double T4 = 2*(1 - mUS/tH)*(1 - mUS/uH);

    m_sigma0 = A0 * ( T1 + T2 + T3 + T4);
    
  } else if ( m_spin == 1 ) {
    
    double A0 = 1/sHS;
    double T1 = 0.5 * (tH/uH + uH/tH); 
    double T2 =  pow2(mZS + mUS)/(tH * uH); 
    double T3 = - 0.5 * mUS * (mZS/tHS + mZS/uHS) ;
    double T4 = - (mZS+mUS)*(1/tH + 1/uH);
    
    m_sigma0 = A0 * ( T1 + T2 + T3 + T4 );

  } else if ( m_spin == 2 ) {

    double A0   = 1 / ( sHS * uHS * tHS * pow2(sH-mZS) ); 
    double F0 = 2*tHS*uHS*( 16*pow(mZS,3) +  mUS*(7*tHS + 12*tH*uH + 7*uHS)
              - 3*(3*tHC + 11*tHS*uH + 11*tH*uHS + 3*uHC)
              + 6*pow(mZS,2)*(7*mUS - 2*tHuH) + mZS*(14*pow(mUS,2) 
              - 15*tHS - 44*tH*uH - 15*uHS + 2*mUS*tHuH) );
    double F2 = 2*tHS*uHS*tHuH*( -8*pow(mZS,2)*tHuH 
              + 4*mZS*(tHS + 3*tH*uH + uHS) 
              + 3*(tHC + 5*tHS*uH + 5*tH*uHS + uHC) );
    double F4 = -2*tHS*uHS*pow(tHuH,3)*(tHS + uHS - mZS*tHuH);

    double G0 = 4*tH*uH*( 6*pow(mZS,3)*(mUS - tH - uH)*tHuH
	      + pow(mZS,2)*( 9*tHC + 7*tHS*uH + 7*tH*uHS + 9*uHC 
              + 15*pow2(mUS)*tHuH - 2*mUS*(12*tHS + 19*tH*uH + 12*uHS) ) 
	      + tH*uH*( 6*pow(mUS,3) - 9*pow(mUS,2)*tHuH - mUS*(tHS 
              + 12*tH*uH + uHS) + 6*(tHC + 6*tHS*uH + 6*tH*uHS + uHC) ) 
	      + mZS*(-3*tHQ + 25*tHC*uH + 58*tHS*uHS + 25*tH*uHC 
              - 3*uHQ + 6*pow(mUS,3)*tHuH 
	      - pow(mUS,2)*(15*tHS + 2*tH*uH + 15*uHS) + 2*mUS*(6*tHC 
              - 11*tHS*uH - 11*tH*uHS + 6*uHC)) );
    double G2 = -4*tHS*uHS*tHuH*( -10*pow2(mZS)*tHuH + 2*mZS*(3*tHS 
              + 7*tH*uH + 3*uHS) + 3*(tHC + 5*tHS*uH + 5*tH*uHS + uHC) ); 
    double G4 = -2*F4;

    double H0 = 24*pow(mZS,3)*tH*uH*pow2(-mUS + tHuH) 
              - 6*pow(mZS,2)*tH*uH*( -9*pow(mUS,3) + 24*pow(mUS,2)*tHuH 
              - mUS*(21*tHS + 38*tH*uH + 21*uHS) 
              + 2*(3*tHC + 5*tHS*uH + 5*tH*uHS + 3*uHC) )
              - mZS*( 3*pow(mUS,4)*(tHS - 12*tH*uH + uHS) 
              - 2*tH*uH*pow2(tHuH)*(6*tHS - 29*tH*uH + 6*uHS) 
	      - 6*pow(mUS,3)*(tHC - 16*tHS*uH - 16*tH*uHS + uHC) 
              + 54*mUS*tH*uH*(tHC + tHS*uH + tH*uHS + uHC) 
	      + pow2(mUS)*(3*tHQ - 102*tHC*uH - 166*tHS*uHS 
              - 102*tH*uHC + 3*uHQ) )
              + tH*uH*( 6*pow(mUS,5) - 18*pow(mUS,4)*tHuH 
              - 12*pow(mUS,2)*pow(tHuH,3) 
              + 3*pow(mUS,3)*(7*tHS + 12*tH*uH + 7*uHS) 
	      - 18*tH*uH*(tHC + 5*tHS*uH + 5*tH*uHS + uHC) 
              + mUS*(3*tHQ + 32*tHC*uH + 78*tHS*uHS + 32*tH*uHC + 3*uHQ) );
    double H2 = 2*tHS*uHS*pow2(tHuH)*( -12*pow2(mZS) + 8*mZS*tHuH 
              + 3*(tHS + 4*tH*uH + uHS) );
    double H4 = F4;

    m_sigma0 = A0*( F0 + 1/mUS*F2 + 1/pow2(mUS)*F4 
	     + m_ratio*(G0 + 1/mUS*G2 + 1/pow2(mUS)*G4) 
	     + pow2(m_ratio)*(H0 + 1/mUS*H2 + 1/pow2(mUS)*H4) );

  } else {
    
    m_sigma0 = 0;
  
  }

}

//--------------------------------------------------------------------------

double Sigma2ffbar2LEDUnparticleZ::sigmaHat() { 

  // Electroweak couplings.
  int idAbs    = abs(id1);
  // Note: 1/2 * (g_L^2 + g_R^2) = (g_v^2 + g_a^2) 
  double facEWS  = 4 * M_PI * alpEM  
                   / (coupSMPtr->sin2thetaW() * coupSMPtr->cos2thetaW()) 
                   * ( 0.25 * 0.25 * coupSMPtr->vf2af2(idAbs) );   

  // Mass Spectrum, (m^2)^(d-2)
  double tmpExp = m_dU - 2;
  double facSpect = pow(mUS, tmpExp);

  // Total cross section
  double sigma = m_constantTerm * facEWS * facSpect * m_sigma0;  
  
  // If f fbar are quarks (1/N_c)
  if (idAbs < 9) sigma /= 3.;

  // Related to mass spactrum weighting.
  sigma /= runBW3;   

  // Truncate sH region or use form factor.
  // Form factor uses either pythia8 renormScale2 
  // or E_jet in cms.
  if (m_cutoff == 1) {
    if (sH > pow2(m_LambdaU) ) { sigma *= pow(m_LambdaU,4)/pow2(sH); }
  } else if (m_graviton && ((m_cutoff == 2) || (m_cutoff == 3))) {
    double tmp_mu = sqrt(Q2RenSave);
    if (m_cutoff == 3) tmp_mu = (sH + s4 - s3) / (2 * mH);
    double tmp_formfact = tmp_mu / (m_tff * m_LambdaU);
    double tmp_exp = double(m_nGrav) + 2;
    sigma *= 1 / (1 + pow(tmp_formfact, tmp_exp));
  }

  return sigma;  

}

//--------------------------------------------------------------------------

void Sigma2ffbar2LEDUnparticleZ::setIdColAcol() {

  // Flavours trivial.
  setId( id1, id2, m_idG, 23);

  // Colour flow topologies. Swap when antiquarks.
  if (abs(id1) < 9) setColAcol( 1, 0, 0, 1, 0, 0);
  else              setColAcol( 0, 0, 0, 0, 0, 0);
  if (id1 < 0) swapColAcol();

}
  
//==========================================================================

// Sigma2ffbar2LEDUnparticlegamma class.
// Cross section for f fbar -> U/G gamma (real LED graviton or unparticle 
// emission).

//--------------------------------------------------------------------------

// Constants: could be changed here if desired, but normally should not.
// These are of technical nature, as described for each.

// FIXRATIO:
// Ratio between the two possible coupling constants of the spin-2 ME. 
// A value different from one give rise to an IR divergence which makes 
// the event generation very slow, so this values is fixed to 1 until
// investigated further.
const double Sigma2ffbar2LEDUnparticlegamma::FIXRATIO = 1.;

//--------------------------------------------------------------------------

void Sigma2ffbar2LEDUnparticlegamma::initProc() {

  // WARNING: Keep in mind that this class uses the photon limit 
  //          of the Z+G/U ME code. This might give rise to some 
  //          confusing things, e.g. mZ = particleDataPtr->m0(22);          
  
  // Init model parameters.
  m_idG        = 5000039;
  if (m_graviton) {
    m_spin     = 2;
    m_nGrav    = settingsPtr->mode("ExtraDimensionsLED:n");
    m_dU       = 0.5 * m_nGrav + 1; 
    m_LambdaU  = settingsPtr->parm("ExtraDimensionsLED:MD");
    m_lambda   = 1;
    m_cutoff   = settingsPtr->mode("ExtraDimensionsLED:CutOffMode"); 
    m_tff      = settingsPtr->parm("ExtraDimensionsLED:t");
  } else {
    m_spin     = settingsPtr->mode("ExtraDimensionsUnpart:spinU");
    m_dU       = settingsPtr->parm("ExtraDimensionsUnpart:dU");
    m_LambdaU  = settingsPtr->parm("ExtraDimensionsUnpart:LambdaU");
    m_lambda   = settingsPtr->parm("ExtraDimensionsUnpart:lambda");
    m_ratio    = FIXRATIO; 
    //         = settingsPtr->parm("ExtraDimensionsUnpart:ratio");
    m_cutoff   = settingsPtr->mode("ExtraDimensionsUnpart:CutOffMode");
  }

  // Store Z0 mass.
  mZ        = particleDataPtr->m0(22);
  mZS       = mZ*mZ;  

  // Init spin-2 parameters
  if ( m_spin != 2 ){
    m_graviton = false;
    m_lambdaPrime = 0;
  } else if (m_graviton) {
    m_lambda = 1;
    m_ratio = 1;
    m_lambdaPrime = m_lambda;
  } else {
    m_lambdaPrime = m_ratio * m_lambda;
  }

  // The A(dU) or S'(n) value
  double tmpAdU = 16 * pow2(M_PI) * sqrt(M_PI) / pow(2. * M_PI, 2. * m_dU)
    * GammaReal(m_dU + 0.5) / (GammaReal(m_dU - 1.) * GammaReal(2. * m_dU));

  if (m_graviton) { 
    tmpAdU  = 2 * M_PI * sqrt( pow(M_PI, double(m_nGrav)) ) 
            / GammaReal(0.5 * m_nGrav); 
  } 

  // Standard 2 to 2 cross section related constants
  double tmpTerm1 = 1/(2 * 16 * pow2(M_PI));
  double tmpLS    = pow2(m_LambdaU);

  // Spin dependent constants from ME.
  double tmpTerm2 = 0;
  if ( m_spin == 0 ) {
    tmpTerm2 = 2 * pow2(m_lambda);
  } else if (m_spin == 1) {
    tmpTerm2 = 4 * pow2(m_lambda);
  } else if (m_spin == 2) {
    tmpTerm2 = pow2(m_lambda)/(4 * 3 * tmpLS);
  } 

  // Unparticle phase space related
  double tmpExp2 = m_dU - 2;
  double tmpTerm3 = tmpAdU / (tmpLS * pow(tmpLS, tmpExp2));

  // All in total
  m_constantTerm = tmpTerm1 * tmpTerm2 * tmpTerm3;

} 

//--------------------------------------------------------------------------

void Sigma2ffbar2LEDUnparticlegamma::sigmaKin() { 

  // Set graviton mass and some powers of mandelstam variables
  mU        = m3;
  mUS       = mU*mU;

  sHS = pow2(sH);
  tHS = pow2(tH);
  uHS = pow2(uH);
  tHC = pow(tH,3);
  uHC = pow(uH,3);
  tHQ = pow(tH,4);
  uHQ = pow(uH,4);
  tHuH = tH+uH;

  // Evaluate (m**2, t, u) part of differential cross section.
  // Extra 1/sHS comes from standard 2 to 2 cross section 
  // phase space factors.

  if ( m_spin == 0 ) {
    
    double A0 = 1/sHS;
    double T1 = - sH/tH - sH/uH;
    double T2 = - (1 - mZS/tH)*(1 - mUS/tH);
    double T3 = - (1 - mZS/uH)*(1 - mUS/uH);
    double T4 = 2*(1 - mUS/tH)*(1 - mUS/uH);
    
    m_sigma0 = A0 * ( T1 + T2 + T3 + T4);
    
  } else if ( m_spin == 1 ) {
    
    double A0 = 1/sHS;
    double T1 = 0.5 * (tH/uH + uH/tH); 
    double T2 =  pow2(mZS + mUS)/(tH * uH); 
    double T3 = - 0.5 * mUS * (mZS/tHS + mZS/uHS) ;
    double T4 = - (mZS+mUS)*(1/tH + 1/uH);
    
    m_sigma0 = A0 * ( T1 + T2 + T3 + T4 );

  } else if ( m_spin == 2 ) {

    double A0 = 1 / ( sHS * uHS * tHS * pow2(sH-mZS) ); 
    double F0 = 2*tHS*uHS*( 16*pow(mZS,3) +  mUS*(7*tHS + 12*tH*uH + 7*uHS) 
              - 3*(3*tHC + 11*tHS*uH + 11*tH*uHS + 3*uHC)
              + 6*pow(mZS,2)*(7*mUS - 2*tHuH) + mZS*(14*pow(mUS,2) 
              - 15*tHS - 44*tH*uH - 15*uHS + 2*mUS*tHuH) );
    double F2 = 2*tHS*uHS*tHuH*( -8*pow(mZS,2)*tHuH 
              + 4*mZS*(tHS + 3*tH*uH + uHS) 
              + 3*(tHC + 5*tHS*uH + 5*tH*uHS + uHC) );
    double F4 = -2*tHS*uHS*pow(tHuH,3)*(tHS + uHS - mZS*tHuH);

    double G0 = 4*tH*uH*( 6*pow(mZS,3)*(mUS - tH - uH)*tHuH
	      + pow(mZS,2)*( 9*tHC + 7*tHS*uH + 7*tH*uHS + 9*uHC 
              + 15*pow2(mUS)*tHuH - 2*mUS*(12*tHS + 19*tH*uH + 12*uHS) ) 
	      + tH*uH*( 6*pow(mUS,3) - 9*pow(mUS,2)*tHuH 
              - mUS*(tHS + 12*tH*uH + uHS) 
              + 6*(tHC + 6*tHS*uH + 6*tH*uHS + uHC) ) 
	      + mZS*(-3*tHQ + 25*tHC*uH + 58*tHS*uHS + 25*tH*uHC 
              - 3*uHQ + 6*pow(mUS,3)*tHuH 
	      - pow(mUS,2)*(15*tHS + 2*tH*uH + 15*uHS) 
              + 2*mUS*(6*tHC - 11*tHS*uH - 11*tH*uHS + 6*uHC)) );
    double G2 = -4*tHS*uHS*tHuH*( -10*pow2(mZS)*tHuH 
              + 2*mZS*(3*tHS + 7*tH*uH + 3*uHS) 
              + 3*(tHC + 5*tHS*uH + 5*tH*uHS + uHC) ); 
    double G4 = -2*F4;

    double H0 = 24*pow(mZS,3)*tH*uH*pow2(-mUS + tHuH) 
              - 6*pow(mZS,2)*tH*uH*( -9*pow(mUS,3) + 24*pow(mUS,2)*tHuH 
              - mUS*(21*tHS + 38*tH*uH + 21*uHS) 
              + 2*(3*tHC + 5*tHS*uH + 5*tH*uHS + 3*uHC) )
              - mZS*( 3*pow(mUS,4)*(tHS - 12*tH*uH + uHS) 
              - 2*tH*uH*pow2(tHuH)*(6*tHS - 29*tH*uH + 6*uHS) 
	      - 6*pow(mUS,3)*(tHC - 16*tHS*uH - 16*tH*uHS + uHC) 
              + 54*mUS*tH*uH*(tHC + tHS*uH + tH*uHS + uHC) 
	      + pow2(mUS)*(3*tHQ - 102*tHC*uH - 166*tHS*uHS 
              - 102*tH*uHC + 3*uHQ) )
              + tH*uH*( 6*pow(mUS,5) - 18*pow(mUS,4)*tHuH 
              - 12*pow(mUS,2)*pow(tHuH,3) 
              + 3*pow(mUS,3)*(7*tHS + 12*tH*uH + 7*uHS) 
	      - 18*tH*uH*(tHC + 5*tHS*uH + 5*tH*uHS + uHC) 
              + mUS*(3*tHQ + 32*tHC*uH + 78*tHS*uHS + 32*tH*uHC + 3*uHQ) );
    double H2 = 2*tHS*uHS*pow2(tHuH)*( -12*pow2(mZS) + 8*mZS*tHuH 
              + 3*(tHS + 4*tH*uH + uHS) );
    double H4 = F4;

    m_sigma0 = A0*( F0 + 1/mUS*F2 + 1/pow2(mUS)*F4 
	     + m_ratio*(G0 + 1/mUS*G2 + 1/pow2(mUS)*G4) 
	     + pow2(m_ratio)*(H0 + 1/mUS*H2 + 1/pow2(mUS)*H4) );

  } else {
    
    m_sigma0 = 0;
  
  }

}

//--------------------------------------------------------------------------

double Sigma2ffbar2LEDUnparticlegamma::sigmaHat() { 

  // Electroweak couplings..
  int idAbs    = abs(id1);
  double facEWS = 4 * M_PI * alpEM * coupSMPtr->ef2(idAbs);

  // Mass Spectrum, (m^2)^(d-2)
  double tmpExp = m_dU - 2;
  double facSpect = pow(mUS, tmpExp);

  // Total cross section
  double sigma = m_constantTerm * facEWS * facSpect * m_sigma0;  

  // If f fbar are quarks
  if (idAbs < 9) sigma /= 3.;

  // Related to mass spactrum weighting.
  sigma /= runBW3;      

  // Truncate sH region or use form factor.
  // Form factor uses either pythia8 renormScale2 
  // or E_jet in cms.
  if (m_cutoff == 1) {
    if (sH > pow2(m_LambdaU) ) { sigma *= pow(m_LambdaU,4)/pow2(sH); }
  } else if (m_graviton && ((m_cutoff == 2) || (m_cutoff == 3))) {
    double tmp_mu = sqrt(Q2RenSave);
    if (m_cutoff == 3) tmp_mu = (sH + s4 - s3) / (2 * mH);
    double tmp_formfact = tmp_mu / (m_tff * m_LambdaU);
    double tmp_exp = double(m_nGrav) + 2;
    sigma *= 1 / (1 + pow(tmp_formfact, tmp_exp));
  }

  return sigma;  

}

//--------------------------------------------------------------------------

void Sigma2ffbar2LEDUnparticlegamma::setIdColAcol() {

  // Flavours trivial.
  setId( id1, id2, m_idG, 22);

  // Colour flow topologies. Swap when antiquarks.
  if (abs(id1) < 9) setColAcol( 1, 0, 0, 1, 0, 0);
  else              setColAcol( 0, 0, 0, 0, 0, 0);
  if (id1 < 0) swapColAcol();

}

//==========================================================================

// Sigma2ffbar2LEDgammagamma class.
// Cross section for f fbar -> (LED G*/U*) -> gamma gamma 
// (virtual graviton/unparticle exchange).

//--------------------------------------------------------------------------

void Sigma2ffbar2LEDgammagamma::initProc() {
  
  // Init model parameters.
  if (m_graviton) {
    m_spin     = 2;
    m_nGrav    = settingsPtr->mode("ExtraDimensionsLED:n");
    m_dU       = 2;
    m_LambdaU  = settingsPtr->parm("ExtraDimensionsLED:LambdaT");
    m_lambda   = 1;
    m_cutoff   = settingsPtr->mode("ExtraDimensionsLED:CutOffMode"); 
    m_tff      = settingsPtr->parm("ExtraDimensionsLED:t");
  } else {
    m_spin     = settingsPtr->mode("ExtraDimensionsUnpart:spinU");
    m_dU       = settingsPtr->parm("ExtraDimensionsUnpart:dU");
    m_LambdaU  = settingsPtr->parm("ExtraDimensionsUnpart:LambdaU");
    m_lambda   = settingsPtr->parm("ExtraDimensionsUnpart:lambda");
  }

  // Model dependent constants.
  if (m_graviton) {
    m_lambda2chi = 4*M_PI;
  } else {
    double tmp_AdU = 16 * pow2(M_PI) * sqrt(M_PI) / pow(2. * M_PI, 2. * m_dU)
      * GammaReal(m_dU + 0.5) / (GammaReal(m_dU - 1.) * GammaReal(2. * m_dU));
    double tmp_dUpi = m_dU * M_PI;
    m_lambda2chi = pow2(m_lambda) * tmp_AdU / (2 * sin(tmp_dUpi));
  }

  // Model parameter check (if not applicable, sigma = 0).
  // Note: SM contribution still generated.
  if ( !(m_spin==0 || m_spin==2) ) {
    m_lambda2chi = 0;
    infoPtr->errorMsg("Error in Sigma2ffbar2LEDgammagamma::initProc: "
		      "Incorrect spin value (turn process off)!");
  } else if ( !m_graviton && (m_dU >= 2)) {
    m_lambda2chi = 0;
    infoPtr->errorMsg("Error in Sigma2ffbar2LEDgammagamma::initProc: "
		      "This process requires dU < 2 (turn process off)!");
  }

} 

//--------------------------------------------------------------------------

void Sigma2ffbar2LEDgammagamma::sigmaKin() { 

  // Mandelstam variables.
  double sHS = pow2(sH);
  double sHQ = pow(sH, 4);
  double tHS = pow2(tH);
  double uHS = pow2(uH);

  // Form factor.
  double tmp_effLambdaU = m_LambdaU;
  if (m_graviton && ((m_cutoff == 2) || (m_cutoff == 3))) {
    double tmp_ffterm = sqrt(Q2RenSave) / (m_tff * m_LambdaU);
    double tmp_exp = double(m_nGrav) + 2;
    double tmp_formfact = 1 + pow(tmp_ffterm, tmp_exp);
    tmp_effLambdaU *= pow(tmp_formfact,0.25);
  }

  // ME from spin-0 and spin-2 unparticles
  // including extra 1/sHS from 2-to-2 phase space.
  if (m_spin == 0) {
    double tmp_sLambda2 = sH / pow2(tmp_effLambdaU);
    double tmp_exp = 2 * m_dU - 1;
    m_term1 = pow(tmp_sLambda2,tmp_exp);
    m_term1 /= sHS;
  } else {
    m_term1 = (uH / tH + tH / uH);
    m_term1 /= sHS;
    double tmp_sLambda2 = sH / pow2(tmp_effLambdaU);
    double tmp_exp = m_dU;
    m_term2 = pow(tmp_sLambda2,tmp_exp) * (uHS + tHS) / sHS;
    m_term2 /= sHS;
    tmp_exp = 2 * m_dU;
    m_term3 = pow(tmp_sLambda2,tmp_exp) * tH * uH * (uHS + tHS) / sHQ;
    m_term3 /= sHS;
  }

}

//--------------------------------------------------------------------------

double Sigma2ffbar2LEDgammagamma::sigmaHat() { 

  // Incoming fermion flavor.
  int idAbs      = abs(id1);

  // Couplings and constants.
  // Note: ME already contain 1/2 for identical 
  //       particles in the final state.
  double sigma = 0;
  if (m_spin == 0) {
    sigma = pow2(m_lambda2chi) * m_term1 / 8;
  } else {
    double tmp_e2Q2 = 4 * M_PI * alpEM * coupSMPtr->ef2(idAbs);
    double tmp_dUpi = m_dU * M_PI;
    sigma = pow2(tmp_e2Q2) * m_term1
          - tmp_e2Q2 * m_lambda2chi * cos(tmp_dUpi) * m_term2
          + pow2(m_lambda2chi) * m_term3 / 4;
  } 

  // dsigma/dt, 2-to-2 phase space factors.
  sigma /= 16 * M_PI;

  // If f fbar are quarks.
  if (idAbs < 9) sigma /= 3.;

  return sigma;  
}

//--------------------------------------------------------------------------

void Sigma2ffbar2LEDgammagamma::setIdColAcol() {

  // Flavours trivial.
  setId( id1, id2, 22, 22);

  // Colour flow topologies. Swap when antiquarks.
  if (abs(id1) < 9) setColAcol( 1, 0, 0, 1, 0, 0, 0, 0);
  else              setColAcol( 0, 0, 0, 0, 0, 0, 0, 0);
  if (id1 < 0) swapColAcol();

}

//==========================================================================

// Sigma2gg2LEDgammagamma class.
// Cross section for g g -> (LED G*/U*) -> gamma gamma 
// (virtual graviton/unparticle exchange).

//--------------------------------------------------------------------------

void Sigma2gg2LEDgammagamma::initProc() {

  // Init model parameters.
  if (m_graviton) {
    m_spin     = 2;
    m_nGrav    = settingsPtr->mode("ExtraDimensionsLED:n");
    m_dU       = 2;
    m_LambdaU  = settingsPtr->parm("ExtraDimensionsLED:LambdaT");
    m_lambda   = 1;
    m_cutoff   = settingsPtr->mode("ExtraDimensionsLED:CutOffMode"); 
    m_tff      = settingsPtr->parm("ExtraDimensionsLED:t");
  } else {
    m_spin     = settingsPtr->mode("ExtraDimensionsUnpart:spinU");
    m_dU       = settingsPtr->parm("ExtraDimensionsUnpart:dU");
    m_LambdaU  = settingsPtr->parm("ExtraDimensionsUnpart:LambdaU");
    m_lambda   = settingsPtr->parm("ExtraDimensionsUnpart:lambda");
  }

  // Model dependent constants.
  if (m_graviton) {
    m_lambda2chi = 4 * M_PI;

  } else {
    double tmp_AdU = 16 * pow2(M_PI) * sqrt(M_PI) / pow(2. * M_PI, 2. * m_dU)
      * GammaReal(m_dU + 0.5) / (GammaReal(m_dU - 1.) * GammaReal(2. * m_dU));
    double tmp_dUpi = m_dU * M_PI;
    m_lambda2chi = pow2(m_lambda) * tmp_AdU / (2 * sin(tmp_dUpi));
  }

  // Model parameter check (if not applicable, sigma = 0).
  if ( !(m_spin==0 || m_spin==2) ) {
    m_lambda2chi = 0;
    infoPtr->errorMsg("Error in Sigma2gg2LEDgammagamma::initProc: "
		      "Incorrect spin value (turn process off)!");
  } else if ( !m_graviton && (m_dU >= 2)) {
    m_lambda2chi = 0;
    infoPtr->errorMsg("Error in Sigma2gg2LEDgammagamma::initProc: "
		      "This process requires dU < 2 (turn process off)!");
  }

} 

//--------------------------------------------------------------------------

void Sigma2gg2LEDgammagamma::sigmaKin() { 
  
  // Mandelstam variables.
  double sHS = pow2(sH);
  double sHQ = pow(sH, 4);
  double tHQ = pow(tH, 4);
  double uHQ = pow(uH, 4);

  // Form factor.
  double tmp_effLambdaU = m_LambdaU;
  if (m_graviton && ((m_cutoff == 2) || (m_cutoff == 3))) {
    double tmp_ffterm = sqrt(Q2RenSave) / (m_tff * m_LambdaU);
    double tmp_exp = double(m_nGrav) + 2;
    double tmp_formfact = 1 + pow(tmp_ffterm, tmp_exp);
    tmp_effLambdaU *= pow(tmp_formfact,0.25);
  }

  // ME from spin-0 and spin-2 unparticles.
  if (m_spin == 0) {
    double tmp_sLambda2 = sH / pow2(tmp_effLambdaU);
    double tmp_exp = 2 * m_dU;
    m_sigma0 = pow(tmp_sLambda2,tmp_exp);
  } else {
    double tmp_sLambda2 = sH / pow2(tmp_effLambdaU);
    double tmp_exp = 2 * m_dU;
    m_sigma0 = pow(tmp_sLambda2,tmp_exp) * (uHQ + tHQ) / sHQ;
  }

  // extra 1/sHS from 2-to-2 phase space.
  m_sigma0 /= sHS;

}

//--------------------------------------------------------------------------

double Sigma2gg2LEDgammagamma::sigmaHat() { 

  // Couplings and constants.
  // Note: ME already contain 1/2 for identical 
  //       particles in the final state.
  double sigma = m_sigma0;
  if (m_spin == 0) {
    sigma *= pow2(m_lambda2chi) / 256;
  } else {
    sigma *= pow2(m_lambda2chi) / 32;
  } 

  // dsigma/dt, 2-to-2 phase space factors.
  sigma /= 16 * M_PI;

  return sigma;  
}

//--------------------------------------------------------------------------

void Sigma2gg2LEDgammagamma::setIdColAcol() {

  // Flavours trivial.
  setId( 21, 21, 22, 22);

  // Colour flow topologies. 
  setColAcol( 1, 2, 2, 1, 0, 0, 0, 0);

}

//==========================================================================

// Sigma2ffbar2LEDllbar class.
// Cross section for f fbar -> (LED G*/U*) -> l lbar
// (virtual graviton/unparticle exchange).
// Does not include t-channel contributions relevant for e^+e^- to e^+e^-

//--------------------------------------------------------------------------

void Sigma2ffbar2LEDllbar::initProc() {
  
  // Init model parameters.
  if (m_graviton) {
    m_spin     = 2;
    m_nGrav    = settingsPtr->mode("ExtraDimensionsLED:n");
    m_dU       = 2;
    m_LambdaU  = settingsPtr->parm("ExtraDimensionsLED:LambdaT");
    m_lambda   = 1;
    m_cutoff   = settingsPtr->mode("ExtraDimensionsLED:CutOffMode"); 
    m_tff      = settingsPtr->parm("ExtraDimensionsLED:t");
  } else {
    m_spin     = settingsPtr->mode("ExtraDimensionsUnpart:spinU");
    m_dU       = settingsPtr->parm("ExtraDimensionsUnpart:dU");
    m_LambdaU  = settingsPtr->parm("ExtraDimensionsUnpart:LambdaU");
    m_lambda   = settingsPtr->parm("ExtraDimensionsUnpart:lambda");
    m_nxx      = settingsPtr->mode("ExtraDimensionsUnpart:gXX");
    m_nxy      = settingsPtr->mode("ExtraDimensionsUnpart:gXY");
  }

  m_mZ  = particleDataPtr->m0(23);
  m_mZS = m_mZ * m_mZ;
  m_GZ  = particleDataPtr->mWidth(23);
  m_GZS = m_GZ * m_GZ;

  // Model dependent constants.
  if (m_graviton) {
    m_lambda2chi = 4*M_PI;
  } else {
    double tmp_AdU = 16 * pow2(M_PI) * sqrt(M_PI) / pow(2. * M_PI, 2. * m_dU)
      * GammaReal(m_dU + 0.5) / (GammaReal(m_dU - 1.) * GammaReal(2. * m_dU));
    double tmp_dUpi = m_dU * M_PI;
    m_lambda2chi = pow2(m_lambda) * tmp_AdU / (2 * sin(tmp_dUpi));
  }

  // Model parameter check (if not applicable, sigma = 0).
  // Note: SM contribution still generated.
  if ( !(m_spin==1 || m_spin==2) ) {
    m_lambda2chi = 0;
    infoPtr->errorMsg("Error in Sigma2ffbar2LEDllbar::initProc: "
		      "Incorrect spin value (turn process off)!");
  } else if ( !m_graviton && (m_dU >= 2)) {
    m_lambda2chi = 0;
    infoPtr->errorMsg("Error in Sigma2ffbar2LEDllbar::initProc: "
		      "This process requires dU < 2 (turn process off)!");
  }

} 

//--------------------------------------------------------------------------

void Sigma2ffbar2LEDllbar::sigmaKin() { 

  // Mandelstam variables.
  double tHS = pow2(tH);
  double uHS = pow2(uH);
  double tHC = pow(tH,3);
  double uHC = pow(uH,3);
  double tHQ = pow(tH,4);
  double uHQ = pow(uH,4);

  // Form factor.
  double tmp_effLambdaU = m_LambdaU;
  if (m_graviton && ((m_cutoff == 2) || (m_cutoff == 3))) {
    double tmp_ffterm = sqrt(Q2RenSave) / (m_tff * m_LambdaU);
    double tmp_exp = double(m_nGrav) + 2;
    double tmp_formfact = 1 + pow(tmp_ffterm, tmp_exp);
    tmp_effLambdaU *= pow(tmp_formfact,0.25);
  }

  // ME from spin-1 and spin-2 unparticles
  m_denomPropZ = pow2(sH - m_mZS) + m_mZS * m_GZS;
  m_rePropZ = (sH - m_mZS) / m_denomPropZ;
  m_imPropZ = -m_mZ * m_GZ / m_denomPropZ;
  m_rePropGamma = 1 / sH;
  if (m_spin == 1) {
    double tmp_sLambda2 = sH / pow2(tmp_effLambdaU);
    double tmp_exp = m_dU - 2;
    m_absMeU  = m_lambda2chi * pow(tmp_sLambda2,tmp_exp) 
              / pow2(tmp_effLambdaU);
  } else {
    double tmp_sLambda2 = sH / pow2(tmp_effLambdaU);
    double tmp_exp = m_dU - 2;
    double tmp_A = -m_lambda2chi * pow(tmp_sLambda2,tmp_exp)
                 / (8 * pow(tmp_effLambdaU,4));
    m_absAS = pow2(tmp_A);
    m_reA   = tmp_A * cos(M_PI * m_dU);
    m_reABW = tmp_A * ((sH - m_mZS) * cos(M_PI * m_dU) + m_mZ * m_GZ 
	    * sin(M_PI * m_dU)) / m_denomPropZ;
    m_poly1 = tHQ + uHQ - 6*tHC*uH - 6*tH*uHC + 18*tHS*uHS;
    double tmp_diffUT = uH - tH;
    m_poly2 = pow(tmp_diffUT,3);
    m_poly3 = tHC - 3*tHS*uH - 3*tH*uHS + uHC;
  }

}

//--------------------------------------------------------------------------

double Sigma2ffbar2LEDllbar::sigmaHat() { 

  // Incoming fermion flavor.
  int idAbs      = abs(id1);

  // Couplings and constants.
  // Qq = coupSMPtr->ef(idAbs), quark, i.e. id > 0.
  // Ql = coupSMPtr->ef(11), electron.
  double tmp_e2QfQl = 4 * M_PI * alpEM * coupSMPtr->ef(idAbs) 
                      * coupSMPtr->ef(11);
  double tmp_gvq = 0.25 * coupSMPtr->vf(idAbs);
  double tmp_gaq = 0.25 * coupSMPtr->af(idAbs);
  double tmp_gLq = tmp_gvq  + tmp_gaq;
  double tmp_gRq = tmp_gvq  - tmp_gaq;
  double tmp_gvl = 0.25 * coupSMPtr->vf(11);
  double tmp_gal = 0.25 * coupSMPtr->af(11);
  double tmp_gLl = tmp_gvl  + tmp_gal;
  double tmp_gRl = tmp_gvl  - tmp_gal;
  double tmp_e2s2c2 = 4 * M_PI * alpEM 
                    / (coupSMPtr->sin2thetaW() * coupSMPtr->cos2thetaW());
     
  // LL, RR, LR, RL  couplings.
  vector<double> tmp_coupZ; 
  tmp_coupZ.push_back(tmp_e2s2c2 * tmp_gLq * tmp_gLl);
  tmp_coupZ.push_back(tmp_e2s2c2 * tmp_gRq * tmp_gRl);
  tmp_coupZ.push_back(tmp_e2s2c2 * tmp_gRq * tmp_gLl);
  tmp_coupZ.push_back(tmp_e2s2c2 * tmp_gLq * tmp_gRl);
  vector<double> tmp_coupU; 
  if (m_nxx == 1) {
    tmp_coupU.push_back(-1); // LL
    tmp_coupU.push_back(-1); // RR
  } else if (m_nxx == 2) {
    tmp_coupU.push_back(0);  // LL
    tmp_coupU.push_back(0);  // RR
  } else {
    tmp_coupU.push_back(1);  // LL
    tmp_coupU.push_back(1);  // RR
  }
  if (m_nxy == 1) {
    tmp_coupU.push_back(-1); // RL
    tmp_coupU.push_back(-1); // LR
  } else if (m_nxy == 2) {
    tmp_coupU.push_back(0);  // RL
    tmp_coupU.push_back(0);  // LR
  } else {
    tmp_coupU.push_back(1);  // RL
    tmp_coupU.push_back(1);  // LR
  }
  
  // Matrix elements
  double tmp_MES = 0;
  if (m_spin == 1) {

    for (unsigned int i = 0; i<tmp_coupZ.size(); ++i) {
      double tmp_MS = pow2(tmp_coupU[i] * m_absMeU) 
	+ pow2(tmp_e2QfQl * m_rePropGamma) 
	+ pow2(tmp_coupZ[i]) / m_denomPropZ
	+ 2 * cos(M_PI * m_dU) * tmp_coupU[i] * m_absMeU 
	    * tmp_e2QfQl * m_rePropGamma
	+ 2 * cos(M_PI * m_dU) * tmp_coupU[i] * m_absMeU 
	    * tmp_coupZ[i] * m_rePropZ 
	+ 2 * tmp_e2QfQl * m_rePropGamma  
	    * tmp_coupZ[i] * m_rePropZ 
	- 2 * sin(M_PI * m_dU) * tmp_coupU[i] * m_absMeU 
	    * tmp_coupZ[i] * m_imPropZ;

      if (i<2) { tmp_MES += 4 * pow2(uH) * tmp_MS; } 
      else if (i<4) { tmp_MES += 4 * pow2(tH) * tmp_MS; }
    }

  } else {
    
    for (unsigned int i = 0; i<tmp_coupZ.size(); ++i) {
      double tmp_MS = pow2(tmp_e2QfQl * m_rePropGamma) 
	+ pow2(tmp_coupZ[i]) / m_denomPropZ
	+ 2 * tmp_e2QfQl * m_rePropGamma  * tmp_coupZ[i] * m_rePropZ;

      if (i<2) { tmp_MES += 4 * pow2(uH) * tmp_MS; }
      else if (i<4) { tmp_MES += 4 * pow2(tH) * tmp_MS; }
    }
    tmp_MES += 8 * m_absAS * m_poly1;
    tmp_MES += 16 * tmp_e2QfQl * m_rePropGamma * m_reA * m_poly2;
    tmp_MES += 16 * tmp_e2s2c2 * m_reABW * (tmp_gaq * tmp_gal * m_poly3 
					  + tmp_gvq * tmp_gvl * m_poly2);
    
  } 

  // dsigma/dt, 2-to-2 phase space factors.
  double sigma = 0.25 * tmp_MES;  // 0.25, is the spin average
  sigma /= 16 * M_PI * pow2(sH); 

  // If f fbar are quarks.
  if (idAbs < 9) sigma /= 3.;

  // sigma(ffbar->llbar) = 3 * sigma(ffbar->eebar) 
  sigma *= 3.;

  return sigma;  
}

//--------------------------------------------------------------------------

void Sigma2ffbar2LEDllbar::setIdColAcol() {

  double tmp_rand = rndmPtr->flat();
  // Flavours trivial.
  if (tmp_rand < 0.33333333) {      setId( id1, id2, 11, -11); } 
  else if (tmp_rand < 0.66666667) { setId( id1, id2, 13, -13); } 
  else {                            setId( id1, id2, 15, -15); }

  // tH defined between f and f': must swap tHat <-> uHat if id1 is fbar.
  swapTU = (id2 > 0);

  // Colour flow topologies. Swap when antiquarks.
  if (abs(id1) < 9) setColAcol( 1, 0, 0, 1, 0, 0, 0, 0);
  else              setColAcol( 0, 0, 0, 0, 0, 0, 0, 0);
  if (id1 < 0) swapColAcol();

}

//==========================================================================

// Sigma2gg2LEDllbar class.
// Cross section for g g -> (LED G*/U*) -> l lbar 
// (virtual graviton/unparticle exchange).

//--------------------------------------------------------------------------

void Sigma2gg2LEDllbar::initProc() {

  // Init model parameters.
  if (m_graviton) {
    m_spin     = 2;
    m_nGrav    = settingsPtr->mode("ExtraDimensionsLED:n");
    m_dU       = 2;
    m_LambdaU  = settingsPtr->parm("ExtraDimensionsLED:LambdaT");
    m_lambda   = 1;
    m_cutoff   = settingsPtr->mode("ExtraDimensionsLED:CutOffMode"); 
    m_tff      = settingsPtr->parm("ExtraDimensionsLED:t");
  } else {
    m_spin     = settingsPtr->mode("ExtraDimensionsUnpart:spinU");
    m_dU       = settingsPtr->parm("ExtraDimensionsUnpart:dU");
    m_LambdaU  = settingsPtr->parm("ExtraDimensionsUnpart:LambdaU");
    m_lambda   = settingsPtr->parm("ExtraDimensionsUnpart:lambda");
  }

  // Model dependent constants.
  if (m_graviton) {
    m_lambda2chi = 4 * M_PI;

  } else {
    double tmp_AdU = 16 * pow2(M_PI) * sqrt(M_PI) / pow(2. * M_PI, 2. * m_dU)
      * GammaReal(m_dU + 0.5) / (GammaReal(m_dU - 1.) * GammaReal(2. * m_dU));
    double tmp_dUpi = m_dU * M_PI;
    m_lambda2chi = pow2(m_lambda) * tmp_AdU / (2 * sin(tmp_dUpi));
  }

  // Model parameter check (if not applicable, sigma = 0).
  if ( !(m_spin==2) ) {
    m_lambda2chi = 0;
    infoPtr->errorMsg("Error in Sigma2gg2LEDllbar::initProc: "
		      "Incorrect spin value (turn process off)!");
  } else if ( !m_graviton && (m_dU >= 2)) {
    m_lambda2chi = 0;
    infoPtr->errorMsg("Error in Sigma2gg2LEDllbar::initProc: "
		      "This process requires dU < 2 (turn process off)!");
  }

} 

//--------------------------------------------------------------------------

void Sigma2gg2LEDllbar::sigmaKin() { 

  // Form factor.
  double tmp_effLambdaU = m_LambdaU;
  if (m_graviton && ((m_cutoff == 2) || (m_cutoff == 3))) {
    double tmp_ffterm = sqrt(Q2RenSave) / (m_tff * m_LambdaU);
    double tmp_exp = double(m_nGrav) + 2;
    double tmp_formfact = 1 + pow(tmp_ffterm, tmp_exp);
    tmp_effLambdaU *= pow(tmp_formfact,0.25);
  }

  // ME from spin-2 unparticle.
  double tmp_sLambda2 = sH / pow2(tmp_effLambdaU);
  double tmp_exp = m_dU - 2;
  double tmp_A = -m_lambda2chi * pow(tmp_sLambda2,tmp_exp)
               / (8 * pow(tmp_effLambdaU,4));
  m_sigma0 = 4 * pow2(tmp_A) * uH * tH * (pow2(uH) + pow2(tH));

  // extra 1/sHS from 2-to-2 phase space.
  m_sigma0 /= 16 * M_PI * pow2(sH);

  // sigma(ffbar->llbar) = 3 * sigma(ffbar->eebar) 
  m_sigma0 *= 3.;

}

//--------------------------------------------------------------------------

void Sigma2gg2LEDllbar::setIdColAcol() {

  double tmp_rand = rndmPtr->flat();
  // Flavours trivial.
  if (tmp_rand < 0.33333333) {      setId( 21, 21, 11, -11); } 
  else if (tmp_rand < 0.66666667) { setId( 21, 21, 13, -13); } 
  else {                            setId( 21, 21, 15, -15); }

  // Colour flow topologies. 
  setColAcol( 1, 2, 2, 1, 0, 0, 0, 0);

}

//==========================================================================

} // end namespace Pythia8
