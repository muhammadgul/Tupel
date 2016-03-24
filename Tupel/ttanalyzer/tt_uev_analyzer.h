//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Oct 10 16:56:03 2015 by ROOT version 6.02/05
// from TChain MuonTree/
//////////////////////////////////////////////////////////

#ifndef tt_uev_analyzer_h
#define tt_uev_analyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
using namespace std;
// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"
#include "vector"

class tt_uev_analyzer {
 public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain

  // Fixed size dimensions of array or collections stored in the TTree if any.
  const Int_t kMaxpatMuonPt = 1;
  const Int_t kMaxpatMuonEta = 1;
  const Int_t kMaxpatMuonPhi = 1;
  const Int_t kMaxpatMuonVtxZ = 1;
  const Int_t kMaxpatMuonEn = 1;
  const Int_t kMaxpatMuonCharge = 1;
  const Int_t kMaxpatMuonDxy = 1;
  const Int_t kMaxpatMuonCombId = 1;
  const Int_t kMaxpatMuonLooseId = 1;
  const Int_t kMaxpatMuonMediumId = 1;
  const Int_t kMaxpatMuonTightId = 1;
  const Int_t kMaxpatMuonTrig = 1;
  const Int_t kMaxpatMuonDetIsoRho = 1;
  const Int_t kMaxpatMuonPfIsoDbeta = 1;
  const Int_t kMaxpatMuonM = 1;
  const Int_t kMaxpatMuonPx = 1;
  const Int_t kMaxpatMuonPy = 1;
  const Int_t kMaxpatMuonPz = 1;
  const Int_t kMaxpatMuonGlobalType = 1;
  const Int_t kMaxpatMuonTrackerType = 1;
  const Int_t kMaxpatMuonPFType = 1;
  const Int_t kMaxpatMuonIsoSumPt = 1;
  const Int_t kMaxpatMuonIsoRelative = 1;
  const Int_t kMaxpatMuonIsoCalComb = 1;
  const Int_t kMaxpatMuonIsoDY = 1;
  const Int_t kMaxpatMuonChi2Ndoff = 1;
  const Int_t kMaxpatMuonNhits = 1;
  const Int_t kMaxpatMuonNMatches = 1;
  const Int_t kMaxpatMuonDz = 1;
  const Int_t kMaxpatMuonPhits = 1;
  const Int_t kMaxpatMuonTkLayers = 1;
  const Int_t kMaxpatMuon_PF_IsoSumChargedHadronPt = 1;
  const Int_t kMaxpatMuon_PF_IsoSumNeutralHadronEt = 1;
  const Int_t kMaxpatMuon_PF_IsoDY = 1;
  const Int_t kMaxpatMuon_Mu17_Mu8_Matched = 1;
  const Int_t kMaxpatMuon_Mu17_TkMu8_Matched = 1;
  const Int_t kMaxpatElecId = 1;
  const Int_t kMaxpatElecdEtaIn = 1;
  const Int_t kMaxpatElecdPhiIn = 1;
  const Int_t kMaxpatElechOverE = 1;
  const Int_t kMaxpatElecsigmaIetaIeta = 1;
  const Int_t kMaxpatElecfull5x5_sigmaIetaIeta = 1;
  const Int_t kMaxpatElecooEmooP = 1;
  const Int_t kMaxpatElecd0 = 1;
  const Int_t kMaxpatElecdz = 1;
  const Int_t kMaxpatElecexpectedMissingInnerHits = 1;
  const Int_t kMaxpatElecpassConversionVeto = 1;
  const Int_t kMaxpatElecTrig = 1;
  const Int_t kMaxpatElecDz = 1;
  const Int_t kMaxpatElecMVATrigId = 1;
  const Int_t kMaxpatElecMVANonTrigId = 1;
  const Int_t kMaxpatElecPt = 1;
  const Int_t kMaxpatElecEta = 1;
  const Int_t kMaxpatElecScEta = 1;
  const Int_t kMaxpatElecPhi = 1;
  const Int_t kMaxpatElecEnergy = 1;
  const Int_t kMaxpatElecCharge = 1;
  const Int_t kMaxpatElecMediumIDOff = 1;
  const Int_t kMaxpatElecMediumIDOff_Tom = 1;
  const Int_t kMaxpatElecchIso03 = 1;
  const Int_t kMaxpatElecnhIso03 = 1;
  const Int_t kMaxpatElecphIso03 = 1;
  const Int_t kMaxpatElecpuChIso03 = 1;
  const Int_t kMaxpatElecPfIso = 1;
  const Int_t kMaxpatElecPfIsodb = 1;
  const Int_t kMaxpatElecPfIsoRho = 1;
  const Int_t kMaxneutral = 1;
  const Int_t kMaxphoton = 1;
  const Int_t kMaxcharged = 1;
  const Int_t kMaxneutral_Tom = 1;
  const Int_t kMaxphoton_Tom = 1;
  const Int_t kMaxcharged_Tom = 1;
  const Int_t kMaxpatElec_mva_presel = 1;
  const Int_t kMaxpatJetPfAk04En = 1;
  const Int_t kMaxpatJetPfAk04Pt = 1;
  const Int_t kMaxpatJetPfAk04Eta = 1;
  const Int_t kMaxpatJetPfAk04Phi = 1;
  const Int_t kMaxpatJetPfAk04LooseId = 1;
  const Int_t kMaxpatJetPfAk04Et = 1;
  const Int_t kMaxpatJetPfAk04RawPt = 1;
  const Int_t kMaxpatJetPfAk04RawEn = 1;
  const Int_t kMaxpatJetPfAk04HadEHF = 1;
  const Int_t kMaxpatJetPfAk04EmEHF = 1;
  const Int_t kMaxpatJetPfAk04chf = 1;
  const Int_t kMaxpatJetPfAk04nhf = 1;
  const Int_t kMaxpatJetPfAk04cemf = 1;
  const Int_t kMaxpatJetPfAk04nemf = 1;
  const Int_t kMaxpatJetPfAk04cmult = 1;
  const Int_t kMaxpatJetPfAk04nconst = 1;
  const Int_t kMaxpatJetPfAk04jetBeta = 1;
  const Int_t kMaxpatJetPfAk04jetBetaClassic = 1;
  const Int_t kMaxpatJetPfAk04jetBetaStar = 1;
  const Int_t kMaxpatJetPfAk04jetBetaStarClassic = 1;
  const Int_t kMaxpatJetPfAk04jetpuMVA = 1;
  const Int_t kMaxpatJetPfAk04jetpukLoose = 1;
  const Int_t kMaxpatJetPfAk04jetpukMedium = 1;
  const Int_t kMaxpatJetPfAk04jetpukTight = 1;
  const Int_t kMaxpatJetPfAk04BDiscCSVv2 = 1;
  const Int_t kMaxpatJetPfAk04BDiscCSVV1 = 1;
  const Int_t kMaxpatJetPfAk04BDiscCSVSLV1 = 1;
  const Int_t kMaxunc = 1;
  const Int_t kMaxpatJetPfAk04PtUp = 1;
  const Int_t kMaxpatJetPfAk04PtDn = 1;
  const Int_t kMaxcaloJetPt = 1;
  const Int_t kMaxcaloJetRawPt = 1;
  const Int_t kMaxcaloJetEn = 1;
  const Int_t kMaxcaloJetEta = 1;
  const Int_t kMaxcaloJetPhi = 1;
  const Int_t kMaxcaloJetHadEHF = 1;
  const Int_t kMaxcaloJetEmEHF = 1;
  const Int_t kMaxcaloJetEmFrac = 1;
  const Int_t kMaxcaloJetn90 = 1;
  const Int_t kMaxid1_pdfInfo = 1;
  const Int_t kMaxid2_pdfInfo = 1;
  const Int_t kMaxx1_pdfInfo = 1;
  const Int_t kMaxx2_pdfInfo = 1;
  const Int_t kMaxscalePDF_pdfInfo = 1;
  const Int_t kMaxptHat = 1;
  const Int_t kMaxmcWeight = 1;
  const Int_t kMaxmcWeights = 1;
  const Int_t kMaxwtot_write = 1;

  // Declaration of leaf types
  vector<double>  *patPfCandPt;
  vector<double>  *patPfCandEta;
  vector<double>  *patPfCandPhi;
  vector<double>  *patPfCandE;
  vector<double>  *patPfCandM;
  vector<double>  *patPfCandPx;
  vector<double>  *patPfCandPhiAtVtx;
  vector<double>  *patPfCandLostInnerHits;
  vector<double>  *patPfCandTrackHighPurity;
  vector<double>  *patPfCandPuppiWeight;
  vector<double>  *patPfCandPuppiWeightNolep;
  vector<double>  *patPfCandCharge;
  vector<double>  *patPfCandDxy;
  vector<double>  *patPfCandDxyerr;
  vector<double>  *patPfCandDz;
  vector<double>  *patPfCandDzAssociatedPV;
  vector<double>  *patPfCandDzerr;
  vector<double>  *patPfCandFromPv;
  vector<double>  *patPfCandVertexRef;
   vector<double>  *patPfpvAssociationQuality; 
 vector<double>  *METPt;
  vector<double>  *METPx;
  vector<double>  *METPy;
  vector<double>  *METPz;
  vector<double>  *METE;
  vector<double>  *METsigx2;
  vector<double>  *METsigxy;
  vector<double>  *METsigy2;
  vector<double>  *METsig;
  UInt_t          event;
  Int_t           realdata;
  UInt_t          run;
  UInt_t          lumi;
  Int_t           bxnumber;
  Double_t        EvtInfo_NumVtx;
  Double_t        PU_npT;
  Double_t        PU_npIT;
  Double_t        MyWeight;
  vector<double>  *Dr01LepPt;
  vector<double>  *Dr01LepEta;
  vector<double>  *Dr01LepPhi;
  vector<double>  *Dr01LepE;
  vector<double>  *Dr01LepM;
  vector<double>  *Dr01LepId;
  vector<double>  *Dr01LepStatus;
  vector<double>  *Dr01LepMomId;
  vector<bool>     *Dr01LepIsPrompt;
  vector<bool>     *Dr01LepIsTauProd;

   vector<double>  *Packed01Pt;
   vector<double>  *Packed01Eta;
   vector<double>  *Packed01Phi;
   vector<double>  *Packed01E;
   vector<double>  *Packed01M;
   vector<double>  *Packed01Id;
   vector<double>  *Packed01Status;
   vector<double>  *Packed01MomId;
  vector<bool>     *Packed01IsPrompt;
  vector<bool>     *Packed01IsTauProd;
  vector<double>     *Packed01Charge;

