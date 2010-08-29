// main61.cc is a part of the PYTHIA event generator.
// Copyright (C) 2010 Richard Corke.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

/*
 * Simple example of fastjet analysis. Roughly follows analysis of:
 * T. Aaltonen et al. [CDF Collaboration],
 * Measurement of the cross section for W-boson production in association
 * with jets in ppbar collisions at sqrt(s)=1.96$ TeV
 * Phys. Rev. D 77 (2008) 011108
 * arXiv:0711.4044 [hep-ex]
 *
 * Cuts:
 *   ET(elec)     > 20GeV
 *   |eta(elec)|  < 1.1
 *   ET(missing)  > 30GeV
 *   ET(jet)      > 20GeV
 *   |eta(jet)|   < 2.0
 *   deltaR(elec, jet) > 0.52
 * Not used:
 *   mT(W)        > 20GeV
 */

#include "Pythia.h"

#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"

using namespace Pythia8;

// Experimental cross section
// sigma(W -> ev + >= n-jet; ET(n'th-jet) > 25GeV), n = 0, 1, 2, 3, 4
const double expCrossSec[] = { 798.0, 53.5, 6.8, 0.84, 0.074 };

int main() {
  // Settings
  int  nEvent = 10000;
  bool doMI   = true;
    
  // Generator
  Pythia pythia;

  // Single W production
  pythia.readString("WeakSingleBoson:ffbar2W = on");
  // Force decay W->ev
  pythia.readString("24:onMode = off");
  pythia.readString("24:onIfAny = 11 12");
  // Multiple Interactions
  if (doMI == false)
    pythia.readString("PartonLevel:MI = off");

  // Initialisation, p pbar @ 1.96 TeV
  pythia.init( 2212, -2212, 1960.);

  // Histograms
  Hist dSigma1("1-jet cross-section (E_jet1 > 20 GeV)", 70, 0.0, 350.0);
  Hist dSigma2("2-jet cross-section (E_jet2 > 20 GeV)", 38, 0.0, 190.0);
  Hist dSigma3("3-jet cross-section (E_jet3 > 20 GeV)", 16, 0.0, 80.0);
  Hist dSigma4("4-jet cross-section (E_jet4 > 20 GeV)",  7, 0.0, 35.0);
  Hist *dSigmaHist[5] = { NULL, &dSigma1, &dSigma2, &dSigma3, &dSigma4 };
  double dSigmaBin[5] = { 0.0, 350.0 / 70.0, 190.0 / 38.0,
                          80.0 / 16.0, 35.0 / 7.0 };

  // Fastjet analysis - select algorithm and parameters
  double Rparam = 0.4;
  fastjet::Strategy               strategy = fastjet::Best;
  fastjet::RecombinationScheme    recombScheme = fastjet::E_scheme;
  fastjet::JetDefinition         *jetDef = NULL;
  jetDef = new fastjet::JetDefinition(fastjet::kt_algorithm, Rparam,
                                      recombScheme, strategy);

  // Fastjet input
  std::vector <fastjet::PseudoJet> fjInputs;

  // Statistics for later
  int nEventAccept25[5] = { 0, 0, 0, 0, 0 };
  int vetoCount[4] = { 0, 0, 0, 0 };
  const char *vetoStr[] = { "ET(elec)", "|eta(elec)|",
                            "ET(missing)", "deltaR(elec, jet)" };
  bool firstEvent = true;

  // Begin event loop. Generate event. Skip if error. List first one.
  for (int iEvent = 0; iEvent < nEvent; ++iEvent) {
    if (iEvent % 10000 == 0) printf("Beginning event %d\n", iEvent);
    if (!pythia.next()) continue;
    if (iEvent < 1) {
      pythia.info.list();
      pythia.event.list();
    }

    // Need to find the electron from the W decay - cheat a bit here
    // and find it from the W in the event record
    int idxW = -1;
    for (int i = pythia.event.size() - 1; i > 0; i--) {
      if (pythia.event[i].idAbs() == 24) {
        idxW = i;
        break;
      }
    }
    if (idxW == -1) {
      cout << "Error: Could not find W" << endl;
      continue;
    }

    // Find the electron from the W decay
    int idxElec = idxW;
    while(true) {
      int daughter = pythia.event[idxElec].daughter1();
      if   (daughter == 0) break;
      else                 idxElec = daughter;
    }
    if (pythia.event[idxElec].idAbs() != 11 ||
       !pythia.event[idxElec].isFinal()) {
      cout << "Error: Found incorrect decay product of the W" << endl;
      continue;
    }

    // Electron cuts
    if (pythia.event[idxElec].pT() < 20.0) {
      vetoCount[0]++;
      continue;
    }
    if (abs(pythia.event[idxElec].eta()) > 1.1) {
      vetoCount[1]++;
      continue;
    }
 
    // Reset Fastjet input
    fjInputs.resize(0);

    // Keep track of missing ET
    Vec4 missingETvec;

    // Loop over event record to decide what to pass to FastJet
    for (int i = 0; i < pythia.event.size(); ++i) {
      // Final state only
      if (!pythia.event[i].isFinal())        continue;

      // No neutrinos
      if (pythia.event[i].idAbs() == 12 || pythia.event[i].idAbs() == 14 ||
          pythia.event[i].idAbs() == 16)     continue;

      // Only |eta| < 3.6
      if (fabs(pythia.event[i].eta()) > 3.6) continue;

      // Missing ET
      missingETvec += pythia.event[i].p();

      // Do not include the electron from the W decay
      if (i == idxElec)                      continue;

      // Store as input to Fastjet
      fjInputs.push_back( fastjet::PseudoJet (pythia.event[i].px(),
						pythia.event[i].py(), pythia.event[i].pz(),
						pythia.event[i].e() ) );
    }

    if (fjInputs.size() == 0) {
      cout << "Error: event with no final state particles" << endl;
      continue;
    }

    // Run Fastjet algorithm
    vector <fastjet::PseudoJet> inclusiveJets, sortedJets;
    fastjet::ClusterSequence clustSeq(fjInputs, *jetDef);

    // For the first event, print the FastJet details
    if (firstEvent) {
      cout << "Ran " << jetDef->description() << endl;
      cout << "Strategy adopted by FastJet was "
           << clustSeq.strategy_string() << endl << endl;
      firstEvent = false;
    }

    // Extract inclusive jets sorted by pT
    inclusiveJets = clustSeq.inclusive_jets();
    sortedJets    = sorted_by_pt(inclusiveJets);  

    // Missing ET cut
    double missingET = missingETvec.pT();
    if (missingET < 30.0) {
      vetoCount[2]++;
      continue;
    }

    // Keep track of jets with pT > 20/25 GeV
    int  jetCount20 = 0, jetCount25 = 0;
    // For the deltaR calculation below
    bool vetoEvent = false;
    fastjet::PseudoJet fjElec(pythia.event[idxElec].px(),
                              pythia.event[idxElec].py(),
                              pythia.event[idxElec].pz(),
                              pythia.event[idxElec].e());
 
    for (unsigned int i = 0; i < sortedJets.size(); i++) {
      // Only count jets that have ET > 20.0 and |eta| < 2.0
      if (sortedJets[i].perp()      < 20.0) break;
      if (fabs(sortedJets[i].rap()) > 2.0)  continue;

      // Check deltaR between W decay electron and jets
      double deltaPhi = fjElec.phi() - sortedJets[i].phi();
      double deltaEta = fjElec.eta() - sortedJets[i].eta();
      double deltaR = sqrt(deltaPhi * deltaPhi + deltaEta * deltaEta);
      if (deltaR < 0.52) { vetoEvent = true; break; }

      // Fill dSigma histograms and count jets with ET > 25.0
      if (sortedJets[i].perp() > 25.0)
        jetCount25++;

      if (jetCount20 <= 3)
        dSigmaHist[++jetCount20]->fill(sortedJets[i].perp());
    }
    if (vetoEvent) { vetoCount[3]++; continue; }

    if (jetCount25 > 4) jetCount25 = 4;
    for (int i = jetCount25; i >= 0; i--)
      nEventAccept25[i]++;

  // End of event loop.
  }

  // Statistics
  pythia.statistics();

  // Output histograms
  double sigmapb = pythia.info.sigmaGen() * 1.0E9;

  for (int i = 1; i <= 4; i++)
    (*dSigmaHist[i]) = ((*dSigmaHist[i]) * sigmapb) / nEvent / dSigmaBin[i];
  cout << dSigma1 << dSigma2 << dSigma3 << dSigma4 << endl;

  // Output cross-sections
  cout << "Jet algorithm is kT" << endl;
  cout << "Multiple interactions are switched "
       << ( (doMI) ? "on" : "off" ) << endl;
  cout << endl << nEvent << " events generated. " << nEventAccept25[0]
       << " events passed cuts." << endl;
  cout << "Vetos:" << endl;
  for (int i = 0; i < 4; i++)
    cout << "  " << vetoStr[i] << " = " << vetoCount[i] << endl;

  cout << endl << "Inclusive cross-sections (pb):" << endl;
  for (int i = 0; i < 5; i++) {
    cout << scientific << setprecision(3)
         << "  " << i << "-jet - Pythia = "
         << ((double) nEventAccept25[i] / (double) nEvent) * sigmapb;
    cout << ", Experimental = " << expCrossSec[i];
    if (i != 0) {
      cout << scientific << setprecision(3)
           << ", Pythia ratio to " << i - 1 << "-jet = "
           << ((double) nEventAccept25[i] / (double) nEventAccept25[i - 1]);
      cout << scientific << setprecision(3)
           << ", Experimental ratio to " << i - 1 << "-jet = "
           << expCrossSec[i] / expCrossSec[i - 1];
    }
    cout << endl;
  }

  return 0;
}

