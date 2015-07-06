/* -*- c-basic-offset: 2; -*-

Code by: Bugra Bilin, Kittikul Kovitanggoon, Tomislav Seva, Efe Yazgan,
         Philippe Gras...

*/

#include <map>
#include <string>
#include <vector>
#include <memory>
#include <TLorentzVector.h>
#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"
#include "PhysicsTools/PatUtils/interface/TriggerHelper.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "EgammaAnalysis/ElectronTools/interface/EGammaCutBasedEleId.h"
#include "EgammaAnalysis/ElectronTools/interface/ElectronEffectiveArea.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "FWCore/Framework/interface/GenericHandle.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
//#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"
//#include "CMGTools/External/interface/PileupJetIdentifier.h"
#include "EgammaAnalysis/ElectronTools/interface/PFIsolationEstimator.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "DataFormats/BTauReco/interface/JetTag.h"

#include "TreeHelper.h"

#define QUOTE2(a) #a
#define QUOTE(a) QUOTE2(a)
const static char* checksum = QUOTE(MYFILE_CHECKSUM);



class TTree;
class Tupel : public edm::EDAnalyzer {

public:
  /// default constructor
  explicit Tupel(const edm::ParameterSet&);
  /// default destructor
  ~Tupel();

private:
/// everything that needs to be done before the event loop
  virtual void beginJob() ;
  /// everything that needs to be done during the event loop
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  /// everything that needs to be done after the event loop
  virtual void endJob() ;

  //help function to compute pseudo rapidity of a TLorentz without
  //ROOT exception in case of infinite pseudo rapidity
  double eta(TLorentzVector v){
    if(fabs(v.CosTheta()) < 1) return -0.5 * log((1.0-v.CosTheta())/(1.0+v.CosTheta()));
    else if(v.Pz() > 0) return 10e10;
    else return -10e10;
  }
  
  //Write Job information tree in the output. The tree
  //contains one event, with general information
  void writeHeader();

  //Retrieves event objets
  void readEvent(const edm::Event& iEvent);

  //Processes MET
  void processMET(const edm::Event& iEvent);

  //Processes vertices
  void processVtx();
		  
  //Processes PU
  void processPu(const edm::Event& iEvent);

  //Processes GenParticles
  void processGenParticles(const edm::Event& iEvent);

  void processGenJets(const edm::Event& iEvent);

  void processPdfInfo(const edm::Event& iEvent);
  
  void processTrigger(const edm::Event& iEvent);

  void processMuons();

  void processElectrons();

  void processJets();
  
  void processPhotons();
  
  // input tags
  //edm::InputTag trigger_;
  //edm::InputTag triggerEvent_;
  //edm::InputTag triggerSummaryLabel_;
  std::string elecMatch_;
  std::string muonMatch_;
  std::string muonMatch2_;
  edm::InputTag photonSrc_;
  edm::InputTag elecSrc_;
  edm::InputTag muonSrc_;
  edm::InputTag tauSrc_;
  edm::InputTag jetSrc_;
  edm::InputTag gjetSrc_;
  edm::InputTag metSrc_;
  edm::InputTag mSrcRho_;
  edm::InputTag CaloJet_;
  edm::InputTag lheSource_;
  edm::InputTag genParticleSrc_;
  std::vector<edm::InputTag> metSources;

  bool photonIdsListed_;
  bool elecIdsListed_;

  //edm::EDGetTokenT<edm::ValueMap<float> > full5x5SigmaIEtaIEtaMapToken_;

  // ----------member data ---------------------------
  TTree *myTree;
  std::auto_ptr<TreeHelper> treeHelper_;
  
  std::auto_ptr<double> MyWeight_;

  std::auto_ptr<unsigned> event_, run_, lumi_;
  std::auto_ptr<int> realdata_, bxnumber_;
  std::auto_ptr<float> EvtInfo_NumVtx_, PU_npT_, PU_npIT_, nup_;
  
  //particles
  std::auto_ptr<std::vector<float> > METPt_;
  std::auto_ptr<std::vector<float> > METPx_;
  std::auto_ptr<std::vector<float> > METPy_;
  std::auto_ptr<std::vector<float> > METPz_;
  std::auto_ptr<std::vector<float> > METE_;
  std::auto_ptr<std::vector<float> > METsigx2_;
  std::auto_ptr<std::vector<float> > METsigxy_;
  std::auto_ptr<std::vector<float> > METsigy2_;   
  std::auto_ptr<std::vector<float> > METsig_;
  std::auto_ptr<std::vector<float> > Dr01LepPt_;
  std::auto_ptr<std::vector<float> > Dr01LepEta_;
  std::auto_ptr<std::vector<float> > Dr01LepPhi_;
  std::auto_ptr<std::vector<float> > Dr01LepE_;
  std::auto_ptr<std::vector<float> > Dr01LepM_;
  std::auto_ptr<std::vector<float> > Dr01LepId_;
  std::auto_ptr<std::vector<float> > Dr01LepStatus_;
  std::auto_ptr<std::vector<float> > Dr01LepMomId_;
  std::auto_ptr<std::vector<float> > Bare01LepPt_;
  std::auto_ptr<std::vector<float> > Bare01LepEta_;
  std::auto_ptr<std::vector<float> > Bare01LepPhi_;
  std::auto_ptr<std::vector<float> > Bare01LepE_;
  std::auto_ptr<std::vector<float> > Bare01LepM_;
  std::auto_ptr<std::vector<float> > Bare01LepId_;
  std::auto_ptr<std::vector<float> > Bare01LepStatus_;
  std::auto_ptr<std::vector<float> > Bare01LepMomId_;
  std::auto_ptr<std::vector<float> > St03Pt_;
  std::auto_ptr<std::vector<float> > St03Eta_;
  std::auto_ptr<std::vector<float> > St03Phi_;
  std::auto_ptr<std::vector<float> > St03E_;
  std::auto_ptr<std::vector<float> > St03M_;
  std::auto_ptr<std::vector<float> > St03Id_;
  std::auto_ptr<std::vector<float> > St03Status_;
  std::auto_ptr<std::vector<float> > St03MotherId_;
  std::auto_ptr<std::vector<float> > St03NumberMom_;

  std::auto_ptr<std::vector<float> > St01PhotonPt_;
  std::auto_ptr<std::vector<float> > St01PhotonEta_;
  std::auto_ptr<std::vector<float> > St01PhotonPhi_;
  std::auto_ptr<std::vector<float> > St01PhotonE_;
  std::auto_ptr<std::vector<float> > St01PhotonM_;
  std::auto_ptr<std::vector<float> > St01PhotonId_;
  std::auto_ptr<std::vector<float> > St01PhotonMomId_;
  std::auto_ptr<std::vector<float> > St01PhotonNumberMom_;
  std::auto_ptr<std::vector<float> > St01PhotonStatus_;



  std::auto_ptr<std::vector<float> > GjPt_;
  std::auto_ptr<std::vector<float> > Gjeta_;
  std::auto_ptr<std::vector<float> > Gjphi_;
  std::auto_ptr<std::vector<float> > GjE_;
  std::auto_ptr<std::vector<float> > GjPx_;
  std::auto_ptr<std::vector<float> > GjPy_;
  std::auto_ptr<std::vector<float> > GjPz_;
  std::auto_ptr<std::vector<float> > GjChargedFraction_;
  std::auto_ptr<std::vector<bool> > matchGjet_;
  std::auto_ptr<std::vector<int> > GjDoughterId_;
  std::auto_ptr<std::vector<float> > GjDoughterPt_;
  std::auto_ptr<std::vector<float> > GjDoughterEta_;
  std::auto_ptr<std::vector<float> > GjDoughterPhi_;
  std::auto_ptr<std::vector<float> > GjDoughterE_;


