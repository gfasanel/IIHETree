#ifndef UserCode_IIHETree_IIHEAnalysis_h
#define UserCode_IIHETree_IIHEAnalysis_h

// System includes
#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

// user includes
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/LuminosityBlock.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "UserCode/IIHETree/interface/BranchWrapper.h"
#include "UserCode/IIHETree/interface/IIHEModule.h"
#include "UserCode/IIHETree/interface/TriggerObject.h"

#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

// ROOT includes
#include "TFile.h"
#include "TTree.h"

// Local includes
#include "UserCode/IIHETree/interface/Types.h"

namespace edm {
  class ParameterSet;
  class Event;
  class EventSetup;
}

// Forward declarations
class IIHEModule ;
class TriggerMatchParameters ;

// class decleration
class IIHEAnalysis : public edm::EDAnalyzer {

friend class IIHEModuleVertex ;
friend class IIHEModuleMuon ;

private:
  edm::EDGetTokenT<reco::BeamSpot> beamSpotLabel_ ;
  math::XYZPoint* beamspot_ ;
  math::XYZPoint* firstPrimaryVertex_ ;
public:
  explicit IIHEAnalysis(const edm::ParameterSet& iConfig);
  ~IIHEAnalysis();
  
  bool store(std::string, bool    );
  bool store(std::string, double  );
  bool store(std::string, float   );
  bool store(std::string, int     );
  bool store(std::string, unsigned);
  bool store(std::string, std::vector<bool        >);
  bool store(std::string, std::vector<double      >);
  bool store(std::string, std::vector<float       >);
  bool store(std::string, std::vector<int         >);
  bool store(std::string, std::vector<unsigned int>);
  
  bool addBranch(std::string) ;
  bool addBranch(std::string,int) ;
  bool branchExists(std::string) ;
  
  void setBranchType(int) ;
  int  getBranchType() ;
  int  saveToFile(TObject*) ;
  void listBranches() ;
  
  // MC truth
  void addToMCTruthWhitelist(std::vector<int>) ;
  std::vector<int> getMCTruthWhitelist(){ return MCTruthWhitelist_ ; }
  
  // Particle collections
  std::vector<const reco::SuperCluster*> getSuperClusters(){ return superclusters_ ; }
  reco::PhotonCollection getPhotonCollection(){
    reco::PhotonCollection        photons(  photonCollection_->begin(),   photonCollection_->end()) ;
    return photons   ;
  }
  reco::GsfElectronCollection getElectronCollection(){
    reco::GsfElectronCollection electrons(electronCollection_->begin(), electronCollection_->end());
    return electrons ;
  }
  reco::MuonCollection getMuonCollection(){
    reco::MuonCollection            muons(    muonCollection_->begin(),     muonCollection_->end()) ;
    return muons     ;
  }
  
  // Primary vertices
  const reco::VertexCollection* getPrimaryVertices(){
    const reco::VertexCollection* primaryVertices = pvCollection_.product() ;
    return primaryVertices ;
  }
  math::XYZPoint* getFirstPrimaryVertex(){ return firstPrimaryVertex_ ; }
  math::XYZPoint* getBeamspot(){ return beamspot_ ; }
  
  edm::EDGetTokenT<EcalRecHitCollection> getReducedBarrelRecHitCollectionToken(){ return reducedBarrelRecHitCollectionToken_ ; }
  edm::EDGetTokenT<EcalRecHitCollection> getReducedEndcapRecHitCollectionToken(){ return reducedEndcapRecHitCollectionToken_ ; }
  
  void configureBranches();
  std::vector<std::string> splitString(const std::string&, const char*) ;
  
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  
  void beginEvent() ;
  void endEvent() ;
  
  // ----------member data ---------------------------
  std::vector<BranchWrapperBase*> allVars_ ;
  std::vector<BranchWrapperBVV* > vars_BVV_;
  std::vector<BranchWrapperDVV* > vars_DVV_;
  std::vector<BranchWrapperFVV* > vars_FVV_;
  std::vector<BranchWrapperIVV* > vars_IVV_;
  std::vector<BranchWrapperUVV* > vars_UVV_;
  std::vector<BranchWrapperBV*  > vars_BV_ ;
  std::vector<BranchWrapperDV*  > vars_DV_ ;
  std::vector<BranchWrapperFV*  > vars_FV_ ;
  std::vector<BranchWrapperIV*  > vars_IV_ ;
  std::vector<BranchWrapperUV*  > vars_UV_ ;
  std::vector<BranchWrapperB*   > vars_B_  ;
  std::vector<BranchWrapperD*   > vars_D_  ;
  std::vector<BranchWrapperF*   > vars_F_  ;
  std::vector<BranchWrapperI*   > vars_I_  ;
  std::vector<BranchWrapperU*   > vars_U_  ;
  
  int currentVarType_ ;
  std::vector< std::pair<std::string, int> > listOfBranches_  ;
  std::vector< std::pair<std::string, int> > missingBranches_ ;
  
  // Bools for including each module so they can be turned on/off without recompilation
  bool includeEventModule_        ;
  bool includeVertexModule_       ;
  bool includeSuperClusterModule_ ;
  bool includePhotonModule_       ;
  bool includeElectronModule_     ;
  bool includeMuonModule_         ;
  bool includeMETModule_          ;
  bool includeHEEPModule_         ;
  bool includeMCTruthModule_      ;
  bool includeTriggerModule_      ;
  
  // Collections of physics objects
  std::vector<const reco::SuperCluster*  >      superclusters_ ;
  edm::Handle<reco::PhotonCollection     >   photonCollection_ ;
  edm::Handle<reco::GsfElectronCollection> electronCollection_ ;
  edm::Handle<reco::MuonCollection       >     muonCollection_ ;
  edm::Handle<reco::VertexCollection     >       pvCollection_ ;
  
  edm::InputTag        photonCollectionLabel_ ;
  edm::InputTag      electronCollectionLabel_ ;
  edm::InputTag          muonCollectionLabel_ ;
  edm::InputTag           primaryVertexLabel_ ;
  edm::Handle<reco::BeamSpot> beamspotHandle_ ;
  
  edm::InputTag reducedBarrelRecHitCollection_ ;
  edm::InputTag reducedEndcapRecHitCollection_ ;
  edm::EDGetTokenT<EcalRecHitCollection> reducedBarrelRecHitCollectionToken_ ;
  edm::EDGetTokenT<EcalRecHitCollection> reducedEndcapRecHitCollectionToken_ ;
  
  bool debug_;
  std::string git_hash_  ;
  std::string globalTag_ ;
  
  // MC truth module
  std::vector<int> MCTruthWhitelist_ ;

  // config parameters -------------------------------
  TFile* mainFile_ ;
  TTree* dataTree_ ;
  TTree* metaTree_ ;
  
  std::vector<IIHEModule*> childModules_;
};
#endif
//define this as a plug-in

