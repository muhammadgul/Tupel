import FWCore.ParameterSet.Config as cms

process = cms.Process("BAOBAB")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring("/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/0C765598-8BD1-E511-BF63-20CF3027A566.root")
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('ntuple.root' )
)

# Load the standard set of configuration modules
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '76X_mcRun2_asymptotic_RunIIFall15DR76_v1', '')


process.tupel = cms.EDAnalyzer("Tupel",
  triggerEvent = cms.InputTag( "patTriggerEvent" ),
  candidateSw  = cms.untracked.string("off"), #on, off, or withTrack
  candidateSrc = cms.untracked.InputTag("packedPFCandidates"),
  photonSw     = cms.untracked.string("on"), #on or off
  photonSrc    = cms.untracked.InputTag("slimmedPhotons"),
  electronSrc  = cms.untracked.InputTag("slimmedElectrons"),
  muonSrc      = cms.untracked.InputTag("slimmedMuons"),
  tauSrc       = cms.untracked.InputTag("slimmedTaus"),
  jetSrc       = cms.untracked.InputTag("slimmedJets"),
  fatJetSw     = cms.untracked.string("on"),
  fatJetSrc    = cms.untracked.InputTag("slimmedJetsAK8"),
  genSrc       = cms.untracked.InputTag("prunedGenParticles"),
  gjetSrc      = cms.untracked.InputTag('slimmedGenJets'),
  gfatJetSrc   = cms.untracked.InputTag('slimmedGenJetsAK8'),
  muonMatch    = cms.string( 'muonTriggerMatchHLTMuons' ),
  muonMatch2   = cms.string( 'muonTriggerMatchHLTMuons2' ),
  elecMatch    = cms.string( 'elecTriggerMatchHLTElecs' ),
  mSrcRho      = cms.untracked.InputTag('fixedGridRhoFastjetAll'),#arbitrary rho now
  CalojetLabel = cms.untracked.InputTag('slimmedJets'), #same collection now BB 
  metSrcs      = cms.VInputTag("slimmedMETs","slimmedMETsNoHF","slimmedMETsPuppi"),
  lheSrc       = cms.untracked.InputTag('source'),
  puSrc        = cms.untracked.InputTag('slimmedAddPileupInfo'),
  puMvaName    = cms.untracked.string('pileupJetId:fullDiscriminan'),
  puJetIdSrc   = cms.untracked.InputTag("pileupJetId"),
  pvSrc        = cms.untracked.InputTag('goodOfflinePrimaryVertices'),
  reducedBarrelRecHitCollection = cms.InputTag("reducedEgamma","reducedEBRecHits"),
  reducedEndcapRecHitCollection = cms.InputTag("reducedEgamma","reducedEERecHits"),
  reducedPreshowerRecHitCollection = cms.InputTag("reducedEgamma","reducedESRecHits")
)

from PhysicsTools.SelectorUtils.pvSelector_cfi import pvSelector
process.goodOfflinePrimaryVertices = cms.EDFilter(
    "PrimaryVertexObjectFilter",
    filterParams = pvSelector.clone( minNdof = cms.double(4.0), maxZ = cms.double(24.0) ),
    src=cms.InputTag('offlineSlimmedPrimaryVertices')
    )


process.p = cms.Path(
 process.tupel 
)

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10
process.MessageLogger.suppressWarning = cms.untracked.vstring('ecalLaserCorrFilter','manystripclus53X','toomanystripclus53X')
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.options.allowUnscheduled = cms.untracked.bool(True)
