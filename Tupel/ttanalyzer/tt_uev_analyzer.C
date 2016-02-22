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
  BTagCalibration sf("csvv2", "btageffic.csv");
  BTagCalibrationReader reader(&calib,               // calibration instance
			       BTagEntry::OP_MEDIUM,  // operating point
			       "mujets",               // measurement type
			       "central");           // systematics type

  BTagCalibrationReader reader2(&sf,               // calibration instance
				BTagEntry::OP_MEDIUM,  // operating point
				"mujets",               // measurement type
				"central");           // systematics type


  standalone_LumiReWeighting puWeight(201525,0), puUp(201525,1), puDown(201525,-1);
  Long64_t nentries = fChain->GetEntries();
  //   if(nentries > 1)nentries = 1000;
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
  double pt_b_range[]={30,50,70,100,140,200,300,670};
  TFile* file_out = new TFile(name,"RECREATE"); 
  file_out->cd();	
  int pdfind_max=1;
  if(dosignal)pdfind_max=2;
  if(dopdf)pdfind_max=103;
  // if(dosignal) pdfind_max=103;
  TH1* h_sig_DXY= new TH1D("sig_DXY","sig_DXY",1000,-200,200);
  TH1* h_sig_DZ= new TH1D("sig_DZ","sig_DZ",1000,-200,200);
  TH2* h_sig_DXY_DZ= new TH2D("sig_DXY_DZ","sig_DXY_DZ",1000,-200,200,1000,-200,200);
  TH1* h_nzeroerr_DXY= new TH1D("nzero_DXY","nzero_DXY",1000,-200,200);
  TH1* h_nzeroerr_DZ= new TH1D("nzero_DZ","nzero_DZ",1000,-200,200);
  TH2* h_nzeroerr_DXY_DZ= new TH2D("nzero_DXY_DZ","nzero_DXY_DZ",1000,-200,200,1000,-200,200);



  TH1* h_zeroerr_DXY= new TH1D("zero_DXY","zero_DXY",1000,-200,200);
  TH1* h_zeroerr_DZ= new TH1D("zero_DZ","zero_DZ",1000,-200,200);
  TH2* h_zeroerr_DXY_DZ= new TH2D("zero_DXY_DZ","zero_DXY_DZ",1000,-200,200,1000,-200,200);

  TH1* h_track_high_purity= new TH1D("track_high_purity","track_high_purity",20,0,20);
  TH1* h_dr_rec_gen_part= new TH1D("dr_rec_gen_part","dr_rec_gen_part",100,0,2);
  TH1* h_drmin_rec_gen_part= new TH1D("drmin_rec_gen_part","drmin_rec_gen_part",100,0,2);

  TH1* h_dr_rec_gen_j1= new TH1D("dr_rec_gen_j1","dr_rec_gen_j1",100,0,2);
  TH1* h_dr_rec_gen_j2= new TH1D("dr_rec_gen_j2","dr_rec_gen_j2",100,0,2);
  TH1* h_dr_rec_gen_bj1= new TH1D("dr_rec_gen_bj1","dr_rec_gen_bj1",100,0,2);
  TH1* h_dr_rec_gen_bj2= new TH1D("dr_rec_gen_bj2","dr_rec_gen_bj2",100,0,2);


  TH1* h_dr_rec_gen_part_samecharge= new TH1D("dr_rec_gen_part_samecharge","dr_rec_gen_part_samecharge",100,0,2);
  TH1* h_drmin_rec_gen_part_samecharge= new TH1D("drmin_rec_gen_part_samecharge","drmin_rec_gen_part_samecharge",100,0,2);

  TH1* h_dr_rec_gen_part_oppcharge= new TH1D("dr_rec_gen_part_oppcharge","dr_rec_gen_part_oppcharge",100,0,2);
  TH1* h_drmin_rec_gen_part_oppcharge= new TH1D("drmin_rec_gen_part_oppcharge","drmin_rec_gen_part_oppcharge",100,0,2);

  TH1* h_dr_tmp= new TH1D("h_dr_tmp","h_dr_tmp",100,0,2);
  TH1* h_gen_mtlep= new TH1D("gen_mtlep","gen_mtlep",100,0,1000);
  TH1* h_gen_mthad= new TH1D("gen_mthad","gen_mthad",100,0,1000);
  TH1* h_gen_mwlep= new TH1D("gen_mwlep","gen_mwlep",200,0,1000);
  TH1* h_gen_mwhad= new TH1D("gen_mwhad","gen_mwhad",200,0,1000);

  TH1* h_gen_pttlep= new TH1D("gen_pttlep","gen_pttlep",100,0,1000);
  TH1* h_gen_ptthad= new TH1D("gen_ptthad","gen_ptthad",100,0,1000);
  TH1* h_gen_ptwlep= new TH1D("gen_ptwlep","gen_ptwlep",100,0,1000);
  TH1* h_gen_ptwhad= new TH1D("gen_ptwhad","gen_ptwhad",100,0,1000);

  TH1* h_gen_ptttbar= new TH1D("gen_ptttbar","gen_ptttbar",100,0,1000);

  TH1* h_gen_mttbar= new TH1D("gen_mttbar","gen_mttbar",100,0,1000);

  TH1* h_miss_pt[pdfind_max*2];
  TH1* h_miss_sumpt[pdfind_max*2];
  TH1* h_miss_avept[pdfind_max*2];
  TH1* h_miss_eta[pdfind_max*2];
  TH1* h_miss_mult[pdfind_max*2];

  //cout<<"aaaaaaaaaaaaaaa"<<endl;
  TH1* h_ljet_pt[pdfind_max*2];
  TH1* h_ljet_eta[pdfind_max*2];
  TH1* h_sljet_pt[pdfind_max*2];
  TH1* h_sljet_eta[pdfind_max*2];
  TH1* h_lbjet_pt[pdfind_max*2];
  TH1* h_lbjet_eta[pdfind_max*2];
  TH1* h_slbjet_pt[pdfind_max*2];
  TH1* h_slbjet_eta[pdfind_max*2];
  TH1* h_dijet_mass[pdfind_max*2];
  TH1* h_dijet_mass_narrow[pdfind_max*2];
  TH1* h_pt_ttbar[pdfind_max*2];
  TH1* h_phi_ttbar[pdfind_max*2];
  TH1* h_dphi_ttbar_pf[pdfind_max*2];
  TH1* h_njet_ttbar[pdfind_max*2];
  TH1* h_njet_15_ttbar[pdfind_max*2];
  TH1* h_njet_bb[pdfind_max*2];
  TH1* h_pt_ttbar_kinrec[pdfind_max*2];
  TH1* h_nu_pz[pdfind_max*2];
  TH1* h_nu_pt[pdfind_max*2];
  TH1* h_n_bjet[pdfind_max*2];
  TH1* h_deltar_pf_jetpf[pdfind_max*2];
  TH1* h_deltar_pf_jet[pdfind_max*2];
  TH1* h_deltar_pf_jet_after[pdfind_max*2];
  TH1* h_deltar_pf_mu[pdfind_max*2];
  TH1* h_mu_pt[pdfind_max*2];
  TH1* h_mu_eta[pdfind_max*2];
  TH1* h_mu_phi[pdfind_max*2];
  TH1* h_mu_iso[pdfind_max*2];
  TH1* h_mu_pt_meas[pdfind_max*2];
  TH1* h_mu_eta_meas[pdfind_max*2];
  TH1* h_mu_phi_meas[pdfind_max*2];
  TH1* h_mu_iso_meas[pdfind_max*2];
  TH1* h_met_meas[pdfind_max*2];
  TH2* h_dphi_ptsumpf[pdfind_max*2];
  TH2* h_dphi_ptaveragepf[pdfind_max*2];
  TH2* h_dphi_npf[pdfind_max*2];
  TH1* h_nvtx_npf[pdfind_max*2];
  TH2* h_dphi_ptsumpf_0j[pdfind_max*2];
  TH2* h_dphi_ptaveragepf_0j[pdfind_max*2];
  TH2* h_dphi_npf_0j[pdfind_max*2];
  TH1* h_nvtx_npf_0j[pdfind_max*2];
  TH2* h_dphi_ptsumpf_1j[pdfind_max*2];
  TH2* h_dphi_ptaveragepf_1j[pdfind_max*2];
  TH2* h_dphi_npf_1j[pdfind_max*2];
  TH1* h_nvtx_npf_1j[pdfind_max*2];
  TH2* h_dphi_ptsumpf_2pj[pdfind_max*2];
  TH2* h_dphi_ptaveragepf_2pj[pdfind_max*2];
  TH2* h_dphi_npf_2pj[pdfind_max*2];
  TH1* h_nvtx_npf_2pj[pdfind_max*2];
  TProfile* h_profile_dphi_ptsumpf[pdfind_max*2];
  TProfile* h_profile_dphi_ptaveragepf[pdfind_max*2];
  TProfile* h_profile_dphi_npf[pdfind_max*2];

  TH1* h_1d_dphi_npf[pdfind_max*2];
  TH2* h_2d_dphi_npf[pdfind_max*2];

  TH1* h_1d_ptttbar_npf[pdfind_max*2];
  TH2* h_2d_ptttbar_npf[pdfind_max*2];

  TH1* h_1d_npf_nott[pdfind_max*2];

  TH1* h_1d_npf[pdfind_max*2];
  TH2* h_2d_npf[pdfind_max*2];

  TH1* h_1d_ptavepf[pdfind_max*2];
  TH2* h_2d_ptavepf[pdfind_max*2];

  TH1* h_1d_ptsumpf[pdfind_max*2];
  TH2* h_2d_ptsumpf[pdfind_max*2];

  TH2* h_2d_mt[pdfind_max*2];
  TProfile* h_profile_nvtx_npf[pdfind_max*2];
  TProfile* h_profile_nvtx_njet15[pdfind_max*2];
  TProfile* h_profile_nvtx_njet30[pdfind_max*2];
  TProfile* h_profile_nvtx_sumpt[pdfind_max*2];
  TProfile* h_profile_dphi_ptsumpf_0j[pdfind_max*2];
  TProfile* h_profile_dphi_ptaveragepf_0j[pdfind_max*2];
  TProfile* h_profile_dphi_npf_0j[pdfind_max*2];
  TProfile* h_profile_nvtx_npf_0j[pdfind_max*2];
  TProfile* h_profile_nvtx_sumpt_0j[pdfind_max*2];
  TProfile* h_profile_dphi_ptsumpf_1j[pdfind_max*2];
  TProfile* h_profile_dphi_ptaveragepf_1j[pdfind_max*2];
  TProfile* h_profile_dphi_npf_1j[pdfind_max*2];
  TProfile* h_profile_nvtx_npf_1j[pdfind_max*2];
  TProfile* h_profile_nvtx_sumpt_1j[pdfind_max*2];
  TProfile* h_profile_dphi_ptsumpf_2pj[pdfind_max*2];
  TProfile* h_profile_dphi_ptaveragepf_2pj[pdfind_max*2];
  TProfile* h_profile_dphi_npf_2pj[pdfind_max*2];
  TProfile* h_profile_nvtx_npf_2pj[pdfind_max*2];
  TProfile* h_profile_nvtx_sumpt_2pj[pdfind_max*2];
  TProfile* h_profile_ptttbar_npf[pdfind_max*2];
  TProfile* h_profile_ptttbar_sumpt[pdfind_max*2];
  TProfile* h_profile_ptttbar_avept[pdfind_max*2];
  TProfile* h_profile_ptttbar_npf_away[pdfind_max*2];
  TProfile* h_profile_ptttbar_sumpt_away[pdfind_max*2];
  TProfile* h_profile_ptttbar_avept_away[pdfind_max*2];
  TProfile* h_profile_ptttbar_npf_transverse[pdfind_max*2];
  TProfile* h_profile_ptttbar_sumpt_transverse[pdfind_max*2];
  TProfile* h_profile_ptttbar_avept_transverse[pdfind_max*2];
  TProfile* h_profile_ptttbar_npf_toward[pdfind_max*2];
  TProfile* h_profile_ptttbar_sumpt_toward[pdfind_max*2];
  TProfile* h_profile_ptttbar_avept_toward[pdfind_max*2];
  TProfile* h_profile_deta_bb_njet_bb[pdfind_max*2];
  TProfile* h_profile_deta_bb_njet_extra[pdfind_max*2];

  TProfile* h_profile_ptttbar_njet30[pdfind_max*2];
  TProfile* h_profile_ptttbar_njet15[pdfind_max*2];

  TProfile* h_profile_ptttbar_njet30_away[pdfind_max*2];
  TProfile* h_profile_ptttbar_njet15_away[pdfind_max*2];

  TProfile* h_profile_ptttbar_njet30_transverse[pdfind_max*2];
  TProfile* h_profile_ptttbar_njet15_transverse[pdfind_max*2];

  TProfile* h_profile_ptttbar_njet30_toward[pdfind_max*2];
  TProfile* h_profile_ptttbar_njet15_toward[pdfind_max*2];

  TProfile* h_profile_mttbar_npf[pdfind_max*2];
  TProfile* h_profile_mttbar_sumpt[pdfind_max*2];
  TProfile* h_profile_mttbar_avept[pdfind_max*2];
  TProfile* h_profile_mttbar_npf_away[pdfind_max*2];
  TProfile* h_profile_mttbar_sumpt_away[pdfind_max*2];
  TProfile* h_profile_mttbar_avept_away[pdfind_max*2];
  TProfile* h_profile_mttbar_npf_transverse[pdfind_max*2];
  TProfile* h_profile_mttbar_sumpt_transverse[pdfind_max*2];
  TProfile* h_profile_mttbar_avept_transverse[pdfind_max*2];
  TProfile* h_profile_mttbar_npf_toward[pdfind_max*2];
  TProfile* h_profile_mttbar_sumpt_toward[pdfind_max*2];
  TProfile* h_profile_mttbar_avept_toward[pdfind_max*2];
  TProfile* h_profile_ytt_npf[pdfind_max*2];
  TProfile* h_profile_ytt_sumpt[pdfind_max*2];
  TProfile* h_profile_ytt_avept[pdfind_max*2];
  TProfile* h_profile_ytt_npf_away[pdfind_max*2];
  TProfile* h_profile_ytt_sumpt_away[pdfind_max*2];
  TProfile* h_profile_ytt_avept_away[pdfind_max*2];
  TProfile* h_profile_ytt_npf_transverse[pdfind_max*2];
  TProfile* h_profile_ytt_sumpt_transverse[pdfind_max*2];
  TProfile* h_profile_ytt_avept_transverse[pdfind_max*2];
  TProfile* h_profile_ytt_npf_toward[pdfind_max*2];
  TProfile* h_profile_ytt_sumpt_toward[pdfind_max*2];
  TProfile* h_profile_ytt_avept_toward[pdfind_max*2];
  TProfile* h_profile_yttj_npf[pdfind_max*2];
  TProfile* h_profile_yttj_sumpt[pdfind_max*2];
  TProfile* h_profile_yttj_avept[pdfind_max*2];
  TProfile* h_profile_yttj_npf_away[pdfind_max*2];
  TProfile* h_profile_yttj_sumpt_away[pdfind_max*2];
  TProfile* h_profile_yttj_avept_away[pdfind_max*2];
  TProfile* h_profile_yttj_npf_transverse[pdfind_max*2];
  TProfile* h_profile_yttj_sumpt_transverse[pdfind_max*2];
  TProfile* h_profile_yttj_avept_transverse[pdfind_max*2];
  TProfile* h_profile_yttj_npf_toward[pdfind_max*2];
  TProfile* h_profile_yttj_sumpt_toward[pdfind_max*2];
  TProfile* h_profile_yttj_avept_toward[pdfind_max*2];
  TProfile* h_profile_mtop_npf[pdfind_max*2];
  TProfile* h_profile_mtop_sumpt[pdfind_max*2];
  TProfile* h_profile_mtop_avept[pdfind_max*2];
  TProfile* h_profile_mtop_npf_away[pdfind_max*2];
  TProfile* h_profile_mtop_sumpt_away[pdfind_max*2];
  TProfile* h_profile_mtop_avept_away[pdfind_max*2];
  TProfile* h_profile_mtop_npf_transverse[pdfind_max*2];
  TProfile* h_profile_mtop_sumpt_transverse[pdfind_max*2];
  TProfile* h_profile_mtop_avept_transverse[pdfind_max*2];
  TProfile* h_profile_mtop_npf_toward[pdfind_max*2];
  TProfile* h_profile_mtop_sumpt_toward[pdfind_max*2];
  TProfile* h_profile_mtop_avept_toward[pdfind_max*2];
  TProfile* h_profile_matop_npf[pdfind_max*2];
  TProfile* h_profile_matop_sumpt[pdfind_max*2];
  TProfile* h_profile_matop_avept[pdfind_max*2];
  TProfile* h_profile_matop_npf_away[pdfind_max*2];
  TProfile* h_profile_matop_sumpt_away[pdfind_max*2];
  TProfile* h_profile_matop_avept_away[pdfind_max*2];
  TProfile* h_profile_matop_npf_transverse[pdfind_max*2];
  TProfile* h_profile_matop_sumpt_transverse[pdfind_max*2];
  TProfile* h_profile_matop_avept_transverse[pdfind_max*2];
  TProfile* h_profile_matop_npf_toward[pdfind_max*2];
  TProfile* h_profile_matop_sumpt_toward[pdfind_max*2];
  TProfile* h_profile_matop_avept_toward[pdfind_max*2];
  TProfile* h_profile_pttop_npf[pdfind_max*2];
  TProfile* h_profile_pttop_sumpt[pdfind_max*2];
  TProfile* h_profile_pttop_avept[pdfind_max*2];
  TProfile* h_profile_pttop_npf_away[pdfind_max*2];
  TProfile* h_profile_pttop_sumpt_away[pdfind_max*2];
  TProfile* h_profile_pttop_avept_away[pdfind_max*2];
  TProfile* h_profile_pttop_npf_transverse[pdfind_max*2];
  TProfile* h_profile_pttop_sumpt_transverse[pdfind_max*2];
  TProfile* h_profile_pttop_avept_transverse[pdfind_max*2];
  TProfile* h_profile_pttop_npf_toward[pdfind_max*2];
  TProfile* h_profile_pttop_sumpt_toward[pdfind_max*2];
  TProfile* h_profile_pttop_avept_toward[pdfind_max*2];
  TProfile* h_profile_ptatop_npf[pdfind_max*2];
  TProfile* h_profile_ptatop_sumpt[pdfind_max*2];
  TProfile* h_profile_ptatop_avept[pdfind_max*2];
  TProfile* h_profile_ptatop_npf_away[pdfind_max*2];
  TProfile* h_profile_ptatop_sumpt_away[pdfind_max*2];
  TProfile* h_profile_ptatop_avept_away[pdfind_max*2];
  TProfile* h_profile_ptatop_npf_transverse[pdfind_max*2];
  TProfile* h_profile_ptatop_sumpt_transverse[pdfind_max*2];
  TProfile* h_profile_ptatop_avept_transverse[pdfind_max*2];
  TProfile* h_profile_ptatop_npf_toward[pdfind_max*2];
  TProfile* h_profile_ptatop_sumpt_toward[pdfind_max*2];
  TProfile* h_profile_ptatop_avept_toward[pdfind_max*2];
  TProfile* h_profile_ytop_npf[pdfind_max*2];
  TProfile* h_profile_ytop_sumpt[pdfind_max*2];
  TProfile* h_profile_ytop_avept[pdfind_max*2];
  TProfile* h_profile_ytop_npf_away[pdfind_max*2];
  TProfile* h_profile_ytop_sumpt_away[pdfind_max*2];
  TProfile* h_profile_ytop_avept_away[pdfind_max*2];
  TProfile* h_profile_ytop_npf_transverse[pdfind_max*2];
  TProfile* h_profile_ytop_sumpt_transverse[pdfind_max*2];
  TProfile* h_profile_ytop_avept_transverse[pdfind_max*2];
  TProfile* h_profile_ytop_npf_toward[pdfind_max*2];
  TProfile* h_profile_ytop_sumpt_toward[pdfind_max*2];
  TProfile* h_profile_ytop_avept_toward[pdfind_max*2];
  TProfile* h_profile_yatop_npf[pdfind_max*2];
  TProfile* h_profile_yatop_sumpt[pdfind_max*2];
  TProfile* h_profile_yatop_avept[pdfind_max*2];
  TProfile* h_profile_yatop_npf_away[pdfind_max*2];
  TProfile* h_profile_yatop_sumpt_away[pdfind_max*2];
  TProfile* h_profile_yatop_avept_away[pdfind_max*2];
  TProfile* h_profile_yatop_npf_transverse[pdfind_max*2];
  TProfile* h_profile_yatop_sumpt_transverse[pdfind_max*2];
  TProfile* h_profile_yatop_avept_transverse[pdfind_max*2];
  TProfile* h_profile_yatop_npf_toward[pdfind_max*2];
  TProfile* h_profile_yatop_sumpt_toward[pdfind_max*2];
  TProfile* h_profile_yatop_avept_toward[pdfind_max*2];
  TProfile* h_profile_mthad_npf[pdfind_max*2];
  TProfile* h_profile_mthad_sumpt[pdfind_max*2];
  TProfile* h_profile_mthad_avept[pdfind_max*2];
  TProfile* h_profile_mthad_npf_away[pdfind_max*2];
  TProfile* h_profile_mthad_sumpt_away[pdfind_max*2];
  TProfile* h_profile_mthad_avept_away[pdfind_max*2];
  TProfile* h_profile_mthad_npf_transverse[pdfind_max*2];
  TProfile* h_profile_mthad_sumpt_transverse[pdfind_max*2];
  TProfile* h_profile_mthad_avept_transverse[pdfind_max*2];
  TProfile* h_profile_mthad_npf_toward[pdfind_max*2];
  TProfile* h_profile_mthad_sumpt_toward[pdfind_max*2];
  TProfile* h_profile_mthad_avept_toward[pdfind_max*2];
  TProfile* h_profile_mtlep_npf[pdfind_max*2];
  TProfile* h_profile_mtlep_sumpt[pdfind_max*2];
  TProfile* h_profile_mtlep_avept[pdfind_max*2];
  TProfile* h_profile_mtlep_npf_away[pdfind_max*2];
  TProfile* h_profile_mtlep_sumpt_away[pdfind_max*2];
  TProfile* h_profile_mtlep_avept_away[pdfind_max*2];
  TProfile* h_profile_mtlep_npf_transverse[pdfind_max*2];
  TProfile* h_profile_mtlep_sumpt_transverse[pdfind_max*2];
  TProfile* h_profile_mtlep_avept_transverse[pdfind_max*2];
  TProfile* h_profile_mtlep_npf_toward[pdfind_max*2];
  TProfile* h_profile_mtlep_sumpt_toward[pdfind_max*2];
  TProfile* h_profile_mtlep_avept_toward[pdfind_max*2];
  TProfile* h_profile_ptthad_npf[pdfind_max*2];
  TProfile* h_profile_ptthad_sumpt[pdfind_max*2];
  TProfile* h_profile_ptthad_avept[pdfind_max*2];
  TProfile* h_profile_ptthad_npf_away[pdfind_max*2];
  TProfile* h_profile_ptthad_sumpt_away[pdfind_max*2];
  TProfile* h_profile_ptthad_avept_away[pdfind_max*2];
  TProfile* h_profile_ptthad_npf_transverse[pdfind_max*2];
  TProfile* h_profile_ptthad_sumpt_transverse[pdfind_max*2];
  TProfile* h_profile_ptthad_avept_transverse[pdfind_max*2];
  TProfile* h_profile_ptthad_npf_toward[pdfind_max*2];
  TProfile* h_profile_ptthad_sumpt_toward[pdfind_max*2];
  TProfile* h_profile_ptthad_avept_toward[pdfind_max*2];
  TProfile* h_profile_pttlep_npf[pdfind_max*2];
  TProfile* h_profile_pttlep_sumpt[pdfind_max*2];
  TProfile* h_profile_pttlep_avept[pdfind_max*2];
  TProfile* h_profile_pttlep_npf_away[pdfind_max*2];
  TProfile* h_profile_pttlep_sumpt_away[pdfind_max*2];
  TProfile* h_profile_pttlep_avept_away[pdfind_max*2];
  TProfile* h_profile_pttlep_npf_transverse[pdfind_max*2];
  TProfile* h_profile_pttlep_sumpt_transverse[pdfind_max*2];
  TProfile* h_profile_pttlep_avept_transverse[pdfind_max*2];
  TProfile* h_profile_pttlep_npf_toward[pdfind_max*2];
  TProfile* h_profile_pttlep_sumpt_toward[pdfind_max*2];
  TProfile* h_profile_pttlep_avept_toward[pdfind_max*2];
  TProfile* h_profile_ythad_npf[pdfind_max*2];
  TProfile* h_profile_ythad_sumpt[pdfind_max*2];
  TProfile* h_profile_ythad_avept[pdfind_max*2];
  TProfile* h_profile_ythad_npf_away[pdfind_max*2];
  TProfile* h_profile_ythad_sumpt_away[pdfind_max*2];
  TProfile* h_profile_ythad_avept_away[pdfind_max*2];
  TProfile* h_profile_ythad_npf_transverse[pdfind_max*2];
  TProfile* h_profile_ythad_sumpt_transverse[pdfind_max*2];
  TProfile* h_profile_ythad_avept_transverse[pdfind_max*2];
  TProfile* h_profile_ythad_npf_toward[pdfind_max*2];
  TProfile* h_profile_ythad_sumpt_toward[pdfind_max*2];
  TProfile* h_profile_ythad_avept_toward[pdfind_max*2];
  TProfile* h_profile_ytlep_npf[pdfind_max*2];
  TProfile* h_profile_ytlep_sumpt[pdfind_max*2];
  TProfile* h_profile_ytlep_avept[pdfind_max*2];
  TProfile* h_profile_ytlep_npf_away[pdfind_max*2];
  TProfile* h_profile_ytlep_sumpt_away[pdfind_max*2];
  TProfile* h_profile_ytlep_avept_away[pdfind_max*2];
  TProfile* h_profile_ytlep_npf_transverse[pdfind_max*2];
  TProfile* h_profile_ytlep_sumpt_transverse[pdfind_max*2];
  TProfile* h_profile_ytlep_avept_transverse[pdfind_max*2];
  TProfile* h_profile_ytlep_npf_toward[pdfind_max*2];
  TProfile* h_profile_ytlep_sumpt_toward[pdfind_max*2];
  TProfile* h_profile_ytlep_avept_toward[pdfind_max*2];
  TProfile* h_profile_mt_npf[pdfind_max*2];
  TProfile* h_profile_mt_sumpt[pdfind_max*2];
  TProfile* h_profile_mt_avept[pdfind_max*2];
  TProfile* h_profile_mt_npf_away[pdfind_max*2];
  TProfile* h_profile_mt_sumpt_away[pdfind_max*2];
  TProfile* h_profile_mt_avept_away[pdfind_max*2];
  TProfile* h_profile_mt_npf_transverse[pdfind_max*2];
  TProfile* h_profile_mt_sumpt_transverse[pdfind_max*2];
  TProfile* h_profile_mt_avept_transverse[pdfind_max*2];
  TProfile* h_profile_mt_npf_toward[pdfind_max*2];
  TProfile* h_profile_mt_sumpt_toward[pdfind_max*2];
  TProfile* h_profile_mt_avept_toward[pdfind_max*2];
  TProfile* h_profile_ptt_npf[pdfind_max*2];
  TProfile* h_profile_ptt_sumpt[pdfind_max*2];
  TProfile* h_profile_ptt_avept[pdfind_max*2];
  TProfile* h_profile_ptt_npf_away[pdfind_max*2];
  TProfile* h_profile_ptt_sumpt_away[pdfind_max*2];
  TProfile* h_profile_ptt_avept_away[pdfind_max*2];
  TProfile* h_profile_ptt_npf_transverse[pdfind_max*2];
  TProfile* h_profile_ptt_sumpt_transverse[pdfind_max*2];
  TProfile* h_profile_ptt_avept_transverse[pdfind_max*2];
  TProfile* h_profile_ptt_npf_toward[pdfind_max*2];
  TProfile* h_profile_ptt_sumpt_toward[pdfind_max*2];
  TProfile* h_profile_ptt_avept_toward[pdfind_max*2];
  TProfile* h_profile_yt_npf[pdfind_max*2];
  TProfile* h_profile_yt_sumpt[pdfind_max*2];
  TProfile* h_profile_yt_avept[pdfind_max*2];
  TProfile* h_profile_yt_npf_away[pdfind_max*2];
  TProfile* h_profile_yt_sumpt_away[pdfind_max*2];
  TProfile* h_profile_yt_avept_away[pdfind_max*2];
  TProfile* h_profile_yt_npf_transverse[pdfind_max*2];
  TProfile* h_profile_yt_sumpt_transverse[pdfind_max*2];
  TProfile* h_profile_yt_avept_transverse[pdfind_max*2];
  TProfile* h_profile_yt_npf_toward[pdfind_max*2];
  TProfile* h_profile_yt_sumpt_toward[pdfind_max*2];
  TProfile* h_profile_yt_avept_toward[pdfind_max*2];
  TH1* h_nvtx[pdfind_max*2];
  TH1* h_pf_dxy[pdfind_max*2];
  TH1* h_pf_dz[pdfind_max*2];
  TH1* h_pf_sigmadxy[pdfind_max*2];
  TH1* h_pf_sigmadz[pdfind_max*2];
  TH1* h_pf_pt[pdfind_max*2];
  TH1* h_csv[pdfind_max*2];
  TH1* h_csvmax[pdfind_max*2];
  TH1* h_csvmax2[pdfind_max*2];
  TH1* h_npf_inclusive[pdfind_max*2];
  TH1* h_npf_toward[pdfind_max*2];
  TH1* h_npf_transverse[pdfind_max*2];
  TH1* h_npf_away[pdfind_max*2];
  TH1* h_ptsumpf_inclusive[pdfind_max*2];
  TH1* h_ptsumpf_toward[pdfind_max*2];
  TH1* h_ptsumpf_transverse[pdfind_max*2];
  TH1* h_ptsumpf_away[pdfind_max*2];
  TH1* h_ptavepf_inclusive[pdfind_max*2];
  TH1* h_ptavepf_toward[pdfind_max*2];
  TH1* h_ptavepf_transverse[pdfind_max*2];
  TH1* h_ptavepf_away[pdfind_max*2];
  TH1*h_puweight[pdfind_max*2];
  TH1*h_puweight_weighted[pdfind_max*2];
  TH1*h_puweight_meas[pdfind_max*2];
  TH1*h_puweight_weighted_meas[pdfind_max*2];
  TH1* h_MTW[pdfind_max*2];
  TH1* h_m_thad[pdfind_max*2];
  TH1* h_m_thad_fixbin[pdfind_max*2];
  TH1* h_m_tlep[pdfind_max*2];
  TH1* h_m_tlep_fixbin[pdfind_max*2];
  TH1* h_m_top[pdfind_max*2];
  TH1* h_m_atop[pdfind_max*2];
  TH1* h_pt_top[pdfind_max*2];
  TH1* h_pt_atop[pdfind_max*2];
  TH1* h_m_top_fixbin[pdfind_max*2];
  TH1* h_m_atop_fixbin[pdfind_max*2];
  TH1* h_pt_top_fixbin[pdfind_max*2];
  TH1* h_pt_atop_fixbin[pdfind_max*2];
  TH1* h_y_top[pdfind_max*2];
  TH1* h_y_atop[pdfind_max*2];
  TH1*   h_rec_ttjY[pdfind_max*2];
  TH1* h_m_ttbar[pdfind_max*2];
  TH1* h_m_ttbar_fixbin[pdfind_max*2];
  TH1* h_y_ttbar[pdfind_max*2];
  TH1* h_pt_thad[pdfind_max*2];
  TH1* h_pt_thad_fixbin[pdfind_max*2];
  TH1* h_pt_tlep[pdfind_max*2];
  TH1* h_pt_tlep_fixbin[pdfind_max*2];
  TH1* h_y_thad[pdfind_max*2];
  TH1* h_y_tlep[pdfind_max*2];
  TH1* h_m_t[pdfind_max*2];
  TH1* h_m_t_fixbin[pdfind_max*2];
  TH1* h_pt_t[pdfind_max*2];
  TH1* h_pt_t_fixbin[pdfind_max*2];
  TH1* h_y_t[pdfind_max*2];
  TH2* h_pt_eta_b[pdfind_max*2];
  TH2* h_pt_eta_b_tagged[pdfind_max*2];
  TH2* h_pt_eta_c[pdfind_max*2];
  TH2* h_pt_eta_c_tagged[pdfind_max*2];
  TH2* h_pt_eta_udsg[pdfind_max*2];
  TH2* h_pt_eta_udsg_tagged[pdfind_max*2];
  char nam[100000];
  for(int i =0; i<pdfind_max*2;i++){
    sprintf(nam,"miss_pt_%i",i);
    h_miss_pt[i]= new TH1D (nam,nam,1000,0,1000);
    sprintf(nam,"miss_sumpt_%i",i);
    h_miss_sumpt[i]= new TH1D (nam,nam,500,0,500);
    sprintf(nam,"miss_avept_%i",i);
    h_miss_avept[i]= new TH1D (nam,nam,500,0,500);
    sprintf(nam,"miss_eta_%i",i);
    h_miss_eta[i]= new TH1D (nam,nam,100,-2.5,2.5);
    sprintf(nam,"miss_mult_%i",i);
    h_miss_mult[i]= new TH1D (nam,nam,500,0,500);
    sprintf(nam,"pt_eta_b_%i",i);
    h_pt_eta_b[i]= new TH2D(nam,nam,7,pt_b_range,10,-2.4,2.4);
    sprintf(nam,"pt_eta_b_tagged_%i",i);
    h_pt_eta_b_tagged[i]= new TH2D(nam,nam,7,pt_b_range,10,-2.4,2.4);
    sprintf(nam,"pt_eta_c_%i",i);
    h_pt_eta_c[i]= new TH2D(nam,nam,7,pt_b_range,10,-2.4,2.4);
    sprintf(nam,"pt_eta_c_tagged_%i",i);
    h_pt_eta_c_tagged[i]= new TH2D(nam,nam,7,pt_b_range,10,-2.4,2.4);
    sprintf(nam,"pt_eta_udsg_%i",i);
    h_pt_eta_udsg[i]= new TH2D(nam,nam,7,pt_b_range,10,-2.4,2.4);
    sprintf(nam,"pt_eta_udsg_tagged_%i",i);
    h_pt_eta_udsg_tagged[i]= new TH2D(nam,nam,7,pt_b_range,10,-2.4,2.4);

    sprintf(nam,"ljet_pt_%i",i);
    h_ljet_pt[i]= new TH1D (nam,nam,100,0,1000);
    sprintf(nam,"ljet_eta_%i",i);
    h_ljet_eta[i]= new TH1D (nam,nam,100,-2.5,2.5);

    sprintf(nam,"sljet_pt_%i",i);
    h_sljet_pt[i]= new TH1D (nam,nam,100,0,1000);
    sprintf(nam,"sljet_eta_%i",i);
    h_sljet_eta[i]= new TH1D (nam,nam,100,-2.5,2.5);

    sprintf(nam,"lbjet_pt_%i",i);
    h_lbjet_pt[i]= new TH1D (nam,nam,100,0,1000);
    sprintf(nam,"lbjet_eta_%i",i);
    h_lbjet_eta[i]= new TH1D (nam,nam,100,-2.5,2.5);

    sprintf(nam,"slbjet_pt_%i",i);
    h_slbjet_pt[i]= new TH1D (nam,nam,100,0,1000);
    sprintf(nam,"slbjet_eta_%i",i);
    h_slbjet_eta[i]= new TH1D (nam,nam,100,-2.5,2.5);

    sprintf(nam,"dijet_mass_%i",i);
    h_dijet_mass[i]= new TH1D (nam,nam,100,0,1000);
    sprintf(nam,"dijet_mass_narrow_%i",i);
    h_dijet_mass_narrow[i]= new TH1D (nam,nam,1000,0,200);
    sprintf(nam,"pt_ttbar_%i",i);
    h_pt_ttbar[i]= new TH1D (nam,nam,10,pt_tt_range);
    sprintf(nam,"phi_ttbar_%i",i);
    h_phi_ttbar[i]= new TH1D (nam,nam,100,0,3.14);
    sprintf(nam,"dphi_ttbar_pf_%i",i);
    h_dphi_ttbar_pf[i]= new TH1D (nam,nam,20,0,180);
    sprintf(nam,"njet_ttbar_%i",i);
    h_njet_ttbar[i]= new TH1D (nam,nam,15,-0.5,14.5);
    sprintf(nam,"njet_15_ttbar_%i",i);
    h_njet_15_ttbar[i]= new TH1D (nam,nam,15,-0.5,14.5);
    sprintf(nam,"njet_bb_%i",i);
    h_njet_bb[i]= new TH1D (nam,nam,15,-0.5,14.5);

    sprintf(nam,"pt_ttbar_kinrec_%i",i);
    h_pt_ttbar_kinrec[i]= new TH1D (nam,nam,10,pt_tt_range);
    sprintf(nam,"nu_pz_%i",i);
    h_nu_pz[i]= new TH1D (nam,nam,200,0,1000);
    sprintf(nam,"nu_pt_%i",i);
    h_nu_pt[i]= new TH1D (nam,nam,200,0,1000);


    sprintf(nam,"n_bjet_%i",i);
    h_n_bjet[i]= new TH1D (nam,nam,15,-0.5,14.5);
    sprintf(nam,"deltar_pf_jetpf_%i",i);
    h_deltar_pf_jetpf[i]= new TH1D (nam,nam,1000,0,5);
    sprintf(nam,"deltar_pf_jet_%i",i);
    h_deltar_pf_jet[i]= new TH1D (nam,nam,1000,0,5);
    sprintf(nam,"deltar_pf_jet_after_%i",i);
    h_deltar_pf_jet_after[i]= new TH1D (nam,nam,1000,0,5);
    sprintf(nam,"deltar_pf_mu_%i",i);
    h_deltar_pf_mu[i]= new TH1D (nam,nam,1000,0,5);

    sprintf(nam,"mu_pt_%i",i);
    h_mu_pt[i]= new TH1D (nam,nam,5000,0,1000);
    sprintf(nam,"mu_eta_%i",i);
    h_mu_eta[i]= new TH1D (nam,nam,100,-2.5,2.5);
    sprintf(nam,"mu_phi_%i",i);
    h_mu_phi[i]= new TH1D (nam,nam,100,0,3.14);
    sprintf(nam,"mu_iso_%i",i);
    h_mu_iso[i]= new TH1D (nam,nam,1000,0,0.5);

    sprintf(nam,"mu_pt_meas_%i",i);
    h_mu_pt_meas[i]= new TH1D (nam,nam,5000,0,1000);
    sprintf(nam,"mu_eta_meas_%i",i);
    h_mu_eta_meas[i]= new TH1D (nam,nam,100,-2.5,2.5);
    sprintf(nam,"mu_phi_meas_%i",i);
    h_mu_phi_meas[i]= new TH1D (nam,nam,100,0,3.14);
    sprintf(nam,"mu_iso_meas_%i",i);
    h_mu_iso_meas[i]= new TH1D (nam,nam,1000,0,0.5);
    sprintf(nam,"met_meas_%i",i);
    h_met_meas[i]= new TH1D (nam,nam,200,0,1000);

    sprintf(nam,"dphi_ptsumpf_%i",i);
    h_dphi_ptsumpf[i]= new TH2D (nam,nam,20,0,180,20,0,10);
    sprintf(nam,"dphi_ptaveragepf_%i",i);
    h_dphi_ptaveragepf[i]= new TH2D (nam,nam,20,0,180,20,0,10);
    sprintf(nam,"dphi_npf_%i",i);
    h_dphi_npf[i]= new TH2D (nam,nam,20,0,180,20,0,10);
    sprintf(nam,"nvtx_npf_%i",i);
    h_nvtx_npf[i]= new TH1D (nam,nam,50,0,49);
    sprintf(nam,"dphi_ptsumpf_0j_%i",i);
    h_dphi_ptsumpf_0j[i]= new TH2D (nam,nam,20,0,180,20,0,10);
    sprintf(nam,"dphi_ptaveragepf_0j_%i",i);
    h_dphi_ptaveragepf_0j[i]= new TH2D (nam,nam,20,0,180,20,0,10);
    sprintf(nam,"dphi_npf_0j_%i",i);
    h_dphi_npf_0j[i]= new TH2D (nam,nam,20,0,180,20,0,10);
    sprintf(nam,"nvtx_npf_0j_%i",i);
    h_nvtx_npf_0j[i]= new TH1D (nam,nam,50,0,49);
    sprintf(nam,"dphi_ptsumpf_1j_%i",i);
    h_dphi_ptsumpf_1j[i]= new TH2D (nam,nam,20,0,180,20,0,10);
    sprintf(nam,"dphi_ptaveragepf_1j_%i",i);
    h_dphi_ptaveragepf_1j[i]= new TH2D (nam,nam,20,0,180,20,0,10);
    sprintf(nam,"dphi_npf_1j_%i",i);
    h_dphi_npf_1j[i]= new TH2D (nam,nam,20,0,180,20,0,10);
    sprintf(nam,"nvtx_npf_1j_%i",i);
    h_nvtx_npf_1j[i]= new TH1D (nam,nam,50,0,49);
    sprintf(nam,"dphi_ptsumpf_2pj_%i",i);
    h_dphi_ptsumpf_2pj[i]= new TH2D (nam,nam,20,0,180,20,0,10);
    sprintf(nam,"dphi_ptaveragepf_2pj_%i",i);
    h_dphi_ptaveragepf_2pj[i]= new TH2D (nam,nam,20,0,180,20,0,10);
    sprintf(nam,"dphi_npf_2pj_%i",i);
    h_dphi_npf_2pj[i]= new TH2D (nam,nam,20,0,180,20,0,10);
    sprintf(nam,"nvtx_npf_2pj_%i",i);
    h_nvtx_npf_2pj[i]= new TH1D (nam,nam,50,0,49);
    sprintf(nam,"profile_dphi_ptsumpf_%i",i);
    h_profile_dphi_ptsumpf[i]= new TProfile (nam,nam,20,0,180,0,1000);
    sprintf(nam,"profile_dphi_ptaveragepf_%i",i);
    h_profile_dphi_ptaveragepf[i]= new TProfile (nam,nam,20,0,180,0,1000);
    sprintf(nam,"profile_dphi_npf_%i",i);
    h_profile_dphi_npf[i]= new TProfile (nam,nam,20,0,180,0,1000);


    sprintf(nam,"1d_dphi_npf_%i",i);
    h_1d_dphi_npf[i]= new TH1D (nam,nam,200,0,199);

    sprintf(nam,"2d_dphi_npf_%i",i);
    h_2d_dphi_npf[i]= new TH2D (nam,nam,200,0,199,200,0,199);


    sprintf(nam,"1d_ptttbar_npf_%i",i);
    h_1d_ptttbar_npf[i]= new TH1D (nam,nam,500,0,499);

    sprintf(nam,"2d_ptttbar_npf_%i",i);
    h_2d_ptttbar_npf[i]= new TH2D (nam,nam,500,0,499,500,0,499);



    sprintf(nam,"1d_npf_%i",i);
    h_1d_npf[i]= new TH1D (nam,nam,500,0,500);

    sprintf(nam,"2d_npf_%i",i);
    h_2d_npf[i]= new TH2D (nam,nam,500,0,500,500,0,500);

    sprintf(nam,"1d_ptsumpf_%i",i);
    h_1d_ptsumpf[i]= new TH1D (nam,nam,500,0,500);

    sprintf(nam,"2d_ptsumpf_%i",i);
    h_2d_ptsumpf[i]= new TH2D (nam,nam,500,0,500,500,0,500);

    sprintf(nam,"1d_ptavepf_%i",i);
    h_1d_ptavepf[i]= new TH1D (nam,nam,500,0,500);

    sprintf(nam,"2d_ptavepf_%i",i);
    h_2d_ptavepf[i]= new TH2D (nam,nam,500,0,500,500,0,500);



    sprintf(nam,"1d_npf_nott_%i",i);
    h_1d_npf_nott[i]= new TH1D (nam,nam,500,0,500);


    sprintf(nam,"2d_mt_%i",i);
    h_2d_mt[i]= new TH2D (nam,nam,100,0,500,100,0,500);

    sprintf(nam,"profile_nvtx_npf_%i",i);
    h_profile_nvtx_npf[i]= new TProfile (nam,nam,50,0,49,0,1000);
    sprintf(nam,"profile_nvtx_sumpt_%i",i);
    h_profile_nvtx_sumpt[i]= new TProfile (nam,nam,50,0,49,0,1000);

    sprintf(nam,"profile_nvtx_njet15_%i",i);
    h_profile_nvtx_njet15[i]= new TProfile (nam,nam,50,0,49,0,1000);
    sprintf(nam,"profile_nvtx_njet30_%i",i);
    h_profile_nvtx_njet30[i]= new TProfile (nam,nam,50,0,49,0,1000);

    sprintf(nam,"profile_dphi_ptsumpf_0j_%i",i);
    h_profile_dphi_ptsumpf_0j[i]= new TProfile (nam,nam,20,0,180,0,1000);
    sprintf(nam,"profile_dphi_ptaveragepf_0j_%i",i);
    h_profile_dphi_ptaveragepf_0j[i]= new TProfile (nam,nam,20,0,180,0,1000);
    sprintf(nam,"profile_dphi_npf_0j_%i",i);
    h_profile_dphi_npf_0j[i]= new TProfile (nam,nam,20,0,180,0,1000);
    sprintf(nam,"profile_nvtx_npf_0j_%i",i);
    h_profile_nvtx_npf_0j[i]= new TProfile (nam,nam,50,0,49,0,1000);
    sprintf(nam,"profile_nvtx_sumpt_0j_%i",i);
    h_profile_nvtx_sumpt_0j[i]= new TProfile (nam,nam,50,0,49,0,1000);
    sprintf(nam,"profile_dphi_ptsumpf_1j_%i",i);
    h_profile_dphi_ptsumpf_1j[i]= new TProfile (nam,nam,20,0,180,0,1000);
    sprintf(nam,"profile_dphi_ptaveragepf_1j_%i",i);
    h_profile_dphi_ptaveragepf_1j[i]= new TProfile (nam,nam,20,0,180,0,1000);
    sprintf(nam,"profile_dphi_npf_1j_%i",i);
    h_profile_dphi_npf_1j[i]= new TProfile (nam,nam,20,0,180,0,1000);
    sprintf(nam,"profile_nvtx_npf_1j_%i",i);
    h_profile_nvtx_npf_1j[i]= new TProfile (nam,nam,50,0,49,0,1000);
    sprintf(nam,"profile_nvtx_sumpt_1j_%i",i);
    h_profile_nvtx_sumpt_1j[i]= new TProfile (nam,nam,50,0,49,0,1000);
    sprintf(nam,"profile_dphi_ptsumpf_2pj_%i",i);
    h_profile_dphi_ptsumpf_2pj[i]= new TProfile (nam,nam,20,0,180,0,1000);
    sprintf(nam,"profile_dphi_ptaveragepf_2pj_%i",i);
    h_profile_dphi_ptaveragepf_2pj[i]= new TProfile (nam,nam,20,0,180,0,1000);
    sprintf(nam,"profile_dphi_npf_2pj_%i",i);
    h_profile_dphi_npf_2pj[i]= new TProfile (nam,nam,20,0,180,0,1000);
    sprintf(nam,"profile_nvtx_npf_2pj_%i",i);
    h_profile_nvtx_npf_2pj[i]= new TProfile (nam,nam,50,0,49,0,1000);
    sprintf(nam,"profile_nvtx_sumpt_2pj_%i",i);
    h_profile_nvtx_sumpt_2pj[i]= new TProfile (nam,nam,50,0,49,0,1000);

    sprintf(nam,"profile_ptttbar_npf_%i",i);
    h_profile_ptttbar_npf[i]= new TProfile (nam,nam,10,pt_tt_range,0,1000);
    sprintf(nam,"profile_ptttbar_sumpt_%i",i);
    h_profile_ptttbar_sumpt[i]= new TProfile (nam,nam,10,pt_tt_range,0,1000);
    sprintf(nam,"profile_ptttbar_avept_%i",i);
    h_profile_ptttbar_avept[i]= new TProfile (nam,nam,10,pt_tt_range,0,1000);

    sprintf(nam,"profile_ptttbar_npf_away_%i",i);
    h_profile_ptttbar_npf_away[i]= new TProfile (nam,nam,10,pt_tt_range,0,1000);
    sprintf(nam,"profile_ptttbar_sumpt_away_%i",i);
    h_profile_ptttbar_sumpt_away[i]= new TProfile (nam,nam,10,pt_tt_range,0,1000);
    sprintf(nam,"profile_ptttbar_avept_away_%i",i);
    h_profile_ptttbar_avept_away[i]= new TProfile (nam,nam,10,pt_tt_range,0,1000);

    sprintf(nam,"profile_ptttbar_npf_transverse_%i",i);
    h_profile_ptttbar_npf_transverse[i]= new TProfile (nam,nam,10,pt_tt_range,0,1000);
    sprintf(nam,"profile_ptttbar_sumpt_transverse_%i",i);
    h_profile_ptttbar_sumpt_transverse[i]= new TProfile (nam,nam,10,pt_tt_range,0,1000);
    sprintf(nam,"profile_ptttbar_avept_transverse_%i",i);
    h_profile_ptttbar_avept_transverse[i]= new TProfile (nam,nam,10,pt_tt_range,0,1000);

    sprintf(nam,"profile_ptttbar_npf_toward_%i",i);
    h_profile_ptttbar_npf_toward[i]= new TProfile (nam,nam,10,pt_tt_range,0,1000);
    sprintf(nam,"profile_ptttbar_sumpt_toward_%i",i);
    h_profile_ptttbar_sumpt_toward[i]= new TProfile (nam,nam,10,pt_tt_range,0,1000);
    sprintf(nam,"profile_ptttbar_avept_toward_%i",i);
    h_profile_ptttbar_avept_toward[i]= new TProfile (nam,nam,10,pt_tt_range,0,1000);

    sprintf(nam,"profile_ptttbar_njet30_%i",i);
    h_profile_ptttbar_njet30[i]= new TProfile (nam,nam,10,pt_tt_range,0,1000);
    sprintf(nam,"profile_ptttbar_njet15_%i",i);
    h_profile_ptttbar_njet15[i]= new TProfile (nam,nam,10,pt_tt_range,0,1000);

    sprintf(nam,"profile_ptttbar_njet30_away_%i",i);
    h_profile_ptttbar_njet30_away[i]= new TProfile (nam,nam,10,pt_tt_range,0,1000);
    sprintf(nam,"profile_ptttbar_njet15_away_%i",i);
    h_profile_ptttbar_njet15_away[i]= new TProfile (nam,nam,10,pt_tt_range,0,1000);

    sprintf(nam,"profile_ptttbar_njet30_transverse_%i",i);
    h_profile_ptttbar_njet30_transverse[i]= new TProfile (nam,nam,10,pt_tt_range,0,1000);
    sprintf(nam,"profile_ptttbar_njet15_transverse_%i",i);
    h_profile_ptttbar_njet15_transverse[i]= new TProfile (nam,nam,10,pt_tt_range,0,1000);

    sprintf(nam,"profile_ptttbar_njet30_toward_%i",i);
    h_profile_ptttbar_njet30_toward[i]= new TProfile (nam,nam,10,pt_tt_range,0,1000);
    sprintf(nam,"profile_ptttbar_njet15_toward_%i",i);
    h_profile_ptttbar_njet15_toward[i]= new TProfile (nam,nam,10,pt_tt_range,0,1000);

    sprintf(nam,"profile_deta_bb_njet_bb_%i",i);
    h_profile_deta_bb_njet_bb[i]= new TProfile (nam,nam,10,0,5,0,1000);
    sprintf(nam,"profile_deta_bb_njet_extra_%i",i);
    h_profile_deta_bb_njet_extra[i]= new TProfile (nam,nam,10,0,5,0,1000);

    sprintf(nam,"profile_mttbar_npf_%i",i);
    h_profile_mttbar_npf[i]= new TProfile (nam,nam,8,m_tt_range,0,1000);
    sprintf(nam,"profile_mttbar_sumpt_%i",i);
    h_profile_mttbar_sumpt[i]= new TProfile (nam,nam,8,m_tt_range,0,1000);
    sprintf(nam,"profile_mttbar_avept_%i",i);
    h_profile_mttbar_avept[i]= new TProfile (nam,nam,8,m_tt_range,0,1000);

    sprintf(nam,"profile_mttbar_npf_away_%i",i);
    h_profile_mttbar_npf_away[i]= new TProfile (nam,nam,8,m_tt_range,0,1000);
    sprintf(nam,"profile_mttbar_sumpt_away_%i",i);
    h_profile_mttbar_sumpt_away[i]= new TProfile (nam,nam,8,m_tt_range,0,1000);
    sprintf(nam,"profile_mttbar_avept_away_%i",i);
    h_profile_mttbar_avept_away[i]= new TProfile (nam,nam,8,m_tt_range,0,1000);

    sprintf(nam,"profile_mttbar_npf_transverse_%i",i);
    h_profile_mttbar_npf_transverse[i]= new TProfile (nam,nam,8,m_tt_range,0,1000);
    sprintf(nam,"profile_mttbar_sumpt_transverse_%i",i);
    h_profile_mttbar_sumpt_transverse[i]= new TProfile (nam,nam,8,m_tt_range,0,1000);
    sprintf(nam,"profile_mttbar_avept_transverse_%i",i);
    h_profile_mttbar_avept_transverse[i]= new TProfile (nam,nam,8,m_tt_range,0,1000);

    sprintf(nam,"profile_mttbar_npf_toward_%i",i);
    h_profile_mttbar_npf_toward[i]= new TProfile (nam,nam,8,m_tt_range,0,1000);
    sprintf(nam,"profile_mttbar_sumpt_toward_%i",i);
    h_profile_mttbar_sumpt_toward[i]= new TProfile (nam,nam,8,m_tt_range,0,1000);
    sprintf(nam,"profile_mttbar_avept_toward_%i",i);
    h_profile_mttbar_avept_toward[i]= new TProfile (nam,nam,8,m_tt_range,0,1000);

    sprintf(nam,"profile_ytt_npf_%i",i);
    h_profile_ytt_npf[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ytt_sumpt_%i",i);
    h_profile_ytt_sumpt[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ytt_avept_%i",i);
    h_profile_ytt_avept[i]= new TProfile (nam,nam,10,0,2.5,0,1000);

    sprintf(nam,"profile_ytt_npf_away_%i",i);
    h_profile_ytt_npf_away[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ytt_sumpt_away_%i",i);
    h_profile_ytt_sumpt_away[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ytt_avept_away_%i",i);
    h_profile_ytt_avept_away[i]= new TProfile (nam,nam,10,0,2.5,0,1000);

    sprintf(nam,"profile_ytt_npf_transverse_%i",i);
    h_profile_ytt_npf_transverse[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ytt_sumpt_transverse_%i",i);
    h_profile_ytt_sumpt_transverse[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ytt_avept_transverse_%i",i);
    h_profile_ytt_avept_transverse[i]= new TProfile (nam,nam,10,0,2.5,0,1000);

    sprintf(nam,"profile_ytt_npf_toward_%i",i);
    h_profile_ytt_npf_toward[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ytt_sumpt_toward_%i",i);
    h_profile_ytt_sumpt_toward[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ytt_avept_toward_%i",i);
    h_profile_ytt_avept_toward[i]= new TProfile (nam,nam,10,0,2.5,0,1000);

    sprintf(nam,"profile_yttj_npf_%i",i);
    h_profile_yttj_npf[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_yttj_sumpt_%i",i);
    h_profile_yttj_sumpt[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_yttj_avept_%i",i);
    h_profile_yttj_avept[i]= new TProfile (nam,nam,10,0,2.5,0,1000);

    sprintf(nam,"profile_yttj_npf_away_%i",i);
    h_profile_yttj_npf_away[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_yttj_sumpt_away_%i",i);
    h_profile_yttj_sumpt_away[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_yttj_avept_away_%i",i);
    h_profile_yttj_avept_away[i]= new TProfile (nam,nam,10,0,2.5,0,1000);

    sprintf(nam,"profile_yttj_npf_transverse_%i",i);
    h_profile_yttj_npf_transverse[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_yttj_sumpt_transverse_%i",i);
    h_profile_yttj_sumpt_transverse[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_yttj_avept_transverse_%i",i);
    h_profile_yttj_avept_transverse[i]= new TProfile (nam,nam,10,0,2.5,0,1000);

    sprintf(nam,"profile_yttj_npf_toward_%i",i);
    h_profile_yttj_npf_toward[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_yttj_sumpt_toward_%i",i);
    h_profile_yttj_sumpt_toward[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_yttj_avept_toward_%i",i);
    h_profile_yttj_avept_toward[i]= new TProfile (nam,nam,10,0,2.5,0,1000);






    sprintf(nam,"profile_mtop_npf_%i",i);
    h_profile_mtop_npf[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mtop_sumpt_%i",i);
    h_profile_mtop_sumpt[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mtop_avept_%i",i);
    h_profile_mtop_avept[i]= new TProfile (nam,nam,10,m_t_range,0,1000);

    sprintf(nam,"profile_mtop_npf_away_%i",i);
    h_profile_mtop_npf_away[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mtop_sumpt_away_%i",i);
    h_profile_mtop_sumpt_away[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mtop_avept_away_%i",i);
    h_profile_mtop_avept_away[i]= new TProfile (nam,nam,10,m_t_range,0,1000);

    sprintf(nam,"profile_mtop_npf_transverse_%i",i);
    h_profile_mtop_npf_transverse[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mtop_sumpt_transverse_%i",i);
    h_profile_mtop_sumpt_transverse[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mtop_avept_transverse_%i",i);
    h_profile_mtop_avept_transverse[i]= new TProfile (nam,nam,10,m_t_range,0,1000);

    sprintf(nam,"profile_mtop_npf_toward_%i",i);
    h_profile_mtop_npf_toward[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mtop_sumpt_toward_%i",i);
    h_profile_mtop_sumpt_toward[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mtop_avept_toward_%i",i);
    h_profile_mtop_avept_toward[i]= new TProfile (nam,nam,10,m_t_range,0,1000);

    sprintf(nam,"profile_matop_npf_%i",i);
    h_profile_matop_npf[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_matop_sumpt_%i",i);
    h_profile_matop_sumpt[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_matop_avept_%i",i);
    h_profile_matop_avept[i]= new TProfile (nam,nam,10,m_t_range,0,1000);

    sprintf(nam,"profile_matop_npf_away_%i",i);
    h_profile_matop_npf_away[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_matop_sumpt_away_%i",i);
    h_profile_matop_sumpt_away[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_matop_avept_away_%i",i);
    h_profile_matop_avept_away[i]= new TProfile (nam,nam,10,m_t_range,0,1000);

    sprintf(nam,"profile_matop_npf_transverse_%i",i);
    h_profile_matop_npf_transverse[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_matop_sumpt_transverse_%i",i);
    h_profile_matop_sumpt_transverse[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_matop_avept_transverse_%i",i);
    h_profile_matop_avept_transverse[i]= new TProfile (nam,nam,10,m_t_range,0,1000);

    sprintf(nam,"profile_matop_npf_toward_%i",i);
    h_profile_matop_npf_toward[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_matop_sumpt_toward_%i",i);
    h_profile_matop_sumpt_toward[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_matop_avept_toward_%i",i);
    h_profile_matop_avept_toward[i]= new TProfile (nam,nam,10,m_t_range,0,1000);

    sprintf(nam,"profile_pttop_npf_%i",i);
    h_profile_pttop_npf[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_pttop_sumpt_%i",i);
    h_profile_pttop_sumpt[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_pttop_avept_%i",i);
    h_profile_pttop_avept[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);

    sprintf(nam,"profile_pttop_npf_away_%i",i);
    h_profile_pttop_npf_away[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_pttop_sumpt_away_%i",i);
    h_profile_pttop_sumpt_away[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_pttop_avept_away_%i",i);
    h_profile_pttop_avept_away[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);

    sprintf(nam,"profile_pttop_npf_transverse_%i",i);
    h_profile_pttop_npf_transverse[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_pttop_sumpt_transverse_%i",i);
    h_profile_pttop_sumpt_transverse[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_pttop_avept_transverse_%i",i);
    h_profile_pttop_avept_transverse[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);

    sprintf(nam,"profile_pttop_npf_toward_%i",i);
    h_profile_pttop_npf_toward[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_pttop_sumpt_toward_%i",i);
    h_profile_pttop_sumpt_toward[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_pttop_avept_toward_%i",i);
    h_profile_pttop_avept_toward[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);

    sprintf(nam,"profile_ptatop_npf_%i",i);
    h_profile_ptatop_npf[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_ptatop_sumpt_%i",i);
    h_profile_ptatop_sumpt[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_ptatop_avept_%i",i);
    h_profile_ptatop_avept[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);

    sprintf(nam,"profile_ptatop_npf_away_%i",i);
    h_profile_ptatop_npf_away[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_ptatop_sumpt_away_%i",i);
    h_profile_ptatop_sumpt_away[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_ptatop_avept_away_%i",i);
    h_profile_ptatop_avept_away[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);

    sprintf(nam,"profile_ptatop_npf_transverse_%i",i);
    h_profile_ptatop_npf_transverse[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_ptatop_sumpt_transverse_%i",i);
    h_profile_ptatop_sumpt_transverse[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_ptatop_avept_transverse_%i",i);
    h_profile_ptatop_avept_transverse[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);

    sprintf(nam,"profile_ptatop_npf_toward_%i",i);
    h_profile_ptatop_npf_toward[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_ptatop_sumpt_toward_%i",i);
    h_profile_ptatop_sumpt_toward[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_ptatop_avept_toward_%i",i);
    h_profile_ptatop_avept_toward[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);



    sprintf(nam,"profile_ytop_npf_%i",i);
    h_profile_ytop_npf[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ytop_sumpt_%i",i);
    h_profile_ytop_sumpt[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ytop_avept_%i",i);
    h_profile_ytop_avept[i]= new TProfile (nam,nam,10,0,2.5,0,1000);

    sprintf(nam,"profile_ytop_npf_away_%i",i);
    h_profile_ytop_npf_away[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ytop_sumpt_away_%i",i);
    h_profile_ytop_sumpt_away[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ytop_avept_away_%i",i);
    h_profile_ytop_avept_away[i]= new TProfile (nam,nam,10,0,2.5,0,1000);

    sprintf(nam,"profile_ytop_npf_transverse_%i",i);
    h_profile_ytop_npf_transverse[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ytop_sumpt_transverse_%i",i);
    h_profile_ytop_sumpt_transverse[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ytop_avept_transverse_%i",i);
    h_profile_ytop_avept_transverse[i]= new TProfile (nam,nam,10,0,2.5,0,1000);

    sprintf(nam,"profile_ytop_npf_toward_%i",i);
    h_profile_ytop_npf_toward[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ytop_sumpt_toward_%i",i);
    h_profile_ytop_sumpt_toward[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ytop_avept_toward_%i",i);
    h_profile_ytop_avept_toward[i]= new TProfile (nam,nam,10,0,2.5,0,1000);

    sprintf(nam,"profile_yatop_npf_%i",i);
    h_profile_yatop_npf[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_yatop_sumpt_%i",i);
    h_profile_yatop_sumpt[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_yatop_avept_%i",i);
    h_profile_yatop_avept[i]= new TProfile (nam,nam,10,0,2.5,0,1000);

    sprintf(nam,"profile_yatop_npf_away_%i",i);
    h_profile_yatop_npf_away[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_yatop_sumpt_away_%i",i);
    h_profile_yatop_sumpt_away[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_yatop_avept_away_%i",i);
    h_profile_yatop_avept_away[i]= new TProfile (nam,nam,10,0,2.5,0,1000);

    sprintf(nam,"profile_yatop_npf_transverse_%i",i);
    h_profile_yatop_npf_transverse[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_yatop_sumpt_transverse_%i",i);
    h_profile_yatop_sumpt_transverse[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_yatop_avept_transverse_%i",i);
    h_profile_yatop_avept_transverse[i]= new TProfile (nam,nam,10,0,2.5,0,1000);

    sprintf(nam,"profile_yatop_npf_toward_%i",i);
    h_profile_yatop_npf_toward[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_yatop_sumpt_toward_%i",i);
    h_profile_yatop_sumpt_toward[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_yatop_avept_toward_%i",i);
    h_profile_yatop_avept_toward[i]= new TProfile (nam,nam,10,0,2.5,0,1000);




    sprintf(nam,"profile_mthad_npf_%i",i);
    h_profile_mthad_npf[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mthad_sumpt_%i",i);
    h_profile_mthad_sumpt[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mthad_avept_%i",i);
    h_profile_mthad_avept[i]= new TProfile (nam,nam,10,m_t_range,0,1000);

    sprintf(nam,"profile_mthad_npf_away_%i",i);
    h_profile_mthad_npf_away[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mthad_sumpt_away_%i",i);
    h_profile_mthad_sumpt_away[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mthad_avept_away_%i",i);
    h_profile_mthad_avept_away[i]= new TProfile (nam,nam,10,m_t_range,0,1000);

    sprintf(nam,"profile_mthad_npf_transverse_%i",i);
    h_profile_mthad_npf_transverse[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mthad_sumpt_transverse_%i",i);
    h_profile_mthad_sumpt_transverse[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mthad_avept_transverse_%i",i);
    h_profile_mthad_avept_transverse[i]= new TProfile (nam,nam,10,m_t_range,0,1000);

    sprintf(nam,"profile_mthad_npf_toward_%i",i);
    h_profile_mthad_npf_toward[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mthad_sumpt_toward_%i",i);
    h_profile_mthad_sumpt_toward[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mthad_avept_toward_%i",i);
    h_profile_mthad_avept_toward[i]= new TProfile (nam,nam,10,m_t_range,0,1000);

    sprintf(nam,"profile_mtlep_npf_%i",i);
    h_profile_mtlep_npf[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mtlep_sumpt_%i",i);
    h_profile_mtlep_sumpt[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mtlep_avept_%i",i);
    h_profile_mtlep_avept[i]= new TProfile (nam,nam,10,m_t_range,0,1000);

    sprintf(nam,"profile_mtlep_npf_away_%i",i);
    h_profile_mtlep_npf_away[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mtlep_sumpt_away_%i",i);
    h_profile_mtlep_sumpt_away[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mtlep_avept_away_%i",i);
    h_profile_mtlep_avept_away[i]= new TProfile (nam,nam,10,m_t_range,0,1000);

    sprintf(nam,"profile_mtlep_npf_transverse_%i",i);
    h_profile_mtlep_npf_transverse[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mtlep_sumpt_transverse_%i",i);
    h_profile_mtlep_sumpt_transverse[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mtlep_avept_transverse_%i",i);
    h_profile_mtlep_avept_transverse[i]= new TProfile (nam,nam,10,m_t_range,0,1000);

    sprintf(nam,"profile_mtlep_npf_toward_%i",i);
    h_profile_mtlep_npf_toward[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mtlep_sumpt_toward_%i",i);
    h_profile_mtlep_sumpt_toward[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mtlep_avept_toward_%i",i);
    h_profile_mtlep_avept_toward[i]= new TProfile (nam,nam,10,m_t_range,0,1000);

    sprintf(nam,"profile_ptthad_npf_%i",i);
    h_profile_ptthad_npf[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_ptthad_sumpt_%i",i);
    h_profile_ptthad_sumpt[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_ptthad_avept_%i",i);
    h_profile_ptthad_avept[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);

    sprintf(nam,"profile_ptthad_npf_away_%i",i);
    h_profile_ptthad_npf_away[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_ptthad_sumpt_away_%i",i);
    h_profile_ptthad_sumpt_away[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_ptthad_avept_away_%i",i);
    h_profile_ptthad_avept_away[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);

    sprintf(nam,"profile_ptthad_npf_transverse_%i",i);
    h_profile_ptthad_npf_transverse[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_ptthad_sumpt_transverse_%i",i);
    h_profile_ptthad_sumpt_transverse[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_ptthad_avept_transverse_%i",i);
    h_profile_ptthad_avept_transverse[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);

    sprintf(nam,"profile_ptthad_npf_toward_%i",i);
    h_profile_ptthad_npf_toward[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_ptthad_sumpt_toward_%i",i);
    h_profile_ptthad_sumpt_toward[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_ptthad_avept_toward_%i",i);
    h_profile_ptthad_avept_toward[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);

    sprintf(nam,"profile_pttlep_npf_%i",i);
    h_profile_pttlep_npf[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_pttlep_sumpt_%i",i);
    h_profile_pttlep_sumpt[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_pttlep_avept_%i",i);
    h_profile_pttlep_avept[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);

    sprintf(nam,"profile_pttlep_npf_away_%i",i);
    h_profile_pttlep_npf_away[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_pttlep_sumpt_away_%i",i);
    h_profile_pttlep_sumpt_away[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_pttlep_avept_away_%i",i);
    h_profile_pttlep_avept_away[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);

    sprintf(nam,"profile_pttlep_npf_transverse_%i",i);
    h_profile_pttlep_npf_transverse[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_pttlep_sumpt_transverse_%i",i);
    h_profile_pttlep_sumpt_transverse[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_pttlep_avept_transverse_%i",i);
    h_profile_pttlep_avept_transverse[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);

    sprintf(nam,"profile_pttlep_npf_toward_%i",i);
    h_profile_pttlep_npf_toward[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_pttlep_sumpt_toward_%i",i);
    h_profile_pttlep_sumpt_toward[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_pttlep_avept_toward_%i",i);
    h_profile_pttlep_avept_toward[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);



    sprintf(nam,"profile_ythad_npf_%i",i);
    h_profile_ythad_npf[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ythad_sumpt_%i",i);
    h_profile_ythad_sumpt[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ythad_avept_%i",i);
    h_profile_ythad_avept[i]= new TProfile (nam,nam,10,0,2.5,0,1000);

    sprintf(nam,"profile_ythad_npf_away_%i",i);
    h_profile_ythad_npf_away[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ythad_sumpt_away_%i",i);
    h_profile_ythad_sumpt_away[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ythad_avept_away_%i",i);
    h_profile_ythad_avept_away[i]= new TProfile (nam,nam,10,0,2.5,0,1000);

    sprintf(nam,"profile_ythad_npf_transverse_%i",i);
    h_profile_ythad_npf_transverse[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ythad_sumpt_transverse_%i",i);
    h_profile_ythad_sumpt_transverse[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ythad_avept_transverse_%i",i);
    h_profile_ythad_avept_transverse[i]= new TProfile (nam,nam,10,0,2.5,0,1000);

    sprintf(nam,"profile_ythad_npf_toward_%i",i);
    h_profile_ythad_npf_toward[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ythad_sumpt_toward_%i",i);
    h_profile_ythad_sumpt_toward[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ythad_avept_toward_%i",i);
    h_profile_ythad_avept_toward[i]= new TProfile (nam,nam,10,0,2.5,0,1000);

    sprintf(nam,"profile_ytlep_npf_%i",i);
    h_profile_ytlep_npf[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ytlep_sumpt_%i",i);
    h_profile_ytlep_sumpt[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ytlep_avept_%i",i);
    h_profile_ytlep_avept[i]= new TProfile (nam,nam,10,0,2.5,0,1000);

    sprintf(nam,"profile_ytlep_npf_away_%i",i);
    h_profile_ytlep_npf_away[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ytlep_sumpt_away_%i",i);
    h_profile_ytlep_sumpt_away[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ytlep_avept_away_%i",i);
    h_profile_ytlep_avept_away[i]= new TProfile (nam,nam,10,0,2.5,0,1000);

    sprintf(nam,"profile_ytlep_npf_transverse_%i",i);
    h_profile_ytlep_npf_transverse[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ytlep_sumpt_transverse_%i",i);
    h_profile_ytlep_sumpt_transverse[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ytlep_avept_transverse_%i",i);
    h_profile_ytlep_avept_transverse[i]= new TProfile (nam,nam,10,0,2.5,0,1000);

    sprintf(nam,"profile_ytlep_npf_toward_%i",i);
    h_profile_ytlep_npf_toward[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ytlep_sumpt_toward_%i",i);
    h_profile_ytlep_sumpt_toward[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_ytlep_avept_toward_%i",i);
    h_profile_ytlep_avept_toward[i]= new TProfile (nam,nam,10,0,2.5,0,1000);




    sprintf(nam,"profile_mt_npf_%i",i);
    h_profile_mt_npf[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mt_sumpt_%i",i);
    h_profile_mt_sumpt[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mt_avept_%i",i);
    h_profile_mt_avept[i]= new TProfile (nam,nam,10,m_t_range,0,1000);

    sprintf(nam,"profile_mt_npf_away_%i",i);
    h_profile_mt_npf_away[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mt_sumpt_away_%i",i);
    h_profile_mt_sumpt_away[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mt_avept_away_%i",i);
    h_profile_mt_avept_away[i]= new TProfile (nam,nam,10,m_t_range,0,1000);

    sprintf(nam,"profile_mt_npf_transverse_%i",i);
    h_profile_mt_npf_transverse[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mt_sumpt_transverse_%i",i);
    h_profile_mt_sumpt_transverse[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mt_avept_transverse_%i",i);
    h_profile_mt_avept_transverse[i]= new TProfile (nam,nam,10,m_t_range,0,1000);

    sprintf(nam,"profile_mt_npf_toward_%i",i);
    h_profile_mt_npf_toward[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mt_sumpt_toward_%i",i);
    h_profile_mt_sumpt_toward[i]= new TProfile (nam,nam,10,m_t_range,0,1000);
    sprintf(nam,"profile_mt_avept_toward_%i",i);
    h_profile_mt_avept_toward[i]= new TProfile (nam,nam,10,m_t_range,0,1000);

    sprintf(nam,"profile_ptt_npf_%i",i);
    h_profile_ptt_npf[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_ptt_sumpt_%i",i);
    h_profile_ptt_sumpt[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_ptt_avept_%i",i);
    h_profile_ptt_avept[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);

    sprintf(nam,"profile_ptt_npf_away_%i",i);
    h_profile_ptt_npf_away[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_ptt_sumpt_away_%i",i);
    h_profile_ptt_sumpt_away[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_ptt_avept_away_%i",i);
    h_profile_ptt_avept_away[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);

    sprintf(nam,"profile_ptt_npf_transverse_%i",i);
    h_profile_ptt_npf_transverse[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_ptt_sumpt_transverse_%i",i);
    h_profile_ptt_sumpt_transverse[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_ptt_avept_transverse_%i",i);
    h_profile_ptt_avept_transverse[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);

    sprintf(nam,"profile_ptt_npf_toward_%i",i);
    h_profile_ptt_npf_toward[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_ptt_sumpt_toward_%i",i);
    h_profile_ptt_sumpt_toward[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);
    sprintf(nam,"profile_ptt_avept_toward_%i",i);
    h_profile_ptt_avept_toward[i]= new TProfile (nam,nam,8,pt_t_range,0,1000);


    sprintf(nam,"profile_yt_npf_%i",i);
    h_profile_yt_npf[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_yt_sumpt_%i",i);
    h_profile_yt_sumpt[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_yt_avept_%i",i);
    h_profile_yt_avept[i]= new TProfile (nam,nam,10,0,2.5,0,1000);

    sprintf(nam,"profile_yt_npf_away_%i",i);
    h_profile_yt_npf_away[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_yt_sumpt_away_%i",i);
    h_profile_yt_sumpt_away[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_yt_avept_away_%i",i);
    h_profile_yt_avept_away[i]= new TProfile (nam,nam,10,0,2.5,0,1000);

    sprintf(nam,"profile_yt_npf_transverse_%i",i);
    h_profile_yt_npf_transverse[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_yt_sumpt_transverse_%i",i);
    h_profile_yt_sumpt_transverse[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_yt_avept_transverse_%i",i);
    h_profile_yt_avept_transverse[i]= new TProfile (nam,nam,10,0,2.5,0,1000);

    sprintf(nam,"profile_yt_npf_toward_%i",i);
    h_profile_yt_npf_toward[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_yt_sumpt_toward_%i",i);
    h_profile_yt_sumpt_toward[i]= new TProfile (nam,nam,10,0,2.5,0,1000);
    sprintf(nam,"profile_yt_avept_toward_%i",i);
    h_profile_yt_avept_toward[i]= new TProfile (nam,nam,10,0,2.5,0,1000);




    sprintf(nam,"nvtx_%i",i);
    h_nvtx[i]= new TH1D (nam,nam,50,0,49);
    sprintf(nam,"pf_dxy_%i",i);
    h_pf_dxy[i]= new TH1D (nam,nam,1000,0,2);
    sprintf(nam,"pf_dz_%i",i);
    h_pf_dz[i]= new TH1D (nam,nam,1000,0,25);
    sprintf(nam,"pf_sigmadxy_%i",i);
    h_pf_sigmadxy[i]= new TH1D (nam,nam,1000,0,25);
    sprintf(nam,"pf_sigmadz_%i",i);
    h_pf_sigmadz[i]= new TH1D (nam,nam,1000,0,25);
    sprintf(nam,"pf_pt_%i",i);
    h_pf_pt[i]= new TH1D (nam,nam,20000,0,2000);
    sprintf(nam,"csv_%i",i);
    h_csv[i]= new TH1D(nam,nam,1000,-1,1);
    sprintf(nam,"csvmax_%i",i);
    h_csvmax[i]= new TH1D(nam,nam,1000,-1,1);
    sprintf(nam,"csvmax2_%i",i);
    h_csvmax2[i]= new TH1D(nam,nam,1000,-1,1);
    sprintf(nam,"npf_inclusive_%i",i);
    h_npf_inclusive[i]= new TH1D (nam,nam,140,0,140);
    sprintf(nam,"npf_toward_%i",i);
    h_npf_toward[i]= new TH1D (nam,nam,140,0,140);
    sprintf(nam,"npf_transverse_%i",i);
    h_npf_transverse[i]= new TH1D (nam,nam,140,0,140);
    sprintf(nam,"npf_away_%i",i);
    h_npf_away[i]= new TH1D (nam,nam,140,0,140);

    sprintf(nam,"ptsumpf_inclusive_%i",i);
    h_ptsumpf_inclusive[i]= new TH1D (nam,nam,100,0,500);
    sprintf(nam,"ptsumpf_toward_%i",i);
    h_ptsumpf_toward[i]= new TH1D (nam,nam,100,0,500);
    sprintf(nam,"ptsumpf_transverse_%i",i);
    h_ptsumpf_transverse[i]= new TH1D (nam,nam,100,0,500);
    sprintf(nam,"ptsumpf_away_%i",i);
    h_ptsumpf_away[i]= new TH1D (nam,nam,100,0,500);

    sprintf(nam,"ptavepf_inclusive_%i",i);
    h_ptavepf_inclusive[i]= new TH1D (nam,nam,50,0,25);
    sprintf(nam,"ptavepf_toward_%i",i);
    h_ptavepf_toward[i]= new TH1D (nam,nam,50,0,25);
    sprintf(nam,"ptavepf_transverse_%i",i);
    h_ptavepf_transverse[i]= new TH1D (nam,nam,50,0,25);
    sprintf(nam,"ptavepf_away_%i",i);
    h_ptavepf_away[i]= new TH1D (nam,nam,50,0,25);

    sprintf(nam,"puweight_%i",i);
    h_puweight[i]= new TH1D(nam,nam,10000,0,1000);
    sprintf(nam,"puweight_weighted_%i",i);
    h_puweight_weighted[i]= new TH1D(nam,nam,10000,0,1000);

    sprintf(nam,"puweight_meas_%i",i);
    h_puweight_meas[i]= new TH1D(nam,nam,10000,0,1000);
    sprintf(nam,"puweight_weighted_meas_%i",i);
    h_puweight_weighted_meas[i]= new TH1D(nam,nam,10000,0,1000);
    sprintf(nam,"MTW_%i",i);
    h_MTW[i]= new TH1D (nam,nam,100,0,1000);
    sprintf(nam,"m_thad_%i",i);
    h_m_thad[i]= new TH1D (nam,nam,10,m_t_range);
    sprintf(nam,"m_thad_fixbin_%i",i);
    h_m_thad_fixbin[i]= new TH1D (nam,nam,200,0,1000);
    sprintf(nam,"m_tlep_%i",i);
    h_m_tlep[i]= new TH1D (nam,nam,10,m_t_range);
    sprintf(nam,"m_tlep_fixbin_%i",i);
    h_m_tlep_fixbin[i]= new TH1D (nam,nam,200,0,1000);

    sprintf(nam,"m_top_%i",i);
    h_m_top[i]= new TH1D (nam,nam,10,m_t_range);
    sprintf(nam,"m_atop_%i",i);
    h_m_atop[i]= new TH1D (nam,nam,10,m_t_range);

    sprintf(nam,"pt_top_%i",i);
    h_pt_top[i]= new TH1D (nam,nam,8,pt_t_range);
    sprintf(nam,"pt_atop_%i",i);
    h_pt_atop[i]= new TH1D (nam,nam,8,pt_t_range);

    sprintf(nam,"m_top_fixbin_%i",i);
    h_m_top_fixbin[i]= new TH1D (nam,nam,200,0,1000);
    sprintf(nam,"m_atop_fixbin_%i",i);
    h_m_atop_fixbin[i]= new TH1D (nam,nam,200,0,1000);

    sprintf(nam,"pt_top_fixbin_%i",i);
    h_pt_top_fixbin[i]= new TH1D (nam,nam,200,0,1000);
    sprintf(nam,"pt_atop_fixbin_%i",i);
    h_pt_atop_fixbin[i]= new TH1D (nam,nam,200,0,1000);


    sprintf(nam,"y_top_%i",i);
    h_y_top[i]= new TH1D (nam,nam,100,-5.,5.);
    sprintf(nam,"y_atop_%i",i);
    h_y_atop[i]= new TH1D (nam,nam,100,-5.,5.);

    sprintf(nam,"rec_ttjY_%i",i);
    h_rec_ttjY[i]= new TH1D (nam,nam,50,-5,5);

    sprintf(nam,"m_ttbar_%i",i);
    h_m_ttbar[i]= new TH1D (nam,nam,8,m_tt_range);
    sprintf(nam,"m_ttbar_fixbin_%i",i);
    h_m_ttbar_fixbin[i]= new TH1D (nam,nam,400,0,2000);
    sprintf(nam,"y_ttbar_%i",i);
    h_y_ttbar[i]= new TH1D (nam,nam,100,-5.,5.);

    sprintf(nam,"pt_thad_%i",i);
    h_pt_thad[i]= new TH1D (nam,nam,8,pt_t_range);
    sprintf(nam,"pt_thad_fixbin_%i",i);
    h_pt_thad_fixbin[i]= new TH1D (nam,nam,200,0,1000);
    sprintf(nam,"pt_tlep_%i",i);
    h_pt_tlep[i]= new TH1D (nam,nam,8,pt_t_range);
    sprintf(nam,"pt_tlep_fixbin_%i",i);
    h_pt_tlep_fixbin[i]= new TH1D (nam,nam,200,0,1000);
    sprintf(nam,"y_thad_%i",i);
    h_y_thad[i]= new TH1D (nam,nam,100,-5.,5.);
    sprintf(nam,"y_tlep_%i",i);
    h_y_tlep[i]= new TH1D (nam,nam,100,-5.,5.);
    sprintf(nam,"m_t_%i",i);
    h_m_t[i]= new TH1D (nam,nam,10,m_t_range);
    sprintf(nam,"m_t_fixbin_%i",i);
    h_m_t_fixbin[i]= new TH1D (nam,nam,200,0,1000);
    sprintf(nam,"pt_t_%i",i);
    h_pt_t[i]= new TH1D (nam,nam,8,pt_t_range);
    sprintf(nam,"pt_t_fixbin_%i",i);
    h_pt_t_fixbin[i]= new TH1D (nam,nam,200,0,1000);
    sprintf(nam,"y_t_%i",i);
    h_y_t[i]= new TH1D (nam,nam,100,-5.,5.);
  }

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

  //cout<<"bbbbbbbbbb"<<endl;

  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    // cout<<"cccccccccc"<<endl;
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if(jentry%10000==0)cout<<name<<" << "<<jentry<<"/"<<nentries<<endl;


    int gn_pf_nott=0;
    int n_pf_nott=0;
    int n_pf_nott_1=0;
    int n_pf_nott_2=0;

      for(unsigned int gp_ind=0;gp_ind<Packed01Id->size();gp_ind++){    
	if(Packed01Pt->at(gp_ind)<0.5 || fabs(Packed01Eta->at(gp_ind))>2.1 ||Packed01Charge->at(gp_ind)==0)continue;
      gn_pf_nott++;
    }
          double ww=1.;
          if (PU_npT>0)ww=puWeight.weight(int(PU_npT));
    for(unsigned int pfind =0; pfind<patPfCandPt->size();pfind++){
      if(patPfCandPt->at(pfind)<0.5 || fabs(patPfCandEta->at(pfind))>2.1||patPfCandCharge->at(pfind)==0 )continue;
      n_pf_nott++;
//||patPfCandFromPv->at(pfind)<2||fabs(patPfCandDxy->at(pfind))>1 ||fabs(patPfCandDz->at(pfind))>3 ||patPfCandEta->at(pfind)>2.1
 //     if(patPfCandFromPv->at(pfind)>=2)n_pf_nott_1++;
 //     if(patPfCandFromPv->at(pfind)>=2&&fabs(patPfCandDxy->at(pfind))<=1 &&fabs(patPfCandDz->at(pfind))<=3 )n_pf_nott_2++;

      if(patPfpvAssociationQuality->at(pfind)>4 && patPfCandVertexRef->at(pfind)==0){
        n_pf_nott_1++;
       // if(patPfCandDxyerr->at(pfind)==0||patPfCandDzerr->at(pfind)==0)cout<<patPfCandDxy->at(pfind)/patPfCandDxyerr->at(pfind)<<"  "<<patPfCandDz->at(pfind)/patPfCandDzerr->at(pfind)<<endl;
       // if(patPfCandDxyerr->at(pfind)==0)cout<<patPfCandDxy->at(pfind)<<endl;
       // if(patPfCandDzerr->at(pfind)==0)cout<<patPfCandDz->at(pfind)<<endl;
        h_sig_DXY->Fill(patPfCandDxy->at(pfind)/patPfCandDxyerr->at(pfind),ww);
        h_sig_DZ->Fill(patPfCandDz->at(pfind)/patPfCandDzerr->at(pfind),ww);
        h_sig_DXY_DZ->Fill(patPfCandDxy->at(pfind)/patPfCandDxyerr->at(pfind),patPfCandDz->at(pfind)/patPfCandDzerr->at(pfind),ww);
        h_track_high_purity->Fill(patPfCandTrackHighPurity->at(pfind),ww);
        if(patPfCandDxyerr->at(pfind)==0||patPfCandDzerr->at(pfind)==0){
          h_zeroerr_DXY->Fill(patPfCandDxy->at(pfind),ww);
          h_zeroerr_DZ->Fill(patPfCandDz->at(pfind),ww);
          h_zeroerr_DXY_DZ->Fill(patPfCandDxy->at(pfind),patPfCandDz->at(pfind),ww);
        }
        if(!(patPfCandDxyerr->at(pfind)==0||patPfCandDzerr->at(pfind)==0)){
          h_nzeroerr_DXY->Fill(patPfCandDxy->at(pfind),ww);
          h_nzeroerr_DZ->Fill(patPfCandDz->at(pfind),ww);
          h_nzeroerr_DXY_DZ->Fill(patPfCandDxy->at(pfind),patPfCandDz->at(pfind),ww);
        }

      }
      if(patPfpvAssociationQuality->at(pfind)>4 && patPfCandVertexRef->at(pfind)==0 &&patPfCandTrackHighPurity->at(pfind)!=0 /*&&
        ((patPfCandDxyerr->at(pfind)==0&& patPfCandDzerr->at(pfind)==0) ||(fabs(patPfCandDxy->at(pfind)/patPfCandDxyerr->at(pfind))<15. &&fabs(patPfCandDz->at(pfind)/patPfCandDzerr->at(pfind))<15.))*/ ){
        n_pf_nott_2++;
      }
    }


	  h_1d_npf_nott[0]->Fill(gn_pf_nott);
      //    cout<<puWeight.weight(int(PU_npT))<<endl;


	  h_1d_npf_nott[1]->Fill(n_pf_nott,ww);

	  h_1d_npf_nott[2]->Fill(n_pf_nott_1,puWeight.weight(int(PU_npT)));
	  h_1d_npf_nott[3]->Fill(n_pf_nott_2,puWeight.weight(int(PU_npT)));

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
    vector<TLorentzVector> vector_vector_gp;
  //  vector<TLorentzVector> st01_mu_vector;
  //  vector<int> st01_mu_charge;
  //  vector<TLorentzVector> st01_nu_vector;
    TLorentzVector st01_mu_vector;
    TLorentzVector st01_nu_vector;
    
    vector<TLorentzVector> Gjet_vector;
    vector<TLorentzVector> Gjet_vector_1530;

    vector<vector<TLorentzVector>> Gjetconst_vector;
    vector<vector<TLorentzVector>> GBjetconst_vector;
    vector<TLorentzVector> GBjet_vector;
    TLorentzVector gtlep_vector;
    TLorentzVector gthad_vector;

    TLorentzVector gtop_vector;
    TLorentzVector gatop_vector;

    TLorentzVector gttbar_vector;
    TLorentzVector gttj_vector;
    double getab1;
    double getab2;
    double getamin=0;
    double gdeltaetabb;
    int gnjet_bb=0;
    int gnjet_transverse=0;
    int gnjet_away=0;
    int gnjet_toward=0;

    int gnjet_transverse15=0;
    int gnjet_away15=0;
    int gnjet_toward15=0;

    unsigned int lind=9999,nind=9999,j1ind=9999,j2ind=9999;
    unsigned int gextra_jet_index=99/*,gextra_jet_index_1530=99*/;
    vector<unsigned int> ga_min;
    int gn_pf=0;
    int gn_pf_dphi[20];
    double gptsum_pf_dphi[20];

    /*         int n_pf_ttpt[10];
	       double ptsum_pf_ttpt[10];

	       int n_pf_ttpt_away[10];
	       double ptsum_pf_ttpt_away[10];

	       int n_pf_ttpt_transverse[10];
	       double ptsum_pf_ttpt_transverse[10];

	       int n_pf_ttpt_toward[10];
	       double ptsum_pf_ttpt_toward[10];*/

    double gptsum_pf=0;
    double gptsum_pf_away=0;
    double gptsum_pf_transverse=0;
    double gptsum_pf_toward=0;
    int gn_pf_away=0;
    int gn_pf_transverse=0;
    int gn_pf_toward=0;
    for(int i =0;i<20;i++){
      gn_pf_dphi[i]=0;
      gptsum_pf_dphi[i]=0;
    } 

    double w=1;
    if(mcWeights_->size()>0)w=mcWeights_->at(0);

    //    vector<TLorentzVector> Gpart_vector;

    //cout<<"1111111111"<<endl;
/*    for(unsigned int st1_ind=0; st1_ind<Dr01LepPt->size();st1_ind++){
      // cout<<Bare01LepId->at(st1_ind)<<"  "<<Bare01LepStatus->at(st1_ind)<<endl;
      //      if(fabs(Dr01LepId->at(st1_ind))==13)st1mu++;
      //      if(fabs(Dr01LepId->at(st1_ind))==13&&)
      //      cout<<st1_ind<<"  "<<Dr01LepId->at(st1_ind)<<"  "<<Dr01LepMomId->at(st1_ind)<<"  "<<Dr01LepIsPrompt->at(st1_ind)<<"  "<<Dr01LepIsTauProd->at(st1_ind)<<endl;
      TLorentzVector st1tmp;
      st1tmp.SetPtEtaPhiE(Dr01LepPt->at(st1_ind),Dr01LepEta->at(st1_ind),Dr01LepPhi->at(st1_ind),Dr01LepE->at(st1_ind));
      if(fabs(Dr01LepId->at(st1_ind))==13 &&Dr01LepPt->at(st1_ind)>22 && fabs(Dr01LepEta->at(st1_ind))<2.4 /*&&Dr01LepIsPrompt->at(st1_ind)// ){
	st1mu++;
	st01_mu_vector.push_back(st1tmp);
	st01_mu_charge.push_back(-1*Dr01LepId->at(st1_ind));  
      }
      if(fabs(Dr01LepId->at(st1_ind))==14 /*&&Dr01LepPt->at(st1_ind)>22 && fabs(Dr01LepEta->at(st1_ind))<2.4 &&Dr01LepIsPrompt->at(st1_ind) ){

	st01_nu_vector.push_back(st1tmp);
      }

    }*/
    //    cout<<st01_mu_vector.size()<<" "<<st01_nu_vector.size()<<endl;
    unsigned int const_size=0;
    int gnjet_30=0;
    int gnjet_15=0;

    //  cout<<"NEW EVENT"<<endl; 	
    for(unsigned int gj_ind=0;gj_ind<GjPt->size();gj_ind++){
      bool isbjet=false;       
      if(gj_ind!=0)const_size+=GjNConst->at(gj_ind-1);


/*      bool ismatchedtolep=false;
      for(unsigned int st1_ind=0; st1_ind<Dr01LepPt->size();st1_ind++){
	if(fabs(Dr01LepId->at(st1_ind))==13 || fabs(Dr01LepId->at(st1_ind))==11){
	  double dr_tmp_l_j=DeltaR(Dr01LepEta->at(st1_ind),Gjeta->at(gj_ind),Dr01LepPhi->at(st1_ind),Gjphi->at(gj_ind));
	  if(dr_tmp_l_j<0.4){ismatchedtolep=true;break;}
	}
      }
      if(ismatchedtolep)continue;*/
      TLorentzVector tmp;
      tmp.SetPtEtaPhiE(GjPt->at(gj_ind),Gjeta->at(gj_ind),Gjphi->at(gj_ind),GjE->at(gj_ind));
      if(GjPt->at(gj_ind)>30 && fabs(Gjeta->at(gj_ind))<2.4){  




	vector<TLorentzVector> Gjetconst_vectortmp;
	for(unsigned int gj=0; gj<GjNConst->at(gj_ind); gj++){


	  if(hasb(GjConstId->at(gj+const_size)))isbjet=true;
	  if(GjConstPt->at(gj+const_size)<0.5)continue;
	  TLorentzVector tmpc;
	  tmpc.SetPtEtaPhiE(GjConstPt->at(gj+const_size),GjConstEta->at(gj+const_size),GjConstPhi->at(gj+const_size),GjConstE->at(gj+const_size));
	  Gjetconst_vectortmp.push_back(tmpc);
         // if(hasb(GjConstId->at(gj+const_size))isbjet=true;
	}

	//        if(isbjet!=0)cout<<isbjet<<endl;


/*	for(unsigned int gp3_ind=0;gp3_ind<St03Pt->size();gp3_ind++){

	  if(St03Status->at(gp3_ind)==2 && hasb(St03Id->at(gp3_ind))){
	    double dr_tmp=DeltaR(St03Eta->at(gp3_ind),Gjeta->at(gj_ind),St03Phi->at(gp3_ind),Gjphi->at(gj_ind));
	    h_dr_tmp->Fill(dr_tmp);
	    if(dr_tmp<0.4)isbjet=true;
	  }
	}*/
	if(isbjet)GBjet_vector.push_back(tmp);
	if(!isbjet)Gjet_vector.push_back(tmp);
	if(!isbjet)Gjetconst_vector.push_back(Gjetconst_vectortmp);
	if(isbjet)GBjetconst_vector.push_back(Gjetconst_vectortmp);
	gnjet_30++; 
      }
      if(GjPt->at(gj_ind)>15 && fabs(Gjeta->at(gj_ind))<2.4){  
	gnjet_15++; 
	if(GjPt->at(gj_ind)<30.)Gjet_vector_1530.push_back(tmp);
      }

    }
/*
    double Mmin=9999999.;
    for(unsigned int jetind=0; jetind<Gjet_vector.size();jetind++){
      ga_min.push_back(jetind);
      for(unsigned int jetindd=jetind; jetindd<Gjet_vector.size();jetindd++){
	if(jetind==jetindd)continue;
	for(unsigned int lepind=0; lepind<st01_mu_vector.size();lepind++){
	  for(unsigned int nuind=0; nuind<st01_nu_vector.size();nuind++){


	    double MLep=(st01_mu_vector[lepind]+st01_nu_vector[nuind]).M();
	    double Mjj=(Gjet_vector[jetind]+Gjet_vector[jetindd]).M();
	    double Mcheck=fabs(MLep-80.4) + fabs(Mjj-80.4);
	    if(Mcheck<Mmin){
	      Mmin=Mcheck;
	      //cout<<MLep<<"  "<<Mjj<<"  "<<Mmin<<endl;
	      lind=  lepind;
	      nind=  nuind;
	      j1ind=jetind;
	      j2ind=jetindd;
	    }
	  }
	}
      }
    }*//*
    for(unsigned int i=0;i<ga_min.size();i++){
      if(ga_min[i]==j1ind||ga_min[i]==j2ind)continue;
      gextra_jet_index=ga_min[i]; break;
    }*/
    //  if(gextra_jet_index==99 &&Gjet_vector_1530.size()>0 )gextra_jet_index_1530=0;

    double m[4];
//    if(!(lind>=1 && nind>=1) && lind!=9999 && GBjet_vector.size()>=2 &&GBjet_vector.size()==2){
     //cout<<pseudoTop_pdgId->size()<<endl;
    if(pseudoTop_pdgId->size()>0&& GBjet_vector.size()==2&& Gjet_vector.size()>1){
    if(
       ( fabs(pseudoTop_pdgId->at(4))==13 && fabs(pseudoTop_pdgId->at(6))<6 &&pseudoTop_pt->at(4)>22 && fabs(pseudoTop_eta->at(4))<2.4 &&pseudoTop_pt->at(6)>30 && fabs(pseudoTop_eta->at(6))<2.4  )
     ||( fabs(pseudoTop_pdgId->at(6))==13 && fabs(pseudoTop_pdgId->at(4))<6 &&pseudoTop_pt->at(6)>22 && fabs(pseudoTop_eta->at(6))<2.4 &&pseudoTop_pt->at(4)>30 && fabs(pseudoTop_eta->at(4))<2.4  ) 
      ){
      //cout<<"asda"<<endl;
      TLorentzVector genWlep;
      TLorentzVector genWhad;
      if( fabs(pseudoTop_pdgId->at(4)) ==13){
        st01_nu_vector.SetPtEtaPhiE(pseudoTop_pt->at(5),pseudoTop_eta->at(5),pseudoTop_phi->at(5),pseudoTop_energy->at(5));
        st01_mu_vector.SetPtEtaPhiE(pseudoTop_pt->at(4),pseudoTop_eta->at(4),pseudoTop_phi->at(4),pseudoTop_energy->at(4));
        genWlep.SetPtEtaPhiE(pseudoTop_pt->at(2),pseudoTop_eta->at(2),pseudoTop_phi->at(2),pseudoTop_energy->at(2));
        genWhad.SetPtEtaPhiE(pseudoTop_pt->at(3),pseudoTop_eta->at(3),pseudoTop_phi->at(3),pseudoTop_energy->at(3));
      }
      //cout<<"asdala"<<endl;
      if( fabs(pseudoTop_pdgId->at(6))==13){
        st01_nu_vector.SetPtEtaPhiE(pseudoTop_pt->at(7),pseudoTop_eta->at(7),pseudoTop_phi->at(7),pseudoTop_energy->at(7));
        st01_mu_vector.SetPtEtaPhiE(pseudoTop_pt->at(6),pseudoTop_eta->at(6),pseudoTop_phi->at(6),pseudoTop_energy->at(6));
        genWlep.SetPtEtaPhiE(pseudoTop_pt->at(3),pseudoTop_eta->at(3),pseudoTop_phi->at(3),pseudoTop_energy->at(3));
        genWhad.SetPtEtaPhiE(pseudoTop_pt->at(2),pseudoTop_eta->at(2),pseudoTop_phi->at(2),pseudoTop_energy->at(2));
      }
      //cout<<"asdalavista"<<endl;
     //cout<<"aaaaaaaaaaaaaaaa "<<GBjet_vector.size()<<endl;
/*
      TLorentzVector genWlep=(st01_mu_vector[lind]+st01_nu_vector[nind]);
      TLorentzVector genWhad=(Gjet_vector[j1ind]+Gjet_vector[j2ind]);
      m[0]=(genWlep + GBjet_vector[0]).M();
      m[1]=(genWlep + GBjet_vector[1]).M();
      m[2]=(genWhad + GBjet_vector[0]).M();
      m[3]=(genWhad + GBjet_vector[1]).M();
      double mtmin1= fabs(m[0]-172.5) + fabs(m[3]-172.5);
      double mtmin2= fabs(m[1]-172.5) + fabs(m[2]-172.5);
      if(mtmin1<mtmin2) {
	gtlep_vector=genWlep + GBjet_vector[0];
	gthad_vector=genWhad + GBjet_vector[1];

      }
      if(mtmin1>mtmin2) {
	gtlep_vector=genWlep + GBjet_vector[1];
	gthad_vector=genWhad + GBjet_vector[0];
      }*/
      //      cout<<genWlep.M()<<"  "<<genWhad.M()<<"  "<<gtlep_vector.M()<<"  "<<gthad_vector.M()<<endl;


      getab1=GBjet_vector[0].Eta();
      getab2=GBjet_vector[1].Eta();
     //cout<<"cccccccccccasdad"<<endl;
      if(getab1<getab2)getamin=getab1;
      else getamin=getab2;
      gdeltaetabb=fabs(getab1-getab2);
     //cout<<"bbbbbbbbbbbbbbbbbb"<<endl;

      for(unsigned int j_ind=0; j_ind<Gjet_vector.size();j_ind++){

	if(j_ind==j1ind ||j_ind==j2ind)continue;

	double dphi=fabs(DeltaPhi(gttbar_vector.Phi(),Gjet_vector[j_ind].Phi()))*180/pi;
	if(dphi<60.)gnjet_toward++;
	if(dphi>60. &&dphi<120.)gnjet_transverse++;
	if(dphi>120. &&dphi<180.)gnjet_away++;

	if(dphi<60.)gnjet_toward15++;
	if(dphi>60. &&dphi<120.)gnjet_transverse15++;
	if(dphi>120. &&dphi<180.)gnjet_away15++;


	if(Gjet_vector[j_ind].Eta()>getamin && Gjet_vector[j_ind].Eta()<getamin+gdeltaetabb ) gnjet_bb++;
      }
      for(unsigned int jet_vector_1530_ind =0; jet_vector_1530_ind<jet_vector_1530.size();jet_vector_1530_ind++){
	if(Gjet_vector_1530[jet_vector_1530_ind].Eta()>getamin && Gjet_vector_1530[jet_vector_1530_ind].Eta()<getamin+gdeltaetabb ) gnjet_bb++;
	//      cout<<fabs(DeltaPhi(ttbar_tmp.Phi(),jet_vector_1530[jet_vector_1530_ind].Phi()))<<endl;           
	double dphi=fabs(DeltaPhi(gttbar_vector.Phi(),jet_vector_1530[jet_vector_1530_ind].Phi()))*180/pi;
	if(dphi<60.)gnjet_toward15++;
	if(dphi>60. &&dphi<120.)gnjet_transverse15++;
	if(dphi>120. &&dphi<180.)gnjet_away15++;
      }

      if(fabs(pseudoTop_pdgId->at(4))==13  ){
	gtlep_vector.SetPtEtaPhiE(pseudoTop_pt->at(0),pseudoTop_eta->at(0),pseudoTop_phi->at(0),pseudoTop_energy->at(0));
	gthad_vector.SetPtEtaPhiE(pseudoTop_pt->at(1),pseudoTop_eta->at(1),pseudoTop_phi->at(1),pseudoTop_energy->at(1));
      }

      if(fabs(pseudoTop_pdgId->at(6))==13 ){
	gthad_vector.SetPtEtaPhiE(pseudoTop_pt->at(0),pseudoTop_eta->at(0),pseudoTop_phi->at(0),pseudoTop_energy->at(0));
	gtlep_vector.SetPtEtaPhiE(pseudoTop_pt->at(1),pseudoTop_eta->at(1),pseudoTop_phi->at(1),pseudoTop_energy->at(1));
      }

      if(pseudoTop_pdgId->at(2)==6){
	gtop_vector.SetPtEtaPhiE(pseudoTop_pt->at(0),pseudoTop_eta->at(0),pseudoTop_phi->at(0),pseudoTop_energy->at(0));
	gatop_vector.SetPtEtaPhiE(pseudoTop_pt->at(1),pseudoTop_eta->at(1),pseudoTop_phi->at(1),pseudoTop_energy->at(1));
      }

      if(pseudoTop_pdgId->at(0)==-6){
	gtop_vector.SetPtEtaPhiE(pseudoTop_pt->at(1),pseudoTop_eta->at(1),pseudoTop_phi->at(1),pseudoTop_energy->at(1));
	gatop_vector.SetPtEtaPhiE(pseudoTop_pt->at(0),pseudoTop_eta->at(0),pseudoTop_phi->at(0),pseudoTop_energy->at(0));
      }

      h_gen_mtlep->Fill(gtlep_vector.M());
      h_gen_mthad->Fill(gthad_vector.M());
      h_gen_mwlep->Fill(genWlep.M());
      h_gen_mwhad->Fill(genWhad.M());

      h_gen_pttlep->Fill(gtlep_vector.Pt());
      h_gen_ptthad->Fill(gthad_vector.Pt());
      h_gen_ptwlep->Fill(genWlep.Pt());
      h_gen_ptwhad->Fill(genWhad.Pt());
     //cout<<"ccccccccccccccccccc"<<endl;
      h_gen_ptttbar->Fill((gtlep_vector + gthad_vector).Pt());
      h_gen_mttbar->Fill((gtlep_vector + gthad_vector).M());
      gttbar_vector=gtlep_vector+gthad_vector;

      /*     if(st01_mu_charge[lind]<0){
	     gtop_vector =gtlep_vector;
	     gatop_vector=gthad_vector;
	     }
	     if(st01_mu_charge[lind]>0){
	     gatop_vector=gtlep_vector;
	     gtop_vector =gthad_vector;
	     }
      */

      //use pseudotop products

      if(pseudoTop_pdgId->at(0)==6){
	gtop_vector.SetPtEtaPhiE(pseudoTop_pt->at(0),pseudoTop_eta->at(0),pseudoTop_phi->at(0),pseudoTop_energy->at(0));
	gatop_vector.SetPtEtaPhiE(pseudoTop_pt->at(1),pseudoTop_eta->at(1),pseudoTop_phi->at(1),pseudoTop_energy->at(1));
      }

      if(pseudoTop_pdgId->at(0)==-6){
	gtop_vector.SetPtEtaPhiE(pseudoTop_pt->at(1),pseudoTop_eta->at(1),pseudoTop_phi->at(1),pseudoTop_energy->at(1));
	gatop_vector.SetPtEtaPhiE(pseudoTop_pt->at(0),pseudoTop_eta->at(0),pseudoTop_phi->at(0),pseudoTop_energy->at(0));
      }
     //cout<<"ddddddddddddddddddddd"<<endl;
      if(gextra_jet_index!=99)gttj_vector=gttbar_vector+Gjet_vector[gextra_jet_index];
      //      if(extra_jet_index==99 &&extra_jet_index_1530!=99 )ttj_vector=top_vector +atop_vector+jet_vector_1530[extra_jet_index_1530];

      for(unsigned int gp_ind=0;gp_ind<Packed01Id->size();gp_ind++){    
	bool matchjet=false;
	//         cout<<gp_ind<<"  "<<Packed01Phi->at(gp_ind)<<endl;
	if(Packed01Pt->at(gp_ind)<0.5 || fabs(Packed01Eta->at(gp_ind))>2.1 ||Packed01Charge->at(gp_ind)==0)continue;
	//        cout<<gp_ind<<endl;
	/*       if(Packed01Id->at(gp_ind)==12 ||Packed01Id->at(gp_ind)==14 ||Packed01Id->at(gp_ind)==16)cout<<"ACHTUNG- neutrinos in the gencoll"<<endl;
		 double dr_gen_mu=DeltaR(Packed01Eta->at(gp_ind),st01_mu_vector[lind].Eta(),Packed01Phi->at(gp_ind),st01_mu_vector[lind].Phi());
		 if(dr_gen_mu<0.1)continue;


		 for(unsigned int const_gen_ind=0;const_gen_ind<Gjetconst_vector[j1ind].size();const_gen_ind++){
		 double dr_gen_j1=DeltaR(Packed01Eta->at(gp_ind),Gjetconst_vector[j1ind][const_gen_ind].Eta(),Packed01Phi->at(gp_ind),Gjetconst_vector[j1ind][const_gen_ind].Phi());
		 if(dr_gen_j1<0.1){
		 matchjet=true;break;
		 }    
		 }

		 for(unsigned int const_gen_ind=0;const_gen_ind<Gjetconst_vector[j2ind].size();const_gen_ind++){
		 double dr_gen_j1=DeltaR(Packed01Eta->at(gp_ind),Gjetconst_vector[j2ind][const_gen_ind].Eta(),Packed01Phi->at(gp_ind),Gjetconst_vector[j2ind][const_gen_ind].Phi());
		 if(dr_gen_j1<0.1){
		 matchjet=true;break;
		 }
		 }

		 for(unsigned int const_gen_ind=0;const_gen_ind<GBjetconst_vector[0].size();const_gen_ind++){
		 double dr_gen_j1=DeltaR(Packed01Eta->at(gp_ind),GBjetconst_vector[0][const_gen_ind].Eta(),Packed01Phi->at(gp_ind),GBjetconst_vector[0][const_gen_ind].Phi());
		 if(dr_gen_j1<0.1){
		 matchjet=true;break;
		 }

		 }

		 for(unsigned int const_gen_ind=0;const_gen_ind<GBjetconst_vector[1].size();const_gen_ind++){
		 double dr_gen_j1=DeltaR(Packed01Eta->at(gp_ind),GBjetconst_vector[1][const_gen_ind].Eta(),Packed01Phi->at(gp_ind),GBjetconst_vector[1][const_gen_ind].Phi());
		 if(dr_gen_j1<0.1){
		 matchjet=true;break;
		 }

		 }
	*/

	    for(unsigned int const_gen_ind=0;const_gen_ind<pseudoTop_const_pt->size();const_gen_ind++){
	      double dr_gen_j1=DeltaR(Packed01Eta->at(gp_ind),pseudoTop_const_eta->at(const_gen_ind),Packed01Phi->at(gp_ind),pseudoTop_const_phi->at(const_gen_ind));
     //         cout<<dr_gen_j1<<"  "<<pseudoTop_const_pdgId->at(const_gen_ind)<<"  "<< Packed01Id->at(gp_ind)<<endl;
//	      if(dr_gen_j1<0.0001&&pseudoTop_const_pdgId->at(const_gen_ind)==Packed01Id->at(gp_ind) ){
	      if(dr_gen_j1<0.05 ){

//              cout<<dr_gen_j1<<"  "<<pseudoTop_const_pdgId->at(const_gen_ind)<<"  "<< Packed01Id->at(gp_ind)<<endl;
	      matchjet=true;break;
	      }
	      }
	 
	//        double dr_gen_j1j=DeltaR(Packed01Eta->at(gp_ind),Gjet_vector[j1ind].Eta(),Packed01Phi->at(gp_ind),Gjet_vector[j1ind].Phi());
	//        double dr_gen_j2j=DeltaR(Packed01Eta->at(gp_ind),Gjet_vector[j2ind].Eta(),Packed01Phi->at(gp_ind),Gjet_vector[j2ind].Phi());
	//        double dr_gen_j1bj=DeltaR(Packed01Eta->at(gp_ind),GBjet_vector[0].Eta(),Packed01Phi->at(gp_ind),Gjet_vector[0].Phi());
	//        double dr_gen_j2bj=DeltaR(Packed01Eta->at(gp_ind),GBjet_vector[1].Eta(),Packed01Phi->at(gp_ind),Gjet_vector[1].Phi());

	//if(matchjet) continue;
	//        if(dr_gen_j1j<0.4 ||dr_gen_j2j<0.4 ||dr_gen_j1bj<0.4 ||dr_gen_j2bj<0.4)continue;
	gn_pf++;
	gptsum_pf+=Packed01Pt->at(gp_ind);
        TLorentzVector gptmp;
        gptmp.SetPtEtaPhiE(Packed01Pt->at(gp_ind),Packed01Eta->at(gp_ind),Packed01Phi->at(gp_ind),Packed01E->at(gp_ind));
        vector_vector_gp.push_back(gptmp);
	double gdeltaphi_tt_pf=DeltaPhi(Packed01Phi->at(gp_ind),gttbar_vector.Phi())*180/pi;
	// cout<<gdeltaphi_tt_pf<<endl;
	if(fabs(gdeltaphi_tt_pf)>0 && fabs(gdeltaphi_tt_pf)<60){
	  gn_pf_toward++;
	  gptsum_pf_toward+=Packed01Pt->at(gp_ind);
	}
	if(fabs(gdeltaphi_tt_pf)>60 && fabs(gdeltaphi_tt_pf)<120){
	  gn_pf_transverse++;
	  gptsum_pf_transverse+=Packed01Pt->at(gp_ind);
	}
	if(fabs(gdeltaphi_tt_pf)>120 && fabs(gdeltaphi_tt_pf)<180){
	  gn_pf_away++;
	  gptsum_pf_away+=Packed01Pt->at(gp_ind);
	}


	for(int gdphiloop=0;gdphiloop<20;gdphiloop++){
	  if(fabs(gdeltaphi_tt_pf)>gdphiloop*9 && fabs(gdeltaphi_tt_pf)<(gdphiloop+1)*9){
	    gn_pf_dphi[gdphiloop]++;
	    gptsum_pf_dphi[gdphiloop]+=Packed01Pt->at(gp_ind);
	  }
	}


      }
     //cout<<"eeeeeeeeeeeeeeeeeeeeeee"<<endl;
     //cout<<"ffffffffffffffffffffffffff"<<endl;
      for(int pdfind=0; pdfind<pdfind_max;pdfind++){
	// if(pdfind!=0)cout<<mcWeights_->at(8+pdfind)<<endl;
	double weight=w;
	if(dopdf&& pdfind!=0)weight=w*mcWeights_->at(8+pdfind);
	if(pdfind==1)continue;

	//	if(!dopdf&&pdfind!=0 &&puWeight.weight(int(PU_npT))!=0 )weight=puUp.weight(int(PU_npT))*w/puWeight.weight(int(PU_npT)); 
	// cout<<"I am alive "<<pdfind<<"  "<<weight<<" "<<gn_pf<<" "<<gn_pf_transverse<<" "<<gn_pf_toward<<" "<<gn_pf_away<<endl;
	h_npf_inclusive[2*pdfind]->Fill(gn_pf,weight);
	h_npf_toward[2*pdfind]->Fill(gn_pf_toward,weight);
	h_npf_transverse[2*pdfind]->Fill(gn_pf_transverse,weight);
	h_npf_away[2*pdfind]->Fill(gn_pf_away,weight);

	h_ptsumpf_inclusive[2*pdfind]->Fill(gptsum_pf,weight);
	h_ptsumpf_toward[2*pdfind]->Fill(gptsum_pf_toward,weight);
	h_ptsumpf_transverse[2*pdfind]->Fill(gptsum_pf_transverse,weight);
	h_ptsumpf_away[2*pdfind]->Fill(gptsum_pf_away,weight);

	if(gn_pf!=0)h_ptavepf_inclusive[2*pdfind]->Fill(gptsum_pf/gn_pf,weight);
	if(gn_pf_toward!=0)h_ptavepf_toward[2*pdfind]->Fill(gptsum_pf_toward/gn_pf_toward,weight);
	if(gn_pf_transverse!=0)h_ptavepf_transverse[2*pdfind]->Fill(gptsum_pf_transverse/gn_pf_transverse,weight);
	if(gn_pf_away!=0)h_ptavepf_away[2*pdfind]->Fill(gptsum_pf_away/gn_pf_away,weight);

     //cout<<"ggggggggggggggggggg"<<endl;



	if(gn_pf!=0){
	  h_1d_npf[2*pdfind]->Fill(gn_pf,weight);
	  h_1d_ptsumpf[2*pdfind]->Fill(gptsum_pf,weight);
	  h_1d_ptavepf[2*pdfind]->Fill(gptsum_pf/gn_pf,weight);
	  for(int dphiloop=0;dphiloop<10;dphiloop++){// 10 bins in pt, [0,1000] GeV
	    if(gttbar_vector.Pt()>dphiloop*100. &&gttbar_vector.Pt()<(dphiloop+1)*100. ){
	      if(gn_pf<200.)h_1d_ptttbar_npf[2*pdfind]->Fill(dphiloop*50.+gn_pf/4.,weight);
	      if(gn_pf>=200.)h_1d_ptttbar_npf[2*pdfind]->Fill(dphiloop*50.+49.9,weight);
	    }
	  }

     //cout<<"hhhhhhhhhhhhhhhhhhhhh"<<endl;
	  for(int dphiloop=0;dphiloop<20;dphiloop++){
	    if(gn_pf_dphi[dphiloop]==0)continue;

	    //            //cout<<dphiloop*10.+gn_pf_dphi[dphiloop]/10.<<endl;
	    if(gn_pf_dphi[dphiloop]<100)h_1d_dphi_npf[2*pdfind]->Fill(dphiloop*10.+gn_pf_dphi[dphiloop]/10.,weight);
	    if(gn_pf_dphi[dphiloop]>=100)h_1d_dphi_npf[2*pdfind]->Fill(dphiloop*10.+9.9,weight);

	    h_dphi_npf[2*pdfind]->Fill(dphiloop*9,gn_pf_dphi[dphiloop],weight);
	    h_dphi_ptsumpf[2*pdfind]->Fill(dphiloop*9,gptsum_pf_dphi[dphiloop],weight);
	    h_dphi_ptaveragepf[2*pdfind]->Fill(dphiloop*9,gptsum_pf_dphi[dphiloop]/gn_pf_dphi[dphiloop],weight);
	    h_profile_dphi_npf[2*pdfind]->Fill(dphiloop*9,gn_pf_dphi[dphiloop],weight);
	    h_profile_dphi_ptsumpf[2*pdfind]->Fill(dphiloop*9,gptsum_pf_dphi[dphiloop],weight);
	    h_profile_dphi_ptaveragepf[2*pdfind]->Fill(dphiloop*9,gptsum_pf_dphi[dphiloop]/gn_pf_dphi[dphiloop],weight);

	    if(gnjet_15==4){
	      h_dphi_npf_0j[2*pdfind]->Fill(dphiloop*9,gn_pf_dphi[dphiloop],weight);
	      h_dphi_ptsumpf_0j[2*pdfind]->Fill(dphiloop*9,gptsum_pf_dphi[dphiloop],weight);
	      h_dphi_ptaveragepf_0j[2*pdfind]->Fill(dphiloop*9,gptsum_pf_dphi[dphiloop]/gn_pf_dphi[dphiloop],weight);
	      h_profile_dphi_npf_0j[2*pdfind]->Fill(dphiloop*9,gn_pf_dphi[dphiloop],weight);
	      h_profile_dphi_ptsumpf_0j[2*pdfind]->Fill(dphiloop*9,gptsum_pf_dphi[dphiloop],weight);
	      h_profile_dphi_ptaveragepf_0j[2*pdfind]->Fill(dphiloop*9,gptsum_pf_dphi[dphiloop]/gn_pf_dphi[dphiloop],weight);
	    }

	    if(gnjet_15==5){
	      h_dphi_npf_1j[2*pdfind]->Fill(dphiloop*9,gn_pf_dphi[dphiloop],weight);
	      h_dphi_ptsumpf_1j[2*pdfind]->Fill(dphiloop*9,gptsum_pf_dphi[dphiloop],weight);
	      h_dphi_ptaveragepf_1j[2*pdfind]->Fill(dphiloop*9,gptsum_pf_dphi[dphiloop]/gn_pf_dphi[dphiloop],weight);
	      h_profile_dphi_npf_1j[2*pdfind]->Fill(dphiloop*9,gn_pf_dphi[dphiloop],weight);
	      h_profile_dphi_ptsumpf_1j[2*pdfind]->Fill(dphiloop*9,gptsum_pf_dphi[dphiloop],weight);
	      h_profile_dphi_ptaveragepf_1j[2*pdfind]->Fill(dphiloop*9,gptsum_pf_dphi[dphiloop]/gn_pf_dphi[dphiloop],weight);
	    }

	    if(gnjet_15>=6){
	      h_dphi_npf_2pj[2*pdfind]->Fill(dphiloop*9,gn_pf_dphi[dphiloop],weight);
	      h_dphi_ptsumpf_2pj[2*pdfind]->Fill(dphiloop*9,gptsum_pf_dphi[dphiloop],weight);
	      h_dphi_ptaveragepf_2pj[2*pdfind]->Fill(dphiloop*9,gptsum_pf_dphi[dphiloop]/gn_pf_dphi[dphiloop],weight);
	      h_profile_dphi_npf_2pj[2*pdfind]->Fill(dphiloop*9,gn_pf_dphi[dphiloop],weight);
	      h_profile_dphi_ptsumpf_2pj[2*pdfind]->Fill(dphiloop*9,gptsum_pf_dphi[dphiloop],weight);
	      h_profile_dphi_ptaveragepf_2pj[2*pdfind]->Fill(dphiloop*9,gptsum_pf_dphi[dphiloop]/gn_pf_dphi[dphiloop],weight);
	    }
	  }
     //cout<<"iiiiiiiiiiiiiiiiiiiiiiii"<<endl;
	  h_nvtx_npf[2*pdfind]->Fill(EvtInfo_NumVtx,weight);
	  h_profile_nvtx_npf[2*pdfind]->Fill(EvtInfo_NumVtx,gn_pf,weight);
	  h_profile_nvtx_sumpt[2*pdfind]->Fill(EvtInfo_NumVtx,gptsum_pf,weight);
	  h_profile_nvtx_njet30[2*pdfind]->Fill(EvtInfo_NumVtx,jet_vector.size()-4,weight);
	  h_profile_nvtx_njet15[2*pdfind]->Fill(EvtInfo_NumVtx,gnjet_15-4,weight);


	  if(gnjet_15==4){
	    h_nvtx_npf_0j[2*pdfind]->Fill(EvtInfo_NumVtx,weight);
	    h_profile_nvtx_npf_0j[2*pdfind]->Fill(EvtInfo_NumVtx,gn_pf,weight);
	    h_profile_nvtx_sumpt_0j[2*pdfind]->Fill(EvtInfo_NumVtx,gptsum_pf,weight);
	  }
	  if(gnjet_15==5){
	    h_nvtx_npf_1j[2*pdfind]->Fill(EvtInfo_NumVtx,weight);
	    h_profile_nvtx_npf_1j[2*pdfind]->Fill(EvtInfo_NumVtx,gn_pf,weight);
	    h_profile_nvtx_sumpt_1j[2*pdfind]->Fill(EvtInfo_NumVtx,gptsum_pf,weight);
	  }

	  if(gnjet_15>=6){
	    h_nvtx_npf_2pj[2*pdfind]->Fill(EvtInfo_NumVtx,weight);
	    h_profile_nvtx_npf_2pj[2*pdfind]->Fill(EvtInfo_NumVtx,gn_pf,weight);
	    h_profile_nvtx_sumpt_2pj[2*pdfind]->Fill(EvtInfo_NumVtx,gptsum_pf,weight);

	  }

     //cout<<"jjjjjjjjjjjjjjjjjjjjjj"<<endl;
	  h_profile_ptttbar_npf[2*pdfind]->Fill(gttbar_vector.Pt(),gn_pf,weight);
	  h_profile_ptttbar_sumpt[2*pdfind]->Fill(gttbar_vector.Pt(),gptsum_pf,weight);
	  h_profile_ptttbar_avept[2*pdfind]->Fill(gttbar_vector.Pt(),gptsum_pf/gn_pf,weight);
	  h_profile_ptttbar_njet15[2*pdfind]->Fill(gttbar_vector.Pt(),gnjet_15-4,weight);
	  h_profile_ptttbar_njet30[2*pdfind]->Fill(gttbar_vector.Pt(),jet_vector.size()-4,weight);

	  if(gn_pf_away!=0)h_profile_ptttbar_npf_away[2*pdfind]->Fill(gttbar_vector.Pt(),gn_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_ptttbar_sumpt_away[2*pdfind]->Fill(gttbar_vector.Pt(),gptsum_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_ptttbar_avept_away[2*pdfind]->Fill(gttbar_vector.Pt(),gptsum_pf_away/gn_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_ptttbar_njet15_away[2*pdfind]->Fill(gttbar_vector.Pt(),gnjet_away15,weight);
	  if(gn_pf_away!=0)h_profile_ptttbar_njet30_away[2*pdfind]->Fill(gttbar_vector.Pt(),gnjet_away,weight);

	  if(gn_pf_transverse!=0)h_profile_ptttbar_npf_transverse[2*pdfind]->Fill(gttbar_vector.Pt(),gn_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_ptttbar_sumpt_transverse[2*pdfind]->Fill(gttbar_vector.Pt(),gptsum_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_ptttbar_avept_transverse[2*pdfind]->Fill(gttbar_vector.Pt(),gptsum_pf_transverse/gn_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_ptttbar_njet15_transverse[2*pdfind]->Fill(gttbar_vector.Pt(),gnjet_transverse15,weight);
	  if(gn_pf_transverse!=0)h_profile_ptttbar_njet30_transverse[2*pdfind]->Fill(gttbar_vector.Pt(),gnjet_transverse,weight);

	  if(gn_pf_toward!=0)h_profile_ptttbar_npf_toward[2*pdfind]->Fill(gttbar_vector.Pt(),gn_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_ptttbar_sumpt_toward[2*pdfind]->Fill(gttbar_vector.Pt(),gptsum_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_ptttbar_avept_toward[2*pdfind]->Fill(gttbar_vector.Pt(),gptsum_pf_toward/gn_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_ptttbar_njet15_toward[2*pdfind]->Fill(gttbar_vector.Pt(),gnjet_toward15,weight);
	  if(gn_pf_toward!=0)h_profile_ptttbar_njet30_toward[2*pdfind]->Fill(gttbar_vector.Pt(),gnjet_toward,weight);

	  h_profile_mttbar_npf[2*pdfind]->Fill(gttbar_vector.M(),gn_pf,weight);
	  h_profile_mttbar_sumpt[2*pdfind]->Fill(gttbar_vector.M(),gptsum_pf,weight);
	  h_profile_mttbar_avept[2*pdfind]->Fill(gttbar_vector.M(),gptsum_pf/gn_pf,weight);
	  if(gn_pf_away!=0)h_profile_mttbar_npf_away[2*pdfind]->Fill(gttbar_vector.M(),gn_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_mttbar_sumpt_away[2*pdfind]->Fill(gttbar_vector.M(),gptsum_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_mttbar_avept_away[2*pdfind]->Fill(gttbar_vector.M(),gptsum_pf_away/gn_pf_away,weight);
	  if(gn_pf_transverse!=0)h_profile_mttbar_npf_transverse[2*pdfind]->Fill(gttbar_vector.M(),gn_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_mttbar_sumpt_transverse[2*pdfind]->Fill(gttbar_vector.M(),gptsum_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_mttbar_avept_transverse[2*pdfind]->Fill(gttbar_vector.M(),gptsum_pf_transverse/gn_pf_transverse,weight);
	  if(gn_pf_toward!=0)h_profile_mttbar_npf_toward[2*pdfind]->Fill(gttbar_vector.M(),gn_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_mttbar_sumpt_toward[2*pdfind]->Fill(gttbar_vector.M(),gptsum_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_mttbar_avept_toward[2*pdfind]->Fill(gttbar_vector.M(),gptsum_pf_toward/gn_pf_toward,weight);



     //cout<<"kkkkkkkkkkkkkkkkkkkkkkkkk"<<endl;
	  h_profile_ytt_npf[2*pdfind]->Fill(fabs(gttbar_vector.Rapidity()),gn_pf,weight);
	  h_profile_ytt_sumpt[2*pdfind]->Fill(fabs(gttbar_vector.Rapidity()),gptsum_pf,weight);
	  h_profile_ytt_avept[2*pdfind]->Fill(fabs(gttbar_vector.Rapidity()),gptsum_pf/gn_pf,weight);
	  if(gn_pf_away!=0)h_profile_ytt_npf_away[2*pdfind]->Fill(fabs(gttbar_vector.Rapidity()),gn_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_ytt_sumpt_away[2*pdfind]->Fill(fabs(gttbar_vector.Rapidity()),gptsum_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_ytt_avept_away[2*pdfind]->Fill(fabs(gttbar_vector.Rapidity()),gptsum_pf_away/gn_pf_away,weight);
	  if(gn_pf_transverse!=0)h_profile_ytt_npf_transverse[2*pdfind]->Fill(fabs(gttbar_vector.Rapidity()),gn_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_ytt_sumpt_transverse[2*pdfind]->Fill(fabs(gttbar_vector.Rapidity()),gptsum_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_ytt_avept_transverse[2*pdfind]->Fill(fabs(gttbar_vector.Rapidity()),gptsum_pf_transverse/gn_pf_transverse,weight);
	  if(gn_pf_toward!=0)h_profile_ytt_npf_toward[2*pdfind]->Fill(fabs(gttbar_vector.Rapidity()),gn_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_ytt_sumpt_toward[2*pdfind]->Fill(fabs(gttbar_vector.Rapidity()),gptsum_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_ytt_avept_toward[2*pdfind]->Fill(fabs(gttbar_vector.Rapidity()),gptsum_pf_toward/gn_pf_toward,weight);

	  h_profile_pttop_npf[2*pdfind]->Fill(gtop_vector.Pt(),gn_pf,weight);
	  h_profile_pttop_sumpt[2*pdfind]->Fill(gtop_vector.Pt(),gptsum_pf,weight);
	  h_profile_pttop_avept[2*pdfind]->Fill(gtop_vector.Pt(),gptsum_pf/gn_pf,weight);
	  if(gn_pf_away!=0)h_profile_pttop_npf_away[2*pdfind]->Fill(gtop_vector.Pt(),gn_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_pttop_sumpt_away[2*pdfind]->Fill(gtop_vector.Pt(),gptsum_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_pttop_avept_away[2*pdfind]->Fill(gtop_vector.Pt(),gptsum_pf_away/gn_pf_away,weight);
	  if(gn_pf_transverse!=0)h_profile_pttop_npf_transverse[2*pdfind]->Fill(gtop_vector.Pt(),gn_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_pttop_sumpt_transverse[2*pdfind]->Fill(gtop_vector.Pt(),gptsum_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_pttop_avept_transverse[2*pdfind]->Fill(gtop_vector.Pt(),gptsum_pf_transverse/gn_pf_transverse,weight);
	  if(gn_pf_toward!=0)h_profile_pttop_npf_toward[2*pdfind]->Fill(gtop_vector.Pt(),gn_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_pttop_sumpt_toward[2*pdfind]->Fill(gtop_vector.Pt(),gptsum_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_pttop_avept_toward[2*pdfind]->Fill(gtop_vector.Pt(),gptsum_pf_toward/gn_pf_toward,weight);

	  h_profile_ptatop_npf[2*pdfind]->Fill(gatop_vector.Pt(),gn_pf,weight);
	  h_profile_ptatop_sumpt[2*pdfind]->Fill(gatop_vector.Pt(),gptsum_pf,weight);
	  h_profile_ptatop_avept[2*pdfind]->Fill(gatop_vector.Pt(),gptsum_pf/gn_pf,weight);
	  if(gn_pf_away!=0)h_profile_ptatop_npf_away[2*pdfind]->Fill(gatop_vector.Pt(),gn_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_ptatop_sumpt_away[2*pdfind]->Fill(gatop_vector.Pt(),gptsum_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_ptatop_avept_away[2*pdfind]->Fill(gatop_vector.Pt(),gptsum_pf_away/gn_pf_away,weight);
	  if(gn_pf_transverse!=0)h_profile_ptatop_npf_transverse[2*pdfind]->Fill(gatop_vector.Pt(),gn_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_ptatop_sumpt_transverse[2*pdfind]->Fill(gatop_vector.Pt(),gptsum_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_ptatop_avept_transverse[2*pdfind]->Fill(gatop_vector.Pt(),gptsum_pf_transverse/gn_pf_transverse,weight);
	  if(gn_pf_toward!=0)h_profile_ptatop_npf_toward[2*pdfind]->Fill(gatop_vector.Pt(),gn_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_ptatop_sumpt_toward[2*pdfind]->Fill(gatop_vector.Pt(),gptsum_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_ptatop_avept_toward[2*pdfind]->Fill(gatop_vector.Pt(),gptsum_pf_toward/gn_pf_toward,weight);

	  h_profile_mtop_npf[2*pdfind]->Fill(gtop_vector.M(),gn_pf,weight);
	  h_profile_mtop_sumpt[2*pdfind]->Fill(gtop_vector.M(),gptsum_pf,weight);
	  h_profile_mtop_avept[2*pdfind]->Fill(gtop_vector.M(),gptsum_pf/gn_pf,weight);
	  if(gn_pf_away!=0)h_profile_mtop_npf_away[2*pdfind]->Fill(gtop_vector.M(),gn_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_mtop_sumpt_away[2*pdfind]->Fill(gtop_vector.M(),gptsum_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_mtop_avept_away[2*pdfind]->Fill(gtop_vector.M(),gptsum_pf_away/gn_pf_away,weight);
	  if(gn_pf_transverse!=0)h_profile_mtop_npf_transverse[2*pdfind]->Fill(gtop_vector.M(),gn_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_mtop_sumpt_transverse[2*pdfind]->Fill(gtop_vector.M(),gptsum_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_mtop_avept_transverse[2*pdfind]->Fill(gtop_vector.M(),gptsum_pf_transverse/gn_pf_transverse,weight);
	  if(gn_pf_toward!=0)h_profile_mtop_npf_toward[2*pdfind]->Fill(gtop_vector.M(),gn_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_mtop_sumpt_toward[2*pdfind]->Fill(gtop_vector.M(),gptsum_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_mtop_avept_toward[2*pdfind]->Fill(gtop_vector.M(),gptsum_pf_toward/gn_pf_toward,weight);

	  h_profile_matop_npf[2*pdfind]->Fill(gatop_vector.M(),gn_pf,weight);
	  h_profile_matop_sumpt[2*pdfind]->Fill(gatop_vector.M(),gptsum_pf,weight);
	  h_profile_matop_avept[2*pdfind]->Fill(gatop_vector.M(),gptsum_pf/gn_pf,weight);
	  if(gn_pf_away!=0)h_profile_matop_npf_away[2*pdfind]->Fill(gatop_vector.M(),gn_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_matop_sumpt_away[2*pdfind]->Fill(gatop_vector.M(),gptsum_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_matop_avept_away[2*pdfind]->Fill(gatop_vector.M(),gptsum_pf_away/gn_pf_away,weight);
	  if(gn_pf_transverse!=0)h_profile_matop_npf_transverse[2*pdfind]->Fill(gatop_vector.M(),gn_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_matop_sumpt_transverse[2*pdfind]->Fill(gatop_vector.M(),gptsum_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_matop_avept_transverse[2*pdfind]->Fill(gatop_vector.M(),gptsum_pf_transverse/gn_pf_transverse,weight);
	  if(gn_pf_toward!=0)h_profile_matop_npf_toward[2*pdfind]->Fill(gatop_vector.M(),gn_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_matop_sumpt_toward[2*pdfind]->Fill(gatop_vector.M(),gptsum_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_matop_avept_toward[2*pdfind]->Fill(gatop_vector.M(),gptsum_pf_toward/gn_pf_toward,weight);

	  h_profile_ytop_npf[2*pdfind]->Fill(fabs(gtop_vector.Rapidity()),gn_pf,weight);
	  h_profile_ytop_sumpt[2*pdfind]->Fill(fabs(gtop_vector.Rapidity()),gptsum_pf,weight);
	  h_profile_ytop_avept[2*pdfind]->Fill(fabs(gtop_vector.Rapidity()),gptsum_pf/gn_pf,weight);
	  if(gn_pf_away!=0)h_profile_ytop_npf_away[2*pdfind]->Fill(fabs(gtop_vector.Rapidity()),gn_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_ytop_sumpt_away[2*pdfind]->Fill(fabs(gtop_vector.Rapidity()),gptsum_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_ytop_avept_away[2*pdfind]->Fill(fabs(gtop_vector.Rapidity()),gptsum_pf_away/gn_pf_away,weight);
	  if(gn_pf_transverse!=0)h_profile_ytop_npf_transverse[2*pdfind]->Fill(fabs(gtop_vector.Rapidity()),gn_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_ytop_sumpt_transverse[2*pdfind]->Fill(fabs(gtop_vector.Rapidity()),gptsum_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_ytop_avept_transverse[2*pdfind]->Fill(fabs(gtop_vector.Rapidity()),gptsum_pf_transverse/gn_pf_transverse,weight);
	  if(gn_pf_toward!=0)h_profile_ytop_npf_toward[2*pdfind]->Fill(fabs(gtop_vector.Rapidity()),gn_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_ytop_sumpt_toward[2*pdfind]->Fill(fabs(gtop_vector.Rapidity()),gptsum_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_ytop_avept_toward[2*pdfind]->Fill(fabs(gtop_vector.Rapidity()),gptsum_pf_toward/gn_pf_toward,weight);

	  h_profile_yatop_npf[2*pdfind]->Fill(fabs(gtop_vector.Rapidity()),gn_pf,weight);
	  h_profile_yatop_sumpt[2*pdfind]->Fill(fabs(gtop_vector.Rapidity()),gptsum_pf,weight);
	  h_profile_yatop_avept[2*pdfind]->Fill(fabs(gtop_vector.Rapidity()),gptsum_pf/gn_pf,weight);
	  if(gn_pf_away!=0)h_profile_yatop_npf_away[2*pdfind]->Fill(fabs(gtop_vector.Rapidity()),gn_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_yatop_sumpt_away[2*pdfind]->Fill(fabs(gtop_vector.Rapidity()),gptsum_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_yatop_avept_away[2*pdfind]->Fill(fabs(gtop_vector.Rapidity()),gptsum_pf_away/gn_pf_away,weight);
	  if(gn_pf_transverse!=0)h_profile_yatop_npf_transverse[2*pdfind]->Fill(fabs(gtop_vector.Rapidity()),gn_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_yatop_sumpt_transverse[2*pdfind]->Fill(fabs(gtop_vector.Rapidity()),gptsum_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_yatop_avept_transverse[2*pdfind]->Fill(fabs(gtop_vector.Rapidity()),gptsum_pf_transverse/gn_pf_transverse,weight);
	  if(gn_pf_toward!=0)h_profile_yatop_npf_toward[2*pdfind]->Fill(fabs(gtop_vector.Rapidity()),gn_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_yatop_sumpt_toward[2*pdfind]->Fill(fabs(gtop_vector.Rapidity()),gptsum_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_yatop_avept_toward[2*pdfind]->Fill(fabs(gtop_vector.Rapidity()),gptsum_pf_toward/gn_pf_toward,weight);

	  h_profile_ptthad_npf[2*pdfind]->Fill(gthad_vector.Pt(),gn_pf,weight);
	  h_profile_ptthad_sumpt[2*pdfind]->Fill(gthad_vector.Pt(),gptsum_pf,weight);
	  h_profile_ptthad_avept[2*pdfind]->Fill(gthad_vector.Pt(),gptsum_pf/gn_pf,weight);
	  if(gn_pf_away!=0)h_profile_ptthad_npf_away[2*pdfind]->Fill(gthad_vector.Pt(),gn_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_ptthad_sumpt_away[2*pdfind]->Fill(gthad_vector.Pt(),gptsum_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_ptthad_avept_away[2*pdfind]->Fill(gthad_vector.Pt(),gptsum_pf_away/gn_pf_away,weight);
	  if(gn_pf_transverse!=0)h_profile_ptthad_npf_transverse[2*pdfind]->Fill(gthad_vector.Pt(),gn_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_ptthad_sumpt_transverse[2*pdfind]->Fill(gthad_vector.Pt(),gptsum_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_ptthad_avept_transverse[2*pdfind]->Fill(gthad_vector.Pt(),gptsum_pf_transverse/gn_pf_transverse,weight);
	  if(gn_pf_toward!=0)h_profile_ptthad_npf_toward[2*pdfind]->Fill(gthad_vector.Pt(),gn_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_ptthad_sumpt_toward[2*pdfind]->Fill(gthad_vector.Pt(),gptsum_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_ptthad_avept_toward[2*pdfind]->Fill(gthad_vector.Pt(),gptsum_pf_toward/gn_pf_toward,weight);

	  h_profile_pttlep_npf[2*pdfind]->Fill(gtlep_vector.Pt(),gn_pf,weight);
	  h_profile_pttlep_sumpt[2*pdfind]->Fill(gtlep_vector.Pt(),gptsum_pf,weight);
	  h_profile_pttlep_avept[2*pdfind]->Fill(gtlep_vector.Pt(),gptsum_pf/gn_pf,weight);
	  if(gn_pf_away!=0)h_profile_pttlep_npf_away[2*pdfind]->Fill(gtlep_vector.Pt(),gn_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_pttlep_sumpt_away[2*pdfind]->Fill(gtlep_vector.Pt(),gptsum_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_pttlep_avept_away[2*pdfind]->Fill(gtlep_vector.Pt(),gptsum_pf_away/gn_pf_away,weight);
	  if(gn_pf_transverse!=0)h_profile_pttlep_npf_transverse[2*pdfind]->Fill(gtlep_vector.Pt(),gn_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_pttlep_sumpt_transverse[2*pdfind]->Fill(gtlep_vector.Pt(),gptsum_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_pttlep_avept_transverse[2*pdfind]->Fill(gtlep_vector.Pt(),gptsum_pf_transverse/gn_pf_transverse,weight);
	  if(gn_pf_toward!=0)h_profile_pttlep_npf_toward[2*pdfind]->Fill(gtlep_vector.Pt(),gn_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_pttlep_sumpt_toward[2*pdfind]->Fill(gtlep_vector.Pt(),gptsum_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_pttlep_avept_toward[2*pdfind]->Fill(gtlep_vector.Pt(),gptsum_pf_toward/gn_pf_toward,weight);

	  h_profile_mthad_npf[2*pdfind]->Fill(gthad_vector.M(),gn_pf,weight);
	  h_profile_mthad_sumpt[2*pdfind]->Fill(gthad_vector.M(),gptsum_pf,weight);
	  h_profile_mthad_avept[2*pdfind]->Fill(gthad_vector.M(),gptsum_pf/gn_pf,weight);
	  if(gn_pf_away!=0)h_profile_mthad_npf_away[2*pdfind]->Fill(gthad_vector.M(),gn_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_mthad_sumpt_away[2*pdfind]->Fill(gthad_vector.M(),gptsum_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_mthad_avept_away[2*pdfind]->Fill(gthad_vector.M(),gptsum_pf_away/gn_pf_away,weight);
	  if(gn_pf_transverse!=0)h_profile_mthad_npf_transverse[2*pdfind]->Fill(gthad_vector.M(),gn_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_mthad_sumpt_transverse[2*pdfind]->Fill(gthad_vector.M(),gptsum_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_mthad_avept_transverse[2*pdfind]->Fill(gthad_vector.M(),gptsum_pf_transverse/gn_pf_transverse,weight);
	  if(gn_pf_toward!=0)h_profile_mthad_npf_toward[2*pdfind]->Fill(gthad_vector.M(),gn_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_mthad_sumpt_toward[2*pdfind]->Fill(gthad_vector.M(),gptsum_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_mthad_avept_toward[2*pdfind]->Fill(gthad_vector.M(),gptsum_pf_toward/gn_pf_toward,weight);

	  h_profile_mtlep_npf[2*pdfind]->Fill(gtlep_vector.M(),gn_pf,weight);
	  h_profile_mtlep_sumpt[2*pdfind]->Fill(gtlep_vector.M(),gptsum_pf,weight);
	  h_profile_mtlep_avept[2*pdfind]->Fill(gtlep_vector.M(),gptsum_pf/gn_pf,weight);
	  if(gn_pf_away!=0)h_profile_mtlep_npf_away[2*pdfind]->Fill(gtlep_vector.M(),gn_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_mtlep_sumpt_away[2*pdfind]->Fill(gtlep_vector.M(),gptsum_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_mtlep_avept_away[2*pdfind]->Fill(gtlep_vector.M(),gptsum_pf_away/gn_pf_away,weight);
	  if(gn_pf_transverse!=0)h_profile_mtlep_npf_transverse[2*pdfind]->Fill(gtlep_vector.M(),gn_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_mtlep_sumpt_transverse[2*pdfind]->Fill(gtlep_vector.M(),gptsum_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_mtlep_avept_transverse[2*pdfind]->Fill(gtlep_vector.M(),gptsum_pf_transverse/gn_pf_transverse,weight);
	  if(gn_pf_toward!=0)h_profile_mtlep_npf_toward[2*pdfind]->Fill(gtlep_vector.M(),gn_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_mtlep_sumpt_toward[2*pdfind]->Fill(gtlep_vector.M(),gptsum_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_mtlep_avept_toward[2*pdfind]->Fill(gtlep_vector.M(),gptsum_pf_toward/gn_pf_toward,weight);

	  h_profile_ythad_npf[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gn_pf,weight);
	  h_profile_ythad_sumpt[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf,weight);
	  h_profile_ythad_avept[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf/gn_pf,weight);
	  if(gn_pf_away!=0)h_profile_ythad_npf_away[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gn_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_ythad_sumpt_away[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_ythad_avept_away[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf_away/gn_pf_away,weight);
	  if(gn_pf_transverse!=0)h_profile_ythad_npf_transverse[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gn_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_ythad_sumpt_transverse[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_ythad_avept_transverse[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf_transverse/gn_pf_transverse,weight);
	  if(gn_pf_toward!=0)h_profile_ythad_npf_toward[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gn_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_ythad_sumpt_toward[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_ythad_avept_toward[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf_toward/gn_pf_toward,weight);
     //cout<<"lllllllllllllllllllllll"<<endl;
	  h_profile_ytlep_npf[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gn_pf,weight);
	  h_profile_ytlep_sumpt[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf,weight);
	  h_profile_ytlep_avept[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf/gn_pf,weight);
	  if(gn_pf_away!=0)h_profile_ytlep_npf_away[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gn_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_ytlep_sumpt_away[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_ytlep_avept_away[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf_away/gn_pf_away,weight);
	  if(gn_pf_transverse!=0)h_profile_ytlep_npf_transverse[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gn_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_ytlep_sumpt_transverse[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_ytlep_avept_transverse[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf_transverse/gn_pf_transverse,weight);
	  if(gn_pf_toward!=0)h_profile_ytlep_npf_toward[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gn_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_ytlep_sumpt_toward[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_ytlep_avept_toward[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf_toward/gn_pf_toward,weight);


	  h_profile_ptt_npf[2*pdfind]->Fill(gthad_vector.Pt(),gn_pf,weight);
	  h_profile_ptt_sumpt[2*pdfind]->Fill(gthad_vector.Pt(),gptsum_pf,weight);
	  h_profile_ptt_avept[2*pdfind]->Fill(gthad_vector.Pt(),gptsum_pf/gn_pf,weight);
	  if(gn_pf_away!=0)h_profile_ptt_npf_away[2*pdfind]->Fill(gthad_vector.Pt(),gn_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_ptt_sumpt_away[2*pdfind]->Fill(gthad_vector.Pt(),gptsum_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_ptt_avept_away[2*pdfind]->Fill(gthad_vector.Pt(),gptsum_pf_away/gn_pf_away,weight);
	  if(gn_pf_transverse!=0)h_profile_ptt_npf_transverse[2*pdfind]->Fill(gthad_vector.Pt(),gn_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_ptt_sumpt_transverse[2*pdfind]->Fill(gthad_vector.Pt(),gptsum_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_ptt_avept_transverse[2*pdfind]->Fill(gthad_vector.Pt(),gptsum_pf_transverse/gn_pf_transverse,weight);
	  if(gn_pf_toward!=0)h_profile_ptt_npf_toward[2*pdfind]->Fill(gthad_vector.Pt(),gn_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_ptt_sumpt_toward[2*pdfind]->Fill(gthad_vector.Pt(),gptsum_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_ptt_avept_toward[2*pdfind]->Fill(gthad_vector.Pt(),gptsum_pf_toward/gn_pf_toward,weight);

	  h_profile_ptt_npf[2*pdfind]->Fill(gtlep_vector.Pt(),gn_pf,weight);
	  h_profile_ptt_sumpt[2*pdfind]->Fill(gtlep_vector.Pt(),gptsum_pf,weight);
	  h_profile_ptt_avept[2*pdfind]->Fill(gtlep_vector.Pt(),gptsum_pf/gn_pf,weight);
	  if(gn_pf_away!=0)h_profile_ptt_npf_away[2*pdfind]->Fill(gtlep_vector.Pt(),gn_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_ptt_sumpt_away[2*pdfind]->Fill(gtlep_vector.Pt(),gptsum_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_ptt_avept_away[2*pdfind]->Fill(gtlep_vector.Pt(),gptsum_pf_away/gn_pf_away,weight);
	  if(gn_pf_transverse!=0)h_profile_ptt_npf_transverse[2*pdfind]->Fill(gtlep_vector.Pt(),gn_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_ptt_sumpt_transverse[2*pdfind]->Fill(gtlep_vector.Pt(),gptsum_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_ptt_avept_transverse[2*pdfind]->Fill(gtlep_vector.Pt(),gptsum_pf_transverse/gn_pf_transverse,weight);
	  if(gn_pf_toward!=0)h_profile_ptt_npf_toward[2*pdfind]->Fill(gtlep_vector.Pt(),gn_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_ptt_sumpt_toward[2*pdfind]->Fill(gtlep_vector.Pt(),gptsum_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_ptt_avept_toward[2*pdfind]->Fill(gtlep_vector.Pt(),gptsum_pf_toward/gn_pf_toward,weight);

	  h_profile_mt_npf[2*pdfind]->Fill(gthad_vector.M(),gn_pf,weight);
	  h_profile_mt_sumpt[2*pdfind]->Fill(gthad_vector.M(),gptsum_pf,weight);
	  h_profile_mt_avept[2*pdfind]->Fill(gthad_vector.M(),gptsum_pf/gn_pf,weight);
	  if(gn_pf_away!=0)h_profile_mt_npf_away[2*pdfind]->Fill(gthad_vector.M(),gn_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_mt_sumpt_away[2*pdfind]->Fill(gthad_vector.M(),gptsum_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_mt_avept_away[2*pdfind]->Fill(gthad_vector.M(),gptsum_pf_away/gn_pf_away,weight);
	  if(gn_pf_transverse!=0)h_profile_mt_npf_transverse[2*pdfind]->Fill(gthad_vector.M(),gn_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_mt_sumpt_transverse[2*pdfind]->Fill(gthad_vector.M(),gptsum_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_mt_avept_transverse[2*pdfind]->Fill(gthad_vector.M(),gptsum_pf_transverse/gn_pf_transverse,weight);
	  if(gn_pf_toward!=0)h_profile_mt_npf_toward[2*pdfind]->Fill(gthad_vector.M(),gn_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_mt_sumpt_toward[2*pdfind]->Fill(gthad_vector.M(),gptsum_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_mt_avept_toward[2*pdfind]->Fill(gthad_vector.M(),gptsum_pf_toward/gn_pf_toward,weight);

	  h_profile_mt_npf[2*pdfind]->Fill(gtlep_vector.M(),gn_pf,weight);
	  h_profile_mt_sumpt[2*pdfind]->Fill(gtlep_vector.M(),gptsum_pf,weight);
	  h_profile_mt_avept[2*pdfind]->Fill(gtlep_vector.M(),gptsum_pf/gn_pf,weight);
	  if(gn_pf_away!=0)h_profile_mt_npf_away[2*pdfind]->Fill(gtlep_vector.M(),gn_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_mt_sumpt_away[2*pdfind]->Fill(gtlep_vector.M(),gptsum_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_mt_avept_away[2*pdfind]->Fill(gtlep_vector.M(),gptsum_pf_away/gn_pf_away,weight);
	  if(gn_pf_transverse!=0)h_profile_mt_npf_transverse[2*pdfind]->Fill(gtlep_vector.M(),gn_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_mt_sumpt_transverse[2*pdfind]->Fill(gtlep_vector.M(),gptsum_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_mt_avept_transverse[2*pdfind]->Fill(gtlep_vector.M(),gptsum_pf_transverse/gn_pf_transverse,weight);
	  if(gn_pf_toward!=0)h_profile_mt_npf_toward[2*pdfind]->Fill(gtlep_vector.M(),gn_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_mt_sumpt_toward[2*pdfind]->Fill(gtlep_vector.M(),gptsum_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_mt_avept_toward[2*pdfind]->Fill(gtlep_vector.M(),gptsum_pf_toward/gn_pf_toward,weight);

	  h_profile_yt_npf[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gn_pf,weight);
	  h_profile_yt_sumpt[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf,weight);
	  h_profile_yt_avept[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf/gn_pf,weight);
	  if(gn_pf_away!=0)h_profile_yt_npf_away[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gn_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_yt_sumpt_away[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_yt_avept_away[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf_away/gn_pf_away,weight);
	  if(gn_pf_transverse!=0)h_profile_yt_npf_transverse[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gn_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_yt_sumpt_transverse[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_yt_avept_transverse[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf_transverse/gn_pf_transverse,weight);
	  if(gn_pf_toward!=0)h_profile_yt_npf_toward[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gn_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_yt_sumpt_toward[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_yt_avept_toward[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf_toward/gn_pf_toward,weight);

	  h_profile_yt_npf[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gn_pf,weight);
	  h_profile_yt_sumpt[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf,weight);
	  h_profile_yt_avept[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf/gn_pf,weight);
	  if(gn_pf_away!=0)h_profile_yt_npf_away[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gn_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_yt_sumpt_away[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf_away,weight);
	  if(gn_pf_away!=0)h_profile_yt_avept_away[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf_away/gn_pf_away,weight);
	  if(gn_pf_transverse!=0)h_profile_yt_npf_transverse[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gn_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_yt_sumpt_transverse[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf_transverse,weight);
	  if(gn_pf_transverse!=0)h_profile_yt_avept_transverse[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf_transverse/gn_pf_transverse,weight);
	  if(gn_pf_toward!=0)h_profile_yt_npf_toward[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gn_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_yt_sumpt_toward[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf_toward,weight);
	  if(gn_pf_toward!=0)h_profile_yt_avept_toward[2*pdfind]->Fill(fabs(gthad_vector.Rapidity()),gptsum_pf_toward/gn_pf_toward,weight);




     //cout<<"mmmmmmmmmmmmmmmmmmmmmmmmmmmm"<<endl;


	  if(gextra_jet_index!=99 /*||extra_jet_index_1530!=99*/ ){
	    h_rec_ttjY[2*pdfind]->Fill(gttj_vector.Rapidity(),weight);

	    h_profile_yttj_npf[2*pdfind]->Fill(fabs(gttj_vector.Rapidity()),gn_pf,weight);
	    h_profile_yttj_sumpt[2*pdfind]->Fill(fabs(gttj_vector.Rapidity()),gptsum_pf,weight);
	    h_profile_yttj_avept[2*pdfind]->Fill(fabs(gttj_vector.Rapidity()),gptsum_pf/gn_pf,weight);
	    if(gn_pf_away!=0)h_profile_yttj_npf_away[2*pdfind]->Fill(fabs(gttj_vector.Rapidity()),gn_pf_away,weight);
	    if(gn_pf_away!=0)h_profile_yttj_sumpt_away[2*pdfind]->Fill(fabs(gttj_vector.Rapidity()),gptsum_pf_away,weight);
	    if(gn_pf_away!=0)h_profile_yttj_avept_away[2*pdfind]->Fill(fabs(gttj_vector.Rapidity()),gptsum_pf_away/gn_pf_away,weight);
	    if(gn_pf_transverse!=0)h_profile_yttj_npf_transverse[2*pdfind]->Fill(fabs(gttj_vector.Rapidity()),gn_pf_transverse,weight);
	    if(gn_pf_transverse!=0)h_profile_yttj_sumpt_transverse[2*pdfind]->Fill(fabs(gttj_vector.Rapidity()),gptsum_pf_transverse,weight);
	    if(gn_pf_transverse!=0)h_profile_yttj_avept_transverse[2*pdfind]->Fill(fabs(gttj_vector.Rapidity()),gptsum_pf_transverse/gn_pf_transverse,weight);
	    if(gn_pf_toward!=0)h_profile_yttj_npf_toward[2*pdfind]->Fill(fabs(gttj_vector.Rapidity()),gn_pf_toward,weight);
	    if(gn_pf_toward!=0)h_profile_yttj_sumpt_toward[2*pdfind]->Fill(fabs(gttj_vector.Rapidity()),gptsum_pf_toward,weight);
	    if(gn_pf_toward!=0)h_profile_yttj_avept_toward[2*pdfind]->Fill(fabs(gttj_vector.Rapidity()),gptsum_pf_toward/gn_pf_toward,weight); 
	  }
     //cout<<"mmmmmmmmmmmmmmmmmmmmmmmmmmmm"<<"11111111111111111"<<endl;
	  //     }
	  //   }

	}
	h_nvtx[2*pdfind]->Fill(EvtInfo_NumVtx,weight);
	h_m_top[2*pdfind]->Fill(gtop_vector.M(),weight);
	h_m_atop[2*pdfind]->Fill(gatop_vector.M(),weight);
	h_pt_top[2*pdfind]->Fill(gtop_vector.Pt(),weight);
	h_pt_atop[2*pdfind]->Fill(gatop_vector.Pt(),weight);
	h_m_top_fixbin[2*pdfind]->Fill(gtop_vector.M(),weight);
	h_m_atop_fixbin[2*pdfind]->Fill(gatop_vector.M(),weight);
	h_pt_top_fixbin[2*pdfind]->Fill(gtop_vector.Pt(),weight);
	h_pt_atop_fixbin[2*pdfind]->Fill(gatop_vector.Pt(),weight);

	h_pt_ttbar_kinrec[2*pdfind]->Fill((gtlep_vector+gthad_vector).Pt(),weight);
     //cout<<"mmmmmmmmmmmmmmmmmmmmmmmmmmmm"<<"22222222222222222222"<<endl;

	//	h_MTW[2*pdfind]->Fill(MTW,weight);
	h_mu_pt_meas[2*pdfind]->Fill(st01_mu_vector.Pt(),weight);
	h_mu_eta_meas[2*pdfind]->Fill(st01_mu_vector.Eta(),weight);
	h_mu_phi_meas[2*pdfind]->Fill(st01_mu_vector.Phi(),weight);
	h_mu_iso_meas[2*pdfind]->Fill(st01_mu_vector.E(),weight);
	h_m_thad[2*pdfind]->Fill(gthad_vector.M(),weight); 
	h_m_tlep[2*pdfind]->Fill(gtlep_vector.M(),weight);   

	h_pt_thad[2*pdfind]->Fill(gthad_vector.Pt(),weight); 
	h_pt_tlep[2*pdfind]->Fill(gtlep_vector.Pt(),weight);   

	h_m_thad_fixbin[2*pdfind]->Fill(gthad_vector.M(),weight); 
	h_m_tlep_fixbin[2*pdfind]->Fill(gtlep_vector.M(),weight);   

	h_pt_thad_fixbin[2*pdfind]->Fill(gthad_vector.Pt(),weight); 
	h_pt_tlep_fixbin[2*pdfind]->Fill(gtlep_vector.Pt(),weight);   

	h_y_thad[2*pdfind]->Fill(gthad_vector.Rapidity(),weight); 
	h_y_tlep[2*pdfind]->Fill(gtlep_vector.Rapidity(),weight);   

     //cout<<"mmmmmmmmmmmmmmmmmmmmmmmmmmmm"<<"333333333333333333333333333"<<endl;
	h_m_t[2*pdfind]->Fill(gthad_vector.M(),weight); 
	h_m_t[2*pdfind]->Fill(gtlep_vector.M(),weight);   

	h_pt_t[2*pdfind]->Fill(gthad_vector.Pt(),weight); 
	h_pt_t[2*pdfind]->Fill(gtlep_vector.Pt(),weight);   

	h_m_t_fixbin[2*pdfind]->Fill(gthad_vector.M(),weight); 
	h_m_t_fixbin[2*pdfind]->Fill(gtlep_vector.M(),weight);   

	h_pt_t_fixbin[2*pdfind]->Fill(gthad_vector.Pt(),weight); 
	h_pt_t_fixbin[2*pdfind]->Fill(gtlep_vector.Pt(),weight);   

	h_y_t[2*pdfind]->Fill(gthad_vector.Rapidity(),weight); 
	h_y_t[2*pdfind]->Fill(gtlep_vector.Rapidity(),weight);   


	h_nu_pz[2*pdfind]->Fill(st01_nu_vector.Pz(),weight);
	h_nu_pt[2*pdfind]->Fill(st01_nu_vector.Pt(),weight);

     //cout<<"nnnnnnnnnnnnnnnnnnnnnnnnnnnnn"<<endl;
	h_njet_bb[2*pdfind]->Fill(gnjet_bb,weight);
	h_njet_15_ttbar[2*pdfind]->Fill(Gjet_vector_1530.size()+Gjet_vector.size()+GBjet_vector.size()-4,weight);
	if(gnjet_bb>=1)h_profile_deta_bb_njet_bb[2*pdfind]->Fill(gdeltaetabb,gnjet_bb,weight);
	if((Gjet_vector_1530.size()+Gjet_vector.size()+GBjet_vector.size())>=5)h_profile_deta_bb_njet_extra[2*pdfind]->Fill(gdeltaetabb,Gjet_vector_1530.size()+Gjet_vector.size()+GBjet_vector.size()-4,weight);
//	h_ljet_pt[2*pdfind]->Fill(Gjet_vector[j1ind].Pt(),weight);
//	h_ljet_eta[2*pdfind]->Fill(Gjet_vector[j1ind].Eta(),weight);    

//	h_sljet_pt[2*pdfind]->Fill(Gjet_vector[j2ind].Pt(),weight);
//	h_sljet_eta[2*pdfind]->Fill(Gjet_vector[j2ind].Eta(),weight);  


	h_lbjet_pt[2*pdfind]->Fill(GBjet_vector[0].Pt(),weight);
	h_lbjet_eta[2*pdfind]->Fill(GBjet_vector[0].Eta(),weight);    

	h_slbjet_pt[2*pdfind]->Fill(GBjet_vector[1].Pt(),weight);
	h_slbjet_eta[2*pdfind]->Fill(GBjet_vector[1].Eta(),weight);  

//	h_dijet_mass[2*pdfind]->Fill((Gjet_vector[j1ind]+Gjet_vector[j2ind]).M(),weight);  
//	h_dijet_mass_narrow[2*pdfind]->Fill((Gjet_vector[j1ind]+Gjet_vector[j2ind]).M(),weight);  


	//	h_met_meas[2*pdfind]->Fill(mett.Pt(),weight);


	h_m_ttbar[2*pdfind]->Fill(gttbar_vector.M(),weight);
	h_m_ttbar_fixbin[2*pdfind]->Fill(gttbar_vector.M(),weight);
	h_y_ttbar[2*pdfind]->Fill(gttbar_vector.Rapidity(),weight);
	h_y_top[2*pdfind]->Fill(gtop_vector.Rapidity(),weight);
	h_y_atop[2*pdfind]->Fill(gatop_vector.Rapidity(),weight);
	h_phi_ttbar[2*pdfind]->Fill(gttbar_vector.Phi(),weight);
	////cout<<gttbar_vector.Phi()<<endl;

	h_njet_ttbar[2*pdfind]->Fill(Gjet_vector.size()+GBjet_vector.size(),weight);
      }
    }
    }



     //cout<<"ooooooooooooooooooooooooooooooooooooooo"<<endl;

    // if(dosignal &&st1mu!=1 ) continue;
    // if(dottother &&st1mu==1 )continue;
    ////cout<<"kkkkkkkkkkkkkkkkkkkkkkkkkk"<<endl;
    // //cout<<st1mu<<endl;

    ////cout<<"tttttttttttttttt"<<endl;
    if(!realdata && PU_npT>0){    
      //        wtot_write-=w;
      w*=puWeight.weight(int(PU_npT)); 

      sum_tot_weight+= puWeight.weight(int(PU_npT));
      sum_no++;
      //        wtot_write+=w;
    }
    h_puweight[0]->Fill(puWeight.weight(int(PU_npT)));
    h_puweight_weighted[0]->Fill(puWeight.weight(int(PU_npT)),w);
    wtot+=wtot_write;
    ////cout<<"aaaaaaaaaaaaaaaaaaaaaaa"<<endl;
    if(!HLT_IsoTkMu20&&!HLT_IsoMu20) continue; //OR requirement of IsoTkMu20 and IsoMu20
    for(unsigned int mu_ind=0; mu_ind<patMuonPt_->size();mu_ind++){
      if(patMuonCombId_->at(mu_ind)>0&& fabs(patMuonEta_->at(mu_ind))<2.1){
	h_mu_pt[0]->Fill(patMuonPt_->at(mu_ind),w);
	h_mu_eta[0]->Fill(patMuonEta_->at(mu_ind),w);
	h_mu_phi[0]->Fill(patMuonPhi_->at(mu_ind),w);
	h_mu_iso[0]->Fill(patMuonPfIsoDbeta_->at(mu_ind),w);
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
    ////cout<<"2222222222"<<endl;
    int ind_jet_const=0;
    double csvmax=-99., csvmax2=-99.;
    for(unsigned int jet_ind=0; jet_ind<patJetPfAk04Pt_->size();jet_ind++){
      if(jet_ind>=1)ind_jet_const+=patJetPfAk04nconst_->at(jet_ind-1);
      if( fabs(patJetPfAk04Eta_->at(jet_ind))>2.4 ||patJetPfAk04LooseId_->at(jet_ind)==0)continue;

      double new_en=(1+ jes*unc_->at(jet_ind))*patJetPfAk04En_->at(jet_ind);
      double new_pt=(1+ jes*unc_->at(jet_ind))*patJetPfAk04Pt_->at(jet_ind);

      TLorentzVector tmp;
      tmp.SetPtEtaPhiE(new_pt,patJetPfAk04Eta_->at(jet_ind),patJetPfAk04Phi_->at(jet_ind),new_en);

      double dr_j_l=99;
      if(mu_index>0) dr_j_l=DeltaR(tmp.Eta(),mu_vector[0].Eta(),tmp.Phi(),mu_vector[0].Phi());

      if(dr_j_l<0.4)continue;
      if(new_pt>15.)njet_15++;
      if(new_pt>15. &&new_pt<30.)jet_vector_1530.push_back(tmp);
      if(new_pt<30.)continue;
      jet_vector.push_back(tmp);
      //jet_part_flav.push_back(patJetPfAk04PartonFlavour_->at(jet_ind));
      if(mu_index==1 &&mu_index20==1)h_csv[0]->Fill(patJetPfAk04BDiscCSVv2_->at(jet_ind),w);
      if(patJetPfAk04BDiscCSVv2_->at(jet_ind)>0.89)b_jet_index.push_back(jet_index);
      // //cout<<"nconst "<<jet_ind<<" "<<patJetPfAk04nconst_->at(jet_ind)<<"  "<<patJetPfAk04ConstId->size()<<endl;

      if(patJetPfAk04BDiscCSVv2_->at(jet_ind)>csvmax)csvmax=patJetPfAk04BDiscCSVv2_->at(jet_ind);
      if(patJetPfAk04BDiscCSVv2_->at(jet_ind)>csvmax2 && patJetPfAk04BDiscCSVv2_->at(jet_ind)<csvmax)csvmax2=patJetPfAk04BDiscCSVv2_->at(jet_ind);

      vector<double>tmp1;
      vector<double>tmp2;
      vector<double>tmp3;
      vector<double>tmp4;
      vector<double>tmp5;


      for(unsigned int jet_const_ind=0;jet_const_ind< patJetPfAk04nconst_->at(jet_ind);jet_const_ind++){
	////cout<<ind_jet_const<<"  "<<jet_const_ind<<"  "<<ind_jet_const+jet_const_ind<<endl;
	//          //cout<<patJetPfAk04ConstPt->at(ind_jet_const+jet_const_ind)<<endl;
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
      double jet_eff=-99;
      if(dosignal){
	// //cout<<patJetPfAk04PartonFlavour_->at(jet_ind)<<endl;
	//    //cout<<BTagEntry::FLAV_B (0)<<"  "<<BTagEntry::FLAV_C (1)<<"  "<<	BTagEntry::FLAV_UDSG (2)<<endl;
	if (new_pt < 670. ) {
	  if(fabs(patJetPfAk04PartonFlavour_->at(jet_ind))==5){
	    jet_scalefactor = reader.eval(BTagEntry::FLAV_B, patJetPfAk04Eta_->at(jet_ind),new_pt); 
	    jet_eff = reader2.eval(BTagEntry::FLAV_B, patJetPfAk04Eta_->at(jet_ind),new_pt); 
	  }
	  else if(fabs(patJetPfAk04PartonFlavour_->at(jet_ind))==4){
	    jet_scalefactor = reader.eval(BTagEntry::FLAV_C, patJetPfAk04Eta_->at(jet_ind),new_pt); 
	    jet_eff = reader2.eval(BTagEntry::FLAV_C, patJetPfAk04Eta_->at(jet_ind),new_pt); 
	  }   
	  else{
	    //         jet_scalefactor = reader.eval(BTagEntry::FLAV_UDSG, patJetPfAk04Eta_->at(jet_ind),new_pt); 
	    // jet_scalefactor =1;
	    jet_scalefactor = reader.eval(BTagEntry::FLAV_C, patJetPfAk04Eta_->at(jet_ind),new_pt); //no udsg SF in the csv table, use C for now.
	    //  //cout<<BTagEntry::FLAV_UDSG<<endl;
	    //  //cout<<reader.eval(BTagEntry::FLAV_C, patJetPfAk04Eta_->at(jet_ind),new_pt) <<"  "<<reader.eval(BTagEntry::FLAV_B, patJetPfAk04Eta_->at(jet_ind),new_pt)<<endl; 
	    jet_eff = reader2.eval(BTagEntry::FLAV_UDSG, patJetPfAk04Eta_->at(jet_ind),new_pt); 
	  }
	}
	else {  // for error evaluation outside bounds:
	  //const TF1* sfFunc = reader.getFunction(BTagEntry::FLAV_B, 2.399, 669.);

	  if(fabs(patJetPfAk04PartonFlavour_->at(jet_ind))==5){
	    jet_scalefactor = reader.eval(BTagEntry::FLAV_B, patJetPfAk04Eta_->at(jet_ind),669); 
	    jet_eff = reader2.eval(BTagEntry::FLAV_B, patJetPfAk04Eta_->at(jet_ind),669); 
	  }
	  else if(fabs(patJetPfAk04PartonFlavour_->at(jet_ind))==4){
	    jet_scalefactor = reader.eval(BTagEntry::FLAV_C, patJetPfAk04Eta_->at(jet_ind),669); 
	    jet_eff = reader2.eval(BTagEntry::FLAV_C, patJetPfAk04Eta_->at(jet_ind),669); 
	  }
	  else{
	    //         jet_scalefactor = reader.eval(BTagEntry::FLAV_UDSG, patJetPfAk04Eta_->at(jet_ind),669); 
	    //   //cout<<BTagEntry::FLAV_UDSG<<endl;
	    //jet_scalefactor =1;
	    jet_scalefactor = reader.eval(BTagEntry::FLAV_C, patJetPfAk04Eta_->at(jet_ind),669); //no udsg SF in the csv table, use C for now.
	    jet_eff = reader2.eval(BTagEntry::FLAV_UDSG, patJetPfAk04Eta_->at(jet_ind),669); 
	  }
	}
	////cout<<jet_scalefactor<<endl;

	//  double eff_b=0.640272;
	//  double eff_l=0.024801;
	if(patJetPfAk04BDiscCSVv2_->at(jet_ind)>0.89)nom*=jet_scalefactor*jet_eff;
	if(patJetPfAk04BDiscCSVv2_->at(jet_ind)<0.89)nom*=1 - (jet_scalefactor*jet_eff);

	if(patJetPfAk04BDiscCSVv2_->at(jet_ind)>0.89)denom*=jet_eff;
	if(patJetPfAk04BDiscCSVv2_->at(jet_ind)<0.89)denom*=(1 - (jet_eff));







	//calculate b-tag efficiencies 

	if(fabs(patJetPfAk04PartonFlavour_->at(jet_ind))==5){
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
	    h_pt_eta_b[0]->Fill(new_pt,patJetPfAk04Eta_->at(jet_ind),w);
	    if(patJetPfAk04BDiscCSVv2_->at(jet_ind)>0.89){
	      mu_tot_b_tagged_jet++;
	      h_pt_eta_b_tagged[0]->Fill(new_pt,patJetPfAk04Eta_->at(jet_ind),w);
	    }
	  }

	  else if(fabs(patJetPfAk04PartonFlavour_->at(jet_ind))==4){
	    mu_tot_c_jet++;
	    h_pt_eta_c[0]->Fill(new_pt,patJetPfAk04Eta_->at(jet_ind),w);
	    if(patJetPfAk04BDiscCSVv2_->at(jet_ind)>0.89){
	      mu_tot_c_tagged_jet++;
	      h_pt_eta_c_tagged[0]->Fill(new_pt,patJetPfAk04Eta_->at(jet_ind),w);    
	    }        
	  }
	  else {
	    mu_tot_udsg_jet++;
	    h_pt_eta_udsg[0]->Fill(new_pt,patJetPfAk04Eta_->at(jet_ind),w);
	    if(patJetPfAk04BDiscCSVv2_->at(jet_ind)>0.89){
	      mu_tot_udsg_tagged_jet++;
	      h_pt_eta_udsg_tagged[0]->Fill(new_pt,patJetPfAk04Eta_->at(jet_ind),w);    
	    }
	  }



	}
      }

    }
    double btagweight=nom/denom;

    if(!realdata)w*=btagweight;
    if(!(jet_vector.size()>=4 && b_jet_index.size()==2 && mu_index==1 &&mu_index20==1)){
      if(gn_pf!=0){


//        cout<<"reco nmu, njet, nbjet "<<mu_index<<"  "<<jet_vector.size()<<"  "<<b_jet_index.size()<<endl;
//        cout<<"gen nmu, njet, nbjet "<<1<<"  "<<Gjet_vector.size()+GBjet_vector.size()<<"  "<<GBjet_vector.size()<<endl;
        h_miss_mult[0]->Fill(gn_pf,w);
        h_miss_sumpt[0]->Fill(gptsum_pf,w);
        h_miss_avept[0]->Fill(gptsum_pf/gn_pf,w);
        for(unsigned int gpindd=0; gpindd<vector_vector_gp.size();gpindd++){
          h_miss_pt[0]->Fill(vector_vector_gp[gpindd].Pt(),w);
          h_miss_eta[0]->Fill(vector_vector_gp[gpindd].Eta(),w);
        }
      }
    }
    if(jet_vector.size()>=4 && mu_index==1 &&mu_index20==1){
      h_n_bjet[0]->Fill(b_jet_index.size(),w);
      h_csvmax[0]->Fill(csvmax,w);
      h_csvmax2[0]->Fill(csvmax2,w);
    }
    if (jet_vector.size()>=4 && b_jet_index.size()==2 && mu_index==1 &&mu_index20==1){//at least 4 jets, 2 of b jets, 1 muon
      ntottt++;
      //      if(!realdata)//cout<<btagweight<<endl;
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
      h_puweight_meas[0]->Fill(puWeight.weight(int(PU_npT)));
      h_puweight_weighted_meas[0]->Fill(puWeight.weight(int(PU_npT)),w);


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

      //////cout<<MTW<<endl;

      TLorentzVector nu_complex;
      bool found=false;  
      if((B-C)<0){
	////cout<<"new complex event "<<MTW<<endl;

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
	    if(MTW_new1>80.399&&MTW_new1<80.401){////cout<<"MTW old, px var +, py var +, MTW new "<<MTW<<"  "<<px_var<<"  "<<py_var<<"  "<<MTW_new1<<endl;
	      double ptnun=met_new1.Pt();
	      double mun= MW*MW/2 + ptl*ptnun*cdphi_new1;
	      double An=mun*pzl/(ptl*ptl);
	      //double Bn=mun*mun*pzl*pzl/(pow(ptl,4));
	      //double Cn= (El*El*ptnun*ptnun- mun*mun)/(ptl*ptl);
	      //double Dn=0;
	      ////cout<<"B, C, B-C old; B, C, B-C new"<<B<<"  "<<C<<"  "<<B-C<<"  "<<Bn<<"  "<<Cn<<"  "<<Bn-Cn<<endl;
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
	    if(MTW_new2>80.399&&MTW_new2<80.401){////cout<<"MTW old, px var +, py var -, MTW new "<<MTW<<"  "<<px_var<<"  "<<py_var<<"  "<<MTW_new2<<endl;
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
      unsigned int ljet_ind1=99, ljet_ind2=99, extra_jet_index=99/*,extra_jet_index_1530=99*/;
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


      TLorentzVector  ttbar_tmp=thad+tlep;



      double etab1=jet_vector[b_jet_index[0]].Eta();
      double etab2=jet_vector[b_jet_index[1]].Eta();
      double etamin=0;
      if(etab1<etab2)etamin=etab1;
      else etamin=etab2;
      double deltaetabb=fabs(etab1-etab2);
      int njet_bb=0;
      int njet_transverse=0;
      int njet_away=0;
      int njet_toward=0;

      int njet_transverse15=0;
      int njet_away15=0;
      int njet_toward15=0;
      for(unsigned int j_ind=0; j_ind<jet_vector.size();j_ind++){

	if(j_ind==b_jet_index[0]|| j_ind==b_jet_index[1]||j_ind==ljet_ind1 ||j_ind==ljet_ind2)continue;
	//cout<<fabs(DeltaPhi(ttbar_tmp.Phi(),jet_vector[j_ind].Phi()))<<endl;           
	//           if(fabs(jet_vector[j_ind].Eta())<fabs(etab1) &&fabs(jet_vector[j_ind].Eta())<fabs(etab2) )njet_bb++;
	double dphi=fabs(DeltaPhi(ttbar_tmp.Phi(),jet_vector[j_ind].Phi()))*180/pi;
	if(dphi<60.)njet_toward++;
	if(dphi>60. &&dphi<120.)njet_transverse++;
	if(dphi>120. &&dphi<180.)njet_away++;

	if(dphi<60.)njet_toward15++;
	if(dphi>60. &&dphi<120.)njet_transverse15++;
	if(dphi>120. &&dphi<180.)njet_away15++;


	if(jet_vector[j_ind].Eta()>etamin && jet_vector[j_ind].Eta()<etamin+deltaetabb ) njet_bb++;
      }
      for(unsigned int jet_vector_1530_ind =0; jet_vector_1530_ind<jet_vector_1530.size();jet_vector_1530_ind++){
	if(jet_vector_1530[jet_vector_1530_ind].Eta()>etamin && jet_vector_1530[jet_vector_1530_ind].Eta()<etamin+deltaetabb ) njet_bb++;
	//      cout<<fabs(DeltaPhi(ttbar_tmp.Phi(),jet_vector_1530[jet_vector_1530_ind].Phi()))<<endl;           
	double dphi=fabs(DeltaPhi(ttbar_tmp.Phi(),jet_vector_1530[jet_vector_1530_ind].Phi()))*180/pi;
	if(dphi<60.)njet_toward15++;
	if(dphi>60. &&dphi<120.)njet_transverse15++;
	if(dphi>120. &&dphi<180.)njet_away15++;


      }


      //      if(extra_jet_index==99 &&jet_vector_1530.size()>0 )extra_jet_index_1530=0;


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
      } 
      TLorentzVector mett;
      mett.SetPxPyPzE(METPx->at(1),METPy->at(1),METPz->at(1),METE->at(1));
      TLorentzVector ttbar= mu_vector[0] +jet_vector[ljet_ind1]+jet_vector[ljet_ind2]+jet_vector[b_jet_index[0]]+jet_vector[b_jet_index[1]]+mett;
      h_pt_ttbar[0]->Fill((ttbar).Pt(),w);
      ttbar=thad+tlep;
      vector<TLorentzVector> recpart_vector;
      vector<int>recpart_charge;
      for(unsigned int pfind =0; pfind<patPfCandPt->size();pfind++){

	if(patPfCandPt->at(pfind)>0.5 ){

	  h_pf_dxy[0]->Fill(fabs(patPfCandDxy->at(pfind)),w);
	  h_pf_dz[0]->Fill(fabs(patPfCandDz->at(pfind)),w);
	  h_pf_sigmadxy[0]->Fill(fabs(patPfCandDxy->at(pfind)/patPfCandDxyerr->at(pfind)),w);
	  h_pf_sigmadz[0]->Fill(fabs(patPfCandDz->at(pfind)/patPfCandDzerr->at(pfind)),w);
	}
//	if(patPfCandPt->at(pfind)<0.5 ||patPfCandFromPv->at(pfind)<2||fabs(patPfCandDxy->at(pfind))>1 ||fabs(patPfCandDz->at(pfind))>3 ||patPfCandEta->at(pfind)>2.1) continue;

        
        if(patPfCandPt->at(pfind)<0.5 ||patPfCandEta->at(pfind)>2.1||
        !(patPfpvAssociationQuality->at(pfind)>4 && patPfCandVertexRef->at(pfind)==0 &&patPfCandTrackHighPurity->at(pfind)!=0 /*&&
        ((patPfCandDxyerr->at(pfind)==0&& patPfCandDzerr->at(pfind)==0) ||(fabs(patPfCandDxy->at(pfind)/patPfCandDxyerr->at(pfind))<15. &&fabs(patPfCandDz->at(pfind)/patPfCandDzerr->at(pfind))<15.)) */))continue;

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
         //   jet_ConstId[array_jetind[jettt]][jetpfind]!=
	    if(deltar_pf_jetpf<dr_pf_jetpf_min)dr_pf_jetpf_min=deltar_pf_jetpf;

	  }
	}
	/*
	  int ind_jet_constt=0;
	  for(unsigned int jet_ind=0; jet_ind<patJetPfAk04Pt_->size();jet_ind++){
	  if(jet_ind>=1)ind_jet_constt+=patJetPfAk04nconst_->at(jet_ind-1);
	  if(new_pt<15. || fabs(patJetPfAk04Eta_->at(jet_ind))>2.5)continue;
	  for(unsigned int jet_const_ind=0;jet_const_ind< patJetPfAk04nconst_->at(jet_ind);jet_const_ind++){
	  double deltar_alljet_pf=DeltaR(patJetPfAk04ConstEta->at(ind_jet_constt+jet_const_ind),patPfCandEta->at(pfind),patJetPfAk04ConstPhi->at(ind_jet_constt+jet_const_ind),patPfCandPhi->at(pfind));
	  if(deltar_alljet_pf<dr_min_alljet_pf)dr_min_alljet_pf=deltar_alljet_pf;
	  }
	  }
	*/
	h_deltar_pf_jetpf[0]->Fill(dr_pf_jetpf_min,w);
	h_deltar_pf_jet[0]->Fill(dr_pf_jet_min,w);
	deltar_pf_mu=  DeltaR(patPfCandEta->at(pfind),mu_vector[0].Eta(),patPfCandPhi->at(pfind),mu_vector[0].Phi()); 
	h_deltar_pf_mu[0]->Fill(deltar_pf_mu,w); 
	//if(dr_pf_jetpf_min<0.05 ||deltar_pf_mu<0.05 /*||dr_min_alljet_pf<0.4*/)continue;
	h_deltar_pf_jet_after[0]->Fill(dr_pf_jet_min,w);
	n_pf++;
	ptsum_pf+=patPfCandPt->at(pfind);
	double deltaphi_tt_pf=DeltaPhi(ttbar.Phi(),patPfCandPhi->at(pfind))*180/pi;
	h_dphi_ttbar_pf[0]->Fill(deltaphi_tt_pf,w);
	h_pf_pt[0]->Fill(patPfCandPt->at(pfind),w);
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
	TLorentzVector tmprecpart_vector;
	tmprecpart_vector.SetPtEtaPhiE(patPfCandPt->at(pfind),patPfCandEta->at(pfind),patPfCandPhi->at(pfind),patPfCandE->at(pfind));
	recpart_vector.push_back(tmprecpart_vector);
	recpart_charge.push_back(patPfCandCharge->at(pfind));
	double drmin_gen_rec=99999.;
	for(unsigned int gp_ind=0;gp_ind<Packed01Id->size();gp_ind++){    

	  if(Packed01Pt->at(gp_ind)<0.5 ||Packed01Eta->at(gp_ind)>2.1||Packed01Charge->at(gp_ind)==0 ||Packed01Charge->at(gp_ind)!=patPfCandCharge->at(pfind) ) continue;

	  double dr_gen_rec=DeltaR(Packed01Eta->at(gp_ind),patPfCandEta->at(pfind),Packed01Phi->at(gp_ind),patPfCandPhi->at(pfind));
	  if(dr_gen_rec<drmin_gen_rec)drmin_gen_rec=dr_gen_rec;
	  //          h_dr_rec_gen_part->Fill(dr_gen_rec);  
	}
	//        h_drmin_rec_gen_part->Fill(drmin_gen_rec);  
      }//pf loop
      if(n_pf==0){
      if(gn_pf!=0){
        h_miss_mult[1]->Fill(gn_pf,w);
        h_miss_sumpt[1]->Fill(gptsum_pf,w);
        h_miss_avept[1]->Fill(gptsum_pf/gn_pf,w);
        for(unsigned int gpindd=0; gpindd<vector_vector_gp.size();gpindd++){
          h_miss_pt[1]->Fill(vector_vector_gp[gpindd].Pt(),w);
          h_miss_eta[1]->Fill(vector_vector_gp[gpindd].Eta(),w);
        }
      }
      }

      int gn_pf_matched=0;
      double gpt_pf_matched=0;
      /* for(unsigned int gp_ind=0;gp_ind<Packed01Id->size();gp_ind++){    

	 if(Packed01Pt->at(gp_ind)<0.5 ||Packed01Eta->at(gp_ind)>2.1||Packed01Charge->at(gp_ind)==0  ) continue;
	 double drmin_gen_rec=99999.;
	 double drmin_gen_rec_samecharge=99999.;
	 double drmin_gen_rec_oppcharge=99999.;
	 for(unsigned int recvecind=0; recvecind<recpart_vector.size();recvecind++){
	 double dr_gen_rec=DeltaR(Packed01Eta->at(gp_ind),recpart_vector[recvecind].Eta(),Packed01Phi->at(gp_ind),recpart_vector[recvecind].Phi());
	 if(dr_gen_rec<drmin_gen_rec)drmin_gen_rec=dr_gen_rec;
	 h_dr_rec_gen_part->Fill(dr_gen_rec);  
	 if(Packed01Charge->at(gp_ind)==recpart_charge[recvecind]){
	 if(dr_gen_rec<drmin_gen_rec_samecharge)drmin_gen_rec_samecharge=dr_gen_rec;
	 h_dr_rec_gen_part_samecharge->Fill(dr_gen_rec);  
	 }
	 if(Packed01Charge->at(gp_ind)!=recpart_charge[recvecind]){
	 if(dr_gen_rec<drmin_gen_rec_oppcharge)drmin_gen_rec_oppcharge=dr_gen_rec;
	 h_dr_rec_gen_part_oppcharge->Fill(dr_gen_rec);  
	 }

	 }
	 h_drmin_rec_gen_part->Fill(drmin_gen_rec);  
	 h_drmin_rec_gen_part_samecharge->Fill(drmin_gen_rec_samecharge);    
	 if(drmin_gen_rec_samecharge<0.05){ 
	 gn_pf_matched++;
	 gpt_pf_matched+=Packed01Pt->at(gp_ind);   
	 }
	 h_drmin_rec_gen_part_oppcharge->Fill(drmin_gen_rec_oppcharge);                
	 }

	 if(gn_pf_matched!=0){
	 h_1d_npf[2]->Fill(gn_pf_matched/4.);
	 h_ptsumpf_inclusive[2]->Fill(gpt_pf_matched);
	 if(n_pf!=0)h_2d_npf[2]->Fill(n_pf/4.,gn_pf_matched/4.);
	 }*/


      double drgenjetrecjet1min=9999, drgenjetrecjet2min=9999, drgenjetrecjetb1min=9999, drgenjetrecjetb2min=9999;
      unsigned int gljMind1=99,  gljMind2=99, gljMindb1=99, gljMindb2=99;
      unsigned int const_size2=0;
      vector<vector<TLorentzVector>> GMjetconst_vector;
      for(unsigned int gj_ind=0;gj_ind<GjPt->size();gj_ind++){
	if(gj_ind!=0)const_size2+=GjNConst->at(gj_ind-1);
	double DRjet_genjet1 =DeltaR(Gjeta->at(gj_ind),jet_vector[ljet_ind1].Eta(),Gjphi->at(gj_ind),jet_vector[ljet_ind1].Phi());
	double DRjet_genjet2 =DeltaR(Gjeta->at(gj_ind),jet_vector[ljet_ind2].Eta(),Gjphi->at(gj_ind),jet_vector[ljet_ind2].Phi());
	double DRjet_genjetb1=DeltaR(Gjeta->at(gj_ind),jet_vector[b_jet_index[0]].Eta(),Gjphi->at(gj_ind),jet_vector[b_jet_index[0]].Phi());
	double DRjet_genjetb2=DeltaR(Gjeta->at(gj_ind),jet_vector[b_jet_index[1]].Eta(),Gjphi->at(gj_ind),jet_vector[b_jet_index[1]].Phi());
	h_dr_rec_gen_j1->Fill(DRjet_genjet1);  
	h_dr_rec_gen_j2->Fill(DRjet_genjet2);  
	h_dr_rec_gen_bj1->Fill(DRjet_genjetb1);  
	h_dr_rec_gen_bj2->Fill(DRjet_genjetb2);  


	vector<TLorentzVector> Gjetconst_vectortmp;
	for(unsigned int gj=0; gj<GjNConst->at(gj_ind); gj++){

	  if(GjConstPt->at(gj+const_size2)<0.5)continue;
	  TLorentzVector tmpc;
	  tmpc.SetPtEtaPhiE(GjConstPt->at(gj+const_size2),GjConstEta->at(gj+const_size2),GjConstPhi->at(gj+const_size2),GjConstE->at(gj+const_size2));
	  Gjetconst_vectortmp.push_back(tmpc);
	}



	if(DRjet_genjet1<drgenjetrecjet1min && DRjet_genjet1<0.1){
	  drgenjetrecjet1min=DRjet_genjet1; gljMind1=gj_ind;
	}

	if(DRjet_genjet2<drgenjetrecjet2min && DRjet_genjet2<0.1){
	  drgenjetrecjet2min=DRjet_genjet2; gljMind2=gj_ind;
	}

	if(DRjet_genjetb1<drgenjetrecjetb1min && DRjet_genjetb1<0.1){
	  drgenjetrecjetb1min=DRjet_genjetb1; gljMindb1=gj_ind;
	}

	if(DRjet_genjetb2<drgenjetrecjetb2min && DRjet_genjetb2<0.1){
	  drgenjetrecjetb2min=DRjet_genjetb2; gljMindb2=gj_ind;
	}
	GMjetconst_vector.push_back(Gjetconst_vectortmp);
      }
      //      cout<<gljMind1<<" "<<gljMind2<<" "<<gljMindb1<<" "<<gljMindb2<<" "<<endl;

      /*
	for(unsigned int gp_ind=0;gp_ind<Packed01Id->size();gp_ind++){    




	}
      */

      if(gljMind1!=99 && gljMind2!=99 &&gljMindb1!=99 && gljMindb2!=99 ){

	for(unsigned int gp_ind=0;gp_ind<Packed01Id->size();gp_ind++){    

	  if(Packed01Pt->at(gp_ind)<0.5 ||Packed01Eta->at(gp_ind)>2.1||Packed01Charge->at(gp_ind)==0  ) continue;


	  if(lind!=9999){
	    double dr_gen_mu=DeltaR(Packed01Eta->at(gp_ind),st01_mu_vector.Eta(),Packed01Phi->at(gp_ind),st01_mu_vector.Phi());
	    if(dr_gen_mu<0.1)continue;
	  }
	  bool matchjet=false;
	  for(unsigned int const_gen_ind=0;const_gen_ind<GMjetconst_vector[gljMind1].size();const_gen_ind++){
	    double dr_gen_j1=DeltaR(Packed01Eta->at(gp_ind),GMjetconst_vector[gljMind1][const_gen_ind].Eta(),Packed01Phi->at(gp_ind),GMjetconst_vector[gljMind1][const_gen_ind].Phi());
	    if(dr_gen_j1<0.1){
	      matchjet=true;break;
	    }    
	  }

	  for(unsigned int const_gen_ind=0;const_gen_ind<GMjetconst_vector[gljMind2].size();const_gen_ind++){
	    double dr_gen_j1=DeltaR(Packed01Eta->at(gp_ind),GMjetconst_vector[gljMind2][const_gen_ind].Eta(),Packed01Phi->at(gp_ind),GMjetconst_vector[gljMind2][const_gen_ind].Phi());
	    if(dr_gen_j1<0.1){
	      matchjet=true;break;
	    }
	  }

	  for(unsigned int const_gen_ind=0;const_gen_ind<GMjetconst_vector[gljMindb1].size();const_gen_ind++){
	    double dr_gen_j1=DeltaR(Packed01Eta->at(gp_ind),GMjetconst_vector[gljMindb1][const_gen_ind].Eta(),Packed01Phi->at(gp_ind),GMjetconst_vector[gljMindb1][const_gen_ind].Phi());
	    if(dr_gen_j1<0.1){
	      matchjet=true;break;
	    }

	  }

	  for(unsigned int const_gen_ind=0;const_gen_ind<GMjetconst_vector[gljMindb2].size();const_gen_ind++){
	    double dr_gen_j1=DeltaR(Packed01Eta->at(gp_ind),GMjetconst_vector[gljMindb2][const_gen_ind].Eta(),Packed01Phi->at(gp_ind),GMjetconst_vector[gljMindb2][const_gen_ind].Phi());
	    if(dr_gen_j1<0.1){
	      matchjet=true;break;
	    }
	  }
	  if(matchjet) continue;








	  double drmin_gen_rec=99999.;
	  double drmin_gen_rec_samecharge=99999.;
	  double drmin_gen_rec_oppcharge=99999.;

	  for(unsigned int recvecind=0; recvecind<recpart_vector.size();recvecind++){
	    double dr_gen_rec=DeltaR(Packed01Eta->at(gp_ind),recpart_vector[recvecind].Eta(),Packed01Phi->at(gp_ind),recpart_vector[recvecind].Phi());
	    if(dr_gen_rec<drmin_gen_rec)drmin_gen_rec=dr_gen_rec;
	    h_dr_rec_gen_part->Fill(dr_gen_rec);  
	    if(Packed01Charge->at(gp_ind)==recpart_charge[recvecind]){
	      if(dr_gen_rec<drmin_gen_rec_samecharge)drmin_gen_rec_samecharge=dr_gen_rec;
	      h_dr_rec_gen_part_samecharge->Fill(dr_gen_rec);  
	    }
	    if(Packed01Charge->at(gp_ind)!=recpart_charge[recvecind]){
	      if(dr_gen_rec<drmin_gen_rec_oppcharge)drmin_gen_rec_oppcharge=dr_gen_rec;
	      h_dr_rec_gen_part_oppcharge->Fill(dr_gen_rec);  
	    }

	  }
	  h_drmin_rec_gen_part->Fill(drmin_gen_rec);  
	  h_drmin_rec_gen_part_samecharge->Fill(drmin_gen_rec_samecharge);    

	  //        if(drmin_gen_rec_samecharge<0.05){ 
	  gn_pf_matched++;
	  gpt_pf_matched+=Packed01Pt->at(gp_ind);   
	  //        }
	  h_drmin_rec_gen_part_oppcharge->Fill(drmin_gen_rec_oppcharge);                
	}
      }

      if(gn_pf!=0&& n_pf!=0){
	  h_1d_npf[2]->Fill(gn_pf,w);
	  h_1d_ptsumpf[2]->Fill(gptsum_pf,w);
	  h_1d_ptavepf[2]->Fill(gptsum_pf/gn_pf,w);
	//h_ptsumpf_inclusive[2]->Fill(gpt_pf_matched);
	  h_2d_npf[2]->Fill(n_pf,gn_pf_matched,w);
	  h_2d_ptsumpf[2]->Fill(ptsum_pf,gptsum_pf,w);
  	  h_2d_ptavepf[2]->Fill(ptsum_pf/n_pf,gptsum_pf/gn_pf,w);

	  h_1d_npf[3]->Fill(n_pf,w);
	  h_1d_ptsumpf[3]->Fill(ptsum_pf,w);
	  h_1d_ptavepf[3]->Fill(ptsum_pf/n_pf,w);

      }



     






      //cout<<n_pf<<"  "<<n_pf_dphi[0]<<"  "<<ptsum_pf_dphi[0]<<endl;
      TLorentzVector ttj_vector;
      if(extra_jet_index!=99)ttj_vector=top_vector +atop_vector+jet_vector[extra_jet_index];
      //      if(extra_jet_index==99 &&extra_jet_index_1530!=99 )ttj_vector=top_vector +atop_vector+jet_vector_1530[extra_jet_index_1530];

      //filling for pdf weights

      for(int pdfind=0; pdfind<pdfind_max;pdfind++){
	// if(pdfind!=0)cout<<mcWeights_->at(8+pdfind)<<endl;
	double weight=w;
        if(pdfind>0)continue;
	if(dopdf&& pdfind!=0)weight=w*mcWeights_->at(8+pdfind);
          

	if(!dopdf&&pdfind!=0 &&puWeight.weight(int(PU_npT))!=0 )weight=puUp.weight(int(PU_npT))*w/puWeight.weight(int(PU_npT)); 

	h_npf_inclusive[2*pdfind +1]->Fill(n_pf,weight);
	h_npf_toward[2*pdfind +1]->Fill(n_pf_toward,weight);
	h_npf_transverse[2*pdfind +1]->Fill(n_pf_transverse,weight);
	h_npf_away[2*pdfind +1]->Fill(n_pf_away,weight);

	h_ptsumpf_inclusive[2*pdfind +1]->Fill(ptsum_pf,weight);
	h_ptsumpf_toward[2*pdfind +1]->Fill(ptsum_pf_toward,weight);
	h_ptsumpf_transverse[2*pdfind +1]->Fill(ptsum_pf_transverse,weight);
	h_ptsumpf_away[2*pdfind +1]->Fill(ptsum_pf_away,weight);

	if(n_pf!=0)h_ptavepf_inclusive[2*pdfind +1]->Fill(ptsum_pf/n_pf,weight);
	if(n_pf_toward!=0)h_ptavepf_toward[2*pdfind +1]->Fill(ptsum_pf_toward/n_pf_toward,weight);
	if(n_pf_transverse!=0)h_ptavepf_transverse[2*pdfind +1]->Fill(ptsum_pf_transverse/n_pf_transverse,weight);
	if(n_pf_away!=0)h_ptavepf_away[2*pdfind +1]->Fill(ptsum_pf_away/n_pf_away,weight);




	if(n_pf!=0){
	  h_1d_npf[2*pdfind +1]->Fill(n_pf,weight);
	  h_1d_ptsumpf[2*pdfind +1]->Fill(ptsum_pf,weight);
	  h_1d_ptavepf[2*pdfind +1]->Fill(ptsum_pf/n_pf,weight);
	  if(gn_pf!=0){
	    h_2d_npf[2*pdfind +1]->Fill(n_pf,gn_pf,weight);
	    h_2d_ptsumpf[2*pdfind +1]->Fill(ptsum_pf,gptsum_pf,weight);
	    h_2d_ptavepf[2*pdfind +1]->Fill(ptsum_pf/n_pf,gptsum_pf/gn_pf,weight);
            h_2d_mt[2*pdfind +1]->Fill(ttbar.M(),gttbar_vector.M(),weight);
	  }
	  for(int dphiloop=0;dphiloop<10;dphiloop++){// 10 bins in pt, [0,1000] GeV
	    if(ttbar.Pt()>dphiloop*100. &&ttbar.Pt()<(dphiloop+1)*100. ){
	      //                cout<<ttbar.Pt()<<"  "<<dphiloop*5<<"  "<<n_pf/4<<endl; 
	      if(n_pf<200.)h_1d_ptttbar_npf[2*pdfind +1]->Fill(dphiloop*50.+n_pf/4.,weight);
	      if(n_pf>=200.)h_1d_ptttbar_npf[2*pdfind +1]->Fill(dphiloop*50.+49.9,weight);
	      if(gn_pf!=0){
		for(int gdphiloop=0;gdphiloop<10;gdphiloop++){  
		  if(gttbar_vector.Pt()>gdphiloop*100. &&gttbar_vector.Pt()<(gdphiloop+1)*100. ){
		    if(n_pf&&gn_pf<200)h_2d_ptttbar_npf[2*pdfind +1]->Fill(dphiloop*50.+n_pf/4.,gdphiloop*50.+gn_pf/4.,weight);
		    if(n_pf>=200&&gn_pf>=200)h_2d_ptttbar_npf[2*pdfind +1]->Fill(dphiloop*50.+49.9,gdphiloop*50.+49.9,weight);
		    if(n_pf<200&&gn_pf>=200)h_2d_ptttbar_npf[2*pdfind +1]->Fill(dphiloop*50.+n_pf/4.,gdphiloop*50.+49.9,weight);
		    if(n_pf>=200&&gn_pf<200)h_2d_ptttbar_npf[2*pdfind +1]->Fill(dphiloop*50.+49.9,gdphiloop*50.+gn_pf/4.,weight);
		  }  
		}     
	      }
	    }
	  }


	  for(int dphiloop=0;dphiloop<20;dphiloop++){
	    if(n_pf_dphi[dphiloop]==0)continue;

	    if(n_pf_dphi[dphiloop]<100)h_1d_dphi_npf[2*pdfind +1]->Fill(dphiloop*10.+n_pf_dphi[dphiloop]/10.,weight);
	    if(n_pf_dphi[dphiloop]>=100)h_1d_dphi_npf[2*pdfind +1]->Fill(dphiloop*10.+9.9,weight);

	    if(gn_pf!=0 ){
	      for(int gdphiloop=0;gdphiloop<20;gdphiloop++){
		if(gn_pf_dphi[gdphiloop]==0)continue;
		if(n_pf_dphi[dphiloop]<100 &&gn_pf_dphi[gdphiloop]<100)h_2d_dphi_npf[2*pdfind +1]->Fill(dphiloop*10.+n_pf_dphi[dphiloop]/10.,gdphiloop*10.+gn_pf_dphi[gdphiloop]/10.,weight);
		if(n_pf_dphi[dphiloop]>=100&&gn_pf_dphi[gdphiloop]>=100)h_2d_dphi_npf[2*pdfind +1]->Fill(dphiloop*10.+9.9,gdphiloop*10.+9.9,weight);

		if(n_pf_dphi[dphiloop]<100 &&gn_pf_dphi[gdphiloop]>=100)h_2d_dphi_npf[2*pdfind +1]->Fill(dphiloop*10.+n_pf_dphi[dphiloop]/10.,gdphiloop*10.+9.9,weight);
		if(n_pf_dphi[dphiloop]>=100&&gn_pf_dphi[gdphiloop]<100)h_2d_dphi_npf[2*pdfind +1]->Fill(dphiloop*10.+9.9,gdphiloop*10.+gn_pf_dphi[gdphiloop]/10.,weight);

	      }
	    }

	    h_dphi_npf[2*pdfind +1]->Fill(dphiloop*9,n_pf_dphi[dphiloop],weight);
	    h_dphi_ptsumpf[2*pdfind +1]->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop],weight);
	    h_dphi_ptaveragepf[2*pdfind +1]->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop]/n_pf_dphi[dphiloop],weight);
	    h_profile_dphi_npf[2*pdfind +1]->Fill(dphiloop*9,n_pf_dphi[dphiloop],weight);
	    h_profile_dphi_ptsumpf[2*pdfind +1]->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop],weight);
	    h_profile_dphi_ptaveragepf[2*pdfind +1]->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop]/n_pf_dphi[dphiloop],weight);

	    if(njet_15==4){
	      h_dphi_npf_0j[2*pdfind +1]->Fill(dphiloop*9,n_pf_dphi[dphiloop],weight);
	      h_dphi_ptsumpf_0j[2*pdfind +1]->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop],weight);
	      h_dphi_ptaveragepf_0j[2*pdfind +1]->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop]/n_pf_dphi[dphiloop],weight);
	      h_profile_dphi_npf_0j[2*pdfind +1]->Fill(dphiloop*9,n_pf_dphi[dphiloop],weight);
	      h_profile_dphi_ptsumpf_0j[2*pdfind +1]->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop],weight);
	      h_profile_dphi_ptaveragepf_0j[2*pdfind +1]->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop]/n_pf_dphi[dphiloop],weight);
	    }

	    if(njet_15==5){
	      h_dphi_npf_1j[2*pdfind +1]->Fill(dphiloop*9,n_pf_dphi[dphiloop],weight);
	      h_dphi_ptsumpf_1j[2*pdfind +1]->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop],weight);
	      h_dphi_ptaveragepf_1j[2*pdfind +1]->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop]/n_pf_dphi[dphiloop],weight);
	      h_profile_dphi_npf_1j[2*pdfind +1]->Fill(dphiloop*9,n_pf_dphi[dphiloop],weight);
	      h_profile_dphi_ptsumpf_1j[2*pdfind +1]->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop],weight);
	      h_profile_dphi_ptaveragepf_1j[2*pdfind +1]->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop]/n_pf_dphi[dphiloop],weight);
	    }

	    if(njet_15>=6){
	      h_dphi_npf_2pj[2*pdfind +1]->Fill(dphiloop*9,n_pf_dphi[dphiloop],weight);
	      h_dphi_ptsumpf_2pj[2*pdfind +1]->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop],weight);
	      h_dphi_ptaveragepf_2pj[2*pdfind +1]->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop]/n_pf_dphi[dphiloop],weight);
	      h_profile_dphi_npf_2pj[2*pdfind +1]->Fill(dphiloop*9,n_pf_dphi[dphiloop],weight);
	      h_profile_dphi_ptsumpf_2pj[2*pdfind +1]->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop],weight);
	      h_profile_dphi_ptaveragepf_2pj[2*pdfind +1]->Fill(dphiloop*9,ptsum_pf_dphi[dphiloop]/n_pf_dphi[dphiloop],weight);
	    }
	  }

	  h_nvtx_npf[2*pdfind +1]->Fill(EvtInfo_NumVtx,weight);
	  h_profile_nvtx_npf[2*pdfind +1]->Fill(EvtInfo_NumVtx,n_pf,weight);
	  h_profile_nvtx_sumpt[2*pdfind +1]->Fill(EvtInfo_NumVtx,ptsum_pf,weight);
	  h_profile_nvtx_njet30[2*pdfind +1]->Fill(EvtInfo_NumVtx,jet_vector.size()-4,weight);
	  h_profile_nvtx_njet15[2*pdfind +1]->Fill(EvtInfo_NumVtx,njet_15-4,weight);


	  if(njet_15==4){
	    h_nvtx_npf_0j[2*pdfind +1]->Fill(EvtInfo_NumVtx,weight);
	    h_profile_nvtx_npf_0j[2*pdfind +1]->Fill(EvtInfo_NumVtx,n_pf,weight);
	    h_profile_nvtx_sumpt_0j[2*pdfind +1]->Fill(EvtInfo_NumVtx,ptsum_pf,weight);
	  }
	  if(njet_15==5){
	    h_nvtx_npf_1j[2*pdfind +1]->Fill(EvtInfo_NumVtx,weight);
	    h_profile_nvtx_npf_1j[2*pdfind +1]->Fill(EvtInfo_NumVtx,n_pf,weight);
	    h_profile_nvtx_sumpt_1j[2*pdfind +1]->Fill(EvtInfo_NumVtx,ptsum_pf,weight);
	  }

	  if(njet_15>=6){
	    h_nvtx_npf_2pj[2*pdfind +1]->Fill(EvtInfo_NumVtx,weight);
	    h_profile_nvtx_npf_2pj[2*pdfind +1]->Fill(EvtInfo_NumVtx,n_pf,weight);
	    h_profile_nvtx_sumpt_2pj[2*pdfind +1]->Fill(EvtInfo_NumVtx,ptsum_pf,weight);

	  }


	  h_profile_ptttbar_npf[2*pdfind +1]->Fill(ttbar.Pt(),n_pf,weight);
	  h_profile_ptttbar_sumpt[2*pdfind +1]->Fill(ttbar.Pt(),ptsum_pf,weight);
	  h_profile_ptttbar_avept[2*pdfind +1]->Fill(ttbar.Pt(),ptsum_pf/n_pf,weight);
	  h_profile_ptttbar_njet15[2*pdfind +1]->Fill(ttbar.Pt(),njet_15-4,weight);
	  h_profile_ptttbar_njet30[2*pdfind +1]->Fill(ttbar.Pt(),jet_vector.size()-4,weight);

	  if(n_pf_away!=0)h_profile_ptttbar_npf_away[2*pdfind +1]->Fill(ttbar.Pt(),n_pf_away,weight);
	  if(n_pf_away!=0)h_profile_ptttbar_sumpt_away[2*pdfind +1]->Fill(ttbar.Pt(),ptsum_pf_away,weight);
	  if(n_pf_away!=0)h_profile_ptttbar_avept_away[2*pdfind +1]->Fill(ttbar.Pt(),ptsum_pf_away/n_pf_away,weight);
	  if(n_pf_away!=0)h_profile_ptttbar_njet15_away[2*pdfind +1]->Fill(ttbar.Pt(),njet_away15,weight);
	  if(n_pf_away!=0)h_profile_ptttbar_njet30_away[2*pdfind +1]->Fill(ttbar.Pt(),njet_away,weight);

	  if(n_pf_transverse!=0)h_profile_ptttbar_npf_transverse[2*pdfind +1]->Fill(ttbar.Pt(),n_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_ptttbar_sumpt_transverse[2*pdfind +1]->Fill(ttbar.Pt(),ptsum_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_ptttbar_avept_transverse[2*pdfind +1]->Fill(ttbar.Pt(),ptsum_pf_transverse/n_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_ptttbar_njet15_transverse[2*pdfind +1]->Fill(ttbar.Pt(),njet_transverse15,weight);
	  if(n_pf_transverse!=0)h_profile_ptttbar_njet30_transverse[2*pdfind +1]->Fill(ttbar.Pt(),njet_transverse,weight);

	  if(n_pf_toward!=0)h_profile_ptttbar_npf_toward[2*pdfind +1]->Fill(ttbar.Pt(),n_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_ptttbar_sumpt_toward[2*pdfind +1]->Fill(ttbar.Pt(),ptsum_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_ptttbar_avept_toward[2*pdfind +1]->Fill(ttbar.Pt(),ptsum_pf_toward/n_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_ptttbar_njet15_toward[2*pdfind +1]->Fill(ttbar.Pt(),njet_toward15,weight);
	  if(n_pf_toward!=0)h_profile_ptttbar_njet30_toward[2*pdfind +1]->Fill(ttbar.Pt(),njet_toward,weight);

	  h_profile_mttbar_npf[2*pdfind +1]->Fill(ttbar.M(),n_pf,weight);
	  h_profile_mttbar_sumpt[2*pdfind +1]->Fill(ttbar.M(),ptsum_pf,weight);
	  h_profile_mttbar_avept[2*pdfind +1]->Fill(ttbar.M(),ptsum_pf/n_pf,weight);
	  if(n_pf_away!=0)h_profile_mttbar_npf_away[2*pdfind +1]->Fill(ttbar.M(),n_pf_away,weight);
	  if(n_pf_away!=0)h_profile_mttbar_sumpt_away[2*pdfind +1]->Fill(ttbar.M(),ptsum_pf_away,weight);
	  if(n_pf_away!=0)h_profile_mttbar_avept_away[2*pdfind +1]->Fill(ttbar.M(),ptsum_pf_away/n_pf_away,weight);
	  if(n_pf_transverse!=0)h_profile_mttbar_npf_transverse[2*pdfind +1]->Fill(ttbar.M(),n_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_mttbar_sumpt_transverse[2*pdfind +1]->Fill(ttbar.M(),ptsum_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_mttbar_avept_transverse[2*pdfind +1]->Fill(ttbar.M(),ptsum_pf_transverse/n_pf_transverse,weight);
	  if(n_pf_toward!=0)h_profile_mttbar_npf_toward[2*pdfind +1]->Fill(ttbar.M(),n_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_mttbar_sumpt_toward[2*pdfind +1]->Fill(ttbar.M(),ptsum_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_mttbar_avept_toward[2*pdfind +1]->Fill(ttbar.M(),ptsum_pf_toward/n_pf_toward,weight);




	  h_profile_ytt_npf[2*pdfind +1]->Fill(fabs(ttbar.Rapidity()),n_pf,weight);
	  h_profile_ytt_sumpt[2*pdfind +1]->Fill(fabs(ttbar.Rapidity()),ptsum_pf,weight);
	  h_profile_ytt_avept[2*pdfind +1]->Fill(fabs(ttbar.Rapidity()),ptsum_pf/n_pf,weight);
	  if(n_pf_away!=0)h_profile_ytt_npf_away[2*pdfind +1]->Fill(fabs(ttbar.Rapidity()),n_pf_away,weight);
	  if(n_pf_away!=0)h_profile_ytt_sumpt_away[2*pdfind +1]->Fill(fabs(ttbar.Rapidity()),ptsum_pf_away,weight);
	  if(n_pf_away!=0)h_profile_ytt_avept_away[2*pdfind +1]->Fill(fabs(ttbar.Rapidity()),ptsum_pf_away/n_pf_away,weight);
	  if(n_pf_transverse!=0)h_profile_ytt_npf_transverse[2*pdfind +1]->Fill(fabs(ttbar.Rapidity()),n_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_ytt_sumpt_transverse[2*pdfind +1]->Fill(fabs(ttbar.Rapidity()),ptsum_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_ytt_avept_transverse[2*pdfind +1]->Fill(fabs(ttbar.Rapidity()),ptsum_pf_transverse/n_pf_transverse,weight);
	  if(n_pf_toward!=0)h_profile_ytt_npf_toward[2*pdfind +1]->Fill(fabs(ttbar.Rapidity()),n_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_ytt_sumpt_toward[2*pdfind +1]->Fill(fabs(ttbar.Rapidity()),ptsum_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_ytt_avept_toward[2*pdfind +1]->Fill(fabs(ttbar.Rapidity()),ptsum_pf_toward/n_pf_toward,weight);

	  h_profile_pttop_npf[2*pdfind +1]->Fill(top_vector.Pt(),n_pf,weight);
	  h_profile_pttop_sumpt[2*pdfind +1]->Fill(top_vector.Pt(),ptsum_pf,weight);
	  h_profile_pttop_avept[2*pdfind +1]->Fill(top_vector.Pt(),ptsum_pf/n_pf,weight);
	  if(n_pf_away!=0)h_profile_pttop_npf_away[2*pdfind +1]->Fill(top_vector.Pt(),n_pf_away,weight);
	  if(n_pf_away!=0)h_profile_pttop_sumpt_away[2*pdfind +1]->Fill(top_vector.Pt(),ptsum_pf_away,weight);
	  if(n_pf_away!=0)h_profile_pttop_avept_away[2*pdfind +1]->Fill(top_vector.Pt(),ptsum_pf_away/n_pf_away,weight);
	  if(n_pf_transverse!=0)h_profile_pttop_npf_transverse[2*pdfind +1]->Fill(top_vector.Pt(),n_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_pttop_sumpt_transverse[2*pdfind +1]->Fill(top_vector.Pt(),ptsum_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_pttop_avept_transverse[2*pdfind +1]->Fill(top_vector.Pt(),ptsum_pf_transverse/n_pf_transverse,weight);
	  if(n_pf_toward!=0)h_profile_pttop_npf_toward[2*pdfind +1]->Fill(top_vector.Pt(),n_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_pttop_sumpt_toward[2*pdfind +1]->Fill(top_vector.Pt(),ptsum_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_pttop_avept_toward[2*pdfind +1]->Fill(top_vector.Pt(),ptsum_pf_toward/n_pf_toward,weight);

	  h_profile_ptatop_npf[2*pdfind +1]->Fill(atop_vector.Pt(),n_pf,weight);
	  h_profile_ptatop_sumpt[2*pdfind +1]->Fill(atop_vector.Pt(),ptsum_pf,weight);
	  h_profile_ptatop_avept[2*pdfind +1]->Fill(atop_vector.Pt(),ptsum_pf/n_pf,weight);
	  if(n_pf_away!=0)h_profile_ptatop_npf_away[2*pdfind +1]->Fill(atop_vector.Pt(),n_pf_away,weight);
	  if(n_pf_away!=0)h_profile_ptatop_sumpt_away[2*pdfind +1]->Fill(atop_vector.Pt(),ptsum_pf_away,weight);
	  if(n_pf_away!=0)h_profile_ptatop_avept_away[2*pdfind +1]->Fill(atop_vector.Pt(),ptsum_pf_away/n_pf_away,weight);
	  if(n_pf_transverse!=0)h_profile_ptatop_npf_transverse[2*pdfind +1]->Fill(atop_vector.Pt(),n_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_ptatop_sumpt_transverse[2*pdfind +1]->Fill(atop_vector.Pt(),ptsum_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_ptatop_avept_transverse[2*pdfind +1]->Fill(atop_vector.Pt(),ptsum_pf_transverse/n_pf_transverse,weight);
	  if(n_pf_toward!=0)h_profile_ptatop_npf_toward[2*pdfind +1]->Fill(atop_vector.Pt(),n_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_ptatop_sumpt_toward[2*pdfind +1]->Fill(atop_vector.Pt(),ptsum_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_ptatop_avept_toward[2*pdfind +1]->Fill(atop_vector.Pt(),ptsum_pf_toward/n_pf_toward,weight);

	  h_profile_mtop_npf[2*pdfind +1]->Fill(top_vector.M(),n_pf,weight);
	  h_profile_mtop_sumpt[2*pdfind +1]->Fill(top_vector.M(),ptsum_pf,weight);
	  h_profile_mtop_avept[2*pdfind +1]->Fill(top_vector.M(),ptsum_pf/n_pf,weight);
	  if(n_pf_away!=0)h_profile_mtop_npf_away[2*pdfind +1]->Fill(top_vector.M(),n_pf_away,weight);
	  if(n_pf_away!=0)h_profile_mtop_sumpt_away[2*pdfind +1]->Fill(top_vector.M(),ptsum_pf_away,weight);
	  if(n_pf_away!=0)h_profile_mtop_avept_away[2*pdfind +1]->Fill(top_vector.M(),ptsum_pf_away/n_pf_away,weight);
	  if(n_pf_transverse!=0)h_profile_mtop_npf_transverse[2*pdfind +1]->Fill(top_vector.M(),n_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_mtop_sumpt_transverse[2*pdfind +1]->Fill(top_vector.M(),ptsum_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_mtop_avept_transverse[2*pdfind +1]->Fill(top_vector.M(),ptsum_pf_transverse/n_pf_transverse,weight);
	  if(n_pf_toward!=0)h_profile_mtop_npf_toward[2*pdfind +1]->Fill(top_vector.M(),n_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_mtop_sumpt_toward[2*pdfind +1]->Fill(top_vector.M(),ptsum_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_mtop_avept_toward[2*pdfind +1]->Fill(top_vector.M(),ptsum_pf_toward/n_pf_toward,weight);

	  h_profile_matop_npf[2*pdfind +1]->Fill(atop_vector.M(),n_pf,weight);
	  h_profile_matop_sumpt[2*pdfind +1]->Fill(atop_vector.M(),ptsum_pf,weight);
	  h_profile_matop_avept[2*pdfind +1]->Fill(atop_vector.M(),ptsum_pf/n_pf,weight);
	  if(n_pf_away!=0)h_profile_matop_npf_away[2*pdfind +1]->Fill(atop_vector.M(),n_pf_away,weight);
	  if(n_pf_away!=0)h_profile_matop_sumpt_away[2*pdfind +1]->Fill(atop_vector.M(),ptsum_pf_away,weight);
	  if(n_pf_away!=0)h_profile_matop_avept_away[2*pdfind +1]->Fill(atop_vector.M(),ptsum_pf_away/n_pf_away,weight);
	  if(n_pf_transverse!=0)h_profile_matop_npf_transverse[2*pdfind +1]->Fill(atop_vector.M(),n_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_matop_sumpt_transverse[2*pdfind +1]->Fill(atop_vector.M(),ptsum_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_matop_avept_transverse[2*pdfind +1]->Fill(atop_vector.M(),ptsum_pf_transverse/n_pf_transverse,weight);
	  if(n_pf_toward!=0)h_profile_matop_npf_toward[2*pdfind +1]->Fill(atop_vector.M(),n_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_matop_sumpt_toward[2*pdfind +1]->Fill(atop_vector.M(),ptsum_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_matop_avept_toward[2*pdfind +1]->Fill(atop_vector.M(),ptsum_pf_toward/n_pf_toward,weight);

	  h_profile_ytop_npf[2*pdfind +1]->Fill(fabs(top_vector.Rapidity()),n_pf,weight);
	  h_profile_ytop_sumpt[2*pdfind +1]->Fill(fabs(top_vector.Rapidity()),ptsum_pf,weight);
	  h_profile_ytop_avept[2*pdfind +1]->Fill(fabs(top_vector.Rapidity()),ptsum_pf/n_pf,weight);
	  if(n_pf_away!=0)h_profile_ytop_npf_away[2*pdfind +1]->Fill(fabs(top_vector.Rapidity()),n_pf_away,weight);
	  if(n_pf_away!=0)h_profile_ytop_sumpt_away[2*pdfind +1]->Fill(fabs(top_vector.Rapidity()),ptsum_pf_away,weight);
	  if(n_pf_away!=0)h_profile_ytop_avept_away[2*pdfind +1]->Fill(fabs(top_vector.Rapidity()),ptsum_pf_away/n_pf_away,weight);
	  if(n_pf_transverse!=0)h_profile_ytop_npf_transverse[2*pdfind +1]->Fill(fabs(top_vector.Rapidity()),n_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_ytop_sumpt_transverse[2*pdfind +1]->Fill(fabs(top_vector.Rapidity()),ptsum_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_ytop_avept_transverse[2*pdfind +1]->Fill(fabs(top_vector.Rapidity()),ptsum_pf_transverse/n_pf_transverse,weight);
	  if(n_pf_toward!=0)h_profile_ytop_npf_toward[2*pdfind +1]->Fill(fabs(top_vector.Rapidity()),n_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_ytop_sumpt_toward[2*pdfind +1]->Fill(fabs(top_vector.Rapidity()),ptsum_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_ytop_avept_toward[2*pdfind +1]->Fill(fabs(top_vector.Rapidity()),ptsum_pf_toward/n_pf_toward,weight);

	  h_profile_yatop_npf[2*pdfind +1]->Fill(fabs(top_vector.Rapidity()),n_pf,weight);
	  h_profile_yatop_sumpt[2*pdfind +1]->Fill(fabs(top_vector.Rapidity()),ptsum_pf,weight);
	  h_profile_yatop_avept[2*pdfind +1]->Fill(fabs(top_vector.Rapidity()),ptsum_pf/n_pf,weight);
	  if(n_pf_away!=0)h_profile_yatop_npf_away[2*pdfind +1]->Fill(fabs(top_vector.Rapidity()),n_pf_away,weight);
	  if(n_pf_away!=0)h_profile_yatop_sumpt_away[2*pdfind +1]->Fill(fabs(top_vector.Rapidity()),ptsum_pf_away,weight);
	  if(n_pf_away!=0)h_profile_yatop_avept_away[2*pdfind +1]->Fill(fabs(top_vector.Rapidity()),ptsum_pf_away/n_pf_away,weight);
	  if(n_pf_transverse!=0)h_profile_yatop_npf_transverse[2*pdfind +1]->Fill(fabs(top_vector.Rapidity()),n_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_yatop_sumpt_transverse[2*pdfind +1]->Fill(fabs(top_vector.Rapidity()),ptsum_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_yatop_avept_transverse[2*pdfind +1]->Fill(fabs(top_vector.Rapidity()),ptsum_pf_transverse/n_pf_transverse,weight);
	  if(n_pf_toward!=0)h_profile_yatop_npf_toward[2*pdfind +1]->Fill(fabs(top_vector.Rapidity()),n_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_yatop_sumpt_toward[2*pdfind +1]->Fill(fabs(top_vector.Rapidity()),ptsum_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_yatop_avept_toward[2*pdfind +1]->Fill(fabs(top_vector.Rapidity()),ptsum_pf_toward/n_pf_toward,weight);

	  h_profile_ptthad_npf[2*pdfind +1]->Fill(thad.Pt(),n_pf,weight);
	  h_profile_ptthad_sumpt[2*pdfind +1]->Fill(thad.Pt(),ptsum_pf,weight);
	  h_profile_ptthad_avept[2*pdfind +1]->Fill(thad.Pt(),ptsum_pf/n_pf,weight);
	  if(n_pf_away!=0)h_profile_ptthad_npf_away[2*pdfind +1]->Fill(thad.Pt(),n_pf_away,weight);
	  if(n_pf_away!=0)h_profile_ptthad_sumpt_away[2*pdfind +1]->Fill(thad.Pt(),ptsum_pf_away,weight);
	  if(n_pf_away!=0)h_profile_ptthad_avept_away[2*pdfind +1]->Fill(thad.Pt(),ptsum_pf_away/n_pf_away,weight);
	  if(n_pf_transverse!=0)h_profile_ptthad_npf_transverse[2*pdfind +1]->Fill(thad.Pt(),n_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_ptthad_sumpt_transverse[2*pdfind +1]->Fill(thad.Pt(),ptsum_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_ptthad_avept_transverse[2*pdfind +1]->Fill(thad.Pt(),ptsum_pf_transverse/n_pf_transverse,weight);
	  if(n_pf_toward!=0)h_profile_ptthad_npf_toward[2*pdfind +1]->Fill(thad.Pt(),n_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_ptthad_sumpt_toward[2*pdfind +1]->Fill(thad.Pt(),ptsum_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_ptthad_avept_toward[2*pdfind +1]->Fill(thad.Pt(),ptsum_pf_toward/n_pf_toward,weight);

	  h_profile_pttlep_npf[2*pdfind +1]->Fill(tlep.Pt(),n_pf,weight);
	  h_profile_pttlep_sumpt[2*pdfind +1]->Fill(tlep.Pt(),ptsum_pf,weight);
	  h_profile_pttlep_avept[2*pdfind +1]->Fill(tlep.Pt(),ptsum_pf/n_pf,weight);
	  if(n_pf_away!=0)h_profile_pttlep_npf_away[2*pdfind +1]->Fill(tlep.Pt(),n_pf_away,weight);
	  if(n_pf_away!=0)h_profile_pttlep_sumpt_away[2*pdfind +1]->Fill(tlep.Pt(),ptsum_pf_away,weight);
	  if(n_pf_away!=0)h_profile_pttlep_avept_away[2*pdfind +1]->Fill(tlep.Pt(),ptsum_pf_away/n_pf_away,weight);
	  if(n_pf_transverse!=0)h_profile_pttlep_npf_transverse[2*pdfind +1]->Fill(tlep.Pt(),n_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_pttlep_sumpt_transverse[2*pdfind +1]->Fill(tlep.Pt(),ptsum_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_pttlep_avept_transverse[2*pdfind +1]->Fill(tlep.Pt(),ptsum_pf_transverse/n_pf_transverse,weight);
	  if(n_pf_toward!=0)h_profile_pttlep_npf_toward[2*pdfind +1]->Fill(tlep.Pt(),n_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_pttlep_sumpt_toward[2*pdfind +1]->Fill(tlep.Pt(),ptsum_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_pttlep_avept_toward[2*pdfind +1]->Fill(tlep.Pt(),ptsum_pf_toward/n_pf_toward,weight);

	  h_profile_mthad_npf[2*pdfind +1]->Fill(thad.M(),n_pf,weight);
	  h_profile_mthad_sumpt[2*pdfind +1]->Fill(thad.M(),ptsum_pf,weight);
	  h_profile_mthad_avept[2*pdfind +1]->Fill(thad.M(),ptsum_pf/n_pf,weight);
	  if(n_pf_away!=0)h_profile_mthad_npf_away[2*pdfind +1]->Fill(thad.M(),n_pf_away,weight);
	  if(n_pf_away!=0)h_profile_mthad_sumpt_away[2*pdfind +1]->Fill(thad.M(),ptsum_pf_away,weight);
	  if(n_pf_away!=0)h_profile_mthad_avept_away[2*pdfind +1]->Fill(thad.M(),ptsum_pf_away/n_pf_away,weight);
	  if(n_pf_transverse!=0)h_profile_mthad_npf_transverse[2*pdfind +1]->Fill(thad.M(),n_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_mthad_sumpt_transverse[2*pdfind +1]->Fill(thad.M(),ptsum_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_mthad_avept_transverse[2*pdfind +1]->Fill(thad.M(),ptsum_pf_transverse/n_pf_transverse,weight);
	  if(n_pf_toward!=0)h_profile_mthad_npf_toward[2*pdfind +1]->Fill(thad.M(),n_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_mthad_sumpt_toward[2*pdfind +1]->Fill(thad.M(),ptsum_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_mthad_avept_toward[2*pdfind +1]->Fill(thad.M(),ptsum_pf_toward/n_pf_toward,weight);

	  h_profile_mtlep_npf[2*pdfind +1]->Fill(tlep.M(),n_pf,weight);
	  h_profile_mtlep_sumpt[2*pdfind +1]->Fill(tlep.M(),ptsum_pf,weight);
	  h_profile_mtlep_avept[2*pdfind +1]->Fill(tlep.M(),ptsum_pf/n_pf,weight);
	  if(n_pf_away!=0)h_profile_mtlep_npf_away[2*pdfind +1]->Fill(tlep.M(),n_pf_away,weight);
	  if(n_pf_away!=0)h_profile_mtlep_sumpt_away[2*pdfind +1]->Fill(tlep.M(),ptsum_pf_away,weight);
	  if(n_pf_away!=0)h_profile_mtlep_avept_away[2*pdfind +1]->Fill(tlep.M(),ptsum_pf_away/n_pf_away,weight);
	  if(n_pf_transverse!=0)h_profile_mtlep_npf_transverse[2*pdfind +1]->Fill(tlep.M(),n_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_mtlep_sumpt_transverse[2*pdfind +1]->Fill(tlep.M(),ptsum_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_mtlep_avept_transverse[2*pdfind +1]->Fill(tlep.M(),ptsum_pf_transverse/n_pf_transverse,weight);
	  if(n_pf_toward!=0)h_profile_mtlep_npf_toward[2*pdfind +1]->Fill(tlep.M(),n_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_mtlep_sumpt_toward[2*pdfind +1]->Fill(tlep.M(),ptsum_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_mtlep_avept_toward[2*pdfind +1]->Fill(tlep.M(),ptsum_pf_toward/n_pf_toward,weight);

	  h_profile_ythad_npf[2*pdfind +1]->Fill(fabs(thad.Rapidity()),n_pf,weight);
	  h_profile_ythad_sumpt[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf,weight);
	  h_profile_ythad_avept[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf/n_pf,weight);
	  if(n_pf_away!=0)h_profile_ythad_npf_away[2*pdfind +1]->Fill(fabs(thad.Rapidity()),n_pf_away,weight);
	  if(n_pf_away!=0)h_profile_ythad_sumpt_away[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf_away,weight);
	  if(n_pf_away!=0)h_profile_ythad_avept_away[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf_away/n_pf_away,weight);
	  if(n_pf_transverse!=0)h_profile_ythad_npf_transverse[2*pdfind +1]->Fill(fabs(thad.Rapidity()),n_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_ythad_sumpt_transverse[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_ythad_avept_transverse[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf_transverse/n_pf_transverse,weight);
	  if(n_pf_toward!=0)h_profile_ythad_npf_toward[2*pdfind +1]->Fill(fabs(thad.Rapidity()),n_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_ythad_sumpt_toward[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_ythad_avept_toward[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf_toward/n_pf_toward,weight);

	  h_profile_ytlep_npf[2*pdfind +1]->Fill(fabs(thad.Rapidity()),n_pf,weight);
	  h_profile_ytlep_sumpt[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf,weight);
	  h_profile_ytlep_avept[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf/n_pf,weight);
	  if(n_pf_away!=0)h_profile_ytlep_npf_away[2*pdfind +1]->Fill(fabs(thad.Rapidity()),n_pf_away,weight);
	  if(n_pf_away!=0)h_profile_ytlep_sumpt_away[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf_away,weight);
	  if(n_pf_away!=0)h_profile_ytlep_avept_away[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf_away/n_pf_away,weight);
	  if(n_pf_transverse!=0)h_profile_ytlep_npf_transverse[2*pdfind +1]->Fill(fabs(thad.Rapidity()),n_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_ytlep_sumpt_transverse[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_ytlep_avept_transverse[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf_transverse/n_pf_transverse,weight);
	  if(n_pf_toward!=0)h_profile_ytlep_npf_toward[2*pdfind +1]->Fill(fabs(thad.Rapidity()),n_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_ytlep_sumpt_toward[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_ytlep_avept_toward[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf_toward/n_pf_toward,weight);


	  h_profile_ptt_npf[2*pdfind +1]->Fill(thad.Pt(),n_pf,weight);
	  h_profile_ptt_sumpt[2*pdfind +1]->Fill(thad.Pt(),ptsum_pf,weight);
	  h_profile_ptt_avept[2*pdfind +1]->Fill(thad.Pt(),ptsum_pf/n_pf,weight);
	  if(n_pf_away!=0)h_profile_ptt_npf_away[2*pdfind +1]->Fill(thad.Pt(),n_pf_away,weight);
	  if(n_pf_away!=0)h_profile_ptt_sumpt_away[2*pdfind +1]->Fill(thad.Pt(),ptsum_pf_away,weight);
	  if(n_pf_away!=0)h_profile_ptt_avept_away[2*pdfind +1]->Fill(thad.Pt(),ptsum_pf_away/n_pf_away,weight);
	  if(n_pf_transverse!=0)h_profile_ptt_npf_transverse[2*pdfind +1]->Fill(thad.Pt(),n_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_ptt_sumpt_transverse[2*pdfind +1]->Fill(thad.Pt(),ptsum_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_ptt_avept_transverse[2*pdfind +1]->Fill(thad.Pt(),ptsum_pf_transverse/n_pf_transverse,weight);
	  if(n_pf_toward!=0)h_profile_ptt_npf_toward[2*pdfind +1]->Fill(thad.Pt(),n_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_ptt_sumpt_toward[2*pdfind +1]->Fill(thad.Pt(),ptsum_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_ptt_avept_toward[2*pdfind +1]->Fill(thad.Pt(),ptsum_pf_toward/n_pf_toward,weight);

	  h_profile_ptt_npf[2*pdfind +1]->Fill(tlep.Pt(),n_pf,weight);
	  h_profile_ptt_sumpt[2*pdfind +1]->Fill(tlep.Pt(),ptsum_pf,weight);
	  h_profile_ptt_avept[2*pdfind +1]->Fill(tlep.Pt(),ptsum_pf/n_pf,weight);
	  if(n_pf_away!=0)h_profile_ptt_npf_away[2*pdfind +1]->Fill(tlep.Pt(),n_pf_away,weight);
	  if(n_pf_away!=0)h_profile_ptt_sumpt_away[2*pdfind +1]->Fill(tlep.Pt(),ptsum_pf_away,weight);
	  if(n_pf_away!=0)h_profile_ptt_avept_away[2*pdfind +1]->Fill(tlep.Pt(),ptsum_pf_away/n_pf_away,weight);
	  if(n_pf_transverse!=0)h_profile_ptt_npf_transverse[2*pdfind +1]->Fill(tlep.Pt(),n_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_ptt_sumpt_transverse[2*pdfind +1]->Fill(tlep.Pt(),ptsum_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_ptt_avept_transverse[2*pdfind +1]->Fill(tlep.Pt(),ptsum_pf_transverse/n_pf_transverse,weight);
	  if(n_pf_toward!=0)h_profile_ptt_npf_toward[2*pdfind +1]->Fill(tlep.Pt(),n_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_ptt_sumpt_toward[2*pdfind +1]->Fill(tlep.Pt(),ptsum_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_ptt_avept_toward[2*pdfind +1]->Fill(tlep.Pt(),ptsum_pf_toward/n_pf_toward,weight);

	  h_profile_mt_npf[2*pdfind +1]->Fill(thad.M(),n_pf,weight);
	  h_profile_mt_sumpt[2*pdfind +1]->Fill(thad.M(),ptsum_pf,weight);
	  h_profile_mt_avept[2*pdfind +1]->Fill(thad.M(),ptsum_pf/n_pf,weight);
	  if(n_pf_away!=0)h_profile_mt_npf_away[2*pdfind +1]->Fill(thad.M(),n_pf_away,weight);
	  if(n_pf_away!=0)h_profile_mt_sumpt_away[2*pdfind +1]->Fill(thad.M(),ptsum_pf_away,weight);
	  if(n_pf_away!=0)h_profile_mt_avept_away[2*pdfind +1]->Fill(thad.M(),ptsum_pf_away/n_pf_away,weight);
	  if(n_pf_transverse!=0)h_profile_mt_npf_transverse[2*pdfind +1]->Fill(thad.M(),n_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_mt_sumpt_transverse[2*pdfind +1]->Fill(thad.M(),ptsum_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_mt_avept_transverse[2*pdfind +1]->Fill(thad.M(),ptsum_pf_transverse/n_pf_transverse,weight);
	  if(n_pf_toward!=0)h_profile_mt_npf_toward[2*pdfind +1]->Fill(thad.M(),n_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_mt_sumpt_toward[2*pdfind +1]->Fill(thad.M(),ptsum_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_mt_avept_toward[2*pdfind +1]->Fill(thad.M(),ptsum_pf_toward/n_pf_toward,weight);

	  h_profile_mt_npf[2*pdfind +1]->Fill(tlep.M(),n_pf,weight);
	  h_profile_mt_sumpt[2*pdfind +1]->Fill(tlep.M(),ptsum_pf,weight);
	  h_profile_mt_avept[2*pdfind +1]->Fill(tlep.M(),ptsum_pf/n_pf,weight);
	  if(n_pf_away!=0)h_profile_mt_npf_away[2*pdfind +1]->Fill(tlep.M(),n_pf_away,weight);
	  if(n_pf_away!=0)h_profile_mt_sumpt_away[2*pdfind +1]->Fill(tlep.M(),ptsum_pf_away,weight);
	  if(n_pf_away!=0)h_profile_mt_avept_away[2*pdfind +1]->Fill(tlep.M(),ptsum_pf_away/n_pf_away,weight);
	  if(n_pf_transverse!=0)h_profile_mt_npf_transverse[2*pdfind +1]->Fill(tlep.M(),n_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_mt_sumpt_transverse[2*pdfind +1]->Fill(tlep.M(),ptsum_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_mt_avept_transverse[2*pdfind +1]->Fill(tlep.M(),ptsum_pf_transverse/n_pf_transverse,weight);
	  if(n_pf_toward!=0)h_profile_mt_npf_toward[2*pdfind +1]->Fill(tlep.M(),n_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_mt_sumpt_toward[2*pdfind +1]->Fill(tlep.M(),ptsum_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_mt_avept_toward[2*pdfind +1]->Fill(tlep.M(),ptsum_pf_toward/n_pf_toward,weight);

	  h_profile_yt_npf[2*pdfind +1]->Fill(fabs(thad.Rapidity()),n_pf,weight);
	  h_profile_yt_sumpt[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf,weight);
	  h_profile_yt_avept[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf/n_pf,weight);
	  if(n_pf_away!=0)h_profile_yt_npf_away[2*pdfind +1]->Fill(fabs(thad.Rapidity()),n_pf_away,weight);
	  if(n_pf_away!=0)h_profile_yt_sumpt_away[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf_away,weight);
	  if(n_pf_away!=0)h_profile_yt_avept_away[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf_away/n_pf_away,weight);
	  if(n_pf_transverse!=0)h_profile_yt_npf_transverse[2*pdfind +1]->Fill(fabs(thad.Rapidity()),n_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_yt_sumpt_transverse[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_yt_avept_transverse[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf_transverse/n_pf_transverse,weight);
	  if(n_pf_toward!=0)h_profile_yt_npf_toward[2*pdfind +1]->Fill(fabs(thad.Rapidity()),n_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_yt_sumpt_toward[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_yt_avept_toward[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf_toward/n_pf_toward,weight);

	  h_profile_yt_npf[2*pdfind +1]->Fill(fabs(thad.Rapidity()),n_pf,weight);
	  h_profile_yt_sumpt[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf,weight);
	  h_profile_yt_avept[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf/n_pf,weight);
	  if(n_pf_away!=0)h_profile_yt_npf_away[2*pdfind +1]->Fill(fabs(thad.Rapidity()),n_pf_away,weight);
	  if(n_pf_away!=0)h_profile_yt_sumpt_away[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf_away,weight);
	  if(n_pf_away!=0)h_profile_yt_avept_away[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf_away/n_pf_away,weight);
	  if(n_pf_transverse!=0)h_profile_yt_npf_transverse[2*pdfind +1]->Fill(fabs(thad.Rapidity()),n_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_yt_sumpt_transverse[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf_transverse,weight);
	  if(n_pf_transverse!=0)h_profile_yt_avept_transverse[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf_transverse/n_pf_transverse,weight);
	  if(n_pf_toward!=0)h_profile_yt_npf_toward[2*pdfind +1]->Fill(fabs(thad.Rapidity()),n_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_yt_sumpt_toward[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf_toward,weight);
	  if(n_pf_toward!=0)h_profile_yt_avept_toward[2*pdfind +1]->Fill(fabs(thad.Rapidity()),ptsum_pf_toward/n_pf_toward,weight);







	  if(extra_jet_index!=99/* ||extra_jet_index_1530!=99*/ ){
	    h_rec_ttjY[2*pdfind +1]->Fill(ttj_vector.Rapidity(),weight);

	    h_profile_yttj_npf[2*pdfind +1]->Fill(fabs(ttj_vector.Rapidity()),n_pf,weight);
	    h_profile_yttj_sumpt[2*pdfind +1]->Fill(fabs(ttj_vector.Rapidity()),ptsum_pf,weight);
	    h_profile_yttj_avept[2*pdfind +1]->Fill(fabs(ttj_vector.Rapidity()),ptsum_pf/n_pf,weight);
	    if(n_pf_away!=0)h_profile_yttj_npf_away[2*pdfind +1]->Fill(fabs(ttj_vector.Rapidity()),n_pf_away,weight);
	    if(n_pf_away!=0)h_profile_yttj_sumpt_away[2*pdfind +1]->Fill(fabs(ttj_vector.Rapidity()),ptsum_pf_away,weight);
	    if(n_pf_away!=0)h_profile_yttj_avept_away[2*pdfind +1]->Fill(fabs(ttj_vector.Rapidity()),ptsum_pf_away/n_pf_away,weight);
	    if(n_pf_transverse!=0)h_profile_yttj_npf_transverse[2*pdfind +1]->Fill(fabs(ttj_vector.Rapidity()),n_pf_transverse,weight);
	    if(n_pf_transverse!=0)h_profile_yttj_sumpt_transverse[2*pdfind +1]->Fill(fabs(ttj_vector.Rapidity()),ptsum_pf_transverse,weight);
	    if(n_pf_transverse!=0)h_profile_yttj_avept_transverse[2*pdfind +1]->Fill(fabs(ttj_vector.Rapidity()),ptsum_pf_transverse/n_pf_transverse,weight);
	    if(n_pf_toward!=0)h_profile_yttj_npf_toward[2*pdfind +1]->Fill(fabs(ttj_vector.Rapidity()),n_pf_toward,weight);
	    if(n_pf_toward!=0)h_profile_yttj_sumpt_toward[2*pdfind +1]->Fill(fabs(ttj_vector.Rapidity()),ptsum_pf_toward,weight);
	    if(n_pf_toward!=0)h_profile_yttj_avept_toward[2*pdfind +1]->Fill(fabs(ttj_vector.Rapidity()),ptsum_pf_toward/n_pf_toward,weight); 
	  }

	  //     }
	  //   }

	}
	h_nvtx[2*pdfind +1]->Fill(EvtInfo_NumVtx,weight);
	h_m_top[2*pdfind +1]->Fill(top_vector.M(),weight);
	h_m_atop[2*pdfind +1]->Fill(atop_vector.M(),weight);
	h_pt_top[2*pdfind +1]->Fill(top_vector.Pt(),weight);
	h_pt_atop[2*pdfind +1]->Fill(atop_vector.Pt(),weight);
	h_m_top_fixbin[2*pdfind +1]->Fill(top_vector.M(),weight);
	h_m_atop_fixbin[2*pdfind +1]->Fill(atop_vector.M(),weight);
	h_pt_top_fixbin[2*pdfind +1]->Fill(top_vector.Pt(),weight);
	h_pt_atop_fixbin[2*pdfind +1]->Fill(atop_vector.Pt(),weight);

	h_pt_ttbar_kinrec[2*pdfind +1]->Fill((tlep+thad).Pt(),weight);


	h_MTW[2*pdfind +1]->Fill(MTW,weight);
	h_mu_pt_meas[2*pdfind +1]->Fill(patMuonPt_->at(0),weight);
	h_mu_eta_meas[2*pdfind +1]->Fill(patMuonEta_->at(0),weight);
	h_mu_phi_meas[2*pdfind +1]->Fill(patMuonPhi_->at(0),weight);
	h_mu_iso_meas[2*pdfind +1]->Fill(patMuonPfIsoDbeta_->at(0),weight);
	h_m_thad[2*pdfind +1]->Fill(thad.M(),weight); 
	h_m_tlep[2*pdfind +1]->Fill(tlep.M(),weight);   

	h_pt_thad[2*pdfind +1]->Fill(thad.Pt(),weight); 
	h_pt_tlep[2*pdfind +1]->Fill(tlep.Pt(),weight);   

	h_m_thad_fixbin[2*pdfind +1]->Fill(thad.M(),weight); 
	h_m_tlep_fixbin[2*pdfind +1]->Fill(tlep.M(),weight);   

	h_pt_thad_fixbin[2*pdfind +1]->Fill(thad.Pt(),weight); 
	h_pt_tlep_fixbin[2*pdfind +1]->Fill(tlep.Pt(),weight);   

	h_y_thad[2*pdfind +1]->Fill(thad.Rapidity(),weight); 
	h_y_tlep[2*pdfind +1]->Fill(tlep.Rapidity(),weight);   


	h_m_t[2*pdfind +1]->Fill(thad.M(),weight); 
	h_m_t[2*pdfind +1]->Fill(tlep.M(),weight);   

	h_pt_t[2*pdfind +1]->Fill(thad.Pt(),weight); 
	h_pt_t[2*pdfind +1]->Fill(tlep.Pt(),weight);   

	h_m_t_fixbin[2*pdfind +1]->Fill(thad.M(),weight); 
	h_m_t_fixbin[2*pdfind +1]->Fill(tlep.M(),weight);   

	h_pt_t_fixbin[2*pdfind +1]->Fill(thad.Pt(),weight); 
	h_pt_t_fixbin[2*pdfind +1]->Fill(tlep.Pt(),weight);   

	h_y_t[2*pdfind +1]->Fill(thad.Rapidity(),weight); 
	h_y_t[2*pdfind +1]->Fill(tlep.Rapidity(),weight);   


	h_nu_pz[2*pdfind +1]->Fill(nu_vector.Pz(),weight);
	h_nu_pt[2*pdfind +1]->Fill(nu_vector.Pt(),weight);


	h_njet_bb[2*pdfind +1]->Fill(njet_bb,weight);
	h_njet_15_ttbar[2*pdfind +1]->Fill(jet_vector_1530.size()+jet_vector.size()-4,weight);
	if(njet_bb>=1)h_profile_deta_bb_njet_bb[2*pdfind +1]->Fill(deltaetabb,njet_bb,weight);
	if((jet_vector_1530.size()+jet_vector.size())>=5)h_profile_deta_bb_njet_extra[2*pdfind +1]->Fill(deltaetabb,jet_vector_1530.size()+jet_vector.size()-4,weight);
	h_ljet_pt[2*pdfind +1]->Fill(jet_vector[ljet_ind1].Pt(),weight);
	h_ljet_eta[2*pdfind +1]->Fill(jet_vector[ljet_ind1].Eta(),weight);    

	h_sljet_pt[2*pdfind +1]->Fill(jet_vector[ljet_ind2].Pt(),weight);
	h_sljet_eta[2*pdfind +1]->Fill(jet_vector[ljet_ind2].Eta(),weight);  


	h_lbjet_pt[2*pdfind +1]->Fill(jet_vector[b_jet_index[0]].Pt(),weight);
	h_lbjet_eta[2*pdfind +1]->Fill(jet_vector[b_jet_index[0]].Eta(),weight);    

	h_slbjet_pt[2*pdfind +1]->Fill(jet_vector[b_jet_index[1]].Pt(),weight);
	h_slbjet_eta[2*pdfind +1]->Fill(jet_vector[b_jet_index[1]].Eta(),weight);  

	h_dijet_mass[2*pdfind +1]->Fill((jet_vector[ljet_ind1]+jet_vector[ljet_ind2]).M(),weight);  
	h_dijet_mass_narrow[2*pdfind +1]->Fill((jet_vector[ljet_ind1]+jet_vector[ljet_ind2]).M(),weight);  


	h_met_meas[2*pdfind +1]->Fill(mett.Pt(),weight);


	h_m_ttbar[2*pdfind +1]->Fill(ttbar.M(),weight);
	h_m_ttbar_fixbin[2*pdfind +1]->Fill(ttbar.M(),weight);
	h_y_ttbar[2*pdfind +1]->Fill(ttbar.Rapidity(),weight);
	h_y_top[2*pdfind +1]->Fill(top_vector.Rapidity(),weight);
	h_y_atop[2*pdfind +1]->Fill(atop_vector.Rapidity(),weight);
	h_phi_ttbar[2*pdfind +1]->Fill(ttbar.Phi(),weight);
	//cout<<ttbar.Phi()<<endl;

	h_njet_ttbar[2*pdfind +1]->Fill(jet_vector.size(),weight);
      }//pdfind loop

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
