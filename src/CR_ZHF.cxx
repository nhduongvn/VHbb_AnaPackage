#include "inc/CR_ZHF.h"
#include "inc/Util.h"
#include <iostream>
#include <sstream>
#include <string>


CR_ZHF::CR_ZHF(string region, bool isData, double wei): 
  AnaBaseSelector(region, isData, wei) 
{
  
  hist_ZeeH.set("ZeeH") ;
  hist_ZmmH.set("ZmmH") ;

}

CR_ZHF::~CR_ZHF()
{
}


void CR_ZHF::SlaveBegin(const BaseTree* r) 
{
  
  cout << "\n======Initial setting for " << m_region << "========" << endl ;
  cout << "\n- Name                    " << m_region ;
  cout << "\n- Is data                 " << m_IsData ;
  cout << "\n- Weight                  " << m_wei ;
  cout << "\n====================================================" << endl ;

  hist_ZeeH.Book(m_region) ;
  hist_ZmmH.Book(m_region) ;

};

void CR_ZHF::Process(const BaseTree* r)
{
  //cout << "\n======================" ;
  //cout << "\n " << r->EVENT_run << " " << r->EVENT_event ;
  //cout << "\n Jet are: " ;
  
  if (m_IsData && r->json!=1) return ;
  if ((r->Vtype) != 0 && (r->Vtype) != 1) return ;
  
  bool doPassTrigger(false) ;
  if ((r->Vtype) == 0 && (r->HLT_BIT_HLT_IsoMu20_v)) doPassTrigger = true ;
#ifdef MCFILE 
  if (!m_IsData && (r->Vtype) == 1 && (r->HLT_BIT_HLT_Ele27_eta2p1_WPLoose_Gsf_v)) doPassTrigger = true ;
#else
  if (m_IsData && (r->Vtype) == 1 && (r->HLT_BIT_HLT_Ele27_eta2p1_WPLoose_Gsf_v)) doPassTrigger = true ;
#endif

  if (!doPassTrigger) return ;

  m_wei = 1. ;

  Obj objTmp ;
  
  std::vector<Obj> vLeps ;
  
  TString typeTmp("") ;
  if (abs((r->vLeptons_pdgId)[0]) == 11) {
    typeTmp = "ele" ;
  }
  if (abs((r->vLeptons_pdgId)[0]) == 13) {
    typeTmp = "muon" ;
  }
  if (typeTmp != "") {
    objTmp.Set(typeTmp, 0, r, true) ; //use vLep
    if (objTmp.SelectLepton(r)) vLeps.push_back(objTmp) ;
  }
 
  if (abs((r->vLeptons_pdgId)[1]) == 11) {
    typeTmp = "ele" ;
  }
  if (abs((r->vLeptons_pdgId)[1]) == 13) {
    typeTmp = "muon" ;
  }
  if (typeTmp != "") {
    objTmp.Set(typeTmp, 1, r, true) ; //use vLep
    if (objTmp.SelectLepton(r)) vLeps.push_back(objTmp) ;
  }

  std::vector<Obj> hJets ;
  objTmp.Set("hjet", (r->hJCidx)[0], r) ;
  if (objTmp.SelectTagJet(r, GLOBC::HJET_PT, 0.935)) hJets.push_back(objTmp) ; 
  objTmp.Set("hjet", (r->hJCidx)[1], r) ;
  if (objTmp.SelectTagJet(r, GLOBC::HJET_PT, 0.46)) hJets.push_back(objTmp) ; 

  float bTagWei(1) ;
#ifdef MCFILE
  bTagWei = (r->bTagWeight) ;
#endif

  if (vLeps.size() == 2 && hJets.size() == 2) {//two hjets found no additional jets
    if ((r->V_mass) > 85 && (r->V_mass) < 97 && ((r->HCSV_mass) < 90 || (r->HCSV_mass) > 145) && fabs((r->HVdPhi)) > 2.9) {
      if ((r->Vtype) == 1) { //Zee
        hist_ZeeH.Fill(r, vLeps[0], vLeps[1], hJets[0], hJets[1], m_wei*bTagWei) ; 
      } //Zee
      if ((r->Vtype) == 0) {
        hist_ZmmH.Fill(r, vLeps[0], vLeps[1], hJets[0], hJets[1], m_wei*bTagWei) ;
      } //Zmumu
    } //V_mass ...
  } //two hjets

    

}

void CR_ZHF::SlaveTerminate(const BaseTree* r) 
{  
};

void CR_ZHF::Terminate(TList* mergedList) 
{
}
