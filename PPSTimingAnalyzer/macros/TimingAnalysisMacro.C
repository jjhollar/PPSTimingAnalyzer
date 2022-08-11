#define TimingAnalysisMacro_cxx
#include "TimingAnalysisMacro.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void TimingAnalysisMacro::Loop()
{
//   In a ROOT session, you can do:
//      root> .L TimingAnalysisMacro.C
//      root> TimingAnalysisMacro t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   Int_t nent = fChain->GetEntries();

   // Counters and PPS track variables
   Int_t npixeltracks45210, npixeltracks56210, ntimetracks45, ntimetracks56; 
   Float_t pixelx45210, pixely45210, pixelx56210, pixely56210, timingx45, timingx56;
   Float_t time45, time56;

   // Histograms
   TH1F *dxpixelstiming45 = new TH1F("dxpixelstiming45","dxpixelstiming45",500,-10,10);
   TH1F *dxpixelstiming56 = new TH1F("dxpixelstiming56","dxpixelstiming56",500,-10,10);

   TH2F *xypixels45 = new TH2F("xypixels45","xypixels45",500,0,30,500,-15,15);
   TH2F *xypixels56 = new TH2F("xypixels56","xypixels56",500,0,30,500,-15,15);


   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      if(jentry %1000 == 0)
	std::cout << "Entry " << jentry << "/" << nent << std::endl;

      // Select events with 1 non-fake primary vertex, with <= 10 tracks
      if((nVertices > 1) || (PrimVertexIsBS[0] == 1) || (PrimVertexNtracks[0] > 10))
	continue;

      npixeltracks45210 = 0;
      npixeltracks56210 = 0;
      ntimetracks45 = 0;
      ntimetracks56 = 0;

      pixelx45210 = 0.0;
      pixely45210 = 0.0;
      pixelx56210 = 0.0;
      pixelx56210 = 0.0;
      timingx45 = 0.0;
      timingx56 = 0.0;
      time45 = -999.0;
      time56 = -999.0;

      // Loop over all of the local "lite" tracks in each Roman Pot station. 
      // Record the multiplicity, the x,y coordinates in the 210m pixel stations on sectors 45 (+z) and 56 (-z), 
      // and the x,time coordinates in the timing stations on sectors 45 (+z) and 56 (-z).
      // For now the 220m pixel stations are not considered
      for(Int_t ptrack = 0; ptrack < nLiteTracks; ptrack++)
	{
	  // Pixels have x and y segmentation, but no time measurement.
	  if(TrackLiteRPID[ptrack] == 3)
	    {
	      pixelx45210 = TrackLiteX[ptrack];
	      pixely45210 = TrackLiteY[ptrack];
	      npixeltracks45210++;
	    }
	  if(TrackLiteRPID[ptrack] == 103)
            {
              pixelx56210 = TrackLiteX[ptrack];
              pixely56210 = TrackLiteY[ptrack];
	      npixeltracks56210++;
            }
	  
	  // Diamonds have only x segmentation, and the time measurement
          if(TrackLiteRPID[ptrack] == 16)
            {
	      timingx45 = TrackLiteX[ptrack];
	      time45 = TrackLiteTime[ptrack];
	      ntimetracks45++;
            }
          if(TrackLiteRPID[ptrack] == 116)
            {
	      timingx56 = TrackLiteX[ptrack];
	      time56 = TrackLiteTime[ptrack];
	      ntimetracks56++;
            }
	}

      // For the final sample, use events with exactly 1 track in each of the 210m pixels, and 1 track in each of the diamonds
      if((npixeltracks45210==1) && (npixeltracks56210==1) && (ntimetracks45==1) && (ntimetracks56))
	{
	  dxpixelstiming45->Fill(pixelx45210-timingx45);
	  dxpixelstiming56->Fill(pixelx56210-timingx56);
	  
	  xypixels45->Fill(pixelx45210,pixely45210);
	  xypixels56->Fill(pixelx56210,pixely56210);
	}

   }

   TFile *fx = new TFile("OuptutTimingHistograms.root","RECREATE");
   dxpixelstiming45->Write();
   dxpixelstiming56->Write();
   xypixels45->Write();
   xypixels56->Write();
   fx->Close();


}
