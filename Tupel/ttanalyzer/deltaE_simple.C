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
   TH1::SetDefaultSumw2();
   TH2::SetDefaultSumw2();

  TString fileName="mc_signal.root";

 TFile *f= TFile::Open(fileName);
  TTree *tree_weight = (TTree *)f->Get("tree");
  double MyWeight1;
  tree_weight->SetBranchAddress("nentries",&MyWeight1);
  tree_weight->GetEntry(0);

  TH1D* gen  =(TH1D*)f->Get("gen_deltaE");
  TH1D* rec  =(TH1D*)f->Get("rec_deltaE");

  vector<double> asym_gen=calculate_asym(gen,MyWeight1,1);
  vector<double> asym_rec=calculate_asym(rec,MyWeight1,1);
  cout<<asym_gen[0]<<"  "<<asym_rec[0]<<endl;
}
