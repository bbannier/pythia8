// SigmaExtraDim.h is a part of the PYTHIA event generator.
// Copyright (C) 2010 Torbjorn Sjostrand.
// Copyright (C) 2010 Stefan Ask for the *LED* routines.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.
 
// Header file for extra-dimensional-process differential cross sections.
// Contains classes derived from SigmaProcess via Sigma(1/2)Process.
 
#ifndef Pythia8_SigmaExtraDim_H
#define Pythia8_SigmaExtraDim_H
 
#include "SigmaProcess.h"
 
namespace Pythia8 {
 
//==========================================================================
 
// A derived class for g g -> G^* (excited graviton state).
 
class Sigma1gg2GravitonStar : public Sigma1Process {
 
public:
 
  // Constructor.
  Sigma1gg2GravitonStar() {}
 
  // Initialize process.
  virtual void initProc();
 
  // Calculate flavour-independent parts of cross section.
  virtual void sigmaKin();
 
  // Evaluate sigmaHat(sHat).
  virtual double sigmaHat() {return sigma;}
 
  // Select flavour, colour and anticolour.
  virtual void setIdColAcol();
 
  // Evaluate weight for G* decay angle.
  virtual double weightDecay( Event& process, int iResBeg, int iResEnd);
 
  // Info on the subprocess.
  virtual string name()       const {return "g g -> G*";}
  virtual int    code()       const {return 5001;}
  virtual string inFlux()     const {return "gg";}
  virtual int    resonanceA() const {return idGstar;}
 
private:
 
  // Parameters set at initialization or for current kinematics.
  bool   m_smbulk;
  int    idGstar;
  double mRes, GammaRes, m2Res, GamMRat, kappaMG, sigma;
 
  // Couplings between graviton and SM (indexed by particle id).
  double m_coupling[26];
 
  // Pointer to properties of the particle species, to access decay channels.
  ParticleDataEntry* gStarPtr;
 
};
 
//==========================================================================
 
// A derived class for f fbar -> G^* (excited graviton state).
 
class Sigma1ffbar2GravitonStar : public Sigma1Process {
 
public:
 
  // Constructor.
  Sigma1ffbar2GravitonStar() {}
 
  // Initialize process.
  virtual void initProc();
 
  // Calculate flavour-independent parts of cross section.
  virtual void sigmaKin();
 
  // Evaluate sigmaHat(sHat).
  virtual double sigmaHat();
 
  // Select flavour, colour and anticolour.
  virtual void setIdColAcol();
 
  // Evaluate weight for G* decay angle.
  virtual double weightDecay( Event& process, int iResBeg, int iResEnd);
 
  // Info on the subprocess.
  virtual string name()       const {return "f fbar -> G*";}
  virtual int    code()       const {return 5002;}
  virtual string inFlux()     const {return "ffbarSame";}
  virtual int    resonanceA() const {return idGstar;}
 
private:
 
  // Parameters set at initialization or for current kinematics.
  bool   m_smbulk;
  int    idGstar;
  double mRes, GammaRes, m2Res, GamMRat, kappaMG, sigma0;
 
  // Couplings between graviton and SM (indexed by particle id).
  double m_coupling[26];
 
  // Pointer to properties of the particle species, to access decay channels.
  ParticleDataEntry* gStarPtr;
 
};
 
//==========================================================================
 
// A derived class for q qbar -> KK-gluon^* (excited kk-gluon state).
 
class Sigma1qqbar2KKgluonStar : public Sigma1Process {
 
public:
 
  // Constructor.
  Sigma1qqbar2KKgluonStar() {}
 
  // Initialize process.
  virtual void initProc();
 
  // Calculate flavour-independent parts of cross section.
  virtual void sigmaKin();
 
  // Evaluate sigmaHat(sHat).
  virtual double sigmaHat();
 
  // Select flavour, colour and anticolour.
  virtual void setIdColAcol();
 
  // Evaluate weight for g* decay angle.
  virtual double weightDecay( Event& process, int iResBeg, int iResEnd);
 
