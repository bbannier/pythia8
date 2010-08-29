//gSystem.Load("../libPythia8");
// File: main01.cc
// This is a simple test program.
// It studies the charged multiplicity distribution at the LHC.
// Modified by Rene Brun to use ROOT for histogramming.
// Copyright C 2007 Torbjorn Sjostrand
#include "Pythia.h"
#include "TH1.h"
#include "TTree.h"
#include "TFile.h"
 using namespace Pythia8;
int main() {
   //gSystem->Load("$PYTHIA8/lib/libpythia8");
   //gSystem->Load("libEGPythia8");
   
 // Generator. Process selection. LHC initialization. Histogram.
 Pythia pythia;
 pythia.readString("HardQCD:all = on");
 pythia.readString("PhaseSpace:pTHatMin = 20.");
 pythia.init( 2212, 2212, 14000.);
 TFile *file = TFile::Open("ex1.root","recreate");
 Event *event = &pythia.event;
 TTree *T = new TTree("T","ev1 Tree");
 //T->Branch("event","Event",&event);
 T->Branch("event",&event);
 TH1F *mult = new TH1F("mult","charged multiplicity", 100, -0.5, 799.5);
 // Begin event loop. Generate event. Skip if error. List first one.
 for (int iEvent = 0; iEvent < 100; ++iEvent) {
   if (!pythia.next()) continue;
   //if (iEvent < 1) {pythia.info.list(); pythia.event.list();}
   // Find number of all final charged particles and fill histogram.
   int nCharged = 0;
   for (int i = 0; i < pythia.event.size(); ++i)
     if (pythia.event[i].isFinal() && pythia.event[i].isCharged())
       ++nCharged;
   mult->Fill( nCharged );
   T->Fill();
 // End of event loop. Statistics. Histogram. Done.
 }
 pythia.statistics();
 cout << mult;
 T->Print();
 T->Write();
 delete file;
 return 0;
}
