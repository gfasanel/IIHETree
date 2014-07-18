#ifndef UserCode_IIHETree_IIHEModule_h
#define UserCode_IIHETree_IIHEModule_h

// system include files
#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

// user include files
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaReco/interface/BasicCluster.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/MuonCocktails.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "RecoEgamma/EgammaElectronAlgos/interface/ElectronHcalHelper.h"
#include "UserCode/IIHETree/interface/BranchWrapper.h"
#include "UserCode/IIHETree/interface/IIHEAnalysis.h"

#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TH1F.h"

namespace edm {
  class ParameterSet;
  class Event;
  class EventSetup;
}

class IIHEAnalysis ; // Forward declaration

// class decleration
class IIHEModule : public edm::EDAnalyzer {

private:

public:
  explicit IIHEModule(const edm::ParameterSet& iConfig);
  ~IIHEModule();
  
  bool addBranch(std::string);
  bool addBranch(std::string,int);
  void config(IIHEAnalysis*);
  void begin();
  void store(std::string, bool  );
  void store(std::string, double);
  void store(std::string, float );
  void store(std::string, int   );
  void store(std::string, std::vector<bool>  );
  void store(std::string, std::vector<double>);
  void store(std::string, std::vector<float> );
  void store(std::string, std::vector<int>   );
  void setBranchType(int);
  
  void   pubBeginJob(){   beginJob() ; } ;
  void pubBeginEvent(){ beginEvent() ; } ;
  void   pubEndEvent(){   endEvent() ; } ;
  virtual void pubAnalyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){ analyze(iEvent, iSetup) ; } ;

protected:
  IIHEAnalysis* parent_;
  
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  
  virtual void beginEvent() ;
  virtual void endEvent() ;
  
  std::vector<BranchWrapperBase*> all_branches_ ;
  std::vector<BranchWrapperBase*> live_branches_;
  
  // ----------member data ---------------------------
  bool debug;
};
#endif
//define this as a plug-in
