// SusyCouplings.h is a part of the PYTHIA event generator.
// Copyright (C) 2010 Peter Skands, Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// Header file for setup of common SUSY couplings.

#ifndef Pythia8_SusyCouplings_H
#define Pythia8_SusyCouplings_H

#include "PythiaComplex.h"
#include "Settings.h"
#include "StandardModel.h"
#include "SusyLesHouches.h"

namespace Pythia8 {
 
//==========================================================================

// CoupSUSY
// Auxiliary class to compute and store various SM and SUSY couplings.

class CoupSUSY {

public:

  // Constructor
  CoupSUSY() {isInit=false; isNMSSM = false;}

  // Initialize
  void init(SusyLesHouches* slhaPtrIn, Settings* settingsPtrIn, 
    ParticleData* particleDataPtrIn, CoupSM* coupSMPtrIn);

  // Status flag. Flag for NMSSM.
  bool isInit, isNMSSM;

  // Z and W pole masses and widths
  double mWpole, wWpole, mZpole, wZpole;

  // Running masses and weak mixing angle 
  // (default to pole values if no running available)
  double mW, mZ, sin2W, sinW, cosW;

  // Tanbeta
  double tanb, cosb, sinb;

  // ~qq~g couplings
  complex LsddG[7][4], RsddG[7][4];
  complex LsuuG[7][4], RsuuG[7][4];
  // Assume generation index for Squark. Translate if PDG code instead.
  complex getLsqqG(int iGenSq, int idQ) {if (abs(iGenSq) > 1000000) 
      iGenSq =  3*(abs(iGenSq)/2000000) + (abs(iGenSq)%10+1)/2;
    return (abs(idQ)%2 == 0) ? LsuuG[iGenSq][abs(idQ)/2]
      : LsddG[iGenSq][(abs(idQ)+1)/2] ;}
  complex getRsqqG(int iGenSq, int idQ) {if (abs(iGenSq) > 1000000) 
      iGenSq =  3*(abs(iGenSq)/2000000) + (abs(iGenSq)%10+1)/2;
    return (abs(idQ)%2 == 0) ? RsuuG[iGenSq][abs(idQ)/2]
      : RsddG[iGenSq][(abs(idQ)+1)/2] ;}

  // ~chi0~chi0Z couplings
  complex OLpp[6][6], ORpp[6][6];

  // ~chi+~chi-Z couplings
  complex OLp[3][3], ORp[3][3];

  // ~chi0~chi+W couplings
  complex OL[6][3], OR[6][3];

  // qqZ couplings 
  double LqqZ[7], RqqZ[7]; 

  // ~q~qZ couplings 
  complex LsdsdZ[7][7], RsdsdZ[7][7]; 
  complex LsusuZ[7][7], RsusuZ[7][7]; 
  complex getLsqsqZ(int idSq1, int idSq2) {    
    if (abs(idSq1)%2 != abs(idSq2)%2) return complex(0.0,0.0);
    int iGen1 = 3*(abs(idSq1)/2000000) + (abs(idSq1)%10+1)/2;
    int iGen2 = 3*(abs(idSq2)/2000000) + (abs(idSq2)%10+1)/2;
    return (abs(idSq1)%2 == 0) ? LsusuZ[iGen1][iGen2] : LsdsdZ[iGen1][iGen2];}
  complex getRsqsqZ(int idSq1, int idSq2) {    
    if (abs(idSq1)%2 != abs(idSq2)%2) return complex(0.0,0.0);
    int iGen1 = 3*(abs(idSq1)/2000000) + (abs(idSq1)%10+1)/2;
    int iGen2 = 3*(abs(idSq2)/2000000) + (abs(idSq2)%10+1)/2;
    return (abs(idSq1)%2 == 0) ? RsusuZ[iGen1][iGen2] : RsdsdZ[iGen1][iGen2];}

  // udW couplings
  complex LudW[4][4], RudW[4][4];

  // ~u~dW couplings
  complex LsusdW[7][7], RsusdW[7][7];

  // ~qq~chi0 couplings
  complex LsddX[7][4][6], RsddX[7][4][6];
  complex LsuuX[7][4][6], RsuuX[7][4][6];
  complex getLsqqX(int iSq, int idQ, int iNeut) {return (abs(idQ)%2 == 0) 
    ? LsuuX[iSq][abs(idQ)/2][iNeut] : LsddX[iSq][(abs(idQ)+1)/2][iNeut] ;}
  complex getRsqqX(int iSq, int idQ, int iNeut) {return (abs(idQ)%2 == 0) 
    ? RsuuX[iSq][abs(idQ)/2][iNeut] : RsddX[iSq][(abs(idQ)+1)/2][iNeut] ;}
 
  // ~du~chi+ couplings
  complex LsduX[7][4][3], RsduX[7][4][3];

  // ~ud~chi+ couplings
  complex LsudX[7][4][3], RsudX[7][4][3];

  // Return neutralino, chargino, sup, sdown and slepton flavour codes.
  int idNeut(int idChi);
  int idChar(int idChi); 
  int idSup(int iSup);
  int idSdown(int iSdown);
  int idSlep(int iSlep); 

  // Return a particle name, given the PDG code.
  string getName(int pdgCode);    

private:

  // Debug flag
  static const bool   DEBUG;

  // Pointer to SLHA instance
  SusyLesHouches* slhaPtr;

  // Pointer to the settings database.
  Settings*      settingsPtr;

  // Pointer to the particle data table.
  ParticleData*  particleDataPtr;

  // Pointer to the Standard Models couplings. 
  CoupSM*        coupSMPtr;

};

//==========================================================================

} // end namespace Pythia8

#endif // Pythia8_SusyCouplings_H