  // Info on the subprocess.
  virtual string name()       const {return "q qbar -> KK-gluon*";}
  virtual int    code()       const {return 5006;}
  virtual string inFlux()     const {return "qqbarSame";}
  virtual int    resonanceA() const {return idKKgluon;}
 
private:
 
  // Parameters set at initialization or for current kinematics.
  int    idKKgluon;
  double mRes, GammaRes, m2Res, GamMRat, sigma0;
 
  // Couplings between graviton and SM (indexed by particle id).
  double m_coupling[10];
 
  // Pointer to properties of the particle species, to access decay
  // channels.
  ParticleDataEntry* gStarPtr;
 
};
 
//==========================================================================
 
// A derived class for g g -> G^* g (excited graviton state).
 
class Sigma2gg2GravitonStarg : public Sigma2Process {
 
public:
 
  // Constructor.
  Sigma2gg2GravitonStarg() {}
 
  // Initialize process.
  virtual void initProc();
 
  // Calculate flavour-independent parts of cross section.
  virtual void sigmaKin();
 
  // Evaluate sigmaHat(sHat).
  virtual double sigmaHat() {return sigma;}
 
  // Select flavour, colour and anticolour.
  virtual void setIdColAcol();
 
  // Evaluate weight: currently isotropic (except secondary top decay)..
  virtual double weightDecay( Event& process, int iResBeg, int iResEnd);
 
  // Info on the subprocess.
  virtual string name()    const {return "g g -> G* g";}
  virtual int    code()    const {return 5003;}
  virtual string inFlux()  const {return "gg";}
  virtual int    id3Mass() const {return idGstar;}
 
private:
 
  // Parameters set at initialization or for current kinematics.
  int    idGstar;
  double mRes, GammaRes, m2Res, GamMRat, kappaMG, openFrac, sigma;
 
};
 
//==========================================================================
 
// A derived class for q g -> G^* q (excited graviton state).
 
class Sigma2qg2GravitonStarq : public Sigma2Process {
 
public:
 
  // Constructor.
  Sigma2qg2GravitonStarq() {}
 
  // Initialize process.
  virtual void initProc();
 
  // Calculate flavour-independent parts of cross section.
  virtual void sigmaKin();
 
  // Evaluate sigmaHat(sHat).
  virtual double sigmaHat() {return sigma;}
 
  // Select flavour, colour and anticolour.
  virtual void setIdColAcol();
 
  // Evaluate weight: currently isotropic (except secondary top decay).
  virtual double weightDecay( Event& process, int iResBeg, int iResEnd);
 
  // Info on the subprocess.
  virtual string name()    const {return "q g -> G* q";}
  virtual int    code()    const {return 5004;}
  virtual string inFlux()  const {return "qg";}
  virtual int    id3Mass() const {return idGstar;}
 
private:
 
  // Parameters set at initialization or for current kinematics.
  int    idGstar;
  double mRes, GammaRes, m2Res, GamMRat, kappaMG, openFrac, sigma;
 
};
 
//==========================================================================
 
// A derived class for q qbar -> G^* g (excited graviton state).
 
class Sigma2qqbar2GravitonStarg : public Sigma2Process {
 
public:
 
  // Constructor.
  Sigma2qqbar2GravitonStarg() {}
 
  // Initialize process.
  virtual void initProc();
 
  // Calculate flavour-independent parts of cross section.
  virtual void sigmaKin();
 
  // Evaluate sigmaHat(sHat).
  virtual double sigmaHat() {return sigma;}
 
  // Select flavour, colour and anticolour.
  virtual void setIdColAcol();
 
  // Evaluate weight: currently isotropic (except secondary top decay).
  virtual double weightDecay( Event& process, int iResBeg, int iResEnd);
 
  // Info on the subprocess.
  virtual string name()    const {return "q qbar -> G* g";}
  virtual int    code()    const {return 5005;}
  virtual string inFlux()  const {return "qqbarSame";}
  virtual int    id3Mass() const {return idGstar;}
 
private:
 
