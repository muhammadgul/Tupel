//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Feb 26 11:06:39 2015 by ROOT version 5.34/22
// from TTree MuonTree/MuonTree
// found on file: /home/bugra/TTJ_ntuple_amcNLO_bugfix_improvedshower/ttj_amcnlo_bugfix_improvedshower.root
//////////////////////////////////////////////////////////

#ifndef ttjana_h
#define ttjana_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.
   const Int_t kMaxxSecNorm = 1;
   const Int_t kMaxpdfInfo = 1;

class ttjana {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   vector<double>  *weight_amcNLO;
   Double_t        MyWeight;
   Double_t        xSecNorm_;
   Double_t        weight_zero;
   Double_t        weight_one;
   Double_t        weight_two;
   Double_t        weight_three;
   vector<double>  *Dr01LepPt;
   vector<double>  *Dr01LepEta;
   vector<double>  *Dr01LepPhi;
   vector<double>  *Dr01LepE;
   vector<double>  *Dr01LepM;
   vector<double>  *Dr01LepId;
   vector<double>  *Dr01LepStatus;
   vector<double>  *Bare01LepPt;
   vector<double>  *Bare01LepEt;
   vector<double>  *Bare01LepPhi;
   vector<double>  *Bare01LepE;
   vector<double>  *Bare01LepM;
   vector<double>  *Bare01LepId;
   vector<double>  *Bare01LepStatus;
   vector<double>  *St03Pt;
   vector<double>  *St03Eta;
   vector<double>  *St03Phi;
   vector<double>  *St03E;
   vector<double>  *St03M;
   vector<double>  *St03Id;
   vector<double>  *St03Status;
   vector<double>  *St03MotherId;
   vector<double>  *St03PhotonNumberMom;
   vector<double>  *St01PhotonPt;
   vector<double>  *St01PhotonEta;
   vector<double>  *St01PhotonPhi;
   vector<double>  *St01PhotonE;
   vector<double>  *St01PhotonM;
   vector<double>  *St01PhotonId;
   vector<double>  *St01PhotonMomId;
   vector<double>  *St01PhotonNumberMom;
   vector<double>  *St01PhotonStatus;
   vector<double>  *GjPt;
   vector<double>  *Gjeta;
   vector<double>  *Gjphi;
   vector<double>  *GjE;
   vector<double>  *GjPx;
   vector<double>  *GjPy;
   vector<double>  *GjPz;
   vector<double>  *GjChargedFraction;
   vector<double>  *pdfInfo_;

   // List of branches
   TBranch        *b_weight_amcNLO;   //!
   TBranch        *b_MyWeight;   //!
   TBranch        *b_xSecNorm_;   //!
   TBranch        *b_weight_zero;   //!
   TBranch        *b_weight_one;   //!
   TBranch        *b_weight_two;   //!
   TBranch        *b_weight_three;   //!
   TBranch        *b_Dr01LepPt;   //!
   TBranch        *b_Dr01LepEta;   //!
   TBranch        *b_Dr01LepPhi;   //!
   TBranch        *b_Dr01LepE;   //!
   TBranch        *b_Dr01LepM;   //!
   TBranch        *b_Dr01LepId;   //!
   TBranch        *b_Dr01LepStatus;   //!
   TBranch        *b_Bare01LepPt;   //!
   TBranch        *b_Bare01LepEt;   //!
   TBranch        *b_Bare01LepPhi;   //!
   TBranch        *b_Bare01LepE;   //!
   TBranch        *b_Bare01LepM;   //!
   TBranch        *b_Bare01LepId;   //!
   TBranch        *b_Bare01LepStatus;   //!
   TBranch        *b_St03Pt;   //!
   TBranch        *b_St03Eta;   //!
   TBranch        *b_St03Phi;   //!
   TBranch        *b_St03E;   //!
   TBranch        *b_St03M;   //!
   TBranch        *b_St03Id;   //!
   TBranch        *b_St03Status;   //!
   TBranch        *b_St03MotherId;   //!
   TBranch        *b_St03PhotonNumberMom;   //!
   TBranch        *b_St01PhotonPt;   //!
   TBranch        *b_St01PhotonEta;   //!
   TBranch        *b_St01PhotonPhi;   //!
   TBranch        *b_St01PhotonE;   //!
   TBranch        *b_St01PhotonM;   //!
   TBranch        *b_St01PhotonId;   //!
   TBranch        *b_St01PhotonMomId;   //!
   TBranch        *b_St01PhotonNumberMom;   //!
   TBranch        *b_St01PhotonStatus;   //!
   TBranch        *b_GjPt;   //!
   TBranch        *b_Gjeta;   //!
   TBranch        *b_Gjphi;   //!
   TBranch        *b_GjE;   //!
   TBranch        *b_GjPx;   //!
   TBranch        *b_GjPy;   //!
   TBranch        *b_GjPz;   //!
   TBranch        *b_GjChargedFraction;   //!
   TBranch        *b_pdfInfo_;   //!

