#include "UserCode/IIHETree/interface/IIHEModulePhoton.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"

#include <iostream>
#include <TMath.h>
#include <vector>

using namespace std ;
using namespace reco;
using namespace edm ;

IIHEModulePhoton::IIHEModulePhoton(const edm::ParameterSet& iConfig): IIHEModule(iConfig){}
IIHEModulePhoton::~IIHEModulePhoton(){}

// ------------ method called once each job just before starting event loop  ------------
void IIHEModulePhoton::beginJob(){
  addBranch("ph_n", kUInt) ;
  setBranchType(kVectorBool) ;
  addBranch("ph_isPFlowPhoton") ;
  addBranch("ph_isStandardPhoton") ;
  addBranch("ph_hasConversionTracks") ;
  addBranch("ph_hasPixelSeed") ;
  //addBranch("ph_conversionTrackProvenance",kVectorInt) ;
  addBranch("ph_isEB") ;
  addBranch("ph_isEE") ;
  addBranch("ph_isEBGap") ;
  addBranch("ph_isEBEtaGap") ;
  addBranch("ph_isEBPhiGap") ;
  addBranch("ph_isEEGap") ;
  addBranch("ph_isEERingGap") ;
  addBranch("ph_isEEDeeGap") ;
  addBranch("ph_isEBEEGap") ;
  
  setBranchType(kVectorFloat) ;
  addBranch("ph_hadronicOverEm") ;
  addBranch("ph_hadronicDepth1OverEm") ;
  addBranch("ph_hadronicDepth2OverEm") ;
  addBranch("ph_hadTowOverEm") ;
  addBranch("ph_hadTowDepth1OverEm") ;
  addBranch("ph_hadTowDepth2OverEm") ;
  
  addBranch("ph_e1x5") ;
  addBranch("ph_e2x5") ;
  addBranch("ph_e3x3") ;
  addBranch("ph_e5x5") ;
  
  addBranch("ph_maxEnergyXtal") ;
  addBranch("ph_sigmaEtaEta") ;
  addBranch("ph_sigmaIetaIeta") ;
  
  addBranch("ph_r1x5") ;
  addBranch("ph_r2x5") ;
  addBranch("ph_r9") ;
  
  //addBranch("ph_CorrectedEnergy") ;
  //addBranch("ph_CorrectedEnergyError") ;
  
  addBranch("ph_mipChi2") ;
  addBranch("ph_mipTotEnergy") ;
  addBranch("ph_mipSlope") ;
  addBranch("ph_mipIntercept") ;
  
  addBranch("ph_mipNhitCone", kVectorInt) ;
  addBranch("ph_mipIsHalo", kVectorBool) ;
  
  setBranchType(kVectorFloat) ;
  addBranch("ph_ecalRecHitSumEtConeDR04") ;
  addBranch("ph_hcalTowerSumEtConeDR04") ;
  addBranch("ph_hcalDepth1TowerSumEtConeDR04") ;
  addBranch("ph_hcalDepth2TowerSumEtConeDR04") ;
  addBranch("ph_hcalTowerSumEtBcConeDR04") ;
  addBranch("ph_hcalDepth1TowerSumEtBcConeDR04") ;
  addBranch("ph_hcalDepth2TowerSumEtBcConeDR04") ;
  addBranch("ph_trkSumPtSolidConeDR04") ;
  addBranch("ph_trkSumPtHollowConeDR04") ;
  
  setBranchType(kVectorInt) ;
  addBranch("ph_nTrkSolidConeDR04") ;
  addBranch("ph_nTrkHollowConeDR04") ;
  
  setBranchType(kVectorFloat) ;
  addBranch("ph_ecalRecHitSumEtConeDR03") ;
  addBranch("ph_hcalTowerSumEtConeDR03") ;
  addBranch("ph_hcalDepth1TowerSumEtConeDR03") ;
  addBranch("ph_hcalDepth2TowerSumEtConeDR03") ;
  addBranch("ph_hcalTowerSumEtBcConeDR03") ;
  addBranch("ph_hcalDepth1TowerSumEtBcConeDR03") ;
  addBranch("ph_hcalDepth2TowerSumEtBcConeDR03") ;
  addBranch("ph_trkSumPtSolidConeDR03") ;
  addBranch("ph_trkSumPtHollowConeDR03") ;
  
  setBranchType(kVectorInt) ;
  addBranch("ph_nTrkSolidConeDR03") ;
  addBranch("ph_nTrkHollowConeDR03") ;
  
  setBranchType(kVectorFloat) ;
  addBranch("ph_chargedHadronIso") ;
  addBranch("ph_chargedHadronIsoWrongVtx") ;
  addBranch("ph_neutralHadronIso") ;
  addBranch("ph_photonIso") ;
  addBranch("ph_sumChargedParticlePt") ;
  addBranch("ph_sumNeutralHadronEtHighThreshold") ;
  addBranch("ph_sumPhotonEtHighThreshold") ;
  addBranch("ph_sumPUPt") ;
  
  addBranch("ph_nClusterOutsideMustache", kVectorInt) ;
  addBranch("ph_etOutsideMustache") ;
  addBranch("ph_pfMVA") ;
}