  // Parameters set at initialization or for current kinematics.
  int    idGstar;
  double mRes, GammaRes, m2Res, GamMRat, kappaMG, openFrac, sigma;
 
};
 
//==========================================================================
 
// NOAM: A derived class for, f fbar -> (gamma/Z)_KKTower -> F Fbar,
// for one heavy F.
// Process provided by N. Hod et al. and is described in arXiv:XXXX.YYYY
 
class Sigma2ffbar2TEVffbar : public Sigma2Process {
 
public:
 
    // Constructor.
  Sigma2ffbar2TEVffbar(int idIn) : idNew(idIn) {}
 
  // Initialize process.
  virtual void initProc();
 
  // Calculate flavour-independent parts of cross section.
  virtual void sigmaKin();
 
  // Evaluate sigmaHat(sHat).
  virtual double sigmaHat();
 
  // Select flavour, colour and anticolour.
  virtual void setIdColAcol();
 
  // Evaluate weight for W decay angles in top decay (else inactive).
  virtual double weightDecay( Event& process, int iResBeg, int iResEnd);
 
  // Info on the subprocess.
  virtual string name()       const {return nameSave;}
  virtual int    code()       const {return 5011;}
  virtual string inFlux()     const {return "ffbarSame";}
  virtual bool   isSChannel() const {return true;}
  virtual int    idSChannel() const {return 5000023;}
  virtual int    resonanceA() const {return 23;}
  virtual int    resonanceB() const {return 5000023;}
  virtual int    id3Mass()    const {return idNew;}
  virtual int    id4Mass()    const {return idNew;}
  // Add phase-space sampling also around the Z_KK resonance.
  virtual int    resonanceA();
  virtual int    resonanceB();
 
private:
 
  // Values stored for process type.
  string  nameSave;
  int     idNew, gmZmode, n_excitation_max;
  bool    isPhysical;
  double  gPlusf, gMinusf, gPlusF, gMinusF, gPlusTop, gMinusTop,
          gPlus, gMinus, gf, gF;
  double  mRes, m2Res, mStar, mTop, m2Top, mZKKn, m2ZKKn, m2gmKKn, mgmKKn,
          alphaem_fixed;
  double  helicityME2, coefTot, coefAngular;
  double  mr, betaf, cosThe, openFracPair;
  double  wgmKKFactor, wgmKKn, wZKKn,
          wZ0, ttbar_wZKKn, ttbar_wgmKKn,
          ttbar_wFactorA, ttbar_wFactorB;
  double  phaseSpace_mHatMin, phaseSpace_mHatMax;
  complex gammaProp, resProp, gmPropKK, ZPropKK, totalProp;
  complex M_I;
};
 
//==========================================================================
 
// A derived class for g g -> U/G g (real graviton emission in
// large extra dimensions or unparticle emission).
 
class Sigma2gg2LEDUnparticleg : public Sigma2Process {
 
public:
 
  // Constructor: bool Graviton  = true, to use LED graviton settings.
  Sigma2gg2LEDUnparticleg( bool Graviton ) : m_graviton(Graviton) {}
 
  // Initialize process.
  virtual void initProc();
 
  // Calculate flavour-independent parts of cross section;
  // first step when inflavours unknown.
  virtual void sigmaKin();
 
  // Evaluate sigmaHat(sHat); second step for given inflavours.
  virtual double sigmaHat();
 
  // Select flavour, colour and anticolour.
  virtual void setIdColAcol();
 
  // Info on the subprocess.
  virtual string name()       const {return
    (m_graviton ? "g g -> G g" : "g g -> U g") ;}
  virtual int    code()       const {return (m_graviton ? 5021 : 5045);}
  virtual string inFlux()     const {return "gg";}
  virtual int    id3Mass()    const {return 5000039;}
  virtual int    id4Mass()    const {return 21;}
 
private:
 
  bool   m_graviton;
  int    m_spin, m_nGrav, m_idG, m_cutoff;
  double mG, mGS, m_sigma0, m_dU, m_LambdaU, m_lambda, m_constantTerm,
         m_tff, m_cf;
 
};
 
//==========================================================================
 
// A derived class for q g -> U/G q (real graviton emission in
// large extra dimensions or unparticle emission).
 
class Sigma2qg2LEDUnparticleq : public Sigma2Process {
 
public:
 
