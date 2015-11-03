TH1 * tmphdata  =(TH1D*)(data->Get(var));
TH1 * tmphmc_s  =(TH1D*)(mc_s->Get(var));
TH1 * tmphmc_o  =(TH1D*)(mc_o->Get(var));
TH1 * tmphst_t_t  =(TH1D*)(st_t_t->Get(var));
TH1 * tmphst_t_tbar  =(TH1D*)(st_t_tbar->Get(var));
TH1 * tmphst_tw_t  =(TH1D*)(st_tw_t->Get(var));
TH1 * tmphst_tw_tbar  =(TH1D*)(st_tw_tbar->Get(var));
TH1 * tmphwjet  =(TH1D*)(wjet->Get(var));

TH1 * tmphdata2  =(TH1D*)(data->Get(var2));
TH1 * tmphmc_s2  =(TH1D*)(mc_s->Get(var2));
TH1 * tmphmc_o2  =(TH1D*)(mc_o->Get(var2));
TH1 * tmphst_t_t2  =(TH1D*)(st_t_t->Get(var2));
TH1 * tmphst_t_tbar2  =(TH1D*)(st_t_tbar->Get(var2));
TH1 * tmphst_tw_t2  =(TH1D*)(st_tw_t->Get(var2));
TH1 * tmphst_tw_tbar2  =(TH1D*)(st_tw_tbar->Get(var2));
TH1 * tmphwjet2  =(TH1D*)(wjet->Get(var2));

TH1D* hdata= (TH1D*)tmphdata->Clone("");
TH1D* hmc_s= (TH1D*)tmphmc_s->Clone("");
TH1D* hmc_o = (TH1D*)tmphmc_o->Clone("");
TH1D* hst_t_t= (TH1D*)tmphst_t_t->Clone("");
TH1D* hst_t_tbar = (TH1D*)tmphst_t_tbar->Clone("");
TH1D* hst_tw_t = (TH1D*)tmphst_tw_t->Clone("");
TH1D* hst_tw_tbar = (TH1D*)tmphst_tw_tbar->Clone("");
TH1D* hwjet = (TH1D*)tmphwjet->Clone("");
