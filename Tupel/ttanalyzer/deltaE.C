vector<double> calculate_asym(TH1D* h1, double MyWeight, int nrebin){
  TH1D* e_plus = (TH1D*)h1->Clone("e_plus");

  /*for(int binn=1;binn<=e_plus->GetNbinsX();binn++){
    e_plus->SetBinContent(binn,e_plus->GetBinContent(binn)/e_plus->GetBinWidth(binn));
    e_plus->SetBinError(binn,e_plus->GetBinError(binn)/e_plus->GetBinWidth(binn)); 
  }*/
  e_plus->Rebin(nrebin);
  //e_plus->Scale(244.9/MyWeight);
  double minus_content=0;
  double minus_error=0;
  double plus_content=0;
  double plus_error=0;
  for(int binn=0;binn<=e_plus->GetNbinsX()/2;binn++){
    minus_content+=e_plus->GetBinContent(binn);
    minus_error+=pow(e_plus->GetBinError(binn),2);
  }

  for(int binn=1+e_plus->GetNbinsX()/2;binn<=e_plus->GetNbinsX()+1;binn++){
    plus_content+=e_plus->GetBinContent(binn);
    plus_error+=pow(e_plus->GetBinError(binn),2);
  }
  vector<double> asym;
  TH1* hup=new TH1D("hup","hup",1,0,1);
  TH1* hdn=new TH1D("hdn","hdn",1,0,1);
  hup->SetBinContent(1,plus_content);
  hup->SetBinError(1,sqrt(plus_error));
  hdn->SetBinContent(1,minus_content);
  hdn->SetBinError(1,sqrt(minus_error));
  hup->Divide(hup,hdn,1,1);
  double asym_val= (plus_content-minus_content) /(plus_content+minus_content);
  double asym_err= hup->GetBinError(1);
 
  if(minus_content!=0 ){
  asym.push_back(asym_val);
  asym.push_back(asym_err);}
  if(minus_content==0 ){
  asym.push_back(0);
  asym.push_back(0);}
  return asym;
}

TH1D * calculate_asym(TH1D* h1, TH1D* h2, double MyWeight, int nrebin){
  TH1D* e_plus = (TH1D*)h1->Clone("e_plus");
  TH1D* e_minus = (TH1D*)h2->Clone("e_plus");
  for(int binn=1;binn<=e_plus->GetNbinsX();binn++){
    e_plus->SetBinContent(binn,e_plus->GetBinContent(binn)/e_plus->GetBinWidth(binn));
    e_minus->SetBinContent(binn,e_minus->GetBinContent(binn)/e_plus->GetBinWidth(binn));
    e_plus->SetBinError(binn,e_plus->GetBinError(binn)/e_plus->GetBinWidth(binn)); 
    e_minus->SetBinError(binn,e_minus->GetBinError(binn)/e_plus->GetBinWidth(binn)); 
  }
  e_plus->Rebin(nrebin);
  e_minus->Rebin(nrebin);
  e_plus->Scale(244.9/MyWeight);
  e_minus->Scale(244.9/MyWeight);

  TH1D* delta= e_plus->Clone("delta");
  delta->Add(e_minus,-1);

  return delta;
}

