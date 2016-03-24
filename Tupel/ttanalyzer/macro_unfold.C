void macro_unfold(){

  TFile *mc_ss = TFile::Open("25ns_tt_uev_miniaodv2_20160307_fromskimmed_isElec_0_v24.root");

  TH2D * matrix_tmp =(TH2D*) mc_ss->Get("2d_npf_1");

  TH2D * matrix =(TH2D*) matrix_tmp->Clone("matrix");
  matrix->Draw("colz");

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

    cout<<"aiaiai "<<matrix->Integral(50,50,50,50)<<"  "<< matrix->GetBinContent(50,50)<<endl;
  int bin_check=0;
  vector<int> bin_ranges;
  for(int bin=1;bin<=rec->GetNbinsX();bin++){

    if(bin<=bin_check)continue;
    double recbincont=matrix->Integral(bin,bin,1,rec->GetNbinsX());
    double recbinprojcont=matrix->Integral(bin,bin,bin,bin);
    double genbincont=matrix->Integral(1,rec->GetNbinsX(),bin,bin);


    bin_ranges.push_back(bin_check);
    cout<<bin_check<<endl;
    for(int binn=bin+1;binn<=rec->GetNbinsX();binn++){
      double stabilityy=recbinprojcont/recbincont;
      double purityy=recbinprojcont/genbincont;
      bin_check=binn;
      if(stabilityy>=0.45&&purityy>=0.45){
        break;
        
      }
        recbinprojcont=matrix->Integral(bin,binn,bin,binn);
        recbincont=matrix->Integral(bin,binn,1,rec->GetNbinsX());
        genbincont=matrix->Integral(1,rec->GetNbinsX(),bin,binn);

    }
  }

  //rebinning using bin edge info obtained
}