   ttjana(TTree *tree=0);
   virtual ~ttjana();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual double    DeltaR(double entry1, double entry2, double entry3, double entry4);
   virtual double    DeltaPhi(double entry1, double entry2);
};

#endif

#ifdef ttjana_cxx
ttjana::ttjana(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
//      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/bugra/TTJ_ntuple_amcNLO_bugfix_improvedshower/ttj_amcnlo_bugfix_improvedshower.root");
        TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/bugra/hadd_TTTo2L2Nu2B_8TeV-powheg-pythia6_corr_.root");
//        TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/bugra/TTJets_MSDecays_central_TuneZ2star_8TeV-madgraph-tauola_merged/hadd_TTJets_MSDecays_central_TuneZ2star_8TeV-madgraph-tauola.root");
     if (!f || !f->IsOpen()) {
//         f = new TFile("/home/bugra/TTJ_ntuple_amcNLO_bugfix_improvedshower/ttj_amcnlo_bugfix_improvedshower.root");
         f = new TFile("/home/bugra/hadd_TTTo2L2Nu2B_8TeV-powheg-pythia6_corr_.root");
//         f = new TFile("/home/bugra/TTJets_MSDecays_central_TuneZ2star_8TeV-madgraph-tauola_merged/hadd_TTJets_MSDecays_central_TuneZ2star_8TeV-madgraph-tauola.root"); 
      }
//      TDirectory * dir = (TDirectory*)f->Get("/home/bugra/TTJ_ntuple_amcNLO_bugfix_improvedshower/ttj_amcnlo_bugfix_improvedshower.root:/analyzeBasicPat");
        TDirectory * dir = (TDirectory*)f->Get("/home/bugra/hadd_TTTo2L2Nu2B_8TeV-powheg-pythia6_corr_.root:/analyzeBasicPat");
 //     TDirectory * dir = (TDirectory*)f->Get("/home/bugra/TTJets_MSDecays_central_TuneZ2star_8TeV-madgraph-tauola_merged/hadd_TTJets_MSDecays_central_TuneZ2star_8TeV-madgraph-tauola.root:/analyzeBasicPat");
      dir->GetObject("MuonTree",tree);

   }
   Init(tree);
}

ttjana::~ttjana()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ttjana::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ttjana::LoadTree(Long64_t entry)
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

