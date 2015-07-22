


void splithist(double ratio=0.2){

  TVirtualPad* pmain = TVirtualPad::Pad();
  
  double h = 1. - pmain->GetTopMargin() - pmain->GetBottomMargin();

  double xlow = 0.; //gStyle->GetPadLeftMargin();
  double xhigh = 1.; // - gStyle->GetPadRightMargin();

  double ytop = 1.; //- gStyle->GetPadTopMargin();
  double ybot = 0.; //gStyle->GetPadBottomMargin();
  double ymid = pmain->GetBottomMargin() + ratio * h; //ybot + ratio * (ytop-ybot);
  

  double yp1bot = ymid;
  double yp2top = ymid;

  TPad* p1 = new TPad(TString(pmain->GetName()) + "_1", pmain->GetTitle(),
		      xlow, yp1bot, xhigh, ytop);
  p1->SetNumber(1);
  TPad* p2 = new TPad(TString(pmain->GetName()) + "_2", pmain->GetTitle(), 
		      xlow, ybot, xhigh, yp2top);
  p2->SetNumber(2);
  p1->SetFillStyle(4000);
  p2->SetFillStyle(4000);

  double p1h = ytop - yp1bot;
  double p2h = yp2top - ybot;
  

/*
  p1->SetTopMargin(pmain->GetTopMargin()/p1h);
  p1->SetBottomMargin((ymid-yp1bot)/p1h);
  p1->SetLeftMargin(pmain->GetLeftMargin());
  p1->SetRightMargin(pmain->GetRightMargin());
  
  p2->SetTopMargin((ymid-yp2top)/p2h);
  p2->SetBottomMargin(pmain->GetBottomMargin()/p2h);
  p2->SetLeftMargin(pmain->GetLeftMargin());
  p2->SetRightMargin(pmain->GetRightMargin());
*/
    p1->SetTopMargin(0.11);
    p1->SetBottomMargin(0.);
    p1->SetRightMargin(0.02);
 
    p2->SetTopMargin(0.);
    p2->SetBottomMargin(0.3);
    p2->SetRightMargin(0.02);



  p2->Draw();
  p1->Draw();
  pmain->Modified();

  p1->cd();
}

void fixsplithist(TH1* htop, TH1* hbot){
  TVirtualPad* pmain = TVirtualPad::Pad()->GetCanvas();
  if(!pmain) return;
  TVirtualPad* p1 = pmain->cd(1);
  TVirtualPad* p2 = pmain->cd(2);

  if(!p1 || !p2) return;
  
  double scale = p1->GetHNDC() / p2->GetHNDC();

  double s = htop->GetYaxis()->GetLabelSize() * scale;
  double ss = htop->GetYaxis()->GetLabelSize();
  hbot->GetYaxis()->SetLabelSize(s);
  htop->GetYaxis()->SetLabelSize(ss);
  s = htop->GetYaxis()->GetTitleSize() * scale;
  hbot->GetYaxis()->SetTitleSize(s);

   hbot->GetYaxis()->SetTitleOffset(0.3);  
   htop->GetYaxis()->SetTitleOffset(0.8);  

  s = htop->GetYaxis()->GetLabelOffset() * scale;

  s = htop->GetXaxis()->GetLabelSize() * scale;
  hbot->GetXaxis()->SetLabelSize(s*1.3);
  htop->GetXaxis()->SetLabelSize(0.);
  s = htop->GetXaxis()->GetTitleSize() * scale;
  hbot->GetXaxis()->SetTitleSize(s*1.7);
  hbot->GetXaxis()->SetTitleOffset(0.8);
 

  s = htop->GetXaxis()->GetLabelOffset() * scale;
  hbot->GetXaxis()->SetLabelOffset(s);  


  hbot->GetYaxis()->SetNdivisions(5);
}



