void estimate_pdfunc_TH1(TString var, TString xtitle, TString ytitle, int setlog,int setlogx, int rebin, double lumi,TLatex * latexlab,int ise, TString mult,double binmin, double binmax,double binminy, double binmaxy,TString vno){
TString iselec;
iselec +=(ise);
   gStyle->SetOptStat(kFALSE);
   gStyle->SetOptTitle(kFALSE);
TFile *mc_s = TFile::Open("25ns_tt_uev_miniaodv2_2110_fromskimmed_isElec_"+iselec+vno+".root");
   TH1* hist_tmp[103];
   TH1* hist[103];
   TH1* disc[103];

   TH1* sum;
   TH1* discsq[103];
   TH1* discsqsum;
   TH1* sqrtdiscsqsum;
TCanvas *c1= new TCanvas("c1","c1",800,800);
c1->cd();

//gPad->SetLogy();

for(int i=0;i<102;i++){
TString ii;
ii +=(i);
hist_tmp[i]= (TH1D*)mc_s->Get(var+"_"+ii);
hist[i]=(TH1D*)hist_tmp[i]->Clone("hist");
for(int bin=1; bin<=hist[i]->GetNbinsX();bin++){
hist[i]->SetBinContent(bin,hist[i]->GetBinContent(bin)/hist[i]->GetBinWidth(bin));
hist[i]->SetBinError(bin,hist[i]->GetBinError(bin)/hist[i]->GetBinWidth(bin));
cout<<i<<"  "<<bin<<"  "<< hist[i]->GetBinContent(bin)-hist[0]->GetBinContent(bin) <<endl;
}



if(i==0)hist[i]->Draw();
else /*if(i%20==0)*/hist[i]->Draw("same");
if(i==1)sum= (TH1D*)hist[1]->Clone("sum");
if(i>1)sum->Add(hist[i]);

}
sum->Scale(1/100.);
cout<<hist[0]->GetBinContent(26)<<endl;
cout<<sum->GetBinContent(26)<<endl;
for(int i=0;i<101;i++){


//disc[i]=(TH1D*)hist[i]->Clone("disc");
//disc[i]->Add(sum,-1);
//cout<<disc[i]->GetBinContent(2)<<endl;
//cout<<hist[i]->GetBinContent(2)<<endl;
//discsq[i]= (TH1D*)disc[i]->Clone("discsq") ;
//discsq[i]->Multiply(disc[i]);

disc[i]=(TH1D*)sum->Clone("disc");
//disc[i]->Add(sum,-1);
//cout<<disc[i]->GetBinContent(2)<<endl;
//cout<<hist[i]->GetBinContent(2)<<endl;
discsq[i]= (TH1D*)sum->Clone("discsq") ;

for(int bin=1; bin<=discsq[i]->GetNbinsX();bin++){

disc[i]->SetBinContent(bin,hist[i]->GetBinContent(bin)-sum->GetBinContent(bin));

discsq[i]->SetBinContent(bin,disc[i]->GetBinContent(bin)*disc[i]->GetBinContent(bin));
}



if(i==1)discsqsum =(TH1D*)discsq[i]->Clone("discsqsum");
if(i>1)discsqsum->Add(discsq[i]);




}
discsqsum->Scale(1/99.);
cout<<discsqsum->GetBinContent(26)<<endl;
TH1* histup= (TH1D *) hist[0]->Clone("histup");
TH1* histdown= (TH1D *) hist[0]->Clone("histdn");
for(int bin=1; bin<=hist[0]->GetNbinsX();bin++){
//cout<<bin<<" "<<sum->GetBinContent(bin)-hist[0]->GetBinContent(bin)<<"  "<<hist[0]->GetBinContent(bin)<<"  "<<sqrt(discsqsum->GetBinContent(bin))<<endl;
histup->SetBinContent(bin,hist[0]->GetBinContent(bin)+sqrt(discsqsum->GetBinContent(bin)));
histdown->SetBinContent(bin,hist[0]->GetBinContent(bin)-sqrt(discsqsum->GetBinContent(bin)));
}
cout<<histup->GetBinContent(1)<<endl;
cout<<histdown->GetBinContent(1)<<endl;

histup->Draw("samehhist");
histdown->Draw("samehhist");
          TString a;
          a+=setlog;
c1->Print("pdfvar_25ns_uev"+vno + "/" + var +"_logy_" + a + "_iselec_" + iselec+ ".pdf");
c1->Print("pdfvar_25ns_uev"+vno + "/" + var +"_logy_" + a + "_iselec_" + iselec+ ".png");
c1->Print("pdfvar_25ns_uev"+vno + "/" + var +"_logy_" + a + "_iselec_" + iselec+ ".root");
TCanvas *c2= new TCanvas("c2","c2",800,800);
c2->cd();
hist[0]->Draw();
histup->Draw("samehhist");
histdown->Draw("samehhist");
c2->Print("pdfvar_25ns_uev"+vno + "/" + var +"_logy_" + a + "_iselec_" + iselec+ "_envelope.pdf");
c2->Print("pdfvar_25ns_uev"+vno + "/" + var +"_logy_" + a + "_iselec_" + iselec+ "_envelope.png");
c2->Print("pdfvar_25ns_uev"+vno + "/" + var +"_logy_" + a + "_iselec_" + iselec+ "_envelope.root");
}


