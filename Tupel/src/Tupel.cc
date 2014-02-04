/*

Code by: Bugra Bilin, Kittikul Kovitanggoon, Tomislav Seva, Efe Yazgan, ...

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
#include "CMGTools/External/interface/PileupJetIdentifier.h"
#include "EgammaAnalysis/ElectronTools/interface/PFIsolationEstimator.h"

#include "FWCore/Framework/interface/MakerMacros.h"

#include "DataFormats/BTauReco/interface/JetTag.h"

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

  // input tags
  edm::InputTag trigger_;
  edm::InputTag triggerEvent_;
  edm::InputTag triggerSummaryLabel_;
  std::string elecMatch_;
  std::string muonMatch_;
  std::string muonMatch2_;
  edm::InputTag photonSrc_;
  edm::InputTag elecSrc_;
  edm::InputTag muonSrc_;
  edm::InputTag tauSrc_;
  edm::InputTag jetSrc_;
  edm::InputTag metSrc_;
  edm::InputTag mSrcRho_;
  edm::InputTag CaloJet_;
  // ----------member data ---------------------------
  TTree *myTree;
  double MyWeight;
  int event,realdata,run,lumi,bxnumber;
  double EvtInfo_NumVtx,PU_npT,PU_npIT,nup;
  //particles
  std::vector<double> Dr01LepPt;
  std::vector<double> Dr01LepEta;
  std::vector<double> Dr01LepPhi;
  std::vector<double> Dr01LepE;
  std::vector<double> Dr01LepM;
  std::vector<double> Dr01LepId;
  std::vector<double> Dr01LepStatus;
  std::vector<double> Bare01LepPt;
  std::vector<double> Bare01LepEta;
  std::vector<double> Bare01LepPhi;
  std::vector<double> Bare01LepE;
  std::vector<double> Bare01LepM;
  std::vector<double> Bare01LepId;
  std::vector<double> Bare01LepStatus;
  std::vector<double> St03Pt;
  std::vector<double> St03Eta;
  std::vector<double> St03Phi;
  std::vector<double> St03E;
  std::vector<double> St03M;
  std::vector<double> St03Id;
  std::vector<double> St03Status;
  std::vector<double> St01PhotonPt;
  std::vector<double> St01PhotonEta;
  std::vector<double> St01PhotonPhi;
  std::vector<double> St01PhotonE;
  std::vector<double> St01PhotonM;
  std::vector<double> St01PhotonId;
  std::vector<double> St01PhotonMomId;
  std::vector<double> St01PhotonNumberMom;
  std::vector<double> St01PhotonStatus;
  std::vector<double> GjPt;
  std::vector<double> Gjeta;
  std::vector<double> Gjphi;
  std::vector<double> GjE;
  std::vector<double> GjPx;
  std::vector<double> GjPy;
  std::vector<double> GjPz;
  std::vector<double> GjChargedFraction;
  std::vector<bool> matchGjet;
  std::vector<double> MGjPt;
  std::vector<double> MGjeta;
  std::vector<double> MGjphi;
  std::vector<double> MGjE;
  //CaloJets
  std::vector<double> caloJetPt_;
  std::vector<double> caloJetRawPt_;
  std::vector<double> caloJetEn_;
  std::vector<double> caloJetEta_;
  std::vector<double> caloJetPhi_;
  std::vector<double> caloJetHadEHF_;
  std::vector<double> caloJetEmEHF_;
  std::vector<double> caloJetEmFrac_;
  std::vector<double> caloJetn90_;
  ///pfjets
  std::vector<double> patJetPfAk05En_;
  std::vector<double> patJetPfAk05Pt_;
  std::vector<double> patJetPfAk05Eta_;
  std::vector<double> patJetPfAk05Phi_;
  //std::vector<double> patJetPfAk05JesUncert_;
  std::vector<double> patJetPfAk05LooseId_;
  std::vector<double> patJetPfAk05Et_;
  std::vector<double> patJetPfAk05RawPt_;
  std::vector<double> patJetPfAk05RawEn_;
  std::vector<double> patJetPfAk05HadEHF_;
  std::vector<double> patJetPfAk05EmEHF_;
  //std::vector<double> patJetPfAk05jetBSZ_;
  //std::vector<double> patJetPfAk05jetBZ_;
  std::vector<double> patJetPfAk05jetBetaClassic_;
  std::vector<double> patJetPfAk05jetBeta_;
  std::vector<double> patJetPfAk05jetBetaStar_;
  std::vector<double> patJetPfAk05jetBetaStarClassic_;
  std::vector<double> patJetPfAk05jetpuMVA_;
  std::vector<double> patJetPfAk05chf_;
  std::vector<double> patJetPfAk05nhf_;
  std::vector<double> patJetPfAk05cemf_;
  std::vector<double> patJetPfAk05nemf_;
  std::vector<double> patJetPfAk05cmult_;
  std::vector<double> patJetPfAk05nconst_;
  std::vector<bool> patJetPfAk05jetpukLoose_;
  std::vector<bool> patJetPfAk05jetpukMedium_;
  std::vector<bool> patJetPfAk05jetpukTight_;
  std::vector<double> patJetPfAk05PtUp_;
  std::vector<double> patJetPfAk05PtDn_;
  std::vector<double> patJetPfAk05BDiscCSV_;
  std::vector<double> patJetPfAk05BDiscCSVV1_;
  std::vector<double> patJetPfAk05BDiscCSVSLV1_;
  std::vector<double> unc_;
  ///Muons
  std::vector<double> patMuonPt_;
  std::vector<double> patMuonEta_;
  std::vector<double> patMuonPhi_;
  std::vector<double> patMuonVtxZ_;
  std::vector<double> patMuonEn_;
  std::vector<double> patMuonCharge_;
  std::vector<double> patMuonDxy_;
  std::vector<double> patMuonCombId_;
  std::vector<double> patMuonTrig_;
  std::vector<double> patMuonDetIsoRho_;
  std::vector<double> patMuonPfIsoDbeta_;
  std::vector<double> patMuonM_;
  std::vector<double> patMuonPx_;
  std::vector<double> patMuonPy_;
  std::vector<double> patMuonPz_;
  std::vector<double> patMuonGlobalType_;
  std::vector<double> patMuonTrackerType_;
  std::vector<double> patMuonPFType_;
  std::vector<double> patMuonIsoSumPt_;
  std::vector<double> patMuonIsoRelative_;
  std::vector<double> patMuonIsoCalComb_;
  std::vector<double> patMuonIsoDY_;
  std::vector<double> patMuonChi2Ndoff_;
  std::vector<double> patMuonNhits_;
  std::vector<double> patMuonNMatches_;
  std::vector<double> patMuonDz_;
  std::vector<double> patMuonPhits_;
  std::vector<double> patMuonTkLayers_;
  std::vector<double> patMuon_PF_IsoSumChargedHadronPt_;
  std::vector<double> patMuon_PF_IsoSumNeutralHadronEt_;
  std::vector<double> patMuon_PF_IsoDY_;
  std::vector<double> patMuon_Mu17_Mu8_Matched_;
  std::vector<double> patMuon_Mu17_TkMu8_Matched_; 
  std::vector<double> patElecTrig_;
  std::vector<double> patElecDz_;
  std::vector<double> patElecMVATrigId_;
  std::vector<double> patElecMVANonTrigId_;
  std::vector<double> patElecPt_;
  std::vector<double> patElecEta_;
  std::vector<double> patElecScEta_;
  std::vector<double> patElecPhi_;
  std::vector<double> patElecEnergy_;
  std::vector<double> patElecCharge_;
  std::vector<double> patElecMediumIDOff_;
  std::vector<double> patElecMediumIDOff_Tom_;
  std::vector<double> patElecPfIso_;
  std::vector<double> patElecPfIsodb_;
  std::vector<double> patElecPfIsoRho_;
  std::vector<double> charged_;
  std::vector<double> photon_;
  std::vector<double> neutral_;
  std::vector<double> charged_Tom_;
  std::vector<double> photon_Tom_;
  std::vector<double> neutral_Tom_;
  std::vector<double> patElec_mva_presel_;
  std::vector<double> id1_pdfInfo_;
  std::vector<double> id2_pdfInfo_;
  std::vector<double> x1_pdfInfo_;
  std::vector<double> x2_pdfInfo_;
  std::vector<double> scalePDF_pdfInfo_;
  double ptHat_,mcWeight_; 
  double rhoPrime,AEff;
  //HLT
  double HLT_Mu17_Mu8,HLT_Mu17_TkMu8;
  double HLT_Elec17_Elec8;
//  JetCorrectionUncertainty *jecUnc;
};

using namespace std;
using namespace reco;
int ccnevent=0;
Tupel::Tupel(const edm::ParameterSet& iConfig):
trigger_( iConfig.getParameter< edm::InputTag >( "trigger" ) ),
  triggerEvent_( iConfig.getParameter< edm::InputTag >( "triggerEvent" ) ),
  triggerSummaryLabel_( iConfig.getParameter< edm::InputTag >( "triggerSummaryLabel" ) ), //added by jyhan
  elecMatch_( iConfig.getParameter< std::string >( "elecMatch" ) ),
  muonMatch_( iConfig.getParameter< std::string >( "muonMatch" ) ),
  muonMatch2_( iConfig.getParameter< std::string >( "muonMatch2" ) ),
  photonSrc_(iConfig.getUntrackedParameter<edm::InputTag>("photonSrc")),
  elecSrc_(iConfig.getUntrackedParameter<edm::InputTag>("electronSrc")),
  muonSrc_(iConfig.getUntrackedParameter<edm::InputTag>("muonSrc")),
  //tauSrc_(iConfig.getUntrackedParameter<edm::InputTag>("tauSrc" )),
  jetSrc_(iConfig.getUntrackedParameter<edm::InputTag>("jetSrc" )),
  metSrc_(iConfig.getUntrackedParameter<edm::InputTag>("metSrc" )),
  mSrcRho_(iConfig.getUntrackedParameter<edm::InputTag>("mSrcRho" )),
  CaloJet_(iConfig.getUntrackedParameter<edm::InputTag>("CalojetLabel"))
{
}

Tupel::~Tupel()
{
}

void Tupel::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  using namespace edm; //ADD
  ++ccnevent;
 
  // PAT trigger event
  edm::Handle<pat::TriggerEvent>  triggerEvent;
  iEvent.getByLabel( triggerEvent_, triggerEvent );
  
  const pat::helper::TriggerMatchHelper matchHelper;	
  edm::Handle<GenParticleCollection> genParticles_h;
  iEvent.getByLabel("genParticles", genParticles_h);
  const GenParticleCollection* genParticles  = genParticles_h.failedToGet () ? 0 : &*genParticles_h;
  
  // get muon collection
  edm::Handle<edm::View<pat::Muon> > muons;
  iEvent.getByLabel(muonSrc_,muons);
  const edm::View<pat::Muon> & mu = *muons;
  
  // get electron collection
  edm::Handle<vector<pat::Electron> > electrons;
  iEvent.getByLabel(elecSrc_,electrons);
  auto_ptr<vector<pat::Electron> > electronColl( new vector<pat::Electron> (*electrons) );
  //const edm::View<pat::Electron> & elec = *electrons;
			      
  edm::Handle<reco::GsfElectronCollection> els_h;
  iEvent.getByLabel("gsfElectrons", els_h);			       
  edm::Handle<reco::ConversionCollection> conversions_h;
  iEvent.getByLabel("allConversions", conversions_h);
  
  
  
  // get tau collection 
  edm::Handle<edm::View<pat::Tau> > taus;
  iEvent.getByLabel(tauSrc_,taus);
					  
  // get jet collection
  edm::Handle<edm::View<pat::Jet> > jets;
  iEvent.getByLabel(jetSrc_,jets);
  //const edm::View<pat::Jet> & jet = *jets;
  
  // get met collection  
  edm::Handle<edm::View<pat::MET> > mets;
  iEvent.getByLabel(metSrc_,mets);
  
  // get photon collection  
  edm::Handle<edm::View<pat::Photon> > photons;
  iEvent.getByLabel(photonSrc_,photons);
  
  edm::Handle<edm::View<reco::Vertex> >  pvHandle;
  iEvent.getByLabel("goodOfflinePrimaryVertices", pvHandle);
  //  const edm::View<reco::Vertex> & vertexColl = *pvHandle;

  //# Get b tag information
 // edm::Handle<reco::JetTagCollection> bTagHandle;
 // iEvent.getByLabel("trackCountingHighEffBJetTags", bTagHandle);
 // const reco::JetTagCollection & bTags = *(bTagHandle.product());
							  
  //  Handle<VertexCollection> pvHandl;//reco::VertexRef needs VertexCollection and does not work with edm::View<reco::Vertex>
  //  iEvent.getByLabel("offlinePrimaryVertices", pvHandl); 
							  
  edm ::Handle<reco::VertexCollection> vtx_h;
  iEvent.getByLabel("goodOfflinePrimaryVertices", vtx_h); 
  int nvtx=vtx_h->size();
  if(nvtx==0) return;
  reco::VertexRef primVtx(vtx_h,0);
  edm::Handle<double>  rho_;
  iEvent.getByLabel(InputTag("kt6PFJets", "rho"), rho_);
  double rhoIso = *rho_;
  reco::BeamSpot beamSpot;
  edm::Handle<reco::BeamSpot> beamSpotHandle;
  iEvent.getByLabel("offlineBeamSpot", beamSpotHandle);
  beamSpot = *beamSpotHandle;
  edm::Handle<double> rho;
  iEvent.getByLabel(mSrcRho_,rho);
  Handle<ValueMap<float> > puJetIDMVA;
  //iEvent.getByLabel(InputTag("puJetMvaChs" ,"fullDiscriminant"),puJetIDMVA);
  iEvent.getByLabel(InputTag("puJetMvaChs" ,"cutbasedDiscriminant"),puJetIDMVA);
  Handle<ValueMap<StoredPileupJetIdentifier> > puJetIdentifier; // The Identifier
  iEvent.getByLabel("puJetIdChs", puJetIdentifier);
  
  Handle<ValueMap<int> > puJetIdFlag; // Outcome of the discriminant
  //iEvent.getByLabel(InputTag("puJetMvaChs","fullId"), puJetIdFlag); // load it
  iEvent.getByLabel(InputTag("puJetMvaChs","cutbasedId"), puJetIdFlag);
  
  // PFIsolationEstimator eIsolator03_, eIsolator04_, gIsolator03_, gIsolator04_;
											      
  edm::Handle<reco::PFCandidateCollection> pfH;
    iEvent.getByLabel( "particleFlow",pfH);
      ///Clear vector//////
    event=0;
    realdata=0;
    run=0;
    lumi=0;
    bxnumber=0;
    EvtInfo_NumVtx=0;
    PU_npT=0;
    PU_npIT=0;
    MyWeight=0;
    nup=0;
    rhoPrime=0;
    AEff=0;    												     
    Dr01LepPt.clear();
    Dr01LepEta.clear();
    Dr01LepPhi.clear();
    Dr01LepE.clear();
    Dr01LepM.clear();
    Dr01LepId.clear();
    Dr01LepStatus.clear();
    Bare01LepPt.clear();
    Bare01LepEta.clear();
    Bare01LepPhi.clear();
    Bare01LepE.clear();
    Bare01LepM.clear();
    Bare01LepId.clear();
    Bare01LepStatus.clear();
    St03Pt.clear();
    St03Eta.clear();
    St03Phi.clear();
    St03E.clear();
    St03M.clear();
    St03Id.clear();
    St03Status.clear();
    St01PhotonPt.clear();
    St01PhotonEta.clear();
    St01PhotonPhi.clear();
    St01PhotonE.clear();
    St01PhotonM.clear();
    St01PhotonId.clear();
    St01PhotonMomId.clear();
    St01PhotonNumberMom.clear();
    St01PhotonStatus.clear();
    GjPt.clear();
    Gjeta.clear();
    Gjphi.clear();
    GjE.clear();
    GjPx.clear();
    GjPy.clear();
    GjPz.clear();
    GjChargedFraction.clear();
    matchGjet.clear();
    MGjPt.clear();
    MGjeta.clear();
    MGjphi.clear();
    MGjE.clear();
    caloJetPt_.clear();
    caloJetRawPt_.clear();
    caloJetEn_.clear();
    caloJetEta_.clear();
    caloJetPhi_.clear();
    caloJetHadEHF_.clear();
    caloJetEmEHF_.clear();
    caloJetEmFrac_.clear();
    caloJetn90_.clear();
    patJetPfAk05En_.clear();
    patJetPfAk05Pt_.clear();
    patJetPfAk05Eta_.clear();
    patJetPfAk05Phi_.clear();
    //patJetPfAk05JesUncert_.clear();
    patJetPfAk05LooseId_.clear();
    patJetPfAk05Et_.clear();
    patJetPfAk05RawPt_.clear();
    patJetPfAk05RawEn_.clear();
    patJetPfAk05HadEHF_.clear();
    patJetPfAk05EmEHF_.clear();
    //patJetPfAk05jetBSZ_.clear();
    //patJetPfAk05jetBZ_.clear();
    patJetPfAk05jetBetaClassic_.clear();
    patJetPfAk05jetBeta_.clear();
    patJetPfAk05jetBetaStar_.clear();
    patJetPfAk05jetBetaStarClassic_.clear();
    patJetPfAk05jetpuMVA_.clear();
    patJetPfAk05chf_.clear();
    patJetPfAk05nhf_.clear();
    patJetPfAk05cemf_.clear();
    patJetPfAk05nemf_.clear();
    patJetPfAk05cmult_.clear();
    patJetPfAk05nconst_.clear();
    patJetPfAk05jetpukLoose_.clear();
    patJetPfAk05jetpukMedium_.clear();
    patJetPfAk05jetpukTight_.clear();
    patJetPfAk05PtUp_.clear();
    patJetPfAk05PtDn_.clear();
    patJetPfAk05BDiscCSV_.clear();
    patJetPfAk05BDiscCSVV1_.clear();
    patJetPfAk05BDiscCSVSLV1_.clear();
    unc_.clear();
    ///Muons
    patMuonPt_.clear();
    patMuonEta_.clear();
    patMuonPhi_.clear();
    patMuonVtxZ_.clear();
    patMuonEn_.clear();
    patMuonCharge_.clear();
    patMuonDxy_.clear();
    patMuonCombId_.clear();
    patMuonTrig_.clear();
    patMuonDetIsoRho_.clear();
    patMuonPfIsoDbeta_.clear();
    patMuonM_.clear();
    patMuonPx_.clear();
    patMuonPy_.clear();
    patMuonPz_.clear();
    patMuonGlobalType_.clear();
    patMuonTrackerType_.clear();
    patMuonPFType_.clear();
    patMuonIsoSumPt_.clear();
    patMuonIsoRelative_.clear();
    patMuonIsoCalComb_.clear();
    patMuonIsoDY_.clear();
    patMuonChi2Ndoff_.clear();
    patMuonNhits_.clear();
    patMuonNMatches_.clear();
    patMuonDz_.clear();
    patMuonPhits_.clear();
    patMuonTkLayers_.clear();
    patMuon_PF_IsoSumChargedHadronPt_.clear();
    patMuon_PF_IsoSumNeutralHadronEt_.clear();
    patMuon_PF_IsoDY_.clear();
    patMuon_Mu17_Mu8_Matched_.clear();
    patMuon_Mu17_TkMu8_Matched_.clear();
    //electrons
    
    patElecTrig_.clear();
    patElecDz_.clear();
    patElecMVATrigId_.clear();
    patElecMVANonTrigId_.clear();
    patElecPt_.clear();
    patElecEta_.clear();
    patElecScEta_.clear();
    patElecPhi_.clear();
    patElecEnergy_.clear();
    patElecCharge_.clear();
    patElecMediumIDOff_.clear();
    patElecMediumIDOff_Tom_.clear();
    patElecPfIso_.clear();
    patElecPfIsodb_.clear();
    patElecPfIsoRho_.clear();
    charged_.clear();
    photon_.clear();  
    neutral_.clear();
    charged_Tom_.clear();
    photon_Tom_.clear();
    neutral_Tom_.clear();
    patElec_mva_presel_.clear();
    //HLT 
    
    HLT_Mu17_Mu8=0;
    HLT_Mu17_TkMu8=0;
    HLT_Elec17_Elec8=0;
    ////Add 08/23/13/////
    id1_pdfInfo_.clear();
    id2_pdfInfo_.clear();
    x1_pdfInfo_.clear();
    x2_pdfInfo_.clear();
    scalePDF_pdfInfo_.clear();
    ptHat_=0;
    mcWeight_=0;
    ///////////////////end clear vector////////////////////// 
    event = iEvent.id().event();
    run = iEvent.id().run();
    lumi = iEvent.luminosityBlock();
    bxnumber = iEvent.bunchCrossing();
    realdata = iEvent.isRealData();
    
    EvtInfo_NumVtx = 0;
    for (edm::View<reco::Vertex>::const_iterator vtx = pvHandle->begin(); vtx != pvHandle->end(); ++vtx){
      if (vtx->isValid() && !vtx->isFake()) ++EvtInfo_NumVtx ;
    }
    
    if(!realdata){
      Handle<std::vector< PileupSummaryInfo > >  PupInfo;
      iEvent.getByLabel("addPileupInfo", PupInfo);
      
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
      PU_npT=npT;
      PU_npIT=npIT;
    }
    else {
      PU_npT=-2.; 
      PU_npIT=-2.;
    }
    if (!realdata && genParticles){     
      const std::vector<reco::GenParticle> & gen = *genParticles_h;
      for (size_t i=0; i<genParticles->size(); ++i){
	TLorentzVector genR1DressLep1(0,0,0,0);
	//      TLorentzVector genPho(0,0,0,0); 
	int st = gen[i].status();
	int id = gen[i].pdgId();
	if(gen[i].numberOfMothers()){
	  if (st==3){
	    TLorentzVector genLep3(0,0,0,0);
	    genLep3.SetPtEtaPhiE(gen[i].pt(),gen[i].eta(),gen[i].phi(),gen[i].energy());
	    St03Pt.push_back(genLep3.Pt());
	    St03Eta.push_back(genLep3.Eta());
	    St03Phi.push_back(genLep3.Phi());
	    St03E.push_back(genLep3.Energy());
	    St03M.push_back(genLep3.M());
	    St03Id.push_back(id);
	    St03Status.push_back(st);
	  }
	  if (st==1){
	    TLorentzVector genLep1(0,0,0,0);
	    genLep1.SetPtEtaPhiE(gen[i].pt(),gen[i].eta(),gen[i].phi(),gen[i].energy());
	    TLorentzVector genR1Pho1(0,0,0,0);
	   
	    edm::Handle<std::vector<reco::GenParticle> > genpart2;//DONT know why we Need to handle another collection
	    iEvent.getByLabel("genParticles", genpart2);
	    const std::vector<reco::GenParticle> & gen2 = *genpart2;
	    //LOOP over photons//
	    
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
		  St01PhotonPt.push_back(thisPho1.Pt());
		  St01PhotonEta.push_back(thisPho1.Eta());
		  St01PhotonPhi.push_back(thisPho1.Phi());
		  St01PhotonE.push_back(thisPho1.Energy());
		  St01PhotonM.push_back(thisPho1.M());
		  St01PhotonId.push_back(gen2[j].pdgId());
		  St01PhotonMomId.push_back(fabs(gen2[j].mother()->pdgId()));
		  St01PhotonNumberMom.push_back(gen2[j].numberOfMothers());
		  St01PhotonStatus.push_back(gen2[j].status()); 
		}
	      }
	    }
	    genR1DressLep1=genLep1+genR1Pho1;
	    Dr01LepPt.push_back(genR1DressLep1.Pt());
	    Dr01LepEta.push_back(genR1DressLep1.Eta());
	    Dr01LepPhi.push_back(genR1DressLep1.Phi());
	    Dr01LepE.push_back(genR1DressLep1.Energy());
	    Dr01LepM.push_back(genR1DressLep1.M());
	    Dr01LepId.push_back(id);
	    Dr01LepStatus.push_back(st);
	    
	    Bare01LepPt.push_back(genLep1.Pt());
	    Bare01LepEta.push_back(genLep1.Eta());
	    Bare01LepPhi.push_back(genLep1.Phi());
	    Bare01LepE.push_back(genLep1.Energy());
	    Bare01LepM.push_back(genLep1.M());
	    Bare01LepId.push_back(id);
	    Bare01LepStatus.push_back(st);
	  }
	}
      }
    }
    if (!realdata){
      //matrix element info
      Handle<LHEEventProduct> lheH;
      iEvent.getByType(lheH);
      if(lheH.isValid()) nup=lheH->hepeup().NUP;
      edm::Handle<reco::GenJetCollection> genjetColl;
      //iEvent.getByLabel("ak5GenJets", genjetColl);
          iEvent.getByLabel("ak5GenJetsNoNu", genjetColl);
      const reco::GenJetCollection & genjet = *genjetColl;
      for(unsigned int k=0; k<genjetColl->size(); ++k){
	GjPt.push_back(genjet[k].pt());
	Gjeta.push_back(genjet[k].eta());
	Gjphi.push_back(genjet[k].phi());
	GjE.push_back(genjet[k].energy());
	GjPx.push_back(genjet[k].px());
	GjPy.push_back(genjet[k].py());
	GjPz.push_back(genjet[k].pz());
	double isChargedJet=false;
	double chargedFraction = 0.;
	std::vector<const GenParticle*> mcparticles = genjet[k].getGenConstituents();
	for(std::vector <const GenParticle*>::const_iterator thepart =mcparticles.begin();thepart != mcparticles.end(); ++ thepart ) {
	  if ( (**thepart).charge()!=0 ){
	    isChargedJet=true;
	    chargedFraction += (**thepart).pt();
	  }
	}
	if ( chargedFraction == 0 ) cout << " is chargeid: " << isChargedJet << "   " << chargedFraction/genjet[k].pt()<< endl;
	GjChargedFraction.push_back(chargedFraction/genjet[k].pt());
      }
    }
    
    ////Add 08/27/13//////
    if(!realdata){
      edm::Handle<GenEventInfoProduct>   genEventInfoProd;
      if (iEvent.getByType(genEventInfoProd)) {
	if (genEventInfoProd->hasBinningValues())
	  ptHat_ = genEventInfoProd->binningValues()[0];
	mcWeight_ = genEventInfoProd->weight();
      }
      /// now get the PDF information
      edm::Handle<GenEventInfoProduct> pdfInfoHandle;
      if (iEvent.getByLabel("generator", pdfInfoHandle)) {
	if (pdfInfoHandle->pdf()) {
	  id1_pdfInfo_.push_back(pdfInfoHandle->pdf()->id.first);
	  id2_pdfInfo_.push_back(pdfInfoHandle->pdf()->id.second);
	  x1_pdfInfo_.push_back(pdfInfoHandle->pdf()->x.first);
	  x2_pdfInfo_.push_back(pdfInfoHandle->pdf()->x.second);
	  //pdfInfo_.push_back(pdfInfoHandle->pdf()->xPDF.first);
	  //dfInfo_.push_back(pdfInfoHandle->pdf()->xPDF.second);
	  scalePDF_pdfInfo_.push_back(pdfInfoHandle->pdf()->scalePDF);
	}   
      }   
    }
    
    int Mu17_Mu8=0;
    int Mu17_TkMu8=0;
    int Elec17_Elec8=0;
    
    HLT_Mu17_Mu8=0;
    HLT_Mu17_TkMu8=0;
    
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
    HLT_Mu17_Mu8=Mu17_Mu8;
    HLT_Mu17_TkMu8=Mu17_TkMu8;
    HLT_Elec17_Elec8=Elec17_Elec8;
    
    double MuFill=0;
    double Mu17_Mu8_Matched=0;
    double Mu17_TkMu8_Matched=0;
    for (unsigned int j = 0; j < muons->size(); ++j){
      if(mu[j].isGlobalMuon()){ 
	const pat::TriggerObjectRef trigRef( matchHelper.triggerMatchObject( muons,j,muonMatch_, iEvent, *triggerEvent ) );
	if ( trigRef.isAvailable() && trigRef.isNonnull() ) {
	  Mu17_Mu8_Matched=1;
	}
	const pat::TriggerObjectRef trigRef2( matchHelper.triggerMatchObject( muons,j,muonMatch2_, iEvent, *triggerEvent ) );
	if ( trigRef2.isAvailable() && trigRef2.isNonnull() ) {
	  Mu17_TkMu8_Matched=1;
	}
	patMuon_Mu17_Mu8_Matched_.push_back(Mu17_Mu8_Matched);
	patMuon_Mu17_TkMu8_Matched_.push_back(Mu17_TkMu8_Matched);
	//MuFill=1;
	patMuonPt_.push_back(mu[j].pt());
	patMuonEta_.push_back(mu[j].eta());
	patMuonPhi_.push_back(mu[j].phi());
	patMuonEn_.push_back(mu[j].energy());
	patMuonCharge_.push_back(mu[j].charge());
	patMuonVtxZ_.push_back(mu[j].vz());
	patMuonM_.push_back(mu[j].mass());
	patMuonPx_.push_back(mu[j].px());
	patMuonPy_.push_back(mu[j].py());
	patMuonPz_.push_back(mu[j].pz());
	patMuonDxy_.push_back(mu[j].dB());
	
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
	patMuonChi2Ndoff_.push_back(normChi2);
	patMuonNhits_.push_back(muonHits);
	patMuonNMatches_.push_back(nMatches);
	patMuonDz_.push_back(dZ);
	patMuonPhits_.push_back(pixelHits);
	patMuonTkLayers_.push_back(trkLayers);
	
	int idpass=0;
	if(mu[j].isGlobalMuon() && mu[j].isPFMuon() && normChi2<10 && muonHits>0 && nMatches>1 && mu[j].dB()<0.2 && dZ<0.5 && pixelHits>0 && trkLayers>5)idpass=1;
	patMuonCombId_.push_back(idpass);
	int TrigSum=0;
	if(Mu17_Mu8_Matched==1) TrigSum=1;
	patMuonTrig_.push_back(TrigSum);
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
	patMuonDetIsoRho_.push_back(dbeta);
	
	// pf Isolation variables
	double chargedHadronIso = mu[j].pfIsolationR04().sumChargedHadronPt;
	double chargedHadronIsoPU = mu[j].pfIsolationR04().sumPUPt;  
	double neutralHadronIso  = mu[j].pfIsolationR04().sumNeutralHadronEt;
	double photonIso  = mu[j].pfIsolationR04().sumPhotonEt;
	  
	// OPTION 1: DeltaBeta corrections for iosolation
	float RelativeIsolationDBetaCorr = (chargedHadronIso + std::max(photonIso+neutralHadronIso - 0.5*chargedHadronIsoPU,0.))/std::max(0.5, mu[j].pt());
	patMuonPfIsoDbeta_.push_back(RelativeIsolationDBetaCorr);
	patMuonGlobalType_.push_back(mu[j].isGlobalMuon());
	patMuonTrackerType_.push_back(mu[j].isTrackerMuon());
	patMuonPFType_.push_back(mu[j].isPFMuon());
	patMuonIsoSumPt_.push_back(mu[j].isolationR03().sumPt);
	patMuonIsoRelative_.push_back(mu[j].isolationR03().sumPt/mu[j].pt());
	patMuonIsoCalComb_.push_back(mu[j].isolationR03().emEt + mu[j].isolationR03().hadEt);
	patMuonIsoDY_.push_back((mu[j].isolationR03().sumPt+mu[j].isolationR03().hadEt)/mu[j].pt());
	patMuon_PF_IsoSumChargedHadronPt_.push_back(mu[j].pfIsolationR03().sumChargedHadronPt);
	patMuon_PF_IsoSumNeutralHadronEt_.push_back(mu[j].pfIsolationR03().sumNeutralHadronEt);
	patMuon_PF_IsoDY_.push_back((mu[j].pfIsolationR03().sumChargedHadronPt+mu[j].pfIsolationR03().sumNeutralHadronEt)/mu[j].pt());
	MuFill++;
      }
    }
    
    
    //electrons B.B.
    
    int ElecFill=0;
    
    EgammaCutBasedEleId::IsoDepositVals electronIsoValPFId(3);
    iEvent.getByLabel("elPFIsoValueCharged03NoPFIdPFlowPFIso", electronIsoValPFId[0]);
    iEvent.getByLabel("elPFIsoValueGamma03NoPFIdPFlowPFIso", electronIsoValPFId[1]);
    iEvent.getByLabel("elPFIsoValueNeutral03NoPFIdPFlowPFIso", electronIsoValPFId[2]);
    
    PFIsolationEstimator eIsolator03_, eIsolator04_, gIsolator03_, gIsolator04_;
    
    eIsolator03_.initializeElectronIsolation(true); eIsolator03_.setConeSize(0.3);
    eIsolator04_.initializeElectronIsolation(true); eIsolator04_.setConeSize(0.4);
    gIsolator03_.initializePhotonIsolation(true);   gIsolator03_.setConeSize(0.3);
    gIsolator04_.initializePhotonIsolation(true);   gIsolator04_.setConeSize(0.4);
    
    //iEvent.getByLabel
    
    //  cout<<"GSF: PAT run:lumi:event:"<<run<<":"<<lumi<<":"<<event<<endl;
    for (unsigned int j=0; j < electronColl->size();++j){
      pat::Electron & el = (*electronColl)[j];
      double Elec17_Elec8_Matched=0;
      if(el.pt()<10. ||el.superCluster()->eta()>5.1 )continue;
      const pat::TriggerObjectRef trigRef( matchHelper.triggerMatchObject( electrons,j,elecMatch_, iEvent, *triggerEvent ) );
      if ( trigRef.isAvailable() && trigRef.isNonnull() ) {
	Elec17_Elec8_Matched=1;
      }
      
      patElecTrig_.push_back(Elec17_Elec8_Matched); 
      reco::Vertex::Point pos(0,0,0);
      if(vtx_h->size() > 0) pos = vtx_h->at(0).position();
      patElecDz_.push_back(el.gsfTrack()->dz(pos));
      const string mvaTrigV0 = "mvaTrigV0";
      const string mvaNonTrigV0 = "mvaNonTrigV0";
      
      patElecMVATrigId_.push_back(el.electronID(mvaTrigV0));
      patElecMVANonTrigId_.push_back(el.electronID(mvaNonTrigV0));
      patElecPt_.push_back(el.pt());
      patElecEta_.push_back(el.eta());
      
      patElecScEta_.push_back(el.superCluster()->eta());
      patElecPhi_.push_back(el.phi());	
      patElecEnergy_.push_back(el.energy());
      patElecCharge_.push_back(el.charge());
      
      AEff = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, el.superCluster()->eta(), ElectronEffectiveArea::kEleEAData2012);
      rhoPrime = std::max(rhoIso, 0.0);
      
      const double chIso03_ = el.chargedHadronIso();
      const double nhIso03_ = el.neutralHadronIso();
      const double phIso03_ = el.photonIso();
      const double puChIso03_= el.puChargedHadronIso();
         
      /*       reco::CandidatePtr elePtr       = electronColl->ptrAt(j);
	       const pat::Electron *ele        = dynamic_cast<const pat::Electron *>( elePtr.get() );
	       const reco::Candidate *genLep   = ele->genLepton();
	       const reco::GsfElectron *gsfEle = dynamic_cast<const reco::GsfElectron *>(ele);
	       reco::GsfElectronRef gsfele(gsfEleH, ele->originalObjectRef().key());
      */
      const pat::Electron *el2 = &(*electronColl)[j];
      //const pat::Electron * el1 = dynamic_cast<const pat::Electron *> ((*electronColl)[j]);
      // const pat::Electron *ele        = dynamic_cast<const pat::Electron *>( el);
      const reco::GsfElectron *GsfEle = dynamic_cast<const reco::GsfElectron *> (el2);
      eIsolator03_.fGetIsolation(GsfEle, &(*pfH), primVtx, vtx_h);
      reco::GsfElectronRef gsfele(els_h, el.originalObjectRef().key());
      
      
      
      photon_Tom_.push_back(eIsolator03_.getIsolationPhoton());
      charged_Tom_.push_back(eIsolator03_.getIsolationCharged());
      neutral_Tom_.push_back(eIsolator03_.getIsolationNeutral());
    
      const EgammaCutBasedEleId::IsoDepositVals * electronIsoVals = &electronIsoValPFId;
      charged_.push_back( (*(*electronIsoVals)[0])[el.originalObjectRef()]);
      photon_.push_back( (*(*electronIsoVals)[1])[el.originalObjectRef()]);
      neutral_.push_back( (*(*electronIsoVals)[2])[el.originalObjectRef()]);
      //cout<<" ELE ISO NEUTRAL "<< eIsolator03_.getIsolationPhoton()<< " "<< el.photonIso()<<" "<<(*(*electronIsoVals)[1])[el.originalObjectRef()]<<endl;
      
      //cout<<" ELE ISO CHARGED "<<eIsolator03_.getIsolationCharged()<<" " <<el.chargedHadronIso()<<" "<<(*(*electronIsoVals)[0])[el.originalObjectRef()]<<endl;
      
      bool medium = EgammaCutBasedEleId::PassWP(EgammaCutBasedEleId::MEDIUM, gsfele, conversions_h, beamSpot, vtx_h, (const double) 0, (const double) 0, (const double) 0, rhoPrime);
      
      patElecMediumIDOff_.push_back(medium);
      
      bool hasId=EgammaCutBasedEleId::PassWP( EgammaCutBasedEleId::MEDIUM, el.isEB(), el.pt(), el.eta(),el.deltaEtaSuperClusterTrackAtVtx(),el.deltaPhiSuperClusterTrackAtVtx(),el.sigmaIetaIeta(),el.hadronicOverEm(),(1.0/el.ecalEnergy() - el.eSuperClusterOverP()/el.ecalEnergy()),
					      fabs(el.gsfTrack()->dxy(primVtx->position())),
					      fabs(el.gsfTrack()->dz(primVtx->position())),
					      0.,0.,0., ConversionTools::hasMatchedConversion(*gsfele,conversions_h,beamSpotHandle->position()),
					      el.gsfTrack()->trackerExpectedHitsInner().numberOfLostHits(),
					      *rho_);
      
      //GSF -> PAT COMPARISON
      
      /*if(medium!=hasId){
	cout<<"GSF: PAT: deltaEta "<<gsfele->deltaEtaSuperClusterTrackAtVtx()<<" "<<el.deltaEtaSuperClusterTrackAtVtx()<<endl;
	cout<<"GSF: PAT: deltaPhi "<<gsfele->deltaPhiSuperClusterTrackAtVtx()<<" "<<el.deltaPhiSuperClusterTrackAtVtx()<<endl;
	cout<<"GSF: PAT: Sihih "<<gsfele->sigmaIetaIeta()<<" "<<el.sigmaIetaIeta()<<endl;
	cout<<"GSF: PAT: hadronicOverEm "<<gsfele->hadronicOverEm()<<" "<<el.hadronicOverEm()<<endl;
	cout<<"GSF: PAT: 1/E- 1/p "<<(1.0/gsfele->ecalEnergy() - gsfele->eSuperClusterOverP()/gsfele->ecalEnergy())<<" "<<(1.0/el.ecalEnergy() - el.eSuperClusterOverP()/el.ecalEnergy())<<endl;
	cout<<"GSF: PAT: D0 "<<(fabs(gsfele->gsfTrack()->dxy(primVtx->position())))<<" "<<(fabs(el.gsfTrack()->dxy(primVtx->position())))<<endl;
	cout<<"GSF: PAT: Dz "<<(fabs(gsfele->gsfTrack()->dz(primVtx->position())))<<" "<<(fabs(el.gsfTrack()->dz(primVtx->position())))<<endl;
	cout<<"GSF: PAT: MHits "<<(gsfele->gsfTrack()->trackerExpectedHitsInner().numberOfLostHits() )<< " "<<(gsfele->gsfTrack()->trackerExpectedHitsInner().numberOfLostHits() )<<endl;
	cout<<"GSF: PAT: Bool"<<medium<<" "<<hasId<<endl<<endl<<endl;
	}*/
      patElecMediumIDOff_Tom_.push_back(hasId);
      patElecPfIso_.push_back(( chIso03_ + nhIso03_ + phIso03_ ) / el.pt());
      patElecPfIsodb_.push_back(( chIso03_ + max(0.0, nhIso03_ + phIso03_ - 0.5*puChIso03_) )/ el.pt());
      patElecPfIsoRho_.push_back(( chIso03_ + max(0.0, nhIso03_ + phIso03_ - rhoPrime*AEff) )/ el.pt());
      
      //Trigger requirement for MVA elec id
      bool myTrigPresel = false;
      if(fabs(el.superCluster()->eta()) < 1.479){
	if(el.sigmaIetaIeta() < 0.014 &&
	   el.hadronicOverEm() < 0.15 &&
	   el.dr03TkSumPt()/el.pt() < 0.2 &&
	   el.dr03EcalRecHitSumEt()/el.pt() < 0.2 &&
	   el.dr03HcalTowerSumEt()/el.pt() < 0.2 &&
	   el.gsfTrack()->trackerExpectedHitsInner().numberOfLostHits() == 0)
	  myTrigPresel = true;
      }
      else {
	if(el.sigmaIetaIeta() < 0.035 &&
	   el.hadronicOverEm() < 0.10 &&
	   el.dr03TkSumPt()/el.pt() < 0.2 &&
	   el.dr03EcalRecHitSumEt()/el.pt() < 0.2 &&
	   el.dr03HcalTowerSumEt()/el.pt() < 0.2 &&
	   el.gsfTrack()->trackerExpectedHitsInner().numberOfLostHits() == 0)
	  myTrigPresel = true;
	  }
      
      patElec_mva_presel_.push_back(myTrigPresel);
      ElecFill++; 
    }
    double PFjetFill=0;
    double chf = 0;
    double nhf = 0;
    double cemf = 0;
    double nemf = 0;
    double cmult = 0;
    double nconst = 0;
    
    //for(edm::View<pat::Jet>::const_iterator jet=jets->begin(); jet!=jets->end(); ++jet){
    for ( unsigned int i=0; i<jets->size(); ++i ) {
      const pat::Jet & jet = jets->at(i);
      
      //if(jet.pt()<20 || MuFill<2) continue;
      //PFjetFill=1;
      //   if(realdata && (jet.pt()<10.|| MuFill<2)) continue;
      if(/*!realdata &&*/ (jet.pt()<10.))continue;  
      
      patJetPfAk05jetpuMVA_.push_back( (*puJetIDMVA)[jets->refAt(i)]);
      patJetPfAk05jetBeta_.push_back((*puJetIdentifier)[jets->refAt(i)].beta());  
      patJetPfAk05jetBetaStar_.push_back((*puJetIdentifier)[jets->refAt(i)].betaStar());
      patJetPfAk05jetBetaClassic_.push_back( (*puJetIdentifier)[jets->refAt(i)].betaClassic());
      patJetPfAk05jetBetaStarClassic_.push_back((*puJetIdentifier)[jets->refAt(i)].betaStarClassic());
      
      int    idflag = (*puJetIdFlag)[jets->refAt(i)];
      bool loose= false; 
      bool medium = false;
      bool tight = false;
      if( PileupJetIdentifier::passJetId( idflag, PileupJetIdentifier::kLoose) ) {
	loose= true; 
      }
      if( PileupJetIdentifier::passJetId( idflag, PileupJetIdentifier::kMedium) ) {
	medium= true; 
      }
      if( PileupJetIdentifier::passJetId( idflag, PileupJetIdentifier::kTight ) ) {
	tight= true; 
      }
      patJetPfAk05jetpukLoose_.push_back(loose);
      patJetPfAk05jetpukMedium_.push_back(medium);
      patJetPfAk05jetpukTight_.push_back(tight);
      
      chf = jet.chargedHadronEnergyFraction();
      nhf = (jet.neutralHadronEnergy()+jet.HFHadronEnergy())/jet.correctedJet(0).energy();
      cemf = jet.chargedEmEnergyFraction();
      nemf = jet.neutralEmEnergyFraction();
      cmult = jet.chargedMultiplicity();
      nconst = jet.numberOfDaughters();
      
      cout<<"jet.bDiscriminator(combinedSecondaryVertexBJetTags)=  "<<jet.bDiscriminator("combinedSecondaryVertexBJetTags")<<endl;
      cout<<"jet.bDiscriminator(combinedSecondaryVertexV1BJetTags)=  "<<jet.bDiscriminator("combinedSecondaryVertexV1BJetTags")<<endl;
      cout<<"jet.bDiscriminator(combinedSecondaryVertexSoftPFLeptonV1BJetTags)=  "<<jet.bDiscriminator("combinedSecondaryVertexSoftPFLeptonV1BJetTags")<<endl;
      patJetPfAk05BDiscCSV_.push_back(jet.bDiscriminator("combinedSecondaryVertexBJetTags"));
      patJetPfAk05BDiscCSVV1_.push_back(jet.bDiscriminator("combinedSecondaryVertexV1BJetTags"));
      patJetPfAk05BDiscCSVSLV1_.push_back(jet.bDiscriminator("combinedSecondaryVertexSoftPFLeptonV1BJetTags"));
      
      patJetPfAk05En_.push_back(jet.energy());
      patJetPfAk05Pt_.push_back(jet.pt());
      patJetPfAk05Eta_.push_back(jet.eta());
      patJetPfAk05Phi_.push_back(jet.phi());
      patJetPfAk05Et_.push_back(jet.et());
      patJetPfAk05RawPt_.push_back(jet.correctedJet(0).pt());
      patJetPfAk05RawEn_.push_back(jet.correctedJet(0).energy());
      patJetPfAk05HadEHF_.push_back(jet.HFHadronEnergy());
      patJetPfAk05EmEHF_.push_back(jet.HFEMEnergy());
      patJetPfAk05chf_.push_back(chf);
      patJetPfAk05nhf_.push_back(nhf);
      patJetPfAk05cemf_.push_back(cemf);
      patJetPfAk05nemf_.push_back(nemf);
      patJetPfAk05cmult_.push_back(cmult);
      patJetPfAk05nconst_.push_back(nconst);
//      jecUnc->setJetEta(jet.eta());
//      jecUnc->setJetPt(jet.pt());
      //double unc = jecUnc->getUncertainty(true);
      double unc = 1.;
      unc_.push_back(unc);
      double up = (1+unc)*jet.pt();
      double down = (1-unc)*jet.pt();
      patJetPfAk05PtUp_.push_back(up);
      patJetPfAk05PtDn_.push_back(down);
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
      patJetPfAk05LooseId_.push_back(tempJetID);
      PFjetFill++;
      
      if(!realdata){
	bool matchGen=false;
	if (jet.genJet()){
	  matchGen=true;
	  MGjPt.push_back(jet.genJet()->pt());
	  MGjeta.push_back(jet.genJet()->eta());
	  MGjphi.push_back(jet.genJet()->phi());
	  MGjE.push_back(jet.genJet()->energy());
	}
	matchGjet.push_back(matchGen);
      }
    }//end jets
    
    /////////////Calo Jets//////////////////////////////
    edm::Handle<edm::View<pat::Jet> > calojets;
    iEvent.getByLabel(CaloJet_,calojets);
    
    for(edm::View<pat::Jet>::const_iterator calojet=calojets->begin(); calojet!=calojets->end(); ++calojet){
      if( calojet->pt()<10 || PFjetFill==0)  continue;
      caloJetPt_.push_back(calojet->pt());
      caloJetRawPt_.push_back(calojet->correctedJet(0).pt());
      caloJetEn_.push_back(calojet->energy());
      caloJetEta_.push_back(calojet->eta());
      caloJetPhi_.push_back(calojet->phi());
      caloJetHadEHF_.push_back(calojet->hadEnergyInHF());
      caloJetEmEHF_.push_back(calojet->emEnergyInHF());
      caloJetEmFrac_.push_back(calojet->emEnergyFraction());
      caloJetn90_.push_back(calojet->n90());
    }
    
    /////////////////////////////////////////////////////////
    
 //   cout<<"bTags size  "<<bTags.size()<<endl;

