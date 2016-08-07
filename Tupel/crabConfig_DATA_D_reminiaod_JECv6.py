from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'test60data_20160302_newD_oldjec_v4'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'simple_run_data_jecv6_cfg.py'
#config.JobType.scriptExe = 'job_crab.sh'
#config.JobType.outputFiles=['events_presys.lhe']
config.JobType.inputFiles = ['Summer15_25nsV6_DATA.db','Summer15_25nsV6_MC.db','Summer15_25nsV6_DATA_Uncertainty_AK4PFchs.txt']

config.section_("Data")
#config.Data.inputDataset = '/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/MINIAODSIM'
config.Data.inputDataset = '/SingleMuon/Run2015D-05Oct2015-v1/MINIAOD'
#config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 10
config.Data.totalUnits= -1
#config.Data.lumiMask= '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions15/13TeV/Cert_246908-258159_13TeV_PromptReco_Collisions15_25ns_JSON_v3.txt'
config.Data.lumiMask= '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions15/13TeV/Cert_246908-260627_13TeV_PromptReco_Collisions15_25ns_JSON.txt'

config.Data.outLFNDirBase = '/store/group/phys_top/bbilin/n-tupel/25ns_pf_reduced_01022016'
config.Data.publication = False
config.Data.outputDatasetTag = 'SingleMuon_Run2015D-05Oct2015-v1_JECv6'
#config.Data.primaryDataset='CRAB_PrivateMC'
config.section_("Site")
config.Site.storageSite = 'T2_CH_CERN'
#config.Site.whitelist = ["T2_US_Nebraska"]