  std::auto_ptr<std::vector<float> > MGjPt_;
  std::auto_ptr<std::vector<float> > MGjeta_;
  std::auto_ptr<std::vector<float> > MGjphi_;
  std::auto_ptr<std::vector<float> > MGjE_;
  //CaloJets
  std::auto_ptr<std::vector<float> > caloJetPt_;
  std::auto_ptr<std::vector<float> > caloJetRawPt_;
  std::auto_ptr<std::vector<float> > caloJetEn_;
  std::auto_ptr<std::vector<float> > caloJetEta_;
  std::auto_ptr<std::vector<float> > caloJetPhi_;
  std::auto_ptr<std::vector<float> > caloJetHadEHF_;
  std::auto_ptr<std::vector<float> > caloJetEmEHF_;
  std::auto_ptr<std::vector<float> > caloJetEmFrac_;
  std::auto_ptr<std::vector<float> > caloJetn90_;
  ///pfjets
  std::auto_ptr<std::vector<float> > patJetPfAk05En_;
  std::auto_ptr<std::vector<float> > patJetPfAk05Pt_;
  std::auto_ptr<std::vector<float> > patJetPfAk05Eta_;
  std::auto_ptr<std::vector<float> > patJetPfAk05Phi_;
  //std::auto_ptr<std::vector<float> > patJetPfAk05JesUncert_;
  std::auto_ptr<std::vector<float> > patJetPfAk05LooseId_;
  std::auto_ptr<std::vector<float> > patJetPfAk05Et_;
  std::auto_ptr<std::vector<float> > patJetPfAk05RawPt_;
  std::auto_ptr<std::vector<float> > patJetPfAk05RawEn_;
  std::auto_ptr<std::vector<float> > patJetPfAk05HadEHF_;
  std::auto_ptr<std::vector<float> > patJetPfAk05EmEHF_;
  //std::auto_ptr<std::vector<float> > patJetPfAk05jetBSZ_;
  //std::auto_ptr<std::vector<float> > patJetPfAk05jetBZ_;
  std::auto_ptr<std::vector<float> > patJetPfAk05jetBetaClassic_;
  std::auto_ptr<std::vector<float> > patJetPfAk05jetBeta_;
  std::auto_ptr<std::vector<float> > patJetPfAk05jetBetaStar_;
  std::auto_ptr<std::vector<float> > patJetPfAk05jetBetaStarClassic_;
  std::auto_ptr<std::vector<float> > patJetPfAk05jetpuMVA_;
  std::auto_ptr<std::vector<float> > patJetPfAk05chf_;
  std::auto_ptr<std::vector<float> > patJetPfAk05nhf_;
  std::auto_ptr<std::vector<float> > patJetPfAk05cemf_;
  std::auto_ptr<std::vector<float> > patJetPfAk05nemf_;
  std::auto_ptr<std::vector<float> > patJetPfAk05cmult_;
  std::auto_ptr<std::vector<float> > patJetPfAk05nconst_;
  std::auto_ptr<std::vector<bool> > patJetPfAk05jetpukLoose_;
  std::auto_ptr<std::vector<bool> > patJetPfAk05jetpukMedium_;
  std::auto_ptr<std::vector<bool> > patJetPfAk05jetpukTight_;
  std::auto_ptr<std::vector<float> > patJetPfAk05PtUp_;
  std::auto_ptr<std::vector<float> > patJetPfAk05PtDn_;
  std::auto_ptr<std::vector<float> > patJetPfAk05BDiscCSV_;
  std::auto_ptr<std::vector<float> > patJetPfAk05BDiscCSVV1_;
  std::auto_ptr<std::vector<float> > patJetPfAk05BDiscCSVSLV1_;
  std::auto_ptr<std::vector<int> > patJetPfAk05DoughterId_;
  std::auto_ptr<std::vector<float> > patJetPfAk05DoughterPt_;
  std::auto_ptr<std::vector<float> > patJetPfAk05DoughterEta_;
  std::auto_ptr<std::vector<float> > patJetPfAk05DoughterPhi_;
  std::auto_ptr<std::vector<float> > patJetPfAk05DoughterE_;

  std::auto_ptr<std::vector<float> > unc_;
  ///Muons
  std::auto_ptr<std::vector<float> > patMuonPt_;
  std::auto_ptr<std::vector<float> > patMuonEta_;
  std::auto_ptr<std::vector<float> > patMuonPhi_;
  std::auto_ptr<std::vector<float> > patMuonVtxZ_;
  std::auto_ptr<std::vector<float> > patMuonEn_;
  std::auto_ptr<std::vector<float> > patMuonCharge_;
  std::auto_ptr<std::vector<float> > patMuonDxy_;
  std::auto_ptr<std::vector<float> > patMuonCombId_;
  std::auto_ptr<std::vector<float> > patMuonTrig_;
  std::auto_ptr<std::vector<float> > patMuonDetIsoRho_;
  std::auto_ptr<std::vector<float> > patMuonPfIsoDbeta_;
  std::auto_ptr<std::vector<float> > patMuonM_;
  std::auto_ptr<std::vector<float> > patMuonPx_;
  std::auto_ptr<std::vector<float> > patMuonPy_;
  std::auto_ptr<std::vector<float> > patMuonPz_;
  std::auto_ptr<std::vector<float> > patMuonGlobalType_;
  std::auto_ptr<std::vector<float> > patMuonTrackerType_;
  std::auto_ptr<std::vector<float> > patMuonPFType_;
  std::auto_ptr<std::vector<float> > patMuonIsoSumPt_;
  std::auto_ptr<std::vector<float> > patMuonIsoRelative_;
  std::auto_ptr<std::vector<float> > patMuonIsoCalComb_;
  std::auto_ptr<std::vector<float> > patMuonIsoDY_;
  std::auto_ptr<std::vector<float> > patMuonChi2Ndoff_;
  std::auto_ptr<std::vector<float> > patMuonNhits_;
  std::auto_ptr<std::vector<float> > patMuonNMatches_;
  std::auto_ptr<std::vector<float> > patMuonDz_;
  std::auto_ptr<std::vector<float> > patMuonPhits_;
  std::auto_ptr<std::vector<float> > patMuonTkLayers_;
  std::auto_ptr<std::vector<float> > patMuon_PF_IsoSumChargedHadronPt_;
  std::auto_ptr<std::vector<float> > patMuon_PF_IsoSumNeutralHadronEt_;
  std::auto_ptr<std::vector<float> > patMuon_PF_IsoDY_;
  std::auto_ptr<std::vector<float> > patMuon_Mu17_Mu8_Matched_;
  std::auto_ptr<std::vector<float> > patMuon_Mu17_TkMu8_Matched_;
  std::auto_ptr<std::vector<bool> >   patMuonIdLoose_;
  std::auto_ptr<std::vector<bool> >   patMuonIdMedium_;
  std::auto_ptr<std::vector<unsigned> > patMuonIdTight_;

  

  std::auto_ptr<std::vector<float> > patElecdEtaIn_;
  std::auto_ptr<std::vector<float> > patElecdPhiIn_;
  std::auto_ptr<std::vector<float> > patElechOverE_;
  std::auto_ptr<std::vector<float> > patElecsigmaIetaIeta_;
  std::auto_ptr<std::vector<float> > patElecfull5x5_sigmaIetaIeta_;
  std::auto_ptr<std::vector<float> > patElecooEmooP_;
  std::auto_ptr<std::vector<float> > patElecd0_;
  std::auto_ptr<std::vector<float> > patElecdz_;
  std::auto_ptr<std::vector<int> >    patElecexpectedMissingInnerHits_;
  std::auto_ptr<std::vector<int> >    patElecpassConversionVeto_;     
  std::auto_ptr<std::vector<float> > patElecTrig_;
  std::auto_ptr<std::vector<float> > patElecDz_;
  std::auto_ptr<std::vector<float> > patElecMVATrigId_;
  std::auto_ptr<std::vector<float> > patElecMVANonTrigId_;
  std::auto_ptr<std::vector<float> > patElecPt_;
  std::auto_ptr<std::vector<float> > patElecEta_;
  std::auto_ptr<std::vector<float> > patElecScEta_;
  std::auto_ptr<std::vector<float> > patElecPhi_;
  std::auto_ptr<std::vector<float> > patElecEnergy_;
  std::auto_ptr<std::vector<float> > patElecCharge_;
  std::auto_ptr<std::vector<float> > patElecMediumIDOff_;
  std::auto_ptr<std::vector<float> > patElecMediumIDOff_Tom_;
  
  std::auto_ptr<std::vector<float> > patElecchIso03_;
  std::auto_ptr<std::vector<float> > patElecnhIso03_;
  std::auto_ptr<std::vector<float> > patElecphIso03_;
  std::auto_ptr<std::vector<float> > patElecpuChIso03_;
  std::auto_ptr<std::vector<float> > patElecPfIso_;
  std::auto_ptr<std::vector<float> > patElecPfIsodb_;
  std::auto_ptr<std::vector<float> > patElecPfIsoRho_;
  std::auto_ptr<std::vector<unsigned> >  patElecId_;
  std::auto_ptr<std::vector<float> > charged_;
  std::auto_ptr<std::vector<float> > photon_;
  std::auto_ptr<std::vector<float> > neutral_;
  std::auto_ptr<std::vector<float> > charged_Tom_;
  std::auto_ptr<std::vector<float> > photon_Tom_;
  std::auto_ptr<std::vector<float> > neutral_Tom_;
  std::auto_ptr<std::vector<float> > patElec_mva_presel_;

  //Photons
  //photon momenta
  std::auto_ptr<std::vector<float> > PhotonPt_;
  std::auto_ptr<std::vector<float> > PhotonEta_;
  std::auto_ptr<std::vector<float> > PhotonPhi_;
  
  //photon isolations
  std::auto_ptr<std::vector<float> > PhotonIsoEcal_;
  std::auto_ptr<std::vector<float> > PhotonIsoHcal_;
  std::auto_ptr<std::vector<float> > PhotonPfIsoChargdH_;
  std::auto_ptr<std::vector<float> > PhotonPfIsoNeutralH_;
  std::auto_ptr<std::vector<float> > PhotonPfIsoPhoton_;
  std::auto_ptr<std::vector<float> > PhotonPfIsoPuChargedH_;
  std::auto_ptr<std::vector<float> > PhotonPfIsoEcalCluster_;
  std::auto_ptr<std::vector<float> > PhotonPfIsoHcalCluster_;
  
  //photon cluster shapes
  std::auto_ptr<std::vector<float> > PhotonE3x3_;
  std::auto_ptr<std::vector<float> > PhotonSigmaIetaIeta_;

  //photon id (bit field)
  std::auto_ptr<std::vector<unsigned> > PhotonId_;
  std::auto_ptr<std::vector<float> > PhotonHoE_;
  std::auto_ptr<std::vector<bool> > PhotonHasPixelSeed_;
  
