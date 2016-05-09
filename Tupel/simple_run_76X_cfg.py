import FWCore.ParameterSet.Config as cms
process = cms.Process("S2")
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.load('JetMETCorrections.Configuration.DefaultJEC_cff')
from JetMETCorrections.Configuration.DefaultJEC_cff import *
from JetMETCorrections.Configuration.JetCorrectionServices_cff import *
runOnData= False #True #data/MC switch

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag

#taken from https://twiki.cern.ch/twiki/bin/viewauth/CMS/JECDataMC
if runOnData:
	process.GlobalTag = GlobalTag(process.GlobalTag, '76X_dataRun2_16Dec2015_v0') #for 25 ns data
else: 
	process.GlobalTag = GlobalTag(process.GlobalTag, '76X_mcRun2_asymptotic_RunIIFall15DR76_v1') #for 25ns mc

#process.load('Configuration.StandardSequences.Services_cff')
#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#process.GlobalTag.globaltag = '76X_mcRun2_asymptotic_RunIIFall15DR76_v1::All'


#jecunctable_="Summer15_25nsV6_DATA_Uncertainty_AK4PFchs.txt"



process.source = cms.Source("PoolSource",
#    fileNames = cms.untracked.vstring("/store/mc/RunIISpring15DR74/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/00000/0066F143-F8FD-E411-9A0B-D4AE526A0D2E.root")
  fileNames = cms.untracked.vstring("/store/mc/RunIIFall15MiniAODv2/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext3-v1/00000/00DF0A73-17C2-E511-B086-E41D2D08DE30.root")
)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )

#from CondCore.DBCommon.CondDBSetup_cfi import *
#import os
#if runOnData:#
#	jecfile="Summer15_50nsV4_DATA"
#else:
#	jecfile="Summer15_50nsV4_MC"

#dBFile = os.path.expandvars(jecfile+".db")
#process.jec = cms.ESSource("PoolDBESSource",CondDBSetup,
#  #connect = cms.string( "sqlite_file://"+dBFile ),
#  connect = cms.string( "sqlite:"+dBFile),
#  toGet =  cms.VPSet(
#  cms.PSet(
#    record = cms.string("JetCorrectionsRecord"),
#    tag = cms.string("JetCorrectorParametersCollection_"+jecfile+"_AK4PF"),
#    label= cms.untracked.string("AK4PF")
#    ),
#  cms.PSet(
#    record = cms.string("JetCorrectionsRecord"),
#    tag = cms.string("JetCorrectorParametersCollection_"+jecfile+"_AK4PF"),
#    label= cms.untracked.string("AK4PFchs")
#    ),
#  )
#  )
#process.es_prefer_jec = cms.ESPrefer("PoolDBESSource",'jec')
#process.load("PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff")
#process.patJetCorrFactorsReapplyJEC = process.patJetCorrFactorsUpdated.clone(
#  src = cms.InputTag("slimmedJets"),
#  levels = ['L1FastJet','L2Relative', 'L3Absolute', 'L2L3Residual'],#residual on data only.
#  payload = 'AK4PFchs' ) # Make sure to choose the appropriate levels and payload here!

#from PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff import patJetsUpdated
#process.patJetsReapplyJEC = process.patJetsUpdated.clone(
#  jetSource = cms.InputTag("slimmedJets"),
#  jetCorrFactorsSource = cms.VInputTag(cms.InputTag("patJetCorrFactorsReapplyJEC"))

#  )
#process.reapplyJEC = cms.Sequence( process.patJetCorrFactorsReapplyJEC + process.patJetsReapplyJEC)
########################################

from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection

updateJetCollection(
   process,
   jetSource = cms.InputTag('slimmedJets'),
   labelName = 'UpdatedJEC',
   jetCorrections = ('AK4PFchs', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute']), 'None')  # Do not forget 'L2L3Residual' on data!
)


process.pseudoTop = cms.EDProducer("PseudoTopProducer",
    finalStates = cms.InputTag("packedGenParticles"),
    genParticles = cms.InputTag("prunedGenParticles"),
    jetConeSize = cms.double(0.4),
    maxJetEta = cms.double(2.4),
    minJetPt = cms.double(20),
    leptonConeSize = cms.double(0.1),

     minLeptonPt = cms.double(20),#new?
     maxLeptonEta= cms.double(2.4),#new?
     minLeptonPtDilepton = cms.double(20),#new?
     maxLeptonEtaDilepton= cms.double(2.4),#new?
     minDileptonMassDilepton= cms.double(0.),#new?
     minLeptonPtSemilepton = cms.double(20),#new?
     maxLeptonEtaSemilepton= cms.double(2.4),#new?
     minVetoLeptonPtSemilepton= cms.double(15.),#new?
     maxVetoLeptonEtaSemilepton= cms.double(2.4),#new?
     minMETSemiLepton=cms.double(0.),#new?
     minMtWSemiLepton=cms.double(0.),#new?
    tMass = cms.double(172.5),
    wMass = cms.double(80.4)
)

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('withJEC_DYJetsToLL_ntuple.root' )
)

