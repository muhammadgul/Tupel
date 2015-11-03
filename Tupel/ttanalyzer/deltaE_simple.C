
#include <TH2.h>
#include <TH1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <TLorentzVector.h>
#include "functions.h"
void deltaE_simple(){

   gStyle->SetOptStat(kFALSE);
   gStyle->SetOptTitle(kFALSE);

   TH1::SetDefaultSumw2();
   TH2::SetDefaultSumw2();  
   TString fileName[100];
   TFile *f[100];
   fileName[0]="mc_signal_25ns_isElec_0";
  fileName[1]="data_25ns_runD_isElec_0";
  fileName[2]="ST_WJet_isElec_0";
   fileName[3]="mc_amc_hpp_signal_isElec_0";
 int nfiles=4;

for(int z =0; z<nfiles;z++){  //input files
f[z]= TFile::Open(fileName[z]+".root");
}


  TTree *tree_weight = (TTree *)f[0]->Get("tree");
  Long64_t MyWeight1;
  tree_weight->SetBranchAddress("nentries",&MyWeight1);
  tree_weight->GetEntry(0);

  TH1D* ydata  =(TH1D*)f[1]->Get("deltaY_reco");
  vector<double> asym_charge_data=calculate_asym(ydata,MyWeight1,1);

  TH1D* ymc  =(TH1D*)f[0]->Get("deltaY_reco");
  vector<double> asym_charge_mc=calculate_asym(ymc,MyWeight1,1);

  TH1D* ymc_gen  =(TH1D*)f[0]->Get("deltaY_gen");
  vector<double> asym_charge_mc_gen=calculate_asym(ymc_gen,MyWeight1,1);

  cout<<"A_C data "<<asym_charge_data[0]<<" #pm "<<asym_charge_data[1]<<endl;

  cout<<"A_C mc "<<asym_charge_mc[0]<<" #pm "<<asym_charge_mc[1]<<endl;

  cout<<"A_C mc gen"<<asym_charge_mc_gen[0]<<" #pm "<<asym_charge_mc_gen[1]<<endl;
  TH1D* gen  =(TH1D*)f[0]->Get("gen_deltaE");
  TH1D* rec  =(TH1D*)f[0]->Get("rec_deltaE");

  vector<double> asym_gen=calculate_asym(gen,MyWeight1,1);
  vector<double> asym_rec=calculate_asym(rec,MyWeight1,1);
  cout<<asym_gen[0]<<"  "<<asym_rec[0]<<endl;

  TH1D* pos  =(TH1D*)f[0]->Get("v_jettheta_0_0_0_0_0");
  TH1D* neg  =(TH1D*)f[0]->Get("v_jettheta_0_1_0_0_0");
  TH1D* pos2  =(TH1D*)f[1]->Get("v_jettheta_0_0_0_0_0");
  TH1D* neg2  =(TH1D*)f[1]->Get("v_jettheta_0_1_0_0_0");


  TH1D* asym_incl= calculate_asymnorm(pos,neg,MyWeight1,4);
  TH1D* asym_incl2= calculate_asymnorm(pos2,neg2,MyWeight1,4);
  TCanvas *c1 = new TCanvas("c1","c1",800,800);
  c1->cd();
  asym_incl2->Draw();
  asym_incl->SetLineColor(kGreen);
  asym_incl->Draw("same");


 TCanvas *c2 = new TCanvas("c2","c2",800,800);
    c2->cd();
char nam[1000];
TH1D* asym[1000];
TH1D* asym_recc[1000];
int ii=0;
TCanvas *c[100];
char nammm[1000];
for(int z =0; z<nfiles;z++){  //input files
for(int i =0; i<10;i++){ 
  for(int k =0; k<2;k++){//jet rapidity 
    for(int l =0; l<3;l++){ //ttj rapidity
      for(int m =0; m<3;m++){  //de 

TString a="";
//if(i!=0)continue;
if(i==0)a+="all";
if(i==1)a+="gg";
if(i==2)a+="qg";
if(i==3)a+="gq";
if(i==4)a+="#bar{q}g";
if(i==5)a+="g#bar{q}";
if(i==6)a+="q#bar{q}";
if(i==7)a+="#bar{q}q";
if(i==8)a+="qg & gq";
if(i==9)a+="qg & gq &#bar{q}g & g#bar{q}";

if(k==1)a+=" |y(j)|<0.5" ;
if(l==1)a+=" |y(ttj)|>0.5"; 
if(l==2)a+=" |y(ttj)|>1.0";

if(m==1)a+=" |p_{T}(j)|>50"; 
if(m==2)a+=" |p_{T}(j)|>120"; 

TLegend *leg1 = new TLegend(0.151567,0.8493719,0.54980511,0.995385);
leg1->SetBorderSize(0);
leg1->SetFillColor(kWhite);
leg1->SetTextSize(0.03);

TLegend *leg2 = new TLegend(0.151567,0.8493719,0.54980511,0.995385);
leg2->SetBorderSize(0);
leg2->SetFillColor(kWhite);
leg2->SetTextSize(0.03);

sprintf(nam,"v_gen_jettheta_%i_0_%i_%i_%i",i,k,l,m);

 TH1D* pos_gen  =(TH1D*)f[z]->Get(nam);
sprintf(nam,"v_gen_jettheta_%i_1_%i_%i_%i",i,k,l,m);

  TH1D* neg_gen  =(TH1D*)f[z]->Get(nam);

  asym[i]= calculate_asymnorm(pos_gen,neg_gen,MyWeight1,4);
  double NBinsmaxx= asym[i]->GetNbinsX()+1;
  //double asym_vall= asym[i]->Integral(0,NBinsmaxx)*100;
  vector<double> asym_charge_gen=calculate_asymm(pos_gen,neg_gen,MyWeight1,1);
  double asym_vall= asym_charge_gen[0]*100;
    double asym_errr= asym_charge_gen[1]*100;
  cout<<"value in the macro "<<asym_vall<<" "<< asym_errr<<endl;
  leg1->AddEntry(asym[i], a,"");
  sprintf(nammm,"total asym %0.4f %% #pm %0.4f %%",asym_vall, asym_errr);

  leg1->AddEntry(asym[i],nammm,"");
  /*if(ii==0){
    asym[i]->SetMinimum(-0.11);
    asym[i]->SetMaximum(0.11);
    asym[i]->Draw();
  }
  else asym[i]->Draw("sames");*/

  c[i]=new TCanvas ("c","c",800,800);
  c[i]->cd();
    asym[i]->SetMinimum(-0.11*100);
    asym[i]->SetMaximum(0.11*100);
    asym[i]->SetXTitle("#theta_{j} gen level");
    asym[i]->Draw();
    leg1->Draw("sames");
  sprintf(nammm,"asym_plots_25ns/%s_asym_gen_%i_%i_%i_%i.pdf",fileName[z].Data(),i,k,l,m);
  c[i]->Print(nammm);


sprintf(nam,"v_jettheta_%i_0_%i_%i_%i",i,k,l,m);

 TH1D* pos_rec  =(TH1D*)f[z]->Get(nam);
sprintf(nam,"v_jettheta_%i_1_%i_%i_%i",i,k,l,m);

  TH1D* neg_rec  =(TH1D*)f[z]->Get(nam);

  asym_recc[i]= calculate_asymnorm(pos_rec,neg_rec,MyWeight1,4);
  double NBinsmax= asym_recc[i]->GetNbinsX()+1;
  vector<double> asym_charge_data=calculate_asymm(pos_rec,neg_rec,MyWeight1,1);
  double asym_val= asym_charge_data[0]*100;
    double asym_err= asym_charge_data[1]*100;
/*  double asym_val= asym_recc[i]->Integral()*100;
  double n1= pos_rec->Integral();
  double n2= neg_rec->Integral();
  TH1* h1 = new TH1D("h1","h1",1,0,1);
  TH1* h2 = new TH1D("h2","h2",1,0,1);
  h1->SetBinContent(1,n1);
  h1->SetBinError(1,1/sqrt(n1));

  h2->SetBinContent(1,n2);
  h2->SetBinError(1,1/sqrt(n2));

  h1->Add(h2,-1);
  double asym_err = h1->GetBinError(1)*100/2;*/

  //asym[i]->SetLineColor(10*i +1);
  leg2->AddEntry(asym[i], a,"");
  sprintf(nammm,"total asym %0.4f %% #pm %0.4f %%",asym_val, asym_err);
  leg2->AddEntry(asym[i],nammm,"");
  /*if(ii==0){
    asym_recc[i]->SetMinimum(-0.11);
    asym_recc[i]->SetMaximum(0.11);
    asym_recc[i]->Draw();
  }
  else asym_recc[i]->Draw("sames");*/

  c[i]=new TCanvas ("c","c",800,800);
  c[i]->cd();
//    asym_recc[i]->SetMinimum(-0.11);
//    asym_recc[i]->SetMaximum(0.11);
    asym_recc[i]->SetXTitle("#theta_{j} rec level");
    asym_recc[i]->Draw();
    leg2->Draw("sames");
  sprintf(nammm,"asym_plots_25ns/%s_asym_rec_%i_%i_%i_%i.pdf",fileName[z].Data(),i,k,l,m);
  c[i]->Print(nammm);





ii++;
}}}}}}
