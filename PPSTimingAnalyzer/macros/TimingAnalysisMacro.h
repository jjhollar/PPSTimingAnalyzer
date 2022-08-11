//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Aug 11 09:50:10 2022 by ROOT version 6.24/07
// from TChain ntp1/
//////////////////////////////////////////////////////////

#ifndef TimingAnalysisMacro_h
#define TimingAnalysisMacro_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class TimingAnalysisMacro {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           Run;
   Int_t           LumiSection;
   Int_t           BX;
   Int_t           EventNum;
   Float_t         CrossingAngle;
   Int_t           nRecHitsTiming;
   Int_t           TimingRecHitArm[48];   //[nRecHitsTiming]
   Int_t           TimingRecHitChannel[48];   //[nRecHitsTiming]
   Int_t           TimingRecHitPlane[48];   //[nRecHitsTiming]
   Double_t        TimingRecHitT[48];   //[nRecHitsTiming]
   Double_t        TimingRecHitX[48];   //[nRecHitsTiming]
   Double_t        TimingRecHitY[48];   //[nRecHitsTiming]
   Double_t        TimingRecHitToT[48];   //[nRecHitsTiming]
   Int_t           TimingRecHitOOTIndex[48];   //[nRecHitsTiming]
   Int_t           TimingRecHitMultiHit[48];   //[nRecHitsTiming]
   Int_t           nLiteTracks;
   Float_t         TrackLiteX[15];   //[nLiteTracks]
   Float_t         TrackLiteY[15];   //[nLiteTracks]
   Float_t         TrackLiteZ[15];   //[nLiteTracks]
   Float_t         TrackLiteTime[15];   //[nLiteTracks]
   Float_t         TrackLiteTimeUnc[15];   //[nLiteTracks]
   Int_t           TrackLiteRPID[15];   //[nLiteTracks]
   Int_t           TrackLiteArm[15];   //[nLiteTracks]
   Int_t           nVertices;
   Double_t        PrimVertexZ[10];   //[nVertices]
   Double_t        PrimVertexX[10];   //[nVertices]
   Double_t        PrimVertexY[10];   //[nVertices]
   Int_t           PrimVertexNtracks[10];   //[nVertices]
   Int_t           PrimVertexIsBS[10];   //[nVertices]
   Int_t           nProtons;
   Float_t         ProtonXi[1];   //[nProtons]
   Float_t         ProtonThX[1];   //[nProtons]
   Float_t         ProtonThY[1];   //[nProtons]
   Float_t         Protont[1];   //[nProtons]
   Int_t           ProtonIsMultiRP[1];   //[nProtons]
   Int_t           ProtonRPID[1];   //[nProtons]
   Int_t           ProtonArm[1];   //[nProtons]
   Float_t         ProtonTime[1];   //[nProtons]

   // List of branches
   TBranch        *b_Run;   //!
   TBranch        *b_LumiSection;   //!
   TBranch        *b_BX;   //!
   TBranch        *b_EventNum;   //!
   TBranch        *b_CrossingAngle;   //!
   TBranch        *b_nRecHitsTiming;   //!
   TBranch        *b_TimingRecHitArm;   //!
   TBranch        *b_TimingRecHitChannel;   //!
   TBranch        *b_TimingRecHitPlane;   //!
   TBranch        *b_TimingRecHitT;   //!
   TBranch        *b_TimingRecHitX;   //!
   TBranch        *b_TimingRecHitY;   //!
   TBranch        *b_TimingRecHitToT;   //!
   TBranch        *b_TimingRecHitOOTIndex;   //!
   TBranch        *b_TimingRecHitMultiHit;   //!
   TBranch        *b_nLiteTracks;   //!
   TBranch        *b_TrackLiteX;   //!
   TBranch        *b_TrackLiteY;   //!
   TBranch        *b_TrackLiteZ;   //!
   TBranch        *b_TrackLiteTime;   //!
   TBranch        *b_TrackLiteTimeUnc;   //!
   TBranch        *b_TrackLiteRPID;   //!
   TBranch        *b_TrackLiteArm;   //!
   TBranch        *b_nVertices;   //!
   TBranch        *b_PrimVertexZ;   //!
   TBranch        *b_PrimVertexX;   //!
   TBranch        *b_PrimVertexY;   //!
   TBranch        *b_PrimVertexNtracks;   //!
   TBranch        *b_PrimVertexIsBS;   //!
   TBranch        *b_nProtons;   //!
   TBranch        *b_ProtonXi;   //!
   TBranch        *b_ProtonThX;   //!
   TBranch        *b_ProtonThY;   //!
   TBranch        *b_Protont;   //!
   TBranch        *b_ProtonIsMultiRP;   //!
   TBranch        *b_ProtonRPID;   //!
   TBranch        *b_ProtonArm;   //!
   TBranch        *b_ProtonTime;   //!

   TimingAnalysisMacro(TTree *tree=0);
   virtual ~TimingAnalysisMacro();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef TimingAnalysisMacro_cxx