  vector<double>  *Bare01LepPt;
  vector<double>  *Bare01LepEta;
  vector<double>  *Bare01LepPhi;
  vector<double>  *Bare01LepE;
  vector<double>  *Bare01LepM;
  vector<double>  *Bare01LepId;
  vector<double>  *Bare01LepStatus;
  vector<double>  *Bare01LepMomId;
  vector<double>  *St03Pt;
  vector<double>  *St03Eta;
  vector<double>  *St03Phi;
  vector<double>  *St03E;
  vector<double>  *St03M;
  vector<double>  *St03Id;
  vector<double>  *St03Status;
  vector<double>  *St03MotherId;
  vector<double>  *St03NumberMom;
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
   vector<double> *GjConstId;
   vector<double> *GjConstPt;
  vector<double>  *GjConstCharge;
   vector<double> *GjConstEta;
   vector<double> *GjConstPhi;
   vector<double> *GjConstE;
   vector<double> *GjNConst;
   vector<double> *pseudoTop_const_pt;
   vector<double> *pseudoTop_const_eta;
   vector<double> *pseudoTop_const_phi;
   vector<double> *pseudoTop_const_energy;
   vector<double> *pseudoTop_const_pdgId;
   vector<double> *pseudoTop_const_charge;
   vector<double> *pseudoTop_pt;
   vector<double> *pseudoTop_eta;
   vector<double> *pseudoTop_phi;
   vector<double> *pseudoTop_energy;
   vector<double> *pseudoTop_pdgId;
   vector<double> *pseudoTop_charge;

  vector<bool>    *matchGjet;
  vector<double>  *MGjPt;
  vector<double>  *MGjeta;
  vector<double>  *MGjphi;
  vector<double>  *MGjE;
  Double_t        HLT_Mu17_Mu8;
  Double_t        HLT_Mu17_TkMu8;
  Double_t        HLT_Elec17_Elec8;
  Double_t        HLT_IsoMu24_eta2p1;
  Double_t  HLT_IsoMu17_eta2p1;
  Double_t  HLT_IsoMu20;
  Double_t  HLT_IsoMu20_eta2p1;
  Double_t  HLT_IsoTkMu20;
  Double_t  HLT_IsoTkMu20_eta2p1;
  Double_t  HLT_Mu20;
  Double_t  HLT_TkMu20;


  Double_t  HLT_IsoMu18;
  Double_t  HLT_IsoMu18_eta2p1;
  Double_t  HLT_IsoTkMu18;
  Double_t  HLT_IsoTkMu18_eta2p1;
  Double_t  HLT_Mu18;
  Double_t  HLT_TkMu18;

  vector<double>  *patMuonPt_;
  vector<double>  *patMuonEta_;
  vector<double>  *patMuonPhi_;
  vector<double>  *patMuonVtxZ_;
  vector<double>  *patMuonEn_;
  vector<double>  *patMuonCharge_;
  vector<double>  *patMuonDxy_;
  vector<double>  *patMuonCombId_;
  vector<double>  *patMuonLooseId_;
  vector<double>  *patMuonMediumId_;
  vector<double>  *patMuonTightId_;
  vector<double>  *patMuonTrig_;
  vector<double>  *patMuonDetIsoRho_;
  vector<double>  *patMuonPfIsoDbeta_;
  vector<double>  *patMuonM_;
  vector<double>  *patMuonPx_;
  vector<double>  *patMuonPy_;
  vector<double>  *patMuonPz_;
  vector<double>  *patMuonGlobalType_;
  vector<double>  *patMuonTrackerType_;
  vector<double>  *patMuonPFType_;
  vector<double>  *patMuonIsoSumPt_;
  vector<double>  *patMuonIsoRelative_;
  vector<double>  *patMuonIsoCalComb_;
  vector<double>  *patMuonIsoDY_;
  vector<double>  *patMuonChi2Ndoff_;
  vector<double>  *patMuonNhits_;
  vector<double>  *patMuonNMatches_;
  vector<double>  *patMuonDz_;
  vector<double>  *patMuonPhits_;
  vector<double>  *patMuonTkLayers_;
  vector<double>  *patMuon_PF_IsoSumChargedHadronPt_;
  vector<double>  *patMuon_PF_IsoSumNeutralHadronEt_;
  vector<double>  *patMuon_PF_IsoDY_;
  vector<double>  *patMuon_Mu17_Mu8_Matched_;
  vector<double>  *patMuon_Mu17_TkMu8_Matched_;
  vector<unsigned int> *patElecId_;
  vector<double>  *patElecdEtaIn_;
  vector<double>  *patElecdPhiIn_;
  vector<double>  *patElechOverE_;
  vector<double>  *patElecsigmaIetaIeta_;
  vector<double>  *patElecfull5x5_sigmaIetaIeta_;
  vector<double>  *patElecooEmooP_;
  vector<double>  *patElecd0_;
  vector<double>  *patElecdz_;
  vector<int>     *patElecexpectedMissingInnerHits_;
  vector<int>     *patElecpassConversionVeto_;
  vector<double>  *patElecTrig_;
  vector<double>  *patElecDz_;
  vector<double>  *patElecMVATrigId_;
  vector<double>  *patElecMVANonTrigId_;
  vector<double>  *patElecPt_;
  vector<double>  *patElecEta_;
  vector<double>  *patElecScEta_;
  vector<double>  *patElecPhi_;
  vector<double>  *patElecEnergy_;
  vector<double>  *patElecCharge_;
  vector<double>  *patElecMediumIDOff_;
  vector<double>  *patElecMediumIDOff_Tom_;
  vector<double>  *patElecchIso03_;
  vector<double>  *patElecnhIso03_;
  vector<double>  *patElecphIso03_;
  vector<double>  *patElecpuChIso03_;
  vector<double>  *patElecPfIso_;
  vector<double>  *patElecPfIsodb_;
  vector<double>  *patElecPfIsoRho_;
  Double_t        rhoPrime;
  vector<double>  *neutral_;
  vector<double>  *photon_;
  vector<double>  *charged_;
  vector<double>  *neutral_Tom_;
  vector<double>  *photon_Tom_;
  vector<double>  *charged_Tom_;
  Double_t        AEff;
  vector<double>  *patElec_mva_presel_;
  vector<double>  *patJetPfAk04En_;
  vector<double>  *patJetPfAk04Pt_;
  vector<double>  *patJetPfAk04Eta_;
  vector<double>  *patJetPfAk04Phi_;
  vector<double>  *patJetPfAk04LooseId_;
  vector<double>  *patJetPfAk04Et_;
  vector<double>  *patJetPfAk04PartonFlavour_;
  vector<double>  *patJetPfAk04RawPt_;
  vector<double>  *patJetPfAk04RawEn_;
  vector<double>  *patJetPfAk04HadEHF_;
  vector<double>  *patJetPfAk04EmEHF_;
  vector<double>  *patJetPfAk04chf_;
  vector<double>  *patJetPfAk04nhf_;
  vector<double>  *patJetPfAk04cemf_;
  vector<double>  *patJetPfAk04nemf_;
  vector<double>  *patJetPfAk04cmult_;
  vector<double>  *patJetPfAk04nconst_;
  vector<double>  *patJetPfAk04jetBeta_;
  vector<double>  *patJetPfAk04jetBetaClassic_;
  vector<double>  *patJetPfAk04jetBetaStar_;
  vector<double>  *patJetPfAk04jetBetaStarClassic_;
  vector<double>  *patJetPfAk04jetpuMVA_;
  vector<bool>    *patJetPfAk04jetpukLoose_;
  vector<bool>    *patJetPfAk04jetpukMedium_;
  vector<bool>    *patJetPfAk04jetpukTight_;
  vector<double>  *patJetPfAk04BDiscCSVv2_;
  vector<double>  *patJetPfAk04BDiscCSVV1_;
  vector<double>  *patJetPfAk04BDiscCSVSLV1_;
  vector<double>  *unc_;
  vector<double>  *patJetPfAk04PtUp_;
  vector<double>  *patJetPfAk04PtDn_;
  vector<double>  *patJetPfAk04ConstId;
  vector<double>  *patJetPfAk04ConstPt;
  vector<double>  *patJetPfAk04ConstCharge;
  vector<double>  *patJetPfAk04ConstEta;
  vector<double>  *patJetPfAk04ConstPhi;
  vector<double>  *patJetPfAk04ConstE;
  vector<double>  *caloJetPt_;
  vector<double>  *caloJetRawPt_;
  vector<double>  *caloJetEn_;
  vector<double>  *caloJetEta_;
  vector<double>  *caloJetPhi_;
  vector<double>  *caloJetHadEHF_;
  vector<double>  *caloJetEmEHF_;
  vector<double>  *caloJetEmFrac_;
  vector<double>  *caloJetn90_;
  vector<double>  *id1_pdfInfo_;
  vector<double>  *id2_pdfInfo_;
  vector<double>  *x1_pdfInfo_;
  vector<double>  *x2_pdfInfo_;
  vector<double>  *scalePDF_pdfInfo_;
  Double_t        ptHat_;
  Double_t        mcWeight_;
  vector<double>  *mcWeights_;
  Double_t  wtot_write;
  Double_t        nup;

