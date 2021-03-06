#include "inc/SR.h"
#include "inc/Util.h"
#include <iostream>
#include <sstream>
#include <string>


SR::SR(string region, bool isData, double wei): 
  AnaBaseSelector(region, isData, wei) 
{
  
  hist_ZeeH_lowVpt_dijet.set("ZeeH_lowVpt_dijet") ;
  hist_ZmmH_lowVpt_dijet.set("ZmmH_lowVpt_dijet") ;
  hist_ZeeH_highVpt_dijet.set("ZeeH_highVpt_dijet") ;
  hist_ZmmH_highVpt_dijet.set("ZmmH_highVpt_dijet") ;
  hist_ZeeH_noVptCut_dijet.set("ZeeH_noVptCut_dijet") ;
  hist_ZmmH_noVptCut_dijet.set("ZmmH_noVptCut_dijet") ;

  hist_ZeeH_lowVpt_dijet_boosted.set("ZeeH_lowVpt_dijet_boosted") ;
  hist_ZmmH_lowVpt_dijet_boosted.set("ZmmH_lowVpt_dijet_boosted") ;
  hist_ZeeH_highVpt_dijet_boosted.set("ZeeH_highVpt_dijet_boosted") ;
  hist_ZmmH_highVpt_dijet_boosted.set("ZmmH_highVpt_dijet_boosted") ;
  hist_ZeeH_noVptCut_dijet_boosted.set("ZeeH_noVptCut_dijet_boosted") ;
  hist_ZmmH_noVptCut_dijet_boosted.set("ZmmH_noVptCut_dijet_boosted") ;

  hist_ZeeH_lowVpt_dijet_only.set("ZeeH_lowVpt_dijet_only") ;
  hist_ZmmH_lowVpt_dijet_only.set("ZmmH_lowVpt_dijet_only") ;
  hist_ZeeH_highVpt_dijet_only.set("ZeeH_highVpt_dijet_only") ;
  hist_ZmmH_highVpt_dijet_only.set("ZmmH_highVpt_dijet_only") ;
  hist_ZeeH_noVptCut_dijet_only.set("ZeeH_noVptCut_dijet_only") ;
  hist_ZmmH_noVptCut_dijet_only.set("ZmmH_noVptCut_dijet_only") ;

  hist_ZeeBoostedH_noVptCut_boosted.set("ZeeBoostedH_subjetCA15pruned_noVptCut_boosted") ;
  hist_ZmmBoostedH_noVptCut_boosted.set("ZmmBoostedH_subjetCA15pruned_noVptCut_boosted") ;
  hist_ZeeBoostedH_highVpt_boosted.set("ZeeBoostedH_subjetCA15pruned_highVpt_boosted") ;
  hist_ZmmBoostedH_highVpt_boosted.set("ZmmBoostedH_subjetCA15pruned_highVpt_boosted") ; 

  hist_ZeeBoostedH_noVptCut_dijet_boosted.set("ZeeBoostedH_subjetCA15pruned_noVptCut_dijet_boosted") ;
  hist_ZmmBoostedH_noVptCut_dijet_boosted.set("ZmmBoostedH_subjetCA15pruned_noVptCut_dijet_boosted") ;
  hist_ZeeBoostedH_highVpt_dijet_boosted.set("ZeeBoostedH_subjetCA15pruned_highVpt_dijet_boosted") ;
  hist_ZmmBoostedH_highVpt_dijet_boosted.set("ZmmBoostedH_subjetCA15pruned_highVpt_dijet_boosted") ;

  hist_ZeeBoostedH_noVptCut_boosted_only.set("ZeeBoostedH_subjetCA15pruned_noVptCut_boosted_only") ;
  hist_ZmmBoostedH_noVptCut_boosted_only.set("ZmmBoostedH_subjetCA15pruned_noVptCut_boosted_only") ;
  hist_ZeeBoostedH_highVpt_boosted_only.set("ZeeBoostedH_subjetCA15pruned_highVpt_boosted_only") ;
  hist_ZmmBoostedH_highVpt_boosted_only.set("ZmmBoostedH_subjetCA15pruned_highVpt_boosted_only") ;

}

