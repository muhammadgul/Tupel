   TH1* h_jettheta[][][][];
   TH1* h_gen_jettheta[][][][];
   double cut_rapidity[]={0,0.5,1.0};
   double cut_de[]={0,50,120};
   char name[10000];
   for(int i = 0; i<2;i++){//pos / neg
     for(int j = 0; j<8;j++){//flavor
       for(int k = 0; k<2;k++){//jet rapidity cut
         for(int l = 0; l<3;l++){// ttj rapidity cut
           for(int l = 0; l<3;l++){//de
          sprintf(name,"v_jettheta_%i_%i_%i_%i_%i",i,j,k,l,m);
          h_jettheta[i][j][k][l]=new TH1D (name,name,20,0,3.14);
          sprintf(name,"v_gen_jettheta_%i_%i_%i_%i_%i",i,j,k,l,m);
          h_gen_jettheta[i][j][k][l]=new TH1D (name,name,20,0,3.14);
         }
       }
     }
   }