  // List of branches
  TBranch        *b_patPfCandPt;   //!
  TBranch        *b_patPfCandEta;   //!
  TBranch        *b_patPfCandPhi;   //!
  TBranch        *b_patPfCandE;   //!
  TBranch        *b_patPfCandM;   //!
  TBranch        *b_patPfCandPx;   //!
  TBranch        *b_patPfCandPhiAtVtx;   //!
  TBranch        *b_patPfCandLostInnerHits;   //!
  TBranch        *b_patPfCandTrackHighPurity;   //!
  TBranch        *b_patPfCandPuppiWeight;   //!
  TBranch        *b_patPfCandPuppiWeightNolep;   //!
  TBranch        *b_patPfCandCharge;   //!
  TBranch        *b_patPfCandDxy;   //!
  TBranch        *b_patPfCandDxyerr;   //!
  TBranch        *b_patPfCandDz;   //!
  TBranch        *b_patPfCandDzAssociatedPV;   //!
  TBranch        *b_patPfCandDzerr;   //!
  TBranch        *b_patPfCandFromPv;
  TBranch        *b_patPfCandVertexRef;
   TBranch        *b_patPfpvAssociationQuality;
  TBranch        *b_METPt;   //!
  TBranch        *b_METPx;   //!
  TBranch        *b_METPy;   //!
  TBranch        *b_METPz;   //!
  TBranch        *b_METE;   //!
  TBranch        *b_METsigx2;   //!
  TBranch        *b_METsigxy;   //!
  TBranch        *b_METsigy2;   //!
  TBranch        *b_METsig;   //!
  TBranch        *b_event;   //!
  TBranch        *b_realdata;   //!
  TBranch        *b_run;   //!
  TBranch        *b_lumi;   //!
  TBranch        *b_bxnumber;   //!
  TBranch        *b_EvtInfo_NumVtx;   //!
  TBranch        *b_PU_npT;   //!
  TBranch        *b_PU_npIT;   //!
  TBranch        *b_MyWeight;   //!
  TBranch        *b_Dr01LepPt;   //!
  TBranch        *b_Dr01LepEta;   //!
  TBranch        *b_Dr01LepPhi;   //!
  TBranch        *b_Dr01LepE;   //!
  TBranch        *b_Dr01LepM;   //!
  TBranch        *b_Dr01LepId;   //!
  TBranch        *b_Dr01LepStatus;   //!
  TBranch        *b_Dr01LepMomId;   //!
   TBranch        *b_Dr01LepIsPrompt;
   TBranch        *b_Dr01LepIsTauProd;
   TBranch        *b_Packed01Pt;   //!
   TBranch        *b_Packed01Eta;   //!
   TBranch        *b_Packed01Phi;   //!
   TBranch        *b_Packed01E;   //!
   TBranch        *b_Packed01M;   //!
   TBranch        *b_Packed01Id;   //!
   TBranch        *b_Packed01Status;   //!
   TBranch        *b_Packed01MomId;   //!
   TBranch        *b_Packed01IsPrompt;
   TBranch        *b_Packed01IsTauProd;
   TBranch        *b_Packed01Charge;
  TBranch        *b_Bare01LepPt;   //!
  TBranch        *b_Bare01LepEta;   //!
  TBranch        *b_Bare01LepPhi;   //!
  TBranch        *b_Bare01LepE;   //!
  TBranch        *b_Bare01LepM;   //!
  TBranch        *b_Bare01LepId;   //!
  TBranch        *b_Bare01LepStatus;   //!
  TBranch        *b_Bare01LepMomId;   //!
  TBranch        *b_St03Pt;   //!
  TBranch        *b_St03Eta;   //!
  TBranch        *b_St03Phi;   //!
  TBranch        *b_St03E;   //!
  TBranch        *b_St03M;   //!
  TBranch        *b_St03Id;   //!
  TBranch        *b_St03Status;   //!
  TBranch        *b_St03MotherId;   //!
  TBranch        *b_St03NumberMom;   //!
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
   TBranch        *b_GjConstId;
   TBranch        *b_GjConstPt;
   TBranch        *b_GjConstCharge;
   TBranch        *b_GjConstEta;
   TBranch        *b_GjConstPhi;
   TBranch        *b_GjConstE;
   TBranch        *b_GjNConst;
   TBranch        *b_pseudoTop_const_pt;
   TBranch        *b_pseudoTop_const_eta;
   TBranch        *b_pseudoTop_const_phi;
   TBranch        *b_pseudoTop_const_energy;
   TBranch        *b_pseudoTop_const_pdgId;
   TBranch        *b_pseudoTop_const_charge;

   TBranch        *b_pseudoTop_pt;
   TBranch        *b_pseudoTop_eta;
   TBranch        *b_pseudoTop_phi;
   TBranch        *b_pseudoTop_energy;
   TBranch        *b_pseudoTop_pdgId;
   TBranch        *b_pseudoTop_charge;

  TBranch        *b_matchGjet;   //!
  TBranch        *b_MGjPt;   //!
  TBranch        *b_MGjeta;   //!
  TBranch        *b_MGjphi;   //!
  TBranch        *b_MGjE;   //!
  TBranch        *b_HLT_Mu17_Mu8;   //!
  TBranch        *b_HLT_Mu17_TkMu8;   //!
  TBranch        *b_HLT_Elec17_Elec8;   //!
  TBranch        *b_HLT_IsoMu24_eta2p1;   //!
  TBranch        *b_HLT_IsoMu17_eta2p1;
  TBranch        *b_HLT_IsoMu20;
  TBranch        *b_HLT_IsoMu20_eta2p1;
  TBranch        *b_HLT_IsoTkMu20;
  TBranch        *b_HLT_IsoTkMu20_eta2p1;
  TBranch        *b_HLT_Mu20;
  TBranch        *b_HLT_TkMu20;


  TBranch        *b_HLT_IsoMu18;
  TBranch        *b_HLT_IsoMu18_eta2p1;
  TBranch        *b_HLT_IsoTkMu18;
  TBranch        *b_HLT_IsoTkMu18_eta2p1;
  TBranch        *b_HLT_Mu18;
  TBranch        *b_HLT_TkMu18;

  TBranch        *b_patMuonPt_;   //!
  TBranch        *b_patMuonEta_;   //!
  TBranch        *b_patMuonPhi_;   //!
  TBranch        *b_patMuonVtxZ_;   //!
  TBranch        *b_patMuonEn_;   //!
  TBranch        *b_patMuonCharge_;   //!
  TBranch        *b_patMuonDxy_;   //!
  TBranch        *b_patMuonCombId_;   //!
  TBranch        *b_patMuonLooseId_;   //!
  TBranch        *b_patMuonMediumId_;   //!
  TBranch        *b_patMuonTightId_;   //!
  TBranch        *b_patMuonTrig_;   //!
  TBranch        *b_patMuonDetIsoRho_;   //!
  TBranch        *b_patMuonPfIsoDbeta_;   //!
  TBranch        *b_patMuonM_;   //!
  TBranch        *b_patMuonPx_;   //!
  TBranch        *b_patMuonPy_;   //!
  TBranch        *b_patMuonPz_;   //!
  TBranch        *b_patMuonGlobalType_;   //!
  TBranch        *b_patMuonTrackerType_;   //!
  TBranch        *b_patMuonPFType_;   //!
  TBranch        *b_patMuonIsoSumPt_;   //!
  TBranch        *b_patMuonIsoRelative_;   //!
  TBranch        *b_patMuonIsoCalComb_;   //!
  TBranch        *b_patMuonIsoDY_;   //!
  TBranch        *b_patMuonChi2Ndoff_;   //!
  TBranch        *b_patMuonNhits_;   //!
  TBranch        *b_patMuonNMatches_;   //!
  TBranch        *b_patMuonDz_;   //!
  TBranch        *b_patMuonPhits_;   //!
  TBranch        *b_patMuonTkLayers_;   //!
  TBranch        *b_patMuon_PF_IsoSumChargedHadronPt_;   //!
  TBranch        *b_patMuon_PF_IsoSumNeutralHadronEt_;   //!
  TBranch        *b_patMuon_PF_IsoDY_;   //!
  TBranch        *b_patMuon_Mu17_Mu8_Matched_;   //!
  TBranch        *b_patMuon_Mu17_TkMu8_Matched_;   //!
  TBranch        *b_patElecId_;   //!
  TBranch        *b_patElecdEtaIn_;   //!
  TBranch        *b_patElecdPhiIn_;   //!
  TBranch        *b_patElechOverE_;   //!
  TBranch        *b_patElecsigmaIetaIeta_;   //!
  TBranch        *b_patElecfull5x5_sigmaIetaIeta_;   //!
  TBranch        *b_patElecooEmooP_;   //!
  TBranch        *b_patElecd0_;   //!
  TBranch        *b_patElecdz_;   //!
  TBranch        *b_patElecexpectedMissingInnerHits_;   //!
  TBranch        *b_patElecpassConversionVeto_;   //!
  TBranch        *b_patElecTrig_;   //!
  TBranch        *b_patElecDz_;   //!
  TBranch        *b_patElecMVATrigId_;   //!
  TBranch        *b_patElecMVANonTrigId_;   //!
  TBranch        *b_patElecPt_;   //!
  TBranch        *b_patElecEta_;   //!
  TBranch        *b_patElecScEta_;   //!
  TBranch        *b_patElecPhi_;   //!
  TBranch        *b_patElecEnergy_;   //!
  TBranch        *b_patElecCharge_;   //!
  TBranch        *b_patElecMediumIDOff_;   //!
  TBranch        *b_patElecMediumIDOff_Tom_;   //!
  TBranch        *b_patElecchIso03_;   //!
  TBranch        *b_patElecnhIso03_;   //!
  TBranch        *b_patElecphIso03_;   //!
  TBranch        *b_patElecpuChIso03_;   //!
  TBranch        *b_patElecPfIso_;   //!
  TBranch        *b_patElecPfIsodb_;   //!
  TBranch        *b_patElecPfIsoRho_;   //!
  TBranch        *b_rhoPrime;   //!
  TBranch        *b_neutral_;   //!
  TBranch        *b_photon_;   //!
  TBranch        *b_charged_;   //!
  TBranch        *b_neutral_Tom_;   //!
  TBranch        *b_photon_Tom_;   //!
  TBranch        *b_charged_Tom_;   //!
  TBranch        *b_AEff;   //!
  TBranch        *b_patElec_mva_presel_;   //!
  TBranch        *b_patJetPfAk04En_;   //!
  TBranch        *b_patJetPfAk04Pt_;   //!
  TBranch        *b_patJetPfAk04Eta_;   //!
  TBranch        *b_patJetPfAk04Phi_;   //!
  TBranch        *b_patJetPfAk04LooseId_;   //!
  TBranch        *b_patJetPfAk04Et_;   //!
  TBranch        *b_patJetPfAk04PartonFlavour_;
  TBranch        *b_patJetPfAk04RawPt_;   //!
  TBranch        *b_patJetPfAk04RawEn_;   //!
  TBranch        *b_patJetPfAk04HadEHF_;   //!
  TBranch        *b_patJetPfAk04EmEHF_;   //!
  TBranch        *b_patJetPfAk04chf_;   //!
  TBranch        *b_patJetPfAk04nhf_;   //!
  TBranch        *b_patJetPfAk04cemf_;   //!
  TBranch        *b_patJetPfAk04nemf_;   //!
  TBranch        *b_patJetPfAk04cmult_;   //!
  TBranch        *b_patJetPfAk04nconst_;   //!
  TBranch        *b_patJetPfAk04jetBeta_;   //!
  TBranch        *b_patJetPfAk04jetBetaClassic_;   //!
  TBranch        *b_patJetPfAk04jetBetaStar_;   //!
  TBranch        *b_patJetPfAk04jetBetaStarClassic_;   //!
  TBranch        *b_patJetPfAk04jetpuMVA_;   //!
  TBranch        *b_patJetPfAk04jetpukLoose_;   //!
  TBranch        *b_patJetPfAk04jetpukMedium_;   //!
  TBranch        *b_patJetPfAk04jetpukTight_;   //!
  TBranch        *b_patJetPfAk04BDiscCSVv2_;   //!
  TBranch        *b_patJetPfAk04BDiscCSVV1_;   //!
  TBranch        *b_patJetPfAk04BDiscCSVSLV1_;   //!
  TBranch        *b_unc_;   //!
  TBranch        *b_patJetPfAk04PtUp_;   //!
  TBranch        *b_patJetPfAk04PtDn_;   //!
  TBranch        *b_patJetPfAk04ConstId;   //!
  TBranch        *b_patJetPfAk04ConstPt;   //!
   TBranch        *b_patJetPfAk04ConstCharge;
  TBranch        *b_patJetPfAk04ConstEta;   //!
  TBranch        *b_patJetPfAk04ConstPhi;   //!
  TBranch        *b_patJetPfAk04ConstE;   //!
  TBranch        *b_caloJetPt_;   //!
  TBranch        *b_caloJetRawPt_;   //!
  TBranch        *b_caloJetEn_;   //!
  TBranch        *b_caloJetEta_;   //!
  TBranch        *b_caloJetPhi_;   //!
  TBranch        *b_caloJetHadEHF_;   //!
  TBranch        *b_caloJetEmEHF_;   //!
  TBranch        *b_caloJetEmFrac_;   //!
  TBranch        *b_caloJetn90_;   //!
  TBranch        *b_id1_pdfInfo_;   //!
  TBranch        *b_id2_pdfInfo_;   //!
  TBranch        *b_x1_pdfInfo_;   //!
  TBranch        *b_x2_pdfInfo_;   //!
  TBranch        *b_scalePDF_pdfInfo_;   //!
  TBranch        *b_ptHat_;   //!
  TBranch        *b_mcWeight_;   //!
  TBranch        *b_mcWeights_;   //!
  TBranch        *b_wtot_write;
  TBranch        *b_nup;   //!

