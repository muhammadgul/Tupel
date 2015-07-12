


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

   hbot->GetYaxis()->SetTitleOffset(0.5);  
   htop->GetYaxis()->SetTitleOffset(0.5);  

  s = htop->GetYaxis()->GetLabelOffset() * scale;

  s = htop->GetXaxis()->GetLabelSize() * scale;
  hbot->GetXaxis()->SetLabelSize(s);
  htop->GetXaxis()->SetLabelSize(0.);
  s = htop->GetXaxis()->GetTitleSize() * scale;
  hbot->GetXaxis()->SetTitleSize(s);

 

  s = htop->GetXaxis()->GetLabelOffset() * scale;
  hbot->GetXaxis()->SetLabelOffset(s);  


  hbot->GetYaxis()->SetNdivisions(5);
}



void plot_stack(TString var, TString xtitle, int setlog){

TFile *data = TFile::Open("data.root");
TFile *mc_s = TFile::Open("mc_signal.root");
TFile *mc_o = TFile::Open("mc_other.root");
TFile *st_tw_t = TFile::Open("ST_tWch_t.root");
TFile *st_tw_tbar = TFile::Open("ST_tWch_tbar.root");
TFile *st_t_t = TFile::Open("ST_tch_t.root");
TFile *st_t_tbar = TFile::Open("ST_tch_tbar.root");
TFile *wjet = TFile::Open("ST_WJet.root");

TH1 * hdata  =(TH1D*)(data->Get(var));
TH1 * hmc_s  =(TH1D*)(mc_s->Get(var));
TH1 * hmc_o  =(TH1D*)(mc_o->Get(var));
TH1 * hst_t_t  =(TH1D*)(st_t_t->Get(var));
TH1 * hst_t_tbar  =(TH1D*)(st_t_tbar->Get(var));
TH1 * hst_tw_t  =(TH1D*)(st_tw_t->Get(var));
TH1 * hst_tw_tbar  =(TH1D*)(st_tw_tbar->Get(var));
TH1 * hwjet  =(TH1D*)(wjet->Get(var));


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

hmc_s->Scale(831.76*5.7/wmc_s);
hmc_o->Scale(831.76*5.7/wmc_o);
hst_t_t->Scale(136.02*5.7/wst_t_t);
hst_t_tbar->Scale(80.95*5.7/wst_t_tbar);
hst_tw_t->Scale(35.6*5.7/wst_tw_t);
hst_tw_tbar->Scale(35.6*5.7/wst_tw_tbar);
hwjet->Scale(3* 20508.9*5.7 /wwjet);




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

TH1* stacst= (TH1D*)hst_t_t->Clone("stackst");
stacst->Add(hst_t_tbar);
stacst->Add(hst_tw_t);
stacst->Add(hst_tw_tbar);

hmc_o->SetFillColor(kGreen);
hmc_s->SetFillColor(kBlue);
stacst->SetFillColor(kRed);
hwjet->SetFillColor(kYellow);
stackmc->SetFillColor(kGreen);

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

hs->Add(stacst);
hs->Add(hmc_o);
hs->Add(hmc_s);
hs->Add(hwjet);
  hs->SetHistogram(hmc_s);
TH1* mont = (TH1D*)stackmc->Clone();
mont->Divide(stackmc,hdata,1,1);

TCanvas *c1 = new TCanvas("c1","c1",800,800);
TPaveText *pt = new TPaveText(.09,.925,.70,0.98);
pt->SetFillColor(0);
   pt->SetBorderSize(0);
   pt->SetLineColor(0);
   pt->AddText("CMS Preliminary #sqrt{s} = 13 TeV, #int L dt = 5.7 pb^{-1} ");

pt->Draw();

          c1->cd(); 
          splithist(0.2);
          c1->cd(1);
          if(setlog)gPad->SetLogy();  

	  hdata->GetYaxis()->SetLabelSize(0.05);
	  hdata->GetYaxis()->SetTitleSize(0.06);
	  hdata->GetYaxis()->SetTitleOffset(0.89);
	  hdata->SetYTitle("#Events");

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
          mont->SetMarkerStyle(20);
          mont->Draw("eX0Csames");
          mont->SetXTitle(xtitle);
          mont->SetMinimum(0);
          mont->SetMaximum(2);
          fixsplithist(hdata,mont);
          TString a;
          a+=setlog;
          c1->Print("stack_plots/" + var +"_logy_" + a + ".pdf");
}


void macro_data_mc_comp(){

   gStyle->SetOptStat(kFALSE);
   gStyle->SetOptTitle(kFALSE);

/*TString a="reco_njet_1muev";
TString b="njet for excl 1 mu events";
plot_stack(a,b);

TString a="reco_nlep";
TString b="nlep";
plot_stack(a,b);*/

plot_stack("reco_nlep","nlep",1);
plot_stack("reco_njet","njet no lep sel",1);
plot_stack("reco_njet_1muev","njet 1 mu exc",1);
plot_stack("reco_njet_1muev_inc","njet 1 mu inc",1);
plot_stack("reco_nbjet","n bjetno lep sel",1);
plot_stack("reco_nbjet_1muev_inc","n bjet 1 mu inc",1);
plot_stack("reco_nbjet_1muev","n bjet 1 mu exc",1);
plot_stack("reco_nbjet_1muev_inc","n bjet 1 mu inc",1);
plot_stack("muon_pt_1muev","mu pt 1mu excl",1);
plot_stack("muon_eta_1muev","mu eta 1mu excl",1);
plot_stack("ljet_pt_1muev","leading jet pt 1mu excl",1);
//plot_stack("ljet_eta_1muev","leading jet eta 1mu excl");
plot_stack("sljet_pt_1muev","subleading jet pt 1mu excl",1);
plot_stack("sljet_pt_1muev","subleading jet eta 1mu excl",1);
plot_stack("MET_ET","MET no lep sel",1);
plot_stack("MET_ET_1muev","MET 1mu excl",1);
plot_stack("MTW_1muev","MTW 1mu excl",1);
plot_stack("m_top","Mt, =2b, >=4j",1);
plot_stack("m_atop","Mtbar, =2b, >=4j",1);
plot_stack("m_top","Mt, =2b, >=4j",0);
plot_stack("m_atop","Mtbar, =2b, >=4j",0);
plot_stack("MTW","MTW, =2b, >=4j",1);
plot_stack("MTW","MTW, =2b, >=4j",0);
}


