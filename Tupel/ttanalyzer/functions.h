vector<double> calculate_asymm(TH1D* h1, TH1D* h2, double MyWeight, int nrebin){
  TH1D* e_plus = (TH1D*)h1->Clone("e_plus");
  TH1D* e_minus = (TH1D*)h2->Clone("e_minus");
  /*for(int binn=1;binn<=e_plus->GetNbinsX();binn++){
    e_plus->SetBinContent(binn,e_plus->GetBinContent(binn)/e_plus->GetBinWidth(binn));
    e_plus->SetBinError(binn,e_plus->GetBinError(binn)/e_plus->GetBinWidth(binn)); 
  }*/
 // e_plus->Rebin(nrebin);
 // e_minus->Rebin(nrebin);
  //e_plus->Scale(244.9/MyWeight);
  double minus_content=0;
  double minus_error=0;
  double plus_content=0;
  double plus_error=0;
  for(int binn=1;binn<=e_plus->GetNbinsX();binn++){
    minus_content+=e_minus->GetBinContent(binn);
    //minus_error+=pow(e_minus->GetBinError(binn),2);

    plus_content+=e_plus->GetBinContent(binn);
    //plus_error+=pow(e_plus->GetBinError(binn),2);
  }

 minus_error=/*1*/sqrt(minus_content);  
 plus_error=/*1*/sqrt(plus_content);  
  vector<double> asym;
  TH1* hup=new TH1D("hup","hup",1,0,1);
  TH1* hdn=new TH1D("hdn","hdn",1,0,1);
  hup->SetBinContent(1,plus_content);
  hup->SetBinError(1,/*sqrt*/(plus_error));
  hdn->SetBinContent(1,minus_content);
  hdn->SetBinError(1,/*sqrt*/(minus_error));

  
  TH1D* hupp = (TH1D*)hup->Clone("hupp");
  TH1D* hdnn = (TH1D*)hup->Clone("hdnn");

  hupp->Add(hdn,-1);
  hdnn->Add(hdn);

  hupp->Divide(hupp,hdnn,1,1);
  double asym_val= (plus_content-minus_content) /(plus_content+minus_content);
  double asym_err= hupp->GetBinError(1);
  cout<<"minus content from asym calc "<<minus_content<<" "<<hupp->GetBinContent(1)*100<<" "<<asym_val*100<<" % "<<asym_err *100 <<"%"<<endl;
  if(minus_content!=0 ){
  asym.push_back(asym_val);
  asym.push_back(asym_err);}
  if(minus_content==0 ){
  asym.push_back(0);
  asym.push_back(0);}
  return asym;
}



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
  e_plus->Rebin(nrebin);
  e_minus->Rebin(nrebin);
  for(int binn=1;binn<=e_plus->GetNbinsX();binn++){
    e_plus->SetBinContent(binn,e_plus->GetBinContent(binn)/e_plus->GetBinWidth(binn));
    e_minus->SetBinContent(binn,e_minus->GetBinContent(binn)/e_plus->GetBinWidth(binn));
    e_plus->SetBinError(binn,e_plus->GetBinError(binn)/e_plus->GetBinWidth(binn)); 
    e_minus->SetBinError(binn,e_minus->GetBinError(binn)/e_plus->GetBinWidth(binn)); 
  }

  e_plus->Scale(244.9/MyWeight);
  e_minus->Scale(244.9/MyWeight);

  TH1D* delta= (TH1D*)e_plus->Clone("delta");
  delta->Add(e_minus,-1);

  return delta;
}

TH1D * calculate_asymnorm(TH1D* h1, TH1D* h2, double MyWeight, int nrebin){
  TH1D* e_plus = (TH1D*)h1->Clone("e_plus");
  TH1D* e_minus = (TH1D*)h2->Clone("e_plus");
  e_plus->Rebin(nrebin);
  e_minus->Rebin(nrebin);
 /* for(int binn=1;binn<=e_plus->GetNbinsX();binn++){
    e_plus->SetBinContent(binn,e_plus->GetBinContent(binn)/e_plus->GetBinWidth(binn));
    e_minus->SetBinContent(binn,e_minus->GetBinContent(binn)/e_plus->GetBinWidth(binn));
    e_plus->SetBinError(binn,e_plus->GetBinError(binn)/e_plus->GetBinWidth(binn)); 
    e_minus->SetBinError(binn,e_minus->GetBinError(binn)/e_plus->GetBinWidth(binn)); 
  }

  e_plus->Scale(244.9/MyWeight);
  e_minus->Scale(244.9/MyWeight);*/

  TH1D* delta= (TH1D*)e_plus->Clone("delta");
  delta->Add(e_minus,-1);
  //delta->Scale(100);
  TH1D* sum= (TH1D*)e_plus->Clone("sum");
  sum->Add(e_minus);

  delta->Divide(delta,sum,1,1);

for(int binn=1;binn<=e_plus->GetNbinsX();binn++){
    delta->SetBinContent(binn,100*delta->GetBinContent(binn));
    delta->SetBinError(binn,100*delta->GetBinError(binn));
  }


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
          TH1D *v_plus=(TH1D*)v_pluss->Clone("v_plus");
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