  std::auto_ptr<std::vector<float> > id1_pdfInfo_;
  std::auto_ptr<std::vector<float> > id2_pdfInfo_;
  std::auto_ptr<std::vector<float> > x1_pdfInfo_;
  std::auto_ptr<std::vector<float> > x2_pdfInfo_;
  std::auto_ptr<std::vector<float> > scalePDF_pdfInfo_;
  std::auto_ptr<float> ptHat_;
  std::auto_ptr<double> mcWeight_;
  std::auto_ptr<std::vector<double> > mcWeights_;
  std::auto_ptr<float> rhoPrime_, AEff_;
  //HLT
  std::auto_ptr<int> HLT_Mu17_Mu8_, HLT_Mu17_TkMu8_;
  std::auto_ptr<int> HLT_Elec17_Elec8_;

//  JetCorrectionUncertainty *jecUnc;


///Event objects
  edm::Handle<GenParticleCollection> genParticles_h;
  const GenParticleCollection* genParticles;
  edm::Handle<edm::View<pat::Muon> > muons;
  const edm::View<pat::Muon> * muon;
  edm::Handle<vector<pat::Electron> > electrons;
  const vector<pat::Electron>  *electron;
  edm::Handle<reco::ConversionCollection> conversions_h;
  edm::Handle<edm::View<pat::Tau> > taus;
  edm::Handle<edm::View<pat::Jet> > jets;
  const edm::View<pat::Jet> * jettt;
  edm::Handle<edm::View<pat::MET> > mets;
  const edm::View<pat::Photon>  *photons;
  edm::Handle<edm::View<reco::Vertex> >  pvHandle;
  edm ::Handle<reco::VertexCollection> vtx_h;
  const edm::View<reco::Vertex> * vtxx;
  double rhoIso;
  edm::Handle<reco::BeamSpot> beamSpotHandle;
  reco::BeamSpot beamSpot;
  edm::Handle<double> rho;
///
};

using namespace std;
using namespace reco;
int ccnevent=0;
Tupel::Tupel(const edm::ParameterSet& iConfig):
//trigger_( iConfig.getParameter< edm::InputTag >( "trigger" ) ),
  //triggerEvent_( iConfig.getParameter< edm::InputTag >( "triggerEvent" ) ),
  //triggerSummaryLabel_( iConfig.getParameter< edm::InputTag >( "triggerSummaryLabel" ) ), //added by jyhan
  elecMatch_( iConfig.getParameter< std::string >( "elecMatch" ) ),
  muonMatch_( iConfig.getParameter< std::string >( "muonMatch" ) ),
  muonMatch2_( iConfig.getParameter< std::string >( "muonMatch2" ) ),
  photonSrc_(iConfig.getUntrackedParameter<edm::InputTag>("photonSrc")),
  elecSrc_(iConfig.getUntrackedParameter<edm::InputTag>("electronSrc")),
  muonSrc_(iConfig.getUntrackedParameter<edm::InputTag>("muonSrc")),
  //tauSrc_(iConfig.getUntrackedParameter<edm::InputTag>("tauSrc" )),
  jetSrc_(iConfig.getUntrackedParameter<edm::InputTag>("jetSrc" )),
  gjetSrc_(iConfig.getUntrackedParameter<edm::InputTag>("gjetSrc" )),
  metSrc_(iConfig.getUntrackedParameter<edm::InputTag>("metSrc" )),
  mSrcRho_(iConfig.getUntrackedParameter<edm::InputTag>("mSrcRho" )),
  CaloJet_(iConfig.getUntrackedParameter<edm::InputTag>("CalojetLabel")),
  lheSource_(iConfig.getUntrackedParameter<edm::InputTag>("lheSource")),
genParticleSrc_(iConfig.getUntrackedParameter<edm::InputTag >("genSrc")),
  metSources(iConfig.getParameter<std::vector<edm::InputTag> >("metSource")),
  photonIdsListed_(false),
  elecIdsListed_(false)

  //full5x5SigmaIEtaIEtaMapToken_(consumes<edm::ValueMap<float> >(iConfig.getParameter<edm::InputTag>("full5x5SigmaIEtaIEtaMap")))


{
}

Tupel::~Tupel()
{
}

//#name -> "name", name ## _ -> name_
#define ADD_BRANCH_D(name, desc) treeHelper_->addBranch(#name, name ## _, desc)
#define ADD_BRANCH(name) treeHelper_->addBranch(#name, name ## _)
#define ADD_MOMENTUM_BRANCH_D(name, desc) treeHelper_->addMomentumBranch(#name, name ## Pt_, name ## Eta_, name ## Phi_, name ## E_, desc)
#define ADD_MOMENTUM_BRANCH(name) treeHelper_->addMomentumBranch(#name, name ## Pt_, name ## Eta_, name ## Phi_, name ## E_)

void Tupel::readEvent(const edm::Event& iEvent){
  *event_ = iEvent.id().event();
  *run_ = iEvent.id().run();
  *lumi_ = iEvent.luminosityBlock();
  *bxnumber_ = iEvent.bunchCrossing();
  *realdata_ = iEvent.isRealData();

  const pat::helper::TriggerMatchHelper matchHelper;	
  iEvent.getByLabel(genParticleSrc_, genParticles_h);
  genParticles  = genParticles_h.failedToGet () ? 0 : &*genParticles_h;
  
  // get muon collection
  iEvent.getByLabel(muonSrc_,muons);
  muon = muons.failedToGet () ? 0 : &*muons;

  
  // get electron collection
  iEvent.getByLabel(elecSrc_,electrons);
  electron = electrons.failedToGet () ? 0 :  &*electrons;
			      
 // edm::Handle<reco::GsfElectronCollection> els_h;
 // iEvent.getByLabel("gsfElectrons", els_h);			       
  iEvent.getByLabel(InputTag("reducedEgamma","reducedConversions"), conversions_h);  
  
  // get tau collection 
  iEvent.getByLabel(tauSrc_,taus);
					  
  // get jet collection
  iEvent.getByLabel(jetSrc_,jets);
  jettt = jets.failedToGet () ? 0 : &*jets ;
  
  // get met collection  
  iEvent.getByLabel(metSrc_,mets);
  
  // get photon collection  
  edm::Handle<edm::View<pat::Photon> > hPhotons;
  iEvent.getByLabel(photonSrc_, hPhotons);
  photons = hPhotons.failedToGet () ? 0 :  &*hPhotons;
  
  iEvent.getByLabel("goodOfflinePrimaryVertices", pvHandle);
  vtxx = pvHandle.failedToGet () ? 0 : &*pvHandle ;
			  
  iEvent.getByLabel("goodOfflinePrimaryVertices", vtx_h); 
//  if(vtxx){
//    int nvtx=vtx_h->size();
//    if(nvtx==0) return;
//    reco::VertexRef primVtx(vtx_h,0);
//  }

  edm::Handle<double>  rho_;
  iEvent.getByLabel(mSrcRho_, rho_);
  rhoIso=99;
  if(!rho_.failedToGet())rhoIso = *rho_;
  iEvent.getByLabel("offlineBeamSpot", beamSpotHandle);
  if(!beamSpotHandle.failedToGet()) beamSpot = *beamSpotHandle;
  iEvent.getByLabel(mSrcRho_,rho);
}

void Tupel::processMET(const edm::Event& iEvent){
   for(unsigned int imet=0;imet<metSources.size();imet++){
    Handle<View<pat::MET> > metH;
    iEvent.getByLabel(metSources[imet], metH);
    if(!metH.isValid())continue;
    //cout<<"MET"<<imet<<"  "<<metSources[imet]<<"  "<<metH->ptrAt(0)->pt()<<endl;

    METPt_->push_back(metH->ptrAt(0)->pt()); 
    METPx_->push_back(metH->ptrAt(0)->px()); 
    METPy_->push_back(metH->ptrAt(0)->py()); 
    METPz_->push_back(metH->ptrAt(0)->pz()); 
    METE_->push_back(metH->ptrAt(0)->energy()); 
    METsigx2_->push_back(metH->ptrAt(0)->getSignificanceMatrix()(0,0)); 
    METsigxy_->push_back(metH->ptrAt(0)->getSignificanceMatrix()(0,1)); 
    METsigy2_->push_back(metH->ptrAt(0)->getSignificanceMatrix()(1,1)); 
    METsig_->push_back(metH->ptrAt(0)->significance()); 
    //Output object in EDM format
    //std::auto_ptr<llvvMet> metOut(new llvvMet());
    //llvvMet& met = *metOut;

    //////////////////////////////////

    // met.SetPxPyPzE(metH->ptrAt(0)->px(), metH->ptrAt(0)->py(), metH->ptrAt(0)->pz(), metH->ptrAt(0)->energy());
    //met.sigx2 = metH->ptrAt(0)->getSignificanceMatrix()(0,0);
    //met.sigxy = metH->ptrAt(0)->getSignificanceMatrix()(0,1);
    //met.sigy2 = metH->ptrAt(0)->getSignificanceMatrix()(1,1);
    //met.sig   = metH->ptrAt(0)->significance();

    //iEvent.put(metOut, metSources[imet].label()); //save the object to the event here, to keep it in the loop
  }
}

void Tupel::processVtx(){
  if(vtxx){
    for (edm::View<reco::Vertex>::const_iterator vtx = pvHandle->begin(); vtx != pvHandle->end(); ++vtx){
      if (vtx->isValid() && !vtx->isFake()) ++(*EvtInfo_NumVtx_);
    }
  }
}

