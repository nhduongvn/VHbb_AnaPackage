#include "inc/CR_ZLF.h"
#include <iostream>
#include <sstream>
#include <string>


CR_ZLF::CR_ZLF(string region, bool isData, double wei): 
  AnaBaseSelector(region, isData, wei) 
{
  
  hist_ZeeH.set("ZeeH") ;
  hist_ZmmH.set("ZmmH") ;
  hist_ZeeBoostedH_boosted.set("ZeeBoostedH_subjetCA15pruned_boosted") ;
  hist_ZmmBoostedH_boosted.set("ZmmBoostedH_subjetCA15pruned_boosted") ;

}

CR_ZLF::~CR_ZLF()
{
}


void CR_ZLF::SlaveBegin(const BaseTree* r) 
{
  
  cout << "\n======Initial setting for " << m_region << "========" << endl ;
  cout << "\n- Name                    " << m_region ;
  cout << "\n- Is data                 " << m_IsData ;
  cout << "\n- Weight                  " << m_wei ;
  cout << "\n====================================================" << endl ;

  hist_ZeeH.Book(m_region) ;
  hist_ZmmH.Book(m_region) ; 
  hist_ZeeBoostedH_boosted.Book(m_region) ;
  hist_ZmmBoostedH_boosted.Book(m_region) ;
  
  TString tmpStr = "CutFlow_ZeeH_" + m_region ; 
  hCutFlow[0] = new TH1D(tmpStr, "", 10, 0, 10) ;
  hCutFlow[0]->GetXaxis()->SetBinLabel(1, "All") ;
  hCutFlow[0]->GetXaxis()->SetBinLabel(2, "JSON") ;
  hCutFlow[0]->GetXaxis()->SetBinLabel(3, "Vtype") ;
  hCutFlow[0]->GetXaxis()->SetBinLabel(4, "Trigger") ;
  hCutFlow[0]->GetXaxis()->SetBinLabel(5, "LepJet_size_nJet") ;
  hCutFlow[0]->GetXaxis()->SetBinLabel(6, "Mass_pt_HVdPhi") ;
  tmpStr = "CutFlow_ZmuuH_" + m_region ; 
  hCutFlow[1] = new TH1D(tmpStr, "", 10, 0, 10) ;
  hCutFlow[1]->GetXaxis()->SetBinLabel(1, "All") ;
  hCutFlow[1]->GetXaxis()->SetBinLabel(2, "JSON") ;
  hCutFlow[1]->GetXaxis()->SetBinLabel(3, "Vtype") ;
  hCutFlow[1]->GetXaxis()->SetBinLabel(4, "Trigger") ;
  hCutFlow[1]->GetXaxis()->SetBinLabel(5, "LepJet_size_nJet") ;
  hCutFlow[1]->GetXaxis()->SetBinLabel(6, "Mass_pt_HVdPhi") ;

  tmpStr = "lheHT_" + m_region ; 
  h_lheHT = new TH1D(tmpStr, "", 1000, 0, 1000) ;

};