void ttjana::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   weight_amcNLO = 0;
   Dr01LepPt = 0;
   Dr01LepEta = 0;
   Dr01LepPhi = 0;
   Dr01LepE = 0;
   Dr01LepM = 0;
   Dr01LepId = 0;
   Dr01LepStatus = 0;
   Bare01LepPt = 0;
   Bare01LepEt = 0;
   Bare01LepPhi = 0;
   Bare01LepE = 0;
   Bare01LepM = 0;
   Bare01LepId = 0;
   Bare01LepStatus = 0;
   St03Pt = 0;
   St03Eta = 0;
   St03Phi = 0;
   St03E = 0;
   St03M = 0;
   St03Id = 0;
   St03Status = 0;
   St03MotherId = 0;
   St03PhotonNumberMom = 0;
   St01PhotonPt = 0;
   St01PhotonEta = 0;
   St01PhotonPhi = 0;
   St01PhotonE = 0;
   St01PhotonM = 0;
   St01PhotonId = 0;
   St01PhotonMomId = 0;
   St01PhotonNumberMom = 0;
   St01PhotonStatus = 0;
   GjPt = 0;
   Gjeta = 0;
   Gjphi = 0;
   GjE = 0;
   GjPx = 0;
   GjPy = 0;
   GjPz = 0;
   GjChargedFraction = 0;
   pdfInfo_ = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("weight_amcNLO", &weight_amcNLO, &b_weight_amcNLO);
   fChain->SetBranchAddress("MyWeight", &MyWeight, &b_MyWeight);
   fChain->SetBranchAddress("xSecNorm_", &xSecNorm_, &b_xSecNorm_);
   fChain->SetBranchAddress("weight_zero", &weight_zero, &b_weight_zero);
   fChain->SetBranchAddress("weight_one", &weight_one, &b_weight_one);
   fChain->SetBranchAddress("weight_two", &weight_two, &b_weight_two);
   fChain->SetBranchAddress("weight_three", &weight_three, &b_weight_three);
   fChain->SetBranchAddress("Dr01LepPt", &Dr01LepPt, &b_Dr01LepPt);
   fChain->SetBranchAddress("Dr01LepEta", &Dr01LepEta, &b_Dr01LepEta);
   fChain->SetBranchAddress("Dr01LepPhi", &Dr01LepPhi, &b_Dr01LepPhi);
   fChain->SetBranchAddress("Dr01LepE", &Dr01LepE, &b_Dr01LepE);
   fChain->SetBranchAddress("Dr01LepM", &Dr01LepM, &b_Dr01LepM);
   fChain->SetBranchAddress("Dr01LepId", &Dr01LepId, &b_Dr01LepId);
   fChain->SetBranchAddress("Dr01LepStatus", &Dr01LepStatus, &b_Dr01LepStatus);
   fChain->SetBranchAddress("Bare01LepPt", &Bare01LepPt, &b_Bare01LepPt);
   fChain->SetBranchAddress("Bare01LepEt", &Bare01LepEt, &b_Bare01LepEt);
   fChain->SetBranchAddress("Bare01LepPhi", &Bare01LepPhi, &b_Bare01LepPhi);
   fChain->SetBranchAddress("Bare01LepE", &Bare01LepE, &b_Bare01LepE);
   fChain->SetBranchAddress("Bare01LepM", &Bare01LepM, &b_Bare01LepM);
   fChain->SetBranchAddress("Bare01LepId", &Bare01LepId, &b_Bare01LepId);
   fChain->SetBranchAddress("Bare01LepStatus", &Bare01LepStatus, &b_Bare01LepStatus);
   fChain->SetBranchAddress("St03Pt", &St03Pt, &b_St03Pt);
   fChain->SetBranchAddress("St03Eta", &St03Eta, &b_St03Eta);
   fChain->SetBranchAddress("St03Phi", &St03Phi, &b_St03Phi);
   fChain->SetBranchAddress("St03E", &St03E, &b_St03E);
   fChain->SetBranchAddress("St03M", &St03M, &b_St03M);
   fChain->SetBranchAddress("St03Id", &St03Id, &b_St03Id);
   fChain->SetBranchAddress("St03Status", &St03Status, &b_St03Status);
   fChain->SetBranchAddress("St03MotherId", &St03MotherId, &b_St03MotherId);
   fChain->SetBranchAddress("St03PhotonNumberMom", &St03PhotonNumberMom, &b_St03PhotonNumberMom);
   fChain->SetBranchAddress("St01PhotonPt", &St01PhotonPt, &b_St01PhotonPt);
   fChain->SetBranchAddress("St01PhotonEta", &St01PhotonEta, &b_St01PhotonEta);
   fChain->SetBranchAddress("St01PhotonPhi", &St01PhotonPhi, &b_St01PhotonPhi);
   fChain->SetBranchAddress("St01PhotonE", &St01PhotonE, &b_St01PhotonE);
   fChain->SetBranchAddress("St01PhotonM", &St01PhotonM, &b_St01PhotonM);
   fChain->SetBranchAddress("St01PhotonId", &St01PhotonId, &b_St01PhotonId);
   fChain->SetBranchAddress("St01PhotonMomId", &St01PhotonMomId, &b_St01PhotonMomId);
   fChain->SetBranchAddress("St01PhotonNumberMom", &St01PhotonNumberMom, &b_St01PhotonNumberMom);
   fChain->SetBranchAddress("St01PhotonStatus", &St01PhotonStatus, &b_St01PhotonStatus);
   fChain->SetBranchAddress("GjPt", &GjPt, &b_GjPt);
   fChain->SetBranchAddress("Gjeta", &Gjeta, &b_Gjeta);
   fChain->SetBranchAddress("Gjphi", &Gjphi, &b_Gjphi);
   fChain->SetBranchAddress("GjE", &GjE, &b_GjE);
   fChain->SetBranchAddress("GjPx", &GjPx, &b_GjPx);
   fChain->SetBranchAddress("GjPy", &GjPy, &b_GjPy);
   fChain->SetBranchAddress("GjPz", &GjPz, &b_GjPz);
   fChain->SetBranchAddress("GjChargedFraction", &GjChargedFraction, &b_GjChargedFraction);
   fChain->SetBranchAddress("pdfInfo_", &pdfInfo_, &b_pdfInfo_);
   Notify();
}

Bool_t ttjana::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ttjana::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ttjana::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

double ttjana::DeltaR(double eta1, double eta2, double phi1, double phi2)
	{
	double deta = eta2 - eta1;
	double dphi = phi2 - phi1;
	if (fabs(dphi) > 3.14) dphi = 6.28 - fabs(dphi);
	double DELTAR = sqrt(pow(dphi,2)+pow(deta,2))*1.0;
	return DELTAR;
	}
double ttjana::DeltaPhi(double phi1, double phi2)
	{
	double dphi = phi2 - phi1;
	if (fabs(dphi) > 3.14) dphi = 6.28 - fabs(dphi);
	return dphi;
	}
	
#endif // #ifdef ttjana_cxx
