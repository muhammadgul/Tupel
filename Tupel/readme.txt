Instructions for ntuple Producer
ssh -Y <uname>@lxplus.cern.ch
cmsrel CMSSW_7_0_9_patch2
cd CMSSW_7_0_9_patch2/src
cmsenv

git clone git@github.com:UGent/Tupel

scram b -j 10

// eos mount (active for ~24 hours)
mkdir ~/eos
eosmount ~/eos

cd /Tupel/Tupel/
cmsRun run_cfg.py
(or crab ...)