  // Constructor: bool Graviton  = true, to use LED graviton settings.
  Sigma2qg2LEDUnparticleq( bool Graviton) : m_graviton(Graviton) {}
 
  // Initialize process.
  virtual void initProc();
 
  // Calculate flavour-independent parts of cross section;
  // first step when inflavours unknown.
  virtual void sigmaKin();
 
  // Evaluate sigmaHat(sHat); second step for given inflavours.
  virtual double sigmaHat();
 
  // Select flavour, colour and anticolour.
  virtual void setIdColAcol();
 
  // Info on the subprocess.
  virtual string name()       const {return
    (m_graviton ? "q g -> G q" : "q g -> U q") ;}
  virtual int    code()       const {return (m_graviton ? 5022 : 5046);}
  virtual string inFlux()     const {return "qg";}
  virtual int    id3Mass()    const {return 5000039;}
 
private:
 
  bool   m_graviton;
  int    m_spin, m_nGrav, m_idG, m_cutoff;
  double mG, mGS, m_sigma0, m_dU, m_LambdaU, m_lambda, m_constantTerm,
         m_tff, m_gf, m_cf;
 
};
 
//==========================================================================
 
// A derived class for q qbar -> U/G g (real graviton emission in
// large extra dimensions or unparticle emission).
 
class Sigma2qqbar2LEDUnparticleg : public Sigma2Process {
 
public:
 
  // Constructor: bool Graviton  = true, to use LED graviton settings.
  Sigma2qqbar2LEDUnparticleg( bool Graviton) : m_graviton(Graviton) {}
 
  // Initialize process.
  virtual void initProc();
 
  // Calculate flavour-independent parts of cross section;
  // first step when inflavours unknown.
  virtual void sigmaKin();
 
  // Evaluate sigmaHat(sHat); second step for given inflavours.
  virtual double sigmaHat();
 
  // Select flavour, colour and anticolour.
  virtual void setIdColAcol();
 
  // Info on the subprocess.
  virtual string name()       const {return
    (m_graviton ? "q qbar -> G g" : "q qbar -> U g") ;}
  virtual int    code()       const {return (m_graviton ? 5023 : 5047);}
  virtual string inFlux()     const {return "qqbarSame";}
  virtual int    id3Mass()    const {return 5000039;}
  virtual int    id4Mass()    const {return 21;}
 
private:
 
  bool   m_graviton;
  int    m_spin, m_nGrav, m_idG, m_cutoff;
  double mG, mGS, m_sigma0, m_dU, m_LambdaU, m_lambda, m_constantTerm,
         m_tff, m_gf, m_cf;
 
};
 
//==========================================================================
 
// A derived class for f fbar -> U/G Z (real graviton emission in
// large extra dimensions or unparticle emission).
 
class Sigma2ffbar2LEDUnparticleZ : public Sigma2Process {
 
public:
 
  // Constructor: bool Graviton  = true, to use LED graviton settings.
  Sigma2ffbar2LEDUnparticleZ( bool Graviton) : m_graviton(Graviton) {}
 
  // Initialize process.
  virtual void initProc();
 
  // Calculate flavour-independent parts of cross section;
  // first step when inflavours unknown.
  virtual void sigmaKin();
 
  // Evaluate sigmaHat(sHat); second step for given inflavours.
  virtual double sigmaHat();
 
  // Select flavour, colour and anticolour.
  virtual void setIdColAcol();
 
  // Info on the subprocess.
  virtual string name()       const {return
    (m_graviton ? "f fbar -> G Z" : "f fbar -> U Z") ;}
  virtual int    code()       const {return (m_graviton ? 5024 : 5041);}
  virtual string inFlux()     const {return "ffbarSame";}
  virtual int    id3Mass()    const {return 5000039;}
  virtual int    id4Mass()    const {return 23;}
  virtual int    resonanceA() const {return 23;}
  virtual int    gmZmode()    const {return 2;}
 
private:
 
