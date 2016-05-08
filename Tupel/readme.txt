Instructions for ntuple Producer
ssh -Y <uname>@lxplus.cern.ch
cmsrel CMSSW_7_6_5
cd CMSSW_7_6_5/src
cmsenv
git-cms-merge-topic 13960
//to fetch the most recent pseudotop producer.
git clone -b Tupel_MiniAOD_TTbar_76X git@github.com:UGent/Tupel

scram b -j 10

// eos mount (active for ~24 hours)
mkdir ~/eos
eosmount ~/eos

cd /Tupel/Tupel/
cmsRun simple_run_76X_cfg.py
cmsRun simple_run_76X_data_cfg.py
(or crab ...)

extra info:

  channel    = cms.string( 'smu' ), 

is for skimming the trees at production level. Options:
dimu, smu, dielec,selec, 
for no skimming, use noselection

  keepparticlecoll    = cms.bool(False),
to keep the particle flow objects and gen level particles. Needed for UE studies. To keep, switch to True