SR::~SR()
{
}


void SR::SlaveBegin(const BaseTree* r) 
{
  
  cout << "\n======Initial setting for " << m_region << "========" << endl ;
  cout << "\n- Name                    " << m_region ;
  cout << "\n- Is data                 " << m_IsData ;
  cout << "\n- Weight                  " << m_wei ;
  cout << "\n====================================================" << endl ;

  hist_ZeeH_lowVpt_dijet.Book(m_region) ;
  hist_ZmmH_lowVpt_dijet.Book(m_region) ;
  hist_ZeeH_highVpt_dijet.Book(m_region) ;
  hist_ZmmH_highVpt_dijet.Book(m_region) ;
  hist_ZeeH_noVptCut_dijet.Book(m_region) ;
  hist_ZmmH_noVptCut_dijet.Book(m_region) ;

  hist_ZeeH_lowVpt_dijet_boosted.Book(m_region) ;
  hist_ZmmH_lowVpt_dijet_boosted.Book(m_region) ;
  hist_ZeeH_highVpt_dijet_boosted.Book(m_region) ;
  hist_ZmmH_highVpt_dijet_boosted.Book(m_region) ;
  hist_ZeeH_noVptCut_dijet_boosted.Book(m_region) ;
  hist_ZmmH_noVptCut_dijet_boosted.Book(m_region) ;

  hist_ZeeH_lowVpt_dijet_only.Book(m_region) ;
  hist_ZmmH_lowVpt_dijet_only.Book(m_region) ;
  hist_ZeeH_highVpt_dijet_only.Book(m_region) ;
  hist_ZmmH_highVpt_dijet_only.Book(m_region) ;
  hist_ZeeH_noVptCut_dijet_only.Book(m_region) ;
  hist_ZmmH_noVptCut_dijet_only.Book(m_region) ;

  hist_ZeeBoostedH_noVptCut_boosted.Book(m_region) ;
  hist_ZmmBoostedH_noVptCut_boosted.Book(m_region) ;
  hist_ZeeBoostedH_highVpt_boosted.Book(m_region) ;
  hist_ZmmBoostedH_highVpt_boosted.Book(m_region) ;

  hist_ZeeBoostedH_noVptCut_dijet_boosted.Book(m_region) ;
  hist_ZmmBoostedH_noVptCut_dijet_boosted.Book(m_region) ;
  hist_ZeeBoostedH_highVpt_dijet_boosted.Book(m_region) ;
  hist_ZmmBoostedH_highVpt_dijet_boosted.Book(m_region) ;

  hist_ZeeBoostedH_noVptCut_boosted_only.Book(m_region) ;
  hist_ZmmBoostedH_noVptCut_boosted_only.Book(m_region) ;
  hist_ZeeBoostedH_highVpt_boosted_only.Book(m_region) ;
  hist_ZmmBoostedH_highVpt_boosted_only.Book(m_region) ;


  TString tmpStr = "dR_V_fatjetCA15pruned_" + m_region ;
  hDr = new TH1D(tmpStr, "", 1000, 0, 10) ;
  tmpStr = "N_fatjetCA15pruned_" + m_region ;
  h_nFatJet = new TH1D(tmpStr, "", 10, 0, 10) ;
  tmpStr = "Vpt_hasZ_" + m_region ;
  hVpt_1 = new TH1D(tmpStr, "", GLOBC::NBIN_MASS, 0, GLOBC::MAX_MASS) ;
  hVpt_1->Sumw2() ;
  tmpStr = "Vpt_hasZ_hasFatJet100_" + m_region ;
  hVpt_2 = new TH1D(tmpStr, "", GLOBC::NBIN_MASS, 0, GLOBC::MAX_MASS) ;
  hVpt_2->Sumw2() ;
  tmpStr = "Vpt_hasZ_hasFatJet100_hasSubJet_" + m_region ;
  hVpt_3 = new TH1D(tmpStr, "", GLOBC::NBIN_MASS, 0, GLOBC::MAX_MASS) ;
  hVpt_3->Sumw2() ;
  tmpStr = "Vpt_hasZ_hasFatJet100_hasSubJet_passSubjetTag_" + m_region ;
  hVpt_4 = new TH1D(tmpStr, "", GLOBC::NBIN_MASS, 0, GLOBC::MAX_MASS) ;
  hVpt_4->Sumw2() ;
  tmpStr = "Vpt_hasZ_hasFatJet100_hasSubJet_passSubjetTag_passCSV_" + m_region ;
  hVpt_5 = new TH1D(tmpStr, "", GLOBC::NBIN_MASS, 0, GLOBC::MAX_MASS) ;
  hVpt_5->Sumw2() ;
  tmpStr = "Vpt_hasZ_hasFatJet100_hasSubJet_passSubjetTag_passCSV_HmassCut_" + m_region ;
  hVpt_6 = new TH1D(tmpStr, "", GLOBC::NBIN_MASS, 0, GLOBC::MAX_MASS) ;
  hVpt_6->Sumw2() ;
  
  hDr_test = new TH1D("Dr_test", "", 1000, 0, 10) ;
  hMassTest = new TH1D("MassTest", "", GLOBC::NBIN_MASS, 0, GLOBC::MAX_MASS) ;
  
};