// ------------ method called to for each event  ------------
void IIHEModulePhoton::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  reco::PhotonCollection photons = parent_->getPhotonCollection() ;
  
  store("ph_n", (unsigned int) photons.size()) ;
  for(reco::PhotonCollection::const_iterator phiter = photons.begin() ; phiter!=photons.end() ; ++phiter){
    store("ph_isPFlowPhoton"                 , phiter->isPFlowPhoton()                   ) ;
    store("ph_isStandardPhoton"              , phiter->isStandardPhoton()                ) ;
    store("ph_hasConversionTracks"           , phiter->hasConversionTracks()             ) ;
    store("ph_hasPixelSeed"                  , phiter->hasPixelSeed()                    ) ;
    //store("ph_conversionTrackProvenance"     , phiter->conversionTrackProvenance()       ) ;
    store("ph_isEB"                          , phiter->isEB()                            ) ;
    store("ph_isEE"                          , phiter->isEE()                            ) ;
    store("ph_isEBGap"                       , phiter->isEBGap()                         ) ;
    store("ph_isEBEtaGap"                    , phiter->isEBEtaGap()                      ) ;
    store("ph_isEBPhiGap"                    , phiter->isEBPhiGap()                      ) ;
    store("ph_isEEGap"                       , phiter->isEEGap()                         ) ;
    store("ph_isEERingGap"                   , phiter->isEERingGap()                     ) ;
    store("ph_isEEDeeGap"                    , phiter->isEEDeeGap()                      ) ;
    store("ph_isEBEEGap"                     , phiter->isEBEEGap()                       ) ;

    store("ph_hadronicOverEm"                , phiter->hadronicOverEm()                  ) ;
    store("ph_hadronicDepth1OverEm"          , phiter->hadronicDepth1OverEm()            ) ;
    store("ph_hadronicDepth2OverEm"          , phiter->hadronicDepth2OverEm()            ) ;
    store("ph_hadTowOverEm"                  , phiter->hadTowOverEm()                    ) ;
    store("ph_hadTowDepth1OverEm"            , phiter->hadTowDepth1OverEm()              ) ;
    store("ph_hadTowDepth2OverEm"            , phiter->hadTowDepth2OverEm()              ) ;

    store("ph_e1x5"                          , phiter->e1x5()                            ) ;
    store("ph_e2x5"                          , phiter->e2x5()                            ) ;
    store("ph_e3x3"                          , phiter->e3x3()                            ) ;
    store("ph_e5x5"                          , phiter->e5x5()                            ) ;

    store("ph_maxEnergyXtal"                 , phiter->maxEnergyXtal()                   ) ;
    store("ph_sigmaEtaEta"                   , phiter->sigmaEtaEta()                     ) ;
    store("ph_sigmaIetaIeta"                 , phiter->sigmaIetaIeta()                   ) ;

    store("ph_r1x5"                          , phiter->r1x5()                            ) ;
    store("ph_r2x5"                          , phiter->r2x5()                            ) ;
    store("ph_r9"                            , phiter->r9()                              ) ;

    //store("ph_CorrectedEnergy"               , phiter->CorrectedEnergy()                 ) ;
    //store("ph_CorrectedEnergyError"          , phiter->CorrectedEnergyError()            ) ;

    store("ph_mipChi2"                       , phiter->mipChi2()                         ) ;
    store("ph_mipTotEnergy"                  , phiter->mipTotEnergy()                    ) ;
    store("ph_mipSlope"                      , phiter->mipSlope()                        ) ;
    store("ph_mipIntercept"                  , phiter->mipIntercept()                    ) ;
    store("ph_mipNhitCone"                   , phiter->mipNhitCone()                     ) ;
    store("ph_mipIsHalo"                     , phiter->mipIsHalo()                       ) ;

    store("ph_ecalRecHitSumEtConeDR04"       , phiter->ecalRecHitSumEtConeDR04()         ) ;
    store("ph_hcalTowerSumEtConeDR04"        , phiter->hcalTowerSumEtConeDR04()          ) ;
    store("ph_hcalDepth1TowerSumEtConeDR04"  , phiter->hcalDepth1TowerSumEtConeDR04()    ) ;
    store("ph_hcalDepth2TowerSumEtConeDR04"  , phiter->hcalDepth2TowerSumEtConeDR04()    ) ;
    store("ph_hcalTowerSumEtBcConeDR04"      , phiter->hcalTowerSumEtBcConeDR04()        ) ;
    store("ph_hcalDepth1TowerSumEtBcConeDR04", phiter->hcalDepth1TowerSumEtBcConeDR04()  ) ;
    store("ph_hcalDepth2TowerSumEtBcConeDR04", phiter->hcalDepth2TowerSumEtBcConeDR04()  ) ;
    store("ph_trkSumPtSolidConeDR04"         , phiter->trkSumPtSolidConeDR04()           ) ;
    store("ph_trkSumPtHollowConeDR04"        , phiter->trkSumPtHollowConeDR04()          ) ;
    store("ph_nTrkSolidConeDR04"             , phiter->nTrkSolidConeDR04()               ) ;
    store("ph_nTrkHollowConeDR04"            , phiter->nTrkHollowConeDR04()              ) ;

    store("ph_ecalRecHitSumEtConeDR03"       , phiter->ecalRecHitSumEtConeDR03()         ) ;
    store("ph_hcalTowerSumEtConeDR03"        , phiter->hcalTowerSumEtConeDR03()          ) ;
    store("ph_hcalDepth1TowerSumEtConeDR03"  , phiter->hcalDepth1TowerSumEtConeDR03()    ) ;
    store("ph_hcalDepth2TowerSumEtConeDR03"  , phiter->hcalDepth2TowerSumEtConeDR03()    ) ;
    store("ph_hcalTowerSumEtBcConeDR03"      , phiter->hcalTowerSumEtBcConeDR03()        ) ;
    store("ph_hcalDepth1TowerSumEtBcConeDR03", phiter->hcalDepth1TowerSumEtBcConeDR03()  ) ;
    store("ph_hcalDepth2TowerSumEtBcConeDR03", phiter->hcalDepth2TowerSumEtBcConeDR03()  ) ;
    store("ph_trkSumPtSolidConeDR03"         , phiter->trkSumPtSolidConeDR03()           ) ;
    store("ph_trkSumPtHollowConeDR03"        , phiter->trkSumPtHollowConeDR03()          ) ;
    store("ph_nTrkSolidConeDR03"             , phiter->nTrkSolidConeDR03()               ) ;
    store("ph_nTrkHollowConeDR03"            , phiter->nTrkHollowConeDR03()              ) ;

    store("ph_chargedHadronIso"               , phiter->chargedHadronIso()               ) ;
    store("ph_chargedHadronIsoWrongVtx"       , phiter->chargedHadronIsoWrongVtx()       ) ;
    store("ph_neutralHadronIso"               , phiter->neutralHadronIso()               ) ;
    store("ph_photonIso"                      , phiter->photonIso()                      ) ;
    store("ph_sumChargedParticlePt"           , phiter->sumChargedParticlePt()           ) ;
    store("ph_sumNeutralHadronEtHighThreshold", phiter->sumNeutralHadronEtHighThreshold()) ;
    store("ph_sumPhotonEtHighThreshold"       , phiter->sumPhotonEtHighThreshold()       ) ;
    store("ph_sumPUPt"                        , phiter->sumPUPt()                        ) ;

    store("ph_nClusterOutsideMustache"        , phiter->nClusterOutsideMustache()        ) ;
    store("ph_etOutsideMustache"              , phiter->etOutsideMustache()              ) ;
    store("ph_pfMVA"                          , phiter->pfMVA()                          ) ;
  }
}

void IIHEModulePhoton::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup){}
void IIHEModulePhoton::beginEvent(){}
void IIHEModulePhoton::endEvent(){}


// ------------ method called once each job just after ending the event loop  ------------
void IIHEModulePhoton::endJob(){}

DEFINE_FWK_MODULE(IIHEModulePhoton);