void plot_stack(TString var, TString xtitle, int setlog, int rebin, double lumi,TLatex * latexlab,int ise){
TString iselec;
iselec +=(ise);
TFile *data = TFile::Open("data_isElec_"+iselec+".root");
TFile *mc_s = TFile::Open("mc_signal_isElec_"+iselec+".root");
TFile *mc_o = TFile::Open("mc_other_isElec_"+iselec+".root");
TFile *st_tw_t = TFile::Open("ST_tWch_t_isElec_"+iselec+".root");
TFile *st_tw_tbar = TFile::Open("ST_tWch_tbar_isElec_"+iselec+".root");
TFile *st_t_t = TFile::Open("ST_tch_t_isElec_"+iselec+".root");
TFile *st_t_tbar = TFile::Open("ST_tch_tbar_isElec_"+iselec+".root");
TFile *wjet = TFile::Open("ST_WJet_isElec_"+iselec+".root");

TH1 * tmphdata  =(TH1D*)(data->Get(var));
TH1 * tmphmc_s  =(TH1D*)(mc_s->Get(var));
TH1 * tmphmc_o  =(TH1D*)(mc_o->Get(var));
TH1 * tmphst_t_t  =(TH1D*)(st_t_t->Get(var));
TH1 * tmphst_t_tbar  =(TH1D*)(st_t_tbar->Get(var));
TH1 * tmphst_tw_t  =(TH1D*)(st_tw_t->Get(var));
TH1 * tmphst_tw_tbar  =(TH1D*)(st_tw_tbar->Get(var));
TH1 * tmphwjet  =(TH1D*)(wjet->Get(var));

TH1D* hdata= (TH1D*)tmphdata->Clone("");
TH1D* hmc_s= (TH1D*)tmphmc_s->Clone("");
TH1D* hmc_o = (TH1D*)tmphmc_o->Clone("");
TH1D* hst_t_t= (TH1D*)tmphst_t_t->Clone("");
TH1D* hst_t_tbar = (TH1D*)tmphst_t_tbar->Clone("");
TH1D* hst_tw_t = (TH1D*)tmphst_tw_t->Clone("");
TH1D* hst_tw_tbar = (TH1D*)tmphst_tw_tbar->Clone("");
TH1D* hwjet = (TH1D*)tmphwjet->Clone("");



 hdata->Rebin(rebin);
 hmc_s->Rebin(rebin);
 hmc_o->Rebin(rebin);
 hst_t_t->Rebin(rebin);
 hst_t_tbar->Rebin(rebin);
 hst_tw_t->Rebin(rebin);
 hst_tw_tbar->Rebin(rebin);
 hwjet->Rebin(rebin);

TTree *tmc_s = (TTree *)mc_s->Get("tree");
Long64_t wmc_s;

tmc_s->SetBranchAddress("nentries",&wmc_s);
tmc_s->GetEntry(0);

TTree *tmc_o = (TTree *)mc_o->Get("tree");
Long64_t wmc_o;

tmc_o->SetBranchAddress("nentries",&wmc_o);
tmc_o->GetEntry(0);

TTree *tst_t_t = (TTree *)st_t_t->Get("tree");
Long64_t wst_t_t;
tst_t_t->SetBranchAddress("nentries",&wst_t_t);
tst_t_t->GetEntry(0);

TTree *tst_t_tbar = (TTree *)st_t_tbar->Get("tree");
Long64_t wst_t_tbar;
tst_t_tbar->SetBranchAddress("nentries",&wst_t_tbar);
tst_t_tbar->GetEntry(0);

TTree *tst_tw_t = (TTree *)st_tw_t->Get("tree");
Long64_t wst_tw_t;
tst_tw_t->SetBranchAddress("nentries",&wst_tw_t);
tst_tw_t->GetEntry(0);


TTree *tst_tw_tbar = (TTree *)st_tw_tbar->Get("tree");
Long64_t wst_tw_tbar;
tst_tw_tbar->SetBranchAddress("nentries",&wst_tw_tbar);
tst_tw_tbar->GetEntry(0);

TTree *twjet = (TTree *)wjet->Get("tree");
Long64_t wwjet;
twjet->SetBranchAddress("nentries",&wwjet);
twjet->GetEntry(0);

cout<<wmc_s<<"  "<<wmc_o<<"  "<<wst_t_t<<"  "<<wst_t_tbar<<"  "<<wwjet<<endl;

hmc_s->Scale(831.76*lumi/wmc_s);
hmc_o->Scale(831.76*lumi/wmc_o);
hst_t_t->Scale(136.02*lumi/wst_t_t);
hst_t_tbar->Scale(80.95*lumi/wst_t_tbar);
hst_tw_t->Scale(35.6*lumi/wst_tw_t);
hst_tw_tbar->Scale(35.6*lumi/wst_tw_tbar);
hwjet->Scale(3* 20508.9*lumi /wwjet);




TH1* stackmc= (TH1D*)hmc_s->Clone("stackmc");
stackmc->Add(hmc_o);
stackmc->Add(hst_t_t);
stackmc->Add(hst_t_tbar);
stackmc->Add(hst_tw_t);
stackmc->Add(hst_tw_tbar);
stackmc->Add(hwjet);
double asd=hdata->Integral()/stackmc->Integral();
cout <<asd<<endl;
stackmc->Scale(hdata->Integral()/stackmc->Integral());
hst_t_t->Scale(asd);
hst_t_tbar->Scale(asd);
hst_tw_t->Scale(asd);
hst_tw_tbar->Scale(asd);
hwjet->Scale(asd);
hmc_s->Scale(asd);
hmc_o->Scale(asd);

double h_data_max=-99;
double h_mc_max=-99;
double max=-99;

double h_data_min=9999999;
double h_mc_min=9999999;
double min=9999999;
for(int i=1; i<=hdata->GetNbinsX();i++){
double tmp1=hdata->GetBinContent(i);
double tmp2=stackmc->GetBinContent(i);
if(tmp1>h_data_max)h_data_max=tmp1;
if(tmp2>h_mc_max)h_mc_max=tmp2;
if(tmp1<h_data_min)h_data_min=tmp1;
if(tmp2<h_mc_min)h_mc_min=tmp2;
}
if(h_mc_max>h_data_max)max=h_mc_max;
if(h_mc_max<h_data_max)max=h_data_max;
if(h_mc_min<h_data_min)min=h_mc_min;
if(h_mc_min>h_data_min)min=h_data_min;

cout<<max<<" "<<h_data_max<<endl;
TH1* stacst= (TH1D*)hst_t_t->Clone("stackst");
stacst->Add(hst_t_tbar);
stacst->Add(hst_tw_t);
stacst->Add(hst_tw_tbar);

hmc_o->SetFillColor(634);
hmc_s->SetFillColor(633);
stacst->SetFillColor(616);
hwjet->SetFillColor(413);
stackmc->SetFillColor(634);

TLegend *leg1 = new TLegend(0.731567,0.553719,0.8980511,0.885385);
leg1->SetBorderSize(0);
leg1->SetFillColor(kWhite);
leg1->SetTextSize(0.03);
leg1->AddEntry(hmc_s, "t#bar{t} signal","peF");
leg1->AddEntry(hmc_o, "t#bar{t} other","peF");
leg1->AddEntry(stacst, "single top","peF");
leg1->AddEntry(hwjet, "WJets","peF");

hdata->SetMarkerStyle(20);



   THStack *hs = new THStack("hs","Stacked 1D histograms");
hs->Add(hwjet);
hs->Add(stacst);
hs->Add(hmc_o);
hs->Add(hmc_s);

  hs->SetHistogram(hmc_s);
TH1* mont = (TH1D*)stackmc->Clone();
mont->Divide(stackmc,hdata,1,1);

TCanvas *c1 = new TCanvas("c1","c1",800,800);
TPaveText *pt = new TPaveText(.09,.925,.70,0.98);
pt->SetFillColor(0);
   pt->SetBorderSize(0);
   pt->SetLineColor(0);

//TString Lumi="";
//Lumi +=(lumi);

   pt->AddText("CMS Preliminary #sqrt{s} = 13 TeV, #int L dt = 5.6 pb^{-1} ");

pt->Draw();
    latexlab->Draw();
          c1->cd(); 
          splithist(0.2);
          c1->cd(1);
          if(setlog)gPad->SetLogy();  
          hdata->SetMinimum(0.1);
          if(!setlog)hdata->SetMaximum(max+4);
          if(setlog)hdata->SetMaximum(max*4);
	  hdata->GetYaxis()->SetLabelSize(0.05);
	  hdata->GetYaxis()->SetTitleSize(0.06);
	  hdata->GetYaxis()->SetTitleOffset(0.89);
 	  hdata->SetYTitle("#Events");
          double firstbin = hdata->FindFirstBinAbove(0);
          double lastbin = hdata->FindLastBinAbove(0);
          hdata->GetXaxis()->SetRange(firstbin,lastbin);
          hdata->Draw("eX0C");
	  hs->Draw("hhistsames");
          hdata->Draw("eX0Csames");
          leg1->Draw("same");
/*
	  stackmc->GetYaxis()->SetLabelSize(0.05);
	  stackmc->GetYaxis()->SetTitleSize(0.06);
	  stackmc->GetYaxis()->SetTitleOffset(0.89);
	  stackmc->SetYTitle("#Events");
	  stackmc->Draw("hhist");
*/


          c1->cd(2);
          mont->GetXaxis()->SetRange(firstbin,lastbin);
          mont->GetXaxis()->SetTitleSize(0.3);
          mont->SetMarkerStyle(20);
          mont->Draw("eX0Csames");
          mont->SetXTitle(xtitle);
          mont->SetMinimum(0);
          mont->SetMaximum(2);
          mont->SetYTitle("MC/Data");
          fixsplithist(hdata,mont);
          TString a;
          a+=setlog;
          c1->Print("stack_plots/" + var +"_logy_" + a + "_iselec_" + iselec+ ".pdf");
          c1->Print("stack_plots/" + var +"_logy_" + a + "_iselec_" + iselec+ ".png");

}