void Tupel::processPu(const edm::Event& iEvent){
  Handle<std::vector< PileupSummaryInfo > >  PupInfo;
  iEvent.getByLabel("addPileupInfo", PupInfo);
  if(!PupInfo.failedToGet()){
    std::vector<PileupSummaryInfo>::const_iterator PVI;
    float npT=-1.;
    float npIT=-1.;
      
    for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) {
	
      int BX = PVI->getBunchCrossing();
	
      if(BX == 0) {
	npT = PVI->getTrueNumInteractions();
	npIT = PVI->getPU_NumInteractions();
      }
    }
    *PU_npT_ = npT;
    *PU_npIT_ =npIT;
  }
  else {
    *PU_npT_ = -2.; 
    *PU_npIT_ = -2.;
  }
}

void Tupel::processGenParticles(const edm::Event& iEvent){
  const std::vector<reco::GenParticle> & gen = *genParticles_h;
  for (size_t i=0; i<genParticles->size(); ++i){
    TLorentzVector genR1DressLep1(0,0,0,0);
    //      TLorentzVector genPho(0,0,0,0); 
    int st = gen[i].status();
    int id = gen[i].pdgId();


    if(gen[i].numberOfMothers()){
      //        if (st!=3 && fabs(id)!=13&& fabs(id)!=11 && fabs(id)!=22 && fabs(id)!=23) continue;
      // if(abs(st)==13 ||abs(st)==12||abs(st)==11||abs(st)==23 ||abs(st)==22||abs(st)==21||abs(st)==61 )cout<<"AAA "<<gen[i].numberOfMothers() <<"  "<< gen[i].mother()->pdgId()<<"  "<< gen[i].pdgId()<<"  "<<st<<"  "<<gen[i].px()<<"  "<<gen[i].py()<<"  "<<gen[i].pz()<<"  "<<gen[i].energy()<<endl;
      if (abs(st)==23 ||abs(st)==22||abs(st)==21||abs(st)==61 ||abs(st)==3 ){
	TLorentzVector genLep3(0,0,0,0);
	if(abs(st)!=21)genLep3.SetPtEtaPhiE(gen[i].pt(),gen[i].eta(),gen[i].phi(),gen[i].energy());
	if(abs(st)==21)genLep3.SetPxPyPzE(0.001,0.001,gen[i].pz(),gen[i].energy());
	St03Pt_->push_back(genLep3.Pt());
	St03Eta_->push_back(eta(genLep3));
	St03Phi_->push_back(genLep3.Phi());
	St03E_->push_back(genLep3.Energy());
	St03M_->push_back(genLep3.M());
	St03MotherId_->push_back(gen[i].mother()->pdgId());
	St03NumberMom_->push_back(gen[i].numberOfMothers());
	St03Id_->push_back(id);
	St03Status_->push_back(st);
      }
      /* if(abs(id)==15){
      //cout<<gen[i].numberOfMothers() <<"  "<< gen[i].mother()->pdgId()<<"  "<< gen[i].pdgId()<<"  "<<st<<endl;
      n_tau++;
      }*/
      if(gen[i].numberOfMothers() ==1 && gen[i].mother()->pdgId() != id){
	//if(abs(id)==15)cout<<"DEAD"<<endl;
	continue;
      }
      if (st==1 && (abs(id)==13||abs(id)==11 || abs(id)==15 ||abs(id)==12||abs(id)==14||abs(id)==16) /*&& gen[i].pt() > 0.1 && fabs(gen[i].eta())<3.0*/){

	TLorentzVector genLep1(0,0,0,0);
	genLep1.SetPtEtaPhiE(gen[i].pt(),gen[i].eta(),gen[i].phi(),gen[i].energy());
	TLorentzVector genR1Pho1(0,0,0,0);

	edm::Handle<std::vector<reco::GenParticle> > genpart2;//DONT know why we Need to handle another collection
	iEvent.getByLabel(genParticleSrc_, genpart2);
	const std::vector<reco::GenParticle> & gen2 = *genpart2;
	//LOOP over photons//
	if (st==1 && (abs(id)==13||abs(id)==11)){
	  for(unsigned int j=0; j<genpart2->size(); ++j){
	    if(gen2[j].numberOfMothers()){
	      if( gen2[j].status()!=1|| gen2[j].pdgId()!=22 || gen2[j].energy()<0.000001 /*|| fabs(MomId2)!=fabs(id)*/) continue;
	      TLorentzVector thisPho1(0,0,0,0);
	      thisPho1.SetPtEtaPhiE(gen2[j].pt(),gen2[j].eta(),gen2[j].phi(),gen2[j].energy());
	      double dR = genLep1.DeltaR(thisPho1);
	      if(dR<0.1){
		genR1Pho1+=thisPho1;
	      }

	      if(dR<0.2){
		St01PhotonPt_->push_back(thisPho1.Pt());
		St01PhotonEta_->push_back(thisPho1.Eta());
		St01PhotonPhi_->push_back(thisPho1.Phi());
		St01PhotonE_->push_back(thisPho1.Energy());
		St01PhotonM_->push_back(thisPho1.M());
		St01PhotonId_->push_back(gen2[j].pdgId());
		St01PhotonMomId_->push_back(fabs(gen2[j].mother()->pdgId()));
		St01PhotonNumberMom_->push_back(gen2[j].numberOfMothers());
		St01PhotonStatus_->push_back(gen2[j].status());
	      }
	    }
	  }
	}

	genR1DressLep1=genLep1+genR1Pho1;
	Dr01LepPt_->push_back(genR1DressLep1.Pt());
	Dr01LepEta_->push_back(genR1DressLep1.Eta());
	Dr01LepPhi_->push_back(genR1DressLep1.Phi());
	Dr01LepE_->push_back(genR1DressLep1.Energy());
	Dr01LepM_->push_back(genR1DressLep1.M());
	Dr01LepId_->push_back(id);
	Dr01LepMomId_->push_back(id);
	Dr01LepStatus_->push_back(st);

	Bare01LepPt_->push_back(genLep1.Pt());
	Bare01LepEta_->push_back(genLep1.Eta());
	Bare01LepPhi_->push_back(genLep1.Phi());
	Bare01LepE_->push_back(genLep1.Energy());
	Bare01LepM_->push_back(genLep1.M());
	Bare01LepId_->push_back(id);
	Bare01LepMomId_->push_back(id);
	Bare01LepStatus_->push_back(st);
      }
    }
  }
}

void Tupel::processGenJets(const edm::Event& iEvent){
  //matrix element info
  Handle<LHEEventProduct> lheH;
  iEvent.getByLabel(lheSource_,lheH);//to be modularized!!!
  if(lheH.isValid()) *nup_ = lheH->hepeup().NUP;
  edm::Handle<reco::GenJetCollection> genjetColl;
  //iEvent.getByLabel("ak5GenJets", genjetColl);
  iEvent.getByLabel(gjetSrc_, genjetColl);
  if(!genjetColl.failedToGet()){
    const reco::GenJetCollection & genjet = *genjetColl;
    for(unsigned int k=0; k<genjetColl->size(); ++k){
      GjPt_->push_back(genjet[k].pt());
      Gjeta_->push_back(genjet[k].eta());
      Gjphi_->push_back(genjet[k].phi());
      GjE_->push_back(genjet[k].energy());
      GjPx_->push_back(genjet[k].px());
      GjPy_->push_back(genjet[k].py());
      GjPz_->push_back(genjet[k].pz());
      //double isChargedJet=false;
      //double chargedFraction = 0.;
      //std::vector<const GenParticle*> mcparticles = genjet[k].getGenConstituents();
      //for(std::vector <const GenParticle*>::const_iterator thepart =mcparticles.begin();thepart != mcparticles.end(); ++ thepart ) {
      //  if ( (**thepart).charge()!=0 ){
      //isChargedJet=true;
      //    chargedFraction += (**thepart).pt();
      //  }
      //}
      //if ( chargedFraction == 0 ) cout << " is chargeid: " << isChargedJet << "   " << chargedFraction/genjet[k].pt()<< endl;
      //GjChargedFraction_->push_back(chargedFraction/genjet[k].pt());
      /*if(genjet[k].numberOfDaughters()>0){
	for(unsigned int idx =0; idx<genjet[k].numberOfDaughters();idx++){
	//cout<<genjet[k].numberOfDaughters()<<" GEN AHMEEEEET "<<idx<<"  "<<genjet[k].daughter(idx)->pdgId()<<"  "<<endl;
	GjDoughterId_->push_back(genjet[k].daughter(idx)->pdgId());
	GjDoughterPt_->push_back(genjet[k].daughter(idx)->pt());
	GjDoughterEta_->push_back(genjet[k].daughter(idx)->eta());
	GjDoughterPhi_->push_back(genjet[k].daughter(idx)->phi());
	GjDoughterE_->push_back(genjet[k].daughter(idx)->energy());
	}
	}*/
    }
  }
}