TH1D * calculate_asymnorm(TH1D* h1, TH1D* h2, double MyWeight, int nrebin){
  TH1D* e_plus = (TH1D*)h1->Clone("e_plus");
  TH1D* e_minus = (TH1D*)h2->Clone("e_plus");
  for(int binn=1;binn<=e_plus->GetNbinsX();binn++){
    e_plus->SetBinContent(binn,e_plus->GetBinContent(binn)/e_plus->GetBinWidth(binn));
    e_minus->SetBinContent(binn,e_minus->GetBinContent(binn)/e_plus->GetBinWidth(binn));
    e_plus->SetBinError(binn,e_plus->GetBinError(binn)/e_plus->GetBinWidth(binn)); 
    e_minus->SetBinError(binn,e_minus->GetBinError(binn)/e_plus->GetBinWidth(binn)); 
  }
  e_plus->Rebin(nrebin);
  e_minus->Rebin(nrebin);
  e_plus->Scale(244.9/MyWeight);
  e_minus->Scale(244.9/MyWeight);

  TH1D* delta= e_plus->Clone("delta");
  delta->Add(e_minus,-1);
  TH1D* sum= e_plus->Clone("sum");
  sum->Add(e_minus);

  delta->Divide(delta,sum,1,1);
  return delta;
}

   void create_table(TString name,TString fileName, double MyWeight,int rebin){
    TFile *f= TFile::Open(fileName);
     double cut_rapidity[]={0,0.5,1.0};
     double cut_de[]={0,50,120};
     TString texname="Table_";
     texname+=fileName;
     texname+=name;
     texname+=".tex";
     ofstream tex_table;
     tex_table.open(texname);
     tex_table<<"\\documentclass[12pt]{article}"<<endl;

     tex_table<<"\\begin{document}"<<endl;
     tex_table<<"\\begin{tabular}{ccccc}"<<endl;
     tex_table<<"$|y_{min}(t\\bar{t}j)|$&$|\\Delta E_{min}(t,\\bar{t})|$ [GeV]&$N_{tot}$&$A_E$ [\\%] & $\\delta A_E $ [\\%]\\\\"<<endl;
     tex_table<<"\\hline"<<endl;
     for(int i = 0; i<3;i++){//ttj rapidity
       for(int j = 0; j<3;j++){//De
          TString namtemp=name;
          namtemp+=(i);
          namtemp+="_";
          namtemp+=(j);
          cout<<namtemp<<endl;
          TH1D *v_plus =(TH1D*)f->Get(namtemp); 
          vector <double> tot_E_assym= calculate_asym(v_plus,MyWeight,rebin);

          tex_table.precision(10);
          tex_table<<cut_rapidity[i]<<" &  "<<cut_de[j]<<" & "<<v_plus->Integral();
          tex_table.precision(3);
          tex_table<<" & "<< tot_E_assym[0]*100<<" & $\\pm$"<<tot_E_assym[1]*100<<"\\\\"<<endl; 
          //system("pdflatex " +tex_table);
        }
      }
      tex_table<<"\\end{tabular}"<<endl;
      tex_table<<"\\end{document}"<<endl;
    }

   void create_table_gq_qg(TString name,TString name2,TString fileName, double MyWeight,int rebin){
    TFile *f= TFile::Open(fileName);
     double cut_rapidity[]={0,0.5,1.0};
     double cut_de[]={0,50,120};
     TString texname="Table_";
     texname+=fileName;
     texname+=name;
     texname+="_sum_qg_gq.tex";
     ofstream tex_table;
     tex_table.open(texname);
     tex_table<<"\\documentclass[12pt]{article}"<<endl;

     tex_table<<"\\begin{document}"<<endl;
     tex_table<<"\\begin{tabular}{ccccc}"<<endl;
     tex_table<<"$|y_{min}(t\\bar{t}j)|$&$|\\Delta E_{min}(t,\\bar{t})|$ [GeV]&$N_{tot}$&$A_E$ [\\%] & $\\delta A_E $ [\\%]\\\\"<<endl;
     tex_table<<"\\hline"<<endl;
     for(int i = 0; i<3;i++){//ttj rapidity
       for(int j = 0; j<3;j++){//De
          TString namtemp=name;
          namtemp+=(i);
          namtemp+="_";
          namtemp+=(j);
          cout<<namtemp<<endl;
          TH1D *v_pluss =(TH1D*)f->Get(namtemp); 
          TString namtemp2=name2;
          namtemp2+=(i);
          namtemp2+="_";
          namtemp2+=(j);
          cout<<namtemp2<<endl;
          TH1D *v_plus2 =(TH1D*)f->Get(namtemp2); 
          TH1D *v_plus=v_pluss->Clone("v_plus");
          v_plus->Add(v_plus2);
          vector <double> tot_E_assym= calculate_asym(v_plus,MyWeight,rebin);

          tex_table.precision(10);
          tex_table<<cut_rapidity[i]<<" &  "<<cut_de[j]<<" & "<<v_plus->Integral();
          tex_table.precision(3);
          tex_table<<" & "<< tot_E_assym[0]*100<<" & $\\pm$"<<tot_E_assym[1]*100<<"\\\\"<<endl; 
          //system("pdflatex " +tex_table);
        }
      }
      tex_table<<"\\end{tabular}"<<endl;
      tex_table<<"\\end{document}"<<endl;
    }