void plot_stack_add(TString var, TString var2, TString xtitle, int setlog, int rebin, double lumi,TLatex * latexlab, int ise){


TString iselec;
iselec +=(ise);
TFile *data = TFile::Open("data_isElec_"+iselec+".root");
TFile *mc_s = TFile::Open("mc_signal_isElec_"+iselec+".root");
TFile *mc_o = TFile::Open("mc_other_isElec_"+iselec+".root");
TFile *st_tw_t = TFile::Open("ST_tWch_t_isElec_"+iselec+".root");
TFile *st_tw_tbar = TFile::Open("ST_tWch_tbar_isElec_"+iselec+".root");
TFile *st_t_t = TFile::Open("ST_tch_t_isElec_"+iselec+".root");
TFile *st_t_tbar = TFile::Open("ST_tch_tbar_isElec_"+iselec+".root");
TFile *wjet = TFile::Open("ST_WJet_isElec_"+iselec+".root");

TH1 * tmphdata  =(TH1D*)(data->Get(var));
TH1 * tmphmc_s  =(TH1D*)(mc_s->Get(var));
TH1 * tmphmc_o  =(TH1D*)(mc_o->Get(var));
TH1 * tmphst_t_t  =(TH1D*)(st_t_t->Get(var));
TH1 * tmphst_t_tbar  =(TH1D*)(st_t_tbar->Get(var));
TH1 * tmphst_tw_t  =(TH1D*)(st_tw_t->Get(var));
TH1 * tmphst_tw_tbar  =(TH1D*)(st_tw_tbar->Get(var));
TH1 * tmphwjet  =(TH1D*)(wjet->Get(var));

TH1D* hdata= (TH1D*)tmphdata->Clone("");
TH1D* hmc_s= (TH1D*)tmphmc_s->Clone("");
TH1D* hmc_o = (TH1D*)tmphmc_o->Clone("");
TH1D* hst_t_t= (TH1D*)tmphst_t_t->Clone("");
TH1D* hst_t_tbar = (TH1D*)tmphst_t_tbar->Clone("");
TH1D* hst_tw_t = (TH1D*)tmphst_tw_t->Clone("");
TH1D* hst_tw_tbar = (TH1D*)tmphst_tw_tbar->Clone("");
TH1D* hwjet = (TH1D*)tmphwjet->Clone("");

TH1 * tmphdata2  =(TH1D*)(data->Get(var2));
TH1 * tmphmc_s2  =(TH1D*)(mc_s->Get(var2));
TH1 * tmphmc_o2  =(TH1D*)(mc_o->Get(var2));
TH1 * tmphst_t_t2  =(TH1D*)(st_t_t->Get(var2));
TH1 * tmphst_t_tbar2  =(TH1D*)(st_t_tbar->Get(var2));
TH1 * tmphst_tw_t2  =(TH1D*)(st_tw_t->Get(var2));
TH1 * tmphst_tw_tbar2  =(TH1D*)(st_tw_tbar->Get(var2));
TH1 * tmphwjet2  =(TH1D*)(wjet->Get(var2));



TH1D* hdata2= (TH1D*)tmphdata2->Clone("");
TH1D* hmc_s2= (TH1D*)tmphmc_s2->Clone("");
TH1D* hmc_o2 = (TH1D*)tmphmc_o2->Clone("");
TH1D* hst_t_t2= (TH1D*)tmphst_t_t2->Clone("");
TH1D* hst_t_tbar2 = (TH1D*)tmphst_t_tbar2->Clone("");
TH1D* hst_tw_t2 = (TH1D*)tmphst_tw_t2->Clone("");
TH1D* hst_tw_tbar2 = (TH1D*)tmphst_tw_tbar2->Clone("");
TH1D* hwjet2 = (TH1D*)tmphwjet2->Clone("");


 hdata->Rebin(rebin);
 hmc_s->Rebin(rebin);
 hmc_o->Rebin(rebin);
 hst_t_t->Rebin(rebin);
 hst_t_tbar->Rebin(rebin);
 hst_tw_t->Rebin(rebin);
 hst_tw_tbar->Rebin(rebin);
 hwjet->Rebin(rebin);

 hdata2->Rebin(rebin);
 hmc_s2->Rebin(rebin);
 hmc_o2->Rebin(rebin);
 hst_t_t2->Rebin(rebin);
 hst_t_tbar2->Rebin(rebin);
 hst_tw_t2->Rebin(rebin);
 hst_tw_tbar2->Rebin(rebin);
 hwjet2->Rebin(rebin);

 hdata->Add(hdata2);
 hmc_s->Add(hmc_s2);
 hmc_o->Add(hmc_o2);
 hst_t_t->Add(hst_t_t2);
 hst_t_tbar->Add(hst_t_tbar2);
 hst_tw_t->Add(hst_tw_t2);
 hst_tw_tbar->Add(hst_tw_tbar2);
 hwjet->Add(hwjet2);

TTree *tmc_s = (TTree *)mc_s->Get("tree");
Long64_t wmc_s;

tmc_s->SetBranchAddress("nentries",&wmc_s);
tmc_s->GetEntry(0);

TTree *tmc_o = (TTree *)mc_o->Get("tree");
Long64_t wmc_o;

tmc_o->SetBranchAddress("nentries",&wmc_o);
tmc_o->GetEntry(0);

TTree *tst_t_t = (TTree *)st_t_t->Get("tree");
Long64_t wst_t_t;
tst_t_t->SetBranchAddress("nentries",&wst_t_t);
tst_t_t->GetEntry(0);

TTree *tst_t_tbar = (TTree *)st_t_tbar->Get("tree");
Long64_t wst_t_tbar;
tst_t_tbar->SetBranchAddress("nentries",&wst_t_tbar);
tst_t_tbar->GetEntry(0);

TTree *tst_tw_t = (TTree *)st_tw_t->Get("tree");
Long64_t wst_tw_t;
tst_tw_t->SetBranchAddress("nentries",&wst_tw_t);
tst_tw_t->GetEntry(0);


TTree *tst_tw_tbar = (TTree *)st_tw_tbar->Get("tree");
Long64_t wst_tw_tbar;
tst_tw_tbar->SetBranchAddress("nentries",&wst_tw_tbar);
tst_tw_tbar->GetEntry(0);

TTree *twjet = (TTree *)wjet->Get("tree");
Long64_t wwjet;
twjet->SetBranchAddress("nentries",&wwjet);
twjet->GetEntry(0);

cout<<wmc_s<<"  "<<wmc_o<<"  "<<wst_t_t<<"  "<<wst_t_tbar<<"  "<<wwjet<<endl;

hmc_s->Scale(831.76*lumi/wmc_s);
hmc_o->Scale(831.76*lumi/wmc_o);
hst_t_t->Scale(136.02*lumi/wst_t_t);
hst_t_tbar->Scale(80.95*lumi/wst_t_tbar);
hst_tw_t->Scale(35.6*lumi/wst_tw_t);
hst_tw_tbar->Scale(35.6*lumi/wst_tw_tbar);
hwjet->Scale(3* 20508.9*lumi /wwjet);




TH1* stackmc= (TH1D*)hmc_s->Clone("stackmc");
stackmc->Add(hmc_o);
stackmc->Add(hst_t_t);
stackmc->Add(hst_t_tbar);
stackmc->Add(hst_tw_t);
stackmc->Add(hst_tw_tbar);
stackmc->Add(hwjet);
double asd=hdata->Integral()/stackmc->Integral();
cout <<asd<<endl;
stackmc->Scale(hdata->Integral()/stackmc->Integral());
hst_t_t->Scale(asd);
hst_t_tbar->Scale(asd);
hst_tw_t->Scale(asd);
hst_tw_tbar->Scale(asd);
hwjet->Scale(asd);
hmc_s->Scale(asd);
hmc_o->Scale(asd);

double h_data_max=-99;
double h_mc_max=-99;
double max=-99;

double h_data_min=9999999;
double h_mc_min=9999999;
double min=9999999;
for(int i=1; i<=hdata->GetNbinsX();i++){
double tmp1=hdata->GetBinContent(i);
double tmp2=stackmc->GetBinContent(i);
if(tmp1>h_data_max)h_data_max=tmp1;
if(tmp2>h_mc_max)h_mc_max=tmp2;
if(tmp1<h_data_min)h_data_min=tmp1;
if(tmp2<h_mc_min)h_mc_min=tmp2;
}
if(h_mc_max>h_data_max)max=h_mc_max;
if(h_mc_max<h_data_max)max=h_data_max;
if(h_mc_min<h_data_min)min=h_mc_min;
if(h_mc_min>h_data_min)min=h_data_min;

cout<<max<<" "<<h_data_max<<endl;
TH1* stacst= (TH1D*)hst_t_t->Clone("stackst");
stacst->Add(hst_t_tbar);
stacst->Add(hst_tw_t);
stacst->Add(hst_tw_tbar);

hmc_o->SetFillColor(634);
hmc_s->SetFillColor(633);
stacst->SetFillColor(616);
hwjet->SetFillColor(413);
stackmc->SetFillColor(634);

TLegend *leg1 = new TLegend(0.7931567,0.453719,0.94980511,0.685385);
leg1->SetBorderSize(0);
leg1->SetFillColor(kWhite);
leg1->SetTextSize(0.04);
leg1->AddEntry(hdata, "data","pe");
leg1->AddEntry(hmc_s, "t#bar{t} signal","peF");
leg1->AddEntry(hmc_o, "t#bar{t} other","peF");
leg1->AddEntry(stacst, "single top","peF");
leg1->AddEntry(hwjet, "WJets","peF");

hdata->SetMarkerStyle(20);



   THStack *hs = new THStack("hs","Stacked 1D histograms");
hs->Add(hwjet);
hs->Add(stacst);
hs->Add(hmc_o);
hs->Add(hmc_s);

  hs->SetHistogram(hmc_s);
TH1* mont = (TH1D*)stackmc->Clone();
mont->Divide(stackmc,hdata,1,1);

TCanvas *c1 = new TCanvas("c1","c1",800,800);
TPaveText *pt = new TPaveText(.09,.925,.70,0.98);
pt->SetFillColor(0);
   pt->SetBorderSize(0);
   pt->SetLineColor(0);

TString Lumi="";
Lumi +=(lumi);

   pt->AddText("CMS Preliminary #sqrt{s} = 13 TeV, #int L dt = 5.6 pb^{-1} ");

//pt->Draw();
   TLatex *latexLabell = new TLatex(); 

    latexLabell->SetTextSize(0.03305);
    latexLabell->SetTextFont(42);
    latexLabell->SetLineWidth(2);
    latexLabell->SetNDC();

    latexLabell->SetTextFont(61);
    latexLabell->DrawLatex(0.873,0.963-0.080,"CMS");
    latexLabell->SetTextFont(52);
    latexLabell->DrawLatex(0.793,0.963-0.120,"Preliminary");
    if(!ise)latexLabell->DrawLatex(0.693,0.963-0.160,"#mu + jets, =2 b-tags");
    if(ise)latexLabell->DrawLatex(0.693,0.963-0.160,"e + jets, =2 b-tags");
    latexLabell->SetTextFont(42);
   // latexLabell->DrawLatex(0.763,0.963-0.035,"5.6 pb^{-1} (13 TeV)");
 latexLabell->DrawLatex(0.763,0.963-0.035,"45 pb^{-1} (13 TeV)");
    latexLabell->Draw("same");

          c1->cd(); 
          splithist(0.2);
          c1->cd(1);
          if(setlog)gPad->SetLogy();  
          if(!setlog)hdata->SetMaximum(max+4);
          if(setlog)hdata->SetMaximum(max*4);
	  hdata->GetYaxis()->SetLabelSize(0.05);
	  hdata->GetYaxis()->SetTitleSize(0.06);
	  hdata->GetYaxis()->SetTitleOffset(0.89);
          cout<<"binwidth "<<hdata->GetBinWidth(5)<<endl;
	  hdata->SetYTitle("Events/(20 GeV)");
          double firstbinn = hdata->FindFirstBinAbove(0);
          double lastbinn = hdata->FindLastBinAbove(0);
          hdata->GetXaxis()->SetRange(firstbinn,lastbinn);
          if(var=="m_top")hdata->GetXaxis()->SetRange(firstbinn+2,lastbinn-24);
          hdata->Draw("e1X0C");
	  hs->Draw("hhistsames");
          hdata->Draw("e1X0Csames");
          leg1->Draw("same");
/*
	  stackmc->GetYaxis()->SetLabelSize(0.05);
	  stackmc->GetYaxis()->SetTitleSize(0.06);
	  stackmc->GetYaxis()->SetTitleOffset(0.89);
	  stackmc->SetYTitle("#Events");
	  stackmc->Draw("hhist");
*/


          c1->cd(2);
         //c1->Update();
          double fbnn=	hdata->GetBinCenter(firstbinn)- hdata->GetBinWidth(firstbinn)/2;
          double lbnn=	hdata->GetBinCenter(lastbinn)+	hdata->GetBinWidth(lastbinn)/2;
          if(var=="m_top"){
             fbnn=	hdata->GetBinCenter(firstbinn+2)- hdata->GetBinWidth(firstbinn+2)/2;   
             lbnn=	hdata->GetBinCenter(lastbinn-24) +hdata->GetBinWidth(lastbinn-24)/2; 
          }


          TLine *l=new TLine(fbnn,1.0,lbnn,1.0);
           l->SetLineColor(kBlue);

          mont->SetMarkerStyle(20);
          mont->GetXaxis()->SetRange(firstbinn,lastbinn);
          if(var=="m_top")mont->GetXaxis()->SetRange(firstbinn+2,lastbinn-24);
          mont->GetXaxis()->SetTitleSize(0.3);
          mont->Draw("eX0Csames");
          mont->SetXTitle(xtitle);
          mont->SetMinimum(0);
          mont->SetMaximum(2);
          mont->SetYTitle("MC/Data");
          l->Draw("same");
          fixsplithist(hdata,mont);

          TString a;
          a+=setlog;
          c1->Print("stack_plots/" + var + var2+"_logy_" + a + "_iselec_" + iselec+".pdf");
          c1->Print("stack_plots/" + var + var2+"_logy_" + a + "_iselec_" + iselec+ ".png");

}



