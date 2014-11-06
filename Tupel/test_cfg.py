0001 import FWCore.ParameterSet.Config as cms
0002 
0003 process = cms.Process("S2")
0004 process.source = cms.Source("PoolSource",
0005     fileNames = cms.untracked.vstring("file:patTuple_mini.root")
0006 )
0007 process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
0008 
0009 from RecoJets.JetProducers.ak5PFJets_cfi import ak5PFJets
0010 from RecoJets.JetProducers.ak5GenJets_cfi import ak5GenJets
0011 from RecoMET.METProducers.PFMET_cfi import pfMet
0012 
0013 process.chs = cms.EDFilter("CandPtrSelector", src = cms.InputTag("packedPFCandidates"), cut = cms.string("fromPV"))
0014 
0015 process.ak5PFJets = ak5PFJets.clone(src = 'packedPFCandidates', doAreaFastjet = True) # no idea while doArea is false by default, but it's True in RECO so we have to set it
0016 process.ak5PFJetsCHS = ak5PFJets.clone(src = 'chs', doAreaFastjet = True) # no idea while doArea is false by default, but it's True in RECO so we have to set it
0017 process.ak5GenJets = ak5GenJets.clone(src = 'packedGenParticles')
0018 process.pfMet = pfMet.clone(src = "packedPFCandidates")
0019 process.pfMet.calculateSignificance = False # this can't be easily implemented on packed PF candidates at the moment
0020 
0021 process.load("PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff")
0022 process.load("Configuration.EventContent.EventContent_cff")
0023 process.load('Configuration.StandardSequences.Geometry_cff')
0024 process.load('Configuration.StandardSequences.MagneticField_38T_cff')
0025 process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
0026 process.GlobalTag.globaltag = 'START70_V6::All'
0027 
0028 
0029 
0030 process.patJets.addJetCharge   = False
0031 process.patJets.addBTagInfo    = True
0032 process.patJets.getJetMCFlavour = False
0033 process.patJets.addAssociatedTracks = False
0034 process.patJetPartonMatch.matched = "prunedGenParticles"
0035 process.patJetCorrFactors.primaryVertices = "offlineSlimmedPrimaryVertices"
0036 process.patMETs.addGenMET = False # There's no point in recalculating this, and we can't remake it since we don't have genParticles beyond |eta|=5
0037 
0038 process.load('RecoBTag.Configuration.RecoBTag_cff')
0039 process.load('RecoJets.Configuration.RecoJetAssociations_cff')
0040 
0041 process.load('PhysicsTools.PatAlgos.slimming.unpackedTracksAndVertices_cfi')
0042 
0043 process.ak5JetTracksAssociatorAtVertexPF.jets = cms.InputTag("ak5PFJetsCHS")
0044 process.ak5JetTracksAssociatorAtVertexPF.tracks = cms.InputTag("unpackedTracksAndVertices")
0045 process.impactParameterTagInfos.primaryVertex = cms.InputTag("unpackedTracksAndVertices")
0046 process.inclusiveSecondaryVertexFinderTagInfos.extSVCollection = cms.InputTag("unpackedTracksAndVertices","secondary","")
0047 process.combinedSecondaryVertex.trackMultiplicityMin = 1 #silly sv, uses un filtered tracks.. i.e. any pt
0048 
0049 
0050 process.p = cms.Path(
0051     process.patJets + process.patMETs + process.inclusiveSecondaryVertexFinderTagInfos
0052 )
0053 
0054 process.load("FWCore.MessageLogger.MessageLogger_cfi")
0055 process.MessageLogger.cerr.FwkReport.reportEvery = 10
0056 process.MessageLogger.suppressWarning = cms.untracked.vstring('ecalLaserCorrFilter','manystripclus53X','toomanystripclus53X')
0057 process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
0058 process.options.allowUnscheduled = cms.untracked.bool(True)
0059 
0060 process.OUT = cms.OutputModule("PoolOutputModule",
0061     fileName = cms.untracked.string('test.root'),
0062     outputCommands = cms.untracked.vstring(['drop *','keep patJets_patJets_*_*','keep *_*_*_PAT','keep recoTracks_unp*_*_*','keep recoVertexs_unp*_*_*'])
0063 )
0064 process.endpath= cms.EndPath(process.OUT)
0065 

