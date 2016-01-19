void macro_btageff(){
   gStyle->SetOptStat(kFALSE);
   gStyle->SetOptTitle(kFALSE);
TFile *mc_s = TFile::Open("25ns_tt_uev_miniaodv2_2110_fromskimmed_isElec_0_v16.root");
TH2D* bmatch_tmp =(TH2D*) mc_s->Get("pt_eta_b_tagged_0");
TH2D* b_tmp = (TH2D*)mc_s->Get("pt_eta_b_0");

TH2D* cmatch_tmp = (TH2D*)mc_s->Get("pt_eta_c_tagged_0");
TH2D* c_tmp = (TH2D*)mc_s->Get("pt_eta_c_0");

TH2D* udsgmatch_tmp = (TH2D*)mc_s->Get("pt_eta_udsg_tagged_0");
TH2D* udsg_tmp = (TH2D*)mc_s->Get("pt_eta_udsg_0");


TH2D* b_eff = (TH2D*)b_tmp->Clone("b_eff");

TH2D* c_eff = (TH2D*)b_tmp->Clone("c_eff");
TH2D* udsg_eff = (TH2D*)b_tmp->Clone("udsg_eff");
ofstream Yfan;
Yfan.open ("btageffic.csv");
for(int i=1;i<=bmatch_tmp->GetNbinsX();i++){
for(int j=1;j<=bmatch_tmp->GetNbinsY();j++){

//cout<<bmatch_tmp->GetBinContent(i,j)<<"  "<<b_tmp->GetBinContent(i,j)<<"  "<<bmatch_tmp->GetBinContent(i,j)/b_tmp->GetBinContent(i,j)<<endl;

Yfan<<"1 , mujets , central , 0 , "
    <<bmatch_tmp->GetYaxis()->GetBinCenter(j)-bmatch_tmp->GetYaxis()->GetBinWidth(j)/2 <<" , "<<bmatch_tmp->GetYaxis()->GetBinCenter(j)+bmatch_tmp->GetYaxis()->GetBinWidth(j)/2 <<" , " 
    <<bmatch_tmp->GetXaxis()->GetBinCenter(i)-bmatch_tmp->GetXaxis()->GetBinWidth(i)/2 <<" , "<<bmatch_tmp->GetXaxis()->GetBinCenter(i)+bmatch_tmp->GetXaxis()->GetBinWidth(i)/2 <<" , " 
    <<"0 , 1 ," 
    <<bmatch_tmp->GetBinContent(i,j)/b_tmp->GetBinContent(i,j)<<endl;
b_eff->SetBinContent(i,j,bmatch_tmp->GetBinContent(i,j)/b_tmp->GetBinContent(i,j));
c_eff->SetBinContent(i,j,cmatch_tmp->GetBinContent(i,j)/c_tmp->GetBinContent(i,j));
udsg_eff->SetBinContent(i,j,udsgmatch_tmp->GetBinContent(i,j)/udsg_tmp->GetBinContent(i,j));
}}
for(int i=1;i<=bmatch_tmp->GetNbinsX();i++){
for(int j=1;j<=bmatch_tmp->GetNbinsY();j++){

Yfan<<"1 , mujets , central , 1 , "
    <<cmatch_tmp->GetYaxis()->GetBinCenter(j)-cmatch_tmp->GetYaxis()->GetBinWidth(j)/2 <<" , "<<cmatch_tmp->GetYaxis()->GetBinCenter(j)+cmatch_tmp->GetYaxis()->GetBinWidth(j)/2 <<" , " 
    <<cmatch_tmp->GetXaxis()->GetBinCenter(i)-cmatch_tmp->GetXaxis()->GetBinWidth(i)/2 <<" , "<<cmatch_tmp->GetXaxis()->GetBinCenter(i)+cmatch_tmp->GetXaxis()->GetBinWidth(i)/2 <<" , " 
    <<"0 , 1 ," 
    <<cmatch_tmp->GetBinContent(i,j)/c_tmp->GetBinContent(i,j)<<endl;
}}
for(int i=1;i<=bmatch_tmp->GetNbinsX();i++){
for(int j=1;j<=bmatch_tmp->GetNbinsY();j++){

Yfan<<"1 , mujets , central , 2 , "
    <<udsgmatch_tmp->GetYaxis()->GetBinCenter(j)-udsgmatch_tmp->GetYaxis()->GetBinWidth(j)/2 <<" , "<<udsgmatch_tmp->GetYaxis()->GetBinCenter(j)+udsgmatch_tmp->GetYaxis()->GetBinWidth(j)/2 <<" , " 
    <<udsgmatch_tmp->GetXaxis()->GetBinCenter(i)-udsgmatch_tmp->GetXaxis()->GetBinWidth(i)/2 <<" , "<<udsgmatch_tmp->GetXaxis()->GetBinCenter(i)+udsgmatch_tmp->GetXaxis()->GetBinWidth(i)/2 <<" , " 
    <<"0 , 1 ," 
    <<udsgmatch_tmp->GetBinContent(i,j)/udsg_tmp->GetBinContent(i,j)<<endl;



}}
TCanvas *c1 = new TCanvas("c1","c1",800,800);
c1->cd();
b_eff->Draw("COLZ");
b_eff->GetXaxis()->SetTitle("p_{T} [GeV]");
b_eff->GetYaxis()->SetTitle("#eta");
c1->Print("b_eff.pdf");

TCanvas *c2 = new TCanvas("c2","c2",800,800);
c2->cd();
c_eff->Draw("COLZ");
c_eff->GetXaxis()->SetTitle("p_{T} [GeV]");
c_eff->GetYaxis()->SetTitle("#eta");
c2->Print("c_eff.pdf");

TCanvas *c3= new TCanvas("c3","c3",800,800);
c3->cd();
udsg_eff->Draw("COLZ");
udsg_eff->GetXaxis()->SetTitle("p_{T} [GeV]");
udsg_eff->GetYaxis()->SetTitle("#eta");
c3->Print("udsg_eff.pdf");


}

