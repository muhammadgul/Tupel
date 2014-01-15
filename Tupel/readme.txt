Instructions for ntuple Producer

setenv CVSROOT ":ext:<cern-user-account>@lxplus5.cern.ch:/afs/cern.ch/user/c/cvscmssw/public/CMSSW"
if you are using bash:
export CVSROOT=":ext:<cern-user-account>@lxplus5.cern.ch:/afs/cern.ch/user/c/cvscmssw/public/CMSSW"


cmsrel CMSSW_5_3_11
cd CMSSW_5_3_11/src
cmsenv

cvs co -r V00-11-17      DPGAnalysis/SiStripTools                         
cvs co -r V01-00-11-01   DPGAnalysis/Skims                                
cvs co -r V06-05-06-12   DataFormats/PatCandidates                        
cvs co -r V00-00-08      DataFormats/TrackerCommon                        
cvs co -r V08-09-62      PhysicsTools/PatAlgos                            
cvs co -r V03-09-28      PhysicsTools/PatUtils         
cvs co -r V00-07-03      RecoBTag/Configuration                           
cvs co -r V01-04-09      RecoBTag/ImpactParameter            
cvs co RecoBTag/PerformanceMeasurements             
cvs co -r V01-10-02      RecoBTag/SecondaryVertex                         
cvs co -r V05-09-02      RecoBTag/SoftLepton                              
cvs co -r V02-03-00      RecoBTau/JetTagComputer                          
cvs co -r V09-00-01      RecoEgamma/EgammaTools                           
cvs co -r V01-09-05      RecoLocalTracker/SubCollectionProducers          
cvs co -r V00-00-08      RecoMET/METAnalyzers                             
cvs co -r V00-00-13-01   RecoMET/METFilters                               
cvs co -r V03-03-12-02   RecoMET/METProducers                             
cvs co -r V15-02-06      RecoParticleFlow/PFProducer                    
cvs co -r V01-04-14      RecoTauTag/Configuration                        
cvs co -r V01-04-26      RecoTauTag/RecoTau                               
cvs co -r V02-02-06      RecoVertex/AdaptiveVertexFinder                  
cvs co -r V00-09-03      SHarper/HEEPAnalyzer                             
cvs co -r V00-02-03s     TauAnalysis/CandidateTools                       
git clone git@github.com:h2gglobe/External CMGTools/External
git clone git@github.com:cms-analysis/EgammaAnalysis-ElectronTools EgammaAnalysis/ElectronTools
git clone git@github.com:UGent/Tupel
cd EgammaAnalysis/ElectronTools/data
cat download.url | xargs wget​
cd -
in CMGTools/External/python/puJetIDAlgo_cff.py: change "RecoJets/JetProducers" --> "CMGTools/External" 

scram b -j 10

// eos mount (active for ~24 hours)
mkdir ~/eos
eosmount ~/eos

cd test
cmsRun config_final_mc_cfg.py
