#define ttjana_reco_cxx

#include "ttjana_reco.h"
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
//#include "standalone_LumiReWeighting.h"

void ttjana_reco::Loop()
{

   TH1::SetDefaultSumw2();
   TH2::SetDefaultSumw2();

//   In a ROOT session, you can do:
//      Root > .L ttjana_reco.C
//      Root > ttjana_reco t
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

   Long64_t nentries = fChain->GetEntries();
   //cout<<fChain->GetEntries()<<endl;
   Long64_t nbytes = 0, nb = 0;


   TFile* file_out = new TFile(name,"RECREATE"); 
   file_out->cd();	
   TH1* h_number_st3 = new TH1D ("number_st3","number_st3",20,-0.5,19.5);
   TH1* h_number_b = new TH1D ("number_b","number_b",20,-0.5,19.5);
   TH1* h_number_decay = new TH1D ("number_decay","number_decay",20,-0.5,19.5);
   TH1* h_gen_nlep = new TH1D ("gen_nlep","gen_nlep",10,-0.5,9.5);
   TH1* h_gen_nljet = new TH1D ("gen_nljet","gen_nljet",10,-0.5,9.5);
   TH1* h_gen_nbjet = new TH1D ("gen_nbjet","gen_nbjet",10,-0.5,9.5);

   TH1* h_reco_nlep = new TH1D ("reco_nlep","reco_nlep",10,-0.5,9.5);
   TH1* h_reco_nljet = new TH1D ("reco_nljet","reco_nljet",10,-0.5,9.5);
   TH1* h_reco_njet = new TH1D ("reco_njet","reco_njet",10,-0.5,9.5);
   TH1* h_reco_nbjet = new TH1D ("reco_nbjet","reco_nbjet",10,-0.5,9.5);

   TH1* h_reco_njet_1muev = new TH1D ("reco_njet_1muev","reco_njet_1muev",10,-0.5,9.5);
   TH1* h_reco_nbjet_1muev = new TH1D ("reco_nbjet_1muev","reco_nbjet_1muev",10,-0.5,9.5);
   TH1* h_reco_nljet_1muev = new TH1D ("reco_nljet_1muev","reco_nljet_1muev",10,-0.5,9.5);

   TH1* h_reco_njet_1muev_inc = new TH1D ("reco_njet_1muev_inc","reco_njet_1muev_inc",10,-0.5,9.5);
   TH1* h_reco_nbjet_1muev_inc = new TH1D ("reco_nbjet_1muev_inc","reco_nbjet_1muev_inc",10,-0.5,9.5);
   TH1* h_reco_nljet_1muev_inc = new TH1D ("reco_nljet_1muev_inc","reco_nljet_1muev_inc",10,-0.5,9.5);

   TH1* h_gen_dijet_mass= new TH1D ("gen_dijet_mass","gen_dijet_mass",100,0,1000);

   TH1* h_gen_m_top= new TH1D ("gen_m_top","gen_m_top",100,0,1000);
   TH1* h_gen_m_atop= new TH1D ("gen_m_atop","gen_m_atop",100,0,1000);


   TH1* h_muon_pt= new TH1D ("muon_pt","muon_pt",100,0,1000);
   TH1* h_muon_eta= new TH1D ("muon_eta","muon_eta",100,-2.5,2.5);

   TH1* h_ljet_pt= new TH1D ("ljet_pt","ljet_pt",100,0,1000);
   TH1* h_ljet_eta= new TH1D ("jlet_eta","ljet_eta",100,-2.5,2.5);

   TH1* h_sljet_pt= new TH1D ("sljet_pt","ljet_pt",100,0,1000);
   TH1* h_sljet_eta= new TH1D ("sjlet_eta","ljet_eta",100,-2.5,2.5);
   TH1* h_MET_ET= new TH1D ("MET_ET","MET_ET",100,0,1000);



   TH1* h_muon_pt_1muev= new TH1D ("muon_pt_1muev","muon_pt_1muev",100,0,1000);
   TH1* h_muon_eta_1muev= new TH1D ("muon_eta_1muev","muon_eta_1muev",100,-2.5,2.5);

   TH1* h_ljet_pt_1muev= new TH1D ("ljet_pt_1muev","ljet_pt_1muev",100,0,1000);
   TH1* h_ljet_eta_1muev= new TH1D ("jlet_eta_1muev","ljet_eta_1muev",100,-2.5,2.5);

   TH1* h_sljet_pt_1muev= new TH1D ("sljet_pt_1muev","ljet_pt_1muev",100,0,1000);
   TH1* h_sljet_eta_1muev= new TH1D ("sjlet_eta_1muev","ljet_eta_1muev",100,-2.5,2.5);
   TH1* h_MET_ET_1muev= new TH1D ("MET_ET_1muev","MET_ET_1muev",100,0,1000);

   TH1* h_muon_pt_1muev_inc= new TH1D ("muon_pt_1muev_inc","muon_pt_1muev_inc",100,0,1000);
   TH1* h_muon_eta_1muev_inc= new TH1D ("muon_eta_1muev_inc","muon_eta_1muev_inc",100,-2.5,2.5);

   TH1* h_ljet_pt_1muev_inc= new TH1D ("ljet_pt_1muev_inc","ljet_pt_1muev_inc",100,0,1000);
   TH1* h_ljet_eta_1muev_inc= new TH1D ("jlet_eta_1muev_inc","ljet_eta_1muev_inc",100,-2.5,2.5);

   TH1* h_sljet_pt_1muev_inc= new TH1D ("sljet_pt_1muev_inc","ljet_pt_1muev_inc",100,0,1000);
   TH1* h_sljet_eta_1muev_inc= new TH1D ("sjlet_eta_1muev_inc","ljet_eta_1muev_inc",100,-2.5,2.5);
   TH1* h_MET_ET_1muev_inc= new TH1D ("MET_ET_1muev_inc","MET_ET_1muev_inc",100,0,1000);



   TH1* h_MTW= new TH1D ("MTW","MTW",100,0,1000);
   TH1* h_MTW_1muev= new TH1D ("MTW_1muev","MTW_1muev",100,0,1000);
   TH1* h_MTW_1muev_inc= new TH1D ("MTW_1muev_inc","MTW_1muev_inc",100,0,1000);

   TH1* h_dijet_mass= new TH1D ("dijet_mass","dijet_mass",100,0,1000);

   TH1* h_m_thad= new TH1D ("m_thad","m_thad",100,0,1000);
   TH1* h_m_tlep= new TH1D ("m_tlep","m_tlep",100,0,1000);

   TH1* h_m_top= new TH1D ("m_top","m_top",100,0,1000);
   TH1* h_m_atop= new TH1D ("m_atop","m_atop",100,0,1000);



     TH1*   h_gen_deltaE= new TH1D ("gen_deltaE","gen_deltaE",200,-1000,1000);

     TH1*   h_rec_deltaE= new TH1D ("rec_deltaE","rec_deltaE",200,-1000,1000);
     TH1*   h_gen_ttjY= new TH1D ("gen_ttjY","gen_ttjY",50,-5,5);
     TH1*   h_rec_ttjY= new TH1D ("rec_ttjY","rec_ttjY",50,-5,5);

   TH1* h_jettheta[10][2][2][3][3];
   TH1* h_gen_jettheta[10][2][2][3][3];
   double cut_rapidity[]={0,0.5,1.0};
   double cut_de[]={0,50,120};
   char nam[10000];
   for(int i = 0; i<10;i++){//flavor
     for(int j = 0; j<2;j++){//pos / neg
       for(int k = 0; k<2;k++){//jet rapidity cut
         for(int l = 0; l<3;l++){// ttj rapidity cut
           for(int m = 0; m<3;m++){//de
             sprintf(nam,"v_jettheta_%i_%i_%i_%i_%i",i,j,k,l,m);
             h_jettheta[i][j][k][l][m]=new TH1D (nam,nam,20,0,3.14);
             sprintf(nam,"v_gen_jettheta_%i_%i_%i_%i_%i",i,j,k,l,m);
             h_gen_jettheta[i][j][k][l][m]=new TH1D (nam,nam,20,0,3.14);
           }
         }
       }
     }
   }


   double real_count=0;
   double complex_count=0;
   double solved_complex_count=0;
   double real=0;
   double fake=0;
   double miss=0;

   nentries=2000000;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {

      bool gen_sel=false;
      bool rec_sel=false;
      if(jentry%10000==0)cout<<name<<" << "<<jentry<<"/"<<nentries<<endl;
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
        int contb=0;
        int contw=0;
        int n_decay=0;
        int n_mu=0;
        for(unsigned int st3_ind=0; st3_ind<St03Pt->size();st3_ind++){
           //cout<< st3_ind<<"  "<<St03Id->at(st3_ind)<<"  "<<St03MotherId->at(st3_ind)<<"  "<<St03Status->at(st3_ind)<<endl;
           if (fabs(St03Id->at(st3_ind))==5)contb++;
           if (fabs(St03Id->at(st3_ind))==24)contw++;
           if(fabs(St03Id->at(st3_ind))!=5 &&fabs(St03Id->at(st3_ind))!=24&& contb>=2&& contw>=2){
             n_decay++; 
             if(fabs(St03Id->at(st3_ind))==13)n_mu++;
           }
        }




  /*      if(n_decay>4){
        for(unsigned int st3_ind=0; st3_ind<St03Pt->size();st3_ind++){
           cout<< st3_ind<<"  "<<St03Id->at(st3_ind)<<"  "<<St03MotherId->at(st3_ind)<<"  "<<St03Status->at(st3_ind)<<endl;
        }
        cout<<contb<<"  "<<n_decay<<"========================================"<<endl;
        }*/
      if(dosignal && n_mu!=1 ) continue;
      if(dottother && n_mu==1 ) continue;
      h_number_st3->Fill(St03Pt->size()); 
      h_number_b->Fill(contb); 
      h_number_decay->Fill(n_decay); 
      int ind_parton1=-99, ind_parton2=-99;
      //cout<<St03Id->at(0)<<"  "<<St03MotherId->at(0)<<"  "<<St03Id->at(1)<<"  "<<St03MotherId->at(1)<<endl;
      if(St03Id->at(0)==21)ind_parton1=0;
      if(St03Id->at(0)<0 &&fabs(St03Id->at(0))<6 )ind_parton1=-1;
      if(St03Id->at(0)>0 &&fabs(St03Id->at(0))<6 )ind_parton1=1;
      if(St03Id->at(1)==21)ind_parton2=0;
      if(St03Id->at(1)<0 &&fabs(St03Id->at(1))<6 )ind_parton2=-1;
      if(St03Id->at(1)>0 &&fabs(St03Id->at(1))<6 )ind_parton2=1;
      //cout<<ind_parton1<<"  "<<ind_parton2<<endl;
      vector<int> plot_inda;
      plot_inda.push_back(0);
      if(ind_parton1== 0 && ind_parton2== 0)plot_inda.push_back(1); //gg 
      if(ind_parton1== 1 && ind_parton2== 0)plot_inda.push_back(2); //qg 
      if(ind_parton1== 0 && ind_parton2== 1)plot_inda.push_back(3); //gq 
      if(ind_parton1==-1 && ind_parton2== 0)plot_inda.push_back(4); //qbarg 
      if(ind_parton1== 0 && ind_parton2==-1)plot_inda.push_back(5); //gqbar 
      if(ind_parton1== 1 && ind_parton2==-1)plot_inda.push_back(6); //qqbar 
      if(ind_parton1==-1 && ind_parton2== 1)plot_inda.push_back(7); //qbarq
      if((ind_parton1== 1 && ind_parton2== 0 )||(ind_parton1== 0 && ind_parton2== 1 ))plot_inda.push_back(8); //qg  & gq
      if((fabs(ind_parton1)== 1 && ind_parton2== 0 )||(ind_parton1== 0 && fabs(ind_parton2)== 1 ))plot_inda.push_back(9); //qg  & gq
      int mu_index=0;	
      int mu_index20=0;	
      vector<TLorentzVector>mu_vector;
      vector<TLorentzVector>mu_vector20;
      vector<int>mu_charge;
      vector<unsigned int>b_jet_index;
      vector<unsigned int>l_jet_index;
      int jet_index=0;	
      vector<TLorentzVector>jet_vector;


      vector<TLorentzVector>gen_lepton_vector;
      vector<TLorentzVector>gen_nu_vector;
      vector<TLorentzVector>gen_light_jet_vector;
      vector<TLorentzVector>gen_b_jet_vector;
      vector<int> gen_b_jet_id;
      TLorentzVector gen_top_vector;
      TLorentzVector gen_atop_vector;
      vector<int> gen_lepton_id;
      unsigned int ind_check=-99;
      //cout<<"1111111"<<endl;

      int n_gen_lep_30=0;
      for(unsigned int st1_ind=0; st1_ind<Bare01LepPt->size();st1_ind++){
        if(st1_ind==ind_check) continue;


        //if(Bare01LepPt->at(st1_ind)<20)continue;
        int lep_id= Bare01LepId->at(st1_ind);
        TLorentzVector lep_tmp;
        lep_tmp.SetPtEtaPhiE(Bare01LepPt->at(st1_ind),Bare01LepEta->at(st1_ind),Bare01LepPhi->at(st1_ind),Bare01LepE->at(st1_ind));
       // cout<<st1_ind<<	"  "<<lep_id<<"  "<<endl;
        for(unsigned int st1_ind_2=st1_ind; st1_ind_2<Bare01LepPt->size();st1_ind_2++){

          TLorentzVector nu_tmp;
          nu_tmp.SetPtEtaPhiE(Bare01LepPt->at(st1_ind_2),Bare01LepEta->at(st1_ind_2),Bare01LepPhi->at(st1_ind_2),Bare01LepE->at(st1_ind_2));
          int nu_id= Bare01LepId->at(st1_ind_2);
          if( fabs(lep_id)==13 &&lep_id*nu_id<0 && (fabs(nu_id)-fabs(lep_id))==1&&lep_tmp.Pt()>20 && lep_tmp.Eta()<2.4){
            gen_lepton_id.push_back(lep_id);
            gen_lepton_vector.push_back(lep_tmp);
            gen_nu_vector.push_back(nu_tmp);
            ind_check=st1_ind_2;
            if(lep_tmp.Pt()>30)n_gen_lep_30++;
            break;
          }
         if( fabs(lep_id)==14 &&lep_id*nu_id<0 && (fabs(lep_id)-fabs(nu_id))==1&&nu_tmp.Pt()>20 && nu_tmp.Eta()<2.4){
            gen_lepton_id.push_back(nu_id);
            gen_lepton_vector.push_back(nu_tmp);
            gen_nu_vector.push_back(lep_tmp);
            ind_check=st1_ind_2;
            if(nu_tmp.Pt()>30)n_gen_lep_30++;
            break;
          }
        }    
      }
      //cout<<"222222222222"<<endl;
        /*if(St03Pt->size()==12){*/

      for(unsigned int jet_ind=0; jet_ind<GjPt->size();jet_ind++){ 
        if(GjPt->at(jet_ind)<30|| Gjeta->at(jet_ind)>2.5)continue;
        bool match_lep=false;
        bool match_b=false;
        TLorentzVector jet_tmp;
        jet_tmp.SetPtEtaPhiE(GjPt->at(jet_ind),Gjeta->at(jet_ind),Gjphi->at(jet_ind),GjE->at(jet_ind));
        if(gen_lepton_vector.size()==1){
            double deltaR1=DeltaR(jet_tmp.Eta(),gen_lepton_vector[0].Eta(),jet_tmp.Phi(),gen_lepton_vector[0].Phi());
            double deltaR2=DeltaR(jet_tmp.Eta(),gen_nu_vector[0].Eta(),jet_tmp.Phi(),gen_nu_vector[0].Phi());
            if(deltaR1<0.5 ||deltaR2<0.5){
              match_lep=true;
            }
            if(match_lep)continue;
        }

      //cout<<"333333333333"<<endl;
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
          gen_b_jet_vector.push_back(jet_tmp);
          gen_b_jet_id.push_back(id_b);
        }
      //cout<<"4444444444endl;
       if(!match_b){
         // double deltaR_ljet_st3q=DeltaR(jet_tmp.Eta(),extra_parton_vector.Eta(),jet_tmp.Phi(),extra_parton_vector.Phi());
          /*if(!(deltaR_ljet_st3q<0.1 &&(fabs(extra_parton_id)==21 ||fabs(extra_parton_id)<6) ))*/gen_light_jet_vector.push_back(jet_tmp);
        }
      }
      //cout<<"5555555555"<<endl;
      double gen_mmin=-9999;
      int gen_ljet_ind1=-99;
      int gen_ljet_ind2=-99;
      h_gen_nlep->Fill(n_gen_lep_30);
      h_gen_nljet->Fill(gen_light_jet_vector.size());
      h_gen_nbjet->Fill(gen_b_jet_vector.size());
      vector<int> gen_a_min;
      int gen_extra_light_index=-99;
      if(n_gen_lep_30==1  &&gen_b_jet_vector.size()==2 && gen_light_jet_vector.size()>=2 ){//gen level l+jet
        for(unsigned int indljet=0;indljet<gen_light_jet_vector.size();indljet++){
         gen_a_min.push_back(indljet);
         for(unsigned int indljet2=indljet;indljet2<gen_light_jet_vector.size();indljet2++){
            if(indljet2==indljet)continue;
            double gen_mmin_temp=(gen_light_jet_vector[indljet]+gen_light_jet_vector[indljet2]).M();
            if(fabs(gen_mmin_temp-80.4)<fabs(gen_mmin-80.4)){
              gen_mmin=gen_mmin_temp;gen_ljet_ind1=indljet;gen_ljet_ind2=indljet2;
            }
          }
        }
        for(unsigned int i=0; i<gen_a_min.size();i++){
          if(gen_a_min[i]==gen_ljet_ind1 ||gen_a_min[i]==gen_ljet_ind2)continue;
          gen_extra_light_index=gen_a_min[i];break;
        }
        
        h_gen_dijet_mass->Fill(gen_mmin);
        if(gen_lepton_id[0]>0){
          if(gen_b_jet_id[0]<0){
            gen_top_vector=gen_lepton_vector[0]+gen_nu_vector[0]+gen_b_jet_vector[0];
            gen_atop_vector=gen_light_jet_vector[gen_ljet_ind1]+gen_light_jet_vector[gen_ljet_ind2]+gen_b_jet_vector[1];
          }
          if(gen_b_jet_id[0]>0){
            gen_top_vector=gen_lepton_vector[0]+gen_nu_vector[0]+gen_b_jet_vector[1];
            gen_atop_vector=gen_light_jet_vector[gen_ljet_ind1]+gen_light_jet_vector[gen_ljet_ind2]+gen_b_jet_vector[0];
          }
        }
        if(gen_lepton_id[0]<0){
          if(gen_b_jet_id[0]<0){
            gen_atop_vector=gen_lepton_vector[0]+gen_nu_vector[0]+gen_b_jet_vector[1];
            gen_top_vector=gen_light_jet_vector[gen_ljet_ind1]+gen_light_jet_vector[gen_ljet_ind2]+gen_b_jet_vector[0];
          }
          if(gen_b_jet_id[0]>0){
            gen_atop_vector=gen_lepton_vector[0]+gen_nu_vector[0]+gen_b_jet_vector[0];
            gen_top_vector=gen_light_jet_vector[gen_ljet_ind1]+gen_light_jet_vector[gen_ljet_ind2]+gen_b_jet_vector[1];
          }
        }
        h_gen_m_top->Fill(gen_top_vector.M());
        h_gen_m_atop->Fill(gen_atop_vector.M());
        gen_sel=true;
        TLorentzVector gen_extra_jet_vector;
        TLorentzVector gen_sum_ttj_vector;
        if(gen_extra_light_index!=-99){
          gen_extra_jet_vector=gen_light_jet_vector[gen_extra_light_index];
          gen_sum_ttj_vector=gen_top_vector+ gen_atop_vector + gen_extra_jet_vector;
          gen_top_vector.Boost(-gen_sum_ttj_vector.BoostVector());
          gen_atop_vector.Boost(-gen_sum_ttj_vector.BoostVector());
          gen_extra_jet_vector.Boost(-gen_sum_ttj_vector.BoostVector());
          double dE=gen_top_vector.E()-gen_atop_vector.E();
          h_gen_deltaE->Fill(dE);
          double ttj_Y=gen_sum_ttj_vector.Rapidity();
          h_gen_ttjY->Fill(ttj_Y);
          double Jettheta_gen=2*atan(exp(-1*gen_extra_jet_vector.Eta()));          
          double rap=gen_extra_jet_vector.Rapidity();

          vector<int> plot_indb;
          vector<int> plot_indc;
          vector<int> plot_indd;
          vector<int> plot_inde;
          if(dE>0)plot_indb.push_back(0);
          if(dE<0)plot_indb.push_back(1);

          plot_indc.push_back(0);
          if(fabs(rap)<0.5) plot_indc.push_back(1);

          if(fabs(ttj_Y)>0)plot_indd.push_back(0);
          if(fabs(ttj_Y)>0.5)plot_indd.push_back(1);
          if(fabs(ttj_Y)>1.0)plot_indd.push_back(2);

          if(fabs(dE)>0)plot_inde.push_back(0);
          if(fabs(dE)>50)plot_inde.push_back(1);
          if(fabs(dE)>120)plot_inde.push_back(2);

          for(unsigned int plota=0;plota<plot_inda.size();plota++){
            for(unsigned int plotb=0;plotb<plot_indb.size();plotb++){
              for(unsigned int plotc=0;plotc<plot_indc.size();plotc++){
                for(unsigned int plotd=0;plotd<plot_indd.size();plotd++){
                  for(unsigned int plote=0;plote<plot_inde.size();plote++){
                     h_gen_jettheta[plot_inda[plota]][plot_indb[plotb]][plot_indc[plotc]][plot_indd[plotd]][plot_inde[plote]]->Fill(Jettheta_gen);
                  }
                }
              }
            }
          }

        }

      }//end gen mult selection
      //cout<<"666666666666"<<endl;









      for(unsigned int mu_ind=0; mu_ind<patMuonPt_->size();mu_ind++){
        if(patMuonPt_->at(mu_ind)>30 && fabs(patMuonEta_->at(mu_ind))<2.4 &&patMuonCombId_->at(mu_ind)>0){
//          cout<<patMuonPt_->size()<<"  " <<mu_ind<<"  "<<patMuonPt_->at(mu_ind)<<endl;
          TLorentzVector tmp;
          tmp.SetPtEtaPhiE(patMuonPt_->at(mu_ind),patMuonEta_->at(mu_ind),patMuonPhi_->at(mu_ind),patMuonEn_->at(mu_ind));
          mu_vector.push_back(tmp);
          mu_charge.push_back(patMuonCharge_->at(mu_ind));
          mu_index++;
       }
        if(patMuonPt_->at(mu_ind)>10 && fabs(patMuonEta_->at(mu_ind))<2.4){
          mu_index20++;
       }
     }



      for(unsigned int jet_ind=0; jet_ind<patJetPfAk05Pt_->size();jet_ind++){

        if(patJetPfAk05Pt_->at(jet_ind)<30. || fabs(patJetPfAk05Eta_->at(jet_ind))>2.5 ||patJetPfAk05LooseId_->at(jet_ind)==0||patJetPfAk05jetpuMVA_->at(jet_ind)<0.697)continue;
          //cout<<patJetPfAk05Pt_->size()<<"  " <<jet_ind<<"  "<<patJetPfAk05Pt_->at(jet_ind)<<endl;
        TLorentzVector tmp;
        tmp.SetPtEtaPhiE(patJetPfAk05Pt_->at(jet_ind),patJetPfAk05Eta_->at(jet_ind),patJetPfAk05Phi_->at(jet_ind),patJetPfAk05En_->at(jet_ind));
        jet_vector.push_back(tmp);
        double dr_j_l=99;
        if(mu_index>0) dr_j_l=DeltaR(tmp.Eta(),mu_vector[0].Eta(),tmp.Phi(),mu_vector[0].Phi());
        if(dr_j_l<0.4)continue;
        if(patJetPfAk05BDiscCSV_->at(jet_ind)>0.697)b_jet_index.push_back(jet_index);//cut value 0.697
        //else l_jet_index.push_back(jet_index);
        jet_index++;
      }
      h_reco_nlep->Fill(mu_index);
      h_reco_nljet->Fill(jet_vector.size()- b_jet_index.size());
      h_reco_njet->Fill(jet_vector.size());
      h_reco_nbjet->Fill( b_jet_index.size());

       if(jet_vector.size()>0){
        h_ljet_pt->Fill(jet_vector[0].Pt());
        h_ljet_eta->Fill(jet_vector[0].Eta());    
       }
       if(jet_vector.size()>1){
        h_sljet_pt->Fill(jet_vector[1].Pt());
        h_sljet_eta->Fill(jet_vector[1].Eta());  
        h_MET_ET->Fill(METPt->at(0));
       }
      if(mu_index==1 &&mu_index20==1){
        double ptll=mu_vector[0].Pt();
        double ptnuu= METPt->at(0);
        TLorentzVector mett;
        mett.SetPxPyPzE(METPx->at(0),METPy->at(0),METPz->at(0),METE->at(0));
        double deltaphii=DeltaPhi(mu_vector[0].Phi(), mett.Phi());
        double cdphii= cos(deltaphii);
	double MTWW=sqrt(2*ptll*ptnuu*(1 -cdphii ));

        h_MTW_1muev->Fill(MTWW);




        h_reco_nljet_1muev->Fill(jet_vector.size()- b_jet_index.size());
        h_reco_njet_1muev->Fill(jet_vector.size());
        h_reco_nbjet_1muev->Fill( b_jet_index.size());
        h_muon_pt_1muev->Fill(mu_vector[0].Pt());
        h_muon_eta_1muev->Fill(mu_vector[0].Eta());
       if(jet_vector.size()>0){
        h_ljet_pt_1muev->Fill(jet_vector[0].Pt());
        h_ljet_eta_1muev->Fill(jet_vector[0].Eta());    
        }
       if(jet_vector.size()>1){
        h_sljet_pt_1muev->Fill(jet_vector[1].Pt());
        h_sljet_eta_1muev->Fill(jet_vector[1].Eta());  
        }
         h_MET_ET_1muev->Fill(METPt->at(0));

      }

      if(mu_index==1){
        double ptll=mu_vector[0].Pt();
        double ptnuu= METPt->at(0);
        TLorentzVector mett;
        mett.SetPxPyPzE(METPx->at(0),METPy->at(0),METPz->at(0),METE->at(0));
        double deltaphii=DeltaPhi(mu_vector[0].Phi(), mett.Phi());
        double cdphii= cos(deltaphii);
	double MTWW=sqrt(2*ptll*ptnuu*(1 -cdphii ));

        h_MTW_1muev_inc->Fill(MTWW);


        h_reco_nljet_1muev_inc->Fill(jet_vector.size()- b_jet_index.size());
        h_reco_njet_1muev_inc->Fill(jet_vector.size());
        h_reco_nbjet_1muev_inc->Fill( b_jet_index.size());
        h_muon_pt_1muev_inc->Fill(mu_vector[0].Pt());
        h_muon_eta_1muev_inc->Fill(mu_vector[0].Eta());
       if(jet_vector.size()>0){
        h_ljet_pt_1muev_inc->Fill(jet_vector[0].Pt());
        h_ljet_eta_1muev_inc->Fill(jet_vector[0].Eta());    
        }
       if(jet_vector.size()>1){
        h_sljet_pt_1muev_inc->Fill(jet_vector[1].Pt());
        h_sljet_eta_1muev_inc->Fill(jet_vector[1].Eta());  
        h_MET_ET_1muev_inc->Fill(METPt->at(0));
        }


      }

      if (jet_vector.size()>=4 && b_jet_index.size()==2 && mu_index==1 &&mu_index20==1){//at least 4 jets, 2 of b jets, 1 muon


        
  
        double pz1=0;
        double pz2=0;
        double MW=80.4;
        double ptl=mu_vector[0].Pt();
        double pzl=mu_vector[0].Pz();
        double El=mu_vector[0].E();
        double ptnu= METPt->at(0);
        TLorentzVector met;
        met.SetPxPyPzE(METPx->at(0),METPy->at(0),METPz->at(0),METE->at(0));
        double deltaphi=DeltaPhi(mu_vector[0].Phi(), met.Phi());
        double cdphi= cos(deltaphi);
	double MTW=sqrt(2*ptl*ptnu*(1 -cdphi ));
        double mu= MW*MW/2 + ptl*ptnu*cdphi;

        double A=mu*pzl/(ptl*ptl);
        double B=mu*mu*pzl*pzl/(pow(ptl,4));
        double C= (El*El*ptnu*ptnu- mu*mu)/(ptl*ptl);
        double D=0;

        ////cout<<MTW<<endl;
        h_MTW->Fill(MTW);
        TLorentzVector nu_complex;
        if((B-C)<0){
        //cout<<"new complex event "<<MTW<<endl;
        bool found=false;  
        double min_i=0;
        double max_i=80;
        
          for(double px_var=min_i;px_var<max_i;px_var+=0.3){
//              double py_var=px_var;
            for(double py_var=0;py_var<=px_var;py_var+=0.3){
              TLorentzVector met_new1;
              met_new1.SetPxPyPzE(METPx->at(0)+px_var,METPy->at(0)+py_var,METPz->at(0),METE->at(0));
              double deltaphi_new1=DeltaPhi(mu_vector[0].Phi(), met_new1.Phi());
              double cdphi_new1= cos(deltaphi_new1);
   	      double MTW_new1=sqrt(2*ptl*met_new1.Pt()*(1 -cdphi_new1 ));
              if(MTW_new1>80.399&&MTW_new1<80.401){//cout<<"MTW old, px var +, py var +, MTW new "<<MTW<<"  "<<px_var<<"  "<<py_var<<"  "<<MTW_new1<<endl;
                double ptnun=met_new1.Pt();
                double mun= MW*MW/2 + ptl*ptnun*cdphi_new1;
                double An=mun*pzl/(ptl*ptl);
                double Bn=mun*mun*pzl*pzl/(pow(ptl,4));
                double Cn= (El*El*ptnun*ptnun- mun*mun)/(ptl*ptl);
                double Dn=0;
                //cout<<"B, C, B-C old; B, C, B-C new"<<B<<"  "<<C<<"  "<<B-C<<"  "<<Bn<<"  "<<Cn<<"  "<<Bn-Cn<<endl;
                A=An;
                nu_complex=met_new1;
                found=true;
                break;
              }
              TLorentzVector met_new2;
              met_new2.SetPxPyPzE(METPx->at(0)+px_var,METPy->at(0)-py_var,METPz->at(0),METE->at(0));
              double deltaphi_new2=DeltaPhi(mu_vector[0].Phi(), met_new2.Phi());
              double cdphi_new2= cos(deltaphi_new2);
   	      double MTW_new2=sqrt(2*ptl*met_new2.Pt()*(1 -cdphi_new2 ));
              if(MTW_new2>80.399&&MTW_new2<80.401){//cout<<"MTW old, px var +, py var -, MTW new "<<MTW<<"  "<<px_var<<"  "<<py_var<<"  "<<MTW_new2<<endl;
                double ptnun=met_new2.Pt();
                double mun= MW*MW/2 + ptl*ptnun*cdphi_new2;
                double An=mun*pzl/(ptl*ptl);
                double Bn=mun*mun*pzl*pzl/(pow(ptl,4));
                double Cn= (El*El*ptnun*ptnun- mun*mun)/(ptl*ptl);
                double Dn=0;
                //cout<<"B, C, B-C old; B, C, B-C new"<<B<<"  "<<C<<"  "<<B-C<<"  "<<Bn<<"  "<<Cn<<"  "<<Bn-Cn<<endl;
                A=An;
                nu_complex=met_new2;
                found=true;
                break;
              }

              TLorentzVector met_new3;
              met_new3.SetPxPyPzE(METPx->at(0)-px_var,METPy->at(0)+py_var,METPz->at(0),METE->at(0));
              double deltaphi_new3=DeltaPhi(mu_vector[0].Phi(), met_new3.Phi());
              double cdphi_new3= cos(deltaphi_new3);
   	      double MTW_new3=sqrt(2*ptl*met_new3.Pt()*(1 -cdphi_new3 ));
              if(MTW_new3>80.399&&MTW_new3<80.401){//cout<<"MTW old, px var -, py var +, MTW new "<<MTW<<"  "<<px_var<<"  "<<py_var<<"  "<<MTW_new3<<endl;
                double ptnun=met_new3.Pt();
                double mun= MW*MW/2 + ptl*ptnun*cdphi_new3;
                double An=mun*pzl/(ptl*ptl);
                double Bn=mun*mun*pzl*pzl/(pow(ptl,4));
                double Cn= (El*El*ptnun*ptnun- mun*mun)/(ptl*ptl);
                double Dn=0;
                //cout<<"B, C, B-C old; B, C, B-C new"<<B<<"  "<<C<<"  "<<B-C<<"  "<<Bn<<"  "<<Cn<<"  "<<Bn-Cn<<endl;
                A=An;
                nu_complex=met_new3;
                found=true;
                break;
              }

              TLorentzVector met_new4;
              met_new4.SetPxPyPzE(METPx->at(0)-px_var,METPy->at(0)-py_var,METPz->at(0),METE->at(0));
              double deltaphi_new4=DeltaPhi(mu_vector[0].Phi(), met_new4.Phi());
              double cdphi_new4= cos(deltaphi_new4);
   	      double MTW_new4=sqrt(2*ptl*met_new4.Pt()*(1 -cdphi_new4 ));
              if(MTW_new4>80.399&&MTW_new4<80.401){//cout<<"MTW old, px var -, py var -, MTW new "<<MTW<<"  "<<px_var<<"  "<<py_var<<"  "<<MTW_new4<<endl;
                double ptnun=met_new4.Pt();
                double mun= MW*MW/2 + ptl*ptnun*cdphi_new4;
                double An=mun*pzl/(ptl*ptl);
                double Bn=mun*mun*pzl*pzl/(pow(ptl,4));
                double Cn= (El*El*ptnun*ptnun- mun*mun)/(ptl*ptl);
                double Dn=0;
                //cout<<"B, C, B-C old; B, C, B-C new"<<B<<"  "<<C<<"  "<<B-C<<"  "<<Bn<<"  "<<Cn<<"  "<<Bn-Cn<<endl;
                A=An;
                nu_complex=met_new4;
                found=true;
                break;
              }
              TLorentzVector met_new5;
              met_new5.SetPxPyPzE(METPx->at(0)+py_var,METPy->at(0)+px_var,METPz->at(0),METE->at(0));
              double deltaphi_new5=DeltaPhi(mu_vector[0].Phi(), met_new5.Phi());
              double cdphi_new5= cos(deltaphi_new5);
   	      double MTW_new5=sqrt(2*ptl*met_new5.Pt()*(1 -cdphi_new5 ));
              if(MTW_new5>80.399&&MTW_new5<80.401){//cout<<"MTW old, px var +, py var +, MTW new "<<MTW<<"  "<<py_var<<"  "<<px_var<<"  "<<MTW_new5<<endl;
                double ptnun=met_new5.Pt();
                double mun= MW*MW/2 + ptl*ptnun*cdphi_new5;
                double An=mun*pzl/(ptl*ptl);
                double Bn=mun*mun*pzl*pzl/(pow(ptl,4));
                double Cn= (El*El*ptnun*ptnun- mun*mun)/(ptl*ptl);
                double Dn=0;
                //cout<<"B, C, B-C old; B, C, B-C new"<<B<<"  "<<C<<"  "<<B-C<<"  "<<Bn<<"  "<<Cn<<"  "<<Bn-Cn<<endl;
                A=An;
                nu_complex=met_new5;
                found=true;
                break;
              }
              TLorentzVector met_new6;
              met_new6.SetPxPyPzE(METPx->at(0)+py_var,METPy->at(0)-px_var,METPz->at(0),METE->at(0));
              double deltaphi_new6=DeltaPhi(mu_vector[0].Phi(), met_new6.Phi());
              double cdphi_new6= cos(deltaphi_new6);
   	      double MTW_new6=sqrt(2*ptl*met_new6.Pt()*(1 -cdphi_new6 ));
              if(MTW_new6>80.399&&MTW_new6<80.401){//cout<<"MTW old, px var +, py var -, MTW new "<<MTW<<"  "<<py_var<<"  "<<px_var<<"  "<<MTW_new6<<endl;
                double ptnun=met_new6.Pt();
                double mun= MW*MW/2 + ptl*ptnun*cdphi_new6;
                double An=mun*pzl/(ptl*ptl);
                double Bn=mun*mun*pzl*pzl/(pow(ptl,4));
                double Cn= (El*El*ptnun*ptnun- mun*mun)/(ptl*ptl);
                double Dn=0;
                //cout<<"B, C, B-C old; B, C, B-C new"<<B<<"  "<<C<<"  "<<B-C<<"  "<<Bn<<"  "<<Cn<<"  "<<Bn-Cn<<endl;
                A=An;
                nu_complex=met_new6;
                found=true;
                break;
              }

              TLorentzVector met_new7;
              met_new7.SetPxPyPzE(METPx->at(0)-py_var,METPy->at(0)+px_var,METPz->at(0),METE->at(0));
              double deltaphi_new7=DeltaPhi(mu_vector[0].Phi(), met_new7.Phi());
              double cdphi_new7= cos(deltaphi_new7);
   	      double MTW_new7=sqrt(2*ptl*met_new7.Pt()*(1 -cdphi_new7 ));
              if(MTW_new7>80.399&&MTW_new7<80.401){//cout<<"MTW old, px var -, py var +, MTW new "<<MTW<<"  "<<py_var<<"  "<<px_var<<"  "<<MTW_new7<<endl;
                double ptnun=met_new7.Pt();
                double mun= MW*MW/2 + ptl*ptnun*cdphi_new7;
                double An=mun*pzl/(ptl*ptl);
                double Bn=mun*mun*pzl*pzl/(pow(ptl,4));
                double Cn= (El*El*ptnun*ptnun- mun*mun)/(ptl*ptl);
                double Dn=0;
                //cout<<"B, C, B-C old; B, C, B-C new"<<B<<"  "<<C<<"  "<<B-C<<"  "<<Bn<<"  "<<Cn<<"  "<<Bn-Cn<<endl;
                A=An;
                nu_complex=met_new7;
                found=true;
                break;
              }

              TLorentzVector met_new8;
              met_new8.SetPxPyPzE(METPx->at(0)-py_var,METPy->at(0)-px_var,METPz->at(0),METE->at(0));
              double deltaphi_new8=DeltaPhi(mu_vector[0].Phi(), met_new8.Phi());
              double cdphi_new8= cos(deltaphi_new8);
   	      double MTW_new8=sqrt(2*ptl*met_new8.Pt()*(1 -cdphi_new8 ));
              if(MTW_new8>80.399&&MTW_new8<80.401){//cout<<"MTW old, px var -, py var -, MTW new "<<MTW<<"  "<<py_var<<"  "<<px_var<<"  "<<MTW_new8<<endl;
                double ptnun=met_new8.Pt();
                double mun= MW*MW/2 + ptl*ptnun*cdphi_new8;
                double An=mun*pzl/(ptl*ptl);
                double Bn=mun*mun*pzl*pzl/(pow(ptl,4));
                double Cn= (El*El*ptnun*ptnun- mun*mun)/(ptl*ptl);
                double Dn=0;
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








        if((B-C)>=0)D= sqrt(B-C);
        if(B-C<0)D=0;
        if(B-C<0)complex_count++;
        if((B-C)>=0)real_count++;
        pz1= A+D;
        pz2=A-D;

        TLorentzVector nu_vector1;
        TLorentzVector nu_vector2;
        TLorentzVector tlep;
        TLorentzVector thad;
        if((B-C)>=0){
          double new_E1=sqrt(METPx->at(0)*METPx->at(0) +METPy->at(0)*METPy->at(0) +pz1*pz1);
          nu_vector1.SetPxPyPzE(METPx->at(0),METPy->at(0),pz1,new_E1);
          double new_E2=sqrt(METPx->at(0)*METPx->at(0) +METPy->at(0)*METPy->at(0) +pz2*pz2);
          nu_vector2.SetPxPyPzE(METPx->at(0),METPy->at(0),pz2,new_E2);
        }

        if((B-C)<0){
          double new_E1=sqrt(nu_complex.Px()*nu_complex.Px() +nu_complex.Py()*nu_complex.Py() +pz1*pz1);
          nu_vector1.SetPxPyPzE(METPx->at(0),METPy->at(0),pz1,new_E1);
          double new_E2=sqrt(nu_complex.Px()*nu_complex.Px() +nu_complex.Py()*nu_complex.Py() +pz2*pz2);
          nu_vector2.SetPxPyPzE(METPx->at(0),METPy->at(0),pz2,new_E2);
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

            }
            if(fabs(m1-172.5) >fabs(m3-172.5)){//m3
              tlep=(mu_vector[0]+nu_vector1+jet_vector[b_jet_index[1]]);
              ind2=b_jet_index[0];
            }
          }
          if(fabs(m3-172.5) > fabs(m4-172.5)){
           if(fabs(m1-172.5) <fabs(m4-172.5)){//m1
              tlep=(mu_vector[0]+nu_vector1+jet_vector[b_jet_index[0]]);
              ind2=b_jet_index[1];
            }
            if(fabs(m1-172.5) >fabs(m4-172.5)){//m4
              tlep=(mu_vector[0]+nu_vector2+jet_vector[b_jet_index[1]]);
              ind2=b_jet_index[0];
            }
          }
        }


        if(fabs(m1-172.5) > fabs(m2-172.5)){
         if(fabs(m3-172.5) < fabs(m4-172.5)){
            if(fabs(m2-172.5) <fabs(m3-172.5)){//m2
              tlep=(mu_vector[0]+nu_vector2+jet_vector[b_jet_index[0]]);
              ind2=b_jet_index[1];
            }
            if(fabs(m2-172.5) >fabs(m3-172.5)){//m3
              tlep=(mu_vector[0]+nu_vector1+jet_vector[b_jet_index[1]]);
              ind2=b_jet_index[0];
            }
          }
          if(fabs(m3-172.5) > fabs(m4-172.5)){
           if(fabs(m2-172.5) <fabs(m4-172.5)){//m2
              tlep=(mu_vector[0]+nu_vector2+jet_vector[b_jet_index[0]]);
              ind2=b_jet_index[1];
            }
            if(fabs(m2-172.5) >fabs(m4-172.5)){//m4
              tlep=(mu_vector[0]+nu_vector2+jet_vector[b_jet_index[1]]);
              ind2=b_jet_index[0];
            }
          }
        }


        if((fabs(m1-172.5) == fabs(m2-172.5) )&& (fabs(m3-172.5) == fabs(m4-172.5) )){
           if(fabs(m1-172.5) <fabs(m3-172.5)){//m1
              tlep=(mu_vector[0]+nu_vector1+jet_vector[b_jet_index[0]]);
              ind2=b_jet_index[1];
           }
          if(fabs(m1-172.5) >fabs(m3-172.5)){//m3
              tlep=(mu_vector[0]+nu_vector1+jet_vector[b_jet_index[1]]);
              ind2=b_jet_index[0];
           }
        } 

        double mmin=9999;
        int ljet_ind1=-99, ljet_ind2=-99, extra_jet_index=-99;
        vector<int> a_min;
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
        //cout<<"indices as follows "<<ljet_ind1<<"  "<<ljet_ind2<<" "<<extra_jet_index<<" "<<endl;
        //cout<<ljet_ind1<<"  "<<ljet_ind2<<"  "<<(jet_vector[ljet_ind1]+jet_vector[ljet_ind2]).M()<<endl;
        h_ljet_pt->Fill(jet_vector[ljet_ind1].Pt());
        h_ljet_eta->Fill(jet_vector[ljet_ind1].Eta());    

        h_sljet_pt->Fill(jet_vector[ljet_ind2].Pt());
        h_sljet_eta->Fill(jet_vector[ljet_ind2].Eta());  

        h_dijet_mass->Fill((jet_vector[ljet_ind1]+jet_vector[ljet_ind2]).M());  
//        cout<<" nu1 b1, nu2 b1, nu1 b2, nu2 b2 "<<"  "<<(mu_vector[0]+nu_vector1+jet_vector[b_jet_index[0]]).M()<<"  "<<(mu_vector[0]+nu_vector2+jet_vector[b_jet_index[0]]).M()<<"  "<<(mu_vector[0]+nu_vector1+jet_vector[b_jet_index[1]]).M()<<"  "<<(mu_vector[0]+nu_vector2+jet_vector[b_jet_index[1]]).M()<<endl;

//       cout<<"jj b1, jj b2  "<<(jet_vector[ljet_ind1]+jet_vector[ljet_ind2] +jet_vector[b_jet_index[0]] ).M()<<"  "<<(jet_vector[ljet_ind1]+jet_vector[ljet_ind2] +jet_vector[b_jet_index[1]] ).M()<<endl;
        thad=jet_vector[ljet_ind1]+jet_vector[ljet_ind2] +jet_vector[ind2];

     //   cout<<m1<<"  "<<m2<<"  "<<m3<<"  "<<m4<<"  "<<endl;
       
     //   cout<<tlep.M()<<" "<<thad.M()<<endl;
        h_m_thad->Fill(thad.M()); 
        h_m_tlep->Fill(tlep.M());       
  
        TLorentzVector top_vector;
        TLorentzVector atop_vector;
        if(mu_charge[0]>0){
          h_m_top->Fill(tlep.M());
          h_m_atop->Fill(thad.M());
          top_vector=tlep;
          atop_vector=thad;
        }

        if(mu_charge[0]<0){
          h_m_atop->Fill(tlep.M());
          h_m_top->Fill(thad.M());
          atop_vector=tlep;
          top_vector=thad;
        }

        rec_sel=true;  
        
        //Boosting to ttj CM frame for tt+>=1j
        TLorentzVector sum_ttj_vector;
        TLorentzVector extra_jet_vector;
        if(extra_jet_index!=-99){
           extra_jet_vector=jet_vector[extra_jet_index];
          sum_ttj_vector=(top_vector+atop_vector+extra_jet_vector);
          top_vector.Boost(-sum_ttj_vector.BoostVector());
          atop_vector.Boost(-sum_ttj_vector.BoostVector());
          extra_jet_vector.Boost(-sum_ttj_vector.BoostVector());



          double dE=top_vector.E()-atop_vector.E();
          h_rec_deltaE->Fill(dE);
          double ttj_Y=sum_ttj_vector.Rapidity();
          h_rec_ttjY->Fill(ttj_Y);
          double Jettheta_gen=2*atan(exp(-1*extra_jet_vector.Eta()));          
          double rap=extra_jet_vector.Rapidity();

          vector<int> plot_indb;
          vector<int> plot_indc;
          vector<int> plot_indd;
          vector<int> plot_inde;
          if(dE>0)plot_indb.push_back(0);
          if(dE<0)plot_indb.push_back(1);

          plot_indc.push_back(0);
          if(fabs(rap)<0.5) plot_indc.push_back(1);

          if(fabs(ttj_Y)>0)plot_indd.push_back(0);
          if(fabs(ttj_Y)>0.5)plot_indd.push_back(1);
          if(fabs(ttj_Y)>1.0)plot_indd.push_back(2);

          if(fabs(dE)>0)plot_inde.push_back(0);
          if(fabs(dE)>50)plot_inde.push_back(1);
          if(fabs(dE)>120)plot_inde.push_back(2);

          for(unsigned int plota=0;plota<plot_inda.size();plota++){
            for(unsigned int plotb=0;plotb<plot_indb.size();plotb++){
              for(unsigned int plotc=0;plotc<plot_indc.size();plotc++){
                for(unsigned int plotd=0;plotd<plot_indd.size();plotd++){
                  for(unsigned int plote=0;plote<plot_inde.size();plote++){
                     h_jettheta[plot_inda[plota]][plot_indb[plotb]][plot_indc[plotc]][plot_indd[plotd]][plot_inde[plote]]->Fill(Jettheta_gen);
                  }
                }
              }
            }
          }






       }




      }//multiplicity requirement

      if(rec_sel&&gen_sel)real++;
      if(rec_sel&&!gen_sel)fake++;   
      if(!rec_sel&&gen_sel)miss++;         
      //cout<<mu_index<<"  "<<jet_index	<<endl;
     
   }

   cout<<"real Nu solutions "<<real_count<<" complex solutions "<<complex_count<<" solved complex solutions "<<solved_complex_count<<" fraction of complex count "<<complex_count/(complex_count+real_count)<<" fraction of solved complex events "<<solved_complex_count/(complex_count)<<endl;    
   cout<<"number of gen and reco tt events "<<real <<" number of gen only "<<miss<<" number of reco only "<<fake<<endl;

  TTree *weight_tree;
  weight_tree = new TTree("tree","tree");
  weight_tree->Branch("nentries",&nentries);

 // if(!sherpa)weight_tree->Branch("cnt0",&cnt0);
 // if(sherpa||mg5amcanlo)weight_tree->Branch("cnt0",&test);

  weight_tree->Fill();

  weight_tree->Print();
   file_out->Write();
   file_out->Close();
}

int main(int argc,char **argv){
  ttjana_reco a;
  a.Loop();
}