void estimate_pdfunc_profile(TString var, TString xtitle, TString ytitle, int setlog,int setlogx, int rebin, double lumi,TLatex * latexlab,int ise, TString mult,double binmin, double binmax,double binminy, double binmaxy,TString vno){
TString iselec;
iselec +=(ise);
   gStyle->SetOptStat(kFALSE);
   gStyle->SetOptTitle(kFALSE);
TFile *mc_s = TFile::Open("25ns_tt_uev_miniaodv2_2110_fromskimmed_isElec_"+iselec+vno+".root");
   TProfile* hist_tmp[103];
   TProfile* hist[103];
   TH1D* sum =new TH1D("sum","sum",100,0,100);
   TH1D* disc[103];
   TH1D* discsq[103];
   TH1D* discsqsum;
   TH1D* sqrtdiscsqsum;
   double sumbin[100];
TCanvas *c1= new TCanvas("c1","c1",800,800);
c1->cd();
for(int i=0;i<101;i++){
TString ii;
ii +=(i);
hist_tmp[i]= (TProfile*)mc_s->Get(var+"_"+ii);
hist[i]=(TProfile*)hist_tmp[i]->Clone("hist");

if(i==0)hist[i]->Draw();
else hist[i]->Draw("same");

for(int bin=1; bin<=hist[i]->GetNbinsX();bin++){
if(i==0){
sumbin[bin]=0;
}
else if(i<101){
sumbin[bin]+=hist[i]->GetBinContent(bin);
//cout<<i<<"  "<<bin<<"  "<<sumbin[bin]<<endl;
}
}
//cout<<hist[i]->GetBinContent(1)<<endl;

}
int nbinsX=hist[0]->GetNbinsX();
double binrangeX[nbinsX];
//sum= (TProfile*)hist[0]->Clone("sum");
for(int bin=1; bin<=hist[0]->GetNbinsX();bin++){
binrangeX[bin-1]= hist[0]->GetXaxis()->GetBinCenter(bin)-hist[0]->GetXaxis()->GetBinWidth(bin)/2;
//cout<< hist[0]->GetXaxis()->GetBinCenter(bin)-hist[0]->GetXaxis()->GetBinWidth(bin)/2<<endl;
sum->SetBinContent(bin,sumbin[bin]);
}

sum->Scale(1/100.);
//cout<<hist[0]->GetBinContent(1)<<endl;
//cout<<"aaa"<<sum->GetBinContent(1)<<endl;
for(int i=0;i<101;i++){
disc[i]=(TH1D*)sum->Clone("disc");
//disc[i]->Add(sum,-1);
//cout<<disc[i]->GetBinContent(2)<<endl;
//cout<<hist[i]->GetBinContent(2)<<endl;
discsq[i]= (TH1D*)sum->Clone("discsq") ;

for(int bin=1; bin<=discsq[i]->GetNbinsX();bin++){

disc[i]->SetBinContent(bin,hist[i]->GetBinContent(bin)-sum->GetBinContent(bin));

discsq[i]->SetBinContent(bin,disc[i]->GetBinContent(bin)*disc[i]->GetBinContent(bin));
}
if(i==1)discsqsum =(TH1D*)discsq[i]->Clone("discsqsum");
if(i>1)discsqsum->Add(discsq[i]);
}
discsqsum->Scale(1/99.);
//cout<<discsqsum->GetBinContent(1)<<" "<<sqrt(discsqsum->GetBinContent(1))*100/hist[0]->GetBinContent(1)<<endl;


//   TProfile* histup = new TProfile("histup","histup",nbinsX,binrangeX,0,1000000);
//   TProfile* histdown= new TProfile("histdown","histdown",nbinsX,binrangeX,0,1000000);
   TProfile* histup;
   TProfile* histdown;
histup= (TProfile *) hist[0]->Clone("histup");
histdown= (TProfile *) hist[0]->Clone("histdn");
//histup->Scale(0);
//histdn->Scale(0);

for(int bin=1; bin<=hist[0]->GetNbinsX();bin++){
//cout<<bin<<" "<<sqrt(discsqsum->GetBinContent(bin))<<endl;
histup->Fill(hist[0]->GetXaxis()->GetBinCenter(bin),hist[0]->GetBinContent(bin)+sqrt(discsqsum->GetBinContent(bin)),  100000000000000000);
histdown->Fill(hist[0]->GetXaxis()->GetBinCenter(bin),hist[0]->GetBinContent(bin)-sqrt(discsqsum->GetBinContent(bin)),100000000000000000);

}
//cout<<histup->GetBinContent(1)<<endl;
//cout<<histdown->GetBinContent(1)<<endl;
          TString a;
          a+=setlog;

c1->Print("pdfvar_25ns_uev"+vno + "/" + var +"_logy_" + a + "_iselec_" + iselec+ ".pdf");
c1->Print("pdfvar_25ns_uev"+vno + "/" + var +"_logy_" + a + "_iselec_" + iselec+ ".png");
c1->Print("pdfvar_25ns_uev"+vno + "/" + var +"_logy_" + a + "_iselec_" + iselec+ ".root");
TCanvas *c2= new TCanvas("c2","c2",800,800);
c2->cd();
hist[0]->Draw();
histup->Draw("samehhist");
histdown->Draw("samehhist");
c2->Print("pdfvar_25ns_uev"+vno + "/" + var +"_logy_" + a + "_iselec_" + iselec+ "_envelope.pdf");
c2->Print("pdfvar_25ns_uev"+vno + "/" + var +"_logy_" + a + "_iselec_" + iselec+ "_envelope.png");
c2->Print("pdfvar_25ns_uev"+vno + "/" + var +"_logy_" + a + "_iselec_" + iselec+ "_envelope.root");

}

void macro_pdfunc(){
   double lumii=1263;
//   double lumii=552.6;
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

for(int ise=0;ise<=1;ise++){
if(ise==1)continue;

estimate_pdfunc_TH1("y_ttbar","y (t#bar{t})","# Events",1,0,1,lumii,latexLabel,ise," ",0,2.2,0,55,"_v12");
estimate_pdfunc_profile("profile_ytt_npf","y (t#bar{t})","N_{ch}",1,0,1,lumii,latexLabel,ise," ",0,2.2,0,55,"_v12");
}

}