  tt_uev_analyzer(TTree *tree=0);
  virtual ~tt_uev_analyzer();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  virtual double    DeltaR(double entry1, double entry2, double entry3, double entry4);
  virtual double    DeltaPhi(double entry1, double entry2);
  virtual bool    hasb(int entry1);
  TString name;
  bool dottother=false;
  bool dosignal=false;
  bool dopdf=false;
  bool doe=false;
  int nev=-1;
  int idd=13;
  int jes=0;
  double pi = 3.1415926535897932384626433832795028841971693;
};

#endif

#ifdef tt_uev_analyzer_cxx
tt_uev_analyzer::tt_uev_analyzer(TTree *tree) : fChain(0) 
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
    f->GetObject("tupel/MuonTree",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
    TChain * chain = new TChain("tupel/MuonTree","");
    if(doe)idd=11;
    /*
    #include "25ns_data_D_prompt_local.h"
    #include "25ns_data_D_reminiaod_local.h"
    name="25ns_data_D_uev_newlist_20160307_fromskimmed";
    */
    /*  
    #include "25ns_wjet_local.h"
    name="25ns_wjet_uev_miniaodv2_20160307_fromskimmed";
    */
    /*
    #include "25ns_tt_local.h"
    dosignal=true;
    nev=1000000;
    name="25ns_tt_uev_miniaodv2_20160307_fromskimmed";
    */
    /*
    #include "25ns_st_t_top_uev_local.h"
    name="25ns_st_t_top_uev_20160307_fromskimmed";
    */
    /*
    #include "25ns_st_t_atop_uev_local.h"
    name="25ns_st_t_atop_uev_20160307_fromskimmed";
    */
    /*
    #include "25ns_st_tw_atop_uev_local.h"
    name="25ns_st_tw_top_uev_20160307_fromskimmed";
    */
    /*
    #include "25ns_st_tw_top_uev_local.h"
    name="25ns_st_tw_atop_uev_20160307_fromskimmed";
    */
    /*
    #include "25ns_powheg_hpp_local.h"
    name="powheg_hpp";
    */
    /*
    #include "25ns_powheg_sdn_local.h"
    name="powheg_sdn";
    */
    /*
    #include "25ns_powheg_sup_local.h"
    name="powheg_up";
    */
    /*
    #include "25ns_data_D_prompt_local.h"
    #include "25ns_data_D_reminiaod_local.h"
    name="25ns_data_D_uev_newlist_2110_fromskimmed_jes_1";
    jes=1;
    */


    /*
    #include "25ns_data_D_prompt_local.h"
    #include "25ns_data_D_reminiaod_local.h"
    name="25ns_data_D_uev_newlist_2110_fromskimmed_jes_-1";
    jes=-1;
    */


    
    #include "25ns_tt_local.h"
    nev=1000000;
    dosignal=true;
    dopdf=true;
    name="25ns_tt_uev_miniaodv2_2110_fromskimmed_pdfvar";
    
















/*    
      chain->Add("/sdb4/Bugra/skimmed/25ns_data_D_reminiaod.root");
//      chain->Add("/sdb4/Bugra/skimmed/25ns_data_D_prompt.root");
      name="25ns_data_D_uev_newlist_2110_fromskimmed";
    
*/

 /*  
      chain->Add("/sdb2/Bugra/skimmed/25ns_data_D_reminiaod_jecv7.root");
//      chain->Add("/sdb2/Bugra/skimmed/25ns_data_D_prompt_jecv7.root");
      name="25ns_data_D_uev_newlist_2110_fromskimmed_jecv7";
    
*/

    /*
      chain->Add("/sdb2/Bugra/skimmed/25ns_data_D_reminiaod_jecv6.root");
//      chain->Add("/sdb2/Bugra/skimmed/25ns_data_D_prompt_jecv6.root");
      name="25ns_data_D_uev_newlist_2110_fromskimmed_jecv6";

*/

    /*
      chain->Add("/sdb5/Bugra/skimmed/25ns_wjet.root");
      name="25ns_wjet_uev_miniaodv2_2110_fromskimmed";
    */
    
//    chain->Add("/sdb2/Bugra/skimmed/25ns_tt_.root");
//    chain->Add("/sdb2/Bugra/skimmed/25ns_tt__1.root");
//    chain->Add("/sdb2/Bugra/skimmed/25ns_tt__2.root");
//    chain->Add("/sdb2/Bugra/skimmed/25ns_tt__3.root");

//    #include "25ns_tt_uev_miniaodv2_0202_forskimmer.h"
//    chain->Add("/sdb4/Bugra/skimmed/withJEC_DYJetsToLL_ntuple_13.root");
/*    chain->Add("/sdb4/Bugra/skimmed/TT_TuneCUETP8M1_13TeV-powheg-pythia8/withJEC_DYJetsToLL_ntuple_1.root");
    chain->Add("/sdb4/Bugra/skimmed/TT_TuneCUETP8M1_13TeV-powheg-pythia8/withJEC_DYJetsToLL_ntuple_10.root");
    chain->Add("/sdb4/Bugra/skimmed/TT_TuneCUETP8M1_13TeV-powheg-pythia8/withJEC_DYJetsToLL_ntuple_100.root");
    chain->Add("/sdb4/Bugra/skimmed/TT_TuneCUETP8M1_13TeV-powheg-pythia8/withJEC_DYJetsToLL_ntuple_101.root");
    chain->Add("/sdb4/Bugra/skimmed/TT_TuneCUETP8M1_13TeV-powheg-pythia8/withJEC_DYJetsToLL_ntuple_102.root");
    chain->Add("/sdb4/Bugra/skimmed/TT_TuneCUETP8M1_13TeV-powheg-pythia8/withJEC_DYJetsToLL_ntuple_103.root");
    chain->Add("/sdb4/Bugra/skimmed/TT_TuneCUETP8M1_13TeV-powheg-pythia8/withJEC_DYJetsToLL_ntuple_105.root");
    chain->Add("/sdb4/Bugra/skimmed/TT_TuneCUETP8M1_13TeV-powheg-pythia8/withJEC_DYJetsToLL_ntuple_106.root");
    chain->Add("/sdb4/Bugra/skimmed/TT_TuneCUETP8M1_13TeV-powheg-pythia8/withJEC_DYJetsToLL_ntuple_107.root");
    chain->Add("/sdb4/Bugra/skimmed/TT_TuneCUETP8M1_13TeV-powheg-pythia8/withJEC_DYJetsToLL_ntuple_108.root");
    chain->Add("/sdb4/Bugra/skimmed/TT_TuneCUETP8M1_13TeV-powheg-pythia8/withJEC_DYJetsToLL_ntuple_109.root");
    chain->Add("/sdb4/Bugra/skimmed/TT_TuneCUETP8M1_13TeV-powheg-pythia8/withJEC_DYJetsToLL_ntuple_11.root");
    chain->Add("/sdb4/Bugra/skimmed/TT_TuneCUETP8M1_13TeV-powheg-pythia8/withJEC_DYJetsToLL_ntuple_110.root");
    chain->Add("/sdb4/Bugra/skimmed/TT_TuneCUETP8M1_13TeV-powheg-pythia8/withJEC_DYJetsToLL_ntuple_111.root");
    chain->Add("/sdb4/Bugra/skimmed/TT_TuneCUETP8M1_13TeV-powheg-pythia8/withJEC_DYJetsToLL_ntuple_112.root");
    chain->Add("/sdb4/Bugra/skimmed/TT_TuneCUETP8M1_13TeV-powheg-pythia8/withJEC_DYJetsToLL_ntuple_113.root");
    chain->Add("/sdb4/Bugra/skimmed/TT_TuneCUETP8M1_13TeV-powheg-pythia8/withJEC_DYJetsToLL_ntuple_114.root");

    dosignal=true;
    name="25ns_tt_uev_miniaodv2_2110_fromskimmed";
   */ 
/*
    chain->Add("../Sskimmed.root");
    dosignal=true;
    name="25ns_tt_uev_miniaodv2_2110_skimmedversion";
*/
/*
    chain->Add("../Snotskimmed.root");
    dosignal=true;
    name="25ns_tt_uev_miniaodv2_2110_nonskimmedversion";
*/
    /*
      chain->Add("/sdb4/Bugra/skimmed/25ns_st_t_top.root");
      name="25ns_st_t_top_uev_2110_fromskimmed";
    */
    /*
      chain->Add("/sdb4/Bugra/skimmed/25ns_st_t_atop.root");
      name="25ns_st_t_atop_uev_2110_fromskimmed";
    */
    /*
      chain->Add("/sdb4/Bugra/skimmed/25ns_st_tw_atop.root");
      name="25ns_st_tw_atop_uev_2110_fromskimmed";
    */
    /*
      chain->Add("/sdb4/Bugra/skimmed/25ns_st_tw_top.root");
      name="25ns_st_tw_top_uev_2110_fromskimmed";
    */
    /*
      chain->Add("/sdb4/Bugra/skimmed/powheg_hpp.root");
      name="powheg_hpp";
    */
    /*
      chain->Add("/sdb4/Bugra/skimmed/powheg_sdn.root");
      name="powheg_sdn";
    */
  /*  
      chain->Add("/sdb4/Bugra/skimmed/powheg_up.root");
      name="powheg_up";
    
*/

    /*
      chain->Add("/sdb4/Bugra/skimmed/25ns_data_D_reminiaod.root");
      chain->Add("/sdb4/Bugra/skimmed/25ns_data_D_prompt.root");
      name="25ns_data_D_uev_newlist_2110_fromskimmed_jes_1";
      jes=1;
    */


    /*
      chain->Add("/sdb4/Bugra/skimmed/25ns_data_D_reminiaod.root");
      chain->Add("/sdb4/Bugra/skimmed/25ns_data_D_prompt.root");
      name="25ns_data_D_uev_newlist_2110_fromskimmed_jes_-1";
      jes=-1;
    */

    /*
      chain->Add("/sdb5/Bugra/skimmed/25ns_tt_.root");
      chain->Add("/sdb5/Bugra/skimmed/25ns_tt__1.root");
      chain->Add("/sdb5/Bugra/skimmed/25ns_tt__2.root");
      chain->Add("/sdb5/Bugra/skimmed/25ns_tt__3.root");
      dosignal=true;
      dopdf=true;
      name="25ns_tt_uev_miniaodv2_2110_fromskimmed_pdfvar";
    */



//    std::cout<<"aaaaa"<<std::endl;
/*
    chain->Add("/sdb3/Bugra/skimmed/25ns_tt_50k_newcut.root");
    dosignal=true;
    name="25ns_tt_uev_miniaodv2_2110_fromskimmed_small";
*/
/*
    chain->Add("/sdb2/Bugra/skimmed/25ns_tt_small_getcorr.root");
    dosignal=true;
    name="25ns_tt_uev_miniaodv2_2110_fromskimmed_small_newjec";
*/

    tree = chain;

    name += "_isElec_";
    name += doe;
    name += "_v24.root";
#endif // SINGLE_TREE

  }
  Init(tree);
}

