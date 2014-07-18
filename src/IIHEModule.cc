#include "UserCode/IIHETree/interface/IIHEAnalysis.h"
#include "UserCode/IIHETree/interface/IIHEModule.h"

IIHEModule::IIHEModule(const edm::ParameterSet& iConfig){}
IIHEModule::~IIHEModule(){}

void IIHEModule::config(IIHEAnalysis* parent){
  parent_ = parent ;
}

bool IIHEModule::addBranch(std::string name, int type){
  bool result = parent_->addBranch(name, type) ;
  return result ;
}
bool IIHEModule::addBranch(std::string name){
  bool result = parent_->addBranch(name) ;
  return result ;
}

void IIHEModule::store(std::string name, bool   value){ parent_->store(name, value) ; }
void IIHEModule::store(std::string name, double value){ parent_->store(name, value) ; }
void IIHEModule::store(std::string name, float  value){ parent_->store(name, value) ; }
void IIHEModule::store(std::string name, int    value){ parent_->store(name, value) ; }
void IIHEModule::store(std::string name, std::vector<bool>   value){ parent_->store(name, value) ; }
void IIHEModule::store(std::string name, std::vector<double> value){ parent_->store(name, value) ; }
void IIHEModule::store(std::string name, std::vector<float>  value){ parent_->store(name, value) ; }
void IIHEModule::store(std::string name, std::vector<int>    value){ parent_->store(name, value) ; }
void IIHEModule::setBranchType(int type){ parent_->setBranchType(type) ; }

// ------------ method called once each job just before starting event loop  ------------
void IIHEModule::beginJob(){}

// ------------ method called to for each event  ------------
void IIHEModule::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
}

void IIHEModule::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup){}
void IIHEModule::beginEvent(){}
void IIHEModule::endEvent(){}


// ------------ method called once each job just after ending the event loop  ------------
void IIHEModule::endJob(){}

DEFINE_FWK_MODULE(IIHEModule);