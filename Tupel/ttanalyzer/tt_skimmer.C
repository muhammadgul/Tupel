#define tt_skimmer_cxx
#include "tt_skimmer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <TLorentzVector.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
//#include "standalone_LumiReWeighting.h"
#include <iomanip>
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TH3.h"
#include "TRandom.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "math.h"
#include <fstream>
#include <string>
#include <iostream>
#include <TStyle.h>
#include "TCanvas.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TChain.h"
#include "TF2.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TPostScript.h"
#include "TLine.h"
#include "TEllipse.h"
#include "TMath.h"
#include "TLatex.h"
#include "TLorentzVector.h"
#include <vector>


void tt_skimmer::Loop()
{
//   In a ROOT session, you can do:
//      root> .L tt_skimmer.C
//      root> tt_skimmer t
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
cout<<"burda"<<endl;
   if (fChain == 0) return;
// standalone_LumiReWeighting puWeight(2015), puUp(2015,1), puDown(2015,-1);
   Long64_t nentries = fChain->GetEntries();
  cout<<nentries<<endl;
//   nentries = 1000000;
 TH1::SetDefaultSumw2();
 TH2::SetDefaultSumw2();
 TProfile::SetDefaultSumw2();
   Long64_t nbytes = 0, nb = 0;

   TFile* file_out = new TFile("/sdb2/Bugra/skimmed/" + name,"RECREATE"); 
   file_out->cd();	
   TTree *weight_tree;
  weight_tree = new TTree("MuonTree","MuonTree");
    double wtot_write=0;
    weight_tree->Branch("patPfCandPt",&patPfCandPt);
    weight_tree->Branch("patPfCandEta",&patPfCandEta);
    weight_tree->Branch("patPfCandPhi",&patPfCandPhi);
    weight_tree->Branch("patPfCandE",&patPfCandE);
    weight_tree->Branch("patPfCandM",&patPfCandM);
    weight_tree->Branch("patPfCandPx",&patPfCandPx);
    weight_tree->Branch("patPfCandPhiAtVtx",&patPfCandPhiAtVtx);
    weight_tree->Branch("patPfCandLostInnerHits",&patPfCandLostInnerHits);
    weight_tree->Branch("patPfCandTrackHighPurity",&patPfCandTrackHighPurity);
    weight_tree->Branch("patPfCandPuppiWeight",&patPfCandPuppiWeight);
    weight_tree->Branch("patPfCandPuppiWeightNolep",&patPfCandPuppiWeightNolep);
    weight_tree->Branch("patPfCandCharge",&patPfCandCharge);
    weight_tree->Branch("patPfCandDxy",&patPfCandDxy);
    weight_tree->Branch("patPfCandDxyerr",&patPfCandDxyerr);
    weight_tree->Branch("patPfCandDz",&patPfCandDz);
    weight_tree->Branch("patPfCandDzAssociatedPV",&patPfCandDzAssociatedPV);
    weight_tree->Branch("patPfCandDzerr",&patPfCandDzerr);
    weight_tree->Branch("patPfCandFromPv",&patPfCandFromPv);

    weight_tree->Branch("METPt",&METPt);
    weight_tree->Branch("METPx",&METPx);
    weight_tree->Branch("METPy",&METPy);
    weight_tree->Branch("METPz",&METPz);
    weight_tree->Branch("METE",&METE);
    weight_tree->Branch("METsigx2",&METsigx2);
    weight_tree->Branch("METsigxy",&METsigxy);
    weight_tree->Branch("METsigy2",&METsigy2);
    weight_tree->Branch("METsig",&METsig);
    weight_tree->Branch("event",&event);
    weight_tree->Branch("realdata",&realdata);
    weight_tree->Branch("run",&run);
    weight_tree->Branch("lumi",&lumi);
    weight_tree->Branch("bxnumber",&bxnumber);
    weight_tree->Branch("EvtInfo_NumVtx",&EvtInfo_NumVtx);
    weight_tree->Branch("PU_npT",&PU_npT);
    weight_tree->Branch("PU_npIT",&PU_npIT);
    weight_tree->Branch("MyWeight",&MyWeight);
    weight_tree->Branch("Dr01LepPt",&Dr01LepPt);
    weight_tree->Branch("Dr01LepEta",&Dr01LepEta);
    weight_tree->Branch("Dr01LepPhi",&Dr01LepPhi);
    weight_tree->Branch("Dr01LepE",&Dr01LepE);
    weight_tree->Branch("Dr01LepM",&Dr01LepM);
    weight_tree->Branch("Dr01LepId",&Dr01LepId);
    weight_tree->Branch("Dr01LepStatus",&Dr01LepStatus);
    weight_tree->Branch("Dr01LepMomId",&Dr01LepMomId);
    weight_tree->Branch("Dr01LepIsPrompt",&Dr01LepIsPrompt);
    weight_tree->Branch("Dr01LepIsTauProd",&Dr01LepIsTauProd);
    weight_tree->Branch("Packed01Pt",&Packed01Pt);
    weight_tree->Branch("Packed01Eta",&Packed01Eta);
    weight_tree->Branch("Packed01Phi",&Packed01Phi);
    weight_tree->Branch("Packed01E",&Packed01E);
    weight_tree->Branch("Packed01M",&Packed01M);
    weight_tree->Branch("Packed01Id",&Packed01Id);
    weight_tree->Branch("Packed01Status",&Packed01Status);
    weight_tree->Branch("Packed01MomId",&Packed01MomId);
    weight_tree->Branch("Packed01IsPrompt",&Packed01IsPrompt);
    weight_tree->Branch("Packed01IsTauProd",&Packed01IsTauProd);
    weight_tree->Branch("Bare01LepPt",&Bare01LepPt);
    weight_tree->Branch("Bare01LepEta",&Bare01LepEta);
    weight_tree->Branch("Bare01LepPhi",&Bare01LepPhi);
    weight_tree->Branch("Bare01LepE",&Bare01LepE);
    weight_tree->Branch("Bare01LepM",&Bare01LepM);
    weight_tree->Branch("Bare01LepId",&Bare01LepId);
    weight_tree->Branch("Bare01LepStatus",&Bare01LepStatus);
    weight_tree->Branch("Bare01LepMomId",&Bare01LepMomId);      
    weight_tree->Branch("St03Pt",&St03Pt);
    weight_tree->Branch("St03Eta",&St03Eta);
    weight_tree->Branch("St03Phi",&St03Phi);
    weight_tree->Branch("St03E",&St03E);
    weight_tree->Branch("St03M",&St03M);
    weight_tree->Branch("St03Id",&St03Id);
    weight_tree->Branch("St03Status",&St03Status);
    weight_tree->Branch("St03MotherId",&St03MotherId);
    weight_tree->Branch("St03NumberMom",&St03NumberMom);    

    
    weight_tree->Branch("St01PhotonPt",&St01PhotonPt);
    weight_tree->Branch("St01PhotonEta",&St01PhotonEta);
    weight_tree->Branch("St01PhotonPhi",&St01PhotonPhi);
    weight_tree->Branch("St01PhotonE",&St01PhotonE);
    weight_tree->Branch("St01PhotonM",&St01PhotonM);
    weight_tree->Branch("St01PhotonId",&St01PhotonId);
    weight_tree->Branch("St01PhotonMomId",&St01PhotonMomId);
    weight_tree->Branch("St01PhotonNumberMom",&St01PhotonNumberMom);
    weight_tree->Branch("St01PhotonStatus",&St01PhotonStatus);
    
    weight_tree->Branch("GjPt",&GjPt);
    weight_tree->Branch("Gjeta",&Gjeta);
    weight_tree->Branch("Gjphi",&Gjphi);
    weight_tree->Branch("GjE",&GjE);
    weight_tree->Branch("GjPx",&GjPx);
    weight_tree->Branch("GjPy",&GjPy);
    weight_tree->Branch("GjPz",&GjPz);
    weight_tree->Branch("GjChargedFraction",&GjChargedFraction);
    weight_tree->Branch("GjConstId",&GjConstId);
    weight_tree->Branch("GjConstPt",&GjConstPt);
    weight_tree->Branch("GjConstEta",&GjConstEta);
    weight_tree->Branch("GjConstPhi",&GjConstPhi);
    weight_tree->Branch("GjConstE",&GjConstE);
    weight_tree->Branch("GjNConst",&GjNConst);
    weight_tree->Branch("matchGjet",&matchGjet);
    weight_tree->Branch("MGjPt",&MGjPt);
    weight_tree->Branch("MGjeta",&MGjeta);
    weight_tree->Branch("MGjphi",&MGjphi);
    weight_tree->Branch("MGjE",&MGjE); 
    
    //HLT
/*    weight_tree->Branch("HLT_Mu17_Mu8",&HLT_Mu17_Mu8);
    weight_tree->Branch("HLT_Mu17_TkMu8",&HLT_Mu17_TkMu8);
    weight_tree->Branch("HLT_Elec17_Elec8",&HLT_Elec17_Elec8);
    weight_tree->Branch("HLT_IsoMu24_eta2p1",&HLT_IsoMu24_eta2p1);
  */  


   weight_tree->Branch("HLT_Mu17_Mu8",&HLT_Mu17_Mu8);
    weight_tree->Branch("HLT_Mu17_TkMu8",&HLT_Mu17_TkMu8);
    weight_tree->Branch("HLT_Elec17_Elec8",&HLT_Elec17_Elec8);
    weight_tree->Branch("HLT_IsoMu24_eta2p1",&HLT_IsoMu24_eta2p1);
     weight_tree->Branch("HLT_IsoMu17_eta2p1",&HLT_IsoMu17_eta2p1); 
     weight_tree->Branch("HLT_IsoMu20",&HLT_IsoMu20); 
     weight_tree->Branch("HLT_IsoMu20_eta2p1",&HLT_IsoMu20_eta2p1); 
     weight_tree->Branch("HLT_IsoTkMu20",&HLT_IsoTkMu20); 
     weight_tree->Branch("HLT_IsoTkMu20_eta2p1",&HLT_IsoTkMu20_eta2p1);
     weight_tree->Branch("HLT_Mu20",&HLT_Mu20); 
     weight_tree->Branch("HLT_TkMu20",&HLT_TkMu20); 


     weight_tree->Branch("HLT_IsoMu18",&HLT_IsoMu18); 
     weight_tree->Branch("HLT_IsoMu18_eta2p1",&HLT_IsoMu18_eta2p1); 
     weight_tree->Branch("HLT_IsoTkMu18",&HLT_IsoTkMu18);
     weight_tree->Branch("HLT_IsoTkMu18_eta2p1",&HLT_IsoTkMu18_eta2p1); 
     weight_tree->Branch("HLT_Mu18",&HLT_Mu18); 
     weight_tree->Branch("HLT_TkMu18",&HLT_TkMu18); 


    //Muons
    weight_tree->Branch("patMuonPt_",&patMuonPt_);
    weight_tree->Branch("patMuonEta_",&patMuonEta_);
    weight_tree->Branch("patMuonPhi_",&patMuonPhi_);
    weight_tree->Branch("patMuonVtxZ_",&patMuonVtxZ_);
    weight_tree->Branch("patMuonEn_",&patMuonEn_);
    weight_tree->Branch("patMuonCharge_",&patMuonCharge_);
    weight_tree->Branch("patMuonDxy_",&patMuonDxy_);
    weight_tree->Branch("patMuonCombId_",&patMuonCombId_);
    weight_tree->Branch("patMuonLooseId_",&patMuonLooseId_);
    weight_tree->Branch("patMuonMediumId_",&patMuonMediumId_);
    weight_tree->Branch("patMuonTightId_",&patMuonTightId_);
    weight_tree->Branch("patMuonTrig_",&patMuonTrig_);
    weight_tree->Branch("patMuonDetIsoRho_",&patMuonDetIsoRho_);
    weight_tree->Branch("patMuonPfIsoDbeta_",&patMuonPfIsoDbeta_);
    weight_tree->Branch("patMuonM_",&patMuonM_);
    weight_tree->Branch("patMuonPx_",&patMuonPx_);
    weight_tree->Branch("patMuonPy_",&patMuonPy_);
    weight_tree->Branch("patMuonPz_",&patMuonPz_);
    weight_tree->Branch("patMuonGlobalType_",&patMuonGlobalType_);
    weight_tree->Branch("patMuonTrackerType_",&patMuonTrackerType_);
    weight_tree->Branch("patMuonPFType_",&patMuonPFType_);
    weight_tree->Branch("patMuonIsoSumPt_",&patMuonIsoSumPt_);
    weight_tree->Branch("patMuonIsoRelative_",&patMuonIsoRelative_);
    weight_tree->Branch("patMuonIsoCalComb_",&patMuonIsoCalComb_);
    weight_tree->Branch("patMuonIsoDY_",&patMuonIsoDY_);
    weight_tree->Branch("patMuonChi2Ndoff_",&patMuonChi2Ndoff_);
    weight_tree->Branch("patMuonNhits_",&patMuonNhits_);
    weight_tree->Branch("patMuonNMatches_",&patMuonNMatches_);
    weight_tree->Branch("patMuonDz_",&patMuonDz_);
    weight_tree->Branch("patMuonPhits_",&patMuonPhits_);
    weight_tree->Branch("patMuonTkLayers_",&patMuonTkLayers_);
    weight_tree->Branch("patMuon_PF_IsoSumChargedHadronPt_",&patMuon_PF_IsoSumChargedHadronPt_);
    weight_tree->Branch("patMuon_PF_IsoSumNeutralHadronEt_",&patMuon_PF_IsoSumNeutralHadronEt_);
    weight_tree->Branch("patMuon_PF_IsoDY_",&patMuon_PF_IsoDY_);
    weight_tree->Branch("patMuon_Mu17_Mu8_Matched_",&patMuon_Mu17_Mu8_Matched_);
    weight_tree->Branch("patMuon_Mu17_TkMu8_Matched_",&patMuon_Mu17_TkMu8_Matched_);

    weight_tree->Branch("patElecId_",&patElecId_);
    weight_tree->Branch("patElecdEtaIn_",&patElecdEtaIn_);
    weight_tree->Branch("patElecdPhiIn_",&patElecdPhiIn_);
    weight_tree->Branch("patElechOverE_",&patElechOverE_);
    weight_tree->Branch("patElecsigmaIetaIeta_",&patElecsigmaIetaIeta_);
    weight_tree->Branch("patElecfull5x5_sigmaIetaIeta_",&patElecfull5x5_sigmaIetaIeta_);
    weight_tree->Branch("patElecooEmooP_",&patElecooEmooP_);
    weight_tree->Branch("patElecd0_",&patElecd0_);
    weight_tree->Branch("patElecdz_",&patElecdz_);
    weight_tree->Branch("patElecexpectedMissingInnerHits_",&patElecexpectedMissingInnerHits_);
    weight_tree->Branch("patElecpassConversionVeto_",&patElecpassConversionVeto_);     
    weight_tree->Branch("patElecTrig_",&patElecTrig_);
    weight_tree->Branch("patElecDz_",&patElecDz_);
    weight_tree->Branch("patElecMVATrigId_",&patElecMVATrigId_);
    weight_tree->Branch("patElecMVANonTrigId_",&patElecMVANonTrigId_);
    weight_tree->Branch("patElecPt_",&patElecPt_);
    weight_tree->Branch("patElecEta_",&patElecEta_);
    weight_tree->Branch("patElecScEta_",&patElecScEta_);
    weight_tree->Branch("patElecPhi_",&patElecPhi_);
    weight_tree->Branch("patElecEnergy_",&patElecEnergy_);
    weight_tree->Branch("patElecCharge_",&patElecCharge_);
    weight_tree->Branch("patElecMediumIDOff_",&patElecMediumIDOff_);
    weight_tree->Branch("patElecMediumIDOff_Tom_",&patElecMediumIDOff_Tom_);

    weight_tree->Branch("patElecchIso03_",&patElecchIso03_);
    weight_tree->Branch("patElecnhIso03_",&patElecnhIso03_);
    weight_tree->Branch("patElecphIso03_",&patElecphIso03_);
    weight_tree->Branch("patElecpuChIso03_",&patElecpuChIso03_);
    weight_tree->Branch("patElecPfIso_",&patElecPfIso_);
    weight_tree->Branch("patElecPfIsodb_",&patElecPfIsodb_);
    weight_tree->Branch("patElecPfIsoRho_",&patElecPfIsoRho_);
    weight_tree->Branch("rhoPrime",&rhoPrime);
    weight_tree->Branch("neutral_",&neutral_);
    weight_tree->Branch("photon_",&photon_);
    weight_tree->Branch("charged_",&charged_);
    weight_tree->Branch("neutral_Tom_",&neutral_Tom_);
    weight_tree->Branch("photon_Tom_",&photon_Tom_);
    weight_tree->Branch("charged_Tom_",&charged_Tom_);
    weight_tree->Branch("AEff",&AEff);
    weight_tree->Branch("patElec_mva_presel_",&patElec_mva_presel_);
    
    //PFJet
    weight_tree->Branch("patJetPfAk04En_",&patJetPfAk04En_);
    weight_tree->Branch("patJetPfAk04Pt_",&patJetPfAk04Pt_);
    weight_tree->Branch("patJetPfAk04Eta_",&patJetPfAk04Eta_);
    weight_tree->Branch("patJetPfAk04Phi_",&patJetPfAk04Phi_);
    weight_tree->Branch("patJetPfAk04LooseId_",&patJetPfAk04LooseId_);
    weight_tree->Branch("patJetPfAk04Et_",&patJetPfAk04Et_);
    weight_tree->Branch("patJetPfAk04PartonFlavour_", &patJetPfAk04PartonFlavour_);
    weight_tree->Branch("patJetPfAk04RawPt_",&patJetPfAk04RawPt_);
    weight_tree->Branch("patJetPfAk04RawEn_",&patJetPfAk04RawEn_);
    weight_tree->Branch("patJetPfAk04HadEHF_",&patJetPfAk04HadEHF_);
    weight_tree->Branch("patJetPfAk04EmEHF_",&patJetPfAk04EmEHF_);
    weight_tree->Branch("patJetPfAk04chf_",&patJetPfAk04chf_);
    weight_tree->Branch("patJetPfAk04nhf_",&patJetPfAk04nhf_);
    weight_tree->Branch("patJetPfAk04cemf_",&patJetPfAk04cemf_);
    weight_tree->Branch("patJetPfAk04nemf_",&patJetPfAk04nemf_);
    weight_tree->Branch("patJetPfAk04cmult_",&patJetPfAk04cmult_);
    weight_tree->Branch("patJetPfAk04nconst_",&patJetPfAk04nconst_);
    weight_tree->Branch("patJetPfAk04jetBeta_",&patJetPfAk04jetBeta_);
    weight_tree->Branch("patJetPfAk04jetBetaClassic_",&patJetPfAk04jetBetaClassic_);
    weight_tree->Branch("patJetPfAk04jetBetaStar_",&patJetPfAk04jetBetaStar_);
    weight_tree->Branch("patJetPfAk04jetBetaStarClassic_",&patJetPfAk04jetBetaStarClassic_);
    weight_tree->Branch("patJetPfAk04jetpuMVA_",&patJetPfAk04jetpuMVA_);
    weight_tree->Branch("patJetPfAk04jetpukLoose_",&patJetPfAk04jetpukLoose_);
    weight_tree->Branch("patJetPfAk04jetpukMedium_",&patJetPfAk04jetpukMedium_);
    weight_tree->Branch("patJetPfAk04jetpukTight_",&patJetPfAk04jetpukTight_);
    weight_tree->Branch("patJetPfAk04BDiscCSVv2_",&patJetPfAk04BDiscCSVv2_);
    weight_tree->Branch("patJetPfAk04BDiscCSVV1_",&patJetPfAk04BDiscCSVV1_);
    weight_tree->Branch("patJetPfAk04BDiscCSVSLV1_",&patJetPfAk04BDiscCSVSLV1_);
    weight_tree->Branch("unc_",&unc_);
    weight_tree->Branch("patJetPfAk04PtUp_",&patJetPfAk04PtUp_);
    weight_tree->Branch("patJetPfAk04PtDn_",&patJetPfAk04PtDn_); 
    weight_tree->Branch("patJetPfAk04ConstId",&patJetPfAk04ConstId);
    weight_tree->Branch("patJetPfAk04ConstPt",&patJetPfAk04ConstPt);
    weight_tree->Branch("patJetPfAk04ConstEta",&patJetPfAk04ConstEta);
    weight_tree->Branch("patJetPfAk04ConstPhi",&patJetPfAk04ConstPhi);
    weight_tree->Branch("patJetPfAk04ConstE",&patJetPfAk04ConstE);


    //CaloJets
    weight_tree->Branch("caloJetPt_",&caloJetPt_);
    weight_tree->Branch("caloJetRawPt_",&caloJetRawPt_);
    weight_tree->Branch("caloJetEn_",&caloJetEn_);
    weight_tree->Branch("caloJetEta_",&caloJetEta_);
    weight_tree->Branch("caloJetPhi_",&caloJetPhi_);
    weight_tree->Branch("caloJetHadEHF_",&caloJetHadEHF_);
    weight_tree->Branch("caloJetEmEHF_",&caloJetEmEHF_);
    weight_tree->Branch("caloJetEmFrac_",&caloJetEmFrac_);
    weight_tree->Branch("caloJetn90_",&caloJetn90_);
    
    weight_tree->Branch("id1_pdfInfo_",&id1_pdfInfo_);
    weight_tree->Branch("id2_pdfInfo_",&id2_pdfInfo_);
    weight_tree->Branch("x1_pdfInfo_",&x1_pdfInfo_);
    weight_tree->Branch("x2_pdfInfo_",&x2_pdfInfo_);
    weight_tree->Branch("scalePDF_pdfInfo_",&scalePDF_pdfInfo_);
    weight_tree->Branch("ptHat_",&ptHat_);
    weight_tree->Branch("mcWeight_",&mcWeight_);
    weight_tree->Branch("mcWeights_",&mcWeights_);
    weight_tree->Branch("wtot_write",&wtot_write);
    weight_tree->Branch("nup",&nup);   
   double wtot=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(jentry%10000==0)cout<<"/sdb2/Bugra/skimmed/" <<name<<" << "<<jentry<<"/"<<nentries<<endl;
      bool found_mu=false;
      bool found_mu_gen=false;
      bool found4jet=false;
      bool found4jet_gen=false;
      // if (Cut(ientry) < 0) continue;
      for(unsigned int mu_ind=0; mu_ind<patMuonPt_->size();mu_ind++){
        if(patMuonCombId_->at(mu_ind)>0&& fabs(patMuonEta_->at(mu_ind))<2.5 &&patMuonPt_->at(mu_ind)>15 ){
          found_mu=true;break;
        }
      }
     int njet=0;
     for(unsigned int jet_ind=0; jet_ind<patJetPfAk04Pt_->size();jet_ind++){
        if( fabs(patJetPfAk04Eta_->at(jet_ind))>2.6 ||patJetPfAk04LooseId_->at(jet_ind)==0 ||patJetPfAk04Pt_->at(jet_ind)<15)continue;
        njet++;
        if(njet==4){found4jet=true;break;}
     }
 



     for(unsigned int mu_ind=0; mu_ind<Dr01LepPt->size();mu_ind++){
        if(fabs(Dr01LepId->at(mu_ind))==13&& fabs(Dr01LepEta->at(mu_ind))<2.5 &&Dr01LepPt->at(mu_ind)>15 ){
          found_mu_gen=true;break;
        }
      }
    int njet_gen=0;
     for(unsigned int jet_ind=0; jet_ind<Gjeta->size();jet_ind++){
        if( fabs(Gjeta->at(jet_ind))>2.6||GjPt->at(jet_ind)<15)continue;
        njet_gen++;
        if(njet_gen==4){found4jet_gen=true;break;}
     }

      double w=1;
      if(mcWeights_->size()>0)w=mcWeights_->at(0);

      wtot+=w;
      if((found_mu&&found4jet)  ||(found_mu_gen&&found4jet_gen) ){
        wtot_write=wtot;
        weight_tree->Fill();
        wtot=0;
      }



   }//event loop

 // if(!sherpa)weight_tree->Branch("cnt0",&cnt0);
 // if(sherpa||mg5amcanlo)weight_tree->Branch("cnt0",&test);



 //  weight_tree->Print();
   file_out->Write();
   file_out->Close();
}

int main(int argc,char **argv){
  tt_skimmer a;
  a.Loop();
}
