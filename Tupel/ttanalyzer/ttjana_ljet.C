#define ttjana_cxx
#include "ttjana_ljet.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <TLorentzVector.h>

void ttjana::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L ttjana.C
//      Root > ttjana t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
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
   TH1::SetDefaultSumw2();
   TH2::SetDefaultSumw2();
   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   TFile* file_out = new TFile("out.root","RECREATE"); 
   file_out->cd();	

   TH1* h_top_M_st3= new TH1D ("top_M_st3","top_M_st3",100,50,350);
   TH1* h_atop_M_st3= new TH1D ("atop_M_st3","atop_M_st3",100,50,350);

   TH1* h_atop_M= new TH1D ("atop_M","atop_M",100,50,350);
   TH1* h_top_M= new TH1D ("top_M","top_M",100,50,350);
   TH1* h_Wplus_M= new TH1D ("Wplus_M","Wplus_M",100,50,350);
   TH1* h_Wminus_M= new TH1D ("Wminus_M","Wminus_M",100,50,350);

   TH1* h_Whad_M= new TH1D ("Whad_M","Whad_M",100,50,350);
   TH1* h_Wlep_M= new TH1D ("Wlep_M","Wlep_M",100,50,350);


   TH1* h_atop_Pt= new TH1D ("atop_Pt","atop_Pt",100,0,1000);
   TH1* h_top_Pt= new TH1D ("top_Pt","top_Pt",100,0,1000);
   TH1* h_ttj_Y=new TH1D ("ttj_Y","ttj_Y",100,-10,10);
   TH1* h_ttj_Y_qq=new TH1D ("ttj_Y_qq","ttj_Y_qq",100,-10,10);
   TH1* h_ttj_Y_qg=new TH1D ("ttj_Y_qg","ttj_Y_qg",100,-10,10);
   TH1* h_ttj_Y_gg=new TH1D ("ttj_Y_gg","ttj_Y_gg",100,-10,10);
   TH1* h_deltar_jet_b=new TH1D ("deltar_jet_b","deltar_jet_b",100,0.,1.0);
   TH1* h_deltae_partons_before=new TH1D ("deltae_partons_before","deltae_partons_before",5000,-1000.,1000.);
   TH1* h_deltae_partons_after=new TH1D ("deltae_partons_after","deltae_partons_after",5000,-1000.,1000.);
   TH1* h_jettheta_deltaE_pos=new TH1D ("jettheta_deltaE_pos","jettheta_deltaE_pos",20,0,3.14);
   TH1* h_jettheta_deltaE_neg=new TH1D ("jettheta_deltaE_neg","jettheta_deltaE_neg",20,0,3.14);

   TH1* h_jettheta_deltaE_pos_qg=new TH1D ("jettheta_deltaE_pos_qg","jettheta_deltaE_pos_qg",20,0,3.14);
   TH1* h_jettheta_deltaE_neg_qg=new TH1D ("jettheta_deltaE_neg_qg","jettheta_deltaE_neg_qg",20,0,3.14);

   TH1* h_jettheta_deltaE_pos_gg=new TH1D ("jettheta_deltaE_pos_gg","jettheta_deltaE_pos_gg",20,0,3.14);
   TH1* h_jettheta_deltaE_neg_gg=new TH1D ("jettheta_deltaE_neg_gg","jettheta_deltaE_neg_gg",20,0,3.14);

   TH1* h_jettheta_deltaE_pos_qqbar=new TH1D ("jettheta_deltaE_pos_qqbar","jettheta_deltaE_pos_qqbar",20,0,3.14);
   TH1* h_jettheta_deltaE_neg_qqbar=new TH1D ("jettheta_deltaE_neg_qqbar","jettheta_deltaE_neg_qqbar",20,0,3.14);
   TH1* h_jettheta_deltaE_pos_qbarq=new TH1D ("jettheta_deltaE_pos_qbarq","jettheta_deltaE_pos_qbarq",20,0,3.14);
   TH1* h_jettheta_deltaE_neg_qbarq=new TH1D ("jettheta_deltaE_neg_qbarq","jettheta_deltaE_neg_qbarq",20,0,3.14);
   TH1* h_jettheta_deltaE_pos_qbarg=new TH1D ("jettheta_deltaE_pos_qbarg","jettheta_deltaE_pos_qbarg",20,0,3.14);
   TH1* h_jettheta_deltaE_neg_qbarg=new TH1D ("jettheta_deltaE_neg_qbarg","jettheta_deltaE_neg_qbarg",20,0,3.14);

   TH1* h_jettheta_deltaE_pos_gq=new TH1D ("jettheta_deltaE_pos_gq","jettheta_deltaE_pos_gq",20,0,3.14);
   TH1* h_jettheta_deltaE_neg_gq=new TH1D ("jettheta_deltaE_neg_gq","jettheta_deltaE_neg_gq",20,0,3.14);

   TH1* h_jettheta_deltaE_pos_gqbar=new TH1D ("jettheta_deltaE_pos_gqbar","jettheta_deltaE_pos_gqbar",20,0,3.14);
   TH1* h_jettheta_deltaE_neg_gqbar=new TH1D ("jettheta_deltaE_neg_gqbar","jettheta_deltaE_neg_gqbar",20,0,3.14);

   TH1* h_jettheta_costheta_j_t_pos=new TH1D ("jettheta_costheta_j_t_pos","jettheta_costheta_j_t_pos",20,0,3.14);
   TH1* h_jettheta_costheta_j_t_neg=new TH1D ("jettheta_costheta_j_t_neg","jettheta_costheta_j_t_neg",20,0,3.14);

   TH1* h_jettheta_costheta_j_t_pos_qg=new TH1D ("jettheta_costheta_j_t_pos_qg","jettheta_costheta_j_t_pos_qg",20,0,3.14);
   TH1* h_jettheta_costheta_j_t_neg_qg=new TH1D ("jettheta_costheta_j_t_neg_qg","jettheta_costheta_j_t_neg_qg",20,0,3.14);

   TH1* h_jettheta_costheta_j_t_pos_gg=new TH1D ("jettheta_costheta_j_t_pos_gg","jettheta_costheta_j_t_pos_gg",20,0,3.14);
   TH1* h_jettheta_costheta_j_t_neg_gg=new TH1D ("jettheta_costheta_j_t_neg_gg","jettheta_costheta_j_t_neg_gg",20,0,3.14);

   TH1* h_jettheta_costheta_j_t_pos_qqbar=new TH1D ("jettheta_costheta_j_t_pos_qqbar","jettheta_costheta_j_t_pos_qqbar",20,0,3.14);
   TH1* h_jettheta_costheta_j_t_neg_qqbar=new TH1D ("jettheta_costheta_j_t_neg_qqbar","jettheta_costheta_j_t_neg_qqbar",20,0,3.14);
   TH1* h_jettheta_costheta_j_t_pos_qbarq=new TH1D ("jettheta_costheta_j_t_pos_qbarq","jettheta_costheta_j_t_pos_qbarq",20,0,3.14);
   TH1* h_jettheta_costheta_j_t_neg_qbarq=new TH1D ("jettheta_costheta_j_t_neg_qbarq","jettheta_costheta_j_t_neg_qbarq",20,0,3.14);
   TH1* h_jettheta_costheta_j_t_pos_qbarg=new TH1D ("jettheta_costheta_j_t_pos_qbarg","jettheta_costheta_j_t_pos_qbarg",20,0,3.14);
   TH1* h_jettheta_costheta_j_t_neg_qbarg=new TH1D ("jettheta_costheta_j_t_neg_qbarg","jettheta_costheta_j_t_neg_qbarg",20,0,3.14);

   TH1* h_jettheta_costheta_j_t_pos_gq=new TH1D ("jettheta_costheta_j_t_pos_gq","jettheta_costheta_j_t_pos_gq",20,0,3.14);
   TH1* h_jettheta_costheta_j_t_neg_gq=new TH1D ("jettheta_costheta_j_t_neg_gq","jettheta_costheta_j_t_neg_gq",20,0,3.14);

   TH1* h_jettheta_costheta_j_t_pos_gqbar=new TH1D ("jettheta_costheta_j_t_pos_gqbar","jettheta_costheta_j_t_pos_gqbar",20,0,3.14);
   TH1* h_jettheta_costheta_j_t_neg_gqbar=new TH1D ("jettheta_costheta_j_t_neg_gqbar","jettheta_costheta_j_t_neg_gqbar",20,0,3.14);

   TH1* h_deltaE_ttbar=new TH1D ("deltaE_ttbar","deltaE_ttbar",200,-1000,1000);
   TH1* h_deltaE_ttbar_qg=new TH1D ("deltaE_ttbar_qg","deltaE_ttbar_qg",200,-1000,1000);
   TH1* h_deltaE_ttbar_gq=new TH1D ("deltaE_ttbar_gq","deltaE_ttbar_gq",200,-1000,1000);

   TH1* h_deltaE_ttbar_qbarg=new TH1D ("deltaE_ttbar_qbarg","deltaE_ttbar_qbarg",200,-1000,1000);
   TH1* h_deltaE_ttbar_gqbar=new TH1D ("deltaE_ttbar_gqbar","deltaE_ttbar_gqbar",200,-1000,1000);

   TH1* h_deltaE_ttbar_qbarq=new TH1D ("deltaE_ttbar_qbarq","deltaE_ttbar_qbarq",200,-1000,1000);
   TH1* h_deltaE_ttbar_qqbar=new TH1D ("deltaE_ttbar_qqbar","deltaE_ttbar_qqbar",200,-1000,1000);

   TH1* h_deltaE_ttbar_gg=new TH1D ("deltaE_ttbar_gg","deltaE_ttbar_gg",200,-1000,1000);

   TH1* h_costheta_j_t_ttbar=new TH1D ("costheta_j_t_ttbar","costheta_j_t_ttbar",200,-1,1);
   TH1* h_costheta_j_t_ttbar_qg=new TH1D ("costheta_j_t_ttbar_qg","costheta_j_t_ttbar_qg",200,-1,1);
   TH1* h_costheta_j_t_ttbar_gq=new TH1D ("costheta_j_t_ttbar_gq","costheta_j_t_ttbar_gq",200,-1,1);

   TH1* h_costheta_j_t_ttbar_qbarg=new TH1D ("costheta_j_t_ttbar_qbarg","costheta_j_t_ttbar_qbarg",200,-1,1);
   TH1* h_costheta_j_t_ttbar_gqbar=new TH1D ("costheta_j_t_ttbar_gqbar","costheta_j_t_ttbar_gqbar",200,-1,1);

   TH1* h_costheta_j_t_ttbar_qbarq=new TH1D ("costheta_j_t_ttbar_qbarq","costheta_j_t_ttbar_qbarq",200,-1,1);
   TH1* h_costheta_j_t_ttbar_qqbar=new TH1D ("costheta_j_t_ttbar_qqbar","costheta_j_t_ttbar_qqbar",200,-1,1);

   TH1* h_costheta_j_t_ttbar_gg=new TH1D ("costheta_j_t_ttbar_gg","costheta_j_t_ttbar_gg",200,-1,1);

   TH1* h_v_jettheta_deltaE_ttbar[11][11][2];
   TH1* h_v_jettheta_deltaE_ttbar_qg[11][11][2];
   TH1* h_v_jettheta_deltaE_ttbar_gq[11][11][2];
   TH1* h_v_jettheta_deltaE_ttbar_qbarg[11][11][2];
   TH1* h_v_jettheta_deltaE_ttbar_gqbar[11][11][2];
   TH1* h_v_jettheta_deltaE_ttbar_qbarq[11][11][2];
   TH1* h_v_jettheta_deltaE_ttbar_qqbar[11][11][2];
   TH1* h_v_jettheta_deltaE_ttbar_gg[11][11][2];

   TH1* h_v_deltaE_ttbar[11][11];
   TH1* h_v_deltaE_ttbar_qg[11][11];
   TH1* h_v_deltaE_ttbar_gq[11][11];
   TH1* h_v_deltaE_ttbar_qbarg[11][11];
   TH1* h_v_deltaE_ttbar_gqbar[11][11];
   TH1* h_v_deltaE_ttbar_qbarq[11][11];
   TH1* h_v_deltaE_ttbar_qqbar[11][11];
   TH1* h_v_deltaE_ttbar_gg[11][11];

   TH1* h_v_costheta_j_t_ttbar[11][11];
   TH1* h_v_costheta_j_t_ttbar_qg[11][11];
   TH1* h_v_costheta_j_t_ttbar_gq[11][11];
   TH1* h_v_costheta_j_t_ttbar_qbarg[11][11];
   TH1* h_v_costheta_j_t_ttbar_gqbar[11][11];
   TH1* h_v_costheta_j_t_ttbar_qbarq[11][11];
   TH1* h_v_costheta_j_t_ttbar_qqbar[11][11];
   TH1* h_v_costheta_j_t_ttbar_gg[11][11];

   char name[10000];
