TH1D* estimate_puunc_TH1(TString vartmp,TString xtitletmp,TString ytitletmp,int setlogtmp,int setlogtmpx, int isetmp, TString vnotmp, int rebintmp){
TString iselec;
iselec +=(isetmp);
   gStyle->SetOptStat(kFALSE);
   gStyle->SetOptTitle(kFALSE);
TFile *mc_ss = TFile::Open("25ns_tt_uev_miniaodv2_2110_fromskimmed_isElec_"+iselec+vnotmp+".root");

//cout<<"25ns_tt_uev_newlist_2110_fromskimmed_isElec_"+iselec+vnotmp+".root"<<endl<<endl;
   TH1* hist_tmp[2];
   TH1* hist[2];

hist_tmp[0]= (TH1D*)mc_ss->Get(vartmp+"_0");
hist[0]=(TH1D*)hist_tmp[0]->Clone("hist0");


hist_tmp[1]= (TH1D*)mc_ss->Get(vartmp+"_1");
hist[1]=(TH1D*)hist_tmp[1]->Clone("hist1");
hist[0]->Rebin(rebintmp);
hist[1]->Rebin(rebintmp);

TCanvas *c111= new TCanvas("c111","c111",800,800);
c111->cd();
if(setlogtmp)gPad->SetLogy();
if(setlogtmpx)gPad->SetLogx();
hist[0]->GetXaxis()->SetTitle(xtitletmp);
hist[0]->GetYaxis()->SetTitle(ytitletmp);
for(int i=0;i<2;i++){
for(int bin=1; bin<=hist[i]->GetNbinsX();bin++){
hist[i]->SetBinContent(bin,hist[i]->GetBinContent(bin)/hist[i]->GetBinWidth(bin));
hist[i]->SetBinError(bin,hist[i]->GetBinError(bin)/hist[i]->GetBinWidth(bin));
hist[i]->SetLineColor(4*i+1);
//cout<<i<<"  "<<bin<<"  "<< hist[i]->GetBinContent(bin)-hist[0]->GetBinContent(bin) <<endl;
}

if(i==0)hist[i]->Draw();
else /*if(i%20==0)*/hist[i]->Draw("same");
}



TH1D* histup= (TH1D *) hist[0]->Clone("histup");

for(int bin=1; bin<=hist[0]->GetNbinsX();bin++){
//cout<<hist[1]->GetBinContent(bin)- hist[0]->GetBinContent(bin)<<endl;

double asd=0;

  asd=fabs(hist[1]->GetBinContent(bin)- hist[0]->GetBinContent(bin));

if(hist[1]->Integral()>0)histup->SetBinError(bin,asd);
if(hist[1]->Integral()==0)histup->SetBinError(bin,0.000001);
}
histup->SetFillColor(kYellow);
histup->Draw("e2same");
hist[0]->Draw("same");
hist[1]->Draw("same");

        TString a;
          a+=setlogtmp;
c111->Print("puvar_25ns_uev_v15/" + vartmp +"_logy_" + a + "_iselec_0.pdf");
c111->Print("puvar_25ns_uev_v15/" + vartmp +"_logy_" + a + "_iselec_0.png");
c111->Print("puvar_25ns_uev_v15/" + vartmp +"_logy_" + a + "_iselec_0.root");
c111->Close();

return histup;
mc_ss->Close();
delete mc_ss;


}


TH1D* estimate_puunc_profile(TString vartmp,TString xtitletmp, TString ytitletmp,int setlogtmp,int setlogtmpx, int isetmp, TString vnotmp, int rebintmp){
//cout<<"aaaaaaa"<<endl;
TString iselec;
iselec +=(isetmp);
   gStyle->SetOptStat(kFALSE);
   gStyle->SetOptTitle(kFALSE);
TFile *mc_ss = TFile::Open("25ns_tt_uev_miniaodv2_2110_fromskimmed_isElec_"+iselec+vnotmp+".root");

   TProfile* hist_tmp[2];
   TProfile* hist[2];


hist_tmp[0]= (TProfile*)mc_ss->Get(vartmp+"_0");
hist[0]=(TProfile*)hist_tmp[0]->Clone("hist0");


hist_tmp[1]= (TProfile*)mc_ss->Get(vartmp+"_1");
hist[1]=(TProfile*)hist_tmp[1]->Clone("hist1");

hist[0]->Rebin(rebintmp);
hist[1]->Rebin(rebintmp);

TCanvas *c111= new TCanvas("c111","c111",800,800);
c111->cd();
if(setlogtmp)gPad->SetLogy();
if(setlogtmpx)gPad->SetLogx();
hist[0]->GetXaxis()->SetTitle(xtitletmp);
hist[0]->GetYaxis()->SetTitle(ytitletmp);

for(int i=0;i<2;i++){
hist[i]->SetLineColor(4*i+1);
if(i==0)hist[i]->Draw();

else /*if(i%20==0)*/hist[i]->Draw("same");

}

int nbinsX=hist[0]->GetNbinsX();
//double binrangeX[nbinsX];


TH1D* histup;

TProfile * histupp= (TProfile *) hist[0]->Clone("histup");
TProfile * histdownn= (TProfile *) hist[0]->Clone("histdn");
histup=(TH1D*)histupp->ProjectionX();

for(int bin=1; bin<=hist[0]->GetNbinsX();bin++){

//cout<<hist[1]->GetBinContent(bin)- hist[0]->GetBinContent(bin)<<endl;

double asd=0;
  asd=fabs(hist[1]->GetBinContent(bin)- hist[0]->GetBinContent(bin));


histupp->Fill(hist[0]->GetXaxis()->GetBinCenter(bin),hist[0]->GetBinContent(bin)+asd,  100000000000000);
histdownn->Fill(hist[0]->GetXaxis()->GetBinCenter(bin),hist[0]->GetBinContent(bin)-asd,100000000000000);
if(hist[1]->Integral()>0)histup->SetBinError(bin,asd);
if(hist[1]->Integral()==0)histup->SetBinError(bin,0.000001);
//cout<<asd<<endl;
}
histupp->SetLineStyle(9);
histdownn->SetLineStyle(9);
histup->SetFillColor(kOrange);
histupp->SetLineColor(kOrange);
histdownn->SetLineColor(kOrange);
//cout << "  " <<histupp->GetLineStyle()<<"  "<<histdownn->GetLineStyle()<<endl;
histup->Draw("e2same");
hist[0]->Draw("same");
hist[1]->Draw("same");

//histupp->Draw("same");
//histdownn->Draw("same");
        TString a;
          a+=setlogtmp;
c111->Print("puvar_25ns_uev_v15/" + vartmp +"_logy_" + a + "_iselec_0.pdf");
c111->Print("puvar_25ns_uev_v15/" + vartmp +"_logy_" + a + "_iselec_0.png");
c111->Print("puvar_25ns_uev_v15/" + vartmp +"_logy_" + a + "_iselec_0.root");
c111->Close();
return histup;
mc_ss->Close();
delete mc_ss;


}




TH1D* estimate_jesunc_TH1(TString vartmp,TString xtitletmp,TString ytitletmp,int setlogtmp,int setlogtmpx, int isetmp, TString vnotmp, int rebintmp){
TString iselec;
iselec +=(isetmp);
   gStyle->SetOptStat(kFALSE);
   gStyle->SetOptTitle(kFALSE);
TFile *data_c = TFile::Open("25ns_data_D_uev_newlist_2110_fromskimmed_isElec_"+iselec+vnotmp+".root");
TFile *data_up = TFile::Open("25ns_data_D_uev_newlist_2110_fromskimmed_jes_1_isElec_"+iselec+vnotmp+".root");
TFile *data_dn = TFile::Open("25ns_data_D_uev_newlist_2110_fromskimmed_jes_-1_isElec_"+iselec+vnotmp+".root");



   TH1* hist_tmp[3];
   TH1* hist[3];


hist_tmp[0]= (TH1D*)data_c->Get(vartmp+"_0");
hist[0]=(TH1D*)hist_tmp[0]->Clone("hist0");


hist_tmp[1]= (TH1D*)data_up->Get(vartmp+"_0");
hist[1]=(TH1D*)hist_tmp[1]->Clone("hist1");


hist_tmp[2]= (TH1D*)data_dn->Get(vartmp+"_0");
hist[2]=(TH1D*)hist_tmp[2]->Clone("hist2");

hist[0]->Rebin(rebintmp);
hist[1]->Rebin(rebintmp);
hist[2]->Rebin(rebintmp);


TCanvas *c111= new TCanvas("c111","c111",800,800);
c111->cd();
if(setlogtmp)gPad->SetLogy();
if(setlogtmpx)gPad->SetLogx();
hist[0]->GetXaxis()->SetTitle(xtitletmp);
hist[0]->GetYaxis()->SetTitle(ytitletmp);
for(int i=0;i<3;i++){
for(int bin=1; bin<=hist[i]->GetNbinsX();bin++){
hist[i]->SetBinContent(bin,hist[i]->GetBinContent(bin)/hist[i]->GetBinWidth(bin));
hist[i]->SetBinError(bin,hist[i]->GetBinError(bin)/hist[i]->GetBinWidth(bin));
hist[i]->SetLineColor(4*i+1);
////cout<<i<<"  "<<bin<<"  "<< hist[i]->GetBinContent(bin)-hist[0]->GetBinContent(bin) <<endl;
}

if(i==0)hist[i]->Draw();
else /*if(i%20==0)*/hist[i]->Draw("same");
}



TH1D* histup= (TH1D *) hist[0]->Clone("histup");

for(int bin=1; bin<=hist[0]->GetNbinsX();bin++){
//cout<<hist[1]->GetBinContent(bin)- hist[0]->GetBinContent(bin)<<"  "<<hist[2]->GetBinContent(bin)- hist[0]->GetBinContent(bin)<<endl;

double asd=0;
if(fabs ( hist[1]->GetBinContent(bin)- hist[0]->GetBinContent(bin) )>fabs( hist[2]->GetBinContent(bin)- hist[0]->GetBinContent(bin) ) ){
  asd=fabs(hist[1]->GetBinContent(bin)- hist[0]->GetBinContent(bin));
}else{
  asd=fabs(hist[2]->GetBinContent(bin)- hist[0]->GetBinContent(bin));
}

if(hist[1]->Integral()>0)histup->SetBinError(bin,asd);
if(hist[1]->Integral()==0)histup->SetBinError(bin,0.000001);

}
histup->SetFillColor(kYellow);
histup->Draw("e2same");
hist[0]->Draw("same");
hist[1]->Draw("same");
hist[2]->Draw("same");
        TString a;
          a+=setlogtmp;
c111->Print("jesvar_25ns_uev_v15/" + vartmp +"_logy_" + a + "_iselec_0.pdf");
c111->Print("jesvar_25ns_uev_v15/" + vartmp +"_logy_" + a + "_iselec_0.png");
c111->Print("jesvar_25ns_uev_v15/" + vartmp +"_logy_" + a + "_iselec_0.root");
c111->Close();

return histup;
data_c->Close();
delete data_c;

data_up->Close();
delete data_up;
data_dn->Close();
delete data_dn;


}


TH1D* estimate_jesunc_profile(TString vartmp,TString xtitletmp, TString ytitletmp,int setlogtmp,int setlogtmpx, int isetmp, TString vnotmp, int rebintmp){
//cout<<"aaaaaaa"<<endl;
TString iselec;
iselec +=(isetmp);
   gStyle->SetOptStat(kFALSE);
   gStyle->SetOptTitle(kFALSE);
TFile *data_c = TFile::Open("25ns_data_D_uev_newlist_2110_fromskimmed_isElec_"+iselec+vnotmp+".root");
TFile *data_up = TFile::Open("25ns_data_D_uev_newlist_2110_fromskimmed_jes_1_isElec_"+iselec+vnotmp+".root");
TFile *data_dn = TFile::Open("25ns_data_D_uev_newlist_2110_fromskimmed_jes_-1_isElec_"+iselec+vnotmp+".root");
   TProfile* hist_tmp[3];
   TProfile* hist[3];


hist_tmp[0]= (TProfile*)data_c->Get(vartmp+"_0");
hist[0]=(TProfile*)hist_tmp[0]->Clone("hist0");


hist_tmp[1]= (TProfile*)data_up->Get(vartmp+"_0");
hist[1]=(TProfile*)hist_tmp[1]->Clone("hist1");


hist_tmp[2]= (TProfile*)data_dn->Get(vartmp+"_0");
hist[2]=(TProfile*)hist_tmp[2]->Clone("hist2");


hist[0]->Rebin(rebintmp);
hist[1]->Rebin(rebintmp);
hist[2]->Rebin(rebintmp);


TCanvas *c111= new TCanvas("c111","c111",800,800);
c111->cd();
if(setlogtmp)gPad->SetLogy();
if(setlogtmpx)gPad->SetLogx();
hist[0]->GetXaxis()->SetTitle(xtitletmp);
hist[0]->GetYaxis()->SetTitle(ytitletmp);
for(int i=0;i<3;i++){
hist[i]->SetLineColor(4*i+1);
if(i==0)hist[i]->Draw();

else /*if(i%20==0)*/hist[i]->Draw("same");

}

int nbinsX=hist[0]->GetNbinsX();
//double binrangeX[nbinsX];


TH1D* histup;

TProfile * histupp= (TProfile *) hist[0]->Clone("histup");
TProfile * histdownn= (TProfile *) hist[0]->Clone("histdn");
histup=(TH1D*)histupp->ProjectionX();

for(int bin=1; bin<=hist[0]->GetNbinsX();bin++){

//cout<<hist[1]->GetBinContent(bin)- hist[0]->GetBinContent(bin)<<"  "<<hist[2]->GetBinContent(bin)- hist[0]->GetBinContent(bin)<<endl;

double asd=0;
if(fabs ( hist[1]->GetBinContent(bin)- hist[0]->GetBinContent(bin) )>fabs( hist[2]->GetBinContent(bin)- hist[0]->GetBinContent(bin) ) ){
  asd=fabs(hist[1]->GetBinContent(bin)- hist[0]->GetBinContent(bin));
}else{
  asd=fabs(hist[2]->GetBinContent(bin)- hist[0]->GetBinContent(bin));
}

histupp->Fill(hist[0]->GetXaxis()->GetBinCenter(bin),hist[0]->GetBinContent(bin)+asd,  100000000000000);
histdownn->Fill(hist[0]->GetXaxis()->GetBinCenter(bin),hist[0]->GetBinContent(bin)-asd,100000000000000);
if(hist[1]->Integral()>0)histup->SetBinError(bin,asd);
if(hist[1]->Integral()==0)histup->SetBinError(bin,0.000001);
//cout<<asd<<endl;
}
histupp->SetLineStyle(9);
histdownn->SetLineStyle(9);
histup->SetFillColor(kOrange);
histupp->SetLineColor(kOrange);
histdownn->SetLineColor(kOrange);
//cout << "  " <<histupp->GetLineStyle()<<"  "<<histdownn->GetLineStyle()<<endl;
histup->Draw("e2same");
hist[0]->Draw("same");
hist[1]->Draw("same");
hist[2]->Draw("same");

//histupp->Draw("same");
//histdownn->Draw("same");
        TString a;
          a+=setlogtmp;
c111->Print("jesvar_25ns_uev_v15/" + vartmp +"_logy_" + a + "_iselec_0.pdf");
c111->Print("jesvar_25ns_uev_v15/" + vartmp +"_logy_" + a + "_iselec_0.png");
c111->Print("jesvar_25ns_uev_v15/" + vartmp +"_logy_" + a + "_iselec_0.root");
c111->Close();
return histup;
data_c->Close();
data_up->Close();
data_dn->Close();
delete data_c;


delete data_up;

delete data_dn;


}


