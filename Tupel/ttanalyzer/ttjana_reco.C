#define ttjana_reco_cxx
#include "ttjana_reco.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <TLorentzVector.h>


void ttjana_reco::Loop()
{
//using namespace std;
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

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;


   TFile* file_out = new TFile("out_reco.root","RECREATE"); 
   file_out->cd();	
   TH1* h_muon_pt= new TH1D ("muon_pt","muon_pt",100,0,1000);
   TH1* h_muon_eta= new TH1D ("muon_eta","muon_eta",100,-2.5,2.5);

   TH1* h_ljet_pt= new TH1D ("ljet_pt","ljet_pt",100,0,1000);
   TH1* h_ljet_eta= new TH1D ("jlet_eta","ljet_eta",100,-2.5,2.5);

   TH1* h_sljet_pt= new TH1D ("sljet_pt","ljet_pt",100,0,1000);
   TH1* h_sljet_eta= new TH1D ("sjlet_eta","ljet_eta",100,-2.5,2.5);

   TH1* h_MET_ET= new TH1D ("MET_ET","MET_ET",100,0,1000);
   TH1* h_dijet_mass= new TH1D ("dijet_mass","dijet_mass",100,0,1000);
   TH1* h_m_thad= new TH1D ("m_thad","m_thad",100,0,1000);
   TH1* h_m_tlep= new TH1D ("m_tlep","m_tlep",100,0,1000);
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      if(jentry%10000==0)cout<<jentry<<"/"<<nentries<<endl;
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      int mu_index=0;	
      vector<TLorentzVector>mu_vector;
      vector<int>mu_charge;
      vector<int>b_jet_index;
      vector<int>l_jet_index;
      int jet_index=0;	
      vector<TLorentzVector>jet_vector;




      for(unsigned int mu_ind=0; mu_ind<patMuonPt_->size();mu_ind++){
        if(patMuonPt_->at(mu_ind)<20 || fabs(patMuonEta_->at(mu_ind))>2.4)continue;
//          cout<<patMuonPt_->size()<<"  " <<mu_ind<<"  "<<patMuonPt_->at(mu_ind)<<endl;
          TLorentzVector tmp;
          tmp.SetPtEtaPhiE(patMuonPt_->at(mu_ind),patMuonEta_->at(mu_ind),patMuonPhi_->at(mu_ind),patMuonEn_->at(mu_ind));
          mu_vector.push_back(tmp);
          mu_charge.push_back(patMuonCharge_->at(mu_ind))
          mu_index++;

      }



      for(unsigned int jet_ind=0; jet_ind<patJetPfAk05Pt_->size();jet_ind++){

        if(patJetPfAk05Pt_->at(jet_ind)<30. || fabs(patJetPfAk05Eta_->at(jet_ind))>2.5 )continue;
          //cout<<patJetPfAk05Pt_->size()<<"  " <<jet_ind<<"  "<<patJetPfAk05Pt_->at(jet_ind)<<endl;
        TLorentzVector tmp;
        tmp.SetPtEtaPhiE(patJetPfAk05Pt_->at(jet_ind),patJetPfAk05Eta_->at(jet_ind),patJetPfAk05Phi_->at(jet_ind),patJetPfAk05En_->at(jet_ind));
        jet_vector.push_back(tmp);
        if(patJetPfAk05BDiscCSV_->at(jet_ind)>0.697)b_jet_index.push_back(jet_index);//cut value 0.697
        //else l_jet_index.push_back(jet_index);
        jet_index++;
      }


      if (jet_vector.size()>=4 && b_jet_index.size()==2 && mu_index==1){//at least 4 jets, 2 of b jets, 1 muon
        h_muon_pt->Fill(mu_vector[0].Pt());
        h_muon_eta->Fill(mu_vector[0].Eta());

        h_MET_ET->Fill(METPt->at(0));
        
  
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
        double mu= MW*MW/2 + ptl*ptnu*cdphi;

        double A=mu*pzl/(ptl*ptl);
        double B=mu*mu*pzl*pzl/(pow(ptl,4));
        double C= (El*El*ptnu*ptnu- mu*mu)/(ptl*ptl);
        double D=0;
        if((B-C)>=0)D= sqrt(B-C);
        pz1= A+D;
        pz2=A-D;

        TLorentzVector nu_vector1;
        TLorentzVector nu_vector2;
        TLorentzVector tlep;
        TLorentzVector thad;
        double new_E1=sqrt(METPx->at(0)*METPx->at(0) +METPy->at(0)+METPy->at(0) +pz1*pz1);
        nu_vector1.SetPxPyPzE(METPx->at(0),METPy->at(0),pz1,new_E1);
        double new_E2=sqrt(METPx->at(0)*METPx->at(0) +METPy->at(0)+METPy->at(0) +pz2*pz2);
        nu_vector2.SetPxPyPzE(METPx->at(0),METPy->at(0),pz2,new_E2);

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
        int ljet_ind1=-99, ljet_ind2=-99;
        for(int j_ind=0; j_ind<jet_vector.size();j_ind++){
          if(j_ind==b_jet_index[0]|| j_ind==b_jet_index[1])continue;
          for(int j_indd=j_ind; j_indd<jet_vector.size();j_indd++){
            if(j_ind==j_indd || j_indd==b_jet_index[0]|| j_indd==b_jet_index[1])continue;

            double mmin_temp=(jet_vector[j_ind]+jet_vector[j_indd]).M();
            if(fabs(mmin_temp-80.4)<fabs(mmin-80.4)){
              mmin=mmin_temp;ljet_ind1=j_ind;ljet_ind2=j_indd;
            }
          }
        }
      //  cout<<ljet_ind1<<"  "<<ljet_ind2<<"  "<<(jet_vector[ljet_ind1]+jet_vector[ljet_ind2]).M()<<endl;
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



        
      }//multiplicity requirement


      //cout<<mu_index<<"  "<<jet_index	<<endl;
     
   }


  file_out->Write();
  file_out->Close();
}