void Tupel::processPdfInfo(const edm::Event& iEvent){
  edm::Handle<GenEventInfoProduct> genEventInfoProd;
  if (iEvent.getByLabel("generator", genEventInfoProd)) {
    if (genEventInfoProd->hasBinningValues()){
      *ptHat_ = genEventInfoProd->binningValues()[0];
    }
    *mcWeight_  = genEventInfoProd->weight();
    *mcWeights_ = genEventInfoProd->weights();
  }
  /// now get the PDF information
  edm::Handle<GenEventInfoProduct> pdfInfoHandle;
  if (iEvent.getByLabel("generator", pdfInfoHandle)) {
    if (pdfInfoHandle->pdf()) {
      id1_pdfInfo_->push_back(pdfInfoHandle->pdf()->id.first);
      id2_pdfInfo_->push_back(pdfInfoHandle->pdf()->id.second);
      x1_pdfInfo_->push_back(pdfInfoHandle->pdf()->x.first);
      x2_pdfInfo_->push_back(pdfInfoHandle->pdf()->x.second);
      //pdfInfo_->push_back(pdfInfoHandle->pdf()->xPDF.first);
      //dfInfo_->push_back(pdfInfoHandle->pdf()->xPDF.second);
      scalePDF_pdfInfo_->push_back(pdfInfoHandle->pdf()->scalePDF);
    }   
  }   
}

void Tupel::processTrigger(const edm::Event& iEvent){

  int Mu17_Mu8=0;
  int Mu17_TkMu8=0;
  int Elec17_Elec8=0;
  
  int ntrigs;
  vector<string> trigname;
  vector<bool> trigaccept;
  edm::Handle< edm::TriggerResults > HLTResHandle;
  edm::InputTag HLTTag = edm::InputTag( "TriggerResults", "", "HLT");
  iEvent.getByLabel(HLTTag, HLTResHandle);
  if ( HLTResHandle.isValid() && !HLTResHandle.failedToGet() ) {
    edm::RefProd<edm::TriggerNames> trigNames( &(iEvent.triggerNames( *HLTResHandle )) );
    ntrigs = (int)trigNames->size();
    for (int i = 0; i < ntrigs; i++) {
      trigname.push_back(trigNames->triggerName(i));
      trigaccept.push_back(HLTResHandle->accept(i));
      if (trigaccept[i]){
	if(std::string(trigname[i]).find("HLT_Mu17_Mu8")!=std::string::npos) Mu17_Mu8=1;
	if(std::string(trigname[i]).find("HLT_Mu17_TkMu8")!=std::string::npos) Mu17_TkMu8=1;
	if(std::string(trigname[i]).find("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL")!=std::string::npos) Elec17_Elec8=1;
      }
    }
    }

  *HLT_Mu17_Mu8_ = Mu17_Mu8;
  *HLT_Mu17_TkMu8_ = Mu17_TkMu8;
  *HLT_Elec17_Elec8_ = Elec17_Elec8;
  
}

void Tupel::processMuons(){
  double MuFill = 0;
  double Mu17_Mu8_Matched = 0;
  double Mu17_TkMu8_Matched = 0;
  
  for (unsigned int j = 0; j < muons->size(); ++j){
    const edm::View<pat::Muon> & mu = *muons;
    if(mu[j].isGlobalMuon()){ 
      //const pat::TriggerObjectRef trigRef( matchHelper.triggerMatchObject( muons,j,muonMatch_, iEvent, *triggerEvent ) );
      //if ( trigRef.isAvailable() && trigRef.isNonnull() ) {
      //  Mu17_Mu8_Matched=1;
      //	}
      //	const pat::TriggerObjectRef trigRef2( matchHelper.triggerMatchObject( muons,j,muonMatch2_, iEvent, *triggerEvent ) );
      //	if ( trigRef2.isAvailable() && trigRef2.isNonnull() ) {
      //	  Mu17_TkMu8_Matched=1;
      //	}
      patMuon_Mu17_Mu8_Matched_->push_back(Mu17_Mu8_Matched);
      patMuon_Mu17_TkMu8_Matched_->push_back(Mu17_TkMu8_Matched);
	  
      patMuonIdLoose_->push_back(mu[j].isLooseMuon());
      //patMuonIdMedium_->push_back(mu[j].isMediumMuon()); Requires CMSSW >= 4_7_2
      if(vtxx){
	unsigned bit = 0;
	unsigned muonTightIds = 0;
	for (edm::View<reco::Vertex>::const_iterator vtx = pvHandle->begin(); vtx != pvHandle->end(); ++vtx){
	  if(vtx->isValid() && !vtx->isFake() && mu[j].isTightMuon(*vtx)){
	    muonTightIds |= (1 <<bit);
	  }
	  ++bit;
	  if(bit > 31) break;
	}
	patMuonIdTight_->push_back(muonTightIds);
      }
	  
	  
      //MuFill=1;
      patMuonPt_->push_back(mu[j].pt());
      patMuonEta_->push_back(mu[j].eta());
      patMuonPhi_->push_back(mu[j].phi());
      patMuonEn_->push_back(mu[j].energy());
      patMuonCharge_->push_back(mu[j].charge());
      patMuonVtxZ_->push_back(mu[j].vz());
      patMuonM_->push_back(mu[j].mass());
      patMuonPx_->push_back(mu[j].px());
      patMuonPy_->push_back(mu[j].py());
      patMuonPz_->push_back(mu[j].pz());
      patMuonDxy_->push_back(mu[j].dB());
	
      double trkLayers = -99999;
      double pixelHits = -99999;
      double muonHits  = -99999;
      double nMatches  = -99999;
      double normChi2  = +99999;
      double dZ = -99999;
      bool isTrackMuon =mu[j].isTrackerMuon();
      bool isGlobalMuon =mu[j].isGlobalMuon();
      if(isTrackMuon && isGlobalMuon){
	trkLayers     = mu[j].innerTrack()->hitPattern().trackerLayersWithMeasurement();
	pixelHits     = mu[j].innerTrack()->hitPattern().numberOfValidPixelHits();
	muonHits      = mu[j].globalTrack()->hitPattern().numberOfValidMuonHits();
	nMatches      = mu[j].numberOfMatchedStations();
	normChi2      = mu[j].globalTrack()->normalizedChi2();
	if( !pvHandle->empty() && !pvHandle->front().isFake() ) {
	  const reco::Vertex &vtx = pvHandle->front();
	  dZ= mu[j].muonBestTrack()->dz(vtx.position());
	}
      }
      patMuonChi2Ndoff_->push_back(normChi2);
      patMuonNhits_->push_back(muonHits);
      patMuonNMatches_->push_back(nMatches);
      patMuonDz_->push_back(dZ);
      patMuonPhits_->push_back(pixelHits);
      patMuonTkLayers_->push_back(trkLayers);
	
      int idpass=0;
      if(mu[j].isGlobalMuon() && mu[j].isPFMuon() && normChi2<10 && muonHits>0 && nMatches>1 && mu[j].dB()<0.2 && dZ<0.5 && pixelHits>0 && trkLayers>5)idpass=1;
      patMuonCombId_->push_back(idpass);
      int TrigSum=0;
      if(Mu17_Mu8_Matched==1) TrigSum=1;
      patMuonTrig_->push_back(TrigSum);
      float muEta = mu[j].eta(); // essentially track direction at Vtx (recommended prescription)
      float Aecal=0.041; // initiallize with EE value
      float Ahcal=0.032; // initiallize with HE value
      if (fabs(muEta)<1.48) {
	Aecal = 0.074;   // substitute EB value 
	Ahcal = 0.023;   // substitute EE value
      } 
      double theRho = *rho;
      float muonIsoRho = mu[j].isolationR03().sumPt + std::max(0.,(mu[j].isolationR03().emEt -Aecal*(theRho))) + std::max(0.,(mu[j].isolationR03().hadEt-Ahcal*(theRho)));
      double dbeta = muonIsoRho/mu[j].pt();
      patMuonDetIsoRho_->push_back(dbeta);
	  
      // pf Isolation variables
      double chargedHadronIso = mu[j].pfIsolationR04().sumChargedHadronPt;
      double chargedHadronIsoPU = mu[j].pfIsolationR04().sumPUPt;  
      double neutralHadronIso  = mu[j].pfIsolationR04().sumNeutralHadronEt;
      double photonIso  = mu[j].pfIsolationR04().sumPhotonEt;
      double a=0.5;  
      // OPTION 1: DeltaBeta corrections for iosolation
      float RelativeIsolationDBetaCorr = (chargedHadronIso + std::max(photonIso+neutralHadronIso - 0.5*chargedHadronIsoPU,0.))/std::max(a, mu[j].pt());
      patMuonPfIsoDbeta_->push_back(RelativeIsolationDBetaCorr);
      patMuonGlobalType_->push_back(mu[j].isGlobalMuon());
      patMuonTrackerType_->push_back(mu[j].isTrackerMuon());
      patMuonPFType_->push_back(mu[j].isPFMuon());
      patMuonIsoSumPt_->push_back(mu[j].isolationR03().sumPt);
      patMuonIsoRelative_->push_back(mu[j].isolationR03().sumPt/mu[j].pt());
      patMuonIsoCalComb_->push_back(mu[j].isolationR03().emEt + mu[j].isolationR03().hadEt);
      patMuonIsoDY_->push_back((mu[j].isolationR03().sumPt+mu[j].isolationR03().hadEt)/mu[j].pt());
      patMuon_PF_IsoSumChargedHadronPt_->push_back(mu[j].pfIsolationR03().sumChargedHadronPt);
      patMuon_PF_IsoSumNeutralHadronEt_->push_back(mu[j].pfIsolationR03().sumNeutralHadronEt);
      patMuon_PF_IsoDY_->push_back((mu[j].pfIsolationR03().sumChargedHadronPt+mu[j].pfIsolationR03().sumNeutralHadronEt)/mu[j].pt());
      MuFill++;
    }
  }
}

