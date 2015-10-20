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
#from Configuration.AlCa.GlobalTag import GlobalTag
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag

if runOnData:
	process.GlobalTag = GlobalTag(process.GlobalTag, '74X_dataRun2_v2') #for 25 ns data
else: 
	process.GlobalTag = GlobalTag(process.GlobalTag, '74X_mcRun2_asymptotic_v2') #for 25ns mc


process.source = cms.Source("PoolSource",
#    fileNames = cms.untracked.vstring("/store/mc/RunIISpring15DR74/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/00000/0066F143-F8FD-E411-9A0B-D4AE526A0D2E.root")
  fileNames = cms.untracked.vstring("/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/00000/0AB045B5-BB0C-E511-81FD-0025905A60B8.root")
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
process.load("PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff")
process.patJetCorrFactorsReapplyJEC = process.patJetCorrFactorsUpdated.clone(
  src = cms.InputTag("slimmedJets"),
  levels = ['L1FastJet','L2Relative', 'L3Absolute', 'L2L3Residual'],
  payload = 'AK4PFchs' ) # Make sure to choose the appropriate levels and payload here!

from PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff import patJetsUpdated
process.patJetsReapplyJEC = process.patJetsUpdated.clone(
  jetSource = cms.InputTag("slimmedJets"),
  jetCorrFactorsSource = cms.VInputTag(cms.InputTag("patJetCorrFactorsReapplyJEC"))

  )
process.reapplyJEC = cms.Sequence( process.patJetCorrFactorsReapplyJEC + process.patJetsReapplyJEC)
########################################
#from RecoJets.JetProducers.ak5PFJets_cfi import ak5PFJets
#from RecoJets.JetProducers.ak4PFJets_cfi import ak4PFJets
#from RecoJets.JetProducers.ak5GenJets_cfi import ak5GenJets
#from RecoJets.JetProducers.ak4GenJets_cfi import ak4GenJets
#from RecoMET.METProducers.PFMET_cfi import pfMet

#process.chs = cms.EDFilter("CandPtrSelector", src = cms.InputTag("packedPFCandidates"), cut = cms.string("fromPV"))

#process.ak5PFJets = ak5PFJets.clone(src = 'packedPFCandidates', doAreaFastjet = True) # no idea while doArea is false by default, but it's True in RECO so we have to set it
#process.ak5PFJetsCHS = ak5PFJets.clone(src = 'chs', doAreaFastjet = True) # no idea while doArea is false by default, but it's True in RECO so we have to set it
#process.ak4PFJetsCHS = ak4PFJets.clone(src = 'chs', doAreaFastjet = True)
#process.ak5GenJets = ak5GenJets.clone(src = 'packedGenParticles')
#process.ak4GenJets = ak5GenJets.clone(src = 'packedGenParticles')
#process.pfMet = pfMet.clone(src = "packedPFCandidates")
#process.pfMet.calculateSignificance = False # this can't be easily implemented on packed PF candidates at the moment

#process.load("PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff")
#process.load("Configuration.EventContent.EventContent_cff")
#process.load('Configuration.StandardSequences.Geometry_cff')
#process.load('Configuration.StandardSequences.MagneticField_38T_cff')
#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#process.GlobalTag.globaltag = 'PHYS14_25_V1::All'


#process.load("RecoJets.JetAssociationProducers.ak5JTA_cff")
#process.load("RecoJets.JetAssociationProducers.ak4JTA_cff")
#process.patJets.addJetCharge   = False
#process.patJets.addBTagInfo    = True
#process.patJets.getJetMCFlavour = False
#process.patJets.addAssociatedTracks = False
#process.patJetPartonMatch.matched = "prunedGenParticles"
#process.patJetCorrFactors.primaryVertices = "offlineSlimmedPrimaryVertices"
#process.patMETs.addGenMET = False # There's no point in recalculating this, and we can't remake it since we don't have genParticles beyond |eta|=5

#process.load('RecoBTag.Configuration.RecoBTag_cff')
#process.load('RecoJets.Configuration.RecoJetAssociations_cff')

#process.load('PhysicsTools.PatAlgos.slimming.unpackedTracksAndVertices_cfi')

#process.ak5JetTracksAssociatorAtVertexPF.jets = cms.InputTag("ak5PFJetsCHS")
#process.ak5JetTracksAssociatorAtVertexPF.tracks = cms.InputTag("unpackedTracksAndVertices")
#process.ak4JetTracksAssociatorAtVertexPF.jets = cms.InputTag("ak4PFJetsCHS")
#process.ak4JetTracksAssociatorAtVertexPF.tracks = cms.InputTag("unpackedTracksAndVertices")
#process.impactParameterTagInfos.primaryVertex = cms.InputTag("unpackedTracksAndVertices")
#process.pfImpactParameterTagInfos.primaryVertex=cms.InputTag("unpackedTracksAndVertices")

#process.patJets.discriminatorSources = cms.VInputTag(cms.InputTag("jetBProbabilityBJetTags"),
# cms.InputTag("jetProbabilityBJetTags"), 
#cms.InputTag("trackCountingHighPurBJetTags"),
# cms.InputTag("trackCountingHighEffBJetTags"), 
#cms.InputTag("simpleSecondaryVertexHighEffBJetTags"), 
#cms.InputTag("simpleSecondaryVertexHighPurBJetTags"),
# cms.InputTag("combinedInclusiveSecondaryVertexV2BJetTags"),
# cms.InputTag("combinedSecondaryVertexBJetTags")
#,cms.InputTag("combinedMVABJetTags")
#) 


#process.inclusiveSecondaryVertexFinderTagInfos.extSVCollection = cms.InputTag("unpackedTracksAndVertices","secondary","")
#process.combinedSecondaryVertex.trackMultiplicityMin = 1 #silly sv, uses un filtered tracks.. i.e. any pt

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

if runOnData:
    jetsrcc="slimmedJets"
else :
    jetsrcc="patJetsReapplyJEC"

process.tupel = cms.EDAnalyzer("Tupel",
#  trigger      = cms.InputTag( "patTrigger" ),
  triggerEvent = cms.InputTag( "patTriggerEvent" ),
  #triggerSummaryLabel = cms.InputTag("hltTriggerSummaryAOD","","HLT"), 
  photonSrc   = cms.untracked.InputTag("slimmedPhotons"),
  electronSrc = cms.untracked.InputTag("slimmedElectrons"),
  muonSrc     = cms.untracked.InputTag("slimmedMuons"),
  #tauSrc      = cms.untracked.InputTag("slimmedPatTaus"),
#  jetSrc      = cms.untracked.InputTag("slimmedJets"),
    pfcandSrc	   = cms.untracked.InputTag("packedPFCandidates"),

    jetSrc      = cms.untracked.InputTag(jetsrcc),
  metSrc      = cms.untracked.InputTag("patMETsPF"),
  genSrc      = cms.untracked.InputTag("prunedGenParticles"),
  gjetSrc       = cms.untracked.InputTag('slimmedGenJets'),
  muonMatch    = cms.string( 'muonTriggerMatchHLTMuons' ),
  muonMatch2    = cms.string( 'muonTriggerMatchHLTMuons2' ),
  elecMatch    = cms.string( 'elecTriggerMatchHLTElecs' ),
  mSrcRho      = cms.untracked.InputTag('fixedGridRhoFastjetAll'),#arbitrary rho now
  CalojetLabel = cms.untracked.InputTag('slimmedJets'), #same collection now BB 
  metSource = cms.VInputTag("slimmedMETs","slimmedMETsNoHF","slimmedMETs","slimmedMETs"), #no MET corr yet
  lheSource=cms.untracked.InputTag('source')

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
 process.tupel 
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