TH1D* estimate_pdfunc_TH1(TString vartmp,TString xtitletmp, TString ytitletmp,int setlogtmp,int setlogtmpx, int isetmp, TString vnotmp, int rebintmp){
TString iselec;
iselec +=(isetmp);
   gStyle->SetOptStat(kFALSE);
   gStyle->SetOptTitle(kFALSE);
TFile *mc_ss = TFile::Open("25ns_tt_uev_miniaodv2_2110_fromskimmed_pdfvar_isElec_"+iselec+vnotmp+".root");
   TH1* hist_tmp[103];
   TH1* hist[103];
   TH1* disc[103];

   TH1* sum;
   TH1* discsq[103];
   TH1* discsqsum;
   TH1* sqrtdiscsqsum;

TCanvas *c111= new TCanvas("c111","c111",800,800);
c111->cd();
if(setlogtmp)gPad->SetLogy();
if(setlogtmpx)gPad->SetLogx();


for(int i=0;i<103;i++){
TString ii;
ii +=(i);
hist_tmp[i]= (TH1D*)mc_ss->Get(vartmp+"_"+ii);
hist[i]=(TH1D*)hist_tmp[i]->Clone("hist");
hist[i]->Rebin(rebintmp);


for(int bin=1; bin<=hist[i]->GetNbinsX();bin++){
hist[i]->SetBinContent(bin,hist[i]->GetBinContent(bin)/hist[i]->GetBinWidth(bin));
hist[i]->SetBinError(bin,hist[i]->GetBinError(bin)/hist[i]->GetBinWidth(bin));
////cout<<i<<"  "<<bin<<"  "<< hist[i]->GetBinContent(bin)-hist[0]->GetBinContent(bin) <<endl;
}
hist[0]->GetXaxis()->SetTitle(xtitletmp);
hist[0]->GetYaxis()->SetTitle(ytitletmp);
if(i==0)hist[i]->Draw();
else /*if(i%20==0)*/hist[i]->Draw("same");


if(i==1)sum= (TH1D*)hist[1]->Clone("sum");
if(i>1&&i<101)sum->Add(hist[i]);

}
sum->Scale(1/100.);
for(int i=1;i<101;i++){

disc[i]=(TH1D*)sum->Clone("disc");

discsq[i]= (TH1D*)sum->Clone("discsq") ;

for(int bin=1; bin<=discsq[i]->GetNbinsX();bin++){

disc[i]->SetBinContent(bin,hist[i]->GetBinContent(bin)-sum->GetBinContent(bin));

discsq[i]->SetBinContent(bin,disc[i]->GetBinContent(bin)*disc[i]->GetBinContent(bin));
}
if(i==1)discsqsum =(TH1D*)discsq[i]->Clone("discsqsum");
if(i>1)discsqsum->Add(discsq[i]);
}
discsqsum->Scale(1/99.);

TH1D* histup= (TH1D *) hist[0]->Clone("histup");
TH1D* histupp= (TH1D *) hist[0]->Clone("histup");
TH1D* histdownn= (TH1D *) hist[0]->Clone("histup");
for(int bin=1; bin<=hist[0]->GetNbinsX();bin++){
////cout<<bin<<" "<<sum->GetBinContent(bin)-hist[0]->GetBinContent(bin)<<"  "<<hist[0]->GetBinContent(bin)<<"  "<<sqrt(discsqsum->GetBinContent(bin))<<endl;
if(hist[1]->Integral()>0)histup->SetBinError(bin,sqrt(discsqsum->GetBinContent(bin)+(hist[101]->GetBinContent(bin)-hist[0]->GetBinContent(bin))*(hist[101]->GetBinContent(bin)-hist[0]->GetBinContent(bin)) + (hist[102]->GetBinContent(bin)-hist[0]->GetBinContent(bin))*(hist[102]->GetBinContent(bin)-hist[0]->GetBinContent(bin))));

if(hist[1]->Integral()==0)histup->SetBinError(bin,0.000001);
}

histupp->Add(histup);
histdownn->Add(histup,-1);
        TString a;
          a+=setlogtmp;
c111->Print("pdfvar_25ns_uev_v15/" + vartmp +"_logy_" + a + "_iselec_0.pdf");
c111->Print("pdfvar_25ns_uev_v15/" + vartmp +"_logy_" + a + "_iselec_0.png");
c111->Print("pdfvar_25ns_uev_v15/" + vartmp +"_logy_" + a + "_iselec_0.root");
c111->Close();
TCanvas *c222= new TCanvas("c222","c222",800,800);
c222->cd();
if(setlogtmp)gPad->SetLogy();
if(setlogtmpx)gPad->SetLogx();
hist[0]->GetXaxis()->SetTitle(xtitletmp);
hist[0]->GetYaxis()->SetTitle(ytitletmp);
hist[0]->Draw();

histupp->Draw("samehhist");
histdownn->Draw("samehhist");
c222->Print("pdfvar_25ns_uev_v15/" + vartmp +"_logy_" + a + "_iselec_0._envelope.pdf");
c222->Print("pdfvar_25ns_uev_v15/" + vartmp +"_logy_" + a + "_iselec_0._envelope.png");
c222->Print("pdfvar_25ns_uev_v15/" + vartmp +"_logy_" + a + "_iselec_0._envelope.root");

c222->Close();
return histup;
mc_ss->Close();
delete mc_ss;


}