void plot_stack_add_e_mu(TString var, TString var2, TString xtitle, int setlog, int rebin, double lumi,TLatex * latexlab, int ise){


TString iselec;
iselec +=(ise);
TFile *data = TFile::Open("data_isElec_0.root");
TFile *mc_s = TFile::Open("mc_signal_isElec_0.root");
TFile *mc_o = TFile::Open("mc_other_isElec_0.root");
TFile *st_tw_t = TFile::Open("ST_tWch_t_isElec_0.root");
TFile *st_tw_tbar = TFile::Open("ST_tWch_tbar_isElec_0.root");
TFile *st_t_t = TFile::Open("ST_tch_t_isElec_0.root");
TFile *st_t_tbar = TFile::Open("ST_tch_tbar_isElec_0.root");
TFile *wjet = TFile::Open("ST_WJet_isElec_0.root");

TFile *data_e = TFile::Open("data_isElec_1.root");
TFile *mc_s_e = TFile::Open("mc_signal_isElec_1.root");
TFile *mc_o_e = TFile::Open("mc_other_isElec_1.root");
TFile *st_tw_t_e = TFile::Open("ST_tWch_t_isElec_1.root");
TFile *st_tw_tbar_e = TFile::Open("ST_tWch_tbar_isElec_1.root");
TFile *st_t_t_e = TFile::Open("ST_tch_t_isElec_1.root");
TFile *st_t_tbar_e = TFile::Open("ST_tch_tbar_isElec_1.root");
TFile *wjet_e = TFile::Open("ST_WJet_isElec_1.root");

TH1 * tmphdata  =(TH1D*)(data->Get(var));
TH1 * tmphmc_s  =(TH1D*)(mc_s->Get(var));
TH1 * tmphmc_o  =(TH1D*)(mc_o->Get(var));
TH1 * tmphst_t_t  =(TH1D*)(st_t_t->Get(var));
TH1 * tmphst_t_tbar  =(TH1D*)(st_t_tbar->Get(var));
TH1 * tmphst_tw_t  =(TH1D*)(st_tw_t->Get(var));
TH1 * tmphst_tw_tbar  =(TH1D*)(st_tw_tbar->Get(var));
TH1 * tmphwjet  =(TH1D*)(wjet->Get(var));

TH1D* hdata= (TH1D*)tmphdata->Clone("");
TH1D* hmc_s= (TH1D*)tmphmc_s->Clone("");
TH1D* hmc_o = (TH1D*)tmphmc_o->Clone("");
TH1D* hst_t_t= (TH1D*)tmphst_t_t->Clone("");
TH1D* hst_t_tbar = (TH1D*)tmphst_t_tbar->Clone("");
TH1D* hst_tw_t = (TH1D*)tmphst_tw_t->Clone("");
TH1D* hst_tw_tbar = (TH1D*)tmphst_tw_tbar->Clone("");
TH1D* hwjet = (TH1D*)tmphwjet->Clone("");

TH1 * tmphdata2  =(TH1D*)(data->Get(var2));
TH1 * tmphmc_s2  =(TH1D*)(mc_s->Get(var2));
TH1 * tmphmc_o2  =(TH1D*)(mc_o->Get(var2));
TH1 * tmphst_t_t2  =(TH1D*)(st_t_t->Get(var2));
TH1 * tmphst_t_tbar2  =(TH1D*)(st_t_tbar->Get(var2));
TH1 * tmphst_tw_t2  =(TH1D*)(st_tw_t->Get(var2));
TH1 * tmphst_tw_tbar2  =(TH1D*)(st_tw_tbar->Get(var2));
TH1 * tmphwjet2  =(TH1D*)(wjet->Get(var2));



TH1D* hdata2= (TH1D*)tmphdata2->Clone("");
TH1D* hmc_s2= (TH1D*)tmphmc_s2->Clone("");
TH1D* hmc_o2 = (TH1D*)tmphmc_o2->Clone("");
TH1D* hst_t_t2= (TH1D*)tmphst_t_t2->Clone("");
TH1D* hst_t_tbar2 = (TH1D*)tmphst_t_tbar2->Clone("");
TH1D* hst_tw_t2 = (TH1D*)tmphst_tw_t2->Clone("");
TH1D* hst_tw_tbar2 = (TH1D*)tmphst_tw_tbar2->Clone("");
TH1D* hwjet2 = (TH1D*)tmphwjet2->Clone("");


TH1 * tmphdata_e  =(TH1D*)(data_e->Get(var));
TH1 * tmphmc_s_e  =(TH1D*)(mc_s_e->Get(var));
TH1 * tmphmc_o_e  =(TH1D*)(mc_o_e->Get(var));
TH1 * tmphst_t_t_e  =(TH1D*)(st_t_t_e->Get(var));
TH1 * tmphst_t_tbar_e  =(TH1D*)(st_t_tbar_e->Get(var));
TH1 * tmphst_tw_t_e  =(TH1D*)(st_tw_t_e->Get(var));
TH1 * tmphst_tw_tbar_e  =(TH1D*)(st_tw_tbar_e->Get(var));
TH1 * tmphwjet_e  =(TH1D*)(wjet_e->Get(var));

TH1D* hdata_e= (TH1D*)tmphdata_e->Clone("");
TH1D* hmc_s_e= (TH1D*)tmphmc_s_e->Clone("");
TH1D* hmc_o_e = (TH1D*)tmphmc_o_e->Clone("");
TH1D* hst_t_t_e= (TH1D*)tmphst_t_t_e->Clone("");
TH1D* hst_t_tbar_e = (TH1D*)tmphst_t_tbar_e->Clone("");
TH1D* hst_tw_t_e = (TH1D*)tmphst_tw_t_e->Clone("");
TH1D* hst_tw_tbar_e = (TH1D*)tmphst_tw_tbar_e->Clone("");
TH1D* hwjet_e = (TH1D*)tmphwjet_e->Clone("");

TH1 * tmphdata2_e  =(TH1D*)(data_e->Get(var2));
TH1 * tmphmc_s2_e  =(TH1D*)(mc_s_e->Get(var2));
TH1 * tmphmc_o2_e  =(TH1D*)(mc_o_e->Get(var2));
TH1 * tmphst_t_t2_e  =(TH1D*)(st_t_t_e->Get(var2));
TH1 * tmphst_t_tbar2_e  =(TH1D*)(st_t_tbar_e->Get(var2));
TH1 * tmphst_tw_t2_e  =(TH1D*)(st_tw_t_e->Get(var2));
TH1 * tmphst_tw_tbar2_e  =(TH1D*)(st_tw_tbar_e->Get(var2));
TH1 * tmphwjet2_e  =(TH1D*)(wjet_e->Get(var2));



TH1D* hdata2_e= (TH1D*)tmphdata2_e->Clone("");
TH1D* hmc_s2_e= (TH1D*)tmphmc_s2_e->Clone("");
TH1D* hmc_o2_e = (TH1D*)tmphmc_o2_e->Clone("");
TH1D* hst_t_t2_e= (TH1D*)tmphst_t_t2_e->Clone("");
TH1D* hst_t_tbar2_e = (TH1D*)tmphst_t_tbar2_e->Clone("");
TH1D* hst_tw_t2_e = (TH1D*)tmphst_tw_t2_e->Clone("");
TH1D* hst_tw_tbar2_e = (TH1D*)tmphst_tw_tbar2_e->Clone("");
TH1D* hwjet2_e = (TH1D*)tmphwjet2_e->Clone("");



 hdata->Rebin(rebin);
 hmc_s->Rebin(rebin);
 hmc_o->Rebin(rebin);
 hst_t_t->Rebin(rebin);
 hst_t_tbar->Rebin(rebin);
 hst_tw_t->Rebin(rebin);
 hst_tw_tbar->Rebin(rebin);
 hwjet->Rebin(rebin);

 hdata2->Rebin(rebin);
 hmc_s2->Rebin(rebin);
 hmc_o2->Rebin(rebin);
 hst_t_t2->Rebin(rebin);
 hst_t_tbar2->Rebin(rebin);
 hst_tw_t2->Rebin(rebin);
 hst_tw_tbar2->Rebin(rebin);
 hwjet2->Rebin(rebin);

hdata_e->Rebin(rebin);
 hmc_s_e->Rebin(rebin);
 hmc_o_e->Rebin(rebin);
 hst_t_t_e->Rebin(rebin);
 hst_t_tbar_e->Rebin(rebin);
 hst_tw_t_e->Rebin(rebin);
 hst_tw_tbar_e->Rebin(rebin);
 hwjet_e->Rebin(rebin);

 hdata2_e->Rebin(rebin);
 hmc_s2_e->Rebin(rebin);
 hmc_o2_e->Rebin(rebin);
 hst_t_t2_e->Rebin(rebin);
 hst_t_tbar2_e->Rebin(rebin);
 hst_tw_t2_e->Rebin(rebin);
 hst_tw_tbar2_e->Rebin(rebin);
 hwjet2_e->Rebin(rebin);

 hdata->Add(hdata2);
 hmc_s->Add(hmc_s2);
 hmc_o->Add(hmc_o2);
 hst_t_t->Add(hst_t_t2);
 hst_t_tbar->Add(hst_t_tbar2);
 hst_tw_t->Add(hst_tw_t2);
 hst_tw_tbar->Add(hst_tw_tbar2);
 hwjet->Add(hwjet2);


 hdata_e->Add(hdata2_e);
 hmc_s_e->Add(hmc_s2_e);
 hmc_o_e->Add(hmc_o2_e);
 hst_t_t_e->Add(hst_t_t2_e);
 hst_t_tbar_e->Add(hst_t_tbar2_e);
 hst_tw_t_e->Add(hst_tw_t2_e);
 hst_tw_tbar_e->Add(hst_tw_tbar2_e);
 hwjet_e->Add(hwjet2_e);

 

TTree *tmc_s = (TTree *)mc_s->Get("tree");
Long64_t wmc_s;

tmc_s->SetBranchAddress("nentries",&wmc_s);
tmc_s->GetEntry(0);

TTree *tmc_o = (TTree *)mc_o->Get("tree");
Long64_t wmc_o;

tmc_o->SetBranchAddress("nentries",&wmc_o);
tmc_o->GetEntry(0);

TTree *tst_t_t = (TTree *)st_t_t->Get("tree");
Long64_t wst_t_t;
tst_t_t->SetBranchAddress("nentries",&wst_t_t);
tst_t_t->GetEntry(0);

TTree *tst_t_tbar = (TTree *)st_t_tbar->Get("tree");
Long64_t wst_t_tbar;
tst_t_tbar->SetBranchAddress("nentries",&wst_t_tbar);
tst_t_tbar->GetEntry(0);

TTree *tst_tw_t = (TTree *)st_tw_t->Get("tree");
Long64_t wst_tw_t;
tst_tw_t->SetBranchAddress("nentries",&wst_tw_t);
tst_tw_t->GetEntry(0);


TTree *tst_tw_tbar = (TTree *)st_tw_tbar->Get("tree");
Long64_t wst_tw_tbar;
tst_tw_tbar->SetBranchAddress("nentries",&wst_tw_tbar);
tst_tw_tbar->GetEntry(0);

TTree *twjet = (TTree *)wjet->Get("tree");
Long64_t wwjet;
twjet->SetBranchAddress("nentries",&wwjet);
twjet->GetEntry(0);

cout<<wmc_s<<"  "<<wmc_o<<"  "<<wst_t_t<<"  "<<wst_t_tbar<<"  "<<wwjet<<endl;

hmc_s->Scale(831.76*lumi/wmc_s);
hmc_o->Scale(831.76*lumi/wmc_o);
hst_t_t->Scale(136.02*lumi/wst_t_t);
hst_t_tbar->Scale(80.95*lumi/wst_t_tbar);
hst_tw_t->Scale(35.6*lumi/wst_tw_t);
hst_tw_tbar->Scale(35.6*lumi/wst_tw_tbar);
hwjet->Scale(3* 20508.9*lumi /wwjet);


hmc_s_e->Scale(831.76*lumi/wmc_s);
hmc_o_e->Scale(831.76*lumi/wmc_o);
hst_t_t_e->Scale(136.02*lumi/wst_t_t);
hst_t_tbar_e->Scale(80.95*lumi/wst_t_tbar);
hst_tw_t_e->Scale(35.6*lumi/wst_tw_t);
hst_tw_tbar_e->Scale(35.6*lumi/wst_tw_tbar);
hwjet_e->Scale(3* 20508.9*lumi /wwjet);

TH1* stackmc_e= (TH1D*)hmc_s_e->Clone("stackmc_e");
stackmc_e->Add(hmc_o_e);
stackmc_e->Add(hst_t_t_e);
stackmc_e->Add(hst_t_tbar_e);
stackmc_e->Add(hst_tw_t_e);
stackmc_e->Add(hst_tw_tbar_e);
stackmc_e->Add(hwjet_e);
double asde=hdata_e->Integral()/stackmc_e->Integral();
cout <<asde<<endl;
stackmc_e->Scale(hdata_e->Integral()/stackmc_e->Integral());
hst_t_t_e->Scale(asde);
hst_t_tbar_e->Scale(asde);
hst_tw_t_e->Scale(asde);
hst_tw_tbar_e->Scale(asde);
hwjet_e->Scale(asde);
hmc_s_e->Scale(asde);
hmc_o_e->Scale(asde);


TH1* stackmc= (TH1D*)hmc_s->Clone("stackmc");
stackmc->Add(hmc_o);
stackmc->Add(hst_t_t);
stackmc->Add(hst_t_tbar);
stackmc->Add(hst_tw_t);
stackmc->Add(hst_tw_tbar);
stackmc->Add(hwjet);
double asd=hdata->Integral()/stackmc->Integral();
cout <<asd<<endl;
stackmc->Scale(hdata->Integral()/stackmc->Integral());
hst_t_t->Scale(asd);
hst_t_tbar->Scale(asd);
hst_tw_t->Scale(asd);
hst_tw_tbar->Scale(asd);
hwjet->Scale(asd);
hmc_s->Scale(asd);
hmc_o->Scale(asd);


hdata->Add(hdata_e);
 hmc_s->Add(hmc_s_e);
 hmc_o->Add(hmc_o_e);
 hst_t_t->Add(hst_t_t_e);
 hst_t_tbar->Add(hst_t_tbar_e);
 hst_tw_t->Add(hst_tw_t_e);
 hst_tw_tbar->Add(hst_tw_tbar_e);
 hwjet->Add(hwjet_e);


double h_data_max=-99;
double h_mc_max=-99;
double max=-99;

double h_data_min=9999999;
double h_mc_min=9999999;
double min=9999999;
for(int i=1; i<=hdata->GetNbinsX();i++){
double tmp1=hdata->GetBinContent(i);
double tmp2=stackmc->GetBinContent(i);
if(tmp1>h_data_max)h_data_max=tmp1;
if(tmp2>h_mc_max)h_mc_max=tmp2;
if(tmp1<h_data_min)h_data_min=tmp1;
if(tmp2<h_mc_min)h_mc_min=tmp2;
}
if(h_mc_max>h_data_max)max=h_mc_max;
if(h_mc_max<h_data_max)max=h_data_max;
if(h_mc_min<h_data_min)min=h_mc_min;
if(h_mc_min>h_data_min)min=h_data_min;

cout<<max<<" "<<h_data_max<<endl;
TH1* stacst= (TH1D*)hst_t_t->Clone("stackst");
stacst->Add(hst_t_tbar);
stacst->Add(hst_tw_t);
stacst->Add(hst_tw_tbar);

hmc_o->SetFillColor(634);
hmc_s->SetFillColor(633);
stacst->SetFillColor(616);
hwjet->SetFillColor(413);
stackmc->SetFillColor(634);

TLegend *leg1 = new TLegend(0.7931567,0.453719,0.94980511,0.685385);
leg1->SetBorderSize(0);
leg1->SetFillColor(kWhite);
leg1->SetTextSize(0.04);
leg1->AddEntry(hdata, "data","pe");
leg1->AddEntry(hmc_s, "t#bar{t} signal","peF");
leg1->AddEntry(hmc_o, "t#bar{t} other","peF");
leg1->AddEntry(stacst, "single top","peF");
leg1->AddEntry(hwjet, "WJets","peF");

hdata->SetMarkerStyle(20);



   THStack *hs = new THStack("hs","Stacked 1D histograms");
hs->Add(hwjet);
hs->Add(stacst);
hs->Add(hmc_o);
hs->Add(hmc_s);

  hs->SetHistogram(hmc_s);
TH1* mont = (TH1D*)stackmc->Clone();
mont->Divide(stackmc,hdata,1,1);

TCanvas *c1 = new TCanvas("c1","c1",800,800);
TPaveText *pt = new TPaveText(.09,.925,.70,0.98);
pt->SetFillColor(0);
   pt->SetBorderSize(0);
   pt->SetLineColor(0);

TString Lumi="";
Lumi +=(lumi);

   pt->AddText("CMS Preliminary #sqrt{s} = 13 TeV, #int L dt = 5.6 pb^{-1} ");

//pt->Draw();
   TLatex *latexLabell = new TLatex(); 

    latexLabell->SetTextSize(0.03305);
    latexLabell->SetTextFont(42);
    latexLabell->SetLineWidth(2);
    latexLabell->SetNDC();

    latexLabell->SetTextFont(61);
    latexLabell->DrawLatex(0.873,0.963-0.080,"CMS");
    latexLabell->SetTextFont(52);
    latexLabell->DrawLatex(0.793,0.963-0.120,"Preliminary");

    latexLabell->DrawLatex(0.533,0.963-0.160,"e, #mu + jets combined, =2 b-tags");
    latexLabell->SetTextFont(42);
   // latexLabell->DrawLatex(0.763,0.963-0.035,"5.6 pb^{-1} (13 TeV)");
 latexLabell->DrawLatex(0.763,0.963-0.035,"45 pb^{-1} (13 TeV)");
    latexLabell->Draw("same");

          c1->cd(); 
          splithist(0.2);
          c1->cd(1);
          if(setlog)gPad->SetLogy();  
          if(!setlog)hdata->SetMaximum(max+4);
          if(setlog)hdata->SetMaximum(max*4);
	  hdata->GetYaxis()->SetLabelSize(0.05);
	  hdata->GetYaxis()->SetTitleSize(0.06);
	  hdata->GetYaxis()->SetTitleOffset(0.89);
          cout<<"binwidth "<<hdata->GetBinWidth(5)<<endl;
	  hdata->SetYTitle("Events/(20 GeV)");
          double firstbinn = hdata->FindFirstBinAbove(0);
          double lastbinn = hdata->FindLastBinAbove(0);
          hdata->GetXaxis()->SetRange(firstbinn,lastbinn);
          if(var=="m_top")hdata->GetXaxis()->SetRange(firstbinn+2,lastbinn-24);
          hdata->Draw("e1X0C");
	  hs->Draw("hhistsames");
          hdata->Draw("e1X0Csames");
          leg1->Draw("same");
/*
	  stackmc->GetYaxis()->SetLabelSize(0.05);
	  stackmc->GetYaxis()->SetTitleSize(0.06);
	  stackmc->GetYaxis()->SetTitleOffset(0.89);
	  stackmc->SetYTitle("#Events");
	  stackmc->Draw("hhist");
*/


          c1->cd(2);
         //c1->Update();
          double fbnn=	hdata->GetBinCenter(firstbinn)- hdata->GetBinWidth(firstbinn)/2;
          double lbnn=	hdata->GetBinCenter(lastbinn)+	hdata->GetBinWidth(lastbinn)/2;
          if(var=="m_top"){
             fbnn=	hdata->GetBinCenter(firstbinn+2)- hdata->GetBinWidth(firstbinn+2)/2;   
             lbnn=	hdata->GetBinCenter(lastbinn-24) +hdata->GetBinWidth(lastbinn-24)/2; 
          }


          TLine *l=new TLine(fbnn,1.0,lbnn,1.0);
           l->SetLineColor(kBlue);

          mont->SetMarkerStyle(20);
          mont->GetXaxis()->SetRange(firstbinn,lastbinn);
          if(var=="m_top")mont->GetXaxis()->SetRange(firstbinn+2,lastbinn-24);
          mont->GetXaxis()->SetTitleSize(0.3);
          mont->Draw("eX0Csames");
          mont->SetXTitle(xtitle);
          mont->SetMinimum(0);
          mont->SetMaximum(2);
          mont->SetYTitle("MC/Data");
          l->Draw("same");
          fixsplithist(hdata,mont);

          TString a;
          a+=setlog;
          c1->Print("stack_plots/" + var + var2+"_logy_" + a + "_mu_elec_comb_.pdf");
          c1->Print("stack_plots/" + var + var2+"_logy_" + a + "_mu_elec_comb_.png");

}