void SR::Process(const BaseTree* r)
{

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

//TEMP: weight = 1 
  m_wei = 1. ;
  
  float bTagWei(1) ;
#ifdef MCFILE
  bTagWei = (r->bTagWeight) ;
#endif

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
  if (objTmp.SelectTagJet(r, GLOBC::HJET_PT, 0.605)) hJets.push_back(objTmp) ; 
  objTmp.Set("hjet", (r->hJCidx)[1], r) ;
  if (objTmp.SelectTagJet(r, GLOBC::HJET_PT, 0.605)) hJets.push_back(objTmp) ; 

  vector<Obj> fatJets ; 
  int nFatJet(0) ;
  float fatJetPtCut = 200 ;
  float bTagSubjetCuts[2] = {0.605, 0.605} ;
  float dRcut = 1.5 ;
  float dRtmp = -1 ;
  for (int i = 0; i < r->nFatjetCA15pruned; i++) {
    dRtmp = Aux::DeltaR(r->V_eta, r->V_phi, r->FatjetCA15pruned_eta[i], r->FatjetCA15pruned_phi[i]) ;
    if (r->FatjetCA15pruned_pt[i] > fatJetPtCut) {
      hDr->Fill(dRtmp) ;
      if (dRtmp > dRcut) nFatJet++ ;
    }
    objTmp.Set("FatjetCA15pruned", i, r) ;
    if (objTmp.SelectFatJet(r, fatJetPtCut, dRcut)) fatJets.push_back(objTmp) ;
  } //end loop over fat jet
     
  sort(fatJets.begin(), fatJets.end(), greater<Obj>()) ;


  std::vector<Obj> boostedHjets ;
  if(fatJets.size() > 0) Aux::GetSubjets(r, fatJets[0], boostedHjets, bTagSubjetCuts, false, true) ;
  float bTagSubjetCuts_tmp[2] = {-1, -1} ; //set both -1 to by pass Tag requirement
  std::vector<Obj> boostedHjets_noBtag ; //no btag for efficiency study
  if(fatJets.size() > 0) Aux::GetSubjets(r, fatJets[0], boostedHjets_noBtag, bTagSubjetCuts_tmp, false, true) ;

  sort(boostedHjets.begin(), boostedHjets.end(), greater<Obj>()) ;
  sort(boostedHjets_noBtag.begin(), boostedHjets_noBtag.end(), greater<Obj>()) ;
  
  bool dijet_selected(false) ;  
  bool boosted_selected(false) ;
  float lowVptCut = 50 ;
  if (vLeps.size() == 2 && hJets.size() == 2) {//two hjets found no additional jets
    if (r->V_pt > lowVptCut && (r->V_mass) > 75 && (r->V_mass) < 105 && (r->HCSV_reg_mass) < 250) {
      dijet_selected = true ;
    } //V_mass ...
  } //two hjets

  if (vLeps.size() == 2 && fatJets.size() > 0 && boostedHjets.size() >=2) {
    float hMass = Aux::Cal_Hmass(boostedHjets) ;
    if (fatJets[0].SubJetTag(boostedHjets[0], boostedHjets[1])) {
    if (r->V_pt > lowVptCut && (r->V_mass) > 75 && (r->V_mass) < 105 && hMass < 250) {
      boosted_selected = true ;
    } //V_mass
    } //SubJetTag
  } //two boostedHjets
  
  if (dijet_selected) {
    FillVH(r, vLeps, hJets, hist_ZeeH_lowVpt_dijet, hist_ZeeH_highVpt_dijet, hist_ZeeH_noVptCut_dijet, hist_ZmmH_lowVpt_dijet, hist_ZmmH_highVpt_dijet, hist_ZmmH_noVptCut_dijet, m_wei*bTagWei) ; 
  }
  if (boosted_selected) {
    FillV_boostedH(r, vLeps, fatJets[0], boostedHjets, hist_ZeeBoostedH_highVpt_boosted, hist_ZeeBoostedH_noVptCut_boosted, hist_ZmmBoostedH_highVpt_boosted, hist_ZmmBoostedH_noVptCut_boosted) ;
  }
  if (dijet_selected && boosted_selected) { 
    FillVH(r, vLeps, hJets, hist_ZeeH_lowVpt_dijet_boosted, hist_ZeeH_highVpt_dijet_boosted, hist_ZeeH_noVptCut_dijet_boosted, hist_ZmmH_lowVpt_dijet_boosted, hist_ZmmH_highVpt_dijet_boosted, hist_ZmmH_noVptCut_dijet_boosted, m_wei*bTagWei) ; 
    FillV_boostedH(r, vLeps, fatJets[0], boostedHjets, hist_ZeeBoostedH_highVpt_dijet_boosted, hist_ZeeBoostedH_noVptCut_dijet_boosted, hist_ZmmBoostedH_highVpt_dijet_boosted, hist_ZmmBoostedH_noVptCut_dijet_boosted) ;
  }
  if (dijet_selected && !boosted_selected) {
    FillVH(r, vLeps, hJets, hist_ZeeH_lowVpt_dijet_only, hist_ZeeH_highVpt_dijet_only, hist_ZeeH_noVptCut_dijet_only, hist_ZmmH_lowVpt_dijet_only, hist_ZmmH_highVpt_dijet_only, hist_ZmmH_noVptCut_dijet_only, m_wei*bTagWei) ; 
  }
  if (!dijet_selected && boosted_selected) {
    FillV_boostedH(r, vLeps, fatJets[0], boostedHjets, hist_ZeeBoostedH_highVpt_boosted_only, hist_ZeeBoostedH_noVptCut_boosted_only, hist_ZmmBoostedH_highVpt_boosted_only, hist_ZmmBoostedH_noVptCut_boosted_only) ;
  
  }

  //===efficiency study===
  if (vLeps.size() == 2) {
       
    h_nFatJet->Fill(nFatJet, m_wei*bTagWei) ; 
    hVpt_1->Fill(r->V_pt, m_wei*bTagWei) ;
    
    if (fatJets.size() > 0) {
      
      hVpt_2->Fill(r->V_pt, m_wei*bTagWei) ;
           
      if (boostedHjets_noBtag.size() >= 2) {
        
        hVpt_3->Fill(r->V_pt, m_wei*bTagWei) ;

        //==apply tagging==
        bool passTag1 = TMath::Max(boostedHjets_noBtag[0].m_mass, boostedHjets_noBtag[1].m_mass) < 0.67*fatJets[0].m_mass ? true : false ;
        dRtmp = Aux::DeltaR(boostedHjets_noBtag[0].m_eta, boostedHjets_noBtag[0].m_phi, boostedHjets_noBtag[1].m_eta, boostedHjets_noBtag[1].m_phi) ;
        bool passTag2 = (TMath::Min(boostedHjets_noBtag[0].m_pt*boostedHjets_noBtag[0].m_pt, boostedHjets_noBtag[1].m_pt*boostedHjets_noBtag[1].m_pt)/(fatJets[0].m_mass*fatJets[0].m_mass))*dRtmp*dRtmp > 0.09 ? true : false ;
        bool passCSV = (boostedHjets_noBtag[0].SelectBoostedHjet(r, GLOBC::HJET_PT, bTagSubjetCuts[0], false, true) && boostedHjets_noBtag[1].SelectBoostedHjet(r, GLOBC::HJET_PT, bTagSubjetCuts[1], false, true)) ? true : false ;

        if (passTag1 && passTag2) {
          
          hVpt_4->Fill(r->V_pt, m_wei*bTagWei) ;

          if (passCSV) {

            hVpt_5->Fill(r->V_pt, m_wei*bTagWei) ;
          
            float mass = Aux::Cal_Hmass(boostedHjets_noBtag) ;
            
            hMassTest->Fill(mass, m_wei*bTagWei) ;
            if (mass < 150 && mass > 90) { 
            
              hVpt_6->Fill(r->V_pt, m_wei*bTagWei) ;
          
            }
          } //pass CSV
        } //pass boosted jet tag
      } // at least two subjet found
    } //end if (fatJets.size() > 0

  } //end vLeps == 2
} //end process