#process.selectedMuons = cms.EDFilter("CandPtrSelector", src = cms.InputTag("slimmedMuons"), cut = cms.string('''abs(eta)<2.5 && pt>10. &&
#    (pfIsolationR04().sumChargedHadronPt+
#     max(0.,pfIsolationR04().sumNeutralHadronEt+
#     pfIsolationR04().sumPhotonEt-
#     0.50*pfIsolationR04().sumPUPt))/pt < 0.20 && 
#     (isPFMuon && (isGlobalMuon || isTrackerMuon) )'''))

#process.selectedElectrons = cms.EDFilter("CandPtrSelector", src = cms.InputTag("slimmedElectrons"), cut = cms.string('''abs(eta)<2.5 && pt>20. &&
#     gsfTrack.isAvailable() &&
#     gsfTrack.hitPattern().numberOfLostHits(\'MISSING_INNER_HITS\') < 2 &&
#     (pfIsolationVariables().sumChargedHadronPt+
#     max(0.,pfIsolationVariables().sumNeutralHadronEt+
#     pfIsolationVariables().sumPhotonEt-
#     0.5*pfIsolationVariables().sumPUPt))/pt < 0.15'''))
 
#process.patJetPartons.particles=cms.InputTag("prunedGenParticles")
#process.patJetPartonMatch.matched = cms.InputTag("prunedGenParticles")
#process.patJetCorrFactors.primaryVertices=cms.InputTag("offlineSlimmedPrimaryVertices")

jetsrcc="updatedPatJetsUpdatedJEC"

process.tupel = cms.EDAnalyzer("Tupel",
#  trigger      = cms.InputTag( "patTrigger" ),
  triggerEvent = cms.InputTag( "patTriggerEvent" ),
  #triggerSummaryLabel = cms.InputTag("hltTriggerSummaryAOD","","HLT"), 
  photonSrc   = cms.InputTag("slimmedPhotons"),
  electronSrc = cms.InputTag("slimmedElectrons"),
  muonSrc     = cms.InputTag("slimmedMuons"),
  #tauSrc      = cms.untracked.InputTag("slimmedPatTaus"),
#  jetSrc      = cms.untracked.InputTag("slimmedJets"),
    pfcandSrc	   = cms.InputTag("packedPFCandidates"),
    jetSrc      = cms.InputTag(jetsrcc),
  metSrc      = cms.InputTag("patMETsPF"),
  genSrc      = cms.InputTag("prunedGenParticles"),
 pgenSrc       =cms.InputTag("packedGenParticles"),
  gjetSrc       = cms.InputTag('slimmedGenJets'),
  muonMatch    = cms.string( 'muonTriggerMatchHLTMuons' ),
  muonMatch2    = cms.string( 'muonTriggerMatchHLTMuons2' ),
  elecMatch    = cms.string( 'elecTriggerMatchHLTElecs' ),
  channel    = cms.string( 'smu' ),
  keepparticlecoll    = cms.bool(True),
  mSrcRho      = cms.InputTag('fixedGridRhoFastjetAll'),#arbitrary rho now
  CalojetLabel = cms.InputTag('slimmedJets'), #same collection now BB 
#  jecunctable = cms.string(jecunctable_),
  #metSource = cms.VInputTag("slimmedMETs","slimmedMETs","slimmedMETs","slimmedMETs"), #no MET corr yet
  metSource = cms.VInputTag("slimmedMETs","slimmedMETsPuppi"),
  lheSource=cms.InputTag('source')

)

from PhysicsTools.SelectorUtils.pvSelector_cfi import pvSelector
process.goodOfflinePrimaryVertices = cms.EDFilter(
    "PrimaryVertexObjectFilter",
    filterParams = pvSelector.clone( minNdof = cms.double(4.0), maxZ = cms.double(24.0) ),
    src=cms.InputTag('offlineSlimmedPrimaryVertices')
    )


#process.load('RecoJets.Configuration.RecoPFJets_cff')
#-------------------- Turn-on the FastJet density calculation -----------------------
#process.kt6PFJets.doRhoFastjet = True

process.p = cms.Path(
#    process.patJets
# + process.patMETs
# + process.inclusiveSecondaryVertexFinderTagInfos
#+process.selectedMuons
#+process.selectedElectrons 
# +process.goodOfflinePrimaryVertices 
#+process.kt6PFJets
process.pseudoTop
+ process.tupel 
)

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10
process.MessageLogger.suppressWarning = cms.untracked.vstring('ecalLaserCorrFilter','manystripclus53X','toomanystripclus53X')
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.options.allowUnscheduled = cms.untracked.bool(True)


process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('test.root'),
#    outputCommands = cms.untracked.vstring(['drop *','keep patJets_patJets_*_*','keep *_*_*_PAT','keep recoTracks_unp*_*_*','keep recoVertexs_unp*_*_*'])
    outputCommands = cms.untracked.vstring(['drop *'])
)
#process.endpath= cms.EndPath(process.out)


#from PhysicsTools.PatAlgos.tools.trigTools import *
#switchOnTrigger( process ) # This is optional and can be omitted.

# Switch to selected PAT objects in the trigger matching
#removeCleaningFromTriggerMatching( process )
##############################
iFileName = "fileNameDump_cfg.py"
file = open(iFileName,'w')
file.write(str(process.dumpPython()))
file.close()