tt_uev_analyzer::~tt_uev_analyzer()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t tt_uev_analyzer::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t tt_uev_analyzer::LoadTree(Long64_t entry)
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

void tt_uev_analyzer::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set object pointer
  patPfCandPt = 0;
  patPfCandEta = 0;
  patPfCandPhi = 0;
  patPfCandE = 0;
  patPfCandM = 0;
  patPfCandPx = 0;
  patPfCandPhiAtVtx = 0;
  patPfCandLostInnerHits = 0;
  patPfCandTrackHighPurity = 0;
  patPfCandPuppiWeight = 0;
  patPfCandPuppiWeightNolep = 0;
  patPfCandCharge = 0;
  patPfCandDxy = 0;
  patPfCandDxyerr = 0;
  patPfCandDz = 0;
  patPfCandDzAssociatedPV = 0;
  patPfCandDzerr = 0;
  patPfCandFromPv = 0;
patPfCandVertexRef = 0;
   patPfpvAssociationQuality = 0;
  METPt = 0;
  METPx = 0;
  METPy = 0;
  METPz = 0;
  METE = 0;
  METsigx2 = 0;
  METsigxy = 0;
  METsigy2 = 0;
  METsig = 0;
  Dr01LepPt = 0;
  Dr01LepEta = 0;
  Dr01LepPhi = 0;
  Dr01LepE = 0;
  Dr01LepM = 0;
  Dr01LepId = 0;
  Dr01LepStatus = 0;
  Dr01LepMomId = 0;
   Dr01LepIsPrompt=0;
   Dr01LepIsTauProd=0;
   Packed01Pt = 0;
   Packed01Eta = 0;
   Packed01Phi = 0;
   Packed01E = 0;
   Packed01M = 0;
   Packed01Id = 0;
   Packed01Status = 0;
   Packed01MomId = 0;
   Packed01IsPrompt=0;
   Packed01IsTauProd=0;
Packed01Charge=0;
  Bare01LepPt = 0;
  Bare01LepEta = 0;
  Bare01LepPhi = 0;
  Bare01LepE = 0;
  Bare01LepM = 0;
  Bare01LepId = 0;
  Bare01LepStatus = 0;
  Bare01LepMomId = 0;
  St03Pt = 0;
  St03Eta = 0;
  St03Phi = 0;
  St03E = 0;
  St03M = 0;
  St03Id = 0;
  St03Status = 0;
  St03MotherId = 0;
  St03NumberMom = 0;
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
   matchGjet = 0;
GjNConst = 0;
      GjConstId = 0;
      GjConstPt = 0;
GjConstCharge = 0;
      GjConstEta = 0;
      GjConstPhi = 0;
      GjConstE = 0;
GjNConst = 0;
pseudoTop_const_pt = 0;
pseudoTop_const_eta = 0;
pseudoTop_const_phi = 0;
pseudoTop_const_energy = 0;
pseudoTop_const_pdgId = 0;
pseudoTop_const_charge = 0;

pseudoTop_pt = 0;
pseudoTop_eta = 0;
pseudoTop_phi = 0;
pseudoTop_energy = 0;
pseudoTop_pdgId = 0;
pseudoTop_charge = 0;

  MGjPt = 0;
  MGjeta = 0;
  MGjphi = 0;
  MGjE = 0;
  patMuonPt_ = 0;
  patMuonEta_ = 0;
  patMuonPhi_ = 0;
  patMuonVtxZ_ = 0;
  patMuonEn_ = 0;
  patMuonCharge_ = 0;
  patMuonDxy_ = 0;
  patMuonCombId_ = 0;
  patMuonLooseId_ = 0;
  patMuonMediumId_ = 0;
  patMuonTightId_ = 0;
  patMuonTrig_ = 0;
  patMuonDetIsoRho_ = 0;
  patMuonPfIsoDbeta_ = 0;
  patMuonM_ = 0;
  patMuonPx_ = 0;
  patMuonPy_ = 0;
  patMuonPz_ = 0;
  patMuonGlobalType_ = 0;
  patMuonTrackerType_ = 0;
  patMuonPFType_ = 0;
  patMuonIsoSumPt_ = 0;
  patMuonIsoRelative_ = 0;
  patMuonIsoCalComb_ = 0;
  patMuonIsoDY_ = 0;
  patMuonChi2Ndoff_ = 0;
  patMuonNhits_ = 0;
  patMuonNMatches_ = 0;
  patMuonDz_ = 0;
  patMuonPhits_ = 0;
  patMuonTkLayers_ = 0;
  patMuon_PF_IsoSumChargedHadronPt_ = 0;
  patMuon_PF_IsoSumNeutralHadronEt_ = 0;
  patMuon_PF_IsoDY_ = 0;
  patMuon_Mu17_Mu8_Matched_ = 0;
  patMuon_Mu17_TkMu8_Matched_ = 0;
  patElecId_ = 0;
  patElecdEtaIn_ = 0;
  patElecdPhiIn_ = 0;
  patElechOverE_ = 0;
  patElecsigmaIetaIeta_ = 0;
  patElecfull5x5_sigmaIetaIeta_ = 0;
  patElecooEmooP_ = 0;
  patElecd0_ = 0;
  patElecdz_ = 0;
  patElecexpectedMissingInnerHits_ = 0;
  patElecpassConversionVeto_ = 0;
  patElecTrig_ = 0;
  patElecDz_ = 0;
  patElecMVATrigId_ = 0;
  patElecMVANonTrigId_ = 0;
  patElecPt_ = 0;
  patElecEta_ = 0;
  patElecScEta_ = 0;
  patElecPhi_ = 0;
  patElecEnergy_ = 0;
  patElecCharge_ = 0;
  patElecMediumIDOff_ = 0;
  patElecMediumIDOff_Tom_ = 0;
  patElecchIso03_ = 0;
  patElecnhIso03_ = 0;
  patElecphIso03_ = 0;
  patElecpuChIso03_ = 0;
  patElecPfIso_ = 0;
  patElecPfIsodb_ = 0;
  patElecPfIsoRho_ = 0;
  neutral_ = 0;
  photon_ = 0;
  charged_ = 0;
  neutral_Tom_ = 0;
  photon_Tom_ = 0;
  charged_Tom_ = 0;
  patElec_mva_presel_ = 0;
  patJetPfAk04En_ = 0;
  patJetPfAk04Pt_ = 0;
  patJetPfAk04Eta_ = 0;
  patJetPfAk04Phi_ = 0;
  patJetPfAk04LooseId_ = 0;
  patJetPfAk04Et_ = 0;
  patJetPfAk04PartonFlavour_=0;
  patJetPfAk04RawPt_ = 0;
  patJetPfAk04RawEn_ = 0;
  patJetPfAk04HadEHF_ = 0;
  patJetPfAk04EmEHF_ = 0;
  patJetPfAk04chf_ = 0;
  patJetPfAk04nhf_ = 0;
  patJetPfAk04cemf_ = 0;
  patJetPfAk04nemf_ = 0;
  patJetPfAk04cmult_ = 0;
  patJetPfAk04nconst_ = 0;
  patJetPfAk04jetBeta_ = 0;
  patJetPfAk04jetBetaClassic_ = 0;
  patJetPfAk04jetBetaStar_ = 0;
  patJetPfAk04jetBetaStarClassic_ = 0;
  patJetPfAk04jetpuMVA_ = 0;
  patJetPfAk04jetpukLoose_ = 0;
  patJetPfAk04jetpukMedium_ = 0;
  patJetPfAk04jetpukTight_ = 0;
  patJetPfAk04BDiscCSVv2_ = 0;
  patJetPfAk04BDiscCSVV1_ = 0;
  patJetPfAk04BDiscCSVSLV1_ = 0;
  unc_ = 0;
  patJetPfAk04PtUp_ = 0;
  patJetPfAk04PtDn_ = 0;
  patJetPfAk04ConstId = 0;
  patJetPfAk04ConstPt = 0;
