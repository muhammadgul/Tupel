Instructions for ntuple Producer
ssh -Y <uname>@lxplus.cern.ch
cmsrel CMSSW_7_4_1
cd CMSSW_7_4_1/src
cmsenv

git clone -b Tupel_MiniAOD_TTbar git@github.com:UGent/Tupel

scram b -j 10

// eos mount (active for ~24 hours)
mkdir ~/eos
eosmount ~/eos

cd /Tupel/Tupel/
cmsRun simple_run_cfg.py
(or crab ...)