TimingAnalysisMacro::TimingAnalysisMacro(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f || !f->IsOpen()) {
         f = new TFile("Memory Directory");
      }
      f->GetObject("ntp1",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("ntp1","");
      chain->Add("output_ZeroBias.root/ntp1");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

TimingAnalysisMacro::~TimingAnalysisMacro()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TimingAnalysisMacro::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t TimingAnalysisMacro::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void TimingAnalysisMacro::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Run", &Run, &b_Run);
   fChain->SetBranchAddress("LumiSection", &LumiSection, &b_LumiSection);
   fChain->SetBranchAddress("BX", &BX, &b_BX);
   fChain->SetBranchAddress("EventNum", &EventNum, &b_EventNum);
   fChain->SetBranchAddress("CrossingAngle", &CrossingAngle, &b_CrossingAngle);
   fChain->SetBranchAddress("nRecHitsTiming", &nRecHitsTiming, &b_nRecHitsTiming);
   fChain->SetBranchAddress("TimingRecHitArm", TimingRecHitArm, &b_TimingRecHitArm);
   fChain->SetBranchAddress("TimingRecHitChannel", TimingRecHitChannel, &b_TimingRecHitChannel);
   fChain->SetBranchAddress("TimingRecHitPlane", TimingRecHitPlane, &b_TimingRecHitPlane);
   fChain->SetBranchAddress("TimingRecHitT", TimingRecHitT, &b_TimingRecHitT);
   fChain->SetBranchAddress("TimingRecHitX", TimingRecHitX, &b_TimingRecHitX);
   fChain->SetBranchAddress("TimingRecHitY", TimingRecHitY, &b_TimingRecHitY);
   fChain->SetBranchAddress("TimingRecHitToT", TimingRecHitToT, &b_TimingRecHitToT);
   fChain->SetBranchAddress("TimingRecHitOOTIndex", TimingRecHitOOTIndex, &b_TimingRecHitOOTIndex);
   fChain->SetBranchAddress("TimingRecHitMultiHit", TimingRecHitMultiHit, &b_TimingRecHitMultiHit);
   fChain->SetBranchAddress("nLiteTracks", &nLiteTracks, &b_nLiteTracks);
   fChain->SetBranchAddress("TrackLiteX", TrackLiteX, &b_TrackLiteX);
   fChain->SetBranchAddress("TrackLiteY", TrackLiteY, &b_TrackLiteY);
   fChain->SetBranchAddress("TrackLiteZ", TrackLiteZ, &b_TrackLiteZ);
   fChain->SetBranchAddress("TrackLiteTime", TrackLiteTime, &b_TrackLiteTime);
   fChain->SetBranchAddress("TrackLiteTimeUnc", TrackLiteTimeUnc, &b_TrackLiteTimeUnc);
   fChain->SetBranchAddress("TrackLiteRPID", TrackLiteRPID, &b_TrackLiteRPID);
   fChain->SetBranchAddress("TrackLiteArm", TrackLiteArm, &b_TrackLiteArm);
   fChain->SetBranchAddress("nVertices", &nVertices, &b_nVertices);
   fChain->SetBranchAddress("PrimVertexZ", PrimVertexZ, &b_PrimVertexZ);
   fChain->SetBranchAddress("PrimVertexX", PrimVertexX, &b_PrimVertexX);
   fChain->SetBranchAddress("PrimVertexY", PrimVertexY, &b_PrimVertexY);
   fChain->SetBranchAddress("PrimVertexNtracks", PrimVertexNtracks, &b_PrimVertexNtracks);
   fChain->SetBranchAddress("PrimVertexIsBS", PrimVertexIsBS, &b_PrimVertexIsBS);
   fChain->SetBranchAddress("nProtons", &nProtons, &b_nProtons);
   fChain->SetBranchAddress("ProtonXi", &ProtonXi, &b_ProtonXi);
   fChain->SetBranchAddress("ProtonThX", &ProtonThX, &b_ProtonThX);
   fChain->SetBranchAddress("ProtonThY", &ProtonThY, &b_ProtonThY);
   fChain->SetBranchAddress("Protont", &Protont, &b_Protont);
   fChain->SetBranchAddress("ProtonIsMultiRP", &ProtonIsMultiRP, &b_ProtonIsMultiRP);
   fChain->SetBranchAddress("ProtonRPID", &ProtonRPID, &b_ProtonRPID);
   fChain->SetBranchAddress("ProtonArm", &ProtonArm, &b_ProtonArm);
   fChain->SetBranchAddress("ProtonTime", &ProtonTime, &b_ProtonTime);
   Notify();
}

Bool_t TimingAnalysisMacro::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TimingAnalysisMacro::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TimingAnalysisMacro::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef TimingAnalysisMacro_cxx