void Tupel::processElectrons(){
  int ElecFill=0;
  auto_ptr<vector<pat::Electron> > electronColl( new vector<pat::Electron> (*electrons) );
  for (unsigned int j=0; j < electronColl->size();++j){
    pat::Electron & el = (*electronColl)[j];

    double dEtaIn_;
    double dPhiIn_;
    double hOverE_;
    double sigmaIetaIeta_;
    double full5x5_sigmaIetaIeta_;
    //double relIsoWithDBeta_;
    double ooEmooP_;
    double d0_;
    double dz_;
    int   expectedMissingInnerHits_;
    int   passConversionVeto_;     

    std::vector<std::pair<std::string,float> > idlist = el.electronIDs();
    if(!elecIdsListed_) {
      std::cout << "Supported electron ids:\n"; 
      for (unsigned k  = 0 ; k < idlist.size(); ++k){
	std::cout << idlist[k].first << ": " << idlist[k].second  << "\n";
      }
      std::cout << std::flush;
      elecIdsListed_ = true;
    }
    unsigned elecid = 0;
      
    if(el.electronID(std::string("cutBasedElectronID-CSA14-50ns-V1-standalone-veto"))) elecid |= 1;
    if(el.electronID(std::string("cutBasedElectronID-CSA14-50ns-V1-standalone-loose"))) elecid |= 2;
    if(el.electronID(std::string("cutBasedElectronID-CSA14-50ns-V1-standalone-medium"))) elecid |= 4;
    if(el.electronID(std::string("cutBasedElectronID-CSA14-50ns-V1-standalone-tight"))) elecid |= 8;
    patElecId_->push_back(elecid);
      
    dEtaIn_ = el.deltaEtaSuperClusterTrackAtVtx();
    dPhiIn_ = el.deltaPhiSuperClusterTrackAtVtx();
    hOverE_ = el.hcalOverEcal();
    sigmaIetaIeta_ = el.sigmaIetaIeta();
    full5x5_sigmaIetaIeta_ =  el.full5x5_sigmaIetaIeta();
    if( el.ecalEnergy() == 0 ){
      // printf("Electron energy is zero!\n");
      ooEmooP_ = 1e30;
    }else if( !std::isfinite(el.ecalEnergy())){
      // printf("Electron energy is not finite!\n");
      ooEmooP_ = 1e30;
    }else{
      ooEmooP_ = fabs(1.0/el.ecalEnergy() - el.eSuperClusterOverP()/el.ecalEnergy() );
    }

    d0_ = (-1) * el.gsfTrack()->dxy(vtx_h->at(0).position() );
    dz_ = el.gsfTrack()->dz( vtx_h->at(0).position() );



    //     expectedMissingInnerHits_ = el.gsfTrack()->trackerExpectedHitsInner().numberOfLostHits();//MISSING!!
    passConversionVeto_ = false;
    if( beamSpotHandle.isValid() && conversions_h.isValid()) {
      passConversionVeto_ = !ConversionTools::hasMatchedConversion(el,conversions_h,
								   beamSpotHandle->position());
    }else{
      printf("\n\nERROR!!! conversions not found!!!\n");
    }


    //cout<<dEtaIn_<<"  "<<dPhiIn_<<"  "<<hOverE_<<"  "<<sigmaIetaIeta_<<"  "<<full5x5_sigmaIetaIeta_<<"  "<<ooEmooP_<<"  "<< d0_<<"  "<< dz_<<"  "<<expectedMissingInnerHits_<<"  "<<passConversionVeto_<<endl;

    patElecdEtaIn_->push_back(dEtaIn_);
    patElecdPhiIn_->push_back(dPhiIn_);
    patElechOverE_->push_back(hOverE_);
    patElecsigmaIetaIeta_->push_back(sigmaIetaIeta_);
    patElecfull5x5_sigmaIetaIeta_->push_back(full5x5_sigmaIetaIeta_);
    patElecooEmooP_->push_back(ooEmooP_);
    patElecd0_->push_back(d0_);
    patElecdz_->push_back(dz_);
    patElecexpectedMissingInnerHits_->push_back(expectedMissingInnerHits_);
    patElecpassConversionVeto_->push_back(passConversionVeto_);     

    double Elec17_Elec8_Matched=0;
      
    patElecTrig_->push_back(Elec17_Elec8_Matched);//no matching yet...BB 
    reco::Vertex::Point pos(0,0,0);
    if(vtx_h->size() > 0) pos = vtx_h->at(0).position();
    patElecDz_->push_back(el.gsfTrack()->dz(pos));
    const string mvaTrigV0 = "mvaTrigV0";
    const string mvaNonTrigV0 = "mvaNonTrigV0";
      
    patElecPt_->push_back(el.pt());
    patElecEta_->push_back(el.eta());
      
    patElecScEta_->push_back(el.superCluster()->eta());
    patElecPhi_->push_back(el.phi());	
    patElecEnergy_->push_back(el.energy());
    patElecCharge_->push_back(el.charge());
      
    *AEff_ = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, el.superCluster()->eta(), ElectronEffectiveArea::kEleEAData2012);
    *rhoPrime_ = std::max(rhoIso, 0.0);
      
    const double chIso03_ = el.chargedHadronIso();
    const double nhIso03_ = el.neutralHadronIso();
    const double phIso03_ = el.photonIso();
    const double puChIso03_= el.puChargedHadronIso();
    patElecchIso03_->push_back(chIso03_);
    patElecnhIso03_->push_back(nhIso03_);
    patElecphIso03_->push_back(phIso03_);
    patElecpuChIso03_->push_back(puChIso03_);
    patElecPfIso_->push_back(( chIso03_ + nhIso03_ + phIso03_ ) / el.pt());
    patElecPfIsodb_->push_back(( chIso03_ + max(0.0, nhIso03_ + phIso03_ - 0.5*puChIso03_) )/ el.pt());
    patElecPfIsoRho_->push_back(( chIso03_ + max(0.0, nhIso03_ + phIso03_ - (*rhoPrime_)*(*AEff_)) )/ el.pt());
      
    bool myTrigPresel = false;
    if(fabs(el.superCluster()->eta()) < 1.479){
      if(el.sigmaIetaIeta() < 0.014 &&
	 el.hadronicOverEm() < 0.15 &&
	 el.dr03TkSumPt()/el.pt() < 0.2 &&
	 el.dr03EcalRecHitSumEt()/el.pt() < 0.2 &&
	 el.dr03HcalTowerSumEt()/el.pt() < 0.2 /*&&
						 el.gsfTrack()->trackerExpectedHitsInner().numberOfLostHits() == 0*/)
	myTrigPresel = true;
    }
    else {
      if(el.sigmaIetaIeta() < 0.035 &&
	 el.hadronicOverEm() < 0.10 &&
	 el.dr03TkSumPt()/el.pt() < 0.2 &&
	 el.dr03EcalRecHitSumEt()/el.pt() < 0.2 &&
	 el.dr03HcalTowerSumEt()/el.pt() < 0.2 /*&&
						 el.gsfTrack()->trackerExpectedHitsInner().numberOfLostHits() == 0*/)
	myTrigPresel = true;
    }     
    patElec_mva_presel_->push_back(myTrigPresel);
    ElecFill++; 
  }
}    

