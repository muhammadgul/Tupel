      vector<TLorentzVector>gen_lepton_vector;
      vector<TLorentzVector>gen_nu_vector;
      vector<TLorentzVector>gen_light_jet_vector;
      vector<TLorentzVector>gen_b_jet_vector;
      vector<int> gen_b_jet_id;
      TLorentzVector gen_top_vector;
      TLorentzVector gen_atop_vector;
      vector<int> gen_lepton_id;
      unsigned int ind_check=-99;
      for(unsigned int st1_ind=0; st1_ind<Bare01LepPt->size();st1_ind++){
        if(st1_ind==ind_check) continue;
        //if(Bare01LepPt->at(st1_ind)<20)continue;
        int lep_id= Bare01LepId->at(st1_ind);
        TLorentzVector lep_tmp;
        lep_tmp.SetPtEtaPhiE(Bare01LepPt->at(st1_ind),Bare01LepEt->at(st1_ind),Bare01LepPhi->at(st1_ind),Bare01LepE->at(st1_ind));
       // cout<<st1_ind<<	"  "<<lep_id<<"  "<<endl;
        for(unsigned int st1_ind_2=st1_ind; st1_ind_2<Bare01LepPt->size();st1_ind_2++){

          TLorentzVector nu_tmp;
          nu_tmp.SetPtEtaPhiE(Bare01LepPt->at(st1_ind_2),Bare01LepEt->at(st1_ind_2),Bare01LepPhi->at(st1_ind_2),Bare01LepE->at(st1_ind_2));
          int nu_id= Bare01LepId->at(st1_ind_2);
          if((fabs(lep_id)==11 || fabs(lep_id)==13 )&&lep_id*nu_id<0 && (fabs(nu_id)-fabs(lep_id))==1){
            gen_lepton_id.push_back(lep_id);
            gen_lepton_vector.push_back(lep_tmp);
            gen_nu_vector.push_back(nu_tmp);
            ind_check=st1_ind_2;
            break;
          }
         if((fabs(lep_id)==12 || fabs(lep_id)==14 )&&lep_id*nu_id<0 && (fabs(lep_id)-fabs(nu_id))==1){
            gen_lepton_id.push_back(nu_id);
            gen_lepton_vector.push_back(nu_tmp);
            gen_nu_vector.push_back(lep_tmp);
            ind_check=st1_ind_2;
            break;
          }
        }    
      }


      for(unsigned int jet_ind=0; jet_ind<GjPt->size();jet_ind++){ 
        if(GjPt->at(jet_ind)<30&& GjEta->at(jet_ind)>2.5)continue;
        bool match_lep=false;
        bool match_b=false;
        TLorentzVector jet_tmp;
        jet_tmp.SetPtEtaPhiE(GjPt->at(jet_ind),Gjeta->at(jet_ind),Gjphi->at(jet_ind),GjE->at(jet_ind));
        if(gen_lepton_vector.size()==1){
            double deltaR1=DeltaR(jet_tmp.Eta(),gen_lepton_vector[0].Eta(),jet_tmp.Phi(),gen_lepton_vector[0].Phi());
            double deltaR2=DeltaR(jet_tmp.Eta(),gen_nu_vector[0].Eta(),jet_tmp.Phi(),gen_nu_vector[0].Phi());
            if(deltaR1<0.5 ||deltaR2<0.5){
              match_lep=true;
            }
            if(match_lep)continue;
        }


        int id_b=0;
        for(unsigned int st3_ind=0; st3_ind<St03Pt->size();st3_ind++){
          if(fabs(St03Id->at(st3_ind))==5){
            TLorentzVector lep_tmp;
            lep_tmp.SetPtEtaPhiE(St03Pt->at(st3_ind),St03Eta->at(st3_ind),St03Phi->at(st3_ind),St03E->at(st3_ind));
            double deltaR=DeltaR(jet_tmp.Eta(),lep_tmp.Eta(),jet_tmp.Phi(),lep_tmp.Phi());
            if(deltaR<0.1){
              //cout<<St03Id->at(st3_ind)<<"  "<<deltaR<<endl;
              match_b=true;
              id_b=St03Id->at(st3_ind);
            }
          }          
        }
        if(match_b){
          gen_b_jet_vector.push_back(jet_tmp);
          gen_b_jet_id.push_back(id_b);
        }

       if(!match_b){
          double deltaR_ljet_st3q=DeltaR(jet_tmp.Eta(),extra_parton_vector.Eta(),jet_tmp.Phi(),extra_parton_vector.Phi());
          /*if(!(deltaR_ljet_st3q<0.1 &&(fabs(extra_parton_id)==21 ||fabs(extra_parton_id)<6) ))*/gen_light_jet_vector.push_back(jet_tmp);
        }
      }


      if(gen_lepton_id.size()==1 && gen_b_jet_vector.size()==2 && gen_light_jet_vectors.size()>=2 ){//gen level l+jet
        for(unsigned int indljet=0;indljet<gen_light_jet_vectors.size();indljet++){

        }
      }