void SR::FillVH(const BaseTree* r, const vector<Obj>& vLeps, const vector<Obj>& hJets, HistVH& hist_ZeeH_lowVpt, HistVH& hist_ZeeH_highVpt, HistVH& hist_ZeeH_noVptCut, HistVH& hist_ZmmH_lowVpt, HistVH& hist_ZmmH_highVpt, HistVH& hist_ZmmH_noVptCut, double wei) {
  float VptCut = 100 ;
  if ((r->Vtype) == 1) { //Zee
    hist_ZeeH_noVptCut.Fill(r, vLeps[0], vLeps[1], hJets[0], hJets[1], wei) ; 
    if (r->V_pt < VptCut) hist_ZeeH_lowVpt.Fill(r, vLeps[0], vLeps[1], hJets[0], hJets[1], wei) ; 
    if (r->V_pt > VptCut) hist_ZeeH_highVpt.Fill(r, vLeps[0], vLeps[1], hJets[0], hJets[1], wei) ; 
  } //Zee
  if ((r->Vtype) == 0) {
    hist_ZmmH_noVptCut.Fill(r, vLeps[0], vLeps[1], hJets[0], hJets[1], wei) ; 
    if (r->V_pt < VptCut) hist_ZmmH_lowVpt.Fill(r, vLeps[0], vLeps[1], hJets[0], hJets[1], wei) ;
    if (r->V_pt > VptCut) hist_ZmmH_highVpt.Fill(r, vLeps[0], vLeps[1], hJets[0], hJets[1], wei) ;
  } //Zmumu
}