void Tupel::processJets(){
  //double PFjetFill=0;
  double chf = 0;
  double nhf = 0;
  double cemf = 0;
  double nemf = 0;
  double cmult = 0;
  double nconst = 0;


  for ( unsigned int i=0; i<jets->size(); ++i ) {
    const pat::Jet & jet = jets->at(i);
       
    patJetPfAk05jetpuMVA_->push_back(jet.userFloat("pileupJetId:fullDiscriminant"));
    chf = jet.chargedHadronEnergyFraction();
    nhf = (jet.neutralHadronEnergy()+jet.HFHadronEnergy())/jet.correctedJet(0).energy();
    cemf = jet.chargedEmEnergyFraction();
    nemf = jet.neutralEmEnergyFraction();
    cmult = jet.chargedMultiplicity();
    nconst = jet.numberOfDaughters();
      
    //  cout<<"jet.bDiscriminator(combinedSecondaryVertexBJetTags)=  "<<jet.bDiscriminator("combinedSecondaryVertexBJetTags")<<endl;
    //  cout<<"jet.bDiscriminator(combinedSecondaryVertexV1BJetTags)=  "<<jet.bDiscriminator("combinedSecondaryVertexV1BJetTags")<<endl;
    //  cout<<"jet.bDiscriminator(combinedSecondaryVertexSoftPFLeptonV1BJetTags)=  "<<jet.bDiscriminator("combinedSecondaryVertexSoftPFLeptonV1BJetTags")<<endl;
    patJetPfAk05BDiscCSV_->push_back(jet.bDiscriminator("combinedSecondaryVertexBJetTags"));
    patJetPfAk05BDiscCSVV1_->push_back(jet.bDiscriminator("combinedSecondaryVertexV1BJetTags"));
    patJetPfAk05BDiscCSVSLV1_->push_back(jet.bDiscriminator("combinedSecondaryVertexSoftPFLeptonV1BJetTags"));
      
    patJetPfAk05En_->push_back(jet.energy());
    patJetPfAk05Pt_->push_back(jet.pt());
    patJetPfAk05Eta_->push_back(jet.eta());
    patJetPfAk05Phi_->push_back(jet.phi());
    patJetPfAk05Et_->push_back(jet.et());
    patJetPfAk05RawPt_->push_back(jet.correctedJet(0).pt());
    patJetPfAk05RawEn_->push_back(jet.correctedJet(0).energy());
    patJetPfAk05HadEHF_->push_back(jet.HFHadronEnergy());
    patJetPfAk05EmEHF_->push_back(jet.HFEMEnergy());
    patJetPfAk05chf_->push_back(chf);
    patJetPfAk05nhf_->push_back(nhf);
    patJetPfAk05cemf_->push_back(cemf);
    patJetPfAk05nemf_->push_back(nemf);
    patJetPfAk05cmult_->push_back(cmult);
    patJetPfAk05nconst_->push_back(nconst);
  
    for(unsigned int idx =0; idx<jet.numberOfDaughters();idx++){
      // cout<<jet.numberOfDaughters()<<" RECO AHMEEEEET "<<idx<<"  "<<jet.daughter(idx)->pdgId()<<"  "<<endl;
      patJetPfAk05DoughterId_->push_back(jet.daughter(idx)->pdgId());
      patJetPfAk05DoughterPt_->push_back(jet.daughter(idx)->pt());
      patJetPfAk05DoughterEta_->push_back(jet.daughter(idx)->eta());
      patJetPfAk05DoughterPhi_->push_back(jet.daughter(idx)->phi());
      patJetPfAk05DoughterE_->push_back(jet.daughter(idx)->energy());


    }
    double unc = 1.;
    unc_->push_back(unc);
    double up = (1+unc)*jet.pt();
    double down = (1-unc)*jet.pt();
    patJetPfAk05PtUp_->push_back(up);
    patJetPfAk05PtDn_->push_back(down);
    double tempJetID=0;
    if( abs(jet.eta())<2.4){
      if(chf>0 && nhf<0.99 && cmult>0.0 && cemf<0.99 && nemf<0.99 && nconst>1) tempJetID=1;
      if((chf>0)&&(nhf<0.95)&&(cmult>0.0)&&(cemf<0.99)&&(nemf<0.95)&&(nconst>1)) tempJetID=2; 
      if((chf>0)&&(nhf<0.9)&&(cmult>0.0)&&(cemf<0.99)&&(nemf<0.9)&&(nconst>1)) tempJetID=3;
    }
    if( abs(jet.eta())>=2.4){
      if ((nhf<0.99)&&(nemf<0.99)&&(nconst>1))tempJetID=1;
      if ((nhf<0.95)&&(nemf<0.95)&&(nconst>1))tempJetID=2; 
      if ((nhf<0.9)&&(nemf<0.9)&&(nconst>1))tempJetID=3;
    }
    patJetPfAk05LooseId_->push_back(tempJetID);//ala 
    //PFjetFill++;
      
    if(!*realdata_){
      bool matchGen=false;
      if (jet.genJet()){
	matchGen=true;
	MGjPt_->push_back(jet.genJet()->pt());
	MGjeta_->push_back(jet.genJet()->eta());
	MGjphi_->push_back(jet.genJet()->phi());
	MGjE_->push_back(jet.genJet()->energy());
      }
      matchGjet_->push_back(matchGen);
    }
  }
}

void Tupel::processPhotons(){
  for (unsigned j = 0; j < photons->size(); ++j){
    const pat::Photon& photon = (*photons)[j];
    //photon momentum
    PhotonPt_->push_back(photon.pt());
    PhotonEta_->push_back(photon.eta());
    PhotonPhi_->push_back(photon.phi());

    //photon isolation
    PhotonIsoEcal_->push_back(photon.ecalIso());
    PhotonIsoHcal_->push_back(photon.hcalIso());
    PhotonPfIsoChargdH_->push_back(photon.chargedHadronIso());
    PhotonPfIsoNeutralH_->push_back(photon.neutralHadronIso());
    PhotonPfIsoPhoton_->push_back(photon.photonIso());
    PhotonPfIsoPuChargedH_->push_back(photon.puChargedHadronIso());
    PhotonPfIsoEcalCluster_->push_back(photon.ecalPFClusterIso());
    PhotonPfIsoHcalCluster_->push_back(photon.hcalPFClusterIso());
      
    //photon cluster shape
    PhotonE3x3_->push_back(photon.e3x3());
    PhotonSigmaIetaIeta_->push_back(photon.sigmaIetaIeta());

    //photon ids:
    std::vector<std::pair<std::string,Bool_t> > idlist = photon.photonIDs();
    if(!photonIdsListed_) {
      std::cout << "Supported photon ids:\n"; 
      for (unsigned k  = 0 ; k < idlist.size(); ++k){
	std::cout << idlist[k].first << ": " << (idlist[k].second ? "yes" : "no") << "\n";
      }
      std::cout << std::flush;
      photonIdsListed_ = true;
    }

    int photonId = 0;
    if(photon.photonID(std::string("PhotonCutBasedIDLoose"))) photonId |= 1;
    if(photon.photonID(std::string("PhotonCutBasedIDTight"))) photonId |= 4;
    PhotonId_->push_back(photonId);
    PhotonHoE_->push_back(photon.hadronicOverEm()); 
    PhotonHasPixelSeed_->push_back(photon.hasPixelSeed());
  }
}

void Tupel::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  using namespace edm; //ADD
  ++ccnevent;

  readEvent(iEvent);

  // PAT trigger event
  //edm::Handle<pat::TriggerEvent>  triggerEvent;
  //iEvent.getByLabel( triggerEvent_, triggerEvent );
  

  // edm::Handle<edm::ValueMap<float> > full5x5sieie;
  // iEvent.getByToken(full5x5SigmaIEtaIEtaMapToken_,full5x5sieie);
  
  processMET(iEvent);

  processVtx();

  if (!*realdata_){
    processPu(iEvent);
    if (genParticles) processGenParticles(iEvent);
    processGenJets(iEvent);
    processPdfInfo(iEvent);
  }

  processTrigger(iEvent);

  if(muon) processMuons();

  //electrons B.B.
  if(electron) processElectrons();

  if(jettt) processJets();

  //photons. Ph. G.
  if(photons) processPhotons();

  //Stores the event in the output tree
  treeHelper_->fill();
  
}

void
Tupel::writeHeader(){
  TTree* t = new TTree("Header", "Header");
  TString checksum_(checksum);
  t->Branch("Tupel_cc_githash", &checksum_);
  t->Fill();
}