  // Constants: could only be changed in the code itself.
  static const double FIXRATIO;
 
  int    m_spin, m_nGrav, m_cutoff, m_idG;
  bool   m_graviton;
  double m_dU, m_LambdaU, m_lambda, m_ratio, m_lambdaPrime,
         m_tff, m_constantTerm;
  double sHS, tHS, uHS, tHC, uHC, tHQ, uHQ, tHuH, mU, mUS, mZ, widZ,
         mZS, mwZS, thetaWRat, m_sigma0;
 
};
 
//==========================================================================
 
// A derived class for f fbar -> U/G gamma (real graviton emission in
// large extra dimensions or unparticle emission).
 
class Sigma2ffbar2LEDUnparticlegamma : public Sigma2Process {
 
public:
 
  // Constructor: bool Graviton  = true, to use LED graviton settings.
  Sigma2ffbar2LEDUnparticlegamma( bool Graviton) : m_graviton(Graviton) {}
 
  // Initialize process.
  virtual void initProc();
 
  // Calculate flavour-independent parts of cross section;
  // first step when inflavours unknown.
  virtual void sigmaKin();
 
  // Evaluate sigmaHat(sHat); second step for given inflavours.
  virtual double sigmaHat();
 
  // Select flavour, colour and anticolour.
  virtual void setIdColAcol();
 
  // Info on the subprocess.
  virtual string name()       const {return
    (m_graviton ? "f fbar -> G gamma" : "f fbar -> U gamma") ;}
  virtual int    code()       const {return (m_graviton ? 5025 : 5042);}
  virtual string inFlux()     const {return "ffbarSame";}
  virtual int    id3Mass()    const {return 5000039;}
  virtual int    id4Mass()    const {return 22;}
 
private:
 
  // Constants: could only be changed in the code itself.
  static const double FIXRATIO;
 
  int    m_spin, m_nGrav, m_cutoff, m_idG;
  bool   m_graviton;
  double m_dU, m_LambdaU, m_lambda, m_ratio, m_lambdaPrime,
         m_tff, m_constantTerm;
  double sHS, tHS, uHS, tHC, uHC, tHQ, uHQ, tHuH, mU, mUS, mZ, widZ,
         mZS, mwZS, thetaWRat, m_sigma0;
 
};
 
//==========================================================================
 
// A derived class for f fbar -> (LED G*/U*) -> gamma gamma
// (virtual graviton/unparticle exchange).
 
class Sigma2ffbar2LEDgammagamma : public Sigma2Process {
 
public:
 
  // Constructor: bool Graviton  = true, to use LED graviton settings.
  Sigma2ffbar2LEDgammagamma( bool Graviton) : m_graviton(Graviton) {}
 
  // Initialize process.
  virtual void initProc();
 
  // Calculate flavour-independent parts of cross section;
  // first step when inflavours unknown.
  virtual void sigmaKin();
 
  // Evaluate sigmaHat(sHat); second step for given inflavours.
  virtual double sigmaHat();
 
  // Select flavour, colour and anticolour.
  virtual void setIdColAcol();
 
  // Info on the subprocess.
  virtual string name()       const {return
    (m_graviton ? "f fbar -> (LED G*) -> gamma gamma"
    : "f fbar -> (U*) -> gamma gamma") ;}
  virtual int    code()       const {return (m_graviton ? 5026 : 5043);}
  virtual string inFlux()     const {return "ffbarSame";}
 
private:
 
  int    m_spin, m_cutoff, m_nGrav;
  bool   m_graviton;
  double m_dU, m_LambdaU, m_lambda, m_lambda2chi,
         m_term1, m_term2, m_term3, m_tff;
 
};
 
//==========================================================================
 
// A derived class for g g -> (LED G*/U*) -> gamma gamma
// (virtual graviton/unparticle exchange).
 
class Sigma2gg2LEDgammagamma : public Sigma2Process {
 
public:
 
  // Constructor: bool Graviton  = true, to use LED graviton settings.
  Sigma2gg2LEDgammagamma( bool Graviton) : m_graviton(Graviton) {}
 
