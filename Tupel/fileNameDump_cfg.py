import FWCore.ParameterSet.Config as cms

process = cms.Process("S2")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('/store/mc/RunIISpring15MiniAODv2/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/74X_mcRun2_asymptotic_v2_ext3-v1/60000/90C569DF-426E-E511-A9CB-0025905A48F0.root')
)
process.goodOfflinePrimaryVertices = cms.EDFilter("PrimaryVertexObjectFilter",
    filterParams = cms.PSet(
        NPV = cms.int32(1),
        maxRho = cms.double(2.0),
        maxZ = cms.double(24.0),
        minNdof = cms.double(4.0),
        pvSrc = cms.InputTag("offlinePrimaryVertices")
    ),
    src = cms.InputTag("offlineSlimmedPrimaryVertices")
)


process.tupel = cms.EDAnalyzer("Tupel",
    CalojetLabel = cms.untracked.InputTag("slimmedJets"),
    elecMatch = cms.string('elecTriggerMatchHLTElecs'),
    electronSrc = cms.untracked.InputTag("slimmedElectrons"),
    genSrc = cms.untracked.InputTag("prunedGenParticles"),
    gjetSrc = cms.untracked.InputTag("slimmedGenJets"),
    jetSrc = cms.untracked.InputTag("slimmedJets"),
    lheSource = cms.untracked.InputTag("source"),
    mSrcRho = cms.untracked.InputTag("fixedGridRhoFastjetAll"),
    metSource = cms.VInputTag("slimmedMETs", "slimmedMETsNoHF", "slimmedMETs", "slimmedMETs"),
    metSrc = cms.untracked.InputTag("patMETsPF"),
    muonMatch = cms.string('muonTriggerMatchHLTMuons'),
    muonMatch2 = cms.string('muonTriggerMatchHLTMuons2'),
    muonSrc = cms.untracked.InputTag("slimmedMuons"),
    pfcandSrc = cms.untracked.InputTag("packedPFCandidates"),
    pgenSrc = cms.untracked.InputTag("packedGenParticles"),
    photonSrc = cms.untracked.InputTag("slimmedPhotons"),
    triggerEvent = cms.InputTag("patTriggerEvent")
)


process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('test.root'),
    outputCommands = cms.untracked.vstring('drop *', 
        'keep patJets_patJets_*_*', 
        'keep *_*_*_PAT', 
        'keep recoTracks_unp*_*_*', 
        'keep recoVertexs_unp*_*_*')
)


process.p = cms.Path(process.tupel)


process.MessageLogger = cms.Service("MessageLogger",
    FrameworkJobReport = cms.untracked.PSet(
        FwkJob = cms.untracked.PSet(
            limit = cms.untracked.int32(10000000),
            optionalPSet = cms.untracked.bool(True)
        ),
        default = cms.untracked.PSet(
            limit = cms.untracked.int32(0)
        ),
        optionalPSet = cms.untracked.bool(True)
    ),
    categories = cms.untracked.vstring('FwkJob', 
        'FwkReport', 
        'FwkSummary', 
        'Root_NoDictionary'),
    cerr = cms.untracked.PSet(
        FwkJob = cms.untracked.PSet(
            limit = cms.untracked.int32(0),
            optionalPSet = cms.untracked.bool(True)
        ),
        FwkReport = cms.untracked.PSet(
            limit = cms.untracked.int32(10000000),
            optionalPSet = cms.untracked.bool(True),
            reportEvery = cms.untracked.int32(10)
        ),
        FwkSummary = cms.untracked.PSet(
            limit = cms.untracked.int32(10000000),
            optionalPSet = cms.untracked.bool(True),
            reportEvery = cms.untracked.int32(1)
        ),
        INFO = cms.untracked.PSet(
            limit = cms.untracked.int32(0)
        ),
        Root_NoDictionary = cms.untracked.PSet(
            limit = cms.untracked.int32(0),
            optionalPSet = cms.untracked.bool(True)
        ),
        default = cms.untracked.PSet(
            limit = cms.untracked.int32(10000000)
        ),
        noTimeStamps = cms.untracked.bool(False),
        optionalPSet = cms.untracked.bool(True),
        threshold = cms.untracked.string('INFO')
    ),
    cerr_stats = cms.untracked.PSet(
        optionalPSet = cms.untracked.bool(True),
        output = cms.untracked.string('cerr'),
        threshold = cms.untracked.string('WARNING')
    ),
    cout = cms.untracked.PSet(
        placeholder = cms.untracked.bool(True)
    ),
    debugModules = cms.untracked.vstring(),
    debugs = cms.untracked.PSet(
        placeholder = cms.untracked.bool(True)
    ),
    default = cms.untracked.PSet(

    ),
    destinations = cms.untracked.vstring('warnings', 
        'errors', 
        'infos', 
        'debugs', 
        'cout', 
        'cerr'),
    errors = cms.untracked.PSet(
        placeholder = cms.untracked.bool(True)
    ),
    fwkJobReports = cms.untracked.vstring('FrameworkJobReport'),
    infos = cms.untracked.PSet(
        Root_NoDictionary = cms.untracked.PSet(
            limit = cms.untracked.int32(0),
            optionalPSet = cms.untracked.bool(True)
        ),
        optionalPSet = cms.untracked.bool(True),
        placeholder = cms.untracked.bool(True)
    ),
    statistics = cms.untracked.vstring('cerr_stats'),
    suppressDebug = cms.untracked.vstring(),
    suppressInfo = cms.untracked.vstring(),
    suppressWarning = cms.untracked.vstring('ecalLaserCorrFilter', 
        'manystripclus53X', 
        'toomanystripclus53X'),
    warnings = cms.untracked.PSet(
        placeholder = cms.untracked.bool(True)
    )
)


process.TFileService = cms.Service("TFileService",
    fileName = cms.string('withJEC_DYJetsToLL_ntuple.root')
)


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(300)
)

process.options = cms.untracked.PSet(
    allowUnscheduled = cms.untracked.bool(True),
    wantSummary = cms.untracked.bool(True)
)