TH1D* estimate_pdfunc_profile(TString vartmp,TString xtitletmp, TString ytitletmp,int setlogtmp,int setlogtmpx, int isetmp, TString vnotmp, int rebintmp){
//cout<<"aaaaaaa"<<endl;
TString iselec;
iselec +=(isetmp);
   gStyle->SetOptStat(kFALSE);
   gStyle->SetOptTitle(kFALSE);
TFile *mc_ss = TFile::Open("25ns_tt_uev_miniaodv2_2110_fromskimmed_pdfvar_isElec_"+iselec+vnotmp+".root");
   TProfile* hist_tmp[103];
   TProfile* hist[103];
   TH1D* sum =new TH1D("sum","sum",100,0,100);
   TH1D* disc[103];
   TH1D* discsq[103];
   TH1D* discsqsum;
   TH1D* sqrtdiscsqsum;
   double sumbin[100];

TCanvas *c111= new TCanvas("c111","c111",800,800);
c111->cd();
if(setlogtmp)gPad->SetLogy();
if(setlogtmpx)gPad->SetLogx();

//cout<<"bbbbbbbbbbbbb"<<endl;
for(int i=0;i<103;i++){
TString ii;
ii +=(i);
hist_tmp[i]= (TProfile*)mc_ss->Get(vartmp+"_"+ii);
hist[i]=(TProfile*)hist_tmp[i]->Clone("hist");

hist[0]->GetXaxis()->SetTitle(xtitletmp);
hist[0]->GetYaxis()->SetTitle(ytitletmp);

if(i==0)hist[i]->Draw();
else /*if(i%20==0)*/hist[i]->Draw("same");


for(int bin=1; bin<=hist[i]->GetNbinsX();bin++){
if(i==0){
sumbin[bin]=0;
}
else if(i<101){
sumbin[bin]+=hist[i]->GetBinContent(bin);
}
}
}
//cout<<"cccccccccccc"<<endl;

int nbinsX=hist[0]->GetNbinsX();
//double binrangeX[nbinsX];

for(int bin=1; bin<=hist[0]->GetNbinsX();bin++){
//binrangeX[bin-1]= hist[0]->GetXaxis()->GetBinCenter(bin)-hist[0]->GetXaxis()->GetBinWidth(bin)/2;

sum->SetBinContent(bin,sumbin[bin]);
}
//cout<<"ddddddddddddddddd"<<endl;
sum->Scale(1/100.);

for(int i=1;i<101;i++){
disc[i]=(TH1D*)sum->Clone("disc");

discsq[i]= (TH1D*)sum->Clone("discsq") ;

for(int bin=1; bin<=discsq[i]->GetNbinsX();bin++){

disc[i]->SetBinContent(bin,hist[i]->GetBinContent(bin)-sum->GetBinContent(bin));

discsq[i]->SetBinContent(bin,disc[i]->GetBinContent(bin)*disc[i]->GetBinContent(bin));
}
if(i==1)discsqsum =(TH1D*)discsq[i]->Clone("discsqsum");
if(i>1)discsqsum->Add(discsq[i]);
}
discsqsum->Scale(1/99.);
//cout<<"eeeeeeeeeeeeeeeeeee"<<endl;

TH1D* histup= (TH1D *)  hist[0]->ProjectionX();

   TProfile* histupp;
   TProfile* histdownn;
histupp= (TProfile *) hist[0]->Clone("histupp");
histdownn= (TProfile *) hist[0]->Clone("histdownn");


for(int bin=1; bin<=hist[0]->GetNbinsX();bin++){
//cout<<bin<<"  "<<hist[0]->GetBinContent(bin)<<"  "<<sqrt(discsqsum->GetBinContent(bin))<<endl;
if(hist[1]->Integral()>0)histup->SetBinError(bin,sqrt(discsqsum->GetBinContent(bin)+(hist[101]->GetBinContent(bin)-hist[0]->GetBinContent(bin))*(hist[101]->GetBinContent(bin)-hist[0]->GetBinContent(bin)) + (hist[102]->GetBinContent(bin)-hist[0]->GetBinContent(bin))*(hist[102]->GetBinContent(bin)-hist[0]->GetBinContent(bin))));

if(hist[1]->Integral()==0)histup->SetBinError(bin,0.000001);

double asde=sqrt( discsqsum->GetBinContent(bin)+ (hist[101]->GetBinContent(bin)-hist[0]->GetBinContent(bin))*(hist[101]->GetBinContent(bin)-hist[0]->GetBinContent(bin)) + (hist[102]->GetBinContent(bin)-hist[0]->GetBinContent(bin))*(hist[102]->GetBinContent(bin)-hist[0]->GetBinContent(bin)) );

histupp->Fill(hist[0]->GetXaxis()->GetBinCenter(bin),hist[0]->GetBinContent(bin)+asde,  100000000000000000);
histdownn->Fill(hist[0]->GetXaxis()->GetBinCenter(bin),hist[0]->GetBinContent(bin)-asde,100000000000000000);

//cout<<histup->GetBinContent(bin)<<endl;
}

        TString a;
          a+=setlogtmp;
c111->Print("pdfvar_25ns_uev_v15/" + vartmp +"_logy_" + a + "_iselec_0.pdf");
c111->Print("pdfvar_25ns_uev_v15/" + vartmp +"_logy_" + a + "_iselec_0.png");
c111->Print("pdfvar_25ns_uev_v15/" + vartmp +"_logy_" + a + "_iselec_0.root");
c111->Close();
TCanvas *c222= new TCanvas("c222","c222",800,800);
c222->cd();
if(setlogtmp)gPad->SetLogy();
if(setlogtmpx)gPad->SetLogx();
hist[0]->GetXaxis()->SetTitle(xtitletmp);
hist[0]->GetYaxis()->SetTitle(ytitletmp);
hist[0]->Draw();
histupp->Draw("samehhist");
histdownn->Draw("samehhist");
c222->Print("pdfvar_25ns_uev_v15/" + vartmp +"_logy_" + a + "_iselec_0._envelope.pdf");
c222->Print("pdfvar_25ns_uev_v15/" + vartmp +"_logy_" + a + "_iselec_0._envelope.png");
c222->Print("pdfvar_25ns_uev_v15/" + vartmp +"_logy_" + a + "_iselec_0._envelope.root");
c222->Close();



return histup;
//cout<<"ffffffffffffffffff"<<endl;
mc_ss->Close();
delete mc_ss;


}



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

   hbot->GetYaxis()->SetTitleOffset(0.45);  
   htop->GetYaxis()->SetTitleOffset(1.1295);  

  s = htop->GetYaxis()->GetLabelOffset() * scale;

  s = htop->GetXaxis()->GetLabelSize() * scale;
  hbot->GetXaxis()->SetLabelSize(s*1.3);
  htop->GetXaxis()->SetLabelSize(0.);
  s = htop->GetXaxis()->GetTitleSize() * scale;
  hbot->GetXaxis()->SetTitleSize(s*1.7);
  hbot->GetXaxis()->SetTitleOffset(0.9);
 

  s = htop->GetXaxis()->GetLabelOffset() * scale;
  hbot->GetXaxis()->SetLabelOffset(s);  


  hbot->GetYaxis()->SetNdivisions(5);
}
void plot_stack_overlay(TString var, TString var2, TString var3,TString var4, TString xtitle, TString ytitle, int setlog,int setlogx, int rebin, double lumi,TLatex * latexlab,int ise, TString mult,double binmin, double binmax,double binminy, double binmaxy,TString vno){
TString iselec;
iselec +=(ise);

TFile *data = TFile::Open("25ns_data_D_uev_newlist_2110_fromskimmed_isElec_"+iselec+vno+".root");
TFile *mc_s = TFile::Open("25ns_tt_uev_miniaodv2_2110_fromskimmed_isElec_"+iselec+vno+".root");
TH1D * tmphdata  =(TH1D*)(data->Get(var +"_0"));
TH1D * tmphmc_s  =(TH1D*)(mc_s->Get(var +"_0"));
TH1D* hdata= (TH1D*)tmphdata->Clone("");
TH1D* hmc_s= (TH1D*)tmphmc_s->Clone("");

TH1D * tmphdata2  =(TH1D*)(data->Get(var2 +"_0"));
TH1D * tmphmc_s2  =(TH1D*)(mc_s->Get(var2 +"_0"));
TH1D* hdata2= (TH1D*)tmphdata2->Clone("");
TH1D* hmc_s2= (TH1D*)tmphmc_s2->Clone("");

TH1D * tmphdata3  =(TH1D*)(data->Get(var3 +"_0"));
TH1D * tmphmc_s3  =(TH1D*)(mc_s->Get(var3 +"_0"));
TH1D* hdata3= (TH1D*)tmphdata3->Clone("");
TH1D* hmc_s3= (TH1D*)tmphmc_s3->Clone("");

TH1D * tmphdata4  =(TH1D*)(data->Get(var4 +"_0"));
TH1D * tmphmc_s4  =(TH1D*)(mc_s->Get(var4 +"_0"));
TH1D* hdata4= (TH1D*)tmphdata4->Clone("");
TH1D* hmc_s4= (TH1D*)tmphmc_s4->Clone("");

 hdata->Rebin(rebin);
 hmc_s->Rebin(rebin);

 hdata2->Rebin(rebin);
 hmc_s2->Rebin(rebin);

 hdata3->Rebin(rebin);
 hmc_s3->Rebin(rebin);

 hdata4->Rebin(rebin);
 hmc_s4->Rebin(rebin);

//cout<<hdata->Integral()<<"  "<<hdata2->Integral()<<hdata3->Integral()<<"  "<<hdata4->Integral()<<endl;

 hdata2->Scale(1/hdata2->Integral());
 hmc_s2->Scale(1/hmc_s2->Integral());

 hdata3->Scale(1/hdata3->Integral());
 hmc_s3->Scale(1/hmc_s3->Integral());

 hdata4->Scale(1/hdata4->Integral());
 hmc_s4->Scale(1/hmc_s4->Integral());

 hdata->Scale(1/hdata->Integral());
 hmc_s->Scale(1/hmc_s->Integral());


 hdata->SetMarkerStyle(20);

 hdata2->SetMarkerStyle(21);
 //hmc_s2->SetMarkerStyle;
 hdata2->SetLineColor(kBlue);
 hmc_s2->SetLineColor(kBlue);
 hdata2->SetMarkerColor(kBlue);


 hdata3->SetMarkerStyle(22);
 //hmc_s3->Rebin(rebin);
 hdata3->SetLineColor(kRed);
 hmc_s3->SetLineColor(kRed);
 hdata3->SetMarkerColor(kRed);


 hdata4->SetMarkerStyle(23);
 hdata4->SetLineColor(kGreen);
 hmc_s4->SetLineColor(kGreen);
 hdata4->SetMarkerColor(kGreen);
 //hmc_s3->Rebin(rebin);

//TLegend *leg1 = new TLegend(0.3931567,0.653719,0.64980511,0.885385);
TLegend *leg1 = new TLegend(0.4553,0.963-0.4180,0.9400,0.933-0.160);
leg1->SetBorderSize(0);
leg1->SetFillColor(kWhite);
leg1->SetTextSize(0.031);
//leg1->AddEntry(hdata, "t#bar{t}","");
leg1->AddEntry(hdata, "overall","pe");
leg1->AddEntry(hdata2, "away","pe");
leg1->AddEntry(hdata3, "transverse","pe");
leg1->AddEntry(hdata4, "toward","pe");
leg1->AddEntry(hmc_s, "t#bar{t} Powheg + Pythia 8 (CUETP8M1)","l");

hdata->SetMarkerStyle(20);

TH1D* monta = (TH1D*)hdata->Clone();
TH1D* mont = (TH1D*)hmc_s->Clone();
mont->Divide(mont,monta,1,1);

TH1D* monta2 = (TH1D*)hdata2->Clone();
TH1D* mont2 = (TH1D*)hmc_s2->Clone();
mont2->Divide(mont2,monta2,1,1);
 mont2->SetMarkerStyle(21);
 mont2->SetMarkerColor(kBlue);
TH1D* monta3 = (TH1D*)hdata3->Clone();
TH1D* mont3 = (TH1D*)hmc_s3->Clone();
mont3->Divide(mont3,monta3,1,1);
 mont3->SetMarkerStyle(22);
 mont3->SetMarkerColor(kRed);
TH1D* monta4 = (TH1D*)hdata4->Clone();
TH1D* mont4 = (TH1D*)hmc_s4->Clone();
mont4->Divide(mont4,monta4,1,1);
 mont4->SetMarkerStyle(23);
 mont4->SetMarkerColor(kGreen);


    TGraphErrors *gr[4];
gr[0] =  new TGraphErrors(mont);
gr[1] =  new TGraphErrors(mont2);
gr[2] =  new TGraphErrors(mont3);
gr[3] =  new TGraphErrors(mont4);


//double *x0[100];
  x0 = gr[0]->GetX();
   x1 = gr[1]->GetX();
   x2 = gr[2]->GetX();
   x3 = gr[3]->GetX();


   for ( is=0;is<hmc_s->GetNbinsX();is++){ 
    double binwidth = hmc_s->GetXaxis()->GetBinWidth(is+1);
     x0[is]=x0[is]-binwidth/3.5;//10.
     x1[is]=x1[is]-binwidth/10.5;//15.
     x2[is]=x2[is]+binwidth/10.5;//20.
     x3[is]=x3[is]+binwidth/3.5;//15.

   cout<<  gr[0]->GetErrorY(is)
     <<"  "<<gr[1]->GetErrorY(is)
      <<"  "<<gr[2]->GetErrorY(is)
      <<"  "<<gr[3]->GetErrorY(is)<<endl;
     gr[0] ->SetPointError(is,0,gr[0]->GetErrorY(is));
     gr[1] ->SetPointError(is,0,gr[1]->GetErrorY(is));
     gr[2] ->SetPointError(is,0,gr[2]->GetErrorY(is));
     gr[3] ->SetPointError(is,0,gr[3]->GetErrorY(is));

   }


//cout<<"burada"<<endl;
TCanvas *c1 = new TCanvas("c1","c1",600,700);
TPaveText *pt = new TPaveText(.09,.925,.70,0.98);
pt->SetFillColor(0);
   pt->SetBorderSize(0);
   pt->SetLineColor(0);

//TString Lumi="";
//Lumi +=(lumi);


/*for(int i=1; i<=hdata->GetNbinsX();i++){
hdata->SetBinError(i,0.0000001);
hmc_s->SetBinError(i,0.000001);
hdata2->SetBinError(i,0.0000001);
hmc_s2->SetBinError(i,0.0000001);
hdata3->SetBinError(i,0.0000001);
hmc_s3->SetBinError(i,0.0000001);
hdata4->SetBinError(i,0.0000001);
hmc_s4->SetBinError(i,0.0000001);
mont->SetBinError(i,0.0000001);
mont2->SetBinError(i,0.0000001);
mont3->SetBinError(i,0.0000001);
mont4->SetBinError(i,0.0000001);
}*/
   pt->AddText("CMS Preliminary #sqrt{s} = 13 TeV, #int L dt = 1.26 fb^{-1} ");

   TLatex *latexLabell = new TLatex(); 

    latexLabell->SetTextSize(0.03305);
    latexLabell->SetTextFont(42);
    latexLabell->SetLineWidth(2);
    latexLabell->SetNDC();

    latexLabell->SetTextFont(61);
//    latexLabell->DrawLatex(0.853,0.963-0.080,"CMS");
    latexLabell->DrawLatex(0.6253,0.963-0.10,"CMS");
    latexLabell->SetTextFont(52);
//    latexLabell->DrawLatex(0.773,0.963-0.120,"Preliminary");
    latexLabell->DrawLatex(0.713,0.963-0.10,"Preliminary");
    latexLabell->SetTextFont(42);
    latexLabell->DrawLatex(0.723,0.963-0.035,"1.26 fb^{-1} (13 TeV)");
   // latexLabell->SetTextSize(0.06305);
   // if(!ise)latexLabell->DrawLatex(0.8123,0.9363-0.160,"t#bar{t}");
    if(ise)latexLabell->DrawLatex(0.673,0.963-0.160,"e + jets, =2 b-tags");


    latexLabell->Draw("same");

          c1->cd(); 
          splithist(0.2);
          c1->cd(1);
          gPad->SetRightMargin(0.04);
          gPad->SetLeftMargin(0.15);
          gPad->SetLogy();  
          if(setlogx)gPad->SetLogx();  
         if(binminy!=-1){
            cout<<binminy<<"  "<<binmaxy<<endl;
            hdata->SetMaximum(binmaxy);
            hdata->SetMinimum(binminy);
          }
  
	  hdata->GetYaxis()->SetLabelSize(0.05);
	  hdata->GetYaxis()->SetTitleSize(0.06);
	  hdata->GetYaxis()->SetTitleOffset(0.89);
 	  hdata->SetYTitle(ytitle);
          double firstbin = hdata->FindFirstBinAbove(0);
          double lastbin = hdata->FindLastBinAbove(0);
          if(binmin==-1)hdata->GetXaxis()->SetRange(firstbin,lastbin);
          else if(binmin!=-1)hdata->GetXaxis()->SetRangeUser(binmin,binmax);
          hdata->Draw("eX0C");
	  hmc_s->Draw("hhistsames");
          hdata2->Draw("eX0Csames");
	  hmc_s2->Draw("hhistsames");
          hdata3->Draw("eX0Csames");
	  hmc_s3->Draw("hhistsames");
          hdata4->Draw("eX0Csames");
	  hmc_s4->Draw("hhistsames");
          leg1->Draw("same");


          c1->cd(2);
                        gPad->SetRightMargin(0.04);
          gPad->SetLeftMargin(0.15);
          gPad->SetBottomMargin(0.35);

          gPad->SetGridy();
 

          //TLine *l=new TLine(fbnn,1.0,lbnn,1.0);
          // l->SetLineColor(kBlue);
          if(binmin==-1)mont->GetXaxis()->SetRange(firstbin,lastbin);
          else if(binmin!=-1) mont->GetXaxis()->SetRangeUser(binmin,binmax);
          mont->GetXaxis()->SetTitleSize(0.3);
          mont->SetMarkerStyle(0);
          mont->SetLineColor(0);
          gr[0]->SetMarkerStyle(20);
          mont->Draw("p");
        //  mont2->Draw("eX0Csames");
        //  mont3->Draw("eX0Csames");
        //  mont4->Draw("eX0Csames");
          for(int iss =0;iss<4;iss++)gr[iss]->Draw("p");         
           //l->Draw("same");
          mont->SetXTitle(xtitle);
          mont->SetMinimum(0.5);
          mont->SetMaximum(1.5);
          mont->SetYTitle("MC/Data");
          fixsplithist(hdata,mont);
          TString a;
          a+=setlog;
          c1->Print("stack_plots_25ns_uev"+vno + "/overlay_" + var +"_logy_" + a + "_iselec_" + iselec+ ".pdf");
          c1->Print("stack_plots_25ns_uev"+vno + "/overlay_" + var +"_logy_" + a + "_iselec_" + iselec+ ".png");
          c1->Print("stack_plots_25ns_uev"+vno + "/overlay_" + var +"_logy_" + a + "_iselec_" + iselec+ ".root");
c1->Close();
data->Close();
mc_s->Close();

delete data;
delete mc_s;





}
void plot_stack_profile(TString var, TString xtitle, TString ytitle, int setlog,int setlogx, int rebin, double lumi,TLatex * latexlab,int ise, TString mult,double binmin, double binmax,double binminy, double binmaxy,TString vno){
TString iselec;
iselec +=(ise);


TFile *data = TFile::Open("25ns_data_D_uev_newlist_2110_fromskimmed_isElec_"+iselec+vno+".root");
TFile *mc_s = TFile::Open("25ns_tt_uev_miniaodv2_2110_fromskimmed_isElec_"+iselec+vno+".root");
TFile *mc_sup = TFile::Open("powheg_up_isElec_"+iselec+vno+".root");
TFile *mc_sdn = TFile::Open("powheg_sdn_isElec_"+iselec+vno+".root");
TFile *mc_hpp = TFile::Open("powheg_hpp_isElec_"+iselec+vno+".root");
TProfile * tmphdata  =(TProfile*)(data->Get(var +"_0"));
TProfile * tmphmc_s  =(TProfile*)(mc_s->Get(var +"_0"));
TProfile * tmphmc_sup  =(TProfile*)(mc_sup->Get(var +"_0"));
TProfile * tmphmc_sdn  =(TProfile*)(mc_sdn->Get(var +"_0"));
TProfile * tmphmc_hpp  =(TProfile*)(mc_hpp->Get(var +"_0"));
TProfile* hdata= (TProfile*)tmphdata->Clone("");
TProfile* hmc_s= (TProfile*)tmphmc_s->Clone("");
TProfile* hmc_sup= (TProfile*)tmphmc_sup->Clone("");
TProfile* hmc_sdn= (TProfile*)tmphmc_sdn->Clone("");
TProfile* hmc_hpp= (TProfile*)tmphmc_hpp->Clone("");
 hdata->Rebin(rebin);
 hmc_s->Rebin(rebin);
 hmc_sup->Rebin(rebin);
 hmc_sdn->Rebin(rebin);
 hmc_hpp->Rebin(rebin);


TH1D* pdfvar = (TH1D*) estimate_pdfunc_profile(var,xtitle,ytitle,setlog,setlogx,ise,"_v15",rebin);
//pdfvar->Rebin(rebin);
TH1D* jesvar = (TH1D*) estimate_jesunc_profile(var,xtitle,ytitle,setlog,setlogx,ise,"_v15",rebin);

TH1D* puvar = (TH1D*) estimate_puunc_profile(var,xtitle,ytitle,setlog,setlogx,ise,"_v15",rebin);

TH1D* pdfvarmont;
TH1D* jesvarmont;
TH1D* puvarmont;
// = (TH1D*) estimate_pdfunc_profile(var,ise,"_v15");
//pdfvarmont->Rebin(rebin);



TLegend *leg1 = new TLegend(0.15931567,0.5263719,0.80980511,0.78575385);
leg1->SetBorderSize(0);
leg1->SetFillColor(kWhite);
leg1->SetFillStyle(0);
leg1->SetTextSize(0.04);
leg1->AddEntry(hdata, "uncorrected data","pe");
leg1->AddEntry(hmc_s, "t#bar{t} Powheg + Pythia 8 (CUETP8M1)","l");
leg1->AddEntry(hmc_sup, "t#bar{t} Powheg + Pythia 8 (CUETP8M1) (2Q)^{2}","l");
leg1->AddEntry(hmc_sdn, "t#bar{t} Powheg + Pythia 8 (CUETP8M1) (Q/2)^{2}","l");
leg1->AddEntry(hmc_hpp, "t#bar{t} Powheg + Herwig++ (EE5C) ","l");

hdata->SetMarkerStyle(20);

hmc_sup->SetLineStyle(9);
hmc_sdn->SetLineStyle(10);
hmc_hpp->SetLineStyle(3);
hdata->SetLineColor(kBlack);
hmc_s->SetLineColor(kBlack);
hmc_sup->SetLineColor(kAzure+4);
hmc_sdn->SetLineColor(kOrange-3);
hmc_hpp->SetLineColor(kRed+2);


hdata->SetLineWidth(2);
hmc_s->SetLineWidth(2);
hmc_sup->SetLineWidth(2);
hmc_sdn->SetLineWidth(2);
hmc_hpp->SetLineWidth(2);


TProfile* montt = (TProfile*)hdata->Clone();
TProfile* monttt = (TProfile*)hmc_s->Clone();
TH1D* monta = (TH1D*)montt->ProjectionX();
TH1D* mont = (TH1D*)monttt->ProjectionX();
mont->Divide(mont,monta,1,1);

TProfile* montttsup = (TProfile*)hmc_sup->Clone();
TProfile* montttsdn = (TProfile*)hmc_sdn->Clone();
TProfile* monttthpp = (TProfile*)hmc_hpp->Clone();
TH1D* montasup = (TH1D*)montt->ProjectionX();
TH1D* montsup = (TH1D*)montttsup->ProjectionX();

TH1D* montasdn = (TH1D*)montt->ProjectionX();
TH1D* montsdn = (TH1D*)montttsdn->ProjectionX();

TH1D* montahpp = (TH1D*)montt->ProjectionX();
TH1D* monthpp = (TH1D*)monttthpp->ProjectionX();


montsup->Divide(montsup,montasup,1,1);
montsdn->Divide(montsdn,montasdn,1,1);
monthpp->Divide(monthpp,montahpp,1,1);

TH1D* hband=(TH1D*)montasup->Clone("hband");
TH1D* hbandd=(TH1D*)montasup->Clone("hband");

TH1D*pdfvarr= (TH1D*)montasup->Clone("pdfvarr");
TH1D*pdfvarrmont= (TH1D*)montasup->Clone("pdfvarrmont");

TH1D*jesvarr= (TH1D*)montasup->Clone("jesvarr");
TH1D*jesvarrmont= (TH1D*)montasup->Clone("jesvarrmont");

TH1D*puvarr= (TH1D*)montasup->Clone("puvarr");
TH1D*puvarrmont= (TH1D*)montasup->Clone("puvarrmont");

TH1D*totvarr= (TH1D*)montasup->Clone("totvarr");
TH1D*totvarrmont= (TH1D*)montasup->Clone("totvarrmont");


for(int i =1 ;i<=hband->GetNbinsX();i++){

hband->SetBinContent(i,(montasdn->GetBinContent(i)+montasup->GetBinContent(i))/2);
hband->SetBinError(i,fabs((montasdn->GetBinContent(i)-montasup->GetBinContent(i))/2));

hbandd->SetBinContent(i,(montsdn->GetBinContent(i)+montsup->GetBinContent(i))/2);
hbandd->SetBinError(i,fabs((montsdn->GetBinContent(i)-montsup->GetBinContent(i))/2));

pdfvarr->SetBinContent(i,hmc_s->GetBinContent(i));
puvarr->SetBinContent(i,hmc_s->GetBinContent(i));
jesvarr->SetBinContent(i,hmc_s->GetBinContent(i));
totvarr->SetBinContent(i,hmc_s->GetBinContent(i));

pdfvarrmont->SetBinContent(i,mont->GetBinContent(i));
puvarrmont->SetBinContent(i,mont->GetBinContent(i));
jesvarrmont->SetBinContent(i,mont->GetBinContent(i));
totvarrmont->SetBinContent(i,mont->GetBinContent(i));


pdfvarr->SetBinError(i,pdfvar->GetBinError(i));
puvarr->SetBinError(i,puvar->GetBinError(i));
jesvarr->SetBinError(i,jesvar->GetBinError(i));

double asdeeee=sqrt(jesvar->GetBinError(i)*jesvar->GetBinError(i) + pdfvarr->GetBinError(i)*pdfvarr->GetBinError(i) + puvarr->GetBinError(i) *puvarr->GetBinError(i));
totvarr->SetBinError(i,asdeeee);
/*
pdfvarrmont->SetBinError(i,fabs(mont->GetBinContent(i)*(pdfvar->GetBinError(i))/(hmc_s->GetBinContent(i)+pdfvar->GetBinError(i))));
puvarrmont->SetBinError(i,fabs(mont->GetBinContent(i)*(puvar->GetBinError(i))/(hmc_s->GetBinContent(i)+puvar->GetBinError(i))));
jesvarrmont->SetBinError(i,fabs(mont->GetBinContent(i)*(jesvar->GetBinError(i))/(hmc_s->GetBinContent(i)+jesvar->GetBinError(i))));

totvarrmont->SetBinError(i,fabs(mont->GetBinContent(i)*(totvarr->GetBinError(i))/(hmc_s->GetBinContent(i)+totvarr->GetBinError(i))));
*/

pdfvarrmont->SetBinError(i,fabs(pdfvar->GetBinError(i)/hdata->GetBinContent(i)));
puvarrmont->SetBinError(i,fabs(puvar->GetBinError(i)/hdata->GetBinContent(i)));
jesvarrmont->SetBinError(i,fabs(jesvar->GetBinError(i)/hdata->GetBinContent(i)));

totvarrmont->SetBinError(i,fabs(totvarr->GetBinError(i)/hdata->GetBinContent(i)));


//cout<<"aaaaaa "<<hmc_s->GetBinContent(i)<<"  "<<pdfvarr->GetBinError(i)<<"  "<<jesvarr->GetBinError(i)<<"  "<<  puvarr->GetBinError(i)<<"  "<<totvarr->GetBinError(i)<<endl;


//cout<<"aaaaaa "<<mont->GetBinContent(i)<<"  "<<pdfvarrmont->GetBinError(i)<<"  "<<jesvarrmont->GetBinError(i)<<"  "<<  puvarrmont->GetBinError(i)<<"  "<<totvarrmont->GetBinError(i)<<endl;


//cout<<"  "<<hmc_s->GetBinContent(i)<<"  "<<pdfvarr->GetBinContent(i)<<" "<<pdfvarr->GetBinError(i)<<endl;
//cout<<pdfvarrmont->GetBinContent(i)<<" "<<pdfvarrmont->GetBinError(i)<<endl;


////cout<<pdfvarr->GetXaxis()->GetBinWidth(i)<<"  "<<mont->GetXaxis()->GetBinWidth(i)<<endl;

}

totvarr->SetFillStyle(3204);
totvarr->SetFillColor(kBlack);
totvarrmont->SetFillStyle(3204);
totvarrmont->SetFillColor(kBlack);
hband->SetFillColorAlpha(kGray,0.5);
hbandd->SetFillColorAlpha(kGray,0.5);

pdfvarr->SetFillColorAlpha(kGray,0.5);
pdfvarrmont->SetFillColorAlpha(kGray,0.5);



puvarr->SetFillColorAlpha(kGreen,0.5);
puvarrmont->SetFillColorAlpha(kGreen,0.5);

jesvarr->SetFillColorAlpha(kYellow,0.5);
jesvarrmont->SetFillColorAlpha(kYellow,0.5);

montsup->SetLineStyle(9);
montsdn->SetLineStyle(10);
monthpp->SetLineStyle(3);

mont->SetLineColor(kBlack);
montsup->SetLineColor(kAzure+4);
montsdn->SetLineColor(kOrange-3);
monthpp->SetLineColor(kRed+2);

mont->SetLineWidth(2);
montsup->SetLineWidth(2);
montsdn->SetLineWidth(2);
monthpp->SetLineWidth(2);


//cout<<"burada"<<endl;
TCanvas *c1 = new TCanvas("c1","c1",600,700);
TPaveText *pt = new TPaveText(.09,.925,.70,0.98);
pt->SetFillColor(0);
   pt->SetBorderSize(0);
   pt->SetLineColor(0);

//TString Lumi="";
//Lumi +=(lumi);

   pt->AddText("CMS Preliminary #sqrt{s} = 13 TeV, #int L dt = 1.26 fb^{-1} ");

   TLatex *latexLabell = new TLatex(); 

    latexLabell->SetTextSize(0.03305);
    latexLabell->SetTextFont(42);
    latexLabell->SetLineWidth(2);
    latexLabell->SetNDC();

    latexLabell->SetTextFont(61);
 //    latexLabell->DrawLatex(0.853,0.963-0.080,"CMS");
    latexLabell->DrawLatex(0.6253,0.963-0.10,"CMS");
    latexLabell->SetTextFont(52);
//    latexLabell->DrawLatex(0.773,0.963-0.120,"Preliminary");
    latexLabell->DrawLatex(0.713,0.963-0.10,"Preliminary");
    latexLabell->SetTextFont(42);
    latexLabell->DrawLatex(0.723,0.963-0.035,"1.26 fb^{-1} (13 TeV)");
   // latexLabell->SetTextSize(0.06305);
   // if(!ise)latexLabell->DrawLatex(0.8123,0.9363-0.160,"t#bar{t}");
    if(ise)latexLabell->DrawLatex(0.673,0.963-0.160,"e + jets, =2 b-tags");
    latexLabell->Draw("same");

          c1->cd(); 
          splithist(0.2);
          c1->cd(1);
          gPad->SetRightMargin(0.04);
          gPad->SetLeftMargin(0.15);

         // if(setlog)gPad->SetLogy();  
         // hdata->SetMinimum(0.1);
          //if(!setlog)hdata->SetMaximum(max+4);
          if(binminy!=-1){
            cout<<binminy<<"  "<<binmaxy<<endl;
            hdata->SetMaximum(binmaxy);
            hdata->SetMinimum(binminy);
          }
          if(setlogx)gPad->SetLogx();  
	  hdata->GetYaxis()->SetLabelSize(0.05);
	  hdata->GetYaxis()->SetTitleSize(0.06);
	  hdata->GetYaxis()->SetTitleOffset(0.89);
 	  hdata->SetYTitle(ytitle);
          double firstbin = hdata->FindFirstBinAbove(0);
          double lastbin = hdata->FindLastBinAbove(0);
          if(binmin==-1)hdata->GetXaxis()->SetRange(firstbin,lastbin);
          else if(binmin!=-1)hdata->GetXaxis()->SetRangeUser(binmin,binmax);
          hdata->Draw("eX0C");
          //hband->Draw("e2sames");
          hdata->Draw("eX0Csames");
	  hmc_s->Draw("hhistsames");
	  hmc_sup->Draw("hhistsames");
	  hmc_sdn->Draw("hhistsames");
	  hmc_hpp->Draw("hhistsames");
//pdfvarr->Draw("e2sames");
//jesvarr->Draw("e2sames");
//puvarr->Draw("e2sames");
//totvarr->Draw("e2sames");
          hdata->Draw("eX0Csames");
	  hmc_s->Draw("hhistsames");
	  hmc_sup->Draw("hhistsames");
	  hmc_sdn->Draw("hhistsames");
	  hmc_hpp->Draw("hhistsames");

          hdata->Draw("eX0Csames");
//	  leg1->AddEntry(pdfvarr,"PDF unc","F");
//	  leg1->AddEntry(jesvarr,"JES unc","F");
//	  leg1->AddEntry(puvarr,"PU unc","F");
          leg1->AddEntry(hmc_s, mult,"");
          leg1->Draw("same");


          c1->cd(2);
              
          if(setlogx)gPad->SetLogx();  
        gPad->SetGridy();
          gPad->SetRightMargin(0.04);
          gPad->SetLeftMargin(0.15);
          gPad->SetBottomMargin(0.40);
   if(setlogx) mont->GetXaxis()->SetMoreLogLabels();
  if(setlogx) mont->GetXaxis()->SetNoExponent();

          //TLine *l=new TLine(fbnn,1.0,lbnn,1.0);
          // l->SetLineColor(kBlue);
          if(binmin==-1)mont->GetXaxis()->SetRange(firstbin,lastbin);
          else if(binmin!=-1) mont->GetXaxis()->SetRangeUser(binmin,binmax);
          mont->GetXaxis()->SetTitleSize(0.15);
          mont->SetMarkerStyle(20);
          mont->Draw("hhistsames");
         // hbandd->Draw("e2sames");
//pdfvarrmont->Draw("e2sames");
//jesvarrmont->Draw("e2sames");
//puvarrmont->Draw("e2sames");
//totvarrmont->Draw("e2sames");
          mont->Draw("hhistsames");
          montsup->Draw("hhistsames");
          montsdn->Draw("hhistsames");
          monthpp->Draw("hhistsames");
          //l->Draw("same");
          mont->SetXTitle(xtitle);
          mont->SetMinimum(0.69);
          mont->SetMaximum(1.31);
          mont->SetYTitle("MC/Data");
          fixsplithist(hdata,mont);
          TString a;
          a+=setlog;
          c1->Print("stack_plots_25ns_uev"+vno + "/profile_" + var +"_logy_" + a + "_iselec_" + iselec+ ".pdf");
          c1->Print("stack_plots_25ns_uev"+vno + "/profile_" + var +"_logy_" + a + "_iselec_" + iselec+ ".png");
          c1->Print("stack_plots_25ns_uev"+vno + "/profile_" + var +"_logy_" + a + "_iselec_" + iselec+ ".root");

c1->Close();
data->Close();
mc_s->Close();
mc_sup->Close();
mc_sdn->Close();
mc_hpp->Close();


delete data;
delete mc_s;
delete mc_sup;
delete mc_sdn;
delete mc_hpp;




}