patJetPfAk04ConstCharge = 0;
  patJetPfAk04ConstEta = 0;
  patJetPfAk04ConstPhi = 0;
  patJetPfAk04ConstE = 0;
  caloJetPt_ = 0;
  caloJetRawPt_ = 0;
  caloJetEn_ = 0;
  caloJetEta_ = 0;
  caloJetPhi_ = 0;
  caloJetHadEHF_ = 0;
  caloJetEmEHF_ = 0;
  caloJetEmFrac_ = 0;
  caloJetn90_ = 0;
  id1_pdfInfo_ = 0;
  id2_pdfInfo_ = 0;
  x1_pdfInfo_ = 0;
  x2_pdfInfo_ = 0;
  scalePDF_pdfInfo_ = 0;
  mcWeights_ = 0;
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("patPfCandPt", &patPfCandPt, &b_patPfCandPt);
  fChain->SetBranchAddress("patPfCandEta", &patPfCandEta, &b_patPfCandEta);
  fChain->SetBranchAddress("patPfCandPhi", &patPfCandPhi, &b_patPfCandPhi);
  fChain->SetBranchAddress("patPfCandE", &patPfCandE, &b_patPfCandE);
  fChain->SetBranchAddress("patPfCandM", &patPfCandM, &b_patPfCandM);
  fChain->SetBranchAddress("patPfCandPx", &patPfCandPx, &b_patPfCandPx);
  fChain->SetBranchAddress("patPfCandPhiAtVtx", &patPfCandPhiAtVtx, &b_patPfCandPhiAtVtx);
  fChain->SetBranchAddress("patPfCandLostInnerHits", &patPfCandLostInnerHits, &b_patPfCandLostInnerHits);
  fChain->SetBranchAddress("patPfCandTrackHighPurity", &patPfCandTrackHighPurity, &b_patPfCandTrackHighPurity);
  fChain->SetBranchAddress("patPfCandPuppiWeight", &patPfCandPuppiWeight, &b_patPfCandPuppiWeight);
  fChain->SetBranchAddress("patPfCandPuppiWeightNolep", &patPfCandPuppiWeightNolep, &b_patPfCandPuppiWeightNolep);
  fChain->SetBranchAddress("patPfCandCharge", &patPfCandCharge, &b_patPfCandCharge);
  fChain->SetBranchAddress("patPfCandDxy", &patPfCandDxy, &b_patPfCandDxy);
  fChain->SetBranchAddress("patPfCandDxyerr", &patPfCandDxyerr, &b_patPfCandDxyerr);
  fChain->SetBranchAddress("patPfCandDz", &patPfCandDz, &b_patPfCandDz);
  fChain->SetBranchAddress("patPfCandDzAssociatedPV", &patPfCandDzAssociatedPV, &b_patPfCandDzAssociatedPV);
  fChain->SetBranchAddress("patPfCandDzerr", &patPfCandDzerr, &b_patPfCandDzerr);
  fChain->SetBranchAddress("patPfCandFromPv",&patPfCandFromPv, &b_patPfCandFromPv);
  fChain->SetBranchAddress("patPfCandVertexRef",&patPfCandVertexRef, &b_patPfCandVertexRef);
    fChain->SetBranchAddress("patPfpvAssociationQuality",&patPfpvAssociationQuality, &b_patPfpvAssociationQuality);
  fChain->SetBranchAddress("METPt", &METPt, &b_METPt);
  fChain->SetBranchAddress("METPx", &METPx, &b_METPx);
  fChain->SetBranchAddress("METPy", &METPy, &b_METPy);
  fChain->SetBranchAddress("METPz", &METPz, &b_METPz);
  fChain->SetBranchAddress("METE", &METE, &b_METE);
  fChain->SetBranchAddress("METsigx2", &METsigx2, &b_METsigx2);
  fChain->SetBranchAddress("METsigxy", &METsigxy, &b_METsigxy);
  fChain->SetBranchAddress("METsigy2", &METsigy2, &b_METsigy2);
  fChain->SetBranchAddress("METsig", &METsig, &b_METsig);
  fChain->SetBranchAddress("event", &event, &b_event);
  fChain->SetBranchAddress("realdata", &realdata, &b_realdata);
  fChain->SetBranchAddress("run", &run, &b_run);
  fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
  fChain->SetBranchAddress("bxnumber", &bxnumber, &b_bxnumber);
  fChain->SetBranchAddress("EvtInfo_NumVtx", &EvtInfo_NumVtx, &b_EvtInfo_NumVtx);
  fChain->SetBranchAddress("PU_npT", &PU_npT, &b_PU_npT);
  fChain->SetBranchAddress("PU_npIT", &PU_npIT, &b_PU_npIT);
  fChain->SetBranchAddress("MyWeight", &MyWeight, &b_MyWeight);
  fChain->SetBranchAddress("Dr01LepPt", &Dr01LepPt, &b_Dr01LepPt);
  fChain->SetBranchAddress("Dr01LepEta", &Dr01LepEta, &b_Dr01LepEta);
  fChain->SetBranchAddress("Dr01LepPhi", &Dr01LepPhi, &b_Dr01LepPhi);
  fChain->SetBranchAddress("Dr01LepE", &Dr01LepE, &b_Dr01LepE);
  fChain->SetBranchAddress("Dr01LepM", &Dr01LepM, &b_Dr01LepM);
  fChain->SetBranchAddress("Dr01LepId", &Dr01LepId, &b_Dr01LepId);
  fChain->SetBranchAddress("Dr01LepStatus", &Dr01LepStatus, &b_Dr01LepStatus);
  fChain->SetBranchAddress("Dr01LepMomId", &Dr01LepMomId, &b_Dr01LepMomId);
   fChain->SetBranchAddress("Dr01LepIsPrompt",&Dr01LepIsPrompt,&b_Dr01LepIsPrompt);
   fChain->SetBranchAddress("Dr01LepIsTauProd",&Dr01LepIsTauProd,&b_Dr01LepIsTauProd);
   fChain->SetBranchAddress("Packed01Pt", &Packed01Pt, &b_Packed01Pt);
   fChain->SetBranchAddress("Packed01Eta", &Packed01Eta, &b_Packed01Eta);
   fChain->SetBranchAddress("Packed01Phi", &Packed01Phi, &b_Packed01Phi);
   fChain->SetBranchAddress("Packed01E", &Packed01E, &b_Packed01E);
   fChain->SetBranchAddress("Packed01M", &Packed01M, &b_Packed01M);
   fChain->SetBranchAddress("Packed01Id", &Packed01Id, &b_Packed01Id);
   fChain->SetBranchAddress("Packed01Status", &Packed01Status, &b_Packed01Status);
   fChain->SetBranchAddress("Packed01MomId", &Packed01MomId, &b_Packed01MomId);
   fChain->SetBranchAddress("Packed01IsPrompt",&Packed01IsPrompt,&b_Packed01IsPrompt);
   fChain->SetBranchAddress("Packed01IsTauProd",&Packed01IsTauProd,&b_Packed01IsTauProd);
   fChain->SetBranchAddress("Packed01Charge",&Packed01Charge,&b_Packed01Charge);
  fChain->SetBranchAddress("Bare01LepPt", &Bare01LepPt, &b_Bare01LepPt);
  fChain->SetBranchAddress("Bare01LepEta", &Bare01LepEta, &b_Bare01LepEta);
  fChain->SetBranchAddress("Bare01LepPhi", &Bare01LepPhi, &b_Bare01LepPhi);
  fChain->SetBranchAddress("Bare01LepE", &Bare01LepE, &b_Bare01LepE);
  fChain->SetBranchAddress("Bare01LepM", &Bare01LepM, &b_Bare01LepM);
  fChain->SetBranchAddress("Bare01LepId", &Bare01LepId, &b_Bare01LepId);
  fChain->SetBranchAddress("Bare01LepStatus", &Bare01LepStatus, &b_Bare01LepStatus);
  fChain->SetBranchAddress("Bare01LepMomId", &Bare01LepMomId, &b_Bare01LepMomId);
  fChain->SetBranchAddress("St03Pt", &St03Pt, &b_St03Pt);
  fChain->SetBranchAddress("St03Eta", &St03Eta, &b_St03Eta);
  fChain->SetBranchAddress("St03Phi", &St03Phi, &b_St03Phi);
  fChain->SetBranchAddress("St03E", &St03E, &b_St03E);
  fChain->SetBranchAddress("St03M", &St03M, &b_St03M);
  fChain->SetBranchAddress("St03Id", &St03Id, &b_St03Id);
  fChain->SetBranchAddress("St03Status", &St03Status, &b_St03Status);
  fChain->SetBranchAddress("St03MotherId", &St03MotherId, &b_St03MotherId);
  fChain->SetBranchAddress("St03NumberMom", &St03NumberMom, &b_St03NumberMom);
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
   fChain->SetBranchAddress("GjNConst",&GjNConst,&b_GjNConst);
   fChain->SetBranchAddress("pseudoTop_const_pt",&pseudoTop_const_pt,&b_pseudoTop_const_pt);
   fChain->SetBranchAddress("pseudoTop_const_eta",&pseudoTop_const_eta,&b_pseudoTop_const_eta);
   fChain->SetBranchAddress("pseudoTop_const_phi",&pseudoTop_const_phi,&b_pseudoTop_const_phi);
   fChain->SetBranchAddress("pseudoTop_const_energy",&pseudoTop_const_energy,&b_pseudoTop_const_energy);
   fChain->SetBranchAddress("pseudoTop_const_pdgId",&pseudoTop_const_pdgId,&b_pseudoTop_const_pdgId);
   fChain->SetBranchAddress("pseudoTop_const_charge",&pseudoTop_const_charge,&b_pseudoTop_const_charge);

   fChain->SetBranchAddress("pseudoTop_pt",&pseudoTop_pt,&b_pseudoTop_pt);
   fChain->SetBranchAddress("pseudoTop_eta",&pseudoTop_eta,&b_pseudoTop_eta);
   fChain->SetBranchAddress("pseudoTop_phi",&pseudoTop_phi,&b_pseudoTop_phi);
   fChain->SetBranchAddress("pseudoTop_energy",&pseudoTop_energy,&b_pseudoTop_energy);
   fChain->SetBranchAddress("pseudoTop_pdgId",&pseudoTop_pdgId,&b_pseudoTop_pdgId);
   fChain->SetBranchAddress("pseudoTop_charge",&pseudoTop_charge,&b_pseudoTop_charge);

   fChain->SetBranchAddress("GjConstId",&GjConstId,&b_GjConstId);
   fChain->SetBranchAddress("GjConstPt",&GjConstPt,&b_GjConstPt);
   fChain->SetBranchAddress("GjConstCharge",&GjConstCharge,&b_GjConstCharge);
   fChain->SetBranchAddress("GjConstEta",&GjConstEta,&b_GjConstEta);
   fChain->SetBranchAddress("GjConstPhi",&GjConstPhi,&b_GjConstPhi);
   fChain->SetBranchAddress("GjConstE",&GjConstE,&b_GjConstE);
  fChain->SetBranchAddress("matchGjet", &matchGjet, &b_matchGjet);
  fChain->SetBranchAddress("MGjPt", &MGjPt, &b_MGjPt);
  fChain->SetBranchAddress("MGjeta", &MGjeta, &b_MGjeta);
  fChain->SetBranchAddress("MGjphi", &MGjphi, &b_MGjphi);
  fChain->SetBranchAddress("MGjE", &MGjE, &b_MGjE);
  fChain->SetBranchAddress("HLT_Mu17_Mu8", &HLT_Mu17_Mu8, &b_HLT_Mu17_Mu8);
  fChain->SetBranchAddress("HLT_Mu17_TkMu8", &HLT_Mu17_TkMu8, &b_HLT_Mu17_TkMu8);
  fChain->SetBranchAddress("HLT_Elec17_Elec8", &HLT_Elec17_Elec8, &b_HLT_Elec17_Elec8);
  fChain->SetBranchAddress("HLT_IsoMu24_eta2p1", &HLT_IsoMu24_eta2p1, &b_HLT_IsoMu24_eta2p1);

  fChain->SetBranchAddress("HLT_IsoMu17_eta2p1", &HLT_IsoMu17_eta2p1, &b_HLT_IsoMu17_eta2p1);
  fChain->SetBranchAddress("HLT_IsoMu20", &HLT_IsoMu20, &b_HLT_IsoMu20);
  fChain->SetBranchAddress("HLT_IsoMu20_eta2p1", &HLT_IsoMu20_eta2p1, &b_HLT_IsoMu20_eta2p1);
  fChain->SetBranchAddress("HLT_IsoTkMu20", &HLT_IsoTkMu20, &b_HLT_IsoTkMu20);
  fChain->SetBranchAddress("HLT_IsoTkMu20_eta2p1", &HLT_IsoTkMu20_eta2p1, &b_HLT_IsoTkMu20_eta2p1);
  fChain->SetBranchAddress("HLT_Mu20", &HLT_Mu20, &b_HLT_Mu20);
  fChain->SetBranchAddress("HLT_TkMu20", &HLT_TkMu20, &b_HLT_TkMu20);


  fChain->SetBranchAddress("HLT_IsoMu18", &HLT_IsoMu18, &b_HLT_IsoMu18);
  fChain->SetBranchAddress("HLT_IsoMu18_eta2p1", &HLT_IsoMu18_eta2p1, &b_HLT_IsoMu18_eta2p1);
  fChain->SetBranchAddress("HLT_IsoTkMu18", &HLT_IsoTkMu18, &b_HLT_IsoTkMu18);
  fChain->SetBranchAddress("HLT_IsoTkMu18_eta2p1", &HLT_IsoTkMu18_eta2p1, &b_HLT_IsoTkMu18_eta2p1);
  fChain->SetBranchAddress("HLT_Mu18", &HLT_Mu18, &b_HLT_Mu18);
  fChain->SetBranchAddress("HLT_TkMu18", &HLT_TkMu18, &b_HLT_TkMu18);


  fChain->SetBranchAddress("patMuonPt_", &patMuonPt_, &b_patMuonPt_);
  fChain->SetBranchAddress("patMuonEta_", &patMuonEta_, &b_patMuonEta_);
  fChain->SetBranchAddress("patMuonPhi_", &patMuonPhi_, &b_patMuonPhi_);
  fChain->SetBranchAddress("patMuonVtxZ_", &patMuonVtxZ_, &b_patMuonVtxZ_);
  fChain->SetBranchAddress("patMuonEn_", &patMuonEn_, &b_patMuonEn_);
  fChain->SetBranchAddress("patMuonCharge_", &patMuonCharge_, &b_patMuonCharge_);
  fChain->SetBranchAddress("patMuonDxy_", &patMuonDxy_, &b_patMuonDxy_);
  fChain->SetBranchAddress("patMuonCombId_", &patMuonCombId_, &b_patMuonCombId_);
  fChain->SetBranchAddress("patMuonLooseId_", &patMuonLooseId_, &b_patMuonLooseId_);
  fChain->SetBranchAddress("patMuonMediumId_", &patMuonMediumId_, &b_patMuonMediumId_);
  fChain->SetBranchAddress("patMuonTightId_", &patMuonTightId_, &b_patMuonTightId_);
  fChain->SetBranchAddress("patMuonTrig_", &patMuonTrig_, &b_patMuonTrig_);
  fChain->SetBranchAddress("patMuonDetIsoRho_", &patMuonDetIsoRho_, &b_patMuonDetIsoRho_);
  fChain->SetBranchAddress("patMuonPfIsoDbeta_", &patMuonPfIsoDbeta_, &b_patMuonPfIsoDbeta_);
  fChain->SetBranchAddress("patMuonM_", &patMuonM_, &b_patMuonM_);
  fChain->SetBranchAddress("patMuonPx_", &patMuonPx_, &b_patMuonPx_);
  fChain->SetBranchAddress("patMuonPy_", &patMuonPy_, &b_patMuonPy_);
  fChain->SetBranchAddress("patMuonPz_", &patMuonPz_, &b_patMuonPz_);
  fChain->SetBranchAddress("patMuonGlobalType_", &patMuonGlobalType_, &b_patMuonGlobalType_);
  fChain->SetBranchAddress("patMuonTrackerType_", &patMuonTrackerType_, &b_patMuonTrackerType_);
  fChain->SetBranchAddress("patMuonPFType_", &patMuonPFType_, &b_patMuonPFType_);
  fChain->SetBranchAddress("patMuonIsoSumPt_", &patMuonIsoSumPt_, &b_patMuonIsoSumPt_);
  fChain->SetBranchAddress("patMuonIsoRelative_", &patMuonIsoRelative_, &b_patMuonIsoRelative_);
  fChain->SetBranchAddress("patMuonIsoCalComb_", &patMuonIsoCalComb_, &b_patMuonIsoCalComb_);
  fChain->SetBranchAddress("patMuonIsoDY_", &patMuonIsoDY_, &b_patMuonIsoDY_);
  fChain->SetBranchAddress("patMuonChi2Ndoff_", &patMuonChi2Ndoff_, &b_patMuonChi2Ndoff_);
  fChain->SetBranchAddress("patMuonNhits_", &patMuonNhits_, &b_patMuonNhits_);
  fChain->SetBranchAddress("patMuonNMatches_", &patMuonNMatches_, &b_patMuonNMatches_);
  fChain->SetBranchAddress("patMuonDz_", &patMuonDz_, &b_patMuonDz_);
  fChain->SetBranchAddress("patMuonPhits_", &patMuonPhits_, &b_patMuonPhits_);
  fChain->SetBranchAddress("patMuonTkLayers_", &patMuonTkLayers_, &b_patMuonTkLayers_);
  fChain->SetBranchAddress("patMuon_PF_IsoSumChargedHadronPt_", &patMuon_PF_IsoSumChargedHadronPt_, &b_patMuon_PF_IsoSumChargedHadronPt_);
  fChain->SetBranchAddress("patMuon_PF_IsoSumNeutralHadronEt_", &patMuon_PF_IsoSumNeutralHadronEt_, &b_patMuon_PF_IsoSumNeutralHadronEt_);
  fChain->SetBranchAddress("patMuon_PF_IsoDY_", &patMuon_PF_IsoDY_, &b_patMuon_PF_IsoDY_);
  fChain->SetBranchAddress("patMuon_Mu17_Mu8_Matched_", &patMuon_Mu17_Mu8_Matched_, &b_patMuon_Mu17_Mu8_Matched_);
  fChain->SetBranchAddress("patMuon_Mu17_TkMu8_Matched_", &patMuon_Mu17_TkMu8_Matched_, &b_patMuon_Mu17_TkMu8_Matched_);
  fChain->SetBranchAddress("patElecId_", &patElecId_, &b_patElecId_);
  fChain->SetBranchAddress("patElecdEtaIn_", &patElecdEtaIn_, &b_patElecdEtaIn_);
  fChain->SetBranchAddress("patElecdPhiIn_", &patElecdPhiIn_, &b_patElecdPhiIn_);
  fChain->SetBranchAddress("patElechOverE_", &patElechOverE_, &b_patElechOverE_);
  fChain->SetBranchAddress("patElecsigmaIetaIeta_", &patElecsigmaIetaIeta_, &b_patElecsigmaIetaIeta_);
  fChain->SetBranchAddress("patElecfull5x5_sigmaIetaIeta_", &patElecfull5x5_sigmaIetaIeta_, &b_patElecfull5x5_sigmaIetaIeta_);
  fChain->SetBranchAddress("patElecooEmooP_", &patElecooEmooP_, &b_patElecooEmooP_);
  fChain->SetBranchAddress("patElecd0_", &patElecd0_, &b_patElecd0_);
  fChain->SetBranchAddress("patElecdz_", &patElecdz_, &b_patElecdz_);
  fChain->SetBranchAddress("patElecexpectedMissingInnerHits_", &patElecexpectedMissingInnerHits_, &b_patElecexpectedMissingInnerHits_);
  fChain->SetBranchAddress("patElecpassConversionVeto_", &patElecpassConversionVeto_, &b_patElecpassConversionVeto_);
  fChain->SetBranchAddress("patElecTrig_", &patElecTrig_, &b_patElecTrig_);
  fChain->SetBranchAddress("patElecDz_", &patElecDz_, &b_patElecDz_);
  fChain->SetBranchAddress("patElecMVATrigId_", &patElecMVATrigId_, &b_patElecMVATrigId_);
  fChain->SetBranchAddress("patElecMVANonTrigId_", &patElecMVANonTrigId_, &b_patElecMVANonTrigId_);
  fChain->SetBranchAddress("patElecPt_", &patElecPt_, &b_patElecPt_);
  fChain->SetBranchAddress("patElecEta_", &patElecEta_, &b_patElecEta_);
  fChain->SetBranchAddress("patElecScEta_", &patElecScEta_, &b_patElecScEta_);
  fChain->SetBranchAddress("patElecPhi_", &patElecPhi_, &b_patElecPhi_);
  fChain->SetBranchAddress("patElecEnergy_", &patElecEnergy_, &b_patElecEnergy_);
  fChain->SetBranchAddress("patElecCharge_", &patElecCharge_, &b_patElecCharge_);
  fChain->SetBranchAddress("patElecMediumIDOff_", &patElecMediumIDOff_, &b_patElecMediumIDOff_);
  fChain->SetBranchAddress("patElecMediumIDOff_Tom_", &patElecMediumIDOff_Tom_, &b_patElecMediumIDOff_Tom_);
  fChain->SetBranchAddress("patElecchIso03_", &patElecchIso03_, &b_patElecchIso03_);
  fChain->SetBranchAddress("patElecnhIso03_", &patElecnhIso03_, &b_patElecnhIso03_);
  fChain->SetBranchAddress("patElecphIso03_", &patElecphIso03_, &b_patElecphIso03_);
  fChain->SetBranchAddress("patElecpuChIso03_", &patElecpuChIso03_, &b_patElecpuChIso03_);
  fChain->SetBranchAddress("patElecPfIso_", &patElecPfIso_, &b_patElecPfIso_);
  fChain->SetBranchAddress("patElecPfIsodb_", &patElecPfIsodb_, &b_patElecPfIsodb_);
  fChain->SetBranchAddress("patElecPfIsoRho_", &patElecPfIsoRho_, &b_patElecPfIsoRho_);
  fChain->SetBranchAddress("rhoPrime", &rhoPrime, &b_rhoPrime);
  fChain->SetBranchAddress("neutral_", &neutral_, &b_neutral_);
  fChain->SetBranchAddress("photon_", &photon_, &b_photon_);
  fChain->SetBranchAddress("charged_", &charged_, &b_charged_);
  fChain->SetBranchAddress("neutral_Tom_", &neutral_Tom_, &b_neutral_Tom_);
  fChain->SetBranchAddress("photon_Tom_", &photon_Tom_, &b_photon_Tom_);
  fChain->SetBranchAddress("charged_Tom_", &charged_Tom_, &b_charged_Tom_);
  fChain->SetBranchAddress("AEff", &AEff, &b_AEff);
  fChain->SetBranchAddress("patElec_mva_presel_", &patElec_mva_presel_, &b_patElec_mva_presel_);
  fChain->SetBranchAddress("patJetPfAk04En_", &patJetPfAk04En_, &b_patJetPfAk04En_);
  fChain->SetBranchAddress("patJetPfAk04Pt_", &patJetPfAk04Pt_, &b_patJetPfAk04Pt_);
  fChain->SetBranchAddress("patJetPfAk04Eta_", &patJetPfAk04Eta_, &b_patJetPfAk04Eta_);
  fChain->SetBranchAddress("patJetPfAk04Phi_", &patJetPfAk04Phi_, &b_patJetPfAk04Phi_);
  fChain->SetBranchAddress("patJetPfAk04LooseId_", &patJetPfAk04LooseId_, &b_patJetPfAk04LooseId_);
  fChain->SetBranchAddress("patJetPfAk04Et_", &patJetPfAk04Et_, &b_patJetPfAk04Et_);
  fChain->SetBranchAddress("patJetPfAk04PartonFlavour_", &patJetPfAk04PartonFlavour_, &b_patJetPfAk04PartonFlavour_);
  fChain->SetBranchAddress("patJetPfAk04RawPt_", &patJetPfAk04RawPt_, &b_patJetPfAk04RawPt_);
  fChain->SetBranchAddress("patJetPfAk04RawEn_", &patJetPfAk04RawEn_, &b_patJetPfAk04RawEn_);
  fChain->SetBranchAddress("patJetPfAk04HadEHF_", &patJetPfAk04HadEHF_, &b_patJetPfAk04HadEHF_);
  fChain->SetBranchAddress("patJetPfAk04EmEHF_", &patJetPfAk04EmEHF_, &b_patJetPfAk04EmEHF_);
  fChain->SetBranchAddress("patJetPfAk04chf_", &patJetPfAk04chf_, &b_patJetPfAk04chf_);
  fChain->SetBranchAddress("patJetPfAk04nhf_", &patJetPfAk04nhf_, &b_patJetPfAk04nhf_);
  fChain->SetBranchAddress("patJetPfAk04cemf_", &patJetPfAk04cemf_, &b_patJetPfAk04cemf_);
  fChain->SetBranchAddress("patJetPfAk04nemf_", &patJetPfAk04nemf_, &b_patJetPfAk04nemf_);
  fChain->SetBranchAddress("patJetPfAk04cmult_", &patJetPfAk04cmult_, &b_patJetPfAk04cmult_);
  fChain->SetBranchAddress("patJetPfAk04nconst_", &patJetPfAk04nconst_, &b_patJetPfAk04nconst_);
  fChain->SetBranchAddress("patJetPfAk04jetBeta_", &patJetPfAk04jetBeta_, &b_patJetPfAk04jetBeta_);
  fChain->SetBranchAddress("patJetPfAk04jetBetaClassic_", &patJetPfAk04jetBetaClassic_, &b_patJetPfAk04jetBetaClassic_);
  fChain->SetBranchAddress("patJetPfAk04jetBetaStar_", &patJetPfAk04jetBetaStar_, &b_patJetPfAk04jetBetaStar_);
  fChain->SetBranchAddress("patJetPfAk04jetBetaStarClassic_", &patJetPfAk04jetBetaStarClassic_, &b_patJetPfAk04jetBetaStarClassic_);
  fChain->SetBranchAddress("patJetPfAk04jetpuMVA_", &patJetPfAk04jetpuMVA_, &b_patJetPfAk04jetpuMVA_);
  fChain->SetBranchAddress("patJetPfAk04jetpukLoose_", &patJetPfAk04jetpukLoose_, &b_patJetPfAk04jetpukLoose_);
  fChain->SetBranchAddress("patJetPfAk04jetpukMedium_", &patJetPfAk04jetpukMedium_, &b_patJetPfAk04jetpukMedium_);
  fChain->SetBranchAddress("patJetPfAk04jetpukTight_", &patJetPfAk04jetpukTight_, &b_patJetPfAk04jetpukTight_);
  fChain->SetBranchAddress("patJetPfAk04BDiscCSVv2_", &patJetPfAk04BDiscCSVv2_, &b_patJetPfAk04BDiscCSVv2_);
  fChain->SetBranchAddress("patJetPfAk04BDiscCSVV1_", &patJetPfAk04BDiscCSVV1_, &b_patJetPfAk04BDiscCSVV1_);
  fChain->SetBranchAddress("patJetPfAk04BDiscCSVSLV1_", &patJetPfAk04BDiscCSVSLV1_, &b_patJetPfAk04BDiscCSVSLV1_);
  fChain->SetBranchAddress("unc_", &unc_, &b_unc_);
  fChain->SetBranchAddress("patJetPfAk04PtUp_", &patJetPfAk04PtUp_, &b_patJetPfAk04PtUp_);
  fChain->SetBranchAddress("patJetPfAk04PtDn_", &patJetPfAk04PtDn_, &b_patJetPfAk04PtDn_);
  fChain->SetBranchAddress("patJetPfAk04ConstId", &patJetPfAk04ConstId, &b_patJetPfAk04ConstId);
  fChain->SetBranchAddress("patJetPfAk04ConstPt", &patJetPfAk04ConstPt, &b_patJetPfAk04ConstPt);
  fChain->SetBranchAddress("patJetPfAk04ConstCharge", &patJetPfAk04ConstCharge,&b_patJetPfAk04ConstCharge);
  fChain->SetBranchAddress("patJetPfAk04ConstEta", &patJetPfAk04ConstEta, &b_patJetPfAk04ConstEta);
  fChain->SetBranchAddress("patJetPfAk04ConstPhi", &patJetPfAk04ConstPhi, &b_patJetPfAk04ConstPhi);
  fChain->SetBranchAddress("patJetPfAk04ConstE", &patJetPfAk04ConstE, &b_patJetPfAk04ConstE);
  fChain->SetBranchAddress("caloJetPt_", &caloJetPt_, &b_caloJetPt_);
  fChain->SetBranchAddress("caloJetRawPt_", &caloJetRawPt_, &b_caloJetRawPt_);
  fChain->SetBranchAddress("caloJetEn_", &caloJetEn_, &b_caloJetEn_);
  fChain->SetBranchAddress("caloJetEta_", &caloJetEta_, &b_caloJetEta_);
  fChain->SetBranchAddress("caloJetPhi_", &caloJetPhi_, &b_caloJetPhi_);
  fChain->SetBranchAddress("caloJetHadEHF_", &caloJetHadEHF_, &b_caloJetHadEHF_);
  fChain->SetBranchAddress("caloJetEmEHF_", &caloJetEmEHF_, &b_caloJetEmEHF_);
  fChain->SetBranchAddress("caloJetEmFrac_", &caloJetEmFrac_, &b_caloJetEmFrac_);
  fChain->SetBranchAddress("caloJetn90_", &caloJetn90_, &b_caloJetn90_);
  fChain->SetBranchAddress("id1_pdfInfo_", &id1_pdfInfo_, &b_id1_pdfInfo_);
  fChain->SetBranchAddress("id2_pdfInfo_", &id2_pdfInfo_, &b_id2_pdfInfo_);
  fChain->SetBranchAddress("x1_pdfInfo_", &x1_pdfInfo_, &b_x1_pdfInfo_);
  fChain->SetBranchAddress("x2_pdfInfo_", &x2_pdfInfo_, &b_x2_pdfInfo_);
  fChain->SetBranchAddress("scalePDF_pdfInfo_", &scalePDF_pdfInfo_, &b_scalePDF_pdfInfo_);
  fChain->SetBranchAddress("ptHat_", &ptHat_, &b_ptHat_);
  fChain->SetBranchAddress("mcWeight_", &mcWeight_, &b_mcWeight_);
  fChain->SetBranchAddress("mcWeights_", &mcWeights_, &b_mcWeights_);
  fChain->SetBranchAddress("wtot_write", &wtot_write, &b_wtot_write);
  fChain->SetBranchAddress("nup", &nup, &b_nup);
  Notify();
}

Bool_t tt_uev_analyzer::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void tt_uev_analyzer::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t tt_uev_analyzer::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}

double tt_uev_analyzer::DeltaR(double eta1, double eta2, double phi1, double phi2)
{
  double deta = eta2 - eta1;
  double dphi = phi2 - phi1;
  if (fabs(dphi) > pi) dphi = 2*pi - fabs(dphi);
  double DELTAR = sqrt(pow(dphi,2)+pow(deta,2))*1.0;
  return DELTAR;
}
double tt_uev_analyzer::DeltaPhi(double phi1, double phi2)
{
  double dphi = phi2 - phi1;
  if (fabs(dphi) > pi) dphi = 2*pi - fabs(dphi);
  return dphi;
}

bool tt_uev_analyzer::hasb(int id)
{
  int fid=fabs(id);
  if((int)fid/10000000!=0)return false;
  if(fid<=100)return false;
  int n0=(fid/1)%10, n1=(fid/10)%10, n2=(fid/100)%10; 
  if( n0 == 0 &&n1 == 0) {
     if ((int)fid%10000!=0) return false;
  }
  if(n0==5 || n1==5||n2==5)return true;
  return false;
}
#endif // #ifdef tt_uev_analyzer_cxx