void SR::FillV_boostedH(const BaseTree* r, const vector<Obj>& vLeps, const Obj& fatJet, const vector<Obj>& boostedHjets_matched, HistVBoostedH& hist_ZeeBoostedH_highVpt, HistVBoostedH& hist_ZeeBoostedH_noVptCut, HistVBoostedH& hist_ZmmBoostedH_highVpt, HistVBoostedH& hist_ZmmBoostedH_noVptCut) {
  
  float hMass = Aux::Cal_Hmass(boostedHjets_matched) ;
  float VptCut = 200 ;
  if (r->Vtype == 1) { //Zee
    hist_ZeeBoostedH_noVptCut.Fill(r, vLeps[0], vLeps[1], fatJet, boostedHjets_matched, m_wei, hMass) ;
    if (r->V_pt > VptCut) hist_ZeeBoostedH_highVpt.Fill(r, vLeps[0], vLeps[1], fatJet, boostedHjets_matched, m_wei, hMass) ;
  }
  if (r->Vtype == 0) { //Zmm
    hist_ZmmBoostedH_noVptCut.Fill(r, vLeps[0], vLeps[1], fatJet, boostedHjets_matched, m_wei, hMass) ;
    if (r->V_pt > VptCut) hist_ZmmBoostedH_highVpt.Fill(r, vLeps[0], vLeps[1], fatJet, boostedHjets_matched, m_wei, hMass) ; 
  }

}


void SR::SlaveTerminate(const BaseTree* r) 
{  
};

void SR::Terminate(TList* mergedList) 
{
}
