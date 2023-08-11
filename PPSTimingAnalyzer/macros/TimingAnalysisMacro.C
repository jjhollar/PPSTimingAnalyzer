#define TimingAnalysisMacro_cxx
#include "TimingAnalysisMacro.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void TimingAnalysisMacro::Loop()
{
// Macro for running on ntuples output from PPS timing analyzer, to perform a 2018-like study of the proton time 
// difference vs. CMS vertex position. Output is a file containing histograms, that can be used for fitting the 
// time resolution in 2-arm events. 
//
// Note - for 2022, until the proton object reconstruction is finalized, this works with local tracks
//
//   In a ROOT session:
//      root> .L TimingAnalysisMacro.C
//      root> TimingAnalysisMacro t
//      root> t.Loop();       // Loop on all entries


   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   Int_t nent = fChain->GetEntries();

   // Ideal correlation between vertex z position and PPS time difference should be c/2. 
   // z is in cm, PPS time is in ns
   Float_t cmtons = 1.0/14.989623;

   // Counters and PPS track variables
   Int_t npixeltracks45210, npixeltracks56210, npixeltracks45220, npixeltracks56220;
   Int_t ntimetracks45, ntimetracks56, ntimetracksbox45, ntimetracksbox56; 
   Float_t pixelx45210, pixely45210, pixelx56210, pixely56210, timingx45, timingx56;
   Float_t pixelx45220, pixely45220, pixelx56220, pixely56220, timingxbox45, timingxbox56;
   Float_t time45, time56, timeunc45, timeunc56, timebox45, timebox56, timeuncbox45, timeuncbox56;

   // Histograms
   TH1F *dxpixelstiming45 = new TH1F("dxpixelstiming45","dxpixelstiming45",500,-10,10);
   TH1F *dxpixelstiming56 = new TH1F("dxpixelstiming56","dxpixelstiming56",500,-10,10);

   TH1F *dxpixelstimingbox45 = new TH1F("dxpixelstimingbox45","dxpixelstimingbox45",500,-10,10);
   TH1F *dxpixelstimingbox56 = new TH1F("dxpixelstimingbox56","dxpixelstimingbox56",500,-10,10);

   TH2F *xypixels45 = new TH2F("xypixels45","xypixels45",500,0,30,500,-15,15);
   TH2F *xypixels56 = new TH2F("xypixels56","xypixels56",500,0,30,500,-15,15);

   TH2F *timevstime = new TH2F("timevstime","timevstime",250,0,25,250,0,25);
   TH2F *timevstimebox = new TH2F("timevstimebox","timevstimebox",250,0,25,250,0,25);

   TH1F *htimeunc45 = new TH1F("htimeunc45","htimeunc45",100,0,2);
   TH1F *htimeunc56 = new TH1F("htimeunc56","htimeunc56",100,0,2);

   TH2F *zvtxvstimediff = new TH2F("zvtxvstimediff","zvtxvstimediff",100,-20,20,50,-3,3);
   TH1F *zminustimediff = new TH1F("zminustimediff","zminustimediff",500,-100,100);

   TH1F *htimeuncbox45 = new TH1F("htimeuncbox45","htimeuncbox45",100,0,2);
   TH1F *htimeuncbox56 = new TH1F("htimeuncbox56","htimeuncbox56",100,0,2);

   TH2F *zvtxvstimediffbox = new TH2F("zvtxvstimediffbox","zvtxvstimediffbox",100,-20,20,50,-3,3);
   TH1F *zminustimediffbox = new TH1F("zminustimediffbox","zminustimediffbox",500,-100,100);

   TH2F *xx45 = new TH2F("xx45","xx45",50,0,25,50,0,25);
   TH2F *xx56 = new TH2F("xx56","xx56",50,0,25,50,0,25);

   TH2F *xxbox45 = new TH2F("xxbox45","xxbox45",50,0,25,50,0,25);
   TH2F *xxbox56 = new TH2F("xxbox56","xxbox56",50,0,25,50,0,25);


   TH2F *channeltimes = new TH2F("channeltimes","channeltimes",96,0,96,350,-10,25);

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      if(jentry %1000 == 0)
	std::cout << "Entry " << jentry << "/" << nent << std::endl;

      // This is for the 2023 low-pileup run
      if((LumiSection < 236) || (LumiSection > 709))
      	continue;

      // Select events with 1 non-fake primary vertex, with <= 10 tracks
      if((nVertices > 1) || (PrimVertexIsBS[0] == 1) || (PrimVertexNtracks[0] > 10))
	continue;

      npixeltracks45210 = 0;
      npixeltracks56210 = 0;
      npixeltracks45220 = 0;
      npixeltracks56220 = 0;
      ntimetracks45 = 0;
      ntimetracks56 = 0;
      ntimetracksbox45 = 0;
      ntimetracksbox56 = 0;

      pixelx45210 = 0.0;
      pixely45210 = 0.0;
      pixelx56210 = 0.0;
      pixelx56210 = 0.0;
      pixelx45220 = 0.0;
      pixely45220 = 0.0;
      pixelx56220 = 0.0;
      pixelx56220 = 0.0;
      timingx45 = 0.0;
      timingx56 = 0.0;
      time45 = -999.0;
      time56 = -999.0;
      timeunc45 = -999.0;
      timeunc56 = -999.0;
      timingxbox45 = 0.0;
      timingxbox56 = 0.0;
      timebox45 = -999.0;
      timebox56 = -999.0;
      timeuncbox45 = -999.0;
      timeuncbox56 = -999.0;

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
          if(TrackLiteRPID[ptrack] == 23)
            {
              pixelx45220 = TrackLiteX[ptrack];
              pixely45220 = TrackLiteY[ptrack];
              npixeltracks45220++;
            }
          if(TrackLiteRPID[ptrack] == 123)
            {
              pixelx56220 = TrackLiteX[ptrack];
              pixely56220 = TrackLiteY[ptrack];
              npixeltracks56220++;
            }
	  
	  // Diamonds have only x segmentation, and the time measurement
          if(TrackLiteRPID[ptrack] == 16)
            {
	      timingx45 = TrackLiteX[ptrack];
	      time45 = TrackLiteTime[ptrack];
	      timeunc45 = TrackLiteTimeUnc[ptrack];
	      ntimetracks45++;
            }
          if(TrackLiteRPID[ptrack] == 116)
            {
	      timingx56 = TrackLiteX[ptrack];
	      time56 = TrackLiteTime[ptrack];
              timeunc56 = TrackLiteTimeUnc[ptrack];
	      ntimetracks56++;
            }
          if(TrackLiteRPID[ptrack] == 22)
            {
              timingxbox45 = TrackLiteX[ptrack];
              timebox45 = TrackLiteTime[ptrack];
              timeuncbox45 = TrackLiteTimeUnc[ptrack];
              ntimetracksbox45++;
            }
          if(TrackLiteRPID[ptrack] == 122)
            {
              timingxbox56 = TrackLiteX[ptrack];
              timebox56 = TrackLiteTime[ptrack];
              timeuncbox56 = TrackLiteTimeUnc[ptrack];
              ntimetracksbox56++;
            }

	}

      // For the final sample, use events with exactly 1 track in each of the 210+220m pixels, and 1 track in the diamonds on each arm
      // FIXME: For now, we treat the 2-arm combinations cylindrical-cylindrical and box-box as 2 separate cases. 
      if((npixeltracks45220==1) && (npixeltracks56220==1) && (npixeltracks45210==1) && (npixeltracks56210==1))
	{
	  // 2d maps of pixel tracks                                                                                                                                                     
	  xypixels45->Fill(pixelx45220,pixely45220);
	  xypixels56->Fill(pixelx56220,pixely56220);

	  if((ntimetracks45==1) && (ntimetracks56==1))
	    {
	      // Time measurement on each arm
	      timevstime->Fill(time45,time56);
	      
	      // Matching between x position of pixel and diamond tracks
	      dxpixelstiming45->Fill(pixelx45220-timingx45);
	      dxpixelstiming56->Fill(pixelx56220-timingx56);
	      
	      // 2d correlation of x position in pixels and x position in diamonds
	      xx45->Fill(pixelx45220,timingx45);
	      xx56->Fill(pixelx56220,timingx56);
	      
	      // Scatter plot of vertex Z vs. proton time difference
	      zvtxvstimediff->Fill(PrimVertexZ[0],time56-time45);
	      // Projection of vertex Z minus proton time difference (converted from ns to cm)
	      zminustimediff->Fill(PrimVertexZ[0] - (time56-time45)/cmtons);
	      
	      // Store the predicted track-by-track time uncertainties, based on which channels 
	      // contribute to the track
	      htimeunc45->Fill(timeunc45);
	      htimeunc56->Fill(timeunc56);
	    }
          if((ntimetracksbox45==1) && (ntimetracksbox56==1))
            {
              // Time measurement on each arm                                                                                                                                              
              timevstimebox->Fill(timebox45,timebox56);

              // Matching between x position of pixel and diamond tracks                                                                                                                   
              dxpixelstimingbox45->Fill(pixelx45220-timingxbox45);
              dxpixelstimingbox56->Fill(pixelx56220-timingxbox56);

              // 2d correlation of x position in pixels and x position in diamonds                                                                                                         
              xxbox45->Fill(pixelx45220,timingxbox45);
              xxbox56->Fill(pixelx56220,timingxbox56);

              // Scatter plot of vertex Z vs. proton time difference                                                                                                                       
              zvtxvstimediffbox->Fill(PrimVertexZ[0],timebox56-timebox45);
              // Projection of vertex Z minus proton time difference (converted from ns to cm)                                                                                             
              zminustimediffbox->Fill(PrimVertexZ[0] - (timebox56-timebox45)/cmtons);

              // Store the predicted track-by-track time uncertainties, based on which channels                                                                                            
              // contribute to the track                                                                                                                                                   
              htimeuncbox45->Fill(timeuncbox45);
              htimeuncbox56->Fill(timeuncbox56);
            }
	}
      // Finally, to check the channel-by-channel time alignment, just plot the RecHit arrival time for 
      // each channel with no selection
      for(Int_t rh = 0; rh < nRecHitsTiming; rh++)
	{
	  // Unroll arms/planes/channels into a single histogram
	  Int_t num = (48*TimingRecHitArm[rh]) + (12*TimingRecHitPlane[rh]) + (TimingRecHitChannel[rh]);

	  // Plot events with a reasonable Time-over-threshold
	  if(TimingRecHitToT[rh] > 0 && TimingRecHitToT[rh] < 25)
	    channeltimes->Fill(num,TimingRecHitT[rh]);
	}

   }

   TFile *fx = new TFile("TimingHistograms.root","RECREATE");
   xypixels45->Write();
   xypixels56->Write();

   dxpixelstiming45->Write();
   dxpixelstiming56->Write();
   xx45->Write();
   xx56->Write();
   zvtxvstimediff->Write();
   zminustimediff->Write();
   htimeunc45->Write();
   htimeunc56->Write();
   timevstime->Write();

   dxpixelstimingbox45->Write();
   dxpixelstimingbox56->Write();
   xxbox45->Write();
   xxbox56->Write();
   zvtxvstimediffbox->Write();
   zminustimediffbox->Write();
   htimeuncbox45->Write();
   htimeuncbox56->Write();
   timevstimebox->Write();


   channeltimes->Write();
   fx->Close();


}