//   double cut_rapidity[]={0,0.25,0.5,0.75,1.0,1.25,1.5,1.75,2.,2.25,2.5};
//   double cut_de[]={0,20,40,60,80,100,120,140,160,180,200};
   double cut_rapidity[]={0,0.5,1.0};
   double cut_de[]={0,50,120};
   for(int i = 0; i<3;i++){//ttj rapidity
     for(int j = 0; j<3;j++){//De
        for(int k = 0; k<2;k++){//De
          sprintf(name,"v_jettheta_deltaE_ttbar_%i_%i_%i",i,j,k);
          h_v_jettheta_deltaE_ttbar[i][j][k]= new TH1D (name,name,20,0,3.14);
          sprintf(name,"v_jettheta_deltaE_ttbar_qg_%i_%i_%i",i,j,k);
          h_v_jettheta_deltaE_ttbar_qg[i][j][k]= new TH1D (name,name,20,0,3.14);
          sprintf(name,"v_jettheta_deltaE_ttbar_gq_%i_%i_%i",i,j,k);
          h_v_jettheta_deltaE_ttbar_gq[i][j][k]= new TH1D (name,name,20,0,3.14);

          sprintf(name,"v_jettheta_deltaE_ttbar_qbarg_%i_%i_%i",i,j,k);
          h_v_jettheta_deltaE_ttbar_qbarg[i][j][k]= new TH1D (name,name,20,0,3.14);
          sprintf(name,"v_jettheta_deltaE_ttbar_gqbar_%i_%i_%i",i,j,k);
          h_v_jettheta_deltaE_ttbar_gqbar[i][j][k]= new TH1D (name,name,20,0,3.14);

          sprintf(name,"v_jettheta_deltaE_ttbar_qbarq_%i_%i_%i",i,j,k);
          h_v_jettheta_deltaE_ttbar_qbarq[i][j][k]= new TH1D (name,name,20,0,3.14);
          sprintf(name,"v_jettheta_deltaE_ttbar_qqbar_%i_%i_%i",i,j,k);
          h_v_jettheta_deltaE_ttbar_qqbar[i][j][k]= new TH1D (name,name,20,0,3.14);
          sprintf(name,"v_jettheta_deltaE_ttbar_gg_%i_%i_%i",i,j,k);
          h_v_jettheta_deltaE_ttbar_gg[i][j][k]= new TH1D (name,name,20,0,3.14);
       }
        sprintf(name,"v_deltaE_ttbar_%i_%i",i,j);
        h_v_deltaE_ttbar[i][j]= new TH1D (name,name,200,-1000,1000);
        sprintf(name,"v_deltaE_ttbar_qg_%i_%i",i,j);
        h_v_deltaE_ttbar_qg[i][j]= new TH1D (name,name,200,-1000,1000);
        sprintf(name,"v_deltaE_ttbar_gq_%i_%i",i,j);
        h_v_deltaE_ttbar_gq[i][j]= new TH1D (name,name,200,-1000,1000);

        sprintf(name,"v_deltaE_ttbar_qbarg_%i_%i",i,j);
        h_v_deltaE_ttbar_qbarg[i][j]= new TH1D (name,name,200,-1000,1000);
        sprintf(name,"v_deltaE_ttbar_gqbar_%i_%i",i,j);
        h_v_deltaE_ttbar_gqbar[i][j]= new TH1D (name,name,200,-1000,1000);

        sprintf(name,"v_deltaE_ttbar_qbarq_%i_%i",i,j);
        h_v_deltaE_ttbar_qbarq[i][j]= new TH1D (name,name,200,-1000,1000);
        sprintf(name,"v_deltaE_ttbar_qqbar_%i_%i",i,j);
        h_v_deltaE_ttbar_qqbar[i][j]= new TH1D (name,name,200,-1000,1000);
        sprintf(name,"v_deltaE_ttbar_gg_%i_%i",i,j);
        h_v_deltaE_ttbar_gg[i][j]= new TH1D (name,name,200,-1000,1000);

        sprintf(name,"v_costheta_j_t_ttbar_%i_%i",i,j);
        h_v_costheta_j_t_ttbar[i][j]= new TH1D (name,name,200,-1,1);
        sprintf(name,"v_costheta_j_t_ttbar_qg_%i_%i",i,j);
        h_v_costheta_j_t_ttbar_qg[i][j]= new TH1D (name,name,200,-1,1);
        sprintf(name,"v_costheta_j_t_ttbar_gq_%i_%i",i,j);
        h_v_costheta_j_t_ttbar_gq[i][j]= new TH1D (name,name,200,-1,1);

        sprintf(name,"v_costheta_j_t_ttbar_qbarg_%i_%i",i,j);
        h_v_costheta_j_t_ttbar_qbarg[i][j]= new TH1D (name,name,200,-1,1);
        sprintf(name,"v_costheta_j_t_ttbar_gqbar_%i_%i",i,j);
        h_v_costheta_j_t_ttbar_gqbar[i][j]= new TH1D (name,name,200,-1,1);

        sprintf(name,"v_costheta_j_t_ttbar_qbarq_%i_%i",i,j);
        h_v_costheta_j_t_ttbar_qbarq[i][j]= new TH1D (name,name,200,-1,1);
        sprintf(name,"v_costheta_j_t_ttbar_qqbar_%i_%i",i,j);
        h_v_costheta_j_t_ttbar_qqbar[i][j]= new TH1D (name,name,200,-1,1);
        sprintf(name,"v_costheta_j_t_ttbar_gg_%i_%i",i,j);
        h_v_costheta_j_t_ttbar_gg[i][j]= new TH1D (name,name,200,-1,1);

     }
   }



   double sum_weight=0;

   //nentries=100;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if (jentry%100000==0)cout <<"AHANDA YENI OLAY "<<jentry<<"/"<<nentries<<endl;
      // if (Cut(ientry) < 0) continue;
      //cout<<"new event  "<<endl;
      int n_gluon=0;
      //
      double w0=1;
      if(weight_amcNLO->size()>0)double w0=weight_amcNLO->at(0);
      //cout<<w0<<endl;
      sum_weight+=w0;
      bool st21=false;
      vector<int> parton_id;
      TLorentzVector extra_parton_vector;
      int extra_parton_id=-99;
      TLorentzVector top_tmp;
      top_tmp.SetPtEtaPhiE(St03Pt->at(4),St03Eta->at(4),St03Phi->at(4),St03E->at(4));
      TLorentzVector atop_tmp;
      atop_tmp.SetPtEtaPhiE(St03Pt->at(5),St03Eta->at(5),St03Phi->at(5),St03E->at(5));
      h_top_M_st3->Fill(top_tmp.M(),w0);
      h_atop_M_st3->Fill(atop_tmp.M(),w0);
      for(unsigned int st3_ind=0; st3_ind<St03Pt->size();st3_ind++){
       // cout<<St03Id->at(st3_ind)<<"  "<<st3_ind<<endl;
        if(St03Status->at(st3_ind)==3 &&st3_ind>1&&st3_ind<4){//incoming partons 3 for old samples with phythia 8
          parton_id.push_back(St03Id->at(st3_ind));
          if(fabs(St03Id->at(st3_ind))==21)n_gluon++;

        }

        if(St03Status->at(st3_ind)==3 &&st3_ind==6){//incoming partons 3 for old samples with phythia 8
          TLorentzVector parton_tmp;
          parton_tmp.SetPtEtaPhiE(St03Pt->at(st3_ind),St03Eta->at(st3_ind),St03Phi->at(st3_ind),St03E->at(st3_ind));
          extra_parton_id=St03Id->at(st3_ind);
          extra_parton_vector=parton_tmp;
          //if(fabs(St03Id->at(st3_ind))==21)n_gluon++;

        }


       if(St03Status->at(st3_ind)==21 &&st3_ind<2){//incoming partons 21 for new samples with phythia 8
          parton_id.push_back(St03Id->at(st3_ind));
          if(fabs(St03Id->at(st3_ind))==21)n_gluon++; 
          st21==true;
        }
      }

      vector<TLorentzVector>lepton_vector;
      vector<TLorentzVector>nu_vector;
      vector<TLorentzVector>light_jet_vector;
      vector<TLorentzVector>b_jet_vector;
      vector<int> b_jet_id;
      TLorentzVector top_vector;
      TLorentzVector atop_vector;
      vector<int> lepton_id;
      unsigned int ind_check=-99;
      for(unsigned int st1_ind=0; st1_ind<Bare01LepPt->size();st1_ind++){
        if(st1_ind==ind_check) continue;
        //if(Bare01LepPt->at(st1_ind)<20)continue;
        int lep_id= Bare01LepId->at(st1_ind);
        TLorentzVector lep_tmp;
        lep_tmp.SetPtEtaPhiE(Bare01LepPt->at(st1_ind),Bare01LepEt->at(st1_ind),Bare01LepPhi->at(st1_ind),Bare01LepE->at(st1_ind));
       // cout<<st1_ind<<	"  "<<lep_id<<"  "<<endl;
        for(unsigned int st1_ind_2=st1_ind; st1_ind_2<Bare01LepPt->size();st1_ind_2++){

          TLorentzVector nu_tmp;
          nu_tmp.SetPtEtaPhiE(Bare01LepPt->at(st1_ind_2),Bare01LepEt->at(st1_ind_2),Bare01LepPhi->at(st1_ind_2),Bare01LepE->at(st1_ind_2));
          int nu_id= Bare01LepId->at(st1_ind_2);
          if((fabs(lep_id)==11 || fabs(lep_id)==13 )&&lep_id*nu_id<0 && (fabs(nu_id)-fabs(lep_id))==1){
            lepton_id.push_back(lep_id);
            lepton_vector.push_back(lep_tmp);
            nu_vector.push_back(nu_tmp);
            ind_check=st1_ind_2;
            break;
          }
         if((fabs(lep_id)==12 || fabs(lep_id)==14 )&&lep_id*nu_id<0 && (fabs(lep_id)-fabs(nu_id))==1){
            lepton_id.push_back(nu_id);
            lepton_vector.push_back(nu_tmp);
            nu_vector.push_back(lep_tmp);
            ind_check=st1_ind_2;
            break;
          }
        }    
      }

      for(unsigned int jet_ind=0; jet_ind<GjPt->size();jet_ind++){ 
        //if(GjPt->at(jet_ind)<20)continue;
        bool match_lep=false;
        bool match_b=false;
        TLorentzVector jet_tmp;
        jet_tmp.SetPtEtaPhiE(GjPt->at(jet_ind),Gjeta->at(jet_ind),Gjphi->at(jet_ind),GjE->at(jet_ind));
        /*for(unsigned int st1_ind=0; st1_ind<Bare01LepPt->size();st1_ind++){
          if(Bare01LepPt->at(st1_ind)<20)continue;
          if(fabs(Bare01LepId->at(st1_ind))==11 || fabs(Bare01LepId->at(st1_ind))==13 ||fabs(Bare01LepId->at(st1_ind))==12 ||fabs(Bare01LepId->at(st1_ind))==14||   
          fabs(Bare01LepId->at(st1_ind))==16){
            TLorentzVector lep_tmp;
            lep_tmp.SetPtEtaPhiE(Bare01LepPt->at(st1_ind),Bare01LepEt->at(st1_ind),Bare01LepPhi->at(st1_ind),Bare01LepE->at(st1_ind));
            double deltaR=DeltaR(jet_tmp.Eta(),lep_tmp.Eta(),jet_tmp.Phi(),lep_tmp.Phi());
            h_deltar_jet_b->Fill(deltaR,w0);
            if(deltaR<0.5){
              match_lep=true;
            }
          }
        }*/

        if(lepton_vector.size()>1){
            double deltaR1=DeltaR(jet_tmp.Eta(),lepton_vector[0].Eta(),jet_tmp.Phi(),lepton_vector[0].Phi());
            double deltaR2=DeltaR(jet_tmp.Eta(),nu_vector[0].Eta(),jet_tmp.Phi(),nu_vector[0].Phi());
            double deltaR3=DeltaR(jet_tmp.Eta(),lepton_vector[1].Eta(),jet_tmp.Phi(),lepton_vector[1].Phi());
            double deltaR4=DeltaR(jet_tmp.Eta(),nu_vector[1].Eta(),jet_tmp.Phi(),nu_vector[1].Phi());
            if(deltaR1<0.5 ||deltaR2<0.5 ||deltaR3<0.5 ||deltaR4<0.5 ){
              match_lep=true;
            }
            if(match_lep)continue;
        }
        int id_b=0;
        for(unsigned int st3_ind=0; st3_ind<St03Pt->size();st3_ind++){
          if(fabs(St03Id->at(st3_ind))==5){
            TLorentzVector lep_tmp;
            lep_tmp.SetPtEtaPhiE(St03Pt->at(st3_ind),St03Eta->at(st3_ind),St03Phi->at(st3_ind),St03E->at(st3_ind));
            double deltaR=DeltaR(jet_tmp.Eta(),lep_tmp.Eta(),jet_tmp.Phi(),lep_tmp.Phi());
            if(deltaR<0.1){
              //cout<<St03Id->at(st3_ind)<<"  "<<deltaR<<endl;
              match_b=true;
              id_b=St03Id->at(st3_ind);
            }
          }          
        }
        if(match_b){
          b_jet_vector.push_back(jet_tmp);
          b_jet_id.push_back(id_b);
        }
        if(!match_b&&GjPt->at(jet_ind)>20){
          double deltaR_ljet_st3q=DeltaR(jet_tmp.Eta(),extra_parton_vector.Eta(),jet_tmp.Phi(),extra_parton_vector.Phi());
          /*if(!(deltaR_ljet_st3q<0.1 &&(fabs(extra_parton_id)==21 ||fabs(extra_parton_id)<6) ))*/light_jet_vector.push_back(jet_tmp);
        }
      }
      //cout<<lepton_id.size()<<endl;
      if(light_jet_vector.size()<2)continue;
      if(lepton_id.size()>=1){//l+jet

        TLorentzVector w1=(lepton_vector[0]+nu_vector[0]);
        double mw=80.4;
        double mwdiff=9999.;
        unsigned int jind1=-99;
        unsigned int jind2=-99;
        unsigned int jind_extra=-99;
        for(unsigned int ljet_ind=0;ljet_ind<light_jet_vector.size();ljet_ind++){
          for(unsigned int ljet_indd=ljet_ind;ljet_indd<light_jet_vector.size();ljet_indd++){
            if (ljet_ind==ljet_indd)continue;
            double mtemp=(light_jet_vector[ljet_ind]+light_jet_vector[ljet_indd]).M();
            if(fabs(mtemp-mw)<mwdiff){
              mwdiff=fabs(mtemp-mw);
              jind1=ljet_ind;
              jind2=ljet_indd;
            }

          }
        }
        //cout <<jind1<<" "<<jind2<<"  "<< mwdiff<<endl;
        for(unsigned int ljet_ind=0;ljet_ind<light_jet_vector.size();ljet_ind++){
          if((ljet_ind<jind1 &&ljet_ind<jind2) || (ljet_ind>jind1 &&ljet_ind<jind2)||(ljet_ind>jind1 &&ljet_ind>jind2)){
            jind_extra=ljet_ind;
            break;
          }
        }
        TLorentzVector w2=(light_jet_vector[jind1]+light_jet_vector[jind2]);
        //cout<<w1.M()<<"  "<<w2.M()<<endl;
 /*         if(b_jet_vector.size()==2 &&light_jet_vector.size()==1 ){
          if(lepton_id[0]<0){
  
            double M1=fabs((w1+b_jet_vector[0]).M()-172.5);
            double M2=fabs((w1+b_jet_vector[1]).M()-172.5);
            if(M1<M2){
              top_vector=(w1+b_jet_vector[0]);
              atop_vector=(w2+b_jet_vector[1]);
            }
            if(M1>M2){
              top_vector=(w1+b_jet_vector[1]);
              atop_vector=(w2+b_jet_vector[0]);
            }
            
          }

          if(lepton_id[0]>0){
            h_Wplus_M->Fill(w2.M(),w0);
            h_Wminus_M->Fill(w1.M(),w0);
            double M1=fabs((w1+b_jet_vector[0]).M()-172.5);
            double M2=fabs((w1+b_jet_vector[1]).M()-172.5);
            if(M1<M2){
              atop_vector=(w1+b_jet_vector[0]);
              top_vector=(w2+b_jet_vector[1]);
            }
            if(M1>M2){
              atop_vector=(w1+b_jet_vector[1]);
              top_vector=(w2+b_jet_vector[0]);
            }           
          }

*/
       if(lepton_id[0]<0){
            h_Wplus_M->Fill(w1.M(),w0);
            h_Wminus_M->Fill(w2.M(),w0);
       }
       if (lepton_id[0]>0){
            h_Wminus_M->Fill(w1.M(),w0);
            h_Wplus_M->Fill(w2.M(),w0);
       }
       h_Whad_M->Fill(w2.M(),w0);
       h_Wlep_M->Fill(w1.M(),w0);
 
       if(b_jet_vector.size()>=2 &&(b_jet_id[0]*b_jet_id[1])<0 ){ 
        // cout<<b_jet_id[0]<<" "<<b_jet_id[1]<<endl;
         if(lepton_id[0]<0){
            //h_Wplus_M->Fill(w1.M(),w0);
            //h_Wminus_M->Fill(w2.M(),w0);
            if(b_jet_id[0]>0){
              top_vector=(w1+b_jet_vector[0]);
              atop_vector=(w2+b_jet_vector[1]);
            }  
            if(b_jet_id[1]>0){
              top_vector=(w1+b_jet_vector[1]);
              atop_vector=(w2+b_jet_vector[0]);
            }  
          }

         if (lepton_id[0]>0){
           // h_Wplus_M->Fill(w2.M(),w0);
           // h_Wminus_M->Fill(w1.M(),w0);
            if(b_jet_id[0]>0){
              top_vector=(w2+b_jet_vector[0]);
              atop_vector=(w1+b_jet_vector[1]);
            }      
            if(b_jet_id[1]>0){
              top_vector=(w2+b_jet_vector[1]);
              atop_vector=(w1+b_jet_vector[0]);
            }      
          }
          if(light_jet_vector.size()<3)continue;
         // cout<<"Top st3 mass, atop st3 mass, top st1 reco mass, atop st1 reco mass: "<<top_tmp.M()<<" , "<<atop_tmp.M()<<" , "<<top_vector.M()<<" , "<<atop_vector.M()<<endl;
          h_top_M->Fill(top_vector.M(),w0);
          h_atop_M->Fill(atop_vector.M(),w0);
          h_top_Pt->Fill(top_vector.Pt(),w0);
          h_atop_Pt->Fill(atop_vector.Pt(),w0);
          TLorentzVector ttj_vector=top_vector+atop_vector+light_jet_vector[jind_extra];
          TLorentzVector tt_vector=top_vector+atop_vector;
          h_ttj_Y->Fill(ttj_vector.Rapidity(),w0);
          if(n_gluon==0)h_ttj_Y_qq->Fill(ttj_vector.Rapidity(),w0);
          if(n_gluon==1)h_ttj_Y_qg->Fill(ttj_vector.Rapidity(),w0);
          if(n_gluon==2)h_ttj_Y_gg->Fill(ttj_vector.Rapidity(),w0);
          TLorentzVector parton_one;
          TLorentzVector parton_two;
          if(!st21){
            parton_one.SetPtEtaPhiE(St03Pt->at(2), St03Eta->at(2), St03Phi->at(2), St03E->at(2));
            parton_two.SetPtEtaPhiE(St03Pt->at(3), St03Eta->at(3), St03Phi->at(3), St03E->at(3));
          }
          if(st21){
            parton_one.SetPtEtaPhiE(St03Pt->at(0), St03Eta->at(0), St03Phi->at(0), St03E->at(0));
            parton_two.SetPtEtaPhiE(St03Pt->at(1), St03Eta->at(1), St03Phi->at(1), St03E->at(1));
          }
          TLorentzVector parton_sum= parton_one+parton_two;
          double Jettheta_before=2*atan(exp(-1*light_jet_vector[jind_extra].Eta()));
 
          h_deltae_partons_before->Fill(parton_one.E()-parton_two.E(),w0);
          TLorentzVector top_vector_ttbar=top_vector;
          TLorentzVector atop_vector_ttbar=atop_vector;
          TLorentzVector light_jet_vector_ttbar=light_jet_vector[jind_extra];

          top_vector_ttbar.Boost(-tt_vector.BoostVector());
	  atop_vector_ttbar.Boost(-tt_vector.BoostVector());
          light_jet_vector_ttbar.Boost(-tt_vector.BoostVector());

          top_vector.Boost(-ttj_vector.BoostVector());
	  atop_vector.Boost(-ttj_vector.BoostVector());
          light_jet_vector[jind_extra].Boost(-ttj_vector.BoostVector());
          parton_one.Boost(-ttj_vector.BoostVector());
          parton_two.Boost(-ttj_vector.BoostVector());
/*
          top_vector.Boost(-parton_sum.BoostVector());
	  atop_vector.Boost(-parton_sum.BoostVector());
          light_jet_vector[0].Boost(-parton_sum.BoostVector());
          parton_one.Boost(-parton_sum.BoostVector());
          parton_two.Boost(-parton_sum.BoostVector());
*/
          //if(fabs(ttj_vector.Rapidity())<0.5)continue;
          h_deltae_partons_after->Fill(parton_one.E()-parton_two.E(),w0);
          double Jettheta_after=2*atan(exp(-1*light_jet_vector[jind_extra].Eta()));
        
          double theta_t_jet=top_vector_ttbar.Angle(light_jet_vector_ttbar.Vect());
          double cos_theta_t_jet=cos(theta_t_jet);
          double Jettheta_ttbar=2*atan(exp(-1*light_jet_vector_ttbar.Eta()));

          double deltaE=top_vector.E()-atop_vector.E();
          h_costheta_j_t_ttbar->Fill(cos_theta_t_jet,w0);
          h_deltaE_ttbar->Fill(deltaE,w0);
          if(deltaE>0)h_jettheta_deltaE_pos->Fill(Jettheta_after,w0);
          if(deltaE<0)h_jettheta_deltaE_neg->Fill(Jettheta_after,w0);
          if(cos_theta_t_jet>0)h_jettheta_costheta_j_t_pos->Fill(Jettheta_ttbar,w0);
          if(cos_theta_t_jet<0)h_jettheta_costheta_j_t_neg->Fill(Jettheta_ttbar,w0);

          bool isgg=false, isgq=false,isqg=false, isgqbar=false,isqbarg=false, isqqbar=false,isqbarq=false;
          if(n_gluon==0){
            if(parton_id[0]>0 &&parton_id[1]<0){
              h_costheta_j_t_ttbar_qqbar->Fill(cos_theta_t_jet,w0);
              h_deltaE_ttbar_qqbar->Fill(deltaE,w0);
              if(deltaE>0)h_jettheta_deltaE_pos_qqbar->Fill(Jettheta_after,w0);
              if(deltaE<0)h_jettheta_deltaE_neg_qqbar->Fill(Jettheta_after,w0);
              if(cos_theta_t_jet>0)h_jettheta_costheta_j_t_pos_qqbar->Fill(Jettheta_ttbar,w0);
              if(cos_theta_t_jet<0)h_jettheta_costheta_j_t_neg_qqbar->Fill(Jettheta_ttbar,w0);
              isqqbar=true;
            }

            if(parton_id[0]<0 &&parton_id[1]>0){
              h_costheta_j_t_ttbar_qbarq->Fill(cos_theta_t_jet,w0);
              h_deltaE_ttbar_qbarq->Fill(deltaE,w0);
              if(deltaE>0)h_jettheta_deltaE_pos_qbarq->Fill(Jettheta_after,w0);
              if(deltaE<0)h_jettheta_deltaE_neg_qbarq->Fill(Jettheta_after,w0);
              if(cos_theta_t_jet>0)h_jettheta_costheta_j_t_pos_qbarq->Fill(Jettheta_ttbar,w0);
              if(cos_theta_t_jet<0)h_jettheta_costheta_j_t_neg_qbarq->Fill(Jettheta_ttbar,w0);
              isqbarq=true;
            }
          }

          if(n_gluon==1){
            if(parton_id[0]*parton_id[1]>0){

              if(fabs(parton_id[0])<6 &&parton_id[1]>6){
                h_costheta_j_t_ttbar_qg->Fill(cos_theta_t_jet,w0);
                h_deltaE_ttbar_qg->Fill(deltaE,w0);
                if(deltaE>0)h_jettheta_deltaE_pos_qg->Fill(Jettheta_after,w0);
                if(deltaE<0)h_jettheta_deltaE_neg_qg->Fill(Jettheta_after,w0);
                if(cos_theta_t_jet>0)h_jettheta_costheta_j_t_pos_qg->Fill(Jettheta_ttbar,w0);
                if(cos_theta_t_jet<0)h_jettheta_costheta_j_t_neg_qg->Fill(Jettheta_ttbar,w0);
                isqg=true;
              }
              if(fabs(parton_id[0])>6 &&parton_id[1]<6){
                h_costheta_j_t_ttbar_gq->Fill(cos_theta_t_jet,w0);
                h_deltaE_ttbar_gq->Fill(deltaE,w0);
                if(deltaE>0)h_jettheta_deltaE_pos_gq->Fill(Jettheta_after,w0);
                if(deltaE<0)h_jettheta_deltaE_neg_gq->Fill(Jettheta_after,w0);
                if(cos_theta_t_jet>0)h_jettheta_costheta_j_t_pos_gq->Fill(Jettheta_ttbar,w0);
                if(cos_theta_t_jet<0)h_jettheta_costheta_j_t_neg_gq->Fill(Jettheta_ttbar,w0);
                isgq=true;
 
              }
            }

            if(parton_id[0]*parton_id[1]<0){

              if(fabs(parton_id[0])<6 &&parton_id[1]>6){
                h_costheta_j_t_ttbar_qbarg->Fill(cos_theta_t_jet,w0);
                h_deltaE_ttbar_qbarg->Fill(deltaE,w0);
                if(deltaE>0)h_jettheta_deltaE_pos_qbarg->Fill(Jettheta_after,w0);
                if(deltaE<0)h_jettheta_deltaE_neg_qbarg->Fill(Jettheta_after,w0);
                if(cos_theta_t_jet>0)h_jettheta_costheta_j_t_pos_qbarg->Fill(Jettheta_ttbar,w0);
                if(cos_theta_t_jet<0)h_jettheta_costheta_j_t_neg_qbarg->Fill(Jettheta_ttbar,w0);
                isqbarg=true;
              }
              if(fabs(parton_id[0])>6 &&parton_id[1]<6){
                h_costheta_j_t_ttbar_gqbar->Fill(cos_theta_t_jet,w0);
                h_deltaE_ttbar_gqbar->Fill(deltaE,w0);
                if(deltaE>0)h_jettheta_deltaE_pos_gqbar->Fill(Jettheta_after,w0);
                if(deltaE<0)h_jettheta_deltaE_neg_gqbar->Fill(Jettheta_after,w0);
                if(cos_theta_t_jet>0)h_jettheta_costheta_j_t_pos_gqbar->Fill(Jettheta_ttbar,w0);
                if(cos_theta_t_jet<0)h_jettheta_costheta_j_t_neg_gqbar->Fill(Jettheta_ttbar,w0);
                isgqbar=true;
              }
            }

          }

          if(n_gluon==2){
            h_costheta_j_t_ttbar_gg->Fill(cos_theta_t_jet,w0);
            h_deltaE_ttbar_gg->Fill(deltaE,w0);
            if(deltaE>0)h_jettheta_deltaE_pos_gg->Fill(Jettheta_after,w0);
            if(deltaE<0)h_jettheta_deltaE_neg_gg->Fill(Jettheta_after,w0);
            if(cos_theta_t_jet>0)h_jettheta_costheta_j_t_pos_gg->Fill(Jettheta_ttbar,w0);
            if(cos_theta_t_jet<0)h_jettheta_costheta_j_t_neg_gg->Fill(Jettheta_ttbar,w0);
            isgg=true;
          }
          if(fabs(light_jet_vector[jind_extra].Rapidity())<0.5){//Asymetry wrt different cuts
            for(int i = 0; i<3;i++){//ttj rapidity
              for(int j = 0; j<3;j++){//De
                if(fabs(ttj_vector.Rapidity())>cut_rapidity[i] &&fabs(deltaE)>cut_de[j] ){
                  h_v_deltaE_ttbar[i][j]->Fill(deltaE,w0);
                  h_v_costheta_j_t_ttbar[i][j]->Fill(cos_theta_t_jet,w0);
                  if(isgg){
                    h_v_deltaE_ttbar_gg[i][j]->Fill(deltaE,w0);
                    h_v_costheta_j_t_ttbar_gg[i][j]->Fill(cos_theta_t_jet,w0);
                  }
                  if(isqg){
                    h_v_deltaE_ttbar_qg[i][j]->Fill(deltaE,w0);
                    h_v_costheta_j_t_ttbar_qg[i][j]->Fill(cos_theta_t_jet,w0);
                  }
                  if(isgq){ 
		    h_v_deltaE_ttbar_gq[i][j]->Fill(deltaE,w0);
                    h_v_costheta_j_t_ttbar_gq[i][j]->Fill(cos_theta_t_jet,w0);
                  }
                  if(isqbarg){
		    h_v_deltaE_ttbar_qbarg[i][j]->Fill(deltaE,w0);
                    h_v_costheta_j_t_ttbar_qbarg[i][j]->Fill(cos_theta_t_jet,w0);
                  }
                  if(isgqbar){
		    h_v_deltaE_ttbar_gqbar[i][j]->Fill(deltaE,w0);
                    h_v_costheta_j_t_ttbar_gqbar[i][j]->Fill(cos_theta_t_jet,w0);
                  }
                  if(isqbarq){
		    h_v_deltaE_ttbar_qbarq[i][j]->Fill(deltaE,w0);
                    h_v_costheta_j_t_ttbar_qbarq[i][j]->Fill(cos_theta_t_jet,w0);
                  }
                  if(isqqbar){
		    h_v_deltaE_ttbar_qqbar[i][j]->Fill(deltaE,w0);
                    h_v_costheta_j_t_ttbar_qqbar[i][j]->Fill(cos_theta_t_jet,w0);
                  }
                  for(int k = 0; k<2;k++){//De
                    if((k==0&&deltaE>0)||(k==1&&deltaE<0)){

                      h_v_jettheta_deltaE_ttbar[i][j][k]->Fill(Jettheta_after,w0);
                      if(isgg){ 
                        h_v_jettheta_deltaE_ttbar_gg[i][j][k]->Fill(Jettheta_after,w0);
                      }
                      if(isqg){ 
                        h_v_jettheta_deltaE_ttbar_qg[i][j][k]->Fill(Jettheta_after,w0);
                      }
                      if(isgq){ 
                        h_v_jettheta_deltaE_ttbar_gq[i][j][k]->Fill(Jettheta_after,w0);
                      }

                      if(isqbarg){ 
                        h_v_jettheta_deltaE_ttbar_qbarg[i][j][k]->Fill(Jettheta_after,w0);
                      }
                      if(isgqbar){ 
                        h_v_jettheta_deltaE_ttbar_gqbar[i][j][k]->Fill(Jettheta_after,w0);
                      }

                      if(isqbarq){ 
                        h_v_jettheta_deltaE_ttbar_qbarg[i][j][k]->Fill(Jettheta_after,w0);
                      }
                      if(isqqbar){ 
                        h_v_jettheta_deltaE_ttbar_gqbar[i][j][k]->Fill(Jettheta_after,w0);
                      }
                    }
                  }
                }
              }
            }
          }
        }//end of jet mult requirement
      }//end dilepton
    }

  TTree *weight_tree;
  weight_tree = new TTree("tree","tree");
  weight_tree->Branch("sum_weight",&sum_weight);

  weight_tree->Fill();

  weight_tree->Print();  
  file_out->Write();
  file_out->Close();
}
