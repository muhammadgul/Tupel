#define tt_uev_analyzer_cxx
#include "tt_uev_analyzer.h"
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
#include "standalone_LumiReWeighting.h"
#include "BTagCalibrationStandalone.h"
#include "BTagCalibrationStandalone.cc"
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


void tt_uev_analyzer::Loop()
{
//   In a ROOT session, you can do:
//      root> .L tt_uev_analyzer.C
//      root> tt_uev_analyzer t
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

BTagCalibration calib("csvv2", "CSVv2.csv");
BTagCalibrationReader reader(&calib,               // calibration instance
                             BTagEntry::OP_MEDIUM,  // operating point
                             "mujets",               // measurement type
                             "central");           // systematics type

 standalone_LumiReWeighting puWeight(201550), puUp(201550,1), puDown(201550,-1);
   Long64_t nentries = fChain->GetEntries();
//   if(nentries > 1000000)nentries = 1000000;
 TH1::SetDefaultSumw2();
 TH2::SetDefaultSumw2();
 TProfile::SetDefaultSumw2();
   Long64_t nbytes = 0, nb = 0;
   double pt_tt_range[]={0,10,20,25,30,40,55,70,90,135,500};

//   double pt_t_range[]={0,20,30,45,55,70,135,300,1000};

   double pt_t_range[]={0,60,100,150,200,260,320,400,1000};


   double m_t_range[]={0,100,130,160,170,180,190,200,210,300,500};

//   double m_tt_range[]={200,300,350,400,420,440,460,490,550,700,1000};
   double m_tt_range[]={200,340,400,470,550,650,800,1100,2000};
   TFile* file_out = new TFile(name,"RECREATE"); 
   file_out->cd();	
   TH1* h_ljet_pt= new TH1D ("ljet_pt","ljet_pt",100,0,1000);
   TH1* h_ljet_eta= new TH1D ("jlet_eta","ljet_eta",100,-2.5,2.5);

   TH1* h_sljet_pt= new TH1D ("sljet_pt","ljet_pt",100,0,1000);
   TH1* h_sljet_eta= new TH1D ("sjlet_eta","ljet_eta",100,-2.5,2.5);

   TH1* h_lbjet_pt= new TH1D ("lbjet_pt","ljet_pt",100,0,1000);
   TH1* h_lbjet_eta= new TH1D ("jblet_eta","ljet_eta",100,-2.5,2.5);

   TH1* h_slbjet_pt= new TH1D ("slbjet_pt","ljet_pt",100,0,1000);
   TH1* h_slbjet_eta= new TH1D ("sjblet_eta","ljet_eta",100,-2.5,2.5);

   TH1* h_dijet_mass= new TH1D ("dijet_mass","dijet_mass",100,0,1000);
   TH1* h_dijet_mass_narrow= new TH1D ("dijet_mass_narrow","dijet_mass_narrow",1000,0,200);
   TH1* h_pt_ttbar= new TH1D ("pt_ttbar","pt_ttbar",10,pt_tt_range);
   TH1* h_phi_ttbar= new TH1D ("phi_ttbar","phi_ttbar",100,0,3.14);
   TH1* h_dphi_ttbar_pf= new TH1D ("dphi_ttbar_pf","dphi_ttbar_pf",20,0,180);
   TH1* h_njet_ttbar= new TH1D ("njet_ttbar","njet_ttbar",15,-0.5,14.5);
   TH1* h_njet_15_ttbar= new TH1D ("njet_15_ttbar","njet_15_ttbar",15,-0.5,14.5);
   TH1* h_njet_bb= new TH1D ("njet_bb","njet_bb",15,-0.5,14.5);

   TH1* h_pt_ttbar_kinrec= new TH1D ("pt_ttbar_kinrec","pt_ttbar_kinrec",10,pt_tt_range);
   TH1* h_nu_pz= new TH1D ("nu_pz","nu_pz",200,0,1000);
   TH1* h_nu_pt= new TH1D ("nu_pt","nu_pt",200,0,1000);


   TH1* h_n_bjet= new TH1D ("n_bjet","n_bjet",15,-0.5,14.5);
   TH1* h_deltar_pf_jetpf= new TH1D ("deltar_pf_jetpf","deltar_pf_jetpf",1000,0,5);
   TH1* h_deltar_pf_jet= new TH1D ("deltar_pf_jet","deltar_pf_jet",1000,0,5);
   TH1* h_deltar_pf_jet_after= new TH1D ("deltar_pf_jet_after","deltar_pf_jet_after",1000,0,5);
   TH1* h_deltar_pf_mu= new TH1D ("deltar_pf_mu","deltar_pf_mu",1000,0,5);

   TH1* h_mu_pt= new TH1D ("mu_pt","mu_pt",5000,0,1000);
   TH1* h_mu_eta= new TH1D ("mu_eta","mu_eta",100,-2.5,2.5);
   TH1* h_mu_phi= new TH1D ("mu_phi","mu_phi",100,0,3.14);
   TH1* h_mu_iso= new TH1D ("mu_iso","mu_iso",1000,0,0.5);

   TH1* h_mu_pt_meas= new TH1D ("mu_pt_meas","mu_pt_meas",5000,0,1000);
   TH1* h_mu_eta_meas= new TH1D ("mu_eta_meas","mu_eta_meas",100,-2.5,2.5);
   TH1* h_mu_phi_meas= new TH1D ("mu_phi_meas","mu_phi_meas",100,0,3.14);
   TH1* h_mu_iso_meas= new TH1D ("mu_iso_meas","mu_iso_meas",1000,0,0.5);
   TH1* h_met_meas= new TH1D ("met_meas","met_meas",200,0,1000);

   TH2* h_dphi_ptsumpf= new TH2D ("dphi_ptsumpf","dphi_ptsumpf",20,0,180,20,0,10);
   TH2* h_dphi_ptaveragepf= new TH2D ("dphi_ptaveragepf","dphi_ptaveragepf",20,0,180,20,0,10);
   TH2* h_dphi_npf= new TH2D ("dphi_npf","dphi_npf",20,0,180,20,0,10);
   TH2* h_nvtx_npf= new TH2D ("nvtx_npf","nvtx_npf",50,0,50,20,0,100);
   TH2* h_dphi_ptsumpf_0j= new TH2D ("dphi_ptsumpf_0j","dphi_ptsumpf_0j",20,0,180,20,0,10);
   TH2* h_dphi_ptaveragepf_0j= new TH2D ("dphi_ptaveragepf_0j","dphi_ptaveragepf_0j",20,0,180,20,0,10);
   TH2* h_dphi_npf_0j= new TH2D ("dphi_npf_0j","dphi_npf_0j",20,0,180,20,0,10);
   TH2* h_nvtx_npf_0j= new TH2D ("nvtx_npf_0j","nvtx_npf_0j",50,0,50,20,0,100);
   TH2* h_dphi_ptsumpf_1j= new TH2D ("dphi_ptsumpf_1j","dphi_ptsumpf_1j",20,0,180,20,0,10);
   TH2* h_dphi_ptaveragepf_1j= new TH2D ("dphi_ptaveragepf_1j","dphi_ptaveragepf_1j",20,0,180,20,0,10);
   TH2* h_dphi_npf_1j= new TH2D ("dphi_npf_1j","dphi_npf_1j",20,0,180,20,0,10);
   TH2* h_nvtx_npf_1j= new TH2D ("nvtx_npf_1j","nvtx_npf_1j",50,0,50,20,0,100);
   TH2* h_dphi_ptsumpf_2pj= new TH2D ("dphi_ptsumpf_2pj","dphi_ptsumpf_2pj",20,0,180,20,0,10);
   TH2* h_dphi_ptaveragepf_2pj= new TH2D ("dphi_ptaveragepf_2pj","dphi_ptaveragepf_2pj",20,0,180,20,0,10);
   TH2* h_dphi_npf_2pj= new TH2D ("dphi_npf_2pj","dphi_npf_2pj",20,0,180,20,0,10);
   TH2* h_nvtx_npf_2pj= new TH2D ("nvtx_npf_2pj","nvtx_npf_2pj",50,0,50,20,0,100);
   TProfile* h_profile_dphi_ptsumpf= new TProfile ("profile_dphi_ptsumpf","profile_dphi_ptsumpf",20,0,180,0,1000);
   TProfile* h_profile_dphi_ptaveragepf= new TProfile ("profile_dphi_ptaveragepf","profile_dphi_ptaveragepf",20,0,180,0,1000);
   TProfile* h_profile_dphi_npf= new TProfile ("profile_dphi_npf","profile_dphi_npf",20,0,180,0,1000);
   TProfile* h_profile_nvtx_npf= new TProfile ("profile_nvtx_npf","profile_nvtx_npf",50,0,50,0,1000);
   TProfile* h_profile_nvtx_sumpt= new TProfile ("profile_nvtx_sumpt","profile_nvtx_sumpt",50,0,50,0,1000);
   TProfile* h_profile_dphi_ptsumpf_0j= new TProfile ("profile_dphi_ptsump_0jf","profile_dphi_ptsumpf_0j",20,0,180,0,1000);
   TProfile* h_profile_dphi_ptaveragepf_0j= new TProfile ("profile_dphi_ptaveragepf_0j","profile_dphi_ptaveragepf_0j",20,0,180,0,1000);
   TProfile* h_profile_dphi_npf_0j= new TProfile ("profile_dphi_npf_0j","profile_dphi_npf_0j",20,0,180,0,1000);
   TProfile* h_profile_nvtx_npf_0j= new TProfile ("profile_nvtx_npf_0j","profile_nvtx_npf_0j",50,0,50,0,1000);
   TProfile* h_profile_nvtx_sumpt_0j= new TProfile ("profile_nvtx_sumpt_0j","profile_nvtx_sumpt_0j",50,0,50,0,1000);
   TProfile* h_profile_dphi_ptsumpf_1j= new TProfile ("profile_dphi_ptsump_1jf","profile_dphi_ptsumpf_1j",20,0,180,0,1000);
   TProfile* h_profile_dphi_ptaveragepf_1j= new TProfile ("profile_dphi_ptaveragepf_1j","profile_dphi_ptaveragepf_1j",20,0,180,0,1000);
   TProfile* h_profile_dphi_npf_1j= new TProfile ("profile_dphi_npf_1j","profile_dphi_npf_1j",20,0,180,0,1000);
   TProfile* h_profile_nvtx_npf_1j= new TProfile ("profile_nvtx_npf_1j","profile_nvtx_npf_1j",50,0,50,0,1000);
   TProfile* h_profile_nvtx_sumpt_1j= new TProfile ("profile_nvtx_sumpt_1j","profile_nvtx_sumpt_1j",50,0,50,0,1000);
   TProfile* h_profile_dphi_ptsumpf_2pj= new TProfile ("profile_dphi_ptsump_2pjf","profile_dphi_ptsumpf_2pj",20,0,180,0,1000);
   TProfile* h_profile_dphi_ptaveragepf_2pj= new TProfile ("profile_dphi_ptaveragepf_2pj","profile_dphi_ptaveragepf_2pj",20,0,180,0,1000);
   TProfile* h_profile_dphi_npf_2pj= new TProfile ("profile_dphi_npf_2pj","profile_dphi_npf_2pj",20,0,180,0,1000);
   TProfile* h_profile_nvtx_npf_2pj= new TProfile ("profile_nvtx_npf_2pj","profile_nvtx_npf_2pj",50,0,50,0,1000);
   TProfile* h_profile_nvtx_sumpt_2pj= new TProfile ("profile_nvtx_sumpt_2pj","profile_nvtx_sumpt_2pj",50,0,50,0,1000);

   TProfile* h_profile_ptttbar_npf= new TProfile ("profile_ptttbar_npf","profile_ptttbar_npf",10,pt_tt_range,0,1000);
   TProfile* h_profile_ptttbar_sumpt= new TProfile ("profile_ptttbar_sumpt","profile_ptttbar_sumpt",10,pt_tt_range,0,1000);
   TProfile* h_profile_ptttbar_avept= new TProfile ("profile_ptttbar_avept","profile_ptttbar_avept",10,pt_tt_range,0,1000);

   TProfile* h_profile_ptttbar_npf_away= new TProfile ("profile_ptttbar_npf_away","profile_ptttbar_npf_away",10,pt_tt_range,0,1000);
   TProfile* h_profile_ptttbar_sumpt_away= new TProfile ("profile_ptttbar_sumpt_away","profile_ptttbar_sumpt_away",10,pt_tt_range,0,1000);
   TProfile* h_profile_ptttbar_avept_away= new TProfile ("profile_ptttbar_avept_away","profile_ptttbar_avept_away",10,pt_tt_range,0,1000);

   TProfile* h_profile_ptttbar_npf_transverse= new TProfile ("profile_ptttbar_npf_transverse","profile_ptttbar_npf_transverse",10,pt_tt_range,0,1000);
   TProfile* h_profile_ptttbar_sumpt_transverse= new TProfile ("profile_ptttbar_sumpt_transverse","profile_ptttbar_sumpt_transverse",10,pt_tt_range,0,1000);
   TProfile* h_profile_ptttbar_avept_transverse= new TProfile ("profile_ptttbar_avept_transverse","profile_ptttbar_avept_transverse",10,pt_tt_range,0,1000);

   TProfile* h_profile_ptttbar_npf_toward= new TProfile ("profile_ptttbar_npf_toward","profile_ptttbar_npf_toward",10,pt_tt_range,0,1000);
   TProfile* h_profile_ptttbar_sumpt_toward= new TProfile ("profile_ptttbar_sumpt_toward","profile_ptttbar_sumpt_toward",10,pt_tt_range,0,1000);
   TProfile* h_profile_ptttbar_avept_toward= new TProfile ("profile_ptttbar_avept_toward","profile_ptttbar_avept_toward",10,pt_tt_range,0,1000);

   TProfile* h_profile_deta_bb_njet_bb= new TProfile ("profile_deta_bb_njet_bb","profile_deta_bb_njet_bb",10,0,5,0,1000);
   TProfile* h_profile_deta_bb_njet_extra= new TProfile ("profile_deta_bb_njet_extra","profile_deta_bb_njet_extra",10,0,5,0,1000);
 
   TProfile* h_profile_mttbar_npf= new TProfile ("profile_mttbar_npf","profile_mttbar_npf",8,m_tt_range,0,1000);
   TProfile* h_profile_mttbar_sumpt= new TProfile ("profile_mttbar_sumpt","profile_mttbar_sumpt",8,m_tt_range,0,1000);
   TProfile* h_profile_mttbar_avept= new TProfile ("profile_mttbar_avept","profile_mttbar_avept",8,m_tt_range,0,1000);

   TProfile* h_profile_mttbar_npf_away= new TProfile ("profile_mttbar_npf_away","profile_mttbar_npf_away",8,m_tt_range,0,1000);
   TProfile* h_profile_mttbar_sumpt_away= new TProfile ("profile_mttbar_sumpt_away","profile_mttbar_sumpt_away",8,m_tt_range,0,1000);
   TProfile* h_profile_mttbar_avept_away= new TProfile ("profile_mttbar_avept_away","profile_mttbar_avept_away",8,m_tt_range,0,1000);

   TProfile* h_profile_mttbar_npf_transverse= new TProfile ("profile_mttbar_npf_transverse","profile_mttbar_npf_transverse",8,m_tt_range,0,1000);
   TProfile* h_profile_mttbar_sumpt_transverse= new TProfile ("profile_mttbar_sumpt_transverse","profile_mttbar_sumpt_transverse",8,m_tt_range,0,1000);
   TProfile* h_profile_mttbar_avept_transverse= new TProfile ("profile_mttbar_avept_transverse","profile_mttbar_avept_transverse",8,m_tt_range,0,1000);

   TProfile* h_profile_mttbar_npf_toward= new TProfile ("profile_mttbar_npf_toward","profile_mttbar_npf_toward",8,m_tt_range,0,1000);
   TProfile* h_profile_mttbar_sumpt_toward= new TProfile ("profile_mttbar_sumpt_toward","profile_mttbar_sumpt_toward",8,m_tt_range,0,1000);
   TProfile* h_profile_mttbar_avept_toward= new TProfile ("profile_mttbar_avept_toward","profile_mttbar_avept_toward",8,m_tt_range,0,1000);

   TProfile* h_profile_ytt_npf= new TProfile ("profile_ytt_npf","profile_ytt_npf",10,0,2.5,0,1000);
   TProfile* h_profile_ytt_sumpt= new TProfile ("profile_ytt_sumpt","profile_ytt_sumpt",10,0,2.5,0,1000);
   TProfile* h_profile_ytt_avept= new TProfile ("profile_ytt_avept","profile_ytt_avept",10,0,2.5,0,1000);

   TProfile* h_profile_ytt_npf_away= new TProfile ("profile_ytt_npf_away","profile_ytt_npf_away",10,0,2.5,0,1000);
   TProfile* h_profile_ytt_sumpt_away= new TProfile ("profile_ytt_sumpt_away","profile_ytt_sumpt_away",10,0,2.5,0,1000);
   TProfile* h_profile_ytt_avept_away= new TProfile ("profile_ytt_avept_away","profile_ytt_avept_away",10,0,2.5,0,1000);

   TProfile* h_profile_ytt_npf_transverse= new TProfile ("profile_ytt_npf_transverse","profile_ytt_npf_transverse",10,0,2.5,0,1000);
   TProfile* h_profile_ytt_sumpt_transverse= new TProfile ("profile_ytt_sumpt_transverse","profile_ytt_sumpt_transverse",10,0,2.5,0,1000);
   TProfile* h_profile_ytt_avept_transverse= new TProfile ("profile_ytt_avept_transverse","profile_ytt_avept_transverse",10,0,2.5,0,1000);

   TProfile* h_profile_ytt_npf_toward= new TProfile ("profile_ytt_npf_toward","profile_ytt_npf_toward",10,0,2.5,0,1000);
   TProfile* h_profile_ytt_sumpt_toward= new TProfile ("profile_ytt_sumpt_toward","profile_ytt_sumpt_toward",10,0,2.5,0,1000);
   TProfile* h_profile_ytt_avept_toward= new TProfile ("profile_ytt_avept_toward","profile_ytt_avept_toward",10,0,2.5,0,1000);

   TProfile* h_profile_yttj_npf= new TProfile ("profile_yttj_npf","profile_yttj_npf",10,0,2.5,0,1000);
   TProfile* h_profile_yttj_sumpt= new TProfile ("profile_yttj_sumpt","profile_yttj_sumpt",10,0,2.5,0,1000);
   TProfile* h_profile_yttj_avept= new TProfile ("profile_yttj_avept","profile_yttj_avept",10,0,2.5,0,1000);

   TProfile* h_profile_yttj_npf_away= new TProfile ("profile_yttj_npf_away","profile_yttj_npf_away",10,0,2.5,0,1000);
   TProfile* h_profile_yttj_sumpt_away= new TProfile ("profile_yttj_sumpt_away","profile_yttj_sumpt_away",10,0,2.5,0,1000);
   TProfile* h_profile_yttj_avept_away= new TProfile ("profile_yttj_avept_away","profile_yttj_avept_away",10,0,2.5,0,1000);

   TProfile* h_profile_yttj_npf_transverse= new TProfile ("profile_yttj_npf_transverse","profile_yttj_npf_transverse",10,0,2.5,0,1000);
   TProfile* h_profile_yttj_sumpt_transverse= new TProfile ("profile_yttj_sumpt_transverse","profile_yttj_sumpt_transverse",10,0,2.5,0,1000);
   TProfile* h_profile_yttj_avept_transverse= new TProfile ("profile_yttj_avept_transverse","profile_yttj_avept_transverse",10,0,2.5,0,1000);

   TProfile* h_profile_yttj_npf_toward= new TProfile ("profile_yttj_npf_toward","profile_yttj_npf_toward",10,0,2.5,0,1000);
   TProfile* h_profile_yttj_sumpt_toward= new TProfile ("profile_yttj_sumpt_toward","profile_yttj_sumpt_toward",10,0,2.5,0,1000);
   TProfile* h_profile_yttj_avept_toward= new TProfile ("profile_yttj_avept_toward","profile_yttj_avept_toward",10,0,2.5,0,1000);






   TProfile* h_profile_mtop_npf= new TProfile ("profile_mtop_npf","profile_mtop_npf",10,m_t_range,0,1000);
   TProfile* h_profile_mtop_sumpt= new TProfile ("profile_mtop_sumpt","profile_mtop_sumpt",10,m_t_range,0,1000);
   TProfile* h_profile_mtop_avept= new TProfile ("profile_mtop_avept","profile_mtop_avept",10,m_t_range,0,1000);

   TProfile* h_profile_mtop_npf_away= new TProfile ("profile_mtop_npf_away","profile_mtop_npf_away",10,m_t_range,0,1000);
   TProfile* h_profile_mtop_sumpt_away= new TProfile ("profile_mtop_sumpt_away","profile_mtop_sumpt_away",10,m_t_range,0,1000);
   TProfile* h_profile_mtop_avept_away= new TProfile ("profile_mtop_avept_away","profile_mtop_avept_away",10,m_t_range,0,1000);

   TProfile* h_profile_mtop_npf_transverse= new TProfile ("profile_mtop_npf_transverse","profile_mtop_npf_transverse",10,m_t_range,0,1000);
   TProfile* h_profile_mtop_sumpt_transverse= new TProfile ("profile_mtop_sumpt_transverse","profile_mtop_sumpt_transverse",10,m_t_range,0,1000);
   TProfile* h_profile_mtop_avept_transverse= new TProfile ("profile_mtop_avept_transverse","profile_mtop_avept_transverse",10,m_t_range,0,1000);

   TProfile* h_profile_mtop_npf_toward= new TProfile ("profile_mtop_npf_toward","profile_mtop_npf_toward",10,m_t_range,0,1000);
   TProfile* h_profile_mtop_sumpt_toward= new TProfile ("profile_mtop_sumpt_toward","profile_mtop_sumpt_toward",10,m_t_range,0,1000);
   TProfile* h_profile_mtop_avept_toward= new TProfile ("profile_mtop_avept_toward","profile_mtop_avept_toward",10,m_t_range,0,1000);

   TProfile* h_profile_matop_npf= new TProfile ("profile_matop_npf","profile_matop_npf",10,m_t_range,0,1000);
   TProfile* h_profile_matop_sumpt= new TProfile ("profile_matop_sumpt","profile_matop_sumpt",10,m_t_range,0,1000);
   TProfile* h_profile_matop_avept= new TProfile ("profile_matop_avept","profile_matop_avept",10,m_t_range,0,1000);

   TProfile* h_profile_matop_npf_away= new TProfile ("profile_matop_npf_away","profile_matop_npf_away",10,m_t_range,0,1000);
   TProfile* h_profile_matop_sumpt_away= new TProfile ("profile_matop_sumpt_away","profile_matop_sumpt_away",10,m_t_range,0,1000);
   TProfile* h_profile_matop_avept_away= new TProfile ("profile_matop_avept_away","profile_matop_avept_away",10,m_t_range,0,1000);

   TProfile* h_profile_matop_npf_transverse= new TProfile ("profile_matop_npf_transverse","profile_matop_npf_transverse",10,m_t_range,0,1000);
   TProfile* h_profile_matop_sumpt_transverse= new TProfile ("profile_matop_sumpt_transverse","profile_matop_sumpt_transverse",10,m_t_range,0,1000);
   TProfile* h_profile_matop_avept_transverse= new TProfile ("profile_matop_avept_transverse","profile_matop_avept_transverse",10,m_t_range,0,1000);

   TProfile* h_profile_matop_npf_toward= new TProfile ("profile_matop_npf_toward","profile_matop_npf_toward",10,m_t_range,0,1000);
   TProfile* h_profile_matop_sumpt_toward= new TProfile ("profile_matop_sumpt_toward","profile_matop_sumpt_toward",10,m_t_range,0,1000);
   TProfile* h_profile_matop_avept_toward= new TProfile ("profile_matop_avept_toward","profile_matop_avept_toward",10,m_t_range,0,1000);

   TProfile* h_profile_pttop_npf= new TProfile ("profile_pttop_npf","profile_pttop_npf",8,pt_t_range,0,1000);
   TProfile* h_profile_pttop_sumpt= new TProfile ("profile_pttop_sumpt","profile_pttop_sumpt",8,pt_t_range,0,1000);
   TProfile* h_profile_pttop_avept= new TProfile ("profile_pttop_avept","profile_pttop_avept",8,pt_t_range,0,1000);

   TProfile* h_profile_pttop_npf_away= new TProfile ("profile_pttop_npf_away","profile_pttop_npf_away",8,pt_t_range,0,1000);
   TProfile* h_profile_pttop_sumpt_away= new TProfile ("profile_pttop_sumpt_away","profile_pttop_sumpt_away",8,pt_t_range,0,1000);
   TProfile* h_profile_pttop_avept_away= new TProfile ("profile_pttop_avept_away","profile_pttop_avept_away",8,pt_t_range,0,1000);

   TProfile* h_profile_pttop_npf_transverse= new TProfile ("profile_pttop_npf_transverse","profile_pttop_npf_transverse",8,pt_t_range,0,1000);
   TProfile* h_profile_pttop_sumpt_transverse= new TProfile ("profile_pttop_sumpt_transverse","profile_pttop_sumpt_transverse",8,pt_t_range,0,1000);
   TProfile* h_profile_pttop_avept_transverse= new TProfile ("profile_pttop_avept_transverse","profile_pttop_avept_transverse",8,pt_t_range,0,1000);

   TProfile* h_profile_pttop_npf_toward= new TProfile ("profile_pttop_npf_toward","profile_pttop_npf_toward",8,pt_t_range,0,1000);
   TProfile* h_profile_pttop_sumpt_toward= new TProfile ("profile_pttop_sumpt_toward","profile_pttop_sumpt_toward",8,pt_t_range,0,1000);
   TProfile* h_profile_pttop_avept_toward= new TProfile ("profile_pttop_avept_toward","profile_pttop_avept_toward",8,pt_t_range,0,1000);

   TProfile* h_profile_ptatop_npf= new TProfile ("profile_ptatop_npf","profile_ptatop_npf",8,pt_t_range,0,1000);
   TProfile* h_profile_ptatop_sumpt= new TProfile ("profile_ptatop_sumpt","profile_ptatop_sumpt",8,pt_t_range,0,1000);
   TProfile* h_profile_ptatop_avept= new TProfile ("profile_ptatop_avept","profile_ptatop_avept",8,pt_t_range,0,1000);

   TProfile* h_profile_ptatop_npf_away= new TProfile ("profile_ptatop_npf_away","profile_ptatop_npf_away",8,pt_t_range,0,1000);
   TProfile* h_profile_ptatop_sumpt_away= new TProfile ("profile_ptatop_sumpt_away","profile_ptatop_sumpt_away",8,pt_t_range,0,1000);
   TProfile* h_profile_ptatop_avept_away= new TProfile ("profile_ptatop_avept_away","profile_ptatop_avept_away",8,pt_t_range,0,1000);

   TProfile* h_profile_ptatop_npf_transverse= new TProfile ("profile_ptatop_npf_transverse","profile_ptatop_npf_transverse",8,pt_t_range,0,1000);
   TProfile* h_profile_ptatop_sumpt_transverse= new TProfile ("profile_ptatop_sumpt_transverse","profile_ptatop_sumpt_transverse",8,pt_t_range,0,1000);
   TProfile* h_profile_ptatop_avept_transverse= new TProfile ("profile_ptatop_avept_transverse","profile_ptatop_avept_transverse",8,pt_t_range,0,1000);

   TProfile* h_profile_ptatop_npf_toward= new TProfile ("profile_ptatop_npf_toward","profile_ptatop_npf_toward",8,pt_t_range,0,1000);
   TProfile* h_profile_ptatop_sumpt_toward= new TProfile ("profile_ptatop_sumpt_toward","profile_ptatop_sumpt_toward",8,pt_t_range,0,1000);
   TProfile* h_profile_ptatop_avept_toward= new TProfile ("profile_ptatop_avept_toward","profile_ptatop_avept_toward",8,pt_t_range,0,1000);



   TProfile* h_profile_ytop_npf= new TProfile ("profile_ytop_npf","profile_ytop_npf",10,0,2.5,0,1000);
   TProfile* h_profile_ytop_sumpt= new TProfile ("profile_ytop_sumpt","profile_ytop_sumpt",10,0,2.5,0,1000);
   TProfile* h_profile_ytop_avept= new TProfile ("profile_ytop_avept","profile_ytop_avept",10,0,2.5,0,1000);

   TProfile* h_profile_ytop_npf_away= new TProfile ("profile_ytop_npf_away","profile_ytop_npf_away",10,0,2.5,0,1000);
   TProfile* h_profile_ytop_sumpt_away= new TProfile ("profile_ytop_sumpt_away","profile_ytop_sumpt_away",10,0,2.5,0,1000);
   TProfile* h_profile_ytop_avept_away= new TProfile ("profile_ytop_avept_away","profile_ytop_avept_away",10,0,2.5,0,1000);

   TProfile* h_profile_ytop_npf_transverse= new TProfile ("profile_ytop_npf_transverse","profile_ytop_npf_transverse",10,0,2.5,0,1000);
   TProfile* h_profile_ytop_sumpt_transverse= new TProfile ("profile_ytop_sumpt_transverse","profile_ytop_sumpt_transverse",10,0,2.5,0,1000);
   TProfile* h_profile_ytop_avept_transverse= new TProfile ("profile_ytop_avept_transverse","profile_ytop_avept_transverse",10,0,2.5,0,1000);

   TProfile* h_profile_ytop_npf_toward= new TProfile ("profile_ytop_npf_toward","profile_ytop_npf_toward",10,0,2.5,0,1000);
   TProfile* h_profile_ytop_sumpt_toward= new TProfile ("profile_ytop_sumpt_toward","profile_ytop_sumpt_toward",10,0,2.5,0,1000);
   TProfile* h_profile_ytop_avept_toward= new TProfile ("profile_ytop_avept_toward","profile_ytop_avept_toward",10,0,2.5,0,1000);

   TProfile* h_profile_yatop_npf= new TProfile ("profile_yatop_npf","profile_yatop_npf",10,0,2.5,0,1000);
   TProfile* h_profile_yatop_sumpt= new TProfile ("profile_yatop_sumpt","profile_yatop_sumpt",10,0,2.5,0,1000);
   TProfile* h_profile_yatop_avept= new TProfile ("profile_yatop_avept","profile_yatop_avept",10,0,2.5,0,1000);

   TProfile* h_profile_yatop_npf_away= new TProfile ("profile_yatop_npf_away","profile_yatop_npf_away",10,0,2.5,0,1000);
   TProfile* h_profile_yatop_sumpt_away= new TProfile ("profile_yatop_sumpt_away","profile_yatop_sumpt_away",10,0,2.5,0,1000);
   TProfile* h_profile_yatop_avept_away= new TProfile ("profile_yatop_avept_away","profile_yatop_avept_away",10,0,2.5,0,1000);

   TProfile* h_profile_yatop_npf_transverse= new TProfile ("profile_yatop_npf_transverse","profile_yatop_npf_transverse",10,0,2.5,0,1000);
   TProfile* h_profile_yatop_sumpt_transverse= new TProfile ("profile_yatop_sumpt_transverse","profile_yatop_sumpt_transverse",10,0,2.5,0,1000);
   TProfile* h_profile_yatop_avept_transverse= new TProfile ("profile_yatop_avept_transverse","profile_yatop_avept_transverse",10,0,2.5,0,1000);

   TProfile* h_profile_yatop_npf_toward= new TProfile ("profile_yatop_npf_toward","profile_yatop_npf_toward",10,0,2.5,0,1000);
   TProfile* h_profile_yatop_sumpt_toward= new TProfile ("profile_yatop_sumpt_toward","profile_yatop_sumpt_toward",10,0,2.5,0,1000);
   TProfile* h_profile_yatop_avept_toward= new TProfile ("profile_yatop_avept_toward","profile_yatop_avept_toward",10,0,2.5,0,1000);




   TProfile* h_profile_mthad_npf= new TProfile ("profile_mthad_npf","profile_mthad_npf",10,m_t_range,0,1000);
   TProfile* h_profile_mthad_sumpt= new TProfile ("profile_mthad_sumpt","profile_mthad_sumpt",10,m_t_range,0,1000);
   TProfile* h_profile_mthad_avept= new TProfile ("profile_mthad_avept","profile_mthad_avept",10,m_t_range,0,1000);

   TProfile* h_profile_mthad_npf_away= new TProfile ("profile_mthad_npf_away","profile_mthad_npf_away",10,m_t_range,0,1000);
   TProfile* h_profile_mthad_sumpt_away= new TProfile ("profile_mthad_sumpt_away","profile_mthad_sumpt_away",10,m_t_range,0,1000);
   TProfile* h_profile_mthad_avept_away= new TProfile ("profile_mthad_avept_away","profile_mthad_avept_away",10,m_t_range,0,1000);

   TProfile* h_profile_mthad_npf_transverse= new TProfile ("profile_mthad_npf_transverse","profile_mthad_npf_transverse",10,m_t_range,0,1000);
   TProfile* h_profile_mthad_sumpt_transverse= new TProfile ("profile_mthad_sumpt_transverse","profile_mthad_sumpt_transverse",10,m_t_range,0,1000);
   TProfile* h_profile_mthad_avept_transverse= new TProfile ("profile_mthad_avept_transverse","profile_mthad_avept_transverse",10,m_t_range,0,1000);

   TProfile* h_profile_mthad_npf_toward= new TProfile ("profile_mthad_npf_toward","profile_mthad_npf_toward",10,m_t_range,0,1000);
   TProfile* h_profile_mthad_sumpt_toward= new TProfile ("profile_mthad_sumpt_toward","profile_mthad_sumpt_toward",10,m_t_range,0,1000);
   TProfile* h_profile_mthad_avept_toward= new TProfile ("profile_mthad_avept_toward","profile_mthad_avept_toward",10,m_t_range,0,1000);

   TProfile* h_profile_mtlep_npf= new TProfile ("profile_mtlep_npf","profile_mtlep_npf",10,m_t_range,0,1000);
   TProfile* h_profile_mtlep_sumpt= new TProfile ("profile_mtlep_sumpt","profile_mtlep_sumpt",10,m_t_range,0,1000);
   TProfile* h_profile_mtlep_avept= new TProfile ("profile_mtlep_avept","profile_mtlep_avept",10,m_t_range,0,1000);

   TProfile* h_profile_mtlep_npf_away= new TProfile ("profile_mtlep_npf_away","profile_mtlep_npf_away",10,m_t_range,0,1000);
   TProfile* h_profile_mtlep_sumpt_away= new TProfile ("profile_mtlep_sumpt_away","profile_mtlep_sumpt_away",10,m_t_range,0,1000);
   TProfile* h_profile_mtlep_avept_away= new TProfile ("profile_mtlep_avept_away","profile_mtlep_avept_away",10,m_t_range,0,1000);

   TProfile* h_profile_mtlep_npf_transverse= new TProfile ("profile_mtlep_npf_transverse","profile_mtlep_npf_transverse",10,m_t_range,0,1000);
   TProfile* h_profile_mtlep_sumpt_transverse= new TProfile ("profile_mtlep_sumpt_transverse","profile_mtlep_sumpt_transverse",10,m_t_range,0,1000);
   TProfile* h_profile_mtlep_avept_transverse= new TProfile ("profile_mtlep_avept_transverse","profile_mtlep_avept_transverse",10,m_t_range,0,1000);

   TProfile* h_profile_mtlep_npf_toward= new TProfile ("profile_mtlep_npf_toward","profile_mtlep_npf_toward",10,m_t_range,0,1000);
   TProfile* h_profile_mtlep_sumpt_toward= new TProfile ("profile_mtlep_sumpt_toward","profile_mtlep_sumpt_toward",10,m_t_range,0,1000);
   TProfile* h_profile_mtlep_avept_toward= new TProfile ("profile_mtlep_avept_toward","profile_mtlep_avept_toward",10,m_t_range,0,1000);

   TProfile* h_profile_ptthad_npf= new TProfile ("profile_ptthad_npf","profile_ptthad_npf",8,pt_t_range,0,1000);
   TProfile* h_profile_ptthad_sumpt= new TProfile ("profile_ptthad_sumpt","profile_ptthad_sumpt",8,pt_t_range,0,1000);
   TProfile* h_profile_ptthad_avept= new TProfile ("profile_ptthad_avept","profile_ptthad_avept",8,pt_t_range,0,1000);

   TProfile* h_profile_ptthad_npf_away= new TProfile ("profile_ptthad_npf_away","profile_ptthad_npf_away",8,pt_t_range,0,1000);
   TProfile* h_profile_ptthad_sumpt_away= new TProfile ("profile_ptthad_sumpt_away","profile_ptthad_sumpt_away",8,pt_t_range,0,1000);
   TProfile* h_profile_ptthad_avept_away= new TProfile ("profile_ptthad_avept_away","profile_ptthad_avept_away",8,pt_t_range,0,1000);

   TProfile* h_profile_ptthad_npf_transverse= new TProfile ("profile_ptthad_npf_transverse","profile_ptthad_npf_transverse",8,pt_t_range,0,1000);
   TProfile* h_profile_ptthad_sumpt_transverse= new TProfile ("profile_ptthad_sumpt_transverse","profile_ptthad_sumpt_transverse",8,pt_t_range,0,1000);
   TProfile* h_profile_ptthad_avept_transverse= new TProfile ("profile_ptthad_avept_transverse","profile_ptthad_avept_transverse",8,pt_t_range,0,1000);

   TProfile* h_profile_ptthad_npf_toward= new TProfile ("profile_ptthad_npf_toward","profile_ptthad_npf_toward",8,pt_t_range,0,1000);
   TProfile* h_profile_ptthad_sumpt_toward= new TProfile ("profile_ptthad_sumpt_toward","profile_ptthad_sumpt_toward",8,pt_t_range,0,1000);
   TProfile* h_profile_ptthad_avept_toward= new TProfile ("profile_ptthad_avept_toward","profile_ptthad_avept_toward",8,pt_t_range,0,1000);

   TProfile* h_profile_pttlep_npf= new TProfile ("profile_pttlep_npf","profile_pttlep_npf",8,pt_t_range,0,1000);
   TProfile* h_profile_pttlep_sumpt= new TProfile ("profile_pttlep_sumpt","profile_pttlep_sumpt",8,pt_t_range,0,1000);
   TProfile* h_profile_pttlep_avept= new TProfile ("profile_pttlep_avept","profile_pttlep_avept",8,pt_t_range,0,1000);

   TProfile* h_profile_pttlep_npf_away= new TProfile ("profile_pttlep_npf_away","profile_pttlep_npf_away",8,pt_t_range,0,1000);
   TProfile* h_profile_pttlep_sumpt_away= new TProfile ("profile_pttlep_sumpt_away","profile_pttlep_sumpt_away",8,pt_t_range,0,1000);
   TProfile* h_profile_pttlep_avept_away= new TProfile ("profile_pttlep_avept_away","profile_pttlep_avept_away",8,pt_t_range,0,1000);

   TProfile* h_profile_pttlep_npf_transverse= new TProfile ("profile_pttlep_npf_transverse","profile_pttlep_npf_transverse",8,pt_t_range,0,1000);
   TProfile* h_profile_pttlep_sumpt_transverse= new TProfile ("profile_pttlep_sumpt_transverse","profile_pttlep_sumpt_transverse",8,pt_t_range,0,1000);
   TProfile* h_profile_pttlep_avept_transverse= new TProfile ("profile_pttlep_avept_transverse","profile_pttlep_avept_transverse",8,pt_t_range,0,1000);

   TProfile* h_profile_pttlep_npf_toward= new TProfile ("profile_pttlep_npf_toward","profile_pttlep_npf_toward",8,pt_t_range,0,1000);
   TProfile* h_profile_pttlep_sumpt_toward= new TProfile ("profile_pttlep_sumpt_toward","profile_pttlep_sumpt_toward",8,pt_t_range,0,1000);
   TProfile* h_profile_pttlep_avept_toward= new TProfile ("profile_pttlep_avept_toward","profile_pttlep_avept_toward",8,pt_t_range,0,1000);



   TProfile* h_profile_ythad_npf= new TProfile ("profile_ythad_npf","profile_ythad_npf",10,0,2.5,0,1000);
   TProfile* h_profile_ythad_sumpt= new TProfile ("profile_ythad_sumpt","profile_ythad_sumpt",10,0,2.5,0,1000);
   TProfile* h_profile_ythad_avept= new TProfile ("profile_ythad_avept","profile_ythad_avept",10,0,2.5,0,1000);

   TProfile* h_profile_ythad_npf_away= new TProfile ("profile_ythad_npf_away","profile_ythad_npf_away",10,0,2.5,0,1000);
   TProfile* h_profile_ythad_sumpt_away= new TProfile ("profile_ythad_sumpt_away","profile_ythad_sumpt_away",10,0,2.5,0,1000);
   TProfile* h_profile_ythad_avept_away= new TProfile ("profile_ythad_avept_away","profile_ythad_avept_away",10,0,2.5,0,1000);

   TProfile* h_profile_ythad_npf_transverse= new TProfile ("profile_ythad_npf_transverse","profile_ythad_npf_transverse",10,0,2.5,0,1000);
   TProfile* h_profile_ythad_sumpt_transverse= new TProfile ("profile_ythad_sumpt_transverse","profile_ythad_sumpt_transverse",10,0,2.5,0,1000);
   TProfile* h_profile_ythad_avept_transverse= new TProfile ("profile_ythad_avept_transverse","profile_ythad_avept_transverse",10,0,2.5,0,1000);

   TProfile* h_profile_ythad_npf_toward= new TProfile ("profile_ythad_npf_toward","profile_ythad_npf_toward",10,0,2.5,0,1000);
   TProfile* h_profile_ythad_sumpt_toward= new TProfile ("profile_ythad_sumpt_toward","profile_ythad_sumpt_toward",10,0,2.5,0,1000);
   TProfile* h_profile_ythad_avept_toward= new TProfile ("profile_ythad_avept_toward","profile_ythad_avept_toward",10,0,2.5,0,1000);

   TProfile* h_profile_ytlep_npf= new TProfile ("profile_ytlep_npf","profile_ytlep_npf",10,0,2.5,0,1000);
   TProfile* h_profile_ytlep_sumpt= new TProfile ("profile_ytlep_sumpt","profile_ytlep_sumpt",10,0,2.5,0,1000);
   TProfile* h_profile_ytlep_avept= new TProfile ("profile_ytlep_avept","profile_ytlep_avept",10,0,2.5,0,1000);

   TProfile* h_profile_ytlep_npf_away= new TProfile ("profile_ytlep_npf_away","profile_ytlep_npf_away",10,0,2.5,0,1000);
   TProfile* h_profile_ytlep_sumpt_away= new TProfile ("profile_ytlep_sumpt_away","profile_ytlep_sumpt_away",10,0,2.5,0,1000);
   TProfile* h_profile_ytlep_avept_away= new TProfile ("profile_ytlep_avept_away","profile_ytlep_avept_away",10,0,2.5,0,1000);

   TProfile* h_profile_ytlep_npf_transverse= new TProfile ("profile_ytlep_npf_transverse","profile_ytlep_npf_transverse",10,0,2.5,0,1000);
   TProfile* h_profile_ytlep_sumpt_transverse= new TProfile ("profile_ytlep_sumpt_transverse","profile_ytlep_sumpt_transverse",10,0,2.5,0,1000);
   TProfile* h_profile_ytlep_avept_transverse= new TProfile ("profile_ytlep_avept_transverse","profile_ytlep_avept_transverse",10,0,2.5,0,1000);

   TProfile* h_profile_ytlep_npf_toward= new TProfile ("profile_ytlep_npf_toward","profile_ytlep_npf_toward",10,0,2.5,0,1000);
   TProfile* h_profile_ytlep_sumpt_toward= new TProfile ("profile_ytlep_sumpt_toward","profile_ytlep_sumpt_toward",10,0,2.5,0,1000);
   TProfile* h_profile_ytlep_avept_toward= new TProfile ("profile_ytlep_avept_toward","profile_ytlep_avept_toward",10,0,2.5,0,1000);




   TProfile* h_profile_mt_npf= new TProfile ("profile_mt_npf","profile_mt_npf",10,m_t_range,0,1000);
   TProfile* h_profile_mt_sumpt= new TProfile ("profile_mt_sumpt","profile_mt_sumpt",10,m_t_range,0,1000);
   TProfile* h_profile_mt_avept= new TProfile ("profile_mt_avept","profile_mt_avept",10,m_t_range,0,1000);

   TProfile* h_profile_mt_npf_away= new TProfile ("profile_mt_npf_away","profile_mt_npf_away",10,m_t_range,0,1000);
   TProfile* h_profile_mt_sumpt_away= new TProfile ("profile_mt_sumpt_away","profile_mt_sumpt_away",10,m_t_range,0,1000);
   TProfile* h_profile_mt_avept_away= new TProfile ("profile_mt_avept_away","profile_mt_avept_away",10,m_t_range,0,1000);

   TProfile* h_profile_mt_npf_transverse= new TProfile ("profile_mt_npf_transverse","profile_mt_npf_transverse",10,m_t_range,0,1000);
   TProfile* h_profile_mt_sumpt_transverse= new TProfile ("profile_mt_sumpt_transverse","profile_mt_sumpt_transverse",10,m_t_range,0,1000);
   TProfile* h_profile_mt_avept_transverse= new TProfile ("profile_mt_avept_transverse","profile_mt_avept_transverse",10,m_t_range,0,1000);

   TProfile* h_profile_mt_npf_toward= new TProfile ("profile_mt_npf_toward","profile_mt_npf_toward",10,m_t_range,0,1000);
   TProfile* h_profile_mt_sumpt_toward= new TProfile ("profile_mt_sumpt_toward","profile_mt_sumpt_toward",10,m_t_range,0,1000);
   TProfile* h_profile_mt_avept_toward= new TProfile ("profile_mt_avept_toward","profile_mt_avept_toward",10,m_t_range,0,1000);

   TProfile* h_profile_ptt_npf= new TProfile ("profile_ptt_npf","profile_ptt_npf",8,pt_t_range,0,1000);
   TProfile* h_profile_ptt_sumpt= new TProfile ("profile_ptt_sumpt","profile_ptt_sumpt",8,pt_t_range,0,1000);
   TProfile* h_profile_ptt_avept= new TProfile ("profile_ptt_avept","profile_ptt_avept",8,pt_t_range,0,1000);

   TProfile* h_profile_ptt_npf_away= new TProfile ("profile_ptt_npf_away","profile_ptt_npf_away",8,pt_t_range,0,1000);
   TProfile* h_profile_ptt_sumpt_away= new TProfile ("profile_ptt_sumpt_away","profile_ptt_sumpt_away",8,pt_t_range,0,1000);
   TProfile* h_profile_ptt_avept_away= new TProfile ("profile_ptt_avept_away","profile_ptt_avept_away",8,pt_t_range,0,1000);

   TProfile* h_profile_ptt_npf_transverse= new TProfile ("profile_ptt_npf_transverse","profile_ptt_npf_transverse",8,pt_t_range,0,1000);
   TProfile* h_profile_ptt_sumpt_transverse= new TProfile ("profile_ptt_sumpt_transverse","profile_ptt_sumpt_transverse",8,pt_t_range,0,1000);
   TProfile* h_profile_ptt_avept_transverse= new TProfile ("profile_ptt_avept_transverse","profile_ptt_avept_transverse",8,pt_t_range,0,1000);

   TProfile* h_profile_ptt_npf_toward= new TProfile ("profile_ptt_npf_toward","profile_ptt_npf_toward",8,pt_t_range,0,1000);
   TProfile* h_profile_ptt_sumpt_toward= new TProfile ("profile_ptt_sumpt_toward","profile_ptt_sumpt_toward",8,pt_t_range,0,1000);
   TProfile* h_profile_ptt_avept_toward= new TProfile ("profile_ptt_avept_toward","profile_ptt_avept_toward",8,pt_t_range,0,1000);


   TProfile* h_profile_yt_npf= new TProfile ("profile_yt_npf","profile_yt_npf",10,0,2.5,0,1000);
   TProfile* h_profile_yt_sumpt= new TProfile ("profile_yt_sumpt","profile_yt_sumpt",10,0,2.5,0,1000);
   TProfile* h_profile_yt_avept= new TProfile ("profile_yt_avept","profile_yt_avept",10,0,2.5,0,1000);

   TProfile* h_profile_yt_npf_away= new TProfile ("profile_yt_npf_away","profile_yt_npf_away",10,0,2.5,0,1000);
   TProfile* h_profile_yt_sumpt_away= new TProfile ("profile_yt_sumpt_away","profile_yt_sumpt_away",10,0,2.5,0,1000);
   TProfile* h_profile_yt_avept_away= new TProfile ("profile_yt_avept_away","profile_yt_avept_away",10,0,2.5,0,1000);

   TProfile* h_profile_yt_npf_transverse= new TProfile ("profile_yt_npf_transverse","profile_yt_npf_transverse",10,0,2.5,0,1000);
   TProfile* h_profile_yt_sumpt_transverse= new TProfile ("profile_yt_sumpt_transverse","profile_yt_sumpt_transverse",10,0,2.5,0,1000);
   TProfile* h_profile_yt_avept_transverse= new TProfile ("profile_yt_avept_transverse","profile_yt_avept_transverse",10,0,2.5,0,1000);

   TProfile* h_profile_yt_npf_toward= new TProfile ("profile_yt_npf_toward","profile_yt_npf_toward",10,0,2.5,0,1000);
   TProfile* h_profile_yt_sumpt_toward= new TProfile ("profile_yt_sumpt_toward","profile_yt_sumpt_toward",10,0,2.5,0,1000);
   TProfile* h_profile_yt_avept_toward= new TProfile ("profile_yt_avept_toward","profile_yt_avept_toward",10,0,2.5,0,1000);




   TH1* h_nvtx= new TH1D ("nvtx_npf","nvtx_npf",50,0,50);
   TH1* h_pf_dxy= new TH1D ("pf_dxy","pf_dxy",1000,0,2);
   TH1* h_pf_dz= new TH1D ("pf_dz","pf_dz",1000,0,25);
   TH1* h_pf_sigmadxy= new TH1D ("pf_sigmadxy","pf_sigmadxy",1000,0,25);
   TH1* h_pf_sigmadz= new TH1D ("pf_sigmadz","pf_sigmadz",1000,0,25);
   TH1* h_pf_pt=new TH1D ("pf_pt","pf_pt",20000,0,2000);
   TH1* h_csv=new TH1D("csv","csv",1000,-1,1);
   TH1* h_csvmax=new TH1D("csvmax","csvmax",1000,-1,1);
   TH1* h_csvmax2=new TH1D("csvmax2","csvmax2",1000,-1,1);
   TH1* h_npf_inclusive=new TH1D ("npf_inclusive","npf_inclusive",140,0,140);
   TH1* h_npf_toward=new TH1D ("npf_toward","npf_toward",140,0,140);
   TH1* h_npf_transverse=new TH1D ("npf_transverse","npf_transverse",140,0,140);
   TH1* h_npf_away=new TH1D ("npf_away","npf_away",140,0,140);

   TH1* h_ptsumpf_inclusive=new TH1D ("ptsumpf_inclusive","ptsumpf_inclusive",100,0,500);
   TH1* h_ptsumpf_toward=new TH1D ("ptsumpf_toward","ptsumpf_toward",100,0,500);
   TH1* h_ptsumpf_transverse=new TH1D ("ptsumpf_transverse","ptsumpf_transverse",100,0,500);
   TH1* h_ptsumpf_away=new TH1D ("ptsumpf_away","ptsumpf_away",100,0,500);

   TH1* h_ptavepf_inclusive=new TH1D ("ptavepf_inclusive","ptavepf_inclusive",50,0,25);
   TH1* h_ptavepf_toward=new TH1D ("ptavepf_toward","ptavepf_toward",50,0,25);
   TH1* h_ptavepf_transverse=new TH1D ("ptavepf_transverse","ptavepf_transverse",50,0,25);
   TH1* h_ptavepf_away=new TH1D ("ptavepf_away","ptavepf_away",50,0,25);

TH1*h_puweight=new TH1D("puweight","puweight",10000,0,1000);
TH1*h_puweight_weighted=new TH1D("puweight_weighted","puweight_weighted",10000,0,1000);

TH1*h_puweight_meas=new TH1D("puweight_meas","puweight_meas",10000,0,1000);
TH1*h_puweight_weighted_meas=new TH1D("puweight_weighted_meas","puweight_weighted_meas",10000,0,1000);
   TH1* h_MTW= new TH1D ("MTW","MTW",100,0,1000);
   TH1* h_m_thad= new TH1D ("m_thad","m_thad",10,m_t_range);
   TH1* h_m_thad_fixbin= new TH1D ("m_thad_fixbin","m_thad_fixbin",200,0,1000);
   TH1* h_m_tlep= new TH1D ("m_tlep","m_tlep",10,m_t_range);
   TH1* h_m_tlep_fixbin= new TH1D ("m_tlep_fixbin","m_tlep_fixbin",200,0,1000);

   TH1* h_m_top= new TH1D ("m_top","m_top",10,m_t_range);
   TH1* h_m_atop= new TH1D ("m_atop","m_atop",10,m_t_range);

   TH1* h_pt_top= new TH1D ("pt_top","pt_top",8,pt_t_range);
   TH1* h_pt_atop= new TH1D ("pt_atop","pt_atop",8,pt_t_range);

   TH1* h_m_top_fixbin= new TH1D ("m_top_fixbin","m_top_fixbin",200,0,1000);
   TH1* h_m_atop_fixbin= new TH1D ("m_atop_fixbin","m_atop_fixbin",200,0,1000);

   TH1* h_pt_top_fixbin= new TH1D ("pt_top_fixbin","pt_top_fixbin",200,0,1000);
   TH1* h_pt_atop_fixbin= new TH1D ("pt_atop_fixbin","pt_atop_fixbin",200,0,1000);


  TH1* h_y_top= new TH1D ("y_top","y_top",100,-5.,5.);
   TH1* h_y_atop= new TH1D ("y_atop","y_atop",100,-5.,5.);

     TH1*   h_rec_ttjY= new TH1D ("rec_ttjY","rec_ttjY",50,-5,5);

   TH1* h_m_ttbar= new TH1D ("m_ttbar","m_ttbar",8,m_tt_range);
   TH1* h_m_ttbar_fixbin= new TH1D ("m_ttbar_fixbin","m_ttbar_fixbin",400,0,2000);
   TH1* h_y_ttbar= new TH1D ("y_ttbar","y_ttbar",100,-5.,5.);

   TH1* h_pt_thad= new TH1D ("pt_thad","pt_thad",8,pt_t_range);
   TH1* h_pt_thad_fixbin= new TH1D ("pt_thad_fixbin","pt_thad_fixbin",200,0,1000);
   TH1* h_pt_tlep= new TH1D ("pt_tlep","pt_tlep",8,pt_t_range);
   TH1* h_pt_tlep_fixbin= new TH1D ("pt_tlep_fixbin","pt_tlep_fixbin",200,0,1000);
  TH1* h_y_thad= new TH1D ("y_thad","y_thad",100,-5.,5.);
   TH1* h_y_tlep= new TH1D ("y_tlep","y_tlep",100,-5.,5.);
   TH1* h_m_t= new TH1D ("m_t","m_t",10,m_t_range);
   TH1* h_m_t_fixbin= new TH1D ("m_t_fixbin","m_t_fixbin",200,0,1000);
   TH1* h_pt_t= new TH1D ("pt_t","pt_t",8,pt_t_range);
   TH1* h_pt_t_fixbin= new TH1D ("pt_t_fixbin","pt_t_fixbin",200,0,1000);
  TH1* h_y_t= new TH1D ("y_t","y_t",100,-5.,5.);



   double wtot=0;
   double sum_tot_weight=0;
   int sum_no=0;
   int N_HLT_Mu20=0;
   int N_HLT_TkMu20=0;
   int N_HLT_Mu18=0;
   int N_HLT_TkMu18=0;
   int N_HLT_Mu20_eta2p1=0;
   int N_HLT_TkMu20_eta2p1=0;
   int N_HLT_Mu18_eta2p1=0;
   int N_HLT_TkMu18_eta2p1=0;
   int N_HLT_Mu24_eta2p1=0;
   int N_HLT_TkMu20ORMu20=0;
   int ntottt=0;
   double real_count=0;
   double complex_count=0;
   double solved_complex_count=0;

/*
   double mu_tot_b_jet=0;
   double mu_tot_b_tagged_jet=0;
   double mu_tot_c_jet=0;
   double mu_tot_c_tagged_jet=0;
   double mu_tot_udsg_jet=0;
   double mu_tot_udsg_tagged_jet=0;
   double tot_b_jet=0;
   double tot_b_tagged_jet=0;
   double tot_c_jet=0;
   double tot_c_tagged_jet=0;
   double tot_udsg_jet=0;
   double tot_udsg_tagged_jet=0;
*/


   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(jentry%10000==0)cout<<name<<" << "<<jentry<<"/"<<nentries<<endl;
      // if (Cut(ientry) < 0) continue;
//cout<<int(PU_npT)<<"  "<<puWeight.weight(int(PU_npT))<<endl;
      //if(run>258158)continue;
      int mu_index=0;	
      int mu_index20=0;	
      vector<TLorentzVector>mu_vector;
      vector<TLorentzVector>mu_vector20;
      vector<int>mu_charge;
      vector<unsigned int>b_jet_index;
      vector<unsigned int>l_jet_index;
      int jet_index=0;	
      int njet_15=0;
      vector<TLorentzVector>jet_vector;
      vector<double> jet_part_flav;
      vector<TLorentzVector>jet_vector_1530;
      vector<vector<double> >jet_ConstId;
      vector<vector<double> >jet_ConstPt;
      vector<vector<double> >jet_ConstEta;
      vector<vector<double> > jet_ConstPhi;
      vector<vector<double> >jet_ConstE;
      int st1mu=0;
//cout<<"1111111111"<<endl;
      for(unsigned int st1_ind=0; st1_ind<Bare01LepPt->size();st1_ind++){
       // cout<<Bare01LepId->at(st1_ind)<<"  "<<Bare01LepStatus->at(st1_ind)<<endl;
        if(fabs(Bare01LepId->at(st1_ind))==13)st1mu++;
      }
      if(dosignal &&st1mu!=1 ) continue;
      if(dottother &&st1mu==1 )continue;
//cout<<"kkkkkkkkkkkkkkkkkkkkkkkkkk"<<endl;

      double w=1;
      if(mcWeights_->size()>0)w=mcWeights_->at(0);
//cout<<"tttttttttttttttt"<<endl;
      if(!realdata && PU_npT>0){    
//        wtot_write-=w;
        w*=puWeight.weight(int(PU_npT));  
        sum_tot_weight+= puWeight.weight(int(PU_npT));
        sum_no++;
//        wtot_write+=w;
      }
      h_puweight->Fill(puWeight.weight(int(PU_npT)));
      h_puweight_weighted->Fill(puWeight.weight(int(PU_npT)),w);
      wtot+=wtot_write;
//cout<<"aaaaaaaaaaaaaaaaaaaaaaa"<<endl;
     if(!HLT_IsoTkMu20&&!HLT_IsoMu20) continue; //OR requirement of IsoTkMu20 and IsoMu20
      for(unsigned int mu_ind=0; mu_ind<patMuonPt_->size();mu_ind++){
        if(patMuonCombId_->at(mu_ind)>0&& fabs(patMuonEta_->at(mu_ind))<2.1){
          h_mu_pt->Fill(patMuonPt_->at(mu_ind),w);
          h_mu_eta->Fill(patMuonEta_->at(mu_ind),w);
          h_mu_phi->Fill(patMuonPhi_->at(mu_ind),w);
          h_mu_iso->Fill(patMuonPfIsoDbeta_->at(mu_ind),w);
        }
        if(patMuonPt_->at(mu_ind)>22 && fabs(patMuonEta_->at(mu_ind))<2.4 &&patMuonCombId_->at(mu_ind)>0 &&fabs(patMuonPfIsoDbeta_->at(mu_ind))<0.15){
          TLorentzVector tmp;
          tmp.SetPtEtaPhiE(patMuonPt_->at(mu_ind),patMuonEta_->at(mu_ind),patMuonPhi_->at(mu_ind),patMuonEn_->at(mu_ind));
          mu_vector.push_back(tmp);
          mu_charge.push_back(patMuonCharge_->at(mu_ind));
          mu_index++;
       }
        if(patMuonPt_->at(mu_ind)>15 && fabs(patMuonEta_->at(mu_ind))<2.4 && fabs(patMuonPfIsoDbeta_->at(mu_ind))<0.3){
          mu_index20++;
       }
     }

     double nom=1, denom=1;
//cout<<"2222222222"<<endl;
      int ind_jet_const=0;
      double csvmax=-99., csvmax2=-99.;
      for(unsigned int jet_ind=0; jet_ind<patJetPfAk04Pt_->size();jet_ind++){
        if(jet_ind>=1)ind_jet_const+=patJetPfAk04nconst_->at(jet_ind-1);
        if( fabs(patJetPfAk04Eta_->at(jet_ind))>2.4 ||patJetPfAk04LooseId_->at(jet_ind)==0)continue;

        TLorentzVector tmp;
        tmp.SetPtEtaPhiE(patJetPfAk04Pt_->at(jet_ind),patJetPfAk04Eta_->at(jet_ind),patJetPfAk04Phi_->at(jet_ind),patJetPfAk04En_->at(jet_ind));

        double dr_j_l=99;
        if(mu_index>0) dr_j_l=DeltaR(tmp.Eta(),mu_vector[0].Eta(),tmp.Phi(),mu_vector[0].Phi());

        if(dr_j_l<0.4)continue;
        if(patJetPfAk04Pt_->at(jet_ind)>15.)njet_15++;
       if(patJetPfAk04Pt_->at(jet_ind)>15. &&patJetPfAk04Pt_->at(jet_ind)<30.)jet_vector_1530.push_back(tmp);
        if(patJetPfAk04Pt_->at(jet_ind)<30.)continue;
        jet_vector.push_back(tmp);
        //jet_part_flav.push_back(patJetPfAk04PartonFlavour_->at(jet_ind));
        if(mu_index==1 &&mu_index20==1)h_csv->Fill(patJetPfAk04BDiscCSVv2_->at(jet_ind),w);
        if(patJetPfAk04BDiscCSVv2_->at(jet_ind)>0.89)b_jet_index.push_back(jet_index);
       // cout<<"nconst "<<jet_ind<<" "<<patJetPfAk04nconst_->at(jet_ind)<<"  "<<patJetPfAk04ConstId->size()<<endl;

        if(patJetPfAk04BDiscCSVv2_->at(jet_ind)>csvmax)csvmax=patJetPfAk04BDiscCSVv2_->at(jet_ind);
        if(patJetPfAk04BDiscCSVv2_->at(jet_ind)>csvmax2 && patJetPfAk04BDiscCSVv2_->at(jet_ind)<csvmax)csvmax2=patJetPfAk04BDiscCSVv2_->at(jet_ind);

        vector<double>tmp1;
        vector<double>tmp2;
        vector<double>tmp3;
        vector<double>tmp4;
        vector<double>tmp5;


        for(unsigned int jet_const_ind=0;jet_const_ind< patJetPfAk04nconst_->at(jet_ind);jet_const_ind++){
          //cout<<ind_jet_const<<"  "<<jet_const_ind<<"  "<<ind_jet_const+jet_const_ind<<endl;
//          cout<<patJetPfAk04ConstPt->at(ind_jet_const+jet_const_ind)<<endl;
          tmp1.push_back(patJetPfAk04ConstId->at(ind_jet_const+jet_const_ind));
          tmp2.push_back(patJetPfAk04ConstPt->at(ind_jet_const+jet_const_ind));
          tmp3.push_back(patJetPfAk04ConstEta->at(ind_jet_const+jet_const_ind));
          tmp4.push_back(patJetPfAk04ConstPhi->at(ind_jet_const+jet_const_ind));
          tmp5.push_back(patJetPfAk04ConstE->at(ind_jet_const+jet_const_ind));
	  
        }
        jet_ConstId.push_back(tmp1);
        jet_ConstPt.push_back(tmp2);
        jet_ConstEta.push_back(tmp3);
        jet_ConstPhi.push_back(tmp4);
        jet_ConstE.push_back(tmp5);
        jet_index++;



      double jet_scalefactor=-99;
       if (patJetPfAk04Pt_->at(jet_ind) < 670. ) {

         jet_scalefactor = reader.eval(BTagEntry::FLAV_B, patJetPfAk04Eta_->at(jet_ind),patJetPfAk04Pt_->at(jet_ind)); 

       }
       else {  // for error evaluation outside bounds:
         //const TF1* sfFunc = reader.getFunction(BTagEntry::FLAV_B, 2.399, 669.);
         jet_scalefactor = reader.eval(BTagEntry::FLAV_B, patJetPfAk04Eta_->at(jet_ind), 669); 
       }
       //cout<<jet_scalefactor<<endl;

       double eff_b=0.640272;
       double eff_l=0.024801;
       if(patJetPfAk04BDiscCSVv2_->at(jet_ind)>0.89)nom*=jet_scalefactor*eff_b;
       if(patJetPfAk04BDiscCSVv2_->at(jet_ind)<0.89)nom*=1 - (jet_scalefactor*eff_l);

        if(patJetPfAk04BDiscCSVv2_->at(jet_ind)>0.89)denom*=eff_b;
       if(patJetPfAk04BDiscCSVv2_->at(jet_ind)<0.89)denom*=(1 - (eff_l));


        //calculate b-tag efficiencies 
 
/*       if(fabs(patJetPfAk04PartonFlavour_->at(jet_ind))==5){
          tot_b_jet++;
          if(patJetPfAk04BDiscCSVv2_->at(jet_ind)>0.89)tot_b_tagged_jet++;
       }

       else if(fabs(patJetPfAk04PartonFlavour_->at(jet_ind))==4){
          tot_c_jet++;
          if(patJetPfAk04BDiscCSVv2_->at(jet_ind)>0.89)tot_c_tagged_jet++;
       }
       else{
          tot_udsg_jet++;
          if(patJetPfAk04BDiscCSVv2_->at(jet_ind)>0.89)tot_udsg_tagged_jet++;
       }


      if(mu_index==1 &&mu_index20==1){

       if(fabs(patJetPfAk04PartonFlavour_->at(jet_ind))==5){
          mu_tot_b_jet++;
          if(patJetPfAk04BDiscCSVv2_->at(jet_ind)>0.89)mu_tot_b_tagged_jet++;
       }

       else if(fabs(patJetPfAk04PartonFlavour_->at(jet_ind))==4){
          mu_tot_c_jet++;
          if(patJetPfAk04BDiscCSVv2_->at(jet_ind)>0.89)mu_tot_c_tagged_jet++;
       }
       else {
          mu_tot_udsg_jet++;
          if(patJetPfAk04BDiscCSVv2_->at(jet_ind)>0.89)mu_tot_udsg_tagged_jet++;
       }



       }
*/
      }
//      double btagweight=nom/denom;

     // if(!realdata)w*=btagweight;
      if(jet_vector.size()>=4 && mu_index==1 &&mu_index20==1){
          h_n_bjet->Fill(b_jet_index.size(),w);
          h_csvmax->Fill(csvmax,w);
          h_csvmax2->Fill(csvmax2,w);
      }
      if (jet_vector.size()>=4 && b_jet_index.size()==2 && mu_index==1 &&mu_index20==1){//at least 4 jets, 2 of b jets, 1 muon
      ntottt++;
//      if(!realdata)cout<<btagweight<<endl;
      if(HLT_IsoMu20)N_HLT_Mu20++;
      if(HLT_IsoTkMu20)N_HLT_TkMu20++;
      if(HLT_IsoTkMu20||HLT_IsoMu20)N_HLT_TkMu20ORMu20++;
      if(HLT_IsoMu18)N_HLT_Mu18++;
      if(HLT_IsoTkMu20)N_HLT_TkMu18++;

      if(HLT_IsoMu20_eta2p1)N_HLT_Mu20_eta2p1++;
      if(HLT_IsoTkMu20_eta2p1)N_HLT_TkMu20_eta2p1++;
      if(HLT_IsoMu18_eta2p1)N_HLT_Mu18_eta2p1++;
      if(HLT_IsoTkMu20_eta2p1)N_HLT_TkMu18_eta2p1++;
      if(HLT_IsoMu24_eta2p1)N_HLT_Mu24_eta2p1++;
      h_puweight_meas->Fill(puWeight.weight(int(PU_npT)));
      h_puweight_weighted_meas->Fill(puWeight.weight(int(PU_npT)),w);


          h_mu_pt_meas->Fill(patMuonPt_->at(0),w);
          h_mu_eta_meas->Fill(patMuonEta_->at(0),w);
          h_mu_phi_meas->Fill(patMuonPhi_->at(0),w);
          h_mu_iso_meas->Fill(patMuonPfIsoDbeta_->at(0),w);




//IMPLEMENTING KIN REC



        double pz1=0;
        double pz2=0;
        double MW=80.4;
        double ptl=mu_vector[0].Pt();
        double pzl=mu_vector[0].Pz();
        double El=mu_vector[0].E();
        double ptnu= METPt->at(1);
        TLorentzVector met;
        met.SetPxPyPzE(METPx->at(1),METPy->at(1),METPz->at(1),METE->at(1));
        double deltaphi=DeltaPhi(mu_vector[0].Phi(), met.Phi());
        double cdphi= cos(deltaphi);
	double MTW=sqrt(2*ptl*ptnu*(1 -cdphi ));
        double mu= MW*MW/2 + ptl*ptnu*cdphi;

        double A=mu*pzl/(ptl*ptl);
        double B=mu*mu*pzl*pzl/(pow(ptl,4));
        double C= (El*El*ptnu*ptnu- mu*mu)/(ptl*ptl);
        double D=0;

        ////cout<<MTW<<endl;
        h_MTW->Fill(MTW,w);
        TLorentzVector nu_complex;
        bool found=false;  
        if((B-C)<0){
        //cout<<"new complex event "<<MTW<<endl;

        double min_i=0;
        double max_i=80;
        
          for(double px_var=min_i;px_var<max_i;px_var+=0.3){
//              double py_var=px_var;
            for(double py_var=0;py_var<=px_var;py_var+=0.3){
              TLorentzVector met_new1;
              met_new1.SetPxPyPzE(METPx->at(1)+px_var,METPy->at(1)+py_var,METPz->at(1),METE->at(1));
              double deltaphi_new1=DeltaPhi(mu_vector[0].Phi(), met_new1.Phi());
              double cdphi_new1= cos(deltaphi_new1);
   	      double MTW_new1=sqrt(2*ptl*met_new1.Pt()*(1 -cdphi_new1 ));
              if(MTW_new1>80.399&&MTW_new1<80.401){//cout<<"MTW old, px var +, py var +, MTW new "<<MTW<<"  "<<px_var<<"  "<<py_var<<"  "<<MTW_new1<<endl;
                double ptnun=met_new1.Pt();
                double mun= MW*MW/2 + ptl*ptnun*cdphi_new1;
                double An=mun*pzl/(ptl*ptl);
                //double Bn=mun*mun*pzl*pzl/(pow(ptl,4));
                //double Cn= (El*El*ptnun*ptnun- mun*mun)/(ptl*ptl);
                //double Dn=0;
                //cout<<"B, C, B-C old; B, C, B-C new"<<B<<"  "<<C<<"  "<<B-C<<"  "<<Bn<<"  "<<Cn<<"  "<<Bn-Cn<<endl;
                A=An;
                nu_complex=met_new1;
                found=true;
                break;
              }
              TLorentzVector met_new2;
              met_new2.SetPxPyPzE(METPx->at(1)+px_var,METPy->at(1)-py_var,METPz->at(1),METE->at(1));
              double deltaphi_new2=DeltaPhi(mu_vector[0].Phi(), met_new2.Phi());
              double cdphi_new2= cos(deltaphi_new2);
   	      double MTW_new2=sqrt(2*ptl*met_new2.Pt()*(1 -cdphi_new2 ));
              if(MTW_new2>80.399&&MTW_new2<80.401){//cout<<"MTW old, px var +, py var -, MTW new "<<MTW<<"  "<<px_var<<"  "<<py_var<<"  "<<MTW_new2<<endl;
                double ptnun=met_new2.Pt();
                double mun= MW*MW/2 + ptl*ptnun*cdphi_new2;
                double An=mun*pzl/(ptl*ptl);
                //double Bn=mun*mun*pzl*pzl/(pow(ptl,4));
                //double Cn= (El*El*ptnun*ptnun- mun*mun)/(ptl*ptl);
                //double Dn=0;
                //cout<<"B, C, B-C old; B, C, B-C new"<<B<<"  "<<C<<"  "<<B-C<<"  "<<Bn<<"  "<<Cn<<"  "<<Bn-Cn<<endl;
                A=An;
                nu_complex=met_new2;
                found=true;
                break;
              }

              TLorentzVector met_new3;
              met_new3.SetPxPyPzE(METPx->at(1)-px_var,METPy->at(1)+py_var,METPz->at(1),METE->at(1));
              double deltaphi_new3=DeltaPhi(mu_vector[0].Phi(), met_new3.Phi());
              double cdphi_new3= cos(deltaphi_new3);
   	      double MTW_new3=sqrt(2*ptl*met_new3.Pt()*(1 -cdphi_new3 ));
              if(MTW_new3>80.399&&MTW_new3<80.401){//cout<<"MTW old, px var -, py var +, MTW new "<<MTW<<"  "<<px_var<<"  "<<py_var<<"  "<<MTW_new3<<endl;
                double ptnun=met_new3.Pt();
                double mun= MW*MW/2 + ptl*ptnun*cdphi_new3;
                double An=mun*pzl/(ptl*ptl);
                //double Bn=mun*mun*pzl*pzl/(pow(ptl,4));
                //double Cn= (El*El*ptnun*ptnun- mun*mun)/(ptl*ptl);
                //double Dn=0;
                //cout<<"B, C, B-C old; B, C, B-C new"<<B<<"  "<<C<<"  "<<B-C<<"  "<<Bn<<"  "<<Cn<<"  "<<Bn-Cn<<endl;
                A=An;
                nu_complex=met_new3;
                found=true;
                break;
              }

              TLorentzVector met_new4;
              met_new4.SetPxPyPzE(METPx->at(1)-px_var,METPy->at(1)-py_var,METPz->at(1),METE->at(1));
              double deltaphi_new4=DeltaPhi(mu_vector[0].Phi(), met_new4.Phi());
              double cdphi_new4= cos(deltaphi_new4);
   	      double MTW_new4=sqrt(2*ptl*met_new4.Pt()*(1 -cdphi_new4 ));
              if(MTW_new4>80.399&&MTW_new4<80.401){//cout<<"MTW old, px var -, py var -, MTW new "<<MTW<<"  "<<px_var<<"  "<<py_var<<"  "<<MTW_new4<<endl;
                double ptnun=met_new4.Pt();
                double mun= MW*MW/2 + ptl*ptnun*cdphi_new4;
                double An=mun*pzl/(ptl*ptl);
                //double Bn=mun*mun*pzl*pzl/(pow(ptl,4));
                //double Cn= (El*El*ptnun*ptnun- mun*mun)/(ptl*ptl);
                //double Dn=0;
                //cout<<"B, C, B-C old; B, C, B-C new"<<B<<"  "<<C<<"  "<<B-C<<"  "<<Bn<<"  "<<Cn<<"  "<<Bn-Cn<<endl;
                A=An;
                nu_complex=met_new4;
                found=true;
                break;
              }
              TLorentzVector met_new5;
              met_new5.SetPxPyPzE(METPx->at(1)+py_var,METPy->at(1)+px_var,METPz->at(1),METE->at(1));
              double deltaphi_new5=DeltaPhi(mu_vector[0].Phi(), met_new5.Phi());
              double cdphi_new5= cos(deltaphi_new5);
   	      double MTW_new5=sqrt(2*ptl*met_new5.Pt()*(1 -cdphi_new5 ));
              if(MTW_new5>80.399&&MTW_new5<80.401){//cout<<"MTW old, px var +, py var +, MTW new "<<MTW<<"  "<<py_var<<"  "<<px_var<<"  "<<MTW_new5<<endl;
                double ptnun=met_new5.Pt();
                double mun= MW*MW/2 + ptl*ptnun*cdphi_new5;
                double An=mun*pzl/(ptl*ptl);
                //double Bn=mun*mun*pzl*pzl/(pow(ptl,4));
                //double Cn= (El*El*ptnun*ptnun- mun*mun)/(ptl*ptl);
                //double Dn=0;
                //cout<<"B, C, B-C old; B, C, B-C new"<<B<<"  "<<C<<"  "<<B-C<<"  "<<Bn<<"  "<<Cn<<"  "<<Bn-Cn<<endl;
                A=An;
                nu_complex=met_new5;
                found=true;
                break;
              }
              TLorentzVector met_new6;
              met_new6.SetPxPyPzE(METPx->at(1)+py_var,METPy->at(1)-px_var,METPz->at(1),METE->at(1));
              double deltaphi_new6=DeltaPhi(mu_vector[0].Phi(), met_new6.Phi());
              double cdphi_new6= cos(deltaphi_new6);
   	      double MTW_new6=sqrt(2*ptl*met_new6.Pt()*(1 -cdphi_new6 ));
              if(MTW_new6>80.399&&MTW_new6<80.401){//cout<<"MTW old, px var +, py var -, MTW new "<<MTW<<"  "<<py_var<<"  "<<px_var<<"  "<<MTW_new6<<endl;
                double ptnun=met_new6.Pt();
                double mun= MW*MW/2 + ptl*ptnun*cdphi_new6;
                double An=mun*pzl/(ptl*ptl);
                //double Bn=mun*mun*pzl*pzl/(pow(ptl,4));
                //double Cn= (El*El*ptnun*ptnun- mun*mun)/(ptl*ptl);
                //double Dn=0;
                //cout<<"B, C, B-C old; B, C, B-C new"<<B<<"  "<<C<<"  "<<B-C<<"  "<<Bn<<"  "<<Cn<<"  "<<Bn-Cn<<endl;
                A=An;
                nu_complex=met_new6;
                found=true;
                break;
              }

              TLorentzVector met_new7;
              met_new7.SetPxPyPzE(METPx->at(1)-py_var,METPy->at(1)+px_var,METPz->at(1),METE->at(1));
              double deltaphi_new7=DeltaPhi(mu_vector[0].Phi(), met_new7.Phi());
              double cdphi_new7= cos(deltaphi_new7);
   	      double MTW_new7=sqrt(2*ptl*met_new7.Pt()*(1 -cdphi_new7 ));
              if(MTW_new7>80.399&&MTW_new7<80.401){//cout<<"MTW old, px var -, py var +, MTW new "<<MTW<<"  "<<py_var<<"  "<<px_var<<"  "<<MTW_new7<<endl;
                double ptnun=met_new7.Pt();
                double mun= MW*MW/2 + ptl*ptnun*cdphi_new7;
                double An=mun*pzl/(ptl*ptl);
                //double Bn=mun*mun*pzl*pzl/(pow(ptl,4));
               // double Cn= (El*El*ptnun*ptnun- mun*mun)/(ptl*ptl);
                //double Dn=0;
                //cout<<"B, C, B-C old; B, C, B-C new"<<B<<"  "<<C<<"  "<<B-C<<"  "<<Bn<<"  "<<Cn<<"  "<<Bn-Cn<<endl;
                A=An;
                nu_complex=met_new7;
                found=true;
                break;
              }

              TLorentzVector met_new8;
              met_new8.SetPxPyPzE(METPx->at(1)-py_var,METPy->at(1)-px_var,METPz->at(1),METE->at(1));
              double deltaphi_new8=DeltaPhi(mu_vector[0].Phi(), met_new8.Phi());
              double cdphi_new8= cos(deltaphi_new8);
   	      double MTW_new8=sqrt(2*ptl*met_new8.Pt()*(1 -cdphi_new8 ));
              if(MTW_new8>80.399&&MTW_new8<80.401){//cout<<"MTW old, px var -, py var -, MTW new "<<MTW<<"  "<<py_var<<"  "<<px_var<<"  "<<MTW_new8<<endl;
                double ptnun=met_new8.Pt();
                double mun= MW*MW/2 + ptl*ptnun*cdphi_new8;
                double An=mun*pzl/(ptl*ptl);
                //double Bn=mun*mun*pzl*pzl/(pow(ptl,4));
               // double Cn= (El*El*ptnun*ptnun- mun*mun)/(ptl*ptl);
                //double Dn=0;
                //cout<<"B, C, B-C old; B, C, B-C new"<<B<<"  "<<C<<"  "<<B-C<<"  "<<Bn<<"  "<<Cn<<"  "<<Bn-Cn<<endl;
                A=An;
                nu_complex=met_new8;
                found=true;
                break;
              }

            }
          if(found)break; 
          }

        if(found)solved_complex_count++;
        }


//cout<<"still alive 4"<<endl;





        if((B-C)>=0)D= sqrt(B-C);
        if(B-C<0)D=0;
        if(B-C<0)complex_count++;
        if((B-C)>=0)real_count++;
        pz1= A+D;
        pz2=A-D;
        if((B-C<0) && !found)continue;
        TLorentzVector nu_vector1;
        TLorentzVector nu_vector2;
        TLorentzVector nu_vector;
        TLorentzVector tlep;
        TLorentzVector thad;

        if((B-C)>=0){
          double new_E1=sqrt(METPx->at(1)*METPx->at(1) +METPy->at(1)*METPy->at(1) +pz1*pz1);
          nu_vector1.SetPxPyPzE(METPx->at(1),METPy->at(1),pz1,new_E1);
          double new_E2=sqrt(METPx->at(1)*METPx->at(1) +METPy->at(1)*METPy->at(1) +pz2*pz2);
          nu_vector2.SetPxPyPzE(METPx->at(1),METPy->at(1),pz2,new_E2);
        }

        if((B-C)<0){
          double new_E1=sqrt(nu_complex.Px()*nu_complex.Px() +nu_complex.Py()*nu_complex.Py() +pz1*pz1);
//          nu_vector1.SetPxPyPzE(METPx->at(1),METPy->at(1),pz1,new_E1);
          nu_vector1.SetPxPyPzE(nu_complex.Px(),nu_complex.Py(),pz1,new_E1);
          double new_E2=sqrt(nu_complex.Px()*nu_complex.Px() +nu_complex.Py()*nu_complex.Py() +pz2*pz2);
//          nu_vector2.SetPxPyPzE(METPx->at(1),METPy->at(1),pz2,new_E2);
          nu_vector2.SetPxPyPzE(nu_complex.Px(),nu_complex.Py(),pz2,new_E2);
        }
      //  cout<<" nu1 b1, nu2 b1, nu1 b2, nu2 b2 "<<"  "<<(mu_vector[0]+nu_vector1+jet_vector[b_jet_index[0]]).M()<<"  "<<(mu_vector[0]+nu_vector2+jet_vector[b_jet_index[0]]).M()<<"  "<<(mu_vector[0]+nu_vector1+jet_vector[b_jet_index[1]]).M()<<"  "<<(mu_vector[0]+nu_vector2+jet_vector[b_jet_index[1]]).M()<<endl;

        double m1=(mu_vector[0]+nu_vector1+jet_vector[b_jet_index[0]]).M();
        double m2=(mu_vector[0]+nu_vector2+jet_vector[b_jet_index[0]]).M();
        double m3=(mu_vector[0]+nu_vector1+jet_vector[b_jet_index[1]]).M();
        double m4=(mu_vector[0]+nu_vector2+jet_vector[b_jet_index[1]]).M();
        int ind2=-1;
        if(fabs(m1-172.5) < fabs(m2-172.5)){
          if(fabs(m3-172.5) < fabs(m4-172.5)){
            if(fabs(m1-172.5) <fabs(m3-172.5)){//m1
              tlep=(mu_vector[0]+nu_vector1+jet_vector[b_jet_index[0]]);
              ind2=b_jet_index[1];
              nu_vector=nu_vector1;

            }
            if(fabs(m1-172.5) >fabs(m3-172.5)){//m3
              tlep=(mu_vector[0]+nu_vector1+jet_vector[b_jet_index[1]]);
              ind2=b_jet_index[0];
              nu_vector=nu_vector1;
            }
          }
          if(fabs(m3-172.5) > fabs(m4-172.5)){
           if(fabs(m1-172.5) <fabs(m4-172.5)){//m1
              tlep=(mu_vector[0]+nu_vector1+jet_vector[b_jet_index[0]]);
              ind2=b_jet_index[1];
              nu_vector=nu_vector1;
            }
            if(fabs(m1-172.5) >fabs(m4-172.5)){//m4
              tlep=(mu_vector[0]+nu_vector2+jet_vector[b_jet_index[1]]);
              ind2=b_jet_index[0];
              nu_vector=nu_vector2;
            }
          }
        }


        if(fabs(m1-172.5) > fabs(m2-172.5)){
         if(fabs(m3-172.5) < fabs(m4-172.5)){
            if(fabs(m2-172.5) <fabs(m3-172.5)){//m2
              tlep=(mu_vector[0]+nu_vector2+jet_vector[b_jet_index[0]]);
              ind2=b_jet_index[1];
              nu_vector=nu_vector2;
            }
            if(fabs(m2-172.5) >fabs(m3-172.5)){//m3
              tlep=(mu_vector[0]+nu_vector1+jet_vector[b_jet_index[1]]);
              ind2=b_jet_index[0];
              nu_vector=nu_vector1;
            }
          }
          if(fabs(m3-172.5) > fabs(m4-172.5)){
           if(fabs(m2-172.5) <fabs(m4-172.5)){//m2
              tlep=(mu_vector[0]+nu_vector2+jet_vector[b_jet_index[0]]);
              ind2=b_jet_index[1];
              nu_vector=nu_vector2;
            }
            if(fabs(m2-172.5) >fabs(m4-172.5)){//m4
              tlep=(mu_vector[0]+nu_vector2+jet_vector[b_jet_index[1]]);
              ind2=b_jet_index[0];
              nu_vector=nu_vector2;
            }
          }
        }


        if((fabs(m1-172.5) == fabs(m2-172.5) )&& (fabs(m3-172.5) == fabs(m4-172.5) )){
           if(fabs(m1-172.5) <fabs(m3-172.5)){//m1
              tlep=(mu_vector[0]+nu_vector1+jet_vector[b_jet_index[0]]);
              ind2=b_jet_index[1];
              nu_vector=nu_vector1;
           }
          if(fabs(m1-172.5) >fabs(m3-172.5)){//m3
              tlep=(mu_vector[0]+nu_vector1+jet_vector[b_jet_index[1]]);
              ind2=b_jet_index[0];
              nu_vector=nu_vector1;
           }
        }

         double mmin=9999;
        unsigned int ljet_ind1=99, ljet_ind2=99, extra_jet_index=99,extra_jet_index_1530=99;
         vector<unsigned int> a_min;
         for(unsigned int j_ind=0; j_ind<jet_vector.size();j_ind++){
           if(j_ind==b_jet_index[0]|| j_ind==b_jet_index[1])continue;
           a_min.push_back(j_ind);
           for(unsigned int j_indd=j_ind; j_indd<jet_vector.size();j_indd++){
             if(j_ind==j_indd || j_indd==b_jet_index[0]|| j_indd==b_jet_index[1])continue;
             //cout<<j_ind<<"  "<<j_indd<<endl;
             double mmin_temp=(jet_vector[j_ind]+jet_vector[j_indd]).M();
             if(fabs(mmin_temp-80.4)<fabs(mmin-80.4)){
               mmin=mmin_temp;ljet_ind1=j_ind;ljet_ind2=j_indd;
               //cout<<ljet_ind1<<"  "<<ljet_ind2<<"  "<<mmin<<endl;
             }
           }
         }
       for(unsigned int i=0;i<a_min.size();i++){
          if(a_min[i]==ljet_ind1||a_min[i]==ljet_ind2)continue;
          extra_jet_index=a_min[i]; break;
        }
        thad=jet_vector[ljet_ind1]+jet_vector[ljet_ind2] +jet_vector[ind2];

        h_m_thad->Fill(thad.M(),w); 
        h_m_tlep->Fill(tlep.M(),w);   

        h_pt_thad->Fill(thad.Pt(),w); 
        h_pt_tlep->Fill(tlep.Pt(),w);   

       h_m_thad_fixbin->Fill(thad.M(),w); 
        h_m_tlep_fixbin->Fill(tlep.M(),w);   

        h_pt_thad_fixbin->Fill(thad.Pt(),w); 
        h_pt_tlep_fixbin->Fill(tlep.Pt(),w);   

        h_y_thad->Fill(thad.Rapidity(),w); 
        h_y_tlep->Fill(tlep.Rapidity(),w);   


        h_m_t->Fill(thad.M(),w); 
        h_m_t->Fill(tlep.M(),w);   

        h_pt_t->Fill(thad.Pt(),w); 
        h_pt_t->Fill(tlep.Pt(),w);   

        h_m_t_fixbin->Fill(thad.M(),w); 
        h_m_t_fixbin->Fill(tlep.M(),w);   

        h_pt_t_fixbin->Fill(thad.Pt(),w); 
        h_pt_t_fixbin->Fill(tlep.Pt(),w);   

        h_y_t->Fill(thad.Rapidity(),w); 
        h_y_t->Fill(tlep.Rapidity(),w);   

    
        h_nu_pz->Fill(nu_vector.Pz(),w);
        h_nu_pt->Fill(nu_vector.Pt(),w);

        TLorentzVector top_vector;
        TLorentzVector atop_vector;
        if(mu_charge[0]>0){

          top_vector=tlep;
          atop_vector=thad;
        }

        if(mu_charge[0]<0){

          atop_vector=tlep;
          top_vector=thad;
        }
          h_m_top->Fill(top_vector.M(),w);
          h_m_atop->Fill(atop_vector.M(),w);
          h_pt_top->Fill(top_vector.Pt(),w);
          h_pt_atop->Fill(atop_vector.Pt(),w);
          h_m_top_fixbin->Fill(top_vector.M(),w);
          h_m_atop_fixbin->Fill(atop_vector.M(),w);
          h_pt_top_fixbin->Fill(top_vector.Pt(),w);
          h_pt_atop_fixbin->Fill(atop_vector.Pt(),w);

         h_pt_ttbar_kinrec->Fill((tlep+thad).Pt(),w);









 
         double etab1=jet_vector[b_jet_index[0]].Eta();
         double etab2=jet_vector[b_jet_index[1]].Eta();
         double etamin=0;
         if(etab1<etab2)etamin=etab1;
         else etamin=etab2;
         double deltaetabb=fabs(etab1-etab2);
         int njet_bb=0;
         for(unsigned int j_ind=0; j_ind<jet_vector.size();j_ind++){

           if(j_ind==b_jet_index[0]|| j_ind==b_jet_index[1]||j_ind==ljet_ind1 ||j_ind==ljet_ind2)continue;
           
//           if(fabs(jet_vector[j_ind].Eta())<fabs(etab1) &&fabs(jet_vector[j_ind].Eta())<fabs(etab2) )njet_bb++;

            if(jet_vector[j_ind].Eta()>etamin && jet_vector[j_ind].Eta()<etamin+deltaetabb ) njet_bb++;
         }
         for(unsigned int jet_vector_1530_ind =0; jet_vector_1530_ind<jet_vector_1530.size();jet_vector_1530_ind++){
            if(jet_vector_1530[jet_vector_1530_ind].Eta()>etamin && jet_vector_1530[jet_vector_1530_ind].Eta()<etamin+deltaetabb ) njet_bb++;


         }

         if(extra_jet_index==99 &&jet_vector_1530.size()>0 )extra_jet_index_1530=0;

         h_njet_bb->Fill(njet_bb,w);
         h_njet_15_ttbar->Fill(jet_vector_1530.size()+jet_vector.size()-4,w);
         if(njet_bb>=1)h_profile_deta_bb_njet_bb->Fill(deltaetabb,njet_bb,w);
         if((jet_vector_1530.size()+jet_vector.size())>=5)h_profile_deta_bb_njet_extra->Fill(deltaetabb,jet_vector_1530.size()+jet_vector.size()-4,w);
         h_ljet_pt->Fill(jet_vector[ljet_ind1].Pt(),w);
         h_ljet_eta->Fill(jet_vector[ljet_ind1].Eta(),w);    

         h_sljet_pt->Fill(jet_vector[ljet_ind2].Pt(),w);
         h_sljet_eta->Fill(jet_vector[ljet_ind2].Eta(),w);  


        h_lbjet_pt->Fill(jet_vector[b_jet_index[0]].Pt(),w);
         h_lbjet_eta->Fill(jet_vector[b_jet_index[0]].Eta(),w);    

         h_slbjet_pt->Fill(jet_vector[b_jet_index[1]].Pt(),w);
         h_slbjet_eta->Fill(jet_vector[b_jet_index[1]].Eta(),w);  

         h_dijet_mass->Fill((jet_vector[ljet_ind1]+jet_vector[ljet_ind2]).M(),w);  
         h_dijet_mass_narrow->Fill((jet_vector[ljet_ind1]+jet_vector[ljet_ind2]).M(),w);  
         TLorentzVector mett;
         mett.SetPxPyPzE(METPx->at(1),METPy->at(1),METPz->at(1),METE->at(1));
         h_met_meas->Fill(mett.Pt(),w);
         TLorentzVector ttbar= mu_vector[0] +jet_vector[ljet_ind1]+jet_vector[ljet_ind2]+jet_vector[b_jet_index[0]]+jet_vector[b_jet_index[1]]+mett;
         h_pt_ttbar->Fill((ttbar).Pt(),w);
          ttbar=thad+tlep;

         h_m_ttbar->Fill(ttbar.M(),w);
         h_m_ttbar_fixbin->Fill(ttbar.M(),w);
         h_y_ttbar->Fill(ttbar.Rapidity(),w);
         h_y_top->Fill(top_vector.Rapidity(),w);
         h_y_atop->Fill(atop_vector.Rapidity(),w);
         h_phi_ttbar->Fill(ttbar.Phi(),w);
         //cout<<ttbar.Phi()<<endl;

         h_njet_ttbar->Fill(jet_vector.size(),w);
 
         int n_pf=0;
         int n_pf_dphi[20];
         double ptsum_pf_dphi[20];

/*         int n_pf_ttpt[10];
         double ptsum_pf_ttpt[10];

         int n_pf_ttpt_away[10];
         double ptsum_pf_ttpt_away[10];

         int n_pf_ttpt_transverse[10];
         double ptsum_pf_ttpt_transverse[10];

         int n_pf_ttpt_toward[10];
         double ptsum_pf_ttpt_toward[10];*/

         double ptsum_pf=0;
         double ptsum_pf_away=0;
         double ptsum_pf_transverse=0;
         double ptsum_pf_toward=0;
         int n_pf_away=0;
         int n_pf_transverse=0;
         int n_pf_toward=0;
         for(int i =0;i<20;i++){
	   n_pf_dphi[i]=0;
	   ptsum_pf_dphi[i]=0;

/*         if(i<10){
	   n_pf_ttpt[i]=0;
	   ptsum_pf_ttpt[i]=0;
	   n_pf_ttpt_away[i]=0;
	   ptsum_pf_ttpt_away[i]=0;
	   n_pf_ttpt_transverse[i]=0;
	   ptsum_pf_ttpt_transverse[i]=0;
	   n_pf_ttpt_toward[i]=0;
	   ptsum_pf_ttpt_toward[i]=0;
         }*/
         } 

         for(unsigned int pfind =0; pfind<patPfCandPt->size();pfind++){
 
           if(patPfCandPt->at(pfind)>0.5 ){

             h_pf_dxy->Fill(fabs(patPfCandDxy->at(pfind)),w);
             h_pf_dz->Fill(fabs(patPfCandDzAssociatedPV->at(pfind)),w);
             h_pf_sigmadxy->Fill(fabs(patPfCandDxy->at(pfind)/patPfCandDxyerr->at(pfind)),w);
             h_pf_sigmadz->Fill(fabs(patPfCandDzAssociatedPV->at(pfind)/patPfCandDzerr->at(pfind)),w);
           }
           if(patPfCandPt->at(pfind)<0.5 ||patPfCandFromPv->at(pfind)<2||fabs(patPfCandDxy->at(pfind))>1 ||fabs(patPfCandDzAssociatedPV->at(pfind))>3 ||patPfCandEta->at(pfind)>2.1) continue;
           //cout<<jet_ConstId[ljet_ind1].size()<<endl;
           unsigned int array_jetind[]={ljet_ind1,ljet_ind2,b_jet_index[0],b_jet_index[1]};
           double dr_pf_jetpf_min=9999;
           double dr_pf_jet_min=9999;
           double deltar_pf_mu=9999;

           //double dr_min_alljet_pf=9999;
          for(int jettt=0;jettt<4;jettt++){


             double deltar_pf_jet=DeltaR(patPfCandEta->at(pfind),jet_vector[jettt].Eta(),patPfCandPhi->at(pfind),jet_vector[jettt].Phi());
             if(deltar_pf_jet<dr_pf_jet_min)dr_pf_jet_min=deltar_pf_jet;
             for(unsigned int jetpfind=0;jetpfind<jet_ConstId[array_jetind[jettt]].size();jetpfind++){
               //cout<<jet_ConstPt[ljet_ind1][jetpfind]<<"  "<<patPfCandPt->at(pfind)<<"  "<<jet_ConstEta[ljet_ind1][jetpfind]<<"  "<<patPfCandEta->at(pfind)<<endl;
               double deltar_pf_jetpf=DeltaR(patPfCandEta->at(pfind),jet_ConstEta[array_jetind[jettt]][jetpfind],patPfCandPhi->at(pfind),jet_ConstPhi[array_jetind[jettt]][jetpfind]);

               if(deltar_pf_jetpf<dr_pf_jetpf_min)dr_pf_jetpf_min=deltar_pf_jetpf;
   
             }
           }
/*
           int ind_jet_constt=0;
           for(unsigned int jet_ind=0; jet_ind<patJetPfAk04Pt_->size();jet_ind++){
             if(jet_ind>=1)ind_jet_constt+=patJetPfAk04nconst_->at(jet_ind-1);
             if(patJetPfAk04Pt_->at(jet_ind)<15. || fabs(patJetPfAk04Eta_->at(jet_ind))>2.5)continue;
             for(unsigned int jet_const_ind=0;jet_const_ind< patJetPfAk04nconst_->at(jet_ind);jet_const_ind++){
               double deltar_alljet_pf=DeltaR(patJetPfAk04ConstEta->at(ind_jet_constt+jet_const_ind),patPfCandEta->at(pfind),patJetPfAk04ConstPhi->at(ind_jet_constt+jet_const_ind),patPfCandPhi->at(pfind));
               if(deltar_alljet_pf<dr_min_alljet_pf)dr_min_alljet_pf=deltar_alljet_pf;
             }
           }
*/
           h_deltar_pf_jetpf->Fill(dr_pf_jetpf_min,w);
           h_deltar_pf_jet->Fill(dr_pf_jet_min,w);
           deltar_pf_mu=  DeltaR(patPfCandEta->at(pfind),mu_vector[0].Eta(),patPfCandPhi->at(pfind),mu_vector[0].Phi()); 
           h_deltar_pf_mu->Fill(deltar_pf_mu,w); 
           if(dr_pf_jetpf_min<0.05 ||deltar_pf_mu<0.05 /*||dr_min_alljet_pf<0.4*/)continue;
           h_deltar_pf_jet_after->Fill(dr_pf_jet_min,w);
           n_pf++;
           ptsum_pf+=patPfCandPt->at(pfind);
           double deltaphi_tt_pf=DeltaPhi(ttbar.Phi(),patPfCandPhi->at(pfind))*180/pi;
           h_dphi_ttbar_pf->Fill(deltaphi_tt_pf,w);
           h_pf_pt->Fill(patPfCandPt->at(pfind),w);
           if(fabs(deltaphi_tt_pf)>0 && fabs(deltaphi_tt_pf)<60){
             n_pf_toward++;
             ptsum_pf_toward+=patPfCandPt->at(pfind);
           }
           if(fabs(deltaphi_tt_pf)>60 && fabs(deltaphi_tt_pf)<120){
             n_pf_transverse++;
             ptsum_pf_transverse+=patPfCandPt->at(pfind);
           }
           if(fabs(deltaphi_tt_pf)>120 && fabs(deltaphi_tt_pf)<180){
             n_pf_away++;
             ptsum_pf_away+=patPfCandPt->at(pfind);
           }
           for(int dphiloop=0;dphiloop<20;dphiloop++){
             if(fabs(deltaphi_tt_pf)>dphiloop*9 && fabs(deltaphi_tt_pf)<(dphiloop+1)*9){
               n_pf_dphi[dphiloop]++;
               ptsum_pf_dphi[dphiloop]+=patPfCandPt->at(pfind);
             }
           }



         
         }//pf loop
         //cout<<n_pf<<"  "<<n_pf_dphi[0]<<"  "<<ptsum_pf_dphi[0]<<endl;
         if(n_pf!=0){
           for(int dphiloop=0;dphiloop<20;dphiloop++){
             if(n_pf_dphi[dphiloop]==0)continue;
             h_dphi_npf->Fill(dphiloop*9,n_pf_dphi[dphiloop],w);
             h_dphi_ptsumpf->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop],w);
             h_dphi_ptaveragepf->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop]/n_pf_dphi[dphiloop],w);
             h_profile_dphi_npf->Fill(dphiloop*9,n_pf_dphi[dphiloop],w);
             h_profile_dphi_ptsumpf->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop],w);
             h_profile_dphi_ptaveragepf->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop]/n_pf_dphi[dphiloop],w);

             if(njet_15==4){
               h_dphi_npf_0j->Fill(dphiloop*9,n_pf_dphi[dphiloop],w);
               h_dphi_ptsumpf_0j->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop],w);
               h_dphi_ptaveragepf_0j->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop]/n_pf_dphi[dphiloop],w);
               h_profile_dphi_npf_0j->Fill(dphiloop*9,n_pf_dphi[dphiloop],w);
               h_profile_dphi_ptsumpf_0j->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop],w);
               h_profile_dphi_ptaveragepf_0j->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop]/n_pf_dphi[dphiloop],w);
             }

             if(njet_15==5){
               h_dphi_npf_1j->Fill(dphiloop*9,n_pf_dphi[dphiloop],w);
               h_dphi_ptsumpf_1j->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop],w);
               h_dphi_ptaveragepf_1j->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop]/n_pf_dphi[dphiloop],w);
               h_profile_dphi_npf_1j->Fill(dphiloop*9,n_pf_dphi[dphiloop],w);
               h_profile_dphi_ptsumpf_1j->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop],w);
               h_profile_dphi_ptaveragepf_1j->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop]/n_pf_dphi[dphiloop],w);
             }

             if(njet_15>=6){
               h_dphi_npf_2pj->Fill(dphiloop*9,n_pf_dphi[dphiloop],w);
               h_dphi_ptsumpf_2pj->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop],w);
               h_dphi_ptaveragepf_2pj->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop]/n_pf_dphi[dphiloop],w);
               h_profile_dphi_npf_2pj->Fill(dphiloop*9,n_pf_dphi[dphiloop],w);
               h_profile_dphi_ptsumpf_2pj->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop],w);
               h_profile_dphi_ptaveragepf_2pj->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop]/n_pf_dphi[dphiloop],w);
             }
           }

           h_nvtx_npf->Fill(EvtInfo_NumVtx,n_pf,w);
           h_profile_nvtx_npf->Fill(EvtInfo_NumVtx,n_pf,w);
           h_profile_nvtx_sumpt->Fill(EvtInfo_NumVtx,ptsum_pf,w);
          
           
           if(njet_15==4){
           h_nvtx_npf_0j->Fill(EvtInfo_NumVtx,n_pf,w);
           h_profile_nvtx_npf_0j->Fill(EvtInfo_NumVtx,n_pf,w);
           h_profile_nvtx_sumpt_0j->Fill(EvtInfo_NumVtx,ptsum_pf,w);
           }
           if(njet_15==5){
           h_nvtx_npf_1j->Fill(EvtInfo_NumVtx,n_pf,w);
           h_profile_nvtx_npf_1j->Fill(EvtInfo_NumVtx,n_pf,w);
           h_profile_nvtx_sumpt_1j->Fill(EvtInfo_NumVtx,ptsum_pf,w);
            }

           if(njet_15>=6){
           h_nvtx_npf_2pj->Fill(EvtInfo_NumVtx,n_pf,w);
           h_profile_nvtx_npf_2pj->Fill(EvtInfo_NumVtx,n_pf,w);
           h_profile_nvtx_sumpt_2pj->Fill(EvtInfo_NumVtx,ptsum_pf,w);

           }

           h_npf_inclusive->Fill(n_pf,w);
           h_npf_toward->Fill(n_pf_toward,w);
           h_npf_transverse->Fill(n_pf_transverse,w);
           h_npf_away->Fill(n_pf_away,w);

           h_ptsumpf_inclusive->Fill(ptsum_pf,w);
           h_ptsumpf_toward->Fill(ptsum_pf_toward,w);
           h_ptsumpf_transverse->Fill(ptsum_pf_transverse,w);
           h_ptsumpf_away->Fill(ptsum_pf_away,w);

           h_ptavepf_inclusive->Fill(ptsum_pf/n_pf,w);
           h_ptavepf_toward->Fill(ptsum_pf_toward/n_pf_toward,w);
           h_ptavepf_transverse->Fill(ptsum_pf_transverse/n_pf_transverse,w);
           h_ptavepf_away->Fill(ptsum_pf_away/n_pf_away,w);

      //     for(int dphiloop=0;dphiloop<10;dphiloop++){
      //       if(ttbar.Pt()>pt_tt_range[dphiloop] && ttbar.Pt()<pt_tt_range[dphiloop+1]){
               h_profile_ptttbar_npf->Fill(ttbar.Pt(),n_pf,w);
               h_profile_ptttbar_sumpt->Fill(ttbar.Pt(),ptsum_pf,w);
               h_profile_ptttbar_avept->Fill(ttbar.Pt(),ptsum_pf/n_pf,w);
               if(n_pf_away!=0)h_profile_ptttbar_npf_away->Fill(ttbar.Pt(),n_pf_away,w);
               if(n_pf_away!=0)h_profile_ptttbar_sumpt_away->Fill(ttbar.Pt(),ptsum_pf_away,w);
               if(n_pf_away!=0)h_profile_ptttbar_avept_away->Fill(ttbar.Pt(),ptsum_pf_away/n_pf_away,w);
               if(n_pf_transverse!=0)h_profile_ptttbar_npf_transverse->Fill(ttbar.Pt(),n_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_ptttbar_sumpt_transverse->Fill(ttbar.Pt(),ptsum_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_ptttbar_avept_transverse->Fill(ttbar.Pt(),ptsum_pf_transverse/n_pf_transverse,w);
               if(n_pf_toward!=0)h_profile_ptttbar_npf_toward->Fill(ttbar.Pt(),n_pf_toward,w);
               if(n_pf_toward!=0)h_profile_ptttbar_sumpt_toward->Fill(ttbar.Pt(),ptsum_pf_toward,w);
               if(n_pf_toward!=0)h_profile_ptttbar_avept_toward->Fill(ttbar.Pt(),ptsum_pf_toward/n_pf_toward,w);


               h_profile_mttbar_npf->Fill(ttbar.M(),n_pf,w);
               h_profile_mttbar_sumpt->Fill(ttbar.M(),ptsum_pf,w);
               h_profile_mttbar_avept->Fill(ttbar.M(),ptsum_pf/n_pf,w);
               if(n_pf_away!=0)h_profile_mttbar_npf_away->Fill(ttbar.M(),n_pf_away,w);
               if(n_pf_away!=0)h_profile_mttbar_sumpt_away->Fill(ttbar.M(),ptsum_pf_away,w);
               if(n_pf_away!=0)h_profile_mttbar_avept_away->Fill(ttbar.M(),ptsum_pf_away/n_pf_away,w);
               if(n_pf_transverse!=0)h_profile_mttbar_npf_transverse->Fill(ttbar.M(),n_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_mttbar_sumpt_transverse->Fill(ttbar.M(),ptsum_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_mttbar_avept_transverse->Fill(ttbar.M(),ptsum_pf_transverse/n_pf_transverse,w);
               if(n_pf_toward!=0)h_profile_mttbar_npf_toward->Fill(ttbar.M(),n_pf_toward,w);
               if(n_pf_toward!=0)h_profile_mttbar_sumpt_toward->Fill(ttbar.M(),ptsum_pf_toward,w);
               if(n_pf_toward!=0)h_profile_mttbar_avept_toward->Fill(ttbar.M(),ptsum_pf_toward/n_pf_toward,w);

 


        h_profile_ytt_npf->Fill(fabs(ttbar.Rapidity()),n_pf,w);
               h_profile_ytt_sumpt->Fill(fabs(ttbar.Rapidity()),ptsum_pf,w);
               h_profile_ytt_avept->Fill(fabs(ttbar.Rapidity()),ptsum_pf/n_pf,w);
               if(n_pf_away!=0)h_profile_ytt_npf_away->Fill(fabs(ttbar.Rapidity()),n_pf_away,w);
               if(n_pf_away!=0)h_profile_ytt_sumpt_away->Fill(fabs(ttbar.Rapidity()),ptsum_pf_away,w);
               if(n_pf_away!=0)h_profile_ytt_avept_away->Fill(fabs(ttbar.Rapidity()),ptsum_pf_away/n_pf_away,w);
               if(n_pf_transverse!=0)h_profile_ytt_npf_transverse->Fill(fabs(ttbar.Rapidity()),n_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_ytt_sumpt_transverse->Fill(fabs(ttbar.Rapidity()),ptsum_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_ytt_avept_transverse->Fill(fabs(ttbar.Rapidity()),ptsum_pf_transverse/n_pf_transverse,w);
               if(n_pf_toward!=0)h_profile_ytt_npf_toward->Fill(fabs(ttbar.Rapidity()),n_pf_toward,w);
               if(n_pf_toward!=0)h_profile_ytt_sumpt_toward->Fill(fabs(ttbar.Rapidity()),ptsum_pf_toward,w);
               if(n_pf_toward!=0)h_profile_ytt_avept_toward->Fill(fabs(ttbar.Rapidity()),ptsum_pf_toward/n_pf_toward,w);

              h_profile_pttop_npf->Fill(top_vector.Pt(),n_pf,w);
               h_profile_pttop_sumpt->Fill(top_vector.Pt(),ptsum_pf,w);
               h_profile_pttop_avept->Fill(top_vector.Pt(),ptsum_pf/n_pf,w);
               if(n_pf_away!=0)h_profile_pttop_npf_away->Fill(top_vector.Pt(),n_pf_away,w);
               if(n_pf_away!=0)h_profile_pttop_sumpt_away->Fill(top_vector.Pt(),ptsum_pf_away,w);
               if(n_pf_away!=0)h_profile_pttop_avept_away->Fill(top_vector.Pt(),ptsum_pf_away/n_pf_away,w);
               if(n_pf_transverse!=0)h_profile_pttop_npf_transverse->Fill(top_vector.Pt(),n_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_pttop_sumpt_transverse->Fill(top_vector.Pt(),ptsum_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_pttop_avept_transverse->Fill(top_vector.Pt(),ptsum_pf_transverse/n_pf_transverse,w);
               if(n_pf_toward!=0)h_profile_pttop_npf_toward->Fill(top_vector.Pt(),n_pf_toward,w);
               if(n_pf_toward!=0)h_profile_pttop_sumpt_toward->Fill(top_vector.Pt(),ptsum_pf_toward,w);
               if(n_pf_toward!=0)h_profile_pttop_avept_toward->Fill(top_vector.Pt(),ptsum_pf_toward/n_pf_toward,w);

               h_profile_ptatop_npf->Fill(atop_vector.Pt(),n_pf,w);
               h_profile_ptatop_sumpt->Fill(atop_vector.Pt(),ptsum_pf,w);
               h_profile_ptatop_avept->Fill(atop_vector.Pt(),ptsum_pf/n_pf,w);
               if(n_pf_away!=0)h_profile_ptatop_npf_away->Fill(atop_vector.Pt(),n_pf_away,w);
               if(n_pf_away!=0)h_profile_ptatop_sumpt_away->Fill(atop_vector.Pt(),ptsum_pf_away,w);
               if(n_pf_away!=0)h_profile_ptatop_avept_away->Fill(atop_vector.Pt(),ptsum_pf_away/n_pf_away,w);
               if(n_pf_transverse!=0)h_profile_ptatop_npf_transverse->Fill(atop_vector.Pt(),n_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_ptatop_sumpt_transverse->Fill(atop_vector.Pt(),ptsum_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_ptatop_avept_transverse->Fill(atop_vector.Pt(),ptsum_pf_transverse/n_pf_transverse,w);
               if(n_pf_toward!=0)h_profile_ptatop_npf_toward->Fill(atop_vector.Pt(),n_pf_toward,w);
               if(n_pf_toward!=0)h_profile_ptatop_sumpt_toward->Fill(atop_vector.Pt(),ptsum_pf_toward,w);
               if(n_pf_toward!=0)h_profile_ptatop_avept_toward->Fill(atop_vector.Pt(),ptsum_pf_toward/n_pf_toward,w);

              h_profile_mtop_npf->Fill(top_vector.M(),n_pf,w);
               h_profile_mtop_sumpt->Fill(top_vector.M(),ptsum_pf,w);
               h_profile_mtop_avept->Fill(top_vector.M(),ptsum_pf/n_pf,w);
               if(n_pf_away!=0)h_profile_mtop_npf_away->Fill(top_vector.M(),n_pf_away,w);
               if(n_pf_away!=0)h_profile_mtop_sumpt_away->Fill(top_vector.M(),ptsum_pf_away,w);
               if(n_pf_away!=0)h_profile_mtop_avept_away->Fill(top_vector.M(),ptsum_pf_away/n_pf_away,w);
               if(n_pf_transverse!=0)h_profile_mtop_npf_transverse->Fill(top_vector.M(),n_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_mtop_sumpt_transverse->Fill(top_vector.M(),ptsum_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_mtop_avept_transverse->Fill(top_vector.M(),ptsum_pf_transverse/n_pf_transverse,w);
               if(n_pf_toward!=0)h_profile_mtop_npf_toward->Fill(top_vector.M(),n_pf_toward,w);
               if(n_pf_toward!=0)h_profile_mtop_sumpt_toward->Fill(top_vector.M(),ptsum_pf_toward,w);
               if(n_pf_toward!=0)h_profile_mtop_avept_toward->Fill(top_vector.M(),ptsum_pf_toward/n_pf_toward,w);

              h_profile_matop_npf->Fill(atop_vector.M(),n_pf,w);
               h_profile_matop_sumpt->Fill(atop_vector.M(),ptsum_pf,w);
               h_profile_matop_avept->Fill(atop_vector.M(),ptsum_pf/n_pf,w);
               if(n_pf_away!=0)h_profile_matop_npf_away->Fill(atop_vector.M(),n_pf_away,w);
               if(n_pf_away!=0)h_profile_matop_sumpt_away->Fill(atop_vector.M(),ptsum_pf_away,w);
               if(n_pf_away!=0)h_profile_matop_avept_away->Fill(atop_vector.M(),ptsum_pf_away/n_pf_away,w);
               if(n_pf_transverse!=0)h_profile_matop_npf_transverse->Fill(atop_vector.M(),n_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_matop_sumpt_transverse->Fill(atop_vector.M(),ptsum_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_matop_avept_transverse->Fill(atop_vector.M(),ptsum_pf_transverse/n_pf_transverse,w);
               if(n_pf_toward!=0)h_profile_matop_npf_toward->Fill(atop_vector.M(),n_pf_toward,w);
               if(n_pf_toward!=0)h_profile_matop_sumpt_toward->Fill(atop_vector.M(),ptsum_pf_toward,w);
               if(n_pf_toward!=0)h_profile_matop_avept_toward->Fill(atop_vector.M(),ptsum_pf_toward/n_pf_toward,w);

             h_profile_ytop_npf->Fill(fabs(top_vector.Rapidity()),n_pf,w);
               h_profile_ytop_sumpt->Fill(fabs(top_vector.Rapidity()),ptsum_pf,w);
               h_profile_ytop_avept->Fill(fabs(top_vector.Rapidity()),ptsum_pf/n_pf,w);
               if(n_pf_away!=0)h_profile_ytop_npf_away->Fill(fabs(top_vector.Rapidity()),n_pf_away,w);
               if(n_pf_away!=0)h_profile_ytop_sumpt_away->Fill(fabs(top_vector.Rapidity()),ptsum_pf_away,w);
               if(n_pf_away!=0)h_profile_ytop_avept_away->Fill(fabs(top_vector.Rapidity()),ptsum_pf_away/n_pf_away,w);
               if(n_pf_transverse!=0)h_profile_ytop_npf_transverse->Fill(fabs(top_vector.Rapidity()),n_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_ytop_sumpt_transverse->Fill(fabs(top_vector.Rapidity()),ptsum_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_ytop_avept_transverse->Fill(fabs(top_vector.Rapidity()),ptsum_pf_transverse/n_pf_transverse,w);
               if(n_pf_toward!=0)h_profile_ytop_npf_toward->Fill(fabs(top_vector.Rapidity()),n_pf_toward,w);
               if(n_pf_toward!=0)h_profile_ytop_sumpt_toward->Fill(fabs(top_vector.Rapidity()),ptsum_pf_toward,w);
               if(n_pf_toward!=0)h_profile_ytop_avept_toward->Fill(fabs(top_vector.Rapidity()),ptsum_pf_toward/n_pf_toward,w);

             h_profile_yatop_npf->Fill(fabs(top_vector.Rapidity()),n_pf,w);
               h_profile_yatop_sumpt->Fill(fabs(top_vector.Rapidity()),ptsum_pf,w);
               h_profile_yatop_avept->Fill(fabs(top_vector.Rapidity()),ptsum_pf/n_pf,w);
               if(n_pf_away!=0)h_profile_yatop_npf_away->Fill(fabs(top_vector.Rapidity()),n_pf_away,w);
               if(n_pf_away!=0)h_profile_yatop_sumpt_away->Fill(fabs(top_vector.Rapidity()),ptsum_pf_away,w);
               if(n_pf_away!=0)h_profile_yatop_avept_away->Fill(fabs(top_vector.Rapidity()),ptsum_pf_away/n_pf_away,w);
               if(n_pf_transverse!=0)h_profile_yatop_npf_transverse->Fill(fabs(top_vector.Rapidity()),n_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_yatop_sumpt_transverse->Fill(fabs(top_vector.Rapidity()),ptsum_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_yatop_avept_transverse->Fill(fabs(top_vector.Rapidity()),ptsum_pf_transverse/n_pf_transverse,w);
               if(n_pf_toward!=0)h_profile_yatop_npf_toward->Fill(fabs(top_vector.Rapidity()),n_pf_toward,w);
               if(n_pf_toward!=0)h_profile_yatop_sumpt_toward->Fill(fabs(top_vector.Rapidity()),ptsum_pf_toward,w);
               if(n_pf_toward!=0)h_profile_yatop_avept_toward->Fill(fabs(top_vector.Rapidity()),ptsum_pf_toward/n_pf_toward,w);

              h_profile_ptthad_npf->Fill(thad.Pt(),n_pf,w);
               h_profile_ptthad_sumpt->Fill(thad.Pt(),ptsum_pf,w);
               h_profile_ptthad_avept->Fill(thad.Pt(),ptsum_pf/n_pf,w);
               if(n_pf_away!=0)h_profile_ptthad_npf_away->Fill(thad.Pt(),n_pf_away,w);
               if(n_pf_away!=0)h_profile_ptthad_sumpt_away->Fill(thad.Pt(),ptsum_pf_away,w);
               if(n_pf_away!=0)h_profile_ptthad_avept_away->Fill(thad.Pt(),ptsum_pf_away/n_pf_away,w);
               if(n_pf_transverse!=0)h_profile_ptthad_npf_transverse->Fill(thad.Pt(),n_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_ptthad_sumpt_transverse->Fill(thad.Pt(),ptsum_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_ptthad_avept_transverse->Fill(thad.Pt(),ptsum_pf_transverse/n_pf_transverse,w);
               if(n_pf_toward!=0)h_profile_ptthad_npf_toward->Fill(thad.Pt(),n_pf_toward,w);
               if(n_pf_toward!=0)h_profile_ptthad_sumpt_toward->Fill(thad.Pt(),ptsum_pf_toward,w);
               if(n_pf_toward!=0)h_profile_ptthad_avept_toward->Fill(thad.Pt(),ptsum_pf_toward/n_pf_toward,w);

               h_profile_pttlep_npf->Fill(tlep.Pt(),n_pf,w);
               h_profile_pttlep_sumpt->Fill(tlep.Pt(),ptsum_pf,w);
               h_profile_pttlep_avept->Fill(tlep.Pt(),ptsum_pf/n_pf,w);
               if(n_pf_away!=0)h_profile_pttlep_npf_away->Fill(tlep.Pt(),n_pf_away,w);
               if(n_pf_away!=0)h_profile_pttlep_sumpt_away->Fill(tlep.Pt(),ptsum_pf_away,w);
               if(n_pf_away!=0)h_profile_pttlep_avept_away->Fill(tlep.Pt(),ptsum_pf_away/n_pf_away,w);
               if(n_pf_transverse!=0)h_profile_pttlep_npf_transverse->Fill(tlep.Pt(),n_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_pttlep_sumpt_transverse->Fill(tlep.Pt(),ptsum_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_pttlep_avept_transverse->Fill(tlep.Pt(),ptsum_pf_transverse/n_pf_transverse,w);
               if(n_pf_toward!=0)h_profile_pttlep_npf_toward->Fill(tlep.Pt(),n_pf_toward,w);
               if(n_pf_toward!=0)h_profile_pttlep_sumpt_toward->Fill(tlep.Pt(),ptsum_pf_toward,w);
               if(n_pf_toward!=0)h_profile_pttlep_avept_toward->Fill(tlep.Pt(),ptsum_pf_toward/n_pf_toward,w);

              h_profile_mthad_npf->Fill(thad.M(),n_pf,w);
               h_profile_mthad_sumpt->Fill(thad.M(),ptsum_pf,w);
               h_profile_mthad_avept->Fill(thad.M(),ptsum_pf/n_pf,w);
               if(n_pf_away!=0)h_profile_mthad_npf_away->Fill(thad.M(),n_pf_away,w);
               if(n_pf_away!=0)h_profile_mthad_sumpt_away->Fill(thad.M(),ptsum_pf_away,w);
               if(n_pf_away!=0)h_profile_mthad_avept_away->Fill(thad.M(),ptsum_pf_away/n_pf_away,w);
               if(n_pf_transverse!=0)h_profile_mthad_npf_transverse->Fill(thad.M(),n_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_mthad_sumpt_transverse->Fill(thad.M(),ptsum_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_mthad_avept_transverse->Fill(thad.M(),ptsum_pf_transverse/n_pf_transverse,w);
               if(n_pf_toward!=0)h_profile_mthad_npf_toward->Fill(thad.M(),n_pf_toward,w);
               if(n_pf_toward!=0)h_profile_mthad_sumpt_toward->Fill(thad.M(),ptsum_pf_toward,w);
               if(n_pf_toward!=0)h_profile_mthad_avept_toward->Fill(thad.M(),ptsum_pf_toward/n_pf_toward,w);

              h_profile_mtlep_npf->Fill(tlep.M(),n_pf,w);
               h_profile_mtlep_sumpt->Fill(tlep.M(),ptsum_pf,w);
               h_profile_mtlep_avept->Fill(tlep.M(),ptsum_pf/n_pf,w);
               if(n_pf_away!=0)h_profile_mtlep_npf_away->Fill(tlep.M(),n_pf_away,w);
               if(n_pf_away!=0)h_profile_mtlep_sumpt_away->Fill(tlep.M(),ptsum_pf_away,w);
               if(n_pf_away!=0)h_profile_mtlep_avept_away->Fill(tlep.M(),ptsum_pf_away/n_pf_away,w);
               if(n_pf_transverse!=0)h_profile_mtlep_npf_transverse->Fill(tlep.M(),n_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_mtlep_sumpt_transverse->Fill(tlep.M(),ptsum_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_mtlep_avept_transverse->Fill(tlep.M(),ptsum_pf_transverse/n_pf_transverse,w);
               if(n_pf_toward!=0)h_profile_mtlep_npf_toward->Fill(tlep.M(),n_pf_toward,w);
               if(n_pf_toward!=0)h_profile_mtlep_sumpt_toward->Fill(tlep.M(),ptsum_pf_toward,w);
               if(n_pf_toward!=0)h_profile_mtlep_avept_toward->Fill(tlep.M(),ptsum_pf_toward/n_pf_toward,w);

             h_profile_ythad_npf->Fill(fabs(thad.Rapidity()),n_pf,w);
               h_profile_ythad_sumpt->Fill(fabs(thad.Rapidity()),ptsum_pf,w);
               h_profile_ythad_avept->Fill(fabs(thad.Rapidity()),ptsum_pf/n_pf,w);
               if(n_pf_away!=0)h_profile_ythad_npf_away->Fill(fabs(thad.Rapidity()),n_pf_away,w);
               if(n_pf_away!=0)h_profile_ythad_sumpt_away->Fill(fabs(thad.Rapidity()),ptsum_pf_away,w);
               if(n_pf_away!=0)h_profile_ythad_avept_away->Fill(fabs(thad.Rapidity()),ptsum_pf_away/n_pf_away,w);
               if(n_pf_transverse!=0)h_profile_ythad_npf_transverse->Fill(fabs(thad.Rapidity()),n_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_ythad_sumpt_transverse->Fill(fabs(thad.Rapidity()),ptsum_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_ythad_avept_transverse->Fill(fabs(thad.Rapidity()),ptsum_pf_transverse/n_pf_transverse,w);
               if(n_pf_toward!=0)h_profile_ythad_npf_toward->Fill(fabs(thad.Rapidity()),n_pf_toward,w);
               if(n_pf_toward!=0)h_profile_ythad_sumpt_toward->Fill(fabs(thad.Rapidity()),ptsum_pf_toward,w);
               if(n_pf_toward!=0)h_profile_ythad_avept_toward->Fill(fabs(thad.Rapidity()),ptsum_pf_toward/n_pf_toward,w);

             h_profile_ytlep_npf->Fill(fabs(thad.Rapidity()),n_pf,w);
               h_profile_ytlep_sumpt->Fill(fabs(thad.Rapidity()),ptsum_pf,w);
               h_profile_ytlep_avept->Fill(fabs(thad.Rapidity()),ptsum_pf/n_pf,w);
               if(n_pf_away!=0)h_profile_ytlep_npf_away->Fill(fabs(thad.Rapidity()),n_pf_away,w);
               if(n_pf_away!=0)h_profile_ytlep_sumpt_away->Fill(fabs(thad.Rapidity()),ptsum_pf_away,w);
               if(n_pf_away!=0)h_profile_ytlep_avept_away->Fill(fabs(thad.Rapidity()),ptsum_pf_away/n_pf_away,w);
               if(n_pf_transverse!=0)h_profile_ytlep_npf_transverse->Fill(fabs(thad.Rapidity()),n_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_ytlep_sumpt_transverse->Fill(fabs(thad.Rapidity()),ptsum_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_ytlep_avept_transverse->Fill(fabs(thad.Rapidity()),ptsum_pf_transverse/n_pf_transverse,w);
               if(n_pf_toward!=0)h_profile_ytlep_npf_toward->Fill(fabs(thad.Rapidity()),n_pf_toward,w);
               if(n_pf_toward!=0)h_profile_ytlep_sumpt_toward->Fill(fabs(thad.Rapidity()),ptsum_pf_toward,w);
               if(n_pf_toward!=0)h_profile_ytlep_avept_toward->Fill(fabs(thad.Rapidity()),ptsum_pf_toward/n_pf_toward,w);


              h_profile_ptt_npf->Fill(thad.Pt(),n_pf,w);
               h_profile_ptt_sumpt->Fill(thad.Pt(),ptsum_pf,w);
               h_profile_ptt_avept->Fill(thad.Pt(),ptsum_pf/n_pf,w);
               if(n_pf_away!=0)h_profile_ptt_npf_away->Fill(thad.Pt(),n_pf_away,w);
               if(n_pf_away!=0)h_profile_ptt_sumpt_away->Fill(thad.Pt(),ptsum_pf_away,w);
               if(n_pf_away!=0)h_profile_ptt_avept_away->Fill(thad.Pt(),ptsum_pf_away/n_pf_away,w);
               if(n_pf_transverse!=0)h_profile_ptt_npf_transverse->Fill(thad.Pt(),n_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_ptt_sumpt_transverse->Fill(thad.Pt(),ptsum_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_ptt_avept_transverse->Fill(thad.Pt(),ptsum_pf_transverse/n_pf_transverse,w);
               if(n_pf_toward!=0)h_profile_ptt_npf_toward->Fill(thad.Pt(),n_pf_toward,w);
               if(n_pf_toward!=0)h_profile_ptt_sumpt_toward->Fill(thad.Pt(),ptsum_pf_toward,w);
               if(n_pf_toward!=0)h_profile_ptt_avept_toward->Fill(thad.Pt(),ptsum_pf_toward/n_pf_toward,w);

               h_profile_ptt_npf->Fill(tlep.Pt(),n_pf,w);
               h_profile_ptt_sumpt->Fill(tlep.Pt(),ptsum_pf,w);
               h_profile_ptt_avept->Fill(tlep.Pt(),ptsum_pf/n_pf,w);
               if(n_pf_away!=0)h_profile_ptt_npf_away->Fill(tlep.Pt(),n_pf_away,w);
               if(n_pf_away!=0)h_profile_ptt_sumpt_away->Fill(tlep.Pt(),ptsum_pf_away,w);
               if(n_pf_away!=0)h_profile_ptt_avept_away->Fill(tlep.Pt(),ptsum_pf_away/n_pf_away,w);
               if(n_pf_transverse!=0)h_profile_ptt_npf_transverse->Fill(tlep.Pt(),n_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_ptt_sumpt_transverse->Fill(tlep.Pt(),ptsum_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_ptt_avept_transverse->Fill(tlep.Pt(),ptsum_pf_transverse/n_pf_transverse,w);
               if(n_pf_toward!=0)h_profile_ptt_npf_toward->Fill(tlep.Pt(),n_pf_toward,w);
               if(n_pf_toward!=0)h_profile_ptt_sumpt_toward->Fill(tlep.Pt(),ptsum_pf_toward,w);
               if(n_pf_toward!=0)h_profile_ptt_avept_toward->Fill(tlep.Pt(),ptsum_pf_toward/n_pf_toward,w);

              h_profile_mt_npf->Fill(thad.M(),n_pf,w);
               h_profile_mt_sumpt->Fill(thad.M(),ptsum_pf,w);
               h_profile_mt_avept->Fill(thad.M(),ptsum_pf/n_pf,w);
               if(n_pf_away!=0)h_profile_mt_npf_away->Fill(thad.M(),n_pf_away,w);
               if(n_pf_away!=0)h_profile_mt_sumpt_away->Fill(thad.M(),ptsum_pf_away,w);
               if(n_pf_away!=0)h_profile_mt_avept_away->Fill(thad.M(),ptsum_pf_away/n_pf_away,w);
               if(n_pf_transverse!=0)h_profile_mt_npf_transverse->Fill(thad.M(),n_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_mt_sumpt_transverse->Fill(thad.M(),ptsum_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_mt_avept_transverse->Fill(thad.M(),ptsum_pf_transverse/n_pf_transverse,w);
               if(n_pf_toward!=0)h_profile_mt_npf_toward->Fill(thad.M(),n_pf_toward,w);
               if(n_pf_toward!=0)h_profile_mt_sumpt_toward->Fill(thad.M(),ptsum_pf_toward,w);
               if(n_pf_toward!=0)h_profile_mt_avept_toward->Fill(thad.M(),ptsum_pf_toward/n_pf_toward,w);

              h_profile_mt_npf->Fill(tlep.M(),n_pf,w);
               h_profile_mt_sumpt->Fill(tlep.M(),ptsum_pf,w);
               h_profile_mt_avept->Fill(tlep.M(),ptsum_pf/n_pf,w);
               if(n_pf_away!=0)h_profile_mt_npf_away->Fill(tlep.M(),n_pf_away,w);
               if(n_pf_away!=0)h_profile_mt_sumpt_away->Fill(tlep.M(),ptsum_pf_away,w);
               if(n_pf_away!=0)h_profile_mt_avept_away->Fill(tlep.M(),ptsum_pf_away/n_pf_away,w);
               if(n_pf_transverse!=0)h_profile_mt_npf_transverse->Fill(tlep.M(),n_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_mt_sumpt_transverse->Fill(tlep.M(),ptsum_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_mt_avept_transverse->Fill(tlep.M(),ptsum_pf_transverse/n_pf_transverse,w);
               if(n_pf_toward!=0)h_profile_mt_npf_toward->Fill(tlep.M(),n_pf_toward,w);
               if(n_pf_toward!=0)h_profile_mt_sumpt_toward->Fill(tlep.M(),ptsum_pf_toward,w);
               if(n_pf_toward!=0)h_profile_mt_avept_toward->Fill(tlep.M(),ptsum_pf_toward/n_pf_toward,w);

             h_profile_yt_npf->Fill(fabs(thad.Rapidity()),n_pf,w);
               h_profile_yt_sumpt->Fill(fabs(thad.Rapidity()),ptsum_pf,w);
               h_profile_yt_avept->Fill(fabs(thad.Rapidity()),ptsum_pf/n_pf,w);
               if(n_pf_away!=0)h_profile_yt_npf_away->Fill(fabs(thad.Rapidity()),n_pf_away,w);
               if(n_pf_away!=0)h_profile_yt_sumpt_away->Fill(fabs(thad.Rapidity()),ptsum_pf_away,w);
               if(n_pf_away!=0)h_profile_yt_avept_away->Fill(fabs(thad.Rapidity()),ptsum_pf_away/n_pf_away,w);
               if(n_pf_transverse!=0)h_profile_yt_npf_transverse->Fill(fabs(thad.Rapidity()),n_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_yt_sumpt_transverse->Fill(fabs(thad.Rapidity()),ptsum_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_yt_avept_transverse->Fill(fabs(thad.Rapidity()),ptsum_pf_transverse/n_pf_transverse,w);
               if(n_pf_toward!=0)h_profile_yt_npf_toward->Fill(fabs(thad.Rapidity()),n_pf_toward,w);
               if(n_pf_toward!=0)h_profile_yt_sumpt_toward->Fill(fabs(thad.Rapidity()),ptsum_pf_toward,w);
               if(n_pf_toward!=0)h_profile_yt_avept_toward->Fill(fabs(thad.Rapidity()),ptsum_pf_toward/n_pf_toward,w);

             h_profile_yt_npf->Fill(fabs(thad.Rapidity()),n_pf,w);
               h_profile_yt_sumpt->Fill(fabs(thad.Rapidity()),ptsum_pf,w);
               h_profile_yt_avept->Fill(fabs(thad.Rapidity()),ptsum_pf/n_pf,w);
               if(n_pf_away!=0)h_profile_yt_npf_away->Fill(fabs(thad.Rapidity()),n_pf_away,w);
               if(n_pf_away!=0)h_profile_yt_sumpt_away->Fill(fabs(thad.Rapidity()),ptsum_pf_away,w);
               if(n_pf_away!=0)h_profile_yt_avept_away->Fill(fabs(thad.Rapidity()),ptsum_pf_away/n_pf_away,w);
               if(n_pf_transverse!=0)h_profile_yt_npf_transverse->Fill(fabs(thad.Rapidity()),n_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_yt_sumpt_transverse->Fill(fabs(thad.Rapidity()),ptsum_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_yt_avept_transverse->Fill(fabs(thad.Rapidity()),ptsum_pf_transverse/n_pf_transverse,w);
               if(n_pf_toward!=0)h_profile_yt_npf_toward->Fill(fabs(thad.Rapidity()),n_pf_toward,w);
               if(n_pf_toward!=0)h_profile_yt_sumpt_toward->Fill(fabs(thad.Rapidity()),ptsum_pf_toward,w);
               if(n_pf_toward!=0)h_profile_yt_avept_toward->Fill(fabs(thad.Rapidity()),ptsum_pf_toward/n_pf_toward,w);





        TLorentzVector ttj_vector;
         if(extra_jet_index!=99)ttj_vector=top_vector +atop_vector+jet_vector[extra_jet_index];
         if(extra_jet_index==99 &&extra_jet_index_1530!=99 )ttj_vector=top_vector +atop_vector+jet_vector_1530[extra_jet_index_1530];

         
         if(extra_jet_index!=99 ||extra_jet_index_1530!=99 ){
           h_rec_ttjY->Fill(ttj_vector.Rapidity(),w);

              h_profile_yttj_npf->Fill(fabs(ttj_vector.Rapidity()),n_pf,w);
               h_profile_yttj_sumpt->Fill(fabs(ttj_vector.Rapidity()),ptsum_pf,w);
               h_profile_yttj_avept->Fill(fabs(ttj_vector.Rapidity()),ptsum_pf/n_pf,w);
               if(n_pf_away!=0)h_profile_yttj_npf_away->Fill(fabs(ttj_vector.Rapidity()),n_pf_away,w);
               if(n_pf_away!=0)h_profile_yttj_sumpt_away->Fill(fabs(ttj_vector.Rapidity()),ptsum_pf_away,w);
               if(n_pf_away!=0)h_profile_yttj_avept_away->Fill(fabs(ttj_vector.Rapidity()),ptsum_pf_away/n_pf_away,w);
               if(n_pf_transverse!=0)h_profile_yttj_npf_transverse->Fill(fabs(ttj_vector.Rapidity()),n_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_yttj_sumpt_transverse->Fill(fabs(ttj_vector.Rapidity()),ptsum_pf_transverse,w);
               if(n_pf_transverse!=0)h_profile_yttj_avept_transverse->Fill(fabs(ttj_vector.Rapidity()),ptsum_pf_transverse/n_pf_transverse,w);
               if(n_pf_toward!=0)h_profile_yttj_npf_toward->Fill(fabs(ttj_vector.Rapidity()),n_pf_toward,w);
               if(n_pf_toward!=0)h_profile_yttj_sumpt_toward->Fill(fabs(ttj_vector.Rapidity()),ptsum_pf_toward,w);
               if(n_pf_toward!=0)h_profile_yttj_avept_toward->Fill(fabs(ttj_vector.Rapidity()),ptsum_pf_toward/n_pf_toward,w);


  
         }

        //     }
        //   }

         }
         h_nvtx->Fill(EvtInfo_NumVtx,w);

       }//mult sel
   }//event loop





  TTree *weight_tree;
  //if(sum_tot_weight!=0)wtot*=(sum_tot_weight/sum_no);
  weight_tree = new TTree("tree","tree");
  weight_tree->Branch("wtot",&wtot);
  cout<<sum_tot_weight/sum_no<<endl;
 // if(!sherpa)weight_tree->Branch("cnt0",&cnt0);
 // if(sherpa||mg5amcanlo)weight_tree->Branch("cnt0",&test);

  weight_tree->Fill();

  weight_tree->Print();
   file_out->Write();
   file_out->Close();
cout<<      ntottt<<" Mu20 "<<N_HLT_Mu20<<" TkMu20 "<<N_HLT_TkMu20<<" Mu20 OR TkMu20 "<<N_HLT_TkMu20ORMu20<<" Mu18 "<<N_HLT_Mu18<<" TkMu18 "<<N_HLT_TkMu18<<" Mu20_eta2p1 "<<N_HLT_Mu20_eta2p1<<" TkMu20_eta2p1 "<<N_HLT_TkMu20_eta2p1<<" Mu18_eta2p1 "<<N_HLT_Mu18_eta2p1<<" TkMu18_eta2p1 "<<N_HLT_TkMu18_eta2p1<<" Mu24_eta2p1 "<<N_HLT_Mu24_eta2p1<<endl;
   cout<<"real Nu solutions "<<real_count<<" complex solutions "<<complex_count<<" solved complex solutions "<<solved_complex_count<<" fraction of complex count "<<complex_count/(complex_count+real_count)<<" fraction of solved complex events "<<solved_complex_count/(complex_count)<<endl;    
//cout<<mu_tot_b_jet<<"  "<<mu_tot_b_tagged_jet<<"  "<<mu_tot_c_jet<<"  "<<mu_tot_c_tagged_jet<<"  "<<mu_tot_udsg_jet<<"  "<<mu_tot_udsg_tagged_jet<<"  "<<tot_b_jet<<"  "<<tot_b_tagged_jet<<"  "<<tot_c_jet<<"  "<<tot_c_tagged_jet<<"  "<<tot_udsg_jet<<"  "<<tot_udsg_tagged_jet<<endl;
//cout<<mu_tot_b_tagged_jet/mu_tot_b_jet<<"  "<<mu_tot_c_tagged_jet/mu_tot_c_jet<<"  "<<mu_tot_udsg_tagged_jet/mu_tot_udsg_jet<<"  "<<tot_b_tagged_jet/tot_b_jet<<"  "<<tot_c_tagged_jet/tot_c_jet<<"  "<<tot_udsg_tagged_jet/tot_udsg_jet<<"  "<<endl;
}

int main(int argc,char **argv){
  tt_uev_analyzer a;
  a.Loop();
}