  // Initialize process.
  virtual void initProc();
 
  // Calculate flavour-independent parts of cross section;
  // first step when inflavours unknown.
  virtual void sigmaKin();
 
  // Evaluate sigmaHat(sHat); second step for given inflavours.
  virtual double sigmaHat();
 
  // Select flavour, colour and anticolour.
  virtual void setIdColAcol();
 
  // Info on the subprocess.
  virtual string name()       const {return (m_graviton
    ? "g g -> (LED G*) -> gamma gamma" : "g g -> (U*) -> gamma gamma") ;}
  virtual int    code()       const {return (m_graviton ? 5027 : 5044);}
  virtual string inFlux()     const {return "gg";}
 
private:
 
  int    m_spin, m_cutoff, m_nGrav;
  bool   m_graviton;
  double m_dU, m_LambdaU, m_lambda, m_lambda2chi, m_sigma0, m_tff;
 
};
 
//==========================================================================
 
// A derived class for f fbar -> (LED G*/U*) -> l lbar
// (virtual graviton/unparticle exchange).
// Does not include t-channel contributions relevant for e^+e^- to e^+e^-
 
class Sigma2ffbar2LEDllbar : public Sigma2Process {
 
public:
 
  // Constructor: bool Graviton  = true, to use LED graviton settings.
  Sigma2ffbar2LEDllbar( bool Graviton) : m_graviton(Graviton) {}
 
  // Initialize process.
  virtual void initProc();
 
  // Calculate flavour-independent parts of cross section;
  // first step when inflavours unknown.
  virtual void sigmaKin();
 
  // Evaluate sigmaHat(sHat); second step for given inflavours.
  virtual double sigmaHat();
 
  // Select flavour, colour and anticolour.
  virtual void setIdColAcol();
 
  // Info on the subprocess.
  virtual string name()       const {return
    (m_graviton ? "f fbar -> (LED G*) -> l l" : "f fbar -> (U*) -> l l") ;}
  virtual int    code()       const {return (m_graviton ? 5028 : 5048);}
  virtual string inFlux()     const {return "ffbarSame";}
  virtual bool   isSChannel() const {return true;}
 
private:
 
  int    m_spin, m_cutoff, m_nGrav,m_nxx, m_nxy;
  bool   m_graviton;
  double m_dU, m_LambdaU, m_lambda, m_lambda2chi, m_tff,
         m_mZ, m_mZS, m_GZ, m_GZS, m_absMeU, m_denomPropZ, m_rePropGamma,
         m_rePropZ, m_imPropZ, m_absAS, m_reA, m_reABW, m_poly1, m_poly2,
         m_poly3;
 
};
 
//==========================================================================
 
// A derived class for g g -> (LED G*/U*) -> l lbar
// (virtual graviton/unparticle exchange).
 
class Sigma2gg2LEDllbar : public Sigma2Process {
 
public:
 
  // Constructor: bool Graviton  = true, to use LED graviton settings.
  Sigma2gg2LEDllbar( bool Graviton) : m_graviton(Graviton) {}
 
 
  // Initialize process.
  virtual void initProc();
 
  // Calculate flavour-independent parts of cross section;
  // first step when inflavours unknown.
  virtual void sigmaKin();
 
  // Evaluate sigmaHat(sHat); second step for given inflavours.
  virtual double sigmaHat() {return m_sigma0;}
 
  // Select flavour, colour and anticolour.
  virtual void setIdColAcol();
 
  // Info on the subprocess.
  virtual string name()       const {return
    (m_graviton ? "g g -> (LED G*) -> l l" : "g g -> (U*) -> l l") ;}
  virtual int    code()       const {return (m_graviton ? 5029 : 5049);}
  virtual string inFlux()     const {return "gg";}
 
private:
 
  int    m_spin, m_cutoff, m_nGrav;
  bool   m_graviton;
  double m_dU, m_LambdaU, m_lambda, m_lambda2chi, m_sigma0, m_tff;
 
};
 
//==========================================================================
 
} // end namespace Pythia8
 
#endif // Pythia8_SigmaExtraDim_H