//# Loop over jets and study b tag info.

//for (uint i = 0; i != bTags.size(); ++i) {
//   cout<<" Jet "<< i
//         <<" has b tag discriminator = "<<bTags[i].second
//         << " and jet Pt = "<<bTags[i].first->pt()<<endl;
//}
    
    myTree->Fill();
    
}

void 
Tupel::beginJob()
{
  
//  jecUnc = new JetCorrectionUncertainty("Fall12_V7_DATA_Uncertainty_AK5PFchs.txt");
    // register to the TFileService
    edm::Service<TFileService> fs;
    TFileDirectory TestDir = fs->mkdir("test");
    myTree = new TTree("MuonTree","MuonTree");
    myTree->Branch("event",&event);
    myTree->Branch("realdata",&realdata);
    myTree->Branch("run",&run);
    myTree->Branch("lumi",&lumi);
    myTree->Branch("bxnumber",&bxnumber);
    myTree->Branch("EvtInfo_NumVtx",&EvtInfo_NumVtx);
    myTree->Branch("PU_npT",&PU_npT);
    myTree->Branch("PU_npIT",&PU_npIT);
    myTree->Branch("MyWeight",&MyWeight);
    myTree->Branch("Dr01LepPt",&Dr01LepPt);
    myTree->Branch("Dr01LepEta",&Dr01LepEta);
    myTree->Branch("Dr01LepPhi",&Dr01LepPhi);
    myTree->Branch("Dr01LepE",&Dr01LepE);
    myTree->Branch("Dr01LepM",&Dr01LepM);
    myTree->Branch("Dr01LepId",&Dr01LepId);
    myTree->Branch("Dr01LepStatus",&Dr01LepStatus);
    myTree->Branch("Bare01LepPt",&Bare01LepPt);
    myTree->Branch("Bare01LepEt",&Bare01LepEta);
    myTree->Branch("Bare01LepPhi",&Bare01LepPhi);
    myTree->Branch("Bare01LepE",&Bare01LepE);
    myTree->Branch("Bare01LepM",&Bare01LepM);
    myTree->Branch("Bare01LepId",&Bare01LepId);
    myTree->Branch("Bare01LepStatus",&Bare01LepStatus);
    
    myTree->Branch("St03Pt",&St03Pt);
    myTree->Branch("St03Eta",&St03Eta);
    myTree->Branch("St03Phi",&St03Phi);
    myTree->Branch("St03E",&St03E);
    myTree->Branch("St03M",&St03M);
    myTree->Branch("St03Id",&St03Id);
    myTree->Branch("St03Status",&St03Status);
    
    myTree->Branch("St01PhotonPt",&St01PhotonPt);
    myTree->Branch("St01PhotonEta",&St01PhotonEta);
    myTree->Branch("St01PhotonPhi",&St01PhotonPhi);
    myTree->Branch("St01PhotonE",&St01PhotonE);
    myTree->Branch("St01PhotonM",&St01PhotonM);
    myTree->Branch("St01PhotonId",&St01PhotonId);
    myTree->Branch("St01PhotonMomId",&St01PhotonMomId);
    myTree->Branch("St01PhotonNumberMom",&St01PhotonNumberMom);
    myTree->Branch("St01PhotonStatus",&St01PhotonStatus);
    
    myTree->Branch("GjPt",&GjPt);
    myTree->Branch("Gjeta",&Gjeta);
    myTree->Branch("Gjphi",&Gjphi);
    myTree->Branch("GjE",&GjE);
    myTree->Branch("GjPx",&GjPx);
    myTree->Branch("GjPy",&GjPy);
    myTree->Branch("GjPz",&GjPz);
    myTree->Branch("GjChargedFraction",&GjChargedFraction);
    myTree->Branch("matchGjet",&matchGjet);
    myTree->Branch("MGjPt",&MGjPt);
    myTree->Branch("MGjeta",&MGjeta);
    myTree->Branch("MGjphi",&MGjphi);
    myTree->Branch("MGjE",&MGjE); 
    
    //HLT
    myTree->Branch("HLT_Mu17_Mu8",&HLT_Mu17_Mu8);
    myTree->Branch("HLT_Mu17_TkMu8",&HLT_Mu17_TkMu8);
    myTree->Branch("HLT_Elec17_Elec8",&HLT_Elec17_Elec8);
    
    //Muons
    myTree->Branch("patMuonPt_",&patMuonPt_);
    myTree->Branch("patMuonEta_",&patMuonEta_);
    myTree->Branch("patMuonPhi_",&patMuonPhi_);
    myTree->Branch("patMuonVtxZ_",&patMuonVtxZ_);
    myTree->Branch("patMuonEn_",&patMuonEn_);
    myTree->Branch("patMuonCharge_",&patMuonCharge_);
    myTree->Branch("patMuonDxy_",&patMuonDxy_);
    myTree->Branch("patMuonCombId_",&patMuonCombId_);
    myTree->Branch("patMuonTrig_",&patMuonTrig_);
    myTree->Branch("patMuonDetIsoRho_",&patMuonDetIsoRho_);
    myTree->Branch("patMuonPfIsoDbeta_",&patMuonPfIsoDbeta_);
    myTree->Branch("patMuonM_",&patMuonM_);
    myTree->Branch("patMuonPx_",&patMuonPx_);
    myTree->Branch("patMuonPy_",&patMuonPy_);
    myTree->Branch("patMuonPz_",&patMuonPz_);
    myTree->Branch("patMuonGlobalType_",&patMuonGlobalType_);
    myTree->Branch("patMuonTrackerType_",&patMuonTrackerType_);
    myTree->Branch("patMuonPFType_",&patMuonPFType_);
    myTree->Branch("patMuonIsoSumPt_",&patMuonIsoSumPt_);
    myTree->Branch("patMuonIsoRelative_",&patMuonIsoRelative_);
    myTree->Branch("patMuonIsoCalComb_",&patMuonIsoCalComb_);
    myTree->Branch("patMuonIsoDY_",&patMuonIsoDY_);
    myTree->Branch("patMuonChi2Ndoff_",&patMuonChi2Ndoff_);
    myTree->Branch("patMuonNhits_",&patMuonNhits_);
    myTree->Branch("patMuonNMatches_",&patMuonNMatches_);
    myTree->Branch("patMuonDz_",&patMuonDz_);
    myTree->Branch("patMuonPhits_",&patMuonPhits_);
    myTree->Branch("patMuonTkLayers_",&patMuonTkLayers_);
    myTree->Branch("patMuon_PF_IsoSumChargedHadronPt_",&patMuon_PF_IsoSumChargedHadronPt_);
    myTree->Branch("patMuon_PF_IsoSumNeutralHadronEt_",&patMuon_PF_IsoSumNeutralHadronEt_);
    myTree->Branch("patMuon_PF_IsoDY_",&patMuon_PF_IsoDY_);
    myTree->Branch("patMuon_Mu17_Mu8_Matched_",&patMuon_Mu17_Mu8_Matched_);
    myTree->Branch("patMuon_Mu17_TkMu8_Matched_",&patMuon_Mu17_TkMu8_Matched_);
    myTree->Branch("patElecTrig_",&patElecTrig_);
    myTree->Branch("patElecDz_",&patElecDz_);
    myTree->Branch("patElecMVATrigId_",&patElecMVATrigId_);
    myTree->Branch("patElecMVANonTrigId_",&patElecMVANonTrigId_);
    myTree->Branch("patElecPt_",&patElecPt_);
    myTree->Branch("patElecEta_",&patElecEta_);
    myTree->Branch("patElecScEta_",&patElecScEta_);
    myTree->Branch("patElecPhi_",&patElecPhi_);
    myTree->Branch("patElecEnergy_",&patElecEnergy_);
    myTree->Branch("patElecCharge_",&patElecCharge_);
    myTree->Branch("patElecMediumIDOff_",&patElecMediumIDOff_);
    myTree->Branch("patElecMediumIDOff_Tom_",&patElecMediumIDOff_Tom_);
    myTree->Branch("patElecPfIso_",&patElecPfIso_);
    myTree->Branch("patElecPfIsodb_",&patElecPfIsodb_);
    myTree->Branch("patElecPfIsoRho_",&patElecPfIsoRho_);
    myTree->Branch("rhoPrime",&rhoPrime);
    myTree->Branch("neutral_",&neutral_);
    myTree->Branch("photon_",&photon_);
    myTree->Branch("charged_",&charged_);
    myTree->Branch("neutral_Tom_",&neutral_Tom_);
    myTree->Branch("photon_Tom_",&photon_Tom_);
    myTree->Branch("charged_Tom_",&charged_Tom_);
    myTree->Branch("AEff",&AEff);
    myTree->Branch("patElec_mva_presel_",&patElec_mva_presel_);
    
    //PFJet
    myTree->Branch("patJetPfAk05En_",&patJetPfAk05En_);
    myTree->Branch("patJetPfAk05Pt_",&patJetPfAk05Pt_);
    myTree->Branch("patJetPfAk05Eta_",&patJetPfAk05Eta_);
    myTree->Branch("patJetPfAk05Phi_",&patJetPfAk05Phi_);
    myTree->Branch("patJetPfAk05LooseId_",&patJetPfAk05LooseId_);
    myTree->Branch("patJetPfAk05Et_",&patJetPfAk05Et_);
    myTree->Branch("patJetPfAk05RawPt_",&patJetPfAk05RawPt_);
    myTree->Branch("patJetPfAk05RawEn_",&patJetPfAk05RawEn_);
    myTree->Branch("patJetPfAk05HadEHF_",&patJetPfAk05HadEHF_);
    myTree->Branch("patJetPfAk05EmEHF_",&patJetPfAk05EmEHF_);
    myTree->Branch("patJetPfAk05chf_",&patJetPfAk05chf_);
    myTree->Branch("patJetPfAk05nhf_",&patJetPfAk05nhf_);
    myTree->Branch("patJetPfAk05cemf_",&patJetPfAk05cemf_);
    myTree->Branch("patJetPfAk05nemf_",&patJetPfAk05nemf_);
    myTree->Branch("patJetPfAk05cmult_",&patJetPfAk05cmult_);
    myTree->Branch("patJetPfAk05nconst_",&patJetPfAk05nconst_);
    myTree->Branch("patJetPfAk05jetBeta_",&patJetPfAk05jetBeta_);
    myTree->Branch("patJetPfAk05jetBetaClassic_",&patJetPfAk05jetBetaClassic_);
    myTree->Branch("patJetPfAk05jetBetaStar_",&patJetPfAk05jetBetaStar_);
    myTree->Branch("patJetPfAk05jetBetaStarClassic_",&patJetPfAk05jetBetaStarClassic_);
    myTree->Branch("patJetPfAk05jetpuMVA_",&patJetPfAk05jetpuMVA_);
    myTree->Branch("patJetPfAk05jetpukLoose_",&patJetPfAk05jetpukLoose_);
    myTree->Branch("patJetPfAk05jetpukMedium_",&patJetPfAk05jetpukMedium_);
    myTree->Branch("patJetPfAk05jetpukTight_",&patJetPfAk05jetpukTight_);
    myTree->Branch("patJetPfAk05BDiscCSV_",&patJetPfAk05BDiscCSV_);
    myTree->Branch("patJetPfAk05BDiscCSVV1_",&patJetPfAk05BDiscCSVV1_);
    myTree->Branch("patJetPfAk05BDiscCSVSLV1_",&patJetPfAk05BDiscCSVSLV1_);
    myTree->Branch("unc_",&unc_);
    myTree->Branch("patJetPfAk05PtUp_",&patJetPfAk05PtUp_);
    myTree->Branch("patJetPfAk05PtDn_",&patJetPfAk05PtDn_); 

    //CaloJets
    myTree->Branch("caloJetPt_",&caloJetPt_);
    myTree->Branch("caloJetRawPt_",&caloJetRawPt_);
    myTree->Branch("caloJetEn_",&caloJetEn_);
    myTree->Branch("caloJetEta_",&caloJetEta_);
    myTree->Branch("caloJetPhi_",&caloJetPhi_);
    myTree->Branch("caloJetHadEHF_",&caloJetHadEHF_);
    myTree->Branch("caloJetEmEHF_",&caloJetEmEHF_);
    myTree->Branch("caloJetEmFrac_",&caloJetEmFrac_);
    myTree->Branch("caloJetn90_",&caloJetn90_);
    
    myTree->Branch("id1_pdfInfo_",&id1_pdfInfo_);
    myTree->Branch("id2_pdfInfo_",&id2_pdfInfo_);
    myTree->Branch("x1_pdfInfo_",&x1_pdfInfo_);
    myTree->Branch("x2_pdfInfo_",&x2_pdfInfo_);
    myTree->Branch("scalePDF_pdfInfo_",&scalePDF_pdfInfo_);
    myTree->Branch("ptHat_",&ptHat_);
    myTree->Branch("mcWeight_",&mcWeight_);
    myTree->Branch("nup",&nup);   
}

void 
Tupel::endJob() 
{
//  delete jecUnc;
  myTree->Print();
}

DEFINE_FWK_MODULE(Tupel);