void CR_ZLF::Process(const BaseTree* r)
{
  //cout << "\n======================" ;
  //cout << "\n " << r->EVENT_run << " " << r->EVENT_event ;
  //cout << "\n Jet are: " ;

#ifdef MCFILE  
  h_lheHT->Fill(r->lheHT) ;
#endif

  hCutFlow[0]->Fill(0.5) ;
  hCutFlow[1]->Fill(0.5) ;
  if (m_IsData && r->json!=1) return ;
  hCutFlow[0]->Fill(1.5) ;
  hCutFlow[1]->Fill(1.5) ;

  int VtypeTmp = r->Vtype ;

  if (VtypeTmp != 0 && VtypeTmp != 1) return ;
  if (VtypeTmp == 1) hCutFlow[0]->Fill(2.5) ;
  if (VtypeTmp == 0) hCutFlow[1]->Fill(2.5) ;
  
  bool doPassTrigger(false) ;
  if (VtypeTmp == 0 && (r->HLT_BIT_HLT_IsoMu20_v)) doPassTrigger = true ;
#ifdef MCFILE 
  if (!m_IsData && (r->Vtype) == 1 && (r->HLT_BIT_HLT_Ele27_eta2p1_WPLoose_Gsf_v)) doPassTrigger = true ;
#else
  if (m_IsData && (r->Vtype) == 1 && (r->HLT_BIT_HLT_Ele27_eta2p1_WPLoose_Gsf_v)) doPassTrigger = true ;
#endif

  if (!doPassTrigger) return ;
  if (VtypeTmp == 1) hCutFlow[0]->Fill(3.5) ;
  if (VtypeTmp == 0) hCutFlow[1]->Fill(3.5) ;

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
  if (objTmp.SelectTagJet(r, GLOBC::HJET_PT, 0.935, true)) hJets.push_back(objTmp) ; 
  objTmp.Set("hjet", (r->hJCidx)[1], r) ;
  if (objTmp.SelectTagJet(r, GLOBC::HJET_PT, 1, true, true)) hJets.push_back(objTmp) ; 
    
  //cout << "\n Size: " << vLeps.size() << "  " << hJets.size() << "  " << nJets << std::endl ;
  
  std::vector<Obj> fatJets ;
  std::vector<Obj> subJets ;
  float bTagSubjetCuts[2] = {0.935, 1} ;
  float fatJetPtCut = 200 ;
  float dRcut = 1.5 ;
  for (int i = 0; i < r->nFatjetCA15pruned; i++) {
    objTmp.Set("FatjetCA15pruned", i, r) ;
    if (objTmp.SelectFatJet(r, fatJetPtCut, dRcut)) fatJets.push_back(objTmp) ;
  } //end loop over fat jet
     
  sort(fatJets.begin(), fatJets.end(), greater<Obj>()) ;

  if(fatJets.size() > 0) Aux::GetSubjets(r, fatJets[0], subJets, bTagSubjetCuts, true, true) ;

  int nJets(0) ;
  int nJets_boostedCase(0) ;
  for (int i = 0; i < r->nJet; i++) {
    //if ((r->Jet_puId)[i] == 7 && (r->Jet_pt)[i] > 20 && fabs((r->Jet_eta)[i]) < 2.4) nJets++ ;
    if ((r->Jet_pt)[i] > 20 && fabs((r->Jet_eta)[i]) < 2.4) {
      float dRtmp = fatJets.size() > 0 ? Aux::DeltaR(fatJets[0].m_eta, fatJets[0].m_phi, (r->Jet_eta)[i], (r->Jet_phi)[i]) : 10 ;
#ifdef MCFILE
      if ((r->Jet_puId)[i] == 7) {
        nJets++ ;
        if (dRtmp > dRcut) nJets_boostedCase++ ;
      }
#else
      nJets++ ;
      if (dRtmp > dRcut) nJets_boostedCase++ ;
#endif

    }
  }

  
  float bTagWei(1) ;
#ifdef MCFILE
  bTagWei = (r->bTagWeight) ;
#endif
  
  if (vLeps.size() == 2 && hJets.size() == 2 && nJets == 2) {//two hjets found no additional jets
    if (VtypeTmp == 1) hCutFlow[0]->Fill(4.5) ;
    if (VtypeTmp == 0) hCutFlow[1]->Fill(4.5) ;
    if ((r->V_mass) > 75 && (r->V_mass) < 105 && (r->V_pt) > 100 && (r->HCSV_pt) > 100 && fabs((r->HVdPhi)) > 2.9) {
      if (VtypeTmp == 1) { //Zee
        hCutFlow[0]->Fill(5.5) ;
        hist_ZeeH.Fill(r, vLeps[0], vLeps[1], hJets[0], hJets[1], m_wei*bTagWei) ; 
      } //Zee
      if (VtypeTmp == 0) {
        hCutFlow[1]->Fill(5.5) ;
        hist_ZmmH.Fill(r, vLeps[0], vLeps[1], hJets[0], hJets[1], m_wei*bTagWei) ;
      } //Zmumu
    } //V_mass ...
  } //two hjets

  if (vLeps.size() == 2 && subJets.size() >= 2 && nJets_boostedCase == 0) { //boosted jet found and no extra jets
    float hMass = Aux::Cal_Hmass(subJets) ;
    float dPhiTmp = Aux::DeltaPhi(fatJets[0].m_phi, r->V_phi) ;
    if ((r->V_mass) > 75 && (r->V_mass) < 105 && (r->V_pt) > 100 && fatJets[0].m_pt > 100 && fabs(dPhiTmp) > 2.9) {
      if (VtypeTmp == 1) { //Zee
        
        hist_ZeeBoostedH_boosted.Fill(r, vLeps[0], vLeps[1], fatJets[0], subJets, m_wei, hMass) ;
      
      } //Zee
      if (VtypeTmp == 0) {
      
        hist_ZmmBoostedH_boosted.Fill(r, vLeps[0], vLeps[1], fatJets[0], subJets, m_wei, hMass) ;
      
      } //Zmumu
    } //V_mass ...

  
  }



  
}

void CR_ZLF::SlaveTerminate(const BaseTree* r) 
{  
};

void CR_ZLF::Terminate(TList* mergedList) 
{
}
