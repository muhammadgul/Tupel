void macro_unfold(){
   gStyle->SetOptStat(kFALSE);
   gStyle->SetOptTitle(kFALSE);

  TFile *mc_ss = TFile::Open("25ns_tt_uev_miniaodv2_20160307_fromskimmed_isElec_0_v24.root");

  TH2D * matrix_tmp =(TH2D*) mc_ss->Get("2d_npf_1");
  TH2D * matrix =(TH2D*) matrix_tmp->Clone("matrix");

  TH1D * gen_tmp =(TH1D*) mc_ss->Get("1d_npf_0");
  TH1D * gen =(TH1D*)gen_tmp->Clone("gen");

  TH1D * rec_tmp =(TH1D*) mc_ss->Get("1d_npf_1");
  TH1D * rec =(TH1D*)rec_tmp->Clone("rec");

//add data and BG and do proper unfolding

  TH1D* rec_unf=(TH1D*)rec_tmp->Clone("rec");//unfold thse same MC for test now
 
  TH1D* purity= (TH1D*) matrix->ProjectionY();//gen
  TH1D* projgen=(TH1D*)purity->Clone();

  TH1D* stability= (TH1D*) matrix->ProjectionX();//rec
  TH1D*	projrec=(TH1D*)stability->Clone();

  stability->Divide(stability,rec_tmp,1,1);
  purity->Divide(purity,gen_tmp,1,1);

  stability->SetLineColor(kRed);

  int bin_check=1;
  vector<int> bin_ranges;
  vector<double> stab_vec;
  vector<double> pur_vec;
  for(int bin=1;bin<=rec->GetNbinsX();bin++){

    if(bin<=bin_check)continue;
    double recbincont=matrix->Integral(bin,bin,1,rec->GetNbinsX());
    double recbinprojcont=matrix->Integral(bin,bin,bin,bin);
    double genbincont=matrix->Integral(1,rec->GetNbinsX(),bin,bin);
    bin_ranges.push_back(bin_check);
    for(int binn=bin+1;binn<=rec->GetNbinsX();binn++){
      double stabilityy=recbinprojcont/recbincont;
      double purityy=recbinprojcont/genbincont;
      bin_check=binn;
      if(stabilityy>=0.5&&purityy>=0.5){
        stab_vec.push_back(stabilityy); pur_vec.push_back(purityy);
        break;
      }
      recbinprojcont=matrix->Integral(bin,binn,bin,binn);
      recbincont=matrix->Integral(bin,binn,1,rec->GetNbinsX());
      genbincont=matrix->Integral(1,rec->GetNbinsX(),bin,binn);
    }
  }
  cout<<bin_ranges.size()<<"  "<<bin_ranges.size()*2<<endl;
  double ranges_for_fill_rec[bin_ranges.size()*2];
  double ranges_for_fill_gen[bin_ranges.size()];
 //rebinning using bin edge info obtained

/*  for(int iii=0;iii<bin_ranges.size();iii++){

    ranges_for_fill_gen[iii]=rec->GetBinCenter(bin_ranges[iii])-rec->GetBinWidth(bin_ranges[iii])/2;
    if(2*iii<=bin_ranges.size())ranges_for_fill_rec[iii]=rec->GetBinCenter(bin_ranges[2*iii])-rec->GetBinWidth(bin_ranges[2*iii])/2;
  }*/
  for(int iii=0;iii<bin_ranges.size();iii++){

    if(iii<bin_ranges.size())ranges_for_fill_gen[iii]=rec->GetBinCenter(bin_ranges[iii])-rec->GetBinWidth(bin_ranges[iii])/2;
    ranges_for_fill_rec[2*iii]=rec->GetBinCenter(bin_ranges[iii])-rec->GetBinWidth(bin_ranges[iii])/2;
    if(iii<bin_ranges.size()-1){
//      ranges_for_fill_rec[2*iii+1]=((rec->GetBinCenter(bin_ranges[iii+1])-rec->GetBinWidth(bin_ranges[iii+1])/2)+(rec->GetBinCenter(bin_ranges[iii])-rec->GetBinWidth(bin_ranges[iii])/2))/2;
       int bincent=(bin_ranges[iii+1]+bin_ranges[iii])/2;
       ranges_for_fill_rec[2*iii+1]=rec->GetBinCenter(bincent)-rec->GetBinWidth(bincent)/2;
       //cout<<"aaa"<<bin_ranges[iii+1]<<"  "<<bin_ranges[iii]<<"  "<<bincent<<endl;
    }

  //  cout<<iii<<"  "<<rec->GetBinCenter(bin_ranges[iii])/2-rec->GetBinWidth(bin_ranges[iii])/4<<"  "<<rec->GetBinCenter(bin_ranges[iii])-rec->GetBinWidth(bin_ranges[iii])/2<<endl;
    //cout<<bin_ranges[iii]<<"  "<<ranges_for_fill_rec[2*iii]<<"  "<<ranges_for_fill_rec[2*iii+1]<<endl;
  }

 // cout<<"I am here"<<endl;
//  TH2D* matrix_rebin = new TH2D("matrix_rebin","matrix_rebin",bin_ranges.size()-1,ranges_for_fill_gen,bin_ranges.size()/2,ranges_for_fill_rec);
  TH2D* matrix_rebin = new TH2D("matrix_rebin","matrix_rebin",bin_ranges.size()-1,ranges_for_fill_gen,(bin_ranges.size()-1)*2,ranges_for_fill_rec);
  for(int iii=0;iii<bin_ranges.size();iii++){
    for(int jjj=0;jjj<bin_ranges.size()*2;jjj++){
   //   cout<<matrix_rebin->GetYaxis()->GetBinCenter(jjj+1)<<endl;
      matrix_rebin->SetBinContent(iii+1,jjj+1,matrix->Integral(bin_ranges[jjj]/2,bin_ranges[jjj]/2,bin_ranges[iii],bin_ranges[iii+1]));
    }
  }

//  TH1D* rec_rebin   =(TH1D*)rec->Rebin(bin_ranges.size()/2,"rec_rebin",ranges_for_fill_rec) ;
  TH1D* rec_rebin   =(TH1D*)rec->Rebin((bin_ranges.size()-1)*2,"rec_rebin",ranges_for_fill_rec) ;
  TH1D* gen_rebin   =(TH1D*)gen->Rebin(bin_ranges.size()-1,"gen_rebin",ranges_for_fill_gen) ;

//  TH1D* rec_unf_rebin   =(TH1D*)rec_unf->Rebin(bin_ranges.size()/2,"rec_rebin",ranges_for_fill_rec) ;
  TH1D* rec_unf_rebin   =(TH1D*)rec_unf->Rebin((bin_ranges.size()-1)*2,"rec_rebin",ranges_for_fill_rec) ;

  TH1D* miss_rebin=(TH1D*)gen_rebin->Clone("miss_rebin");
  TH1D* gen_Rec_rebin=(TH1D*)matrix_rebin->ProjectionX();
  miss_rebin->Add(gen_Rec_rebin,-1);
  
  TH1D* miss=(TH1D*)gen->Clone("miss");
  TH1D* gen_Rec=(TH1D*)matrix->ProjectionY();//not reverted before rebinning
  miss->Add(gen_Rec,-1);

  TH1D* miss_rebin_check   =(TH1D*)miss->Rebin(bin_ranges.size()-1,"miss_rebin_check",ranges_for_fill_gen) ;

  //add data and BG after done.


  for(int iii=0;iii<bin_ranges.size();iii++){
    matrix_rebin->SetBinContent(iii+1,0,miss_rebin->GetBinContent(iii+1));
  }


  TUnfoldSys tunfold(matrix_rebin, TUnfold::kHistMapOutputHoriz, TUnfold::kRegModeCurvature);
//  tunfold.SetInput(rec_unf_rebin);




  TH1D* eff_acc=(TH1D*)gen_Rec_rebin->Clone("eff_acc");
  eff_acc->Divide(eff_acc,gen_rebin,1,1);
  TH1D* stability_before= (TH1D*)rec->Clone("stability_before");
  TH1D* purity_before= (TH1D*)rec->Clone("purity_before");

  TH1D* stability_after= (TH1D*)gen_rebin->Clone("stability_after");
  TH1D* purity_after= (TH1D*)gen_rebin->Clone("purity_after");

  for(int bin=1;bin<=rec->GetNbinsX();bin++){
    double recbincont=matrix->Integral(bin,bin,1,rec->GetNbinsX());
    double recbinprojcont=matrix->Integral(bin,bin,bin,bin);
    double genbincont=matrix->Integral(1,rec->GetNbinsX(),bin,bin);
    double stabilityy=0.;
    double purityy=0.;
     if(recbincont!=0)stabilityy=recbinprojcont/recbincont;
     if(genbincont!=0)purityy=recbinprojcont/genbincont;
    stability_before->SetBinContent(bin,stabilityy);
    purity_before->SetBinContent(bin,purityy);
    stability_before->SetBinError(bin,0);
    purity_before->SetBinError(bin,0);
    if(bin<=stability_after->GetNbinsX()){
      stability_after->SetBinContent(bin,stab_vec[bin-1]);
      purity_after->SetBinContent(bin,pur_vec[bin-1]);
      stability_after->SetBinError(bin,0);
      purity_after->SetBinError(bin,0);
    }
  }

  







  stability_before->SetLineColor(kRed);
  stability_after->SetLineColor(kRed);
  purity_before->SetLineColor(kGreen);
  purity_after->SetLineColor(kGreen);

  TLegend *leg1= new TLegend(0.7531567,0.653719,0.904980511,0.885385);
  leg1->SetBorderSize(0);
  leg1->SetFillColor(kWhite);
  leg1->SetTextSize(0.0351);
  leg1->AddEntry(purity_after, "purity","l");
  leg1->AddEntry(stability_after, "stability","l");

  purity_after->SetLineStyle(5);
  purity_before->SetLineStyle(5);
 TCanvas *c1=new TCanvas("c1","c1",800,800);
  c1->cd();
  gPad->SetLogz();
  matrix->GetXaxis()->SetTitle("rec");
  matrix->GetYaxis()->SetTitle("gen");
  matrix->GetYaxis()->SetTitleOffset(1.5);
  matrix->Draw("colz");
  c1->Print("before_rebin.pdf");
  TCanvas *c2=new TCanvas("c2","c2",800,800);
  c2->cd();
  gPad->SetLogz();
  matrix_rebin->GetXaxis()->SetTitle("gen");
  matrix_rebin->GetYaxis()->SetTitle("rec");
  matrix_rebin->GetYaxis()->SetTitleOffset(0.8);
  matrix_rebin->Draw("colz");
  c2->Print("after_rebin.pdf");
  TCanvas *c3=new TCanvas("c3","c3",800,800);
  c3->cd();
  purity_after->Draw();
  stability_after->Draw("same");
  leg1->Draw("same");
  c3->Print("sta_pur_after.pdf");
  TCanvas *c4=new TCanvas("c4","c4",800,800);
  c4->cd();
  purity_before->Draw();
  stability_before->Draw("same");
  purity_before->GetXaxis()->SetRangeUser(ranges_for_fill_gen[0],ranges_for_fill_gen[bin_ranges.size()]);

  leg1->Draw("same");
  c4->Print("sta_pur_before.pdf");
TCanvas *c5=new TCanvas("c5","c5",800,800);
  c5->cd();
eff_acc->Draw();
  c4->Print("eff_acc_before.pdf");
}