void macro_data_mc_comp(){

   gStyle->SetOptStat(kFALSE);
   gStyle->SetOptTitle(kFALSE);
//  double lumii=23.757;
   double lumii=5.6;
    TLatex *latexLabel = new TLatex(); 

    latexLabel->SetTextSize(0.03305);
    latexLabel->SetTextFont(42);
    latexLabel->SetLineWidth(2);
    latexLabel->SetNDC();

    latexLabel->SetTextFont(61);
    latexLabel->DrawLatex(0.13,0.963,"CMS");
    latexLabel->SetTextFont(52);
    latexLabel->DrawLatex(0.20,0.963,"Preliminary");
    latexLabel->SetTextFont(42);
    latexLabel->DrawLatex(0.13,0.963-0.035,"5.6 pb^{-1} (13 TeV)");





/*TString a="reco_njet_1muev";
TString b="njet for excl 1 mu events";
plot_stack(a,b);

TString a="reco_nlep";
TString b="nlep";
plot_stack(a,b);*/

/*plot_stack("reco_nlep","nlep",1,4,lumii);
plot_stack("reco_njet","njet no lep sel",1,4,lumii);

plot_stack("reco_njet_1muev_inc","njet 1 mu inc",1,4,lumii);
plot_stack("reco_nbjet","n bjetno lep sel",1,4,lumii);
plot_stack("reco_nbjet_1muev_inc","n bjet 1 mu inc",1,4,lumii);
plot_stack("reco_nbjet_1muev","n bjet 1 mu exc",1,4,lumii);
plot_stack("reco_nbjet_1muev_inc","n bjet 1 mu inc",1,4,lumii);
plot_stack("muon_pt_1muev","mu pt 1mu excl",1,4,lumii);
plot_stack("muon_eta_1muev","mu eta 1mu excl",1,4,lumii);
plot_stack("ljet_pt_1muev","leading jet pt 1mu excl",1,4,lumii);
//plot_stack("ljet_eta_1muev","leading jet eta 1mu excl",4,lumii);
plot_stack("sljet_pt_1muev","subleading jet pt 1mu excl",1,4,lumii);
plot_stack("sljet_eta_1muev","subleading jet eta 1mu excl",1,4,lumii);
plot_stack("MET_ET","MET no lep sel",1,4,lumii);
plot_stack("MET_ET_1muev","MET 1mu excl",1,4,lumii);
plot_stack("MTW_1muev","MTW 1mu excl",1,4,lumii);*/
for(int ise=0;ise<=1;ise++){
plot_stack("reco_njet_1muev","njet 1 mu exc",1,1,lumii,latexLabel,ise);
plot_stack("m_top","m(t) [GeV]",1,2,lumii,latexLabel,ise);
plot_stack("m_atop","m(#bar{t}) [GeV]",1,2,lumii,latexLabel,ise);
plot_stack("m_top","m(t) [GeV]",0,2,lumii,latexLabel,ise);
plot_stack("m_atop","m(#bar{t}) [GeV]",0,2,lumii,latexLabel,ise);
plot_stack("MTW","M_{T}W [GeV]",1,2,lumii,latexLabel,ise);
plot_stack("MTW","M_{T}W [GeV]",0,2,lumii,latexLabel,ise);
plot_stack("rec_ttjY","y(t#bar{t}j)",1,2,lumii,latexLabel,ise);
plot_stack("rec_ttjY","y(t#bar{t}j)",0,2,lumii,latexLabel,ise);
plot_stack("m_ttbar","m(t#bar{t}) [GeV]",1,4,lumii,latexLabel,ise);
plot_stack("y_ttbar","y(t#bar{t})",1,4,lumii,latexLabel,ise);
plot_stack("pt_ttbar","p_{T}(t#bar{t}) [GeV]",1,4,lumii,latexLabel,ise);
plot_stack("njet_ttbar","n_{jet}",1,1,lumii,latexLabel,ise);
plot_stack("pt_top","p_{T}(t) [GeV] ",1,4,lumii,latexLabel,ise);
plot_stack("pt_atop","p_{T}(#bar{t}) [GeV]",1,4,lumii,latexLabel,ise);
plot_stack("y_top","y(t)",1,4,lumii,latexLabel,ise);
plot_stack("y_atop","y(#bar{t})",1,4,lumii,latexLabel,ise);
plot_stack("m_ttbar","m(t#bar{t}) [GeV]",0,4,lumii,latexLabel,ise);
plot_stack("y_ttbar","y(t#bar{t})",0,4,lumii,latexLabel,ise);
plot_stack("pt_ttbar","p_{T}(t#bar{t}) [GeV]",0,4,lumii,latexLabel,ise);
plot_stack("njet_ttbar","n_{jet}",0,1,lumii,latexLabel,ise);
plot_stack("pt_top","p_{T}(t) [GeV]",0,4,lumii,latexLabel,ise);
plot_stack("pt_atop","p_{T}(#bar{t}) [GeV]",0,4,lumii,latexLabel,ise);
plot_stack("y_top","y(t)",0,4,lumii,latexLabel,ise);
plot_stack("y_atop","y(#bar{t})",0,4,lumii,latexLabel,ise);
plot_stack("deltaY_reco","|y_{t}| -|y_{#bar{t}}|",0,5,lumii,latexLabel,ise);


plot_stack_add("m_top","m_atop","m_{t} [GeV]",1,4,lumii,latexLabel,ise);
plot_stack_add("pt_top","pt_atop","p_{T}(t) [GeV]",1,4,lumii,latexLabel,ise);
plot_stack_add("m_top","m_atop","m_{t} [GeV]",0,2,lumii,latexLabel,ise);
plot_stack_add("pt_top","pt_atop","p_{T}(t) [GeV]",0,4,lumii,latexLabel,ise);

plot_stack_add_e_mu("m_top","m_atop","m_{t} [GeV]",1,4,lumii,latexLabel,ise);
plot_stack_add_e_mu("pt_top","pt_atop","p_{T}(t) [GeV]",1,4,lumii,latexLabel,ise);
plot_stack_add_e_mu("m_top","m_atop","m_{t} [GeV]",0,2,lumii,latexLabel,ise);
plot_stack_add_e_mu("pt_top","pt_atop","p_{T}(t) [GeV]",0,4,lumii,latexLabel,ise);
}

}