void plot_stack(TString var, TString xtitle, int setlog,int setlogx, int rebin, double lumi,TLatex * latexlab,int ise,double binmin, double binmax,double binminy, double binmaxy,TString vno){
TString ytitle="#Events/bin width";
TString iselec;
iselec +=(ise);
//cout<<"111"<<endl;

TFile *data = TFile::Open("25ns_data_D_uev_newlist_2110_fromskimmed_isElec_"+iselec+vno+".root");
TFile *mc_s = TFile::Open("25ns_tt_uev_miniaodv2_2110_fromskimmed_isElec_"+iselec+vno+".root");
TFile *mc_sup = TFile::Open("powheg_up_isElec_"+iselec+vno+".root");
TFile *mc_sdn = TFile::Open("powheg_sdn_isElec_"+iselec+vno+".root");
//TFile *mc_o = TFile::Open("mc_signal_25ns_uev_ttother_fromskimmed_isElec_"+iselec+vno+".root");
TFile *st_tw_t = TFile::Open("25ns_st_tw_top_uev_2110_fromskimmed_isElec_"+iselec+vno+".root");
TFile *st_tw_tbar = TFile::Open("25ns_st_tw_atop_uev_2110_fromskimmed_isElec_"+iselec+vno+".root");
TFile *st_t_t = TFile::Open("25ns_st_t_top_uev_2110_fromskimmed_isElec_"+iselec+vno+".root");
TFile *st_t_tbar = TFile::Open("25ns_st_t_atop_uev_2110_fromskimmed_isElec_"+iselec+vno+".root");
TFile *wjet = TFile::Open("25ns_wjet_uev_miniaodv2_2110_fromskimmed_isElec_"+iselec+vno+".root");
//cout<<"222"<<endl;
TH1 * tmphdata  =(TH1D*)(data->Get(var +"_0"));
TH1 * tmphmc_s  =(TH1D*)(mc_s->Get(var +"_0"));
//TH1 * tmphmc_o  =(TH1D*)(mc_o->Get(var +"_0"));
TH1 * tmphst_t_t  =(TH1D*)(st_t_t->Get(var +"_0"));
TH1 * tmphst_t_tbar  =(TH1D*)(st_t_tbar->Get(var +"_0"));
TH1 * tmphst_tw_t  =(TH1D*)(st_tw_t->Get(var +"_0"));
TH1 * tmphst_tw_tbar  =(TH1D*)(st_tw_tbar->Get(var +"_0"));
TH1 * tmphwjet  =(TH1D*)(wjet->Get(var +"_0"));

TH1 * tmphmc_sup  =(TH1D*)(mc_sup->Get(var +"_0"));
TH1 * tmphmc_sdn  =(TH1D*)(mc_sdn->Get(var +"_0"));


TH1D* hdata= (TH1D*)tmphdata->Clone("");
TH1D* hmc_s= (TH1D*)tmphmc_s->Clone("");
TH1D* hmc_sup= (TH1D*)tmphmc_sup->Clone("");
TH1D* hmc_sdn= (TH1D*)tmphmc_sdn->Clone("");
//TH1D* hmc_o = (TH1D*)tmphmc_o->Clone("");
TH1D* hst_t_t= (TH1D*)tmphst_t_t->Clone("");
TH1D* hst_t_tbar = (TH1D*)tmphst_t_tbar->Clone("");
TH1D* hst_tw_t = (TH1D*)tmphst_tw_t->Clone("");
TH1D* hst_tw_tbar = (TH1D*)tmphst_tw_tbar->Clone("");
TH1D* hwjet = (TH1D*)tmphwjet->Clone("");
//cout<<"333"<<endl;

TH1D*pdfvar= (TH1D*) estimate_pdfunc_TH1(var,xtitle,ytitle,setlog,setlogx, ise, "_v15",rebin);
TH1D* jesvar = (TH1D*) estimate_jesunc_TH1(var,xtitle,ytitle,setlog,setlogx,ise,"_v15",rebin);
TH1D* puvar = (TH1D*) estimate_puunc_TH1(var,xtitle,ytitle,setlog,setlogx,ise,"_v15",rebin);
//pdfvar->Rebin(rebin);
//jesvar->Rebin(rebin);
//puvar->Rebin(rebin);

 hdata->Rebin(rebin);
 hmc_s->Rebin(rebin);
 hmc_sup->Rebin(rebin);
 hmc_sdn->Rebin(rebin);
 //hmc_o->Rebin(rebin);
 hst_t_t->Rebin(rebin);
 hst_t_tbar->Rebin(rebin);
 hst_tw_t->Rebin(rebin);
 hst_tw_tbar->Rebin(rebin);
 hwjet->Rebin(rebin);
//cout<<"444"<<endl;
TTree *tmc_s = (TTree *)mc_s->Get("tree");
double wmc_s;

tmc_s->SetBranchAddress("wtot",&wmc_s);
tmc_s->GetEntry(0);


TTree *tmc_sup = (TTree *)mc_sup->Get("tree");
double wmc_sup;

tmc_sup->SetBranchAddress("wtot",&wmc_sup);
tmc_sup->GetEntry(0);


TTree *tmc_sdn = (TTree *)mc_sdn->Get("tree");
double wmc_sdn;

tmc_sdn->SetBranchAddress("wtot",&wmc_sdn);
tmc_sdn->GetEntry(0);


/*TTree *tmc_o = (TTree *)mc_o->Get("tree");
double wmc_o;
//cout<<"555"<<endl;
tmc_o->SetBranchAddress("wtot",&wmc_o);
tmc_o->GetEntry(0);
*/
TTree *tst_t_t = (TTree *)st_t_t->Get("tree");
double wst_t_t;
tst_t_t->SetBranchAddress("wtot",&wst_t_t);
tst_t_t->GetEntry(0);

TTree *tst_t_tbar = (TTree *)st_t_tbar->Get("tree");
double wst_t_tbar;
tst_t_tbar->SetBranchAddress("wtot",&wst_t_tbar);
tst_t_tbar->GetEntry(0);

TTree *tst_tw_t = (TTree *)st_tw_t->Get("tree");
double wst_tw_t;
tst_tw_t->SetBranchAddress("wtot",&wst_tw_t);
tst_tw_t->GetEntry(0);


TTree *tst_tw_tbar = (TTree *)st_tw_tbar->Get("tree");
double wst_tw_tbar;
tst_tw_tbar->SetBranchAddress("wtot",&wst_tw_tbar);
tst_tw_tbar->GetEntry(0);

TTree *twjet = (TTree *)wjet->Get("tree");
double wwjet;
twjet->SetBranchAddress("wtot",&wwjet);
twjet->GetEntry(0);

////cout<<wmc_s<<"  "<<wmc_o<<"  "<<wst_t_t<<"  "<<wst_t_tbar<<"  "<<wwjet<<endl;

hmc_s->Scale(831.76*lumi/wmc_s);
hmc_sup->Scale(831.76*lumi/wmc_sup);
hmc_sdn->Scale(831.76*lumi/wmc_sdn);

pdfvar->Scale(831.76*lumi/wmc_s);
//jesvar->Scale(831.76*lumi/wmc_s);
puvar->Scale(831.76*lumi/wmc_s);

//hmc_o->Scale(831.76*lumi/wmc_o);
hst_t_t->Scale(136.02*lumi/wst_t_t);
hst_t_tbar->Scale(80.95*lumi/wst_t_tbar);
hst_tw_t->Scale(35.85*lumi/wst_tw_t);
hst_tw_tbar->Scale(35.85*lumi/wst_tw_tbar);
hwjet->Scale(3* 20508.9*lumi /wwjet);






for(int i=1; i<=hdata->GetNbinsX();i++){
hdata->SetBinContent(i,hdata->GetBinContent(i)/hdata->GetBinWidth(i));
hmc_s->SetBinContent(i,hmc_s->GetBinContent(i)/hmc_s->GetBinWidth(i));
hmc_sup->SetBinContent(i,hmc_sup->GetBinContent(i)/hmc_sup->GetBinWidth(i));
hmc_sdn->SetBinContent(i,hmc_sdn->GetBinContent(i)/hmc_sdn->GetBinWidth(i));
hst_t_t->SetBinContent(i,hst_t_t->GetBinContent(i)/hst_t_t->GetBinWidth(i));
hst_t_tbar->SetBinContent(i,hst_t_tbar->GetBinContent(i)/hst_t_tbar->GetBinWidth(i));
hst_tw_t->SetBinContent(i,hst_tw_t->GetBinContent(i)/hst_tw_t->GetBinWidth(i));
hst_tw_tbar->SetBinContent(i,hst_tw_tbar->GetBinContent(i)/hst_tw_tbar->GetBinWidth(i));
hwjet->SetBinContent(i,hwjet->GetBinContent(i)/hwjet->GetBinWidth(i));

hdata->SetBinError(i,hdata->GetBinError(i)/hdata->GetBinWidth(i));
hmc_s->SetBinError(i,hmc_s->GetBinError(i)/hmc_s->GetBinWidth(i));
hmc_sup->SetBinError(i,hmc_sup->GetBinError(i)/hmc_sup->GetBinWidth(i));
hmc_sdn->SetBinError(i,hmc_sdn->GetBinError(i)/hmc_sdn->GetBinWidth(i));
hst_t_t->SetBinError(i,hst_t_t->GetBinError(i)/hst_t_t->GetBinWidth(i));
hst_t_tbar->SetBinError(i,hst_t_tbar->GetBinError(i)/hst_t_tbar->GetBinWidth(i));
hst_tw_t->SetBinError(i,hst_tw_t->GetBinError(i)/hst_tw_t->GetBinWidth(i));
hst_tw_tbar->SetBinError(i,hst_tw_tbar->GetBinError(i)/hst_tw_tbar->GetBinWidth(i));
hwjet->SetBinError(i,hwjet->GetBinError(i)/hwjet->GetBinWidth(i));

}



TH1* stackmc= (TH1D*)hmc_s->Clone("stackmc");
//stackmc->Add(hmc_o);
stackmc->Add(hst_t_t);
stackmc->Add(hst_t_tbar);
stackmc->Add(hst_tw_t);
stackmc->Add(hst_tw_tbar);
stackmc->Add(hwjet);
double asd=hdata->Integral()/stackmc->Integral();

cout <<asd<<endl;
asd=1.;
stackmc->Scale(asd);
hst_t_t->Scale(asd);
hst_t_tbar->Scale(asd);
hst_tw_t->Scale(asd);
hst_tw_tbar->Scale(asd);
hwjet->Scale(asd);
hmc_s->Scale(asd);
hmc_sup->Scale(asd);
hmc_sdn->Scale(asd);
//hmc_o->Scale(asd);


hmc_sup->Add(hst_t_t);
hmc_sup->Add(hst_t_tbar);
hmc_sup->Add(hst_tw_t);
hmc_sup->Add(hst_tw_tbar);
hmc_sup->Add(hwjet);

hmc_sdn->Add(hst_t_t);
hmc_sdn->Add(hst_t_tbar);
hmc_sdn->Add(hst_tw_t);
hmc_sdn->Add(hst_tw_tbar);
hmc_sdn->Add(hwjet);






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

//cout<<max<<" "<<h_data_max<<endl;
TH1* stacst= (TH1D*)hst_t_t->Clone("stackst");
stacst->Add(hst_t_tbar);
stacst->Add(hst_tw_t);
stacst->Add(hst_tw_tbar);

//hmc_o->SetFillColor(634);
hmc_s->SetFillColor(633);
stacst->SetFillColor(616);
hwjet->SetFillColor(413);
stackmc->SetFillColor(634);

hmc_sup->SetLineColor(kAzure+4);
hmc_sdn->SetLineColor(kOrange-3);
hmc_sup->SetLineStyle(9);
hmc_sdn->SetLineStyle(10);

TLegend *leg1 = new TLegend(0.7531567,0.453719,0.904980511,0.685385);
leg1->SetBorderSize(0);
leg1->SetFillColor(kWhite);
leg1->SetTextSize(0.04);
leg1->AddEntry(hdata, "data","pe");
leg1->AddEntry(hmc_s, "t#bar{t}","peF");
//leg1->AddEntry(hmc_o, "t#bar{t} other","peF");
leg1->AddEntry(stacst, "single top","peF");
leg1->AddEntry(hwjet, "WJets","peF");
//leg1->AddEntry(hmc_sup, "t#bar{t} (2Q)^{2}","l");
//leg1->AddEntry(hmc_sdn, "t#bar{t} (Q/2)^{2}","l");


hdata->SetMarkerStyle(20);



   THStack *hs = new THStack("hs","Stacked 1D histograms");
hs->Add(hwjet);
hs->Add(stacst);
//hs->Add(hmc_o);
hs->Add(hmc_s);

  hs->SetHistogram(hmc_s);
TH1* mont = (TH1D*)hdata->Clone();
mont->Divide(hdata,stackmc,1,1);


TH1* montup = (TH1D*)hmc_sup->Clone();
montup->Divide(hmc_sup,stackmc,1,1);

TH1* montdn = (TH1D*)hmc_sdn->Clone();
montdn->Divide(hmc_sdn,stackmc,1,1);

montup->SetLineColor(kAzure+4);
montdn->SetLineColor(kOrange-3);
montup->SetLineStyle(9);
montdn->SetLineStyle(10);

montup->SetLineWidth(2);
montdn->SetLineWidth(2);


TH1D*pdfvarr= (TH1D*)hmc_s->Clone("pdfvarr");
TH1D*pdfvarrmont= (TH1D*)hmc_s->Clone("pdfvarrmont");

TH1D*jesvarr= (TH1D*)hmc_s->Clone("jesvarr");
TH1D*jesvarrmont= (TH1D*)hmc_s->Clone("jesvarrmont");

TH1D*puvarr= (TH1D*)hmc_s->Clone("puvarr");
TH1D*puvarrmont= (TH1D*)hmc_s->Clone("puvarrmont");

TH1D*totvarr= (TH1D*)hmc_s->Clone("totvarr");
TH1D*totvarrmont= (TH1D*)hmc_s->Clone("totvarrmont");

for(int i=1; i<=hdata->GetNbinsX();i++){
pdfvarr->SetBinContent(i,stackmc->GetBinContent(i));
jesvarr->SetBinContent(i,stackmc->GetBinContent(i));
puvarr->SetBinContent(i,stackmc->GetBinContent(i));
totvarr->SetBinContent(i,stackmc->GetBinContent(i));



pdfvarrmont->SetBinContent(i,mont->GetBinContent(i));
puvarrmont->SetBinContent(i,mont->GetBinContent(i));
jesvarrmont->SetBinContent(i,mont->GetBinContent(i));
totvarrmont->SetBinContent(i,mont->GetBinContent(i));


pdfvarr->SetBinError(i,pdfvar->GetBinError(i));
puvarr->SetBinError(i,puvar->GetBinError(i));
jesvarr->SetBinError(i,jesvar->GetBinError(i));
//cout<<puvar->GetBinError(i)<<endl;
double asdeeee=sqrt(jesvar->GetBinError(i)*jesvar->GetBinError(i) + pdfvarr->GetBinError(i)*pdfvarr->GetBinError(i) + puvarr->GetBinError(i) *puvarr->GetBinError(i));
totvarr->SetBinError(i,asdeeee);

pdfvarrmont->SetBinError(i,fabs(mont->GetBinContent(i)*(pdfvar->GetBinError(i))/(hmc_s->GetBinContent(i)+pdfvar->GetBinError(i))));
puvarrmont->SetBinError(i,fabs(mont->GetBinContent(i)*(puvar->GetBinError(i))/(hmc_s->GetBinContent(i)+puvar->GetBinError(i))));
jesvarrmont->SetBinError(i,fabs(mont->GetBinContent(i)*(jesvar->GetBinError(i))/(hmc_s->GetBinContent(i)+jesvar->GetBinError(i))));

totvarrmont->SetBinError(i,fabs(mont->GetBinContent(i)*(totvarr->GetBinError(i))/(hmc_s->GetBinContent(i)+totvarr->GetBinError(i))));



}




totvarr->SetFillStyle(3204);
totvarr->SetFillColor(kBlack);
totvarrmont->SetFillStyle(3204);
totvarrmont->SetFillColor(kBlack);


pdfvarr->SetFillColorAlpha(kGray,0.5);
pdfvarrmont->SetFillColorAlpha(kGray,0.5);



puvarr->SetFillColorAlpha(kGreen,0.5);
puvarrmont->SetFillColorAlpha(kGreen,0.5);

jesvarr->SetFillColorAlpha(kYellow,0.5);
jesvarrmont->SetFillColorAlpha(kYellow,0.5);


//cout<<"burada"<<endl;
TCanvas *c1 = new TCanvas("c1","c1",600,700);
TPaveText *pt = new TPaveText(.09,.925,.70,0.98);
pt->SetFillColor(0);
   pt->SetBorderSize(0);
   pt->SetLineColor(0);

//TString Lumi="";
//Lumi +=(lumi);

   pt->AddText("CMS Preliminary #sqrt{s} = 13 TeV, #int L dt = 1.26 fb^{-1} ");

   TLatex *latexLabell = new TLatex(); 

    latexLabell->SetTextSize(0.03305);
    latexLabell->SetTextFont(42);
    latexLabell->SetLineWidth(2);
    latexLabell->SetNDC();

    latexLabell->SetTextFont(61);
    latexLabell->DrawLatex(0.6253,0.963-0.10,"CMS");
    latexLabell->SetTextFont(52);
//    latexLabell->DrawLatex(0.773,0.963-0.120,"Preliminary");
    latexLabell->DrawLatex(0.713,0.963-0.10,"Preliminary");

 //   if(!ise)latexLabell->DrawLatex(0.673,0.963-0.160,"t#bar{t}");
 //   if(ise)latexLabell->DrawLatex(0.673,0.963-0.160,"e + jets, =2 b-tags");
    latexLabell->SetTextFont(42);
 latexLabell->DrawLatex(0.723,0.963-0.035,"1.26 fb^{-1} (13 TeV)");


    latexLabell->Draw("same");

//cout<<"hayır burada"<<endl;

          c1->cd(); 
          splithist(0.2);
          c1->cd(1);
          gPad->SetRightMargin(0.04);
          gPad->SetLeftMargin(0.15);
          if(setlog)gPad->SetLogy();  
          hdata->SetMinimum(0.1);
          if(binminy==-1){
          if(!setlog)hdata->SetMaximum(max+4);
          if(setlog)hdata->SetMaximum(max*4);
          if(!setlog)hdata->SetMinimum(min+4);
          if(setlog)hdata->SetMinimum(min*4);}
          if(binminy!=-1){
          hdata->SetMaximum(binmaxy);
          hdata->SetMinimum(binminy);
          }
          if(setlogx)gPad->SetLogx();  
	  hdata->GetYaxis()->SetLabelSize(0.05);
	  hdata->GetYaxis()->SetTitleSize(0.06);
	  hdata->GetYaxis()->SetTitleOffset(0.89);
 	  hdata->SetYTitle("#Events/bin width");
          double firstbin = hdata->FindFirstBinAbove(0);
          double lastbin = hdata->FindLastBinAbove(0);
         if(binmin==-1) hdata->GetXaxis()->SetRange(firstbin,lastbin);
          else if(binmin!=-1)hdata->GetXaxis()->SetRangeUser(binmin,binmax);
          if(var=="m_thad")hdata->GetXaxis()->SetRange(firstbin+2,lastbin-20);
          hdata->Draw("eX0C");
	  hs->Draw("hhistsames");
          hdata->Draw("eX0Csames");

//	  pdfvarr->Draw("e2sames");
//	  jesvarr->Draw("e2sames");
//	  puvarr->Draw("e2sames");
//	  totvarr->Draw("e2sames");
          hdata->Draw("eX0Csames");
	 // hmc_sup->Draw("hhistsames");
	 // hmc_sdn->Draw("hhistsames");
//	  leg1->AddEntry(pdfvarr,"PDF unc","F");
//	  leg1->AddEntry(jesvarr,"JES unc","F");
//	  leg1->AddEntry(puvarr,"PU unc","F");
          leg1->Draw("same");
/*
	  stackmc->GetYaxis()->SetLabelSize(0.05);
	  stackmc->GetYaxis()->SetTitleSize(0.06);
	  stackmc->GetYaxis()->SetTitleOffset(0.89);
	  stackmc->SetYTitle("#Events/bin width");
	  stackmc->Draw("hhist");
*/

//cout<<"Burada aq"<<endl;
          c1->cd(2);
              gPad->SetGridy();
          gPad->SetRightMargin(0.04);
          gPad->SetLeftMargin(0.15);
          gPad->SetBottomMargin(0.35);
          if(setlogx)gPad->SetLogx();  
           //  double fbnn=	hdata->GetBinCenter(firstbin+2)- hdata->GetBinWidth(firstbin+2)/2;   
           //  double lbnn=	hdata->GetBinCenter(lastbin-20) +hdata->GetBinWidth(lastbin-20)/2; 
 

        //  TLine *l=new TLine(fbnn,1.0,lbnn,1.0);
        //   l->SetLineColor(kBlue);
          if(binmin==-1)mont->GetXaxis()->SetRange(firstbin,lastbin);
          else if(binmin!=-1)mont->GetXaxis()->SetRangeUser(binmin,binmax);
          //if(var=="m_thad")mont->GetXaxis()->SetRange(firstbin+2,lastbin-20);
          mont->GetXaxis()->SetTitleSize(0.3);
          mont->SetMarkerStyle(20);
          mont->Draw("eX0Csames");
//pdfvarrmont->Draw("e2sames");
//jesvarrmont->Draw("e2sames");
//puvarrmont->Draw("e2sames");
//totvarrmont->Draw("e2sames");
          mont->Draw("eX0Csames");
//montup->Draw("hhistsames");
//montdn->Draw("hhistsames");
         // l->Draw("same");
          mont->SetXTitle(xtitle);
          mont->SetMinimum(0.5);
          mont->SetMaximum(1.5);
          mont->SetYTitle("Data/MC");
          fixsplithist(hdata,mont);
          TString a;
          a+=setlog;
          c1->Print("stack_plots_25ns_uev"+vno + "/" + var +"_logy_" + a + "_iselec_" + iselec+ ".pdf");
          c1->Print("stack_plots_25ns_uev"+vno + "/" + var +"_logy_" + a + "_iselec_" + iselec+ ".png");
          c1->Print("stack_plots_25ns_uev"+vno + "/" + var +"_logy_" + a + "_iselec_" + iselec+ ".root");
c1->Close();

data->Close();
mc_s->Close();
mc_sup->Close();
mc_sdn->Close();
st_tw_t->Close();
st_tw_tbar->Close();
st_t_t->Close();
st_t_tbar->Close();
wjet->Close();


delete data;
delete mc_s;
delete mc_sup;
delete mc_sdn;
delete st_tw_t;
delete st_tw_tbar;
delete st_t_t;
delete st_t_tbar;
delete wjet;


}