void deltaE(){
   TH1::SetDefaultSumw2();
   TH2::SetDefaultSumw2();

  //TString fileName="out_powheg_nojetcut_incl.root";
  //TString fileName="out_powheg_20jetcut_incl.root";
  //TString fileName="out_powheg_50jetcut_incl.root";
  //TString fileName="out_MG_50jetcut_incl.root";
  //TString fileName="out_MG_nojetcut_incl.root";
//  TString fileName="out_MG_20jetcut_incl.root";
  //TString fileName="out_powheg_nojetcut_incl_qjet_only.root";
  //TString fileName="out_powheg_20jetcut_incl_qjet_only.root";
  //TString fileName="out_powheg_nojetcut_incl_gjet_only.root";
//  TString fileName="out_powheg_20jetcut_incl_gjet_only.root";


  //TString fileName="out_powheg.root";
  //TString fileName="out_g_jet_only.root";
  //TString fileName="out_q_jet_only.root";
  //TString fileName="out_q_g_jet.root";
  //TString fileName="out_nomatch_criteria.root";
 //TString fileName="out_nomatch.root";
  TString fileName="out.root";

 TFile *f= TFile::Open(fileName);
  TTree *tree_weight = (TTree *)f->Get("tree");
  double MyWeight1;
  tree_weight->SetBranchAddress("sum_weight",&MyWeight1);
  tree_weight->GetEntry(0);

  TH1D* plus  =(TH1D*)f->Get("jettheta_deltaE_pos_gq");
  TH1D* minus =(TH1D*)f->Get("jettheta_deltaE_neg_gq");
  TH1D* asym= calculate_asym(plus,minus,MyWeight1,2);
  TH1D* asymnorm= calculate_asymnorm(plus,minus,MyWeight1,2);


  TH1D* plus2  =(TH1D*)f->Get("jettheta_deltaE_pos_qg");
  TH1D* minus2 =(TH1D*)f->Get("jettheta_deltaE_neg_qg");
  TH1D* asym2= calculate_asym(plus2,minus2,MyWeight1,2);
  TH1D* asymnorm2= calculate_asymnorm(plus2,minus2,MyWeight1,2);
  asym2->SetLineColor(kRed);
  asymnorm2->SetLineColor(kRed);
  TH1D* plus3  =(TH1D*)f->Get("jettheta_deltaE_pos_gg");
  TH1D* minus3 =(TH1D*)f->Get("jettheta_deltaE_neg_gg");
  TH1D* asym3= calculate_asym(plus3,minus3,MyWeight1,2);
  TH1D* asymnorm3= calculate_asymnorm(plus3,minus3,MyWeight1,2);
  asym3->SetLineColor(kGreen);
  asymnorm3->SetLineColor(kGreen);
  TH1D* plus4  =(TH1D*)f->Get("jettheta_deltaE_pos_gqbar");
  TH1D* minus4 =(TH1D*)f->Get("jettheta_deltaE_neg_gqbar");
  TH1D* asym4= calculate_asym(plus4,minus4,MyWeight1,2);
  TH1D* asymnorm4= calculate_asymnorm(plus4,minus4,MyWeight1,2);
  asym4->SetLineColor(kBlue);
  asymnorm4->SetLineColor(kBlue);
  TLegend* leg1 = new TLegend(0.3431567,0.653719,0.580511,0.816905385);
  leg1->AddEntry(asym, "gq","pel");
  leg1->AddEntry(asym2, "qg","pel");
  leg1->AddEntry(asym3, "gg","pel");
  //leg1->AddEntry(asym4, "gqbar","pe");

 TLegend* leg2 = new TLegend(0.3431567,0.153719,0.580511,0.316905385);
  leg2->AddEntry(asym, "gq","pel");
  leg2->AddEntry(asym2, "qg","pel");
  leg2->AddEntry(asym3, "gg","pel");
  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  c1->cd();
  asymnorm->Draw("e1");
  asymnorm2->Draw("e1same");
  asymnorm3->Draw("e1same");
  //asymnorm4->Draw("e1same");
  leg1->Draw("same");
  TString name_out1=fileName;
  name_out1+="_E_asym_norm.pdf";
  c1->Print(name_out1);

  TCanvas *c2 = new TCanvas("c2","c2",800,600);
  c2->cd();
  asym->Draw("e1");
  asym2->Draw("e1same");
  asym3->Draw("e1same");
  //asym4->Draw("e1same");
  leg1->Draw("same");
  TString name_out2=fileName;
  name_out2+="_E_asym.pdf";
  c2->Print(name_out2);



  TH1D* plus11  =(TH1D*)f->Get("jettheta_costheta_j_t_pos_gq");
  TH1D* minus11 =(TH1D*)f->Get("jettheta_costheta_j_t_neg_gq");
  TH1D* asym11= calculate_asym(plus,minus,MyWeight1,2);
  TH1D* asymnorm11= calculate_asymnorm(plus11,minus11,MyWeight1,2);


  TH1D* plus12  =(TH1D*)f->Get("jettheta_costheta_j_t_pos_qg");
  TH1D* minus12 =(TH1D*)f->Get("jettheta_costheta_j_t_neg_qg");
  TH1D* asym12= calculate_asym(plus12,minus12,MyWeight1,2);
  TH1D* asymnorm12= calculate_asymnorm(plus12,minus12,MyWeight1,2);
  asym12->SetLineColor(kRed);
  asymnorm12->SetLineColor(kRed);  

  TH1D* plus13  =(TH1D*)f->Get("jettheta_costheta_j_t_pos_gg");
  TH1D* minus13 =(TH1D*)f->Get("jettheta_costheta_j_t_neg_gg");
  TH1D* asym13= calculate_asym(plus13,minus13,MyWeight1,2);
  TH1D* asymnorm13= calculate_asymnorm(plus13,minus13,MyWeight1,2);
  asym13->SetLineColor(kGreen);
  asymnorm13->SetLineColor(kGreen);  
  TCanvas *c3 = new TCanvas("c3","c3",800,600);
  c3->cd();
  asymnorm11->Draw("e1");
  asymnorm12->Draw("e1same");
  asymnorm13->Draw("e1same");
  //asymnorm3->Draw("e1same");
  //asymnorm4->Draw("e1same");
  leg2->Draw("same");
  TString name_out3=fileName;
  name_out3+="_costheta_asym_norm.pdf";
  c3->Print(name_out3);

  TH1D* de_qg  =(TH1D*)f->Get("deltaE_ttbar_qg");
vector <double> qg_tot_E_assym= calculate_asym(de_qg,MyWeight1,1);
cout<<qg_tot_E_assym[0]<<"  "<<qg_tot_E_assym[1]<<endl;

  TH1D* dtheta_qg  =(TH1D*)f->Get("costheta_j_t_ttbar_qg");
vector <double> qg_tot_theta_assym= calculate_asym(dtheta_qg,MyWeight1,1);
cout<<qg_tot_theta_assym[0]<<"  "<<qg_tot_theta_assym[1]<<endl;

  TH1D* de_gq  =(TH1D*)f->Get("deltaE_ttbar_gq");
vector <double> gq_tot_E_assym= calculate_asym(de_gq,MyWeight1,1);
cout<<gq_tot_E_assym[0]<<"  "<<gq_tot_E_assym[1]<<endl;

  TH1D* dtheta_gq  =(TH1D*)f->Get("costheta_j_t_ttbar_gq");
vector <double> gq_tot_theta_assym= calculate_asym(dtheta_gq,MyWeight1,1);
cout<<gq_tot_theta_assym[0]<<"  "<<gq_tot_theta_assym[1]<<endl;
TH1D* v_plus[11][11];
TH1D* v_pluss[11][11];
TH1D* v_plusss[11][11];
TH1D* E_v_plus_qg[11][11][11];
TH1D* E_v_minus_qg[11][11][11];
TH1D* E_asym_norm_qg[11][11];

TH1D* E_v_plus_gg[11][11][11];
TH1D* E_v_minus_gg[11][11][11];
TH1D* E_asym_norm_gg[11][11];

TH1D* E_v_plus_gq[11][11][11];
TH1D* E_v_minus_gq[11][11][11];
TH1D* E_asym_norm_gq[11][11];

TH1D* E_v_plus[11][11][11];
TH1D* E_v_minus[11][11][11];
TH1D* E_asym_norm[11][11];
char name[10000];
//   double cut_rapidity[]={0,0.25,0.5,0.75,1.0,1.25,1.5,1.75,2.,2.25,2.5};
//   double cut_de[]={0,20,40,60,80,100,120,140,160,180,200};

   create_table("v_deltaE_ttbar_",fileName,MyWeight1,1);
   create_table("v_deltaE_ttbar_qg_",fileName,MyWeight1,1);
   create_table("v_deltaE_ttbar_gq_",fileName,MyWeight1,1);
   create_table("v_deltaE_ttbar_gg_",fileName,MyWeight1,1);
   create_table("v_deltaE_ttbar_qqbar_",fileName,MyWeight1,1);
   create_table("v_deltaE_ttbar_qbarq_",fileName,MyWeight1,1);
   create_table("v_deltaE_ttbar_qbarg_",fileName,MyWeight1,1);
   create_table("v_deltaE_ttbar_gqbar_",fileName,MyWeight1,1);

   create_table_gq_qg("v_deltaE_ttbar_qg_","v_deltaE_ttbar_gq_",fileName,MyWeight1,1);

   for(int i = 0; i<3;i++){//ttj rapidity
     for(int j = 0; j<3;j++){//De

        sprintf(name,"v_jettheta_deltaE_ttbar_qg_%i_%i_%i",i,j,0);
        E_v_plus_qg[i][j][0]  =(TH1D*)f->Get(name); 
        sprintf(name,"v_jettheta_deltaE_ttbar_qg_%i_%i_%i",i,j,1);
        E_v_minus_qg[i][j][1]  =(TH1D*)f->Get(name); 
        E_asym_norm_qg[i][j]  =calculate_asymnorm(E_v_plus_qg[i][j][0],E_v_minus_qg[i][j][1],MyWeight1,2);
        sprintf(name,"v_jettheta_deltaE_ttbar_gq_%i_%i_%i",i,j,0);
        E_v_plus_gq[i][j][0]  =(TH1D*)f->Get(name); 
        sprintf(name,"v_jettheta_deltaE_ttbar_gq_%i_%i_%i",i,j,1);
        E_v_minus_gq[i][j][1]  =(TH1D*)f->Get(name); 
        E_asym_norm_gq[i][j]  =calculate_asymnorm(E_v_plus_gq[i][j][0],E_v_minus_gq[i][j][1],MyWeight1,2);

        sprintf(name,"v_jettheta_deltaE_ttbar_gg_%i_%i_%i",i,j,0);
        E_v_plus_gg[i][j][0]  =(TH1D*)f->Get(name); 
        sprintf(name,"v_jettheta_deltaE_ttbar_gg_%i_%i_%i",i,j,1);
        E_v_minus_gg[i][j][1]  =(TH1D*)f->Get(name); 
        E_asym_norm_gg[i][j]  =calculate_asymnorm(E_v_plus_gg[i][j][0],E_v_minus_gg[i][j][1],MyWeight1,2);
 
        sprintf(name,"v_jettheta_deltaE_ttbar_%i_%i_%i",i,j,0);
        E_v_plus[i][j][0]  =(TH1D*)f->Get(name); 
        sprintf(name,"v_jettheta_deltaE_ttbar_%i_%i_%i",i,j,1);
        E_v_minus[i][j][1]  =(TH1D*)f->Get(name); 
        E_asym_norm[i][j]  =calculate_asymnorm(E_v_plus[i][j][0],E_v_minus[i][j][1],MyWeight1,2);


  TCanvas *c4 = new TCanvas("c4","c4",800,600);
  c4->cd();
  E_asym_norm_qg[i][j]->SetLineColor(kRed);
  E_asym_norm_qg[i][j]->Draw("e1");
  E_asym_norm_gq[i][j]->Draw("e1same");
  E_asym_norm[i][j]->SetLineColor(kGreen);
  E_asym_norm[i][j]->Draw("e1same");
  E_asym_norm_gg[i][j]->SetLineColor(kBlue);
  E_asym_norm_gg[i][j]->Draw("e1same");
  leg1->Draw("same");
  sprintf(name,"v_jettheta_deltaE_ttbar_qg_%i_%i.pdf",i,j);
  TString name_out4=fileName;
  name_out4+="_v_jettheta_deltaE_ttbar_qg_";
  name_out4+=(i);
  name_out4+="_";
  name_out4+=(j);
  name_out4+=".pdf";
  c4->Print(name_out4);

  }
} 

}
