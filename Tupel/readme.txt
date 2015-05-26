Instructions for ntuple Producer
ssh -Y <uname>@lxplus.cern.ch
cmsrel CMSSW_7_2_0
cd CMSSW_7_2_0/src
cmsenv

git clone -b Tupel_MiniAOD git@github.com:UGent/Tupel

scram b -j 10

// eos mount (active for ~24 hours)
mkdir ~/eos
eosmount ~/eos

cd /Tupel/Tupel/
cmsRun simple_run_cfg.py
(or crab ...)