void macro_uev_plots(){

   gStyle->SetOptStat(kFALSE);
   gStyle->SetOptTitle(kFALSE);
//  double lumii=23.757;
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



int plot_set=2;
if(plot_set==1){


plot_stack("lbjet_eta","#eta(bj_{1})",1,0,10,lumii,latexLabel,ise,-1,-1,2,20000,"_v15");
plot_stack("slbjet_eta","#eta(bj_{2})",1,0,10,lumii,latexLabel,ise,-1,-1,2,20000,"_v15");
plot_stack("csv","CSVv2",1,0,10,lumii,latexLabel,ise,-1,-1,-1,-1,"_v15");
plot_stack("csvmax","CSVv2",1,0,10,lumii,latexLabel,ise,-1,-1,1000,10000000,"_v15");
plot_stack("csvmax2","CSVv2",1,0,10,lumii,latexLabel,ise,-1,-1,-1,-1,"_v15");
plot_stack("dphi_ttbar_pf","#Delta#phi(t#bar{t},ch)",1,0,1,lumii,latexLabel,ise,-1,-1,10,50000,"_v15");
plot_stack("ljet_pt","p_{T}(j_{1}) [GeV]",1,0,1,lumii,latexLabel,ise,30.,300,0.1,1000,"_v15");
plot_stack("ljet_eta","#eta(j_{1})",1,0,4,lumii,latexLabel,ise,-1,-1,10,20000,"_v15");
plot_stack("sljet_pt","p_{T}(j_{2}) [GeV]",1,0,1,lumii,latexLabel,ise,30,200,-1,-1,"_v15");
plot_stack("sljet_eta","#eta(j_{2})",1,0,4,lumii,latexLabel,ise,-1,-1,10,20000,"_v15");

plot_stack("pf_dxy","dxy [cm]",1,0,40,lumii,latexLabel,ise,-1,-1,-1,-1,"_v15");

plot_stack("pf_dz","dz [cm]",1,0,40,lumii,latexLabel,ise,-1,-1,0.1,1000000,"_v15");

plot_stack("pf_sigmadxy","Sdxy",1,0,20,lumii,latexLabel,ise,-1,-1,-1,-1,"_v15");

plot_stack("pf_sigmadz","sdz",1,0,20,lumii,latexLabel,ise,-1,-1,-1,-1,"_v15");

plot_stack("pf_pt","p_{T}^{ch}  [GeV]",1,0,40,lumii,latexLabel,ise,-1,-1,-1,-1,"_v15");




//hist name, x title, setlogy, rebin, lumii, dummy, is electron, binmin, binmax (if  set as -1 getbinabove 0 is used)
plot_stack("mu_pt_meas","p_{T} (#mu) [GeV]",1,0,100,lumii,latexLabel,ise,-1,-1,0.1,1000,"_v15");

plot_stack("met_meas","MET [GeV]",1,0,4,lumii,latexLabel,ise,-1,-1,0.1,700,"_v15");

plot_stack("mu_eta_meas","#eta (#mu)",1,0,10,lumii,latexLabel,ise,-1,-1,1,50000,"_v15");

plot_stack("mu_phi_meas","#phi (#mu)",1,0,4,lumii,latexLabel,ise,-1,-1,50,10000,"_v15");

plot_stack("mu_iso_meas","Iso (#mu)",1,0,20,lumii,latexLabel,ise,0,0.2,-1,-1,"_v15");

plot_stack("n_bjet","N bjet",1,0,1,lumii,latexLabel,ise,-1,-1,-1,-1,"_v15");

plot_stack("lbjet_pt","p_{T}(bj_{1}) [GeV]",1,0,2,lumii,latexLabel,ise,30,300,0.1,200000,"_v15");

plot_stack("slbjet_pt","p_{T}(bj_{2}) [GeV]",1,0,1,lumii,latexLabel,ise,30,200,0.1,200000,"_v15");

plot_stack("dijet_mass","M_{jj} [GeV]",1,0,2,lumii,latexLabel,ise,0,500,0.051,800,"_v15");

plot_stack("dijet_mass_narrow","M_{jj} [GeV]",0,0,40,lumii,latexLabel,ise,-1,-1,0,439.8,"_v15");

plot_stack("pt_ttbar","p_{T}(t#bar{t}) [GeV]",0,0,1,lumii,latexLabel,ise,-1,-1,0,280,"_v15");

plot_stack("pt_ttbar_kinrec","p_{T}(t#bar{t}) [GeV]",0,0,1,lumii,latexLabel,ise,-1,-1,0,280,"_v15");

plot_stack("nu_pz","p_{z}(#nu) [GeV]",0,0,4,lumii,latexLabel,ise,-1,-1,0,100,"_v15");

plot_stack("nu_pt","p_{T}(#nu) [GeV]",0,0,4,lumii,latexLabel,ise,-1,-1,0,200,"_v15");

plot_stack("rec_ttjY","y (t#bar{t}j)",0,0,1,lumii,latexLabel,ise,-1,-1,0,7000,"_v15");



plot_stack("y_ttbar","y (t#bar{t})",0,0,2,lumii,latexLabel,ise,-1,-1,0,9000,"_v15");



plot_stack("m_ttbar","M (t#bar{t}) [GeV]",0,0,1,lumii,latexLabel,ise,-1,-1,0,70,"_v15");

plot_stack("m_thad","M (t_{had}) [GeV]",0,0,1,lumii,latexLabel,ise,-1,-1,0,250,"_v15");

plot_stack("m_tlep","M (t_{lep}) [GeV]",0,0,1,lumii,latexLabel,ise,-1,-1,0,750,"_v15");

plot_stack("pt_thad","p_{T} (t_{had}) [GeV]",0,0,1,lumii,latexLabel,ise,-1,-1,0,100,"_v15");

plot_stack("pt_tlep","p_{T} (t_{lep}) [GeV]",0,0,1,lumii,latexLabel,ise,-1,-1,0,100,"_v15");

plot_stack("m_t","M (t and #bar{t}) [GeV]",0,0,1,lumii,latexLabel,ise,-1,-1,0,750,"_v15");

plot_stack("pt_t","p_{T} (t and #bar{t}) [GeV]",0,0,1,lumii,latexLabel,ise,-1,-1,0,400,"_v15");

plot_stack("m_ttbar_fixbin","M (t#bar{t}) [GeV]",0,0,4,lumii,latexLabel,ise,-1,-1,0,70,"_v15");

plot_stack("m_thad_fixbin","M (t_{had}) [GeV]",0,0,4,lumii,latexLabel,ise,-1,-1,0,250,"_v15");

plot_stack("m_tlep_fixbin","M (t_{lep}) [GeV]",0,0,4,lumii,latexLabel,ise,-1,-1,0,750,"_v15");

plot_stack("pt_thad_fixbin","p_{T} (t_{had}) [GeV]",0,0,4,lumii,latexLabel,ise,-1,-1,0,100,"_v15");

plot_stack("pt_tlep_fixbin","p_{T} (t_{lep}) [GeV]",0,0,4,lumii,latexLabel,ise,-1,-1,0,100,"_v15");

plot_stack("m_t_fixbin","M (t and #bar{t}) [GeV]",0,0,4,lumii,latexLabel,ise,-1,-1,0,750,"_v15");

plot_stack("pt_t_fixbin","p_{T} (t and #bar{t}) [GeV]",0,0,4,lumii,latexLabel,ise,-1,-1,0,400,"_v15");


plot_stack("y_thad","y (t_{had})",0,0,2,lumii,latexLabel,ise,-1,-1,0,9000,"_v15");

plot_stack("y_tlep","y (t_{lep})",0,0,2,lumii,latexLabel,ise,-1,-1,0,9000,"_v15");


plot_stack("y_t","y (t and #bar{t})",0,0,2,lumii,latexLabel,ise,-1,-1,0,20000,"_v15");


plot_stack("njet_ttbar","N_{jet} p_{T}(j)>30 GeV",1,0,1,lumii,latexLabel,ise,4,9,-1,-1,"_v15");

plot_stack("njet_15_ttbar","N_{jet}(extra) p_{T}(j)>15 GeV",1,0,1,lumii,latexLabel,ise,-1,-1,1,10000,"_v15");

plot_stack("deltar_pf_jetpf","#Delta R_{min} (ch,jconst)",1,0,2,lumii,latexLabel,ise,0.,0.1,0.1,10000000,"_v15");

plot_stack("deltar_pf_jet","#Delta R_{min} (ch,j)",1,0,1,lumii,latexLabel,ise,0.,0.1,50,10000000,"_v15");

plot_stack("deltar_pf_jet_after","#Delta R_{min} (ch,j) after DR cut",1,0,1,lumii,latexLabel,ise,0.,0.1,50,10000000,"_v15");

plot_stack("deltar_pf_mu","#Delta R (ch,mu)",1,0,2,lumii,latexLabel,ise,0.,0.1,0.1,10000000,"_v15");

plot_stack("nvtx_npf","N_{vtx}",1,0,1,lumii,latexLabel,ise,-1,-1,-1,-1,"_v15");

plot_stack("npf_inclusive","N^{ch}",1,0,1,lumii,latexLabel,ise,-1,-1,-1,-1,"_v15");

plot_stack("npf_toward","N^{ch}, toward region",1,0,1,lumii,latexLabel,ise,-1,-1,-1,-1,"_v15");

plot_stack("npf_transverse","N^{ch}, transverse region",1,0,1,lumii,latexLabel,ise,-1,-1,-1,-1,"_v15");

plot_stack("npf_away","N^{ch}, away region",1,0,1,lumii,latexLabel,ise,-1,-1,-1,-1,"_v15");

plot_stack("ptsumpf_inclusive","#Sigma p_{T}(ch) [GeV]",1,0,2,lumii,latexLabel,ise,-1,-1,0.01,10000,"_v15");

plot_stack("ptsumpf_toward","#Sigma p_{T}(ch) [GeV] toward region",1,0,1,lumii,latexLabel,ise,-1,-1,-1,-1,"_v15");

plot_stack("ptsumpf_transverse","#Sigma p_{T}(ch) [GeV] transverse region",1,0,1,lumii,latexLabel,ise,-1,-1,-1,-1,"_v15");

plot_stack("ptsumpf_away","#Sigma p_{T}(ch) [GeV] away region",1,0,2,lumii,latexLabel,ise,-1,-1,0.01,10000,"_v15");

plot_stack("ptavepf_inclusive","#bar{p}_{T}^{ch} [GeV]",1,0,1,lumii,latexLabel,ise,-1,-1,-1,-1,"_v15");

plot_stack("ptavepf_toward","#bar{p}_{T}^{ch} [GeV] toward region",1,0,1,lumii,latexLabel,ise,-1,-1,-1,-1,"_v15");

plot_stack("ptavepf_transverse","#bar{p}_{T}^{ch} [GeV] transverse region",1,0,1,lumii,latexLabel,ise,-1,-1,-1,-1,"_v15");

plot_stack("ptavepf_away","#bar{p}_{T}^{ch} [GeV] away region",1,0,1,lumii,latexLabel,ise,-1,-1,-1,-1,"_v15");

plot_stack("njet_bb","n_{extra jet} in bb span",1,0,1,lumii,latexLabel,ise,-1,-1,1,20000,"_v15");


}
if(plot_set==2){
plot_stack_overlay("ptavepf_inclusive","ptavepf_away","ptavepf_transverse","ptavepf_toward","#LT p_{T}^{ch} #GT [GeV]","1/N_{ev} dN_{ev}/d(#LT p_{T}^{ch} #GT) [/GeV]",1,0,5,lumii,latexLabel,ise," ",-1,-1,0.000012,5,"_v15");
plot_stack_overlay("ptsumpf_inclusive","ptsumpf_away","ptsumpf_transverse","ptsumpf_toward","#Sigma p_{T}^{ch} [GeV]","1/N_{ev} dN_{ev}/d#Sigma p_{T}^{ch} [/GeV]",1,0,10,lumii,latexLabel,ise," ",-1,-1,0.000012,5,"_v15");
plot_stack_overlay("npf_inclusive","npf_away","npf_transverse","npf_toward","N^{ch}","1/N_{ev} dN_{ev}/dN^{ch}",1,0,7,lumii,latexLabel,ise," ",-1,-1,0.000012,5,"_v15");



plot_stack_profile("profile_dphi_ptsumpf_0j","#Delta #phi","d (#Sigma p_{T}^{ch}) /d (#Delta #phi) [GeV/9 deg]",1,0,1,lumii,latexLabel,ise," =0 jet",0,179,1,25,"_v15");
plot_stack_profile("profile_dphi_ptaveragepf_0j","#Delta #phi","d (#LT p_{T}^{ch} #GT) /d (#Delta #phi) [GeV/9 deg]",1,0,1,lumii,latexLabel,ise," =0 jet",0,179,1.01,5.51,"_v15");
plot_stack_profile("profile_dphi_npf_0j","#Delta #phi","d (N^{ch})/d (#Delta #phi)[/9 deg]",1,0,1,lumii,latexLabel,ise," =0 jet",0,179,1.01,5.51,"_v15");


plot_stack_profile("profile_dphi_ptsumpf_1j","#Delta #phi","d (#Sigma p_{T}^{ch}) /d (#Delta #phi)[GeV/9 deg]",1,0,1,lumii,latexLabel,ise," =1 jet",0,179,1,25,"_v15");
plot_stack_profile("profile_dphi_ptaveragepf_1j","#Delta #phi","d (#LT p_{T}^{ch} #GT) /d (#Delta #phi)  [GeV/9 deg]",1,0,1,lumii,latexLabel,ise," =1 jet",0,179,1.01,5.51,"_v15");
plot_stack_profile("profile_dphi_npf_1j","#Delta #phi","d (N^{ch})/d (#Delta #phi)[/9 deg]",1,0,1,lumii,latexLabel,ise," =1 jet",0,179,1.01,5.51,"_v15");


plot_stack_profile("profile_dphi_ptsumpf_2pj","#Delta #phi","d (#Sigma p_{T}^{ch}) /d (#Delta #phi)[GeV/9 deg]",1,0,1,lumii,latexLabel,ise," >=2 jets",0,179,1,25,"_v15");
plot_stack_profile("profile_dphi_ptaveragepf_2pj","#Delta #phi","d (#LT p_{T}^{ch} #GT) /d (#Delta #phi) [GeV/9 deg]",1,0,1,lumii,latexLabel,ise," >=2 jets",0,179,1.01,5.51,"_v15");
plot_stack_profile("profile_dphi_npf_2pj","#Delta #phi","d (N^{ch})/d (#Delta #phi)[/9 deg]",1,0,1,lumii,latexLabel,ise," >=2 jets",0,179,1.01,5.51,"_v15");



plot_stack_profile("profile_dphi_ptsumpf","#Delta #phi","d (#Sigma p_{T}^{ch}) /d (#Delta #phi)[GeV/9 deg]",1,0,1,lumii,latexLabel,ise," ",0,179,1,25,"_v15");
plot_stack_profile("profile_dphi_ptaveragepf","#Delta #phi","d (#LT p_{T}^{ch} #GT) /d (#Delta #phi) [GeV/9 deg]",1,0,1,lumii,latexLabel,ise," ",0,179,1.01,5.51,"_v15");
plot_stack_profile("profile_dphi_npf","#Delta #phi","d (N^{ch})/d (#Delta #phi)[/9 deg]",1,0,1,lumii,latexLabel,ise," ",0,179,1.01,5.51,"_v15");



plot_stack_profile("profile_ptttbar_npf","p_{T}^{t#bar{t}} [GeV]","N_{ch} ",1,1,1,lumii,latexLabel,ise," ",-1,-1,2.1,68.1,"_v15");
plot_stack_profile("profile_ptttbar_sumpt","p_{T}^{t#bar{t}} [GeV]","#Sigma p_{T}^{ch} [GeV]",1,1,1,lumii,latexLabel,ise," ",-1,-1,8.01,260.1,"_v15");
plot_stack_profile("profile_ptttbar_avept","p_{T}^{t#bar{t}} [GeV]","#LT p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise," ",-1,-1,1.1,10.1,"_v15");

plot_stack_profile("profile_ptttbar_npf_away","p_{T}^{t#bar{t}} [GeV]","N_{ch} ",1,1,1,lumii,latexLabel,ise,"away",-1,-1,2.1,68.1,"_v15");
plot_stack_profile("profile_ptttbar_sumpt_away","p_{T}^{t#bar{t}} [GeV]","#Sigma p_{T}^{ch} [GeV]",1,1,1,lumii,latexLabel,ise,"away",-1,-1,8.01,260.1,"_v15");
plot_stack_profile("profile_ptttbar_avept_away","p_{T}^{t#bar{t}} [GeV]","#LT p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"away",-1,-1,1.1,10.1,"_v15");

plot_stack_profile("profile_ptttbar_npf_transverse","p_{T}^{t#bar{t}} [GeV]","N_{ch} ",1,1,1,lumii,latexLabel,ise,"transverse",-1,-1,4.1,16.1,"_v15");
plot_stack_profile("profile_ptttbar_sumpt_transverse","p_{T}^{t#bar{t}} [GeV]","#Sigma p_{T}^{ch} [GeV]",1,1,1,lumii,latexLabel,ise,"transverse",-1,-1,7.01,45.1,"_v15");
plot_stack_profile("profile_ptttbar_avept_transverse","p_{T}^{t#bar{t}} [GeV]","#LT p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"transverse",-1,-1,1.4,4.5,"_v15");

plot_stack_profile("profile_ptttbar_npf_toward","p_{T}^{t#bar{t}} [GeV]","N_{ch} ",1,1,1,lumii,latexLabel,ise,"toward",-1,-1,4.1,16.1,"_v15");
plot_stack_profile("profile_ptttbar_sumpt_toward","p_{T}^{t#bar{t}} [GeV]","#Sigma p_{T}^{ch} [GeV]",1,1,1,lumii,latexLabel,ise,"toward",-1,-1,7.01,45.1,"_v15");
plot_stack_profile("profile_ptttbar_avept_toward","p_{T}^{t#bar{t}} [GeV]","#LT p_{T}^{ch} #GT  [GeV]",1,1,1,lumii,latexLabel,ise,"toward",-1,-1,1.4,4.5,"_v15");
}
if(plot_set==3){

plot_stack_profile("profile_ytt_npf","y (t#bar{t})","#LT N_{ch} #GT",1,0,1,lumii,latexLabel,ise," ",0,2.2,0,55,"_v15");

plot_stack_profile("profile_mttbar_npf","M (t#bar{t}) [GeV]","#LT N_{ch} #GT",1,1,1,lumii,latexLabel,ise," ",-1,-1,0,55,"_v15");
plot_stack_profile("profile_mttbar_sumpt","M (t#bar{t}) [GeV]","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise," ",-1,-1,0,200,"_v15");
plot_stack_profile("profile_mttbar_avept","M (t#bar{t}) [GeV]","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise," ",-1,-1,1,8.5,"_v15");

plot_stack_profile("profile_mttbar_npf_away","M (t#bar{t}) [GeV]","#LT N_{ch} #GT",1,1,1,lumii,latexLabel,ise,"away",-1,-1,0,55,"_v15");
plot_stack_profile("profile_mttbar_sumpt_away","M (t#bar{t}) [GeV]","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"away",-1,-1,0,200,"_v15");
plot_stack_profile("profile_mttbar_avept_away","M (t#bar{t}) [GeV]","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"away",-1,-1,1,8.5,"_v15");

plot_stack_profile("profile_mttbar_npf_transverse","M (t#bar{t}) [GeV]","#LT N_{ch} #GT",1,1,1,lumii,latexLabel,ise,"transverse",-1,-1,0,55,"_v15");
plot_stack_profile("profile_mttbar_sumpt_transverse","M (t#bar{t}) [GeV]","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"transverse",-1,-1,0,200,"_v15");
plot_stack_profile("profile_mttbar_avept_transverse","M (t#bar{t}) [GeV]","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"transverse",-1,-1,1,8.5,"_v15");

plot_stack_profile("profile_mttbar_npf_toward","M (t#bar{t}) [GeV]","#LT N_{ch} #GT",1,1,1,lumii,latexLabel,ise,"toward",-1,-1,0,55,"_v15");
plot_stack_profile("profile_mttbar_sumpt_toward","M (t#bar{t}) [GeV]","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"toward",-1,-1,0,200,"_v15");
plot_stack_profile("profile_mttbar_avept_toward","M (t#bar{t}) [GeV]","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"toward",-1,-1,1,8.5,"_v15");


plot_stack_profile("profile_ptthad_npf","p_{T} (t_{had}) [GeV]","#LT N_{ch} #GT",1,1,1,lumii,latexLabel,ise," ",-1,-1,0,55,"_v15");
plot_stack_profile("profile_ptthad_sumpt","p_{T} (t_{had}) [GeV]","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise," ",-1,-1,0,200,"_v15");
plot_stack_profile("profile_ptthad_avept","p_{T} (t_{had}) [GeV]","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise," ",-1,-1,1,8.5,"_v15");

plot_stack_profile("profile_ptthad_npf_away","p_{T} (t_{had}) [GeV]","#LT N_{ch} #GT",1,1,1,lumii,latexLabel,ise,"away",-1,-1,0,55,"_v15");
plot_stack_profile("profile_ptthad_sumpt_away","p_{T} (t_{had}) [GeV]","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"away",-1,-1,0,200,"_v15");
plot_stack_profile("profile_ptthad_avept_away","p_{T} (t_{had}) [GeV]","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"away",-1,-1,1,8.5,"_v15");

plot_stack_profile("profile_ptthad_npf_transverse","p_{T} (t_{had}) [GeV]","#LT N_{ch} #GT",1,1,1,lumii,latexLabel,ise,"transverse",-1,-1,0,55,"_v15");
plot_stack_profile("profile_ptthad_sumpt_transverse","p_{T} (t_{had}) [GeV]","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"transverse",-1,-1,0,200,"_v15");
plot_stack_profile("profile_ptthad_avept_transverse","p_{T} (t_{had}) [GeV]","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"transverse",-1,-1,1,8.5,"_v15");


plot_stack_profile("profile_ptthad_npf_toward","p_{T} (t_{had}) [GeV]","#LT N_{ch} #GT",1,1,1,lumii,latexLabel,ise,"toward",-1,-1,0,55,"_v15");
plot_stack_profile("profile_ptthad_sumpt_toward","p_{T} (t_{had}) [GeV]","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"toward",-1,-1,0,200,"_v15");
plot_stack_profile("profile_ptthad_avept_toward","p_{T} (t_{had}) [GeV]","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"toward",-1,-1,1,8.5,"_v15");



plot_stack_profile("profile_pttlep_npf","p_{T} (t_{lep}) [GeV]","#LT N_{ch} #GT",1,1,1,lumii,latexLabel,ise," ",-1,-1,0,55,"_v15");
plot_stack_profile("profile_pttlep_sumpt","p_{T} (t_{lep}) [GeV]","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise," ",-1,-1,0,200,"_v15");
plot_stack_profile("profile_pttlep_avept","p_{T} (t_{lep}) [GeV]","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise," ",-1,-1,1,8.5,"_v15");

plot_stack_profile("profile_pttlep_npf_away","p_{T} (t_{lep}) [GeV]","#LT N_{ch} #GT",1,1,1,lumii,latexLabel,ise,"away",-1,-1,0,55,"_v15");
plot_stack_profile("profile_pttlep_sumpt_away","p_{T} (t_{lep}) [GeV]","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"away",-1,-1,0,200,"_v15");
plot_stack_profile("profile_pttlep_avept_away","p_{T} (t_{lep}) [GeV]","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"away",-1,-1,1,8.5,"_v15");

plot_stack_profile("profile_pttlep_npf_transverse","p_{T} (t_{lep}) [GeV]","#LT N_{ch} #GT",1,1,1,lumii,latexLabel,ise,"transverse",-1,-1,0,55,"_v15");
plot_stack_profile("profile_pttlep_sumpt_transverse","p_{T} (t_{lep}) [GeV]","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"transverse",-1,-1,0,200,"_v15");
plot_stack_profile("profile_pttlep_avept_transverse","p_{T} (t_{lep}) [GeV]","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"transverse",-1,-1,1,8.5,"_v15");

plot_stack_profile("profile_pttlep_npf_toward","p_{T} (t_{lep}) [GeV]","#LT N_{ch} #GT",1,1,1,lumii,latexLabel,ise,"toward",-1,-1,0,55,"_v15");
plot_stack_profile("profile_pttlep_sumpt_toward","p_{T} (t_{lep}) [GeV]","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"toward",-1,-1,0,200,"_v15");
plot_stack_profile("profile_pttlep_avept_toward","p_{T} (t_{lep}) [GeV]","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"toward",-1,-1,1,8.5,"_v15");


plot_stack_profile("profile_ytt_npf","y (t#bar{t})","#LT N_{ch} #GT",1,0,1,lumii,latexLabel,ise," ",0,2.2,0,55,"_v15");
plot_stack_profile("profile_ytt_sumpt","y (t#bar{t})","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise," ",0,2.2,0,200,"_v15");
plot_stack_profile("profile_ytt_avept","y (t#bar{t})","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise," ",0,2.2,1,8.5,"_v15");

plot_stack_profile("profile_ytt_npf_away","y (t#bar{t})","#LT N_{ch} #GT",1,0,1,lumii,latexLabel,ise,"away",0,2.2,0,55,"_v15");
plot_stack_profile("profile_ytt_sumpt_away","y (t#bar{t})","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"away",0,2.2,0,200,"_v15");
plot_stack_profile("profile_ytt_avept_away","y (t#bar{t})","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"away",0,2.2,1,8.5,"_v15");

plot_stack_profile("profile_ytt_npf_transverse","y (t#bar{t})","#LT N_{ch} #GT",1,0,1,lumii,latexLabel,ise,"transverse",0,2.2,0,55,"_v15");
plot_stack_profile("profile_ytt_sumpt_transverse","y (t#bar{t})","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"transverse",0,2.2,0,200,"_v15");
plot_stack_profile("profile_ytt_avept_transverse","y (t#bar{t})","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"transverse",0,2.2,1,8.5,"_v15");

plot_stack_profile("profile_ytt_npf_toward","y (t#bar{t})","#LT N_{ch} #GT",1,0,1,lumii,latexLabel,ise,"toward",0,2.2,0,55,"_v15");
plot_stack_profile("profile_ytt_sumpt_toward","y (t#bar{t})","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"toward",0,2.2,0,200,"_v15");
plot_stack_profile("profile_ytt_avept_toward","y (t#bar{t})","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"toward",0,2.2,1,8.5,"_v15");

plot_stack_profile("profile_yttj_npf","y (t#bar{t}j)","#LT N_{ch} #GT",1,0,1,lumii,latexLabel,ise," ",0,2.2,0,55,"_v15");
plot_stack_profile("profile_yttj_sumpt","y (t#bar{t}j)","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise," ",0,2.2,0,200,"_v15");
plot_stack_profile("profile_yttj_avept","y (t#bar{t}j)","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise," ",0,2.2,1,8.5,"_v15");

plot_stack_profile("profile_yttj_npf_away","y (t#bar{t}j)","#LT N_{ch} #GT",1,0,1,lumii,latexLabel,ise,"away",0,2.2,0,55,"_v15");
plot_stack_profile("profile_yttj_sumpt_away","y (t#bar{t}j)","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"away",0,2.2,0,200,"_v15");
plot_stack_profile("profile_yttj_avept_away","y (t#bar{t}j)","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"away",0,2.2,1,8.5,"_v15");

plot_stack_profile("profile_yttj_npf_transverse","y (t#bar{t}j)","#LT N_{ch} #GT",1,0,1,lumii,latexLabel,ise,"transverse",0,2.2,0,55,"_v15");
plot_stack_profile("profile_yttj_sumpt_transverse","y (t#bar{t}j)","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"transverse",0,2.2,0,200,"_v15");
plot_stack_profile("profile_yttj_avept_transverse","y (t#bar{t}j)","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"transverse",0,2.2,1,8.5,"_v15");

plot_stack_profile("profile_yttj_npf_toward","y (t#bar{t}j)","#LT N_{ch} #GT",1,0,1,lumii,latexLabel,ise,"toward",0,2.2,0,55,"_v15");
plot_stack_profile("profile_yttj_sumpt_toward","y (t#bar{t}j)","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"toward",0,2.2,0,200,"_v15");
plot_stack_profile("profile_yttj_avept_toward","y (t#bar{t}j)","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"toward",0,2.2,1,8.5,"_v15");


plot_stack_profile("profile_ythad_npf","y (t_{had})","#LT N_{ch} #GT",1,0,1,lumii,latexLabel,ise," ",0,2.2,0,55,"_v15");
plot_stack_profile("profile_ythad_sumpt","y (t_{had})","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise," ",0,2.2,0,200,"_v15");
plot_stack_profile("profile_ythad_avept","y (t_{had})","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise," ",0,2.2,1,8.5,"_v15");

plot_stack_profile("profile_ythad_npf_away","y (t_{had})","#LT N_{ch} #GT",1,0,1,lumii,latexLabel,ise,"away",0,2.2,0,55,"_v15");
plot_stack_profile("profile_ythad_sumpt_away","y (t_{had})","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"away",0,2.2,0,200,"_v15");
plot_stack_profile("profile_ythad_avept_away","y (t_{had})","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"away",0,2.2,1,8.5,"_v15");

plot_stack_profile("profile_ythad_npf_transverse","y (t_{had})","#LT N_{ch} #GT",1,0,1,lumii,latexLabel,ise,"transverse",0,2.2,0,55,"_v15");
plot_stack_profile("profile_ythad_sumpt_transverse","y (t_{had})","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"transverse",0,2.2,0,200,"_v15");
plot_stack_profile("profile_ythad_avept_transverse","y (t_{had})","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"transverse",0,2.2,1,8.5,"_v15");

plot_stack_profile("profile_ythad_npf_toward","y (t_{had})","#LT N_{ch} #GT",1,0,1,lumii,latexLabel,ise,"toward",0,2.2,0,55,"_v15");
plot_stack_profile("profile_ythad_sumpt_toward","y (t_{had})","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"toward",0,2.2,0,200,"_v15");
plot_stack_profile("profile_ythad_avept_toward","y (t_{had})","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"toward",0,2.2,1,8.5,"_v15");

plot_stack_profile("profile_ytlep_npf","y (t_{lep})","#LT N_{ch} #GT",1,0,1,lumii,latexLabel,ise," ",0,2.2,0,55,"_v15");
plot_stack_profile("profile_ytlep_sumpt","y (t_{lep})","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise," ",0,2.2,0,200,"_v15");
plot_stack_profile("profile_ytlep_avept","y (t_{lep})","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise," ",0,2.2,1,8.5,"_v15");

plot_stack_profile("profile_ytlep_npf_away","y (t_{lep})","#LT N_{ch} #GT",1,0,1,lumii,latexLabel,ise,"away",0,2.2,0,55,"_v15");
plot_stack_profile("profile_ytlep_sumpt_away","y (t_{lep})","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"away",0,2.2,0,200,"_v15");
plot_stack_profile("profile_ytlep_avept_away","y (t_{lep})","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"away",0,2.2,1,8.5,"_v15");

plot_stack_profile("profile_ytlep_npf_transverse","y (t_{lep})","#LT N_{ch} #GT",1,0,1,lumii,latexLabel,ise,"transverse",0,2.2,0,55,"_v15");
plot_stack_profile("profile_ytlep_sumpt_transverse","y (t_{lep})","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"transverse",0,2.2,0,200,"_v15");
plot_stack_profile("profile_ytlep_avept_transverse","y (t_{lep})","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"transverse",0,2.2,1,8.5,"_v15");

plot_stack_profile("profile_ytlep_npf_toward","y (t_{lep})","#LT N_{ch} #GT",1,0,1,lumii,latexLabel,ise,"toward",0,2.2,0,55,"_v15");
plot_stack_profile("profile_ytlep_sumpt_toward","y (t_{lep})","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"toward",0,2.2,0,200,"_v15");
plot_stack_profile("profile_ytlep_avept_toward","y (t_{lep})","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"toward",0,2.2,1,8.5,"_v15");



plot_stack_profile("profile_yt_npf","y (t and #bar{t})","#LT N_{ch} #GT",1,0,1,lumii,latexLabel,ise," ",0,2.2,0,55,"_v15");
plot_stack_profile("profile_yt_sumpt","y (t and #bar{t})","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise," ",0,2.2,0,200,"_v15");
plot_stack_profile("profile_yt_avept","y (t and #bar{t})","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise," ",0,2.2,1,8.5,"_v15");

plot_stack_profile("profile_yt_npf_away","y (t and #bar{t})","#LT N_{ch} #GT",1,0,1,lumii,latexLabel,ise,"away",0,2.2,0,55,"_v15");
plot_stack_profile("profile_yt_sumpt_away","y (t and #bar{t})","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"away",0,2.2,0,200,"_v15");
plot_stack_profile("profile_yt_avept_away","y (t and #bar{t})","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"away",0,2.2,1,8.5,"_v15");

plot_stack_profile("profile_yt_npf_transverse","y (t and #bar{t})","#LT N_{ch} #GT",1,0,1,lumii,latexLabel,ise,"transverse",0,2.2,0,55,"_v15");
plot_stack_profile("profile_yt_sumpt_transverse","y (t and #bar{t})","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"transverse",0,2.2,0,200,"_v15");
plot_stack_profile("profile_yt_avept_transverse","y (t and #bar{t})","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"transverse",0,2.2,1,8.5,"_v15");

plot_stack_profile("profile_yt_npf_toward","y (t and #bar{t})","#LT N_{ch} #GT",1,0,1,lumii,latexLabel,ise,"toward",0,2.2,0,55,"_v15");
plot_stack_profile("profile_yt_sumpt_toward","y (t and #bar{t})","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"toward",0,2.2,0,200,"_v15");
plot_stack_profile("profile_yt_avept_toward","y (t and #bar{t})","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise,"toward",0,2.2,1,8.5,"_v15");


plot_stack_profile("profile_mthad_npf","M (t_{had}) [GeV]","#LT N_{ch} #GT",1,1,1,lumii,latexLabel,ise," ",-1,-1,0,55,"_v15");
plot_stack_profile("profile_mthad_sumpt","M (t_{had}) [GeV]","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise," ",-1,-1,0,200,"_v15");
plot_stack_profile("profile_mthad_avept","M (t_{had}) [GeV]","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise," ",-1,-1,1,8.5,"_v15");

plot_stack_profile("profile_mthad_npf_away","M (t_{had}) [GeV]","#LT N_{ch} #GT",1,1,1,lumii,latexLabel,ise,"away",-1,-1,0,55,"_v15");
plot_stack_profile("profile_mthad_sumpt_away","M (t_{had}) [GeV]","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"away",-1,-1,0,200,"_v15");
plot_stack_profile("profile_mthad_avept_away","M (t_{had}) [GeV]","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"away",-1,-1,1,8.5,"_v15");

plot_stack_profile("profile_mthad_npf_transverse","M (t_{had}) [GeV]","#LT N_{ch} #GT",1,1,1,lumii,latexLabel,ise,"transverse",-1,-1,0,55,"_v15");
plot_stack_profile("profile_mthad_sumpt_transverse","M (t_{had}) [GeV]","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"transverse",-1,-1,0,200,"_v15");
plot_stack_profile("profile_mthad_avept_transverse","M (t_{had}) [GeV]","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"transverse",-1,-1,1,8.5,"_v15");

plot_stack_profile("profile_mthad_npf_toward","M (t_{had}) [GeV]","#LT N_{ch} #GT",1,1,1,lumii,latexLabel,ise,"toward",-1,-1,0,55,"_v15");
plot_stack_profile("profile_mthad_sumpt_toward","M (t_{had}) [GeV]","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"toward",-1,-1,0,200,"_v15");
plot_stack_profile("profile_mthad_avept_toward","M (t_{had}) [GeV]","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"toward",-1,-1,1,8.5,"_v15");

plot_stack_profile("profile_mtlep_npf","M (t_{lep}) [GeV]","#LT N_{ch} #GT",1,1,1,lumii,latexLabel,ise," ",-1,-1,0,55,"_v15");
plot_stack_profile("profile_mtlep_sumpt","M (t_{lep}) [GeV]","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise," ",-1,-1,0,200,"_v15");
plot_stack_profile("profile_mtlep_avept","M (t_{lep}) [GeV]","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise," ",-1,-1,1,8.5,"_v15");


plot_stack_profile("profile_mtlep_npf_away","M (t_{lep}) [GeV]","#LT N_{ch} #GT",1,1,1,lumii,latexLabel,ise,"away",-1,-1,0,55,"_v15");
plot_stack_profile("profile_mtlep_sumpt_away","M (t_{lep}) [GeV]","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"away",-1,-1,0,200,"_v15");
plot_stack_profile("profile_mtlep_avept_away","M (t_{lep}) [GeV]","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"away",-1,-1,1,8.5,"_v15");

plot_stack_profile("profile_mtlep_npf_transverse","M (t_{lep}) [GeV]","#LT N_{ch} #GT",1,1,1,lumii,latexLabel,ise,"transverse",-1,-1,0,55,"_v15");
plot_stack_profile("profile_mtlep_sumpt_transverse","M (t_{lep}) [GeV]","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"transverse",-1,-1,0,200,"_v15");
plot_stack_profile("profile_mtlep_avept_transverse","M (t_{lep}) [GeV]","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"transverse",-1,-1,1,8.5,"_v15");

plot_stack_profile("profile_mtlep_npf_toward","M (t_{lep}) [GeV]","#LT N_{ch} #GT",1,1,1,lumii,latexLabel,ise,"toward",-1,-1,0,55,"_v15");
plot_stack_profile("profile_mtlep_sumpt_toward","M (t_{lep}) [GeV]","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"toward",-1,-1,0,200,"_v15");
plot_stack_profile("profile_mtlep_avept_toward","M (t_{lep}) [GeV]","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"toward",-1,-1,1,8.5,"_v15");



plot_stack_profile("profile_ptt_npf","p_{T} (t and #bar{t}) [GeV]","#LT N_{ch} #GT",1,1,1,lumii,latexLabel,ise," ",-1,-1,0,55,"_v15");
plot_stack_profile("profile_ptt_sumpt","p_{T} (t and #bar{t}) [GeV]","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise," ",-1,-1,0,200,"_v15");
plot_stack_profile("profile_ptt_avept","p_{T} (t and #bar{t}) [GeV]","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise," ",-1,-1,1,8.5,"_v15");

plot_stack_profile("profile_ptt_npf_away","p_{T} (t and #bar{t}) [GeV]","#LT N_{ch} #GT",1,1,1,lumii,latexLabel,ise,"away",-1,-1,0,55,"_v15");
plot_stack_profile("profile_ptt_sumpt_away","p_{T} (t and #bar{t}) [GeV]","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"away",-1,-1,0,200,"_v15");
plot_stack_profile("profile_ptt_avept_away","p_{T} (t and #bar{t}) [GeV]","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"away",-1,-1,1,8.5,"_v15");

plot_stack_profile("profile_ptt_npf_transverse","p_{T} (t and #bar{t}) [GeV]","#LT N_{ch} #GT",1,1,1,lumii,latexLabel,ise,"transverse",-1,-1,0,55,"_v15");
plot_stack_profile("profile_ptt_sumpt_transverse","p_{T} (t and #bar{t}) [GeV]","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"transverse",-1,-1,0,200,"_v15");
plot_stack_profile("profile_ptt_avept_transverse","p_{T} (t and #bar{t}) [GeV]","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"transverse",-1,-1,1,8.5,"_v15");


plot_stack_profile("profile_ptt_npf_toward","p_{T} (t and #bar{t}) [GeV]","#LT N_{ch} #GT",1,1,1,lumii,latexLabel,ise,"toward",-1,-1,0,55,"_v15");
plot_stack_profile("profile_ptt_sumpt_toward","p_{T} (t and #bar{t}) [GeV]","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"toward",-1,-1,0,200,"_v15");
plot_stack_profile("profile_ptt_avept_toward","p_{T} (t and #bar{t}) [GeV]","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"toward",-1,-1,1,8.5,"_v15");






plot_stack_profile("profile_mt_npf","M (t and #bar{t}) [GeV]","#LT N_{ch} #GT",1,1,1,lumii,latexLabel,ise," ",-1,-1,0,55,"_v15");
plot_stack_profile("profile_mt_sumpt","M (t and #bar{t}) [GeV]","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise," ",-1,-1,0,200,"_v15");
plot_stack_profile("profile_mt_avept","M (t and #bar{t}) [GeV]","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise," ",-1,-1,1,8.5,"_v15");

plot_stack_profile("profile_mt_npf_away","M (t and #bar{t}) [GeV]","#LT N_{ch} #GT",1,1,1,lumii,latexLabel,ise,"away",-1,-1,0,55,"_v15");
plot_stack_profile("profile_mt_sumpt_away","M (t and #bar{t}) [GeV]","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"away",-1,-1,0,200,"_v15");
plot_stack_profile("profile_mt_avept_away","M (t and #bar{t}) [GeV]","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"away",-1,-1,1,8.5,"_v15");

plot_stack_profile("profile_mt_npf_transverse","M (t and #bar{t}) [GeV]","#LT N_{ch} #GT",1,1,1,lumii,latexLabel,ise,"transverse",-1,-1,0,55,"_v15");
plot_stack_profile("profile_mt_sumpt_transverse","M (t and #bar{t}) [GeV]","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"transverse",-1,-1,0,200,"_v15");
plot_stack_profile("profile_mt_avept_transverse","M (t and #bar{t}) [GeV]","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"transverse",-1,-1,1,8.5,"_v15");

plot_stack_profile("profile_mt_npf_toward","M (t and #bar{t}) [GeV]","#LT N_{ch} #GT",1,1,1,lumii,latexLabel,ise,"toward",-1,-1,0,55,"_v15");
plot_stack_profile("profile_mt_sumpt_toward","M (t and #bar{t}) [GeV]","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"toward",-1,-1,0,200,"_v15");
plot_stack_profile("profile_mt_avept_toward","M (t and #bar{t}) [GeV]","#LT #bar{p}_{T}^{ch} #GT [GeV]",1,1,1,lumii,latexLabel,ise,"toward",-1,-1,1,8.5,"_v15");






plot_stack_profile("profile_nvtx_npf","N_{vtx}","<N^{ch}>",1,0,1,lumii,latexLabel,ise," ",-1,-1,0,50,"_v15");
plot_stack_profile("profile_nvtx_sumpt","N_{vtx}","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise," ",-1,-1,0,170,"_v15");
plot_stack_profile("profile_nvtx_npf_0j","N_{vtx}","<N^{ch}>",1,0,1,lumii,latexLabel,ise," =0 jet",-1,-1,0,50,"_v15");
plot_stack_profile("profile_nvtx_sumpt_0j","N_{vtx}","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise," =0 jet",-1,-1,0,170,"_v15");
plot_stack_profile("profile_nvtx_npf_1j","N_{vtx}","<N^{ch}> [GeV]",1,0,1,lumii,latexLabel,ise," =1 jet",-1,-1,0,50,"_v15");
plot_stack_profile("profile_nvtx_sumpt_1j","N_{vtx}","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise," =1 jet",-1,-1,0,170,"_v15");
plot_stack_profile("profile_nvtx_npf_2pj","N_{vtx}","<N^{ch}>",1,0,1,lumii,latexLabel,ise," >=2 jets",-1,-1,0,50,"_v15");
plot_stack_profile("profile_nvtx_sumpt_2pj","N_{vtx}","#LT #Sigma p_{T}^{ch} #GT [GeV]",1,0,1,lumii,latexLabel,ise," >=2 jets",-1,-1,0,170,"_v15");

plot_stack_profile("profile_deta_bb_njet_bb","#Delta#eta(b,b)","<n_{extra jet}>",1,0,1,lumii,latexLabel,ise," in bb rapidity span",0,4.5,0,5,"_v15");

plot_stack_profile("profile_deta_bb_njet_extra","#Delta#eta(b,b)","<n_{extra jet}>",1,0,1,lumii,latexLabel,ise," inclusive",0,4.5,0,5,"_v15");
}



}

}