void 
Tupel::beginJob()
{
  
  //  jecUnc = new JetCorrectionUncertainty("Fall12_V7_DATA_Uncertainty_AK5PFchs.txt");
  // register to the TFileService
  edm::Service<TFileService> fs;
  TFileDirectory TestDir = fs->mkdir("test");

  writeHeader();

  myTree = new TTree("EventTree"," EventTree");
  treeHelper_ = std::auto_ptr<TreeHelper>(new TreeHelper(myTree, new TTree("Description", "Description")));
			      
  ADD_BRANCH(METPt);
  treeHelper_->addDescription("MET", "PF MET");
  ADD_BRANCH(METPx);
  ADD_BRANCH(METPy);
  ADD_BRANCH(METPz);
  ADD_BRANCH(METE);
  ADD_BRANCH(METsigx2);
  ADD_BRANCH(METsigxy);
  ADD_BRANCH(METsigy2);
  ADD_BRANCH(METsig);
  ADD_BRANCH_D(event, "Event number");
  ADD_BRANCH_D(realdata, "True if real data, false if MC");
  ADD_BRANCH_D(run, "Run number");
  ADD_BRANCH_D(lumi, "Luminosity block number");
  ADD_BRANCH_D(bxnumber, "Bunch crossing number");
  ADD_BRANCH(EvtInfo_NumVtx);
  ADD_BRANCH(PU_npT);
  ADD_BRANCH(PU_npIT);
  ADD_BRANCH(MyWeight);
  ADD_BRANCH(Dr01LepPt);
  ADD_BRANCH(Dr01LepEta);
  ADD_BRANCH(Dr01LepPhi);
  ADD_BRANCH(Dr01LepE);
  ADD_BRANCH(Dr01LepM);
  ADD_BRANCH(Dr01LepId);
  ADD_BRANCH(Dr01LepStatus);
  ADD_BRANCH(Dr01LepMomId);
  ADD_BRANCH(Bare01LepPt);
  ADD_BRANCH(Bare01LepEta);
  ADD_BRANCH(Bare01LepPhi);
  ADD_BRANCH(Bare01LepE);
  ADD_BRANCH(Bare01LepM);
  ADD_BRANCH(Bare01LepId);
  ADD_BRANCH(Bare01LepStatus);
  ADD_BRANCH(Bare01LepMomId);      
  ADD_BRANCH(St03Pt);
  ADD_BRANCH(St03Eta);
  ADD_BRANCH(St03Phi);
  ADD_BRANCH(St03E);
  ADD_BRANCH(St03M);
  ADD_BRANCH(St03Id);
  ADD_BRANCH(St03Status);
  ADD_BRANCH(St03MotherId);
  ADD_BRANCH(St03NumberMom);    


  ADD_BRANCH(St01PhotonPt);
  ADD_BRANCH(St01PhotonEta);
  ADD_BRANCH(St01PhotonPhi);
  ADD_BRANCH(St01PhotonE);
  ADD_BRANCH(St01PhotonM);
  ADD_BRANCH(St01PhotonId);
  ADD_BRANCH(St01PhotonMomId);
  ADD_BRANCH(St01PhotonNumberMom);
  ADD_BRANCH(St01PhotonStatus);
    
  ADD_BRANCH(GjPt);
  ADD_BRANCH(Gjeta);
  ADD_BRANCH(Gjphi);
  ADD_BRANCH(GjE);
  ADD_BRANCH(GjPx);
  ADD_BRANCH(GjPy);
  ADD_BRANCH(GjPz);
  ADD_BRANCH(GjChargedFraction);
  ADD_BRANCH(matchGjet);

  ADD_BRANCH(GjDoughterId);
  ADD_BRANCH(GjDoughterPt);
  ADD_BRANCH(GjDoughterEta);
  ADD_BRANCH(GjDoughterPhi);
  ADD_BRANCH(GjDoughterE);

  ADD_BRANCH(MGjPt);
  ADD_BRANCH(MGjeta);
  ADD_BRANCH(MGjphi);
  ADD_BRANCH(MGjE); 
    
  //HLT
  ADD_BRANCH(HLT_Mu17_Mu8);
  ADD_BRANCH(HLT_Mu17_TkMu8);
  ADD_BRANCH(HLT_Elec17_Elec8);
    
  //Muons
  ADD_BRANCH(patMuonPt);
  ADD_BRANCH(patMuonEta);
  ADD_BRANCH(patMuonPhi);
  ADD_BRANCH(patMuonVtxZ);
  ADD_BRANCH(patMuonEn);
  ADD_BRANCH(patMuonCharge);
  ADD_BRANCH(patMuonDxy);
  ADD_BRANCH(patMuonCombId);
  ADD_BRANCH(patMuonTrig);
  ADD_BRANCH(patMuonDetIsoRho);
  ADD_BRANCH(patMuonPfIsoDbeta);
  ADD_BRANCH(patMuonM);
  ADD_BRANCH(patMuonPx);
  ADD_BRANCH(patMuonPy);
  ADD_BRANCH(patMuonPz);
  ADD_BRANCH(patMuonGlobalType);
  ADD_BRANCH(patMuonTrackerType);
  ADD_BRANCH(patMuonPFType);
  ADD_BRANCH(patMuonIsoSumPt);
  ADD_BRANCH(patMuonIsoRelative);
  ADD_BRANCH(patMuonIsoCalComb);
  ADD_BRANCH(patMuonIsoDY);
  ADD_BRANCH(patMuonChi2Ndoff);
  ADD_BRANCH(patMuonNhits);
  ADD_BRANCH(patMuonNMatches);
  ADD_BRANCH(patMuonDz);
  ADD_BRANCH(patMuonPhits);
  ADD_BRANCH(patMuonTkLayers);
  ADD_BRANCH(patMuon_PF_IsoSumChargedHadronPt);
  ADD_BRANCH(patMuon_PF_IsoSumNeutralHadronEt);
  ADD_BRANCH(patMuon_PF_IsoDY);
  ADD_BRANCH(patMuon_Mu17_Mu8_Matched);
  ADD_BRANCH(patMuon_Mu17_TkMu8_Matched);
  ADD_BRANCH(patMuonIdLoose);
  ADD_BRANCH(patMuonIdMedium);
  ADD_BRANCH(patMuonIdTight);


  ADD_BRANCH(patElecdEtaIn);
  ADD_BRANCH(patElecdPhiIn);
  ADD_BRANCH(patElechOverE);
  ADD_BRANCH(patElecsigmaIetaIeta);
  ADD_BRANCH(patElecfull5x5_sigmaIetaIeta);
  ADD_BRANCH(patElecooEmooP);
  ADD_BRANCH(patElecd0);
  ADD_BRANCH(patElecdz);
  ADD_BRANCH(patElecexpectedMissingInnerHits);
  ADD_BRANCH(patElecpassConversionVeto);     
  ADD_BRANCH(patElecTrig);
  ADD_BRANCH(patElecDz);
  ADD_BRANCH(patElecMVATrigId);
  ADD_BRANCH(patElecMVANonTrigId);
  ADD_BRANCH(patElecPt);
  ADD_BRANCH(patElecEta);
  ADD_BRANCH(patElecScEta);
  ADD_BRANCH(patElecPhi);
  ADD_BRANCH(patElecEnergy);
  ADD_BRANCH(patElecCharge);
  ADD_BRANCH(patElecMediumIDOff);
  ADD_BRANCH(patElecMediumIDOff_Tom);

  ADD_BRANCH(patElecchIso03);
  ADD_BRANCH(patElecnhIso03);
  ADD_BRANCH(patElecphIso03);
  ADD_BRANCH(patElecpuChIso03);
  ADD_BRANCH(patElecPfIso);
  ADD_BRANCH(patElecPfIsodb);
  ADD_BRANCH(patElecPfIsoRho);
  ADD_BRANCH(patElecId);
  ADD_BRANCH(rhoPrime);
  ADD_BRANCH(neutral);
  ADD_BRANCH(photon);
  ADD_BRANCH(charged);
  ADD_BRANCH(neutral_Tom);
  ADD_BRANCH(photon_Tom);
  ADD_BRANCH(charged_Tom);
  ADD_BRANCH(AEff);
  ADD_BRANCH(patElec_mva_presel);
    
  //PFJet
  ADD_BRANCH(patJetPfAk05En);
  ADD_BRANCH(patJetPfAk05Pt);
  ADD_BRANCH(patJetPfAk05Eta);
  ADD_BRANCH(patJetPfAk05Phi);
  ADD_BRANCH(patJetPfAk05LooseId);
  ADD_BRANCH(patJetPfAk05Et);
  ADD_BRANCH(patJetPfAk05RawPt);
  ADD_BRANCH(patJetPfAk05RawEn);
  ADD_BRANCH(patJetPfAk05HadEHF);
  ADD_BRANCH(patJetPfAk05EmEHF);
  ADD_BRANCH(patJetPfAk05chf);
  ADD_BRANCH(patJetPfAk05nhf);
  ADD_BRANCH(patJetPfAk05cemf);
  ADD_BRANCH(patJetPfAk05nemf);
  ADD_BRANCH(patJetPfAk05cmult);
  ADD_BRANCH(patJetPfAk05nconst);
  ADD_BRANCH(patJetPfAk05jetBeta);
  ADD_BRANCH(patJetPfAk05jetBetaClassic);
  ADD_BRANCH(patJetPfAk05jetBetaStar);
  ADD_BRANCH(patJetPfAk05jetBetaStarClassic);
  ADD_BRANCH(patJetPfAk05jetpuMVA);
  ADD_BRANCH(patJetPfAk05jetpukLoose);
  ADD_BRANCH(patJetPfAk05jetpukMedium);
  ADD_BRANCH(patJetPfAk05jetpukTight);
  ADD_BRANCH(patJetPfAk05BDiscCSV);
  ADD_BRANCH(patJetPfAk05BDiscCSVV1);
  ADD_BRANCH(patJetPfAk05BDiscCSVSLV1);
  ADD_BRANCH(unc);
  ADD_BRANCH(patJetPfAk05DoughterId);
  ADD_BRANCH(patJetPfAk05DoughterPt);
  ADD_BRANCH(patJetPfAk05DoughterEta);
  ADD_BRANCH(patJetPfAk05DoughterPhi);
  ADD_BRANCH(patJetPfAk05DoughterE);

  ADD_BRANCH(patJetPfAk05PtUp);
  ADD_BRANCH(patJetPfAk05PtDn); 

  //CaloJets
  ADD_BRANCH(caloJetPt);
  ADD_BRANCH(caloJetRawPt);
  ADD_BRANCH(caloJetEn);
  ADD_BRANCH(caloJetEta);
  ADD_BRANCH(caloJetPhi);
  ADD_BRANCH(caloJetHadEHF);
  ADD_BRANCH(caloJetEmEHF);
  ADD_BRANCH(caloJetEmFrac);
  ADD_BRANCH(caloJetn90);


  //photon momenta
  ADD_BRANCH(PhotonPt);;
  ADD_BRANCH(PhotonEta);;
  ADD_BRANCH(PhotonPhi);;
  
  //photon isolations
  ADD_BRANCH(PhotonIsoEcal);
  ADD_BRANCH(PhotonIsoHcal);
  ADD_BRANCH(PhotonPfIsoChargdH);
  ADD_BRANCH(PhotonPfIsoNeutralH);
  ADD_BRANCH(PhotonPfIsoPhoton);
  ADD_BRANCH(PhotonPfIsoPuChargedH);
  ADD_BRANCH(PhotonPfIsoEcalCluster);
  ADD_BRANCH(PhotonPfIsoHcalCluster);
  
  //photon cluster shapes
  ADD_BRANCH(PhotonE3x3);
  ADD_BRANCH(PhotonSigmaIetaIeta);
  ADD_BRANCH(PhotonHoE);

  //photon ID
  ADD_BRANCH(PhotonId);
  ADD_BRANCH(PhotonHasPixelSeed);
  
  ADD_BRANCH(id1_pdfInfo);
  ADD_BRANCH(id2_pdfInfo);
  ADD_BRANCH(x1_pdfInfo);
  ADD_BRANCH(x2_pdfInfo);
  ADD_BRANCH(scalePDF_pdfInfo);
  ADD_BRANCH(ptHat);
  ADD_BRANCH(mcWeight);
  ADD_BRANCH(mcWeights);
  ADD_BRANCH(nup);   
}

void 
Tupel::endJob() 
{
  //  delete jecUnc;
  //  myTree->Print();
}

DEFINE_FWK_MODULE(Tupel);
