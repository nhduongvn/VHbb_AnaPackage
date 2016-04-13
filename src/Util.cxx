#include "inc/Util.h"


//==function and method of Object=====
//
//====constructor=======
void Obj::Set(TString type, unsigned i, const BaseTree* r, bool doUseVobject) {
  m_softLep_type = 0 ;
  if (type == "") cout << "\n Warning: you set no type!!!" ;
  if (type == "ele") {
    m_ind = i ;
    m_type = "ele" ;
    m_e = -1 ; //TODO: need to calculate electron energy
    if (!doUseVobject) {
    m_pt = (r->selLeptons_pt)[i] ;
    m_eta = (r->selLeptons_eta)[i] ;
    m_phi = (r->selLeptons_phi)[i] ;
    m_mass = (r->selLeptons_mass)[i] ;
    m_charge = (r->selLeptons_charge)[i] ;
    }
    else {
    m_pt = (r->vLeptons_pt)[i] ;
    m_eta = (r->vLeptons_eta)[i] ;
    m_phi = (r->vLeptons_phi)[i] ;
    m_mass = (r->vLeptons_mass)[i] ;
    m_charge = (r->vLeptons_charge)[i] ;
    }
  }

  if (type == "muon") {
    m_ind = i ;
    m_type = "muon" ;
    m_e = -1 ; //TODO: need to calculate muon energy
    if (!doUseVobject) {
    m_pt = (r->selLeptons_pt)[i] ;
    m_eta = (r->selLeptons_eta)[i] ;
    m_phi = (r->selLeptons_phi)[i] ;
    m_mass = (r->selLeptons_mass)[i] ;
    m_charge = (r->selLeptons_charge)[i] ;
    }
    else {
    m_pt = (r->vLeptons_pt)[i] ;
    m_eta = (r->vLeptons_eta)[i] ;
    m_phi = (r->vLeptons_phi)[i] ;
    m_mass = (r->vLeptons_mass)[i] ;
    m_charge = (r->vLeptons_charge)[i] ;
    }
  }


  if (type == "jet" || type == "hjet") {
    m_ind = i ;
    m_type = type ;
    m_e = -1 ; 
    m_pt = (r->Jet_pt)[i] ;
    m_eta = (r->Jet_eta)[i] ;
    m_phi = (r->Jet_phi)[i] ;
    m_mass = (r->Jet_mass)[i] ; //TODO: need to calculate jet mass 
    m_charge = -100 ;
  }

  if (type == "SubjetCA15pruned") {
    m_ind = i ;
    m_type = type ;
    m_e = -1 ; 
    m_pt = (r->SubjetCA15pruned_pt)[i] ;
    m_eta = (r->SubjetCA15pruned_eta)[i] ;
    m_phi = (r->SubjetCA15pruned_phi)[i] ;
    m_mass = (r->SubjetCA15pruned_mass)[i] ; //TODO: need to calculate jet mass 
    m_charge = -100 ;
  }
  
  if (type == "FatjetCA15pruned") {
    m_ind = i ;
    m_type = type ;
    m_e = -1 ; 
    m_pt = (r->FatjetCA15pruned_pt)[i] ;
    m_eta = (r->FatjetCA15pruned_eta)[i] ;
    m_phi = (r->FatjetCA15pruned_phi)[i] ;
    m_mass = (r->FatjetCA15pruned_mass)[i] ; //TODO: need to calculate jet mass 
    m_charge = -100 ;
  }


  if (type == "met") {
    m_ind = i ;
    m_type = "met" ;
    m_e = -1 ;
    m_pt = (r->met_pt) ;
    m_eta = -10 ; 
    m_phi = (r->met_phi) ;
    m_mass = -1 ;
    m_charge = -100 ;
  }

//====setting gen objects====
#ifdef MCFILE
/*
  if (type == "genEle") {
    m_ind = i ;
    m_type = "genEle" ;
    m_e = -1 ; //TODO: need to calculate electron energy
    m_pt = (r->genLep_pt)[i] ;
    m_eta = (r->genLep_eta)[i] ;
    m_phi = (r->genLep_phi)[i] ;
    m_mass = 0.511*1e-3 ;
    m_charge = (r->genLep_charge)[i] ;
  }
  if (type == "genMuon") {
    m_ind = i ;
    m_type = "genMuon" ;
    m_e = -1 ; //TODO: need to calculate muon energy
    m_pt = (r->genLep_pt)[i] ;
    m_eta = (r->genLep_eta)[i] ;
    m_phi = (r->genLep_phi)[i] ;
    m_mass = 105.658*1e-3 ;
    m_charge = (r->genLep_charge)[i] ;
  }
  if (type == "genJet") {
    m_ind = i ;
    m_type = "genJet" ;
    m_e = -100 ; //==TODO need to set correct energy for genJet
    m_pt = (r->genJet_pt)[i] ;
    m_eta = (r->genJet_eta)[i] ;
    m_phi = (r->genJet_phi)[i] ;
    m_mass = -1 ; //TODO: need to calculate jet mass 
    m_charge = -100 ; 
  }
*/
#endif

} //end Obj::Set

//====Operator------------
bool Obj::operator> (const Obj& o1) const {
  return (m_pt >= o1.m_pt) ;
}

//====Electron selection---------
bool Obj::SelectElec() {
  if (fabs(m_eta) < 1.442 || (fabs(m_eta) < 2.4 && fabs(m_eta) > 1.556)) {
    if (m_pt > 20) {
      return true ;      
    }
  }
  return false ;
}

//====Muon selection==============
bool Obj::SelectMuon() {
  if (fabs(m_eta) < 2.4) {
    if (m_pt > 20) {
      return true ;      
    }
  }
  return false ;
}

bool Obj::SelectLepton(const BaseTree* r) {
  if (m_pt > 20 && fabs(m_eta) < 2.4) {
    if ((r->vLeptons_relIso04)[m_ind] < 0.25) {
      return true ;
    }
  }
  return false ;
}


bool Obj::SelectGenLep(BaseTree* r) {
  if (fabs(m_eta) > 2.4) return false ;
  if (m_pt < 20) return false ;
  return true ;
}


//====Jet selection===============
bool Obj::SelectJet(float ptCut) const {
  if (fabs(m_eta) < 2.4) {
    if (m_pt > ptCut) {
      return true ;      
    }
  }
  return false ;
}

bool Obj::SelectGenJet(BaseTree* r) {
  if (fabs(m_eta) < 2.4) {
    if (m_pt > 30) {
      return true ;      
    }
  }
  return false ;
}


//====MET selection===============
bool Obj::SelectMet(BaseTree* r) {
  if((r->met_pt) < 40) return true ;
  return false ;
}

//====MET selection===============
bool Obj::SelectMet(float sig, const vector<Obj>& jets, TH1D* hTest, TH1D* hTest1, TH1D* hTest2) const {
  if (sig < 2) return false ;
  float minDr = 100 ;
  hTest1->Fill(m_phi) ;
  for (unsigned i = 0 ; i < jets.size() ; ++i) {
    hTest2->Fill(jets[i].m_phi) ;
    float dRtmp = Aux::DeltaPhi(m_phi, jets[i].m_phi) ;
    if (dRtmp < minDr) minDr = dRtmp ;
  }
  hTest->Fill(minDr) ;
  if (minDr > 0.2) return true ;
  return false ;
}


bool Obj::SelectTagJet(const BaseTree* r, double ptCut, double csv_cut, bool invert_csvCut, bool gtZero_csv) {
  bool passJet = SelectJet(ptCut) ;
  bool passCsvCut = invert_csvCut ? ((r->Jet_btagCSV)[m_ind] < csv_cut) : ((r->Jet_btagCSV)[m_ind] > csv_cut);
  passCsvCut = gtZero_csv ? (passCsvCut && (r->Jet_btagCSV)[m_ind] > 0) : passCsvCut ;
  if (passJet && passCsvCut) return true ;
  return false ;
}

bool Obj::SelectBoostedHjet(const BaseTree* r, double ptCut, double csv_cut, bool invert_csvCut, bool gtZero_csv) {
  bool passJet = SelectJet(ptCut) ;
  bool passCsvCut = invert_csvCut ? ((r->SubjetCA15pruned_btag)[m_ind] < csv_cut) : ((r->SubjetCA15pruned_btag)[m_ind] > csv_cut);
  passCsvCut = gtZero_csv ? (passCsvCut && (r->SubjetCA15pruned_btag)[m_ind] > 0) : passCsvCut ;
  if (passJet && passCsvCut) return true ;
  return false ;
}

bool Obj::SubJetTag(Obj jet1, Obj jet2) {
  bool passTag1 = TMath::Max(jet1.m_mass, jet2.m_mass) < 0.67*m_mass ? true : false ;
  float dRtmp = Aux::DeltaR(jet1.m_eta, jet1.m_phi, jet2.m_eta, jet2.m_phi) ;
  bool passTag2 = (TMath::Min(jet1.m_pt*jet1.m_pt, jet2.m_pt*jet2.m_pt)/(m_mass*m_mass))*dRtmp*dRtmp > 0.09 ? true : false ;
  return passTag1 && passTag2 ;
}


void Obj::ApplyJECshift(BaseTree* r, TString uncType, bool doUseAobject) {
  /*
  float jetunc = 0 ;
  if (!doUseAobject) jetunc = (r->Jet_JECUnc)[m_ind] ;
  else jetunc = (r->Jet_JECUnc)[m_ind] ;
  //cout << "\n Jet unc: " << m_pt << "  " << jetunc ;
  if (uncType == "JECU") {
    m_e *= (1+jetunc) ;
    m_pt *= (1+jetunc) ;
  }
  if (uncType == "JECD") {
    m_e *= (1-jetunc) ;
    m_pt *= (1-jetunc) ;
  }
  //cout << "\n Jet unc after: " << m_pt << "  " << jetunc ;
  */
}

void Obj::ApplyJER(BaseTree* r, TString uncType, bool doUseAobject) {
  /*
  float bestMCjet_pt ;
  float bestMCjet_eta ;
  if (!doUseAobject) {
    bestMCjet_pt = (r->Jet_pt_bestMC)[m_ind] ;
    bestMCjet_eta = (r->Jet_eta_bestMC)[m_ind] ;
  }
  else {
    bestMCjet_pt = (r->Jet_pt_bestMC)[m_ind] ;
    bestMCjet_eta = (r->Jet_eta_bestMC)[m_ind] ;
  }

  float resBias = Aux::ResolutionBias_NOM(fabs(m_eta)) ;
  if (uncType == "JERU") resBias = Aux::ResolutionBias_UP(fabs(m_eta)) ;
  if (uncType == "JERD") resBias = Aux::ResolutionBias_DOWN(fabs(m_eta)) ;
  if (m_pt > 0 && (fabs(m_pt - bestMCjet_pt)/m_pt)<0.5) {
    float cor = (m_pt + resBias*(m_pt-bestMCjet_pt))/m_pt ;
    m_pt *= cor ; 
    m_e *= cor ;
  }
  */
}

//===BOOK histogram=====================
//===function and method of HistObj=====
//======================================
void HistObj::Book(TString regionName) {
  
  TString nameTmp = m_type + "_pt_" + regionName ;
  pt = new TH1D(nameTmp, "", GLOBC::NBIN_PT, 0, GLOBC::MAX_PT) ;
  pt->Sumw2() ;
  nameTmp = m_type + "_eta_" + regionName ;
  eta = new TH1D(nameTmp, "", GLOBC::NBIN_ETA, GLOBC::MIN_ETA, GLOBC::MAX_ETA) ;
  eta->Sumw2() ;
  nameTmp = m_type + "_phi_" + regionName ;
  phi = new TH1D(nameTmp, "", GLOBC::NBIN_PHI, GLOBC::MIN_PHI, GLOBC::MAX_PHI) ;
  phi->Sumw2() ;

}

void HistObj::Fill(const BaseTree* r, const Obj& objIn, double w) {
  pt->Fill(objIn.m_pt,w) ;
  eta->Fill(objIn.m_eta,w) ;
  phi->Fill(objIn.m_phi,w) ;
}

void HistObj::Write() {
  pt->Write() ;
  eta->Write() ;
  phi->Write() ;
}

//==function and method of HistJet=======
void HistJet::Book(TString regionName) {
  HistObj::Book(regionName) ;
  TString strTmp = m_type + "_csv_" + regionName ;
  csv = new TH1D(strTmp, "", GLOBC::NBIN_CSV, GLOBC::MIN_CSV, GLOBC::MAX_CSV) ;
  csv->Sumw2() ;
}

void HistJet::Fill(const BaseTree* r, const Obj& objIn, double w) {
  HistObj::Fill(r, objIn, w) ;
  csv->Fill((r->Jet_btagCSV)[objIn.m_ind], w) ;
}

//void HistJet::Write() {
  //HistObj::Write() ;
  //csv->Write() ;
//}

//==function and method of HistZ==
void HistZ::Book(TString regionName) {
  m_l1.Book(m_type + "_" + regionName) ;
  m_l2.Book(m_type + "_" + regionName) ;
  vpt = new TH1D("Vpt_" + regionName, "", GLOBC::NBIN_MASS, 0, GLOBC::MAX_MASS) ;
  vpt_Hmass_cut = new TH1D("Vpt_Hmass_cut_" + regionName, "", GLOBC::NBIN_MASS, 0, GLOBC::MAX_MASS) ;
}

void HistZ::Fill(const BaseTree* r, const Obj& lep1, const Obj& lep2, double w, float boostedH_mass) {
  m_l1.Fill(r, lep1, w) ;
  m_l2.Fill(r, lep2, w) ;
  vpt->Fill(r->V_pt, w) ;
  if (boostedH_mass < 0 && r->HCSV_reg_mass < 150 && r->HCSV_reg_mass > 90) vpt_Hmass_cut->Fill(r->V_pt, w) ;
  if (boostedH_mass > 90 && boostedH_mass < 150) vpt_Hmass_cut->Fill(r->V_pt, w) ;
}

void HistZ::Write() {
  m_l1.Write() ;
  m_l2.Write() ;
}

void HistH::Book(TString regionName) {
  m_j1.Book("H_" + regionName) ;
  m_j2.Book("H_" + regionName) ;
  hcsv_mass = new TH1D("HCSV_mass_" + regionName, "", GLOBC::NBIN_MASS, 0, GLOBC::MAX_MASS) ;
  hcsv_reg_mass = new TH1D("HCSV_reg_mass_" + regionName, "", GLOBC::NBIN_MASS, 0, GLOBC::MAX_MASS) ;
  h_mass = new TH1D("H_mass_" + regionName, "", GLOBC::NBIN_MASS, 0, GLOBC::MAX_MASS) ;
  h_reg_mass = new TH1D("H_reg_mass_" + regionName, "", GLOBC::NBIN_MASS, 0, GLOBC::MAX_MASS) ;
}

void HistH::Fill(const BaseTree* r, const Obj& jet1, const Obj& jet2, double w) {
  m_j1.Fill(r, jet1, w) ;
  m_j2.Fill(r, jet2, w) ;
  hcsv_mass->Fill(r->HCSV_mass, w) ;
  hcsv_reg_mass->Fill(r->HCSV_reg_mass, w) ;
  h_mass->Fill(r->H_mass, w) ;
  h_reg_mass->Fill(r->H_reg_mass, w) ;
}

void HistH::Write() {
  m_j1.Write() ;
  m_j2.Write() ;
}

//=====BoostedH=====
void HistBoostedH::Book(TString regionName) {
  m_fatJet.Book("BoostedH_" + m_type + "_" + regionName) ;
  m_j1.Book("BoostedH_" + m_type + "_" + regionName) ;
  m_j2.Book("BoostedH_" + m_type + "_" + regionName) ;
  m_j3.Book("BoostedH_" + m_type + "_" + regionName) ;
  h_mass_subjets = new TH1D("BoostedH_mass_subjets_" + m_type + "_" + regionName, "", GLOBC::NBIN_MASS, 0, GLOBC::MAX_MASS) ;
  h_mass_fatJet = new TH1D("BoostedH_mass_fatJet_" + m_type + "_" + regionName, "", GLOBC::NBIN_MASS, 0, GLOBC::MAX_MASS) ;
}

void HistBoostedH::Fill(const BaseTree* r, const Obj& fatJet, const vector<Obj>& jets, double w) {
  m_fatJet.Fill(r, fatJet, w) ;
  if (jets.size() >=1) m_j1.Fill(r, jets[0], w) ;
  if (jets.size() >=2) m_j2.Fill(r, jets[1], w) ;
  if (jets.size() >=3) m_j3.Fill(r, jets[2], w) ;
  
  //===reconstruct from 3 leading jets===
  float mass = -1 ;
  if (jets.size() == 2) {
    mass = Aux::Mass2(jets[0].m_mass, jets[0].m_pt, jets[0].m_eta, jets[0].m_phi, jets[1].m_mass, jets[1].m_pt, jets[1].m_eta, jets[1].m_phi, true) ;   
  }
  if (jets.size() >= 3) {
    mass = Aux::Mass3(jets[0].m_mass, jets[0].m_pt, jets[0].m_eta, jets[0].m_phi, jets[1].m_mass, jets[1].m_pt, jets[1].m_eta, jets[1].m_phi, jets[2].m_mass, jets[2].m_pt, jets[2].m_eta, jets[2].m_phi, true) ;
  }
  h_mass_subjets->Fill(mass, w) ;
  h_mass_fatJet->Fill(fatJet.m_mass, w) ;
}


void HistVH::Book(TString regionName) {
  m_Z.Book(m_type + "_" + regionName) ;
  m_H.Book(m_type + "_" + regionName) ;
}

void HistVH::Fill(const BaseTree* r, const Obj& lep1, const Obj& lep2, const Obj& jet1, const Obj& jet2, double w) {
  m_Z.Fill(r, lep1, lep2, w) ;
  m_H.Fill(r, jet1, jet2, w) ;
}

void HistVH::Write() {
  m_Z.Write() ;
  m_H.Write() ;
}

void HistVBoostedH::Book(TString regionName) {
  m_Z.Book(m_type + "_" + regionName) ;
  m_H.Book(m_type + "_" + regionName) ;
}

void HistVBoostedH::Fill(const BaseTree* r, const Obj& lep1, const Obj& lep2, const Obj& fatJet, const vector<Obj>& jets, double w, double boostedH_mass) {
  m_Z.Fill(r, lep1, lep2, w, boostedH_mass) ;
  m_H.Fill(r, fatJet, jets, w) ;
}


//==function and method of HistBasic=====
void HistBasic::Book(TString regionName) {
  
  TString nameTmp = "Lep1_pt_" + regionName ;
  lep_pt[0] = new TH1D(nameTmp, "", GLOBC::NBIN_PT, 0, GLOBC::MAX_PT) ;
  lep_pt[0]->Sumw2() ;
  nameTmp = "Lep1_eta_" + regionName ;
  lep_eta[0] = new TH1D(nameTmp, "", GLOBC::NBIN_ETA, GLOBC::MIN_ETA, GLOBC::MAX_ETA) ;
  lep_eta[0]->Sumw2() ;
  nameTmp = "Lep1_phi_" + regionName ;
  lep_phi[0] = new TH1D(nameTmp, "", GLOBC::NBIN_PHI, GLOBC::MIN_PHI, GLOBC::MAX_PHI) ;
  lep_phi[0]->Sumw2() ;
  
  nameTmp = "Lep2_pt_" + regionName ;
  lep_pt[1] = new TH1D(nameTmp, "", GLOBC::NBIN_PT, 0, GLOBC::MAX_PT) ;
  lep_pt[1]->Sumw2() ;
  nameTmp = "Lep2_eta_" + regionName ;
  lep_eta[1] = new TH1D(nameTmp, "", GLOBC::NBIN_ETA, GLOBC::MIN_ETA, GLOBC::MAX_ETA) ;
  lep_eta[1]->Sumw2() ;
  nameTmp = "Lep2_phi_" + regionName ;
  lep_phi[1] = new TH1D(nameTmp, "", GLOBC::NBIN_PHI, GLOBC::MIN_PHI, GLOBC::MAX_PHI) ;
  lep_phi[1]->Sumw2() ;
  
  nameTmp = "Zmass_" + regionName ;
  Zmass = new TH1D(nameTmp, "", GLOBC::NBIN_MASS, 0, GLOBC::MAX_MASS) ;
  Zmass->Sumw2() ;
 
  nameTmp = "jet1_pt_all_" + regionName ;
  jet1_pt[0] = new TH1D(nameTmp, "", GLOBC::NBIN_PT, 0, GLOBC::MAX_PT) ;
  jet1_pt[0]->Sumw2() ;
  nameTmp = "jet1_eta_all_" + regionName ;
  jet1_eta[0] = new TH1D(nameTmp, "", GLOBC::NBIN_ETA, GLOBC::MIN_ETA, GLOBC::MAX_ETA) ;
  jet1_eta[0]->Sumw2() ;
  nameTmp = "jet1_phi_all_" + regionName ;
  jet1_phi[0] = new TH1D(nameTmp, "", GLOBC::NBIN_PHI, GLOBC::MIN_PHI, GLOBC::MAX_PHI) ;
  jet1_phi[0]->Sumw2() ;
  nameTmp = "jet1_csv_all_" + regionName ;
  jet1_csv[0]= new TH1D(nameTmp, "", GLOBC::NBIN_CSV, GLOBC::MIN_CSV, GLOBC::MAX_CSV) ;
  jet1_csv[0]->Sumw2() ;
  nameTmp = "jet1_vtxMass_all_" + regionName ;
  jet1_vtxMass[0]= new TH1D(nameTmp, "", GLOBC::NBIN_VTXMASS, GLOBC::MIN_VTXMASS, GLOBC::MAX_VTXMASS) ;
  jet1_vtxMass[0]->Sumw2() ;
  nameTmp = "jet1_vtx3dL_all_" + regionName ;
  jet1_vtx3dL[0]= new TH1D(nameTmp, "", GLOBC::NBIN_VTX3DL, GLOBC::MIN_VTX3DL, GLOBC::MAX_VTX3DL) ;
  jet1_vtx3dL[0]->Sumw2() ;
  nameTmp = "jet1_nTracksSV_all_" + regionName ;
  jet1_nTracksSV[0]= new TH1D(nameTmp, "", GLOBC::NBIN_NTRACKSSV, 0, GLOBC::MAX_NTRACKSSV) ;
  jet1_nTracksSV[0]->Sumw2() ;
  
  nameTmp = "jet1_pt_ljet_" + regionName ;
  jet1_pt[1] = new TH1D(nameTmp, "", GLOBC::NBIN_PT, 0, GLOBC::MAX_PT) ;
  jet1_pt[1]->Sumw2() ;
  nameTmp = "jet1_eta_ljet_" + regionName ;
  jet1_eta[1] = new TH1D(nameTmp, "", GLOBC::NBIN_ETA, GLOBC::MIN_ETA, GLOBC::MAX_ETA) ;
  jet1_eta[1]->Sumw2() ;
  nameTmp = "jet1_phi_ljet_" + regionName ;
  jet1_phi[1] = new TH1D(nameTmp, "", GLOBC::NBIN_PHI, GLOBC::MIN_PHI, GLOBC::MAX_PHI) ;
  jet1_phi[1]->Sumw2() ;
  nameTmp = "jet1_csv_ljet_" + regionName ;
  jet1_csv[1]= new TH1D(nameTmp, "", GLOBC::NBIN_CSV, GLOBC::MIN_CSV, GLOBC::MAX_CSV) ;
  jet1_csv[1]->Sumw2() ;
  nameTmp = "jet1_vtxMass_ljet_" + regionName ;
  jet1_vtxMass[1]= new TH1D(nameTmp, "", GLOBC::NBIN_VTXMASS, GLOBC::MIN_VTXMASS, GLOBC::MAX_VTXMASS) ;
  jet1_vtxMass[1]->Sumw2() ; 
  nameTmp = "jet1_vtx3dL_ljet_" + regionName ;
  jet1_vtx3dL[1]= new TH1D(nameTmp, "", GLOBC::NBIN_VTX3DL, GLOBC::MIN_VTX3DL, GLOBC::MAX_VTX3DL) ;
  jet1_vtx3dL[1]->Sumw2() ;
  nameTmp = "jet1_nTracksSV_ljet_" + regionName ;
  jet1_nTracksSV[1]= new TH1D(nameTmp, "", GLOBC::NBIN_NTRACKSSV, 0, GLOBC::MAX_NTRACKSSV) ;
  jet1_nTracksSV[1]->Sumw2() ;
  
  nameTmp = "jet1_pt_bjet_" + regionName ;
  jet1_pt[2] = new TH1D(nameTmp, "", GLOBC::NBIN_PT, 0, GLOBC::MAX_PT) ;
  jet1_pt[2]->Sumw2() ;
  nameTmp = "jet1_eta_bjet_" + regionName ;
  jet1_eta[2] = new TH1D(nameTmp, "", GLOBC::NBIN_ETA, GLOBC::MIN_ETA, GLOBC::MAX_ETA) ;
  jet1_eta[2]->Sumw2() ;
  nameTmp = "jet1_phi_bjet_" + regionName ;
  jet1_phi[2] = new TH1D(nameTmp, "", GLOBC::NBIN_PHI, GLOBC::MIN_PHI, GLOBC::MAX_PHI) ;
  jet1_phi[2]->Sumw2() ;
  nameTmp = "jet1_csv_bjet_" + regionName ;
  jet1_csv[2]= new TH1D(nameTmp, "", GLOBC::NBIN_CSV, GLOBC::MIN_CSV, GLOBC::MAX_CSV) ;
  jet1_csv[2]->Sumw2() ;
  nameTmp = "jet1_vtxMass_bjet_" + regionName ;
  jet1_vtxMass[2]= new TH1D(nameTmp, "", GLOBC::NBIN_VTXMASS, GLOBC::MIN_VTXMASS, GLOBC::MAX_VTXMASS) ;
  jet1_vtxMass[2]->Sumw2() ; 
  nameTmp = "jet1_vtx3dL_bjet_" + regionName ;
  jet1_vtx3dL[2]= new TH1D(nameTmp, "", GLOBC::NBIN_VTX3DL, GLOBC::MIN_VTX3DL, GLOBC::MAX_VTX3DL) ;
  jet1_vtx3dL[2]->Sumw2() ;
  nameTmp = "jet1_nTracksSV_bjet_" + regionName ;
  jet1_nTracksSV[2]= new TH1D(nameTmp, "", GLOBC::NBIN_NTRACKSSV, 0, GLOBC::MAX_NTRACKSSV) ;
  jet1_nTracksSV[2]->Sumw2() ;
  
  nameTmp = "jet1_pt_cjet_" + regionName ;
  jet1_pt[3] = new TH1D(nameTmp, "", GLOBC::NBIN_PT, 0, GLOBC::MAX_PT) ;
  jet1_pt[3]->Sumw2() ;
  nameTmp = "jet1_eta_cjet_" + regionName ;
  jet1_eta[3] = new TH1D(nameTmp, "", GLOBC::NBIN_ETA, GLOBC::MIN_ETA, GLOBC::MAX_ETA) ;
  jet1_eta[3]->Sumw2() ;
  nameTmp = "jet1_phi_cjet_" + regionName ;
  jet1_phi[3] = new TH1D(nameTmp, "", GLOBC::NBIN_PHI, GLOBC::MIN_PHI, GLOBC::MAX_PHI) ;
  jet1_phi[3]->Sumw2() ;
  nameTmp = "jet1_csv_cjet_" + regionName ;
  jet1_csv[3]= new TH1D(nameTmp, "", GLOBC::NBIN_CSV, GLOBC::MIN_CSV, GLOBC::MAX_CSV) ;
  jet1_csv[3]->Sumw2() ;
  nameTmp = "jet1_vtxMass_cjet_" + regionName ;
  jet1_vtxMass[3]= new TH1D(nameTmp, "", GLOBC::NBIN_VTXMASS, GLOBC::MIN_VTXMASS, GLOBC::MAX_VTXMASS) ;
  jet1_vtxMass[3]->Sumw2() ;
  nameTmp = "jet1_vtx3dL_cjet_" + regionName ;
  jet1_vtx3dL[3]= new TH1D(nameTmp, "", GLOBC::NBIN_VTX3DL, GLOBC::MIN_VTX3DL, GLOBC::MAX_VTX3DL) ;
  jet1_vtx3dL[3]->Sumw2() ;
  nameTmp = "jet1_nTracksSV_cjet_" + regionName ;
  jet1_nTracksSV[3]= new TH1D(nameTmp, "", GLOBC::NBIN_NTRACKSSV, 0, GLOBC::MAX_NTRACKSSV) ;
  jet1_nTracksSV[3]->Sumw2() ;
  
  nameTmp = "jet1_pt_otherJet_" + regionName ;
  jet1_pt[4] = new TH1D(nameTmp, "", GLOBC::NBIN_PT, 0, GLOBC::MAX_PT) ;
  jet1_pt[4]->Sumw2() ;
  nameTmp = "jet1_eta_otherJet_" + regionName ;
  jet1_eta[4] = new TH1D(nameTmp, "", GLOBC::NBIN_ETA, GLOBC::MIN_ETA, GLOBC::MAX_ETA) ;
  jet1_eta[4]->Sumw2() ;
  nameTmp = "jet1_phi_otherJet_" + regionName ;
  jet1_phi[4] = new TH1D(nameTmp, "", GLOBC::NBIN_PHI, GLOBC::MIN_PHI, GLOBC::MAX_PHI) ;
  jet1_phi[4]->Sumw2() ;
  nameTmp = "jet1_csv_otherJet_" + regionName ;
  jet1_csv[4]= new TH1D(nameTmp, "", GLOBC::NBIN_CSV, GLOBC::MIN_CSV, GLOBC::MAX_CSV) ;
  jet1_csv[4]->Sumw2() ;
  nameTmp = "jet1_vtxMass_otherJet_" + regionName ;
  jet1_vtxMass[4]= new TH1D(nameTmp, "", GLOBC::NBIN_VTXMASS, GLOBC::MIN_VTXMASS, GLOBC::MAX_VTXMASS) ;
  jet1_vtxMass[4]->Sumw2() ;
  nameTmp = "jet1_vtx3dL_otherJet_" + regionName ;
  jet1_vtx3dL[4]= new TH1D(nameTmp, "", GLOBC::NBIN_VTX3DL, GLOBC::MIN_VTX3DL, GLOBC::MAX_VTX3DL) ;
  jet1_vtx3dL[4]->Sumw2() ;
  nameTmp = "jet1_nTracksSV_otherJet_" + regionName ;
  jet1_nTracksSV[4]= new TH1D(nameTmp, "", GLOBC::NBIN_NTRACKSSV, 0, GLOBC::MAX_NTRACKSSV) ;
  jet1_nTracksSV[4]->Sumw2() ;

  nameTmp = "jet1_pt_vtxMass_bjet_" + regionName ; //include other jets
  jet1_pt_vtxMass_bjet = new TH2D(nameTmp, "", GLOBC::NBIN_PT, 0, GLOBC::MAX_PT, GLOBC::NBIN_VTXMASS, 0, GLOBC::MAX_VTXMASS) ;
  jet1_pt_vtxMass_bjet->Sumw2() ;

}

void HistBasic::Fill(BaseTree* r, const vector<Obj>& leps, const vector<Obj>& taggedJets, double w) {

  
   for (int i = 0; i < 2 ; i++) {
     lep_pt[i]->Fill(leps[i].m_pt, w) ;
     lep_eta[i]->Fill(leps[i].m_eta, w) ;
     lep_phi[i]->Fill(leps[i].m_phi, w) ;
   }
   
   double ZmassVal = Aux::Mass2(leps[0].m_mass, leps[0].m_pt, leps[0].m_eta, leps[0].m_phi, leps[1].m_mass, leps[1].m_pt, leps[1].m_eta, leps[1].m_phi, true) ;
   Zmass->Fill(ZmassVal, w) ;

  int jetInd = taggedJets[0].m_ind ;
  //int jetType = (r->Jet_flavour)[jetInd] ;
  int jetType = 1 ; 
  
  //==all jet type==
   jet1_pt[0]->Fill(taggedJets[0].m_pt, w) ;
   jet1_eta[0]->Fill(taggedJets[0].m_eta, w) ;
   jet1_phi[0]->Fill(taggedJets[0].m_phi, w) ;
   jet1_csv[0]->Fill((r->Jet_btagCSV)[jetInd], w) ;
   jet1_vtxMass[0]->Fill((r->Jet_vtxMass)[jetInd], w) ;
   //jet1_vtx3dL[0]->Fill((r->Jet_vtx3dL)[jetInd], w) ;
   //jet1_nTracksSV[0]->Fill((r->Jet_numTracksSV)[jetInd], w) ;
      
   if (abs(jetType) == 4) { //c-jet
      jet1_pt[3]->Fill(taggedJets[0].m_pt, w) ;
      jet1_eta[3]->Fill(taggedJets[0].m_eta, w) ;
      jet1_phi[3]->Fill(taggedJets[0].m_phi, w) ;
      jet1_csv[3]->Fill((r->Jet_btagCSV)[jetInd], w) ;
      jet1_vtxMass[3]->Fill((r->Jet_vtxMass)[jetInd], w) ;
      //jet1_vtx3dL[3]->Fill((r->Jet_vtx3dL)[jetInd], w) ;
      //jet1_nTracksSV[3]->Fill((r->Jet_numTracksSV)[jetInd], w) ;
   }

   else if (abs(jetType) == 5) { //b-jet
      jet1_pt[2]->Fill(taggedJets[0].m_pt, w) ;
      jet1_eta[2]->Fill(taggedJets[0].m_eta, w) ;
      jet1_phi[2]->Fill(taggedJets[0].m_phi, w) ;
      jet1_csv[2]->Fill((r->Jet_btagCSV)[jetInd], w) ;
      jet1_vtxMass[2]->Fill((r->Jet_vtxMass)[jetInd], w) ;
      //jet1_vtx3dL[2]->Fill((r->Jet_vtx3dL)[jetInd], w) ;
      //jet1_nTracksSV[2]->Fill((r->Jet_numTracksSV)[jetInd], w) ;
      jet1_pt_vtxMass_bjet->Fill(taggedJets[0].m_pt, (r->Jet_vtxMass)[jetInd], w) ;
   }
   
   else if ((abs(jetType) < 4 && abs(jetType) !=0) || abs(jetType) == 21) { //light-jet
     jet1_pt[1]->Fill(taggedJets[0].m_pt, w) ;
      jet1_eta[1]->Fill(taggedJets[0].m_eta, w) ;
      jet1_phi[1]->Fill(taggedJets[0].m_phi, w) ;
      jet1_csv[1]->Fill((r->Jet_btagCSV)[jetInd], w) ;
      jet1_vtxMass[1]->Fill((r->Jet_vtxMass)[jetInd], w) ;
      //jet1_vtx3dL[1]->Fill((r->Jet_vtx3dL)[jetInd], w) ;
      //jet1_nTracksSV[1]->Fill((r->Jet_numTracksSV)[jetInd], w) ;
   }
   
   else { //all other jet
     jet1_pt[4]->Fill(taggedJets[0].m_pt, w) ;
      jet1_eta[4]->Fill(taggedJets[0].m_eta, w) ;
      jet1_phi[4]->Fill(taggedJets[0].m_phi, w) ;
      jet1_csv[4]->Fill((r->Jet_btagCSV)[jetInd], w) ;
      jet1_vtxMass[4]->Fill((r->Jet_vtxMass)[jetInd], w) ;
      //jet1_vtx3dL[4]->Fill((r->Jet_vtx3dL)[jetInd], w) ;
      //jet1_nTracksSV[4]->Fill((r->Jet_numTracksSV)[jetInd], w) ;
   }

} //end HistBasic::Fill

void HistBasic::Write() {
  for (int i = 0; i < 2; i++) {
    lep_pt[i]->Write() ;
    lep_eta[i]->Write() ;
    lep_phi[i]->Write() ;  	
  }
  Zmass->Write() ;
  for(int i = 0 ; i < 5 ; ++i) {
    jet1_pt[i]->Write() ;
    jet1_eta[i]->Write() ;
    jet1_phi[i]->Write() ;
    jet1_csv[i]->Write() ;
    jet1_vtxMass[i]->Write() ;
    jet1_vtx3dL[i]->Write() ;
  }
}


//------------All utility function--------------
double Aux::DeltaPhi(double phi1, double phi2) {
  double delPhi = fabs(phi1-phi2) ;
  return (delPhi>TMath::Pi())?2*TMath::Pi()-delPhi:delPhi ;
}

double Aux::DeltaPhi1(double phi1, double phi2) {
  double delPhi = phi1 - phi2 ;
  if (delPhi >= TMath::Pi()) delPhi -= TMath::TwoPi() ;
  if (delPhi < -TMath::Pi()) delPhi += TMath::TwoPi() ;
  return delPhi ;
}

double Aux::DeltaEta(double eta1, double eta2) {
  return fabs(eta1-eta2) ;
}

double Aux::DeltaR(double eta1, double phi1, double eta2, double phi2) {
  double delEta = DeltaEta(eta1,eta2) ;
  double delPhi = DeltaPhi(phi1,phi2) ;
  return TMath::Sqrt(delEta*delEta+delPhi*delPhi) ;
}

double Aux::MT(double pTlep, double phiLep, double MET, double METphi) {
  return sqrt(2*pTlep*MET*(1-cos(phiLep-METphi)))/GLOBC::GeV ;
}

double Aux::MT(TLorentzVector ele_tlv, double MET, double METphi) {
  float px = ele_tlv.Px();
  float py = ele_tlv.Py();
  float Et = sqrt(px*px+py*py);
  float MET_x = MET*TMath::Cos(METphi);
  float MET_y = MET*TMath::Sin(METphi);
  float MT2 = (MET+Et)*(MET+Et)-(px+MET_x)*(px+MET_x)-(py+MET_y)*(py+MET_y) ;
  return MT2 < 0.0 ? -sqrt(-MT2)/GLOBC::GeV:sqrt(MT2)/GLOBC::GeV ;
}

double Aux::Mass2(double E1, double pt1, double eta1, double phi1, double E2, double pt2, double eta2, double phi2, bool isMass) {
  TLorentzVector v1 ;
  if (isMass) v1.SetPtEtaPhiM(pt1, eta1, phi1, E1) ;
  else v1.SetPtEtaPhiE(pt1, eta1, phi1, E1) ;
  TLorentzVector v2 ;
  if (isMass) v2.SetPtEtaPhiM(pt2, eta2, phi2, E2) ;
  else v2.SetPtEtaPhiE(pt2, eta2, phi2, E2) ;
  return (v1+v2).M()/GLOBC::GeV ;
}

double Aux::Mass3(double E1, double pt1, double eta1, double phi1, double E2, double pt2, double eta2, double phi2, double E3, double pt3, double eta3, double phi3, bool isMass) {
  TLorentzVector v1 ;
  if (isMass) v1.SetPtEtaPhiM(pt1, eta1, phi1, E1) ;
  else v1.SetPtEtaPhiE(pt1, eta1, phi1, E1) ;
  TLorentzVector v2 ;
  if (isMass) v2.SetPtEtaPhiM(pt2, eta2, phi2, E2) ;
  else v2.SetPtEtaPhiE(pt2, eta2, phi2, E2) ;
  TLorentzVector v3 ;
  if (isMass) v3.SetPtEtaPhiM(pt3, eta3, phi3, E3) ;
  else v3.SetPtEtaPhiE(pt3, eta3, phi3, E3) ;
  return (v1+v2+v3).M()/GLOBC::GeV ;
}

double Aux::Mass4(double E1, double pt1, double eta1, double phi1, double E2, double pt2, double eta2, double phi2, double E3, double pt3, double eta3, double phi3, double E4, double pt4, double eta4, double phi4, bool isMass) {
  TLorentzVector v1 ;
  if (isMass) v1.SetPtEtaPhiM(pt1, eta1, phi1, E1) ;
  else v1.SetPtEtaPhiE(pt1, eta1, phi1, E1) ;
  TLorentzVector v2 ;
  if (isMass) v2.SetPtEtaPhiM(pt2, eta2, phi2, E2) ;
  else v2.SetPtEtaPhiE(pt2, eta2, phi2, E2) ;
  TLorentzVector v3 ;
  if (isMass) v3.SetPtEtaPhiM(pt3, eta3, phi3, E3) ;
  else v3.SetPtEtaPhiE(pt3, eta3, phi3, E3) ;
  TLorentzVector v4 ;
  if (isMass) v4.SetPtEtaPhiM(pt4, eta4, phi4, E4) ;
  else v4.SetPtEtaPhiE(pt4, eta4, phi4, E4) ;
  return (v1+v2+v3+v4).M()/GLOBC::GeV ;
}

double Aux::METrel(double met_et, double met_phi, const vector<Obj>& leps, const vector<Obj>& jets) {
  float dPhiMin = 1000 ;
  for(unsigned int i = 0 ; i < leps.size() ; ++i) {
    float dPhiTmp = Aux::DeltaPhi(met_phi, leps[i].m_phi) ;
    dPhiMin = (dPhiTmp < dPhiMin) ? dPhiTmp:dPhiMin ;
  }
  for(unsigned int i = 0 ; i < jets.size() ; ++i) {
    float dPhiTmp = Aux::DeltaPhi(met_phi, jets[i].m_phi) ;
    dPhiMin = (dPhiTmp < dPhiMin) ? dPhiTmp:dPhiMin ; 
  }
  if (dPhiMin < TMath::Pi()/2) return met_et*sin(dPhiMin) ;
  return met_et ;
}

bool Aux::SortPt(ObjStruct i, ObjStruct j) {
  return (i.pt >= j.pt) ;
}

void Aux::SortPt(std::vector<int>& inds, float pts[]) { //note pt is fixed and cloned from obj_pt
  int indTmp ; 
  for (unsigned i = 0 ; i < inds.size() ; ++i) {
    for (unsigned j = i+1 ; j < inds.size() ; ++j) {
      if (pts[inds[j]] > pts[inds[i]]) {
        indTmp = inds[i] ;
        inds[i] = inds[j] ;
        inds[j] = indTmp ;
        break ;
      }
    }
  }
}

int Aux::findPtBin(float pTin) {
//  for (int iBin = nBin_fR - 1 ; iBin >=0 ; --iBin) {
  //  if (pTin >= pTbin_fR[iBin]) return iBin ;
 // }
  return -1 ;
}

void Aux::printBits(unsigned value, TString label) {
   const int SHIFT = 8 * sizeof( unsigned ) - 1;
   const unsigned MASK = 1 << SHIFT;

   cout << label << ": " ;
   for ( int i = 1; i <= SHIFT + 1; i++ ) 
   {
      cout << ( value & MASK ? '1' : '0' );
      value <<= 1;

      if ( i % 8 == 0 )
         cout << ' ';
   }

   cout << endl;
}

vector<float> Aux::XY(float t, float phi) {
  vector<float> xy ;
  float x = t*cos(phi) ;
  float y = t*sin(phi) ;
  xy.push_back(x) ;
  xy.push_back(y) ;
  return xy ;
}

float dRminMax(double eta1, double phi1, vector<double> eta2s, vector<double> phi2s, bool doFindDrMax) {
  float dRminMaxTmp = 100 ;
  if (doFindDrMax) dRminMaxTmp = -1 ;
  double dRtmp = dRminMaxTmp ;
  for (unsigned i = 0; i < eta2s.size(); i++) {
    double dRtmp = Aux::DeltaR(eta1, phi1, eta2s[i], phi2s[i]) ;
    if (!doFindDrMax && dRtmp < dRminMaxTmp) dRminMaxTmp = dRtmp ;
    if (doFindDrMax && dRtmp > dRminMaxTmp) dRminMaxTmp = dRtmp ;
  }
  return dRminMaxTmp ;
}

float Aux::ResolutionBias_NOM(float eta) 
{
// return 0;//Nominal!
/* if(eta< 1.1) return 0.05;
 if(eta< 2.5) return 0.10;
 if(eta< 5) return 0.30;*/
//new numbers from: https://twiki.cern.ch/twiki/bin/view/CMS/JetResolution
//==These are for 7 TeV==
//   if(eta< 0.5) return 0.052;
//   if(eta< 1.1) return 0.057;
//   if(eta< 1.7) return 0.096;
//   if(eta< 2.3) return 0.134;
//   if(eta< 5) return 0.28;
//==NOTE : update for 8 TeV data (Duong 10-11-2015)
//put here c-1 with c from https://twiki.cern.ch/twiki/bin/view/CMS/JetResolution
   if(eta< 0.5) return 0.079;
   if(eta< 1.1) return 0.099;
   if(eta< 1.7) return 0.121;
   if(eta< 2.3) return 0.208;
   if(eta< 2.8) return 0.254;
   if(eta< 3.2) return 0.395;
   if(eta<5) return 0.056;

   return 0;
}

float Aux::ResolutionBias_UP(float eta) 
{
   if(eta< 0.5) return 0.105;
   if(eta< 1.1) return 0.127;
   if(eta< 1.7) return 0.150;
   if(eta< 2.3) return 0.254;
   if(eta< 2.8) return 0.316;
   if(eta< 3.2) return 0.458;
   if(eta<5) return 0.247;

   return 0;
}

float Aux::ResolutionBias_DOWN(float eta) 
{
   if(eta< 0.5) return 0.053;
   if(eta< 1.1) return 0.071;
   if(eta< 1.7) return 0.092;
   if(eta< 2.3) return 0.162;
   if(eta< 2.8) return 0.192;
   if(eta< 3.2) return 0.332;
   if(eta<5) return 0.865;

   return 0;
}


float Aux::PtWei(float pt) {
 if (pt < 5) return 0 ;
 if (pt < 10) return 0 ;
 if (pt < 15) return 0 ;
 if (pt < 20) return 0 ;
 if (pt < 25) return 0 ;
 if (pt < 30) return 0 ;
 if (pt < 35) return 4.3502 ;
 if (pt < 40) return 2.97646 ;
 if (pt < 45) return 2.33947 ;
 if (pt < 50) return 1.90664 ;
 if (pt < 55) return 1.3614 ;
 if (pt < 60) return 1.12922 ;
 if (pt < 65) return 0.962324 ;
 if (pt < 70) return 0.752649 ;
 if (pt < 75) return 0.658252 ;
 if (pt < 80) return 0.558722 ;
 if (pt < 85) return 0.489828 ;
 if (pt < 90) return 0.446067 ;
 if (pt < 95) return 0.429567 ;
 if (pt < 100) return 0.424134 ;
 if (pt < 105) return 0.361232 ;
 if (pt < 110) return 0.394676 ;
 if (pt < 115) return 0.315694 ;
 if (pt < 120) return 0.280657 ;
 if (pt < 125) return 0.249182 ;
 if (pt < 130) return 0.289278 ;
 if (pt < 135) return 0.218737 ;
 if (pt < 140) return 0.183164 ;
 if (pt < 145) return 0.231088 ;
 if (pt < 150) return 0.234927 ;
 if (pt < 155) return 0.176662 ;
 if (pt < 160) return 0.180819 ;
 if (pt < 165) return 0.315283 ;
 if (pt < 170) return 0.418734 ;
 if (pt < 175) return 0.222627 ;
 if (pt < 180) return 0.148074 ;
 if (pt < 185) return 0.258978 ;
 if (pt < 190) return 0.191237 ;
 if (pt < 195) return 0.299003 ;
 if (pt < 200) return 0.301557 ;
 return 0.3 ; 
}

float Aux::PtWei1(float pt) {

 if (pt < 30 ) return 1. ;
 if (pt < 35 ) return 1.36277 ; 
 if (pt < 40 ) return 1.21806 ; 
 if (pt < 45 ) return 0.842268 ; 
 if (pt < 50 ) return 0.859112 ; 
 if (pt < 55 ) return 0.977557 ; 
 if (pt < 60 ) return 1.08761 ; 
 if (pt < 65 ) return 0.688449 ; 
 if (pt < 70 ) return 1.08358 ; 
 if (pt < 75 ) return 0.875343 ; 
 if (pt < 80 ) return 0.764628 ; 
 if (pt < 85 ) return 0.88034 ; 
 if (pt < 90 ) return 0.781285 ; 
 if (pt < 95 ) return 1.2567 ; 
 if (pt < 100 ) return 0.557137 ; 

 return 1. ;

}

/*
float Aux::PtWeiTtEleMu(float pt) {
 if (pt < 30) return 1. ;
 if (pt < 35) return 58.5016 ; 
 if (pt < 40) return 18.1025 ; 
 if (pt < 45) return 6.68498 ; 
 if (pt < 50) return 3.33635 ; 
 if (pt < 55) return 1.72108 ; 
 if (pt < 60) return 1.2884 ; 
 if (pt < 65) return 1.00769 ; 
 if (pt < 70) return 0.734015 ; 
 if (pt < 75) return 0.625786 ; 
 if (pt < 80) return 0.477181 ; 
 if (pt < 85) return 0.379136 ; 
 if (pt < 90) return 0.363707 ; 
 if (pt < 95) return 0.345769 ; 
 if (pt < 100) return 0.338256 ; 
 if (pt < 105) return 0.286643 ; 
 if (pt < 110) return 0.308798 ; 
 if (pt < 115) return 0.224202 ; 
 if (pt < 120) return 0.23756 ; 
 if (pt < 125) return 0.183759 ; 
 if (pt < 130) return 0.225629 ; 
 if (pt < 135) return 0.173241 ; 
 if (pt < 140) return 0.120543 ; 
 if (pt < 145) return 0.18811 ; 
 if (pt < 150) return 0.202092 ; 
 if (pt < 155) return 0.129677 ; 
 if (pt < 160) return 0.123613 ; 
 if (pt < 165) return 0.278915 ; 
 if (pt < 170) return 0.29906 ; 
 if (pt < 175) return 0.224379 ; 
 if (pt < 180) return 0.0954646 ; 
 if (pt < 185) return 0.200476 ; 
 if (pt < 190) return 0.120071 ; 
 if (pt < 195) return 0.261978 ; 
 if (pt < 200) return 0.217716 ; 
 if (pt < 205) return 0.0991829 ; 
 if (pt < 210) return 0.213044 ; 
 if (pt < 215) return 0.165201 ; 
 if (pt < 220) return 0.312072 ; 
 if (pt < 225) return 0.0685545 ; 
 if (pt < 230) return 0.214243 ; 
 if (pt < 235) return 0.233219 ; 
 if (pt < 240) return 0.178682 ; 
 if (pt < 245) return 0.0912154 ; 
 if (pt < 250) return 0.123449 ; 
 if (pt < 255) return 0.190062 ; 
 if (pt < 260) return 0.305982 ; 
 if (pt < 265) return 0.106945 ; 
 if (pt < 270) return 0.107357 ; 
 if (pt < 275) return 0.189586 ; 
 if (pt < 280) return 0.644638 ; 
 if (pt < 285) return 0.557708 ; 
 if (pt < 300) return 0.173562 ;

 return 1 ;

}
*/

float Aux::PtWeiTtEleMu(float pt) {
 
 if (pt < 10) return 1. ; 
 if (pt < 20) return 1. ; 
 if (pt < 30) return 1. ; 
 if (pt < 40) return 5.32067 ; 
 if (pt < 50) return 2.34623 ; 
 if (pt < 60) return 1.22178 ; 
 if (pt < 70) return 0.747482 ; 
 if (pt < 80) return 0.525389 ; 
 if (pt < 90) return 0.419504 ; 
 if (pt < 100) return 0.39391 ; 
 if (pt < 110) return 0.381344 ; 
 if (pt < 120) return 0.290776 ; 
 if (pt < 130) return 0.260379 ; 
 if (pt < 140) return 0.20604 ; 
 if (pt < 150) return 0.252607 ; 
 if (pt < 160) return 0.20113 ; 
 if (pt < 170) return 0.489302 ; 
 if (pt < 180) return 0.221827 ; 
 if (pt < 190) return 0.284755 ; 
 if (pt < 200) return 0.377387 ; 
 if (pt < 210) return 0.198899 ; 
 if (pt < 220) return 0.341505 ; 
 if (pt < 230) return 0.191681 ; 
 if (pt < 240) return 0.572203 ; 
 if (pt < 250) return 0.534434 ; 
 if (pt < 260) return 0.601912 ; 
 if (pt < 270) return 0.285387 ; 
 if (pt < 280) return 0.783925 ; 
 if (pt < 290) return 0.296673 ; 
 if (pt < 300) return 0.139015 ;

 /*if (pt < 30) return 0. ;
 if (pt < 35) return 5.31193 ; 
 if (pt < 40) return 3.35113 ; 
 if (pt < 45) return 2.61247 ; 
 if (pt < 50) return 1.86988 ; 
 if (pt < 55) return 1.24525 ; 
 if (pt < 60) return 1.0504 ; 
 if (pt < 65) return 0.868239 ; 
 if (pt < 70) return 0.667659 ; 
 if (pt < 75) return 0.579531 ; 
 if (pt < 80) return 0.484729 ; 
 if (pt < 85) return 0.456399 ; 
 if (pt < 90) return 0.40813 ; 
 if (pt < 95) return 0.390596 ; 
 if (pt < 100) return 0.434771 ; 
 if (pt < 105) return 0.352817 ; 
 if (pt < 110) return 0.418702 ; 
 if (pt < 115) return 0.299472 ; 
 if (pt < 120) return 0.333175 ; 
 if (pt < 125) return 0.251565 ; 
 if (pt < 130) return 0.299345 ; 
 if (pt < 135) return 0.250152 ; 
 if (pt < 140) return 0.194008 ; 
 if (pt < 145) return 0.274748 ; 
 if (pt < 150) return 0.331339 ; 
 if (pt < 155) return 0.228453 ; 
 if (pt < 160) return 0.214954 ; 
 if (pt < 165) return 0.579576 ; 
 if (pt < 170) return 0.612533 ; 
 if (pt < 175) return 0.355548 ; 
 if (pt < 180) return 0.18874 ; 
 if (pt < 185) return 0.401815 ; 
 if (pt < 190) return 0.276234 ; 
 if (pt < 195) return 0.457408 ; 
 if (pt < 200) return 0.39472 ; 
 if (pt < 205) return 0.105863 ; 
 if (pt < 210) return 0.437613 ; 
 if (pt < 215) return 0.32305 ; 
 if (pt < 220) return 0.652682 ; 
 if (pt < 225) return 0.124512 ; 
 if (pt < 230) return 0.479194 ; 
 if (pt < 235) return 0.521638 ; 
 if (pt < 240) return 1.02768 ; 
 if (pt < 245) return 0.262311 ; 
 if (pt < 250) return 0.62126 ; 
 if (pt < 255) return 0.409925 ; 
 if (pt < 260) return 0.879924 ; 
 if (pt < 265) return 0.307545 ; 
 if (pt < 270) return 0.308729 ; 
 if (pt < 275) return 0.817797 ;

 if (pt < 40) return 29.4152 ; 
 if (pt < 50) return 4.27814 ; 
 if (pt < 60) return 1.44772 ; 
 if (pt < 70) return 0.797007 ; 
 if (pt < 80) return 0.49349 ; 
 if (pt < 90) return 0.359675 ; 
 if (pt < 100) return 0.327713 ; 
 if (pt < 110) return 0.307274 ; 
 if (pt < 120) return 0.238878 ; 
 if (pt < 130) return 0.205187 ; 
 if (pt < 140) return 0.164585 ; 
 if (pt < 150) return 0.238375 ; 
 if (pt < 160) return 0.151185 ; 
 if (pt < 170) return 0.416172 ; 
 if (pt < 180) return 0.177723 ; 
 if (pt < 190) return 0.226967 ; 
 if (pt < 200) return 0.292369 ; 
 if (pt < 210) return 0.167088 ; 
 if (pt < 220) return 0.251696 ; 
 if (pt < 230) return 0.146913 ; 
 if (pt < 240) return 0.387404 ; 
 if (pt < 250) return 0.250552 ; 
 if (pt < 260) return 0.391395 ; 
 if (pt < 270) return 0.219573 ; 
 if (pt < 280) return 0.690837 ; 
 if (pt < 290) return 0.211684 ; 
 if (pt < 300) return 0.197632 ; 
 if (pt < 310) return 2.09239 ; 
 if (pt < 320) return 1.20929 ; 
 if (pt < 330) return 0.162315 ; 
 if (pt < 370) return 1.03866 ;
 */     

 //if (pt < 30) return 1 ;
 //if (pt < 35) return 83.2686 ; 
 //if (pt < 40) return 16.4904 ; 
 //if (pt < 45) return 6.11569 ; 
 //if (pt < 50) return 3.17561 ; 
 //if (pt < 55) return 1.65775 ; 
 //if (pt < 60) return 1.25486 ; 
 //if (pt < 65) return 0.924762 ; 
 //if (pt < 70) return 0.676711 ; 
 //if (pt < 75) return 0.552859 ; 
 //if (pt < 80) return 0.436236 ; 
 //if (pt < 85) return 0.376828 ; 
 //if (pt < 90) return 0.340867 ; 
 //if (pt < 95) return 0.332689 ; 
 //if (pt < 100) return 0.322256 ; 
 //if (pt < 105) return 0.286084 ; 
 //if (pt < 110) return 0.331125 ; 
 //if (pt < 115) return 0.231146 ; 
 //if (pt < 120) return 0.248741 ; 
 //if (pt < 125) return 0.192694 ; 
 //if (pt < 130) return 0.219735 ; 
 //if (pt < 135) return 0.209171 ; 
 //if (pt < 140) return 0.124492 ; 
 //if (pt < 145) return 0.2215 ; 
 //if (pt < 150) return 0.259289 ; 
 //if (pt < 155) return 0.143442 ; 
 //if (pt < 160) return 0.160864 ; 
 //if (pt < 165) return 0.39019 ; 
 //if (pt < 170) return 0.443728 ; 
 //if (pt < 175) return 0.237876 ; 
 //if (pt < 180) return 0.119574 ; 
 //if (pt < 185) return 0.308848 ; 
 //if (pt < 190) return 0.166445 ; 
 //if (pt < 195) return 0.29831 ; 
 //if (pt < 200) return 0.287053 ; 
 //if (pt < 205) return 0.123205 ; 
 //if (pt < 210) return 0.227428 ; 
 //if (pt < 215) return 0.199869 ; 
 //if (pt < 220) return 0.355352 ; 
 //if (pt < 225) return 0.0851586 ; 
 //if (pt < 230) return 0.243955 ; 
 //if (pt < 235) return 0.371789 ; 
 //if (pt < 240) return 0.406924 ; 
 //if (pt < 245) return 0.103866 ; 
 //if (pt < 250) return 0.983983 ; 
 //if (pt < 255) return 0.32463 ; 
 //if (pt < 260) return 0.418101 ; 
 //if (pt < 265) return 0.202961 ; 
 //if (pt < 270) return 0.244491 ; 
 //if (pt < 275) return 0.323817 ;
 
 return 1 ;

}

float Aux::PtWeiNegTag(float pt) {
 if (pt < 30 ) return 1 ;
 if (pt < 35 ) return 0.877756 ; 
 if (pt < 40 ) return 0.762115 ; 
 if (pt < 45 ) return 1.12389 ; 
 if (pt < 50 ) return 1.32711 ; 
 if (pt < 55 ) return 1.52439 ; 
 if (pt < 60 ) return 2.48683 ; 
 if (pt < 65 ) return 2.36363 ; 
 if (pt < 70 ) return 1.3044 ; 
 return 1 ;
}

float Aux::NtrksSVwei(int nTrksSV) {
	if (nTrksSV < 3 ) return 1.04475 ; 
 if (nTrksSV < 4 ) return 0.766979 ; 
 if (nTrksSV < 5 ) return 1.16903 ; 
 if (nTrksSV < 6 ) return 1.69626 ; 
 if (nTrksSV < 7 ) return 1.01183 ; 
 if (nTrksSV < 8 ) return 0 ; 
	 return 1. ;
}
float Aux::Wei_3dL_JP(float l) {
 if (l < 0) return 1. ; 
 if (l < 1) return 3.1166 ; 
 if (l < 2) return 1.29167 ; 
 if (l < 3) return 0.680413 ; 
 if (l < 4) return 0.365021 ; 
 if (l < 5) return 0.217915 ; 
 if (l < 6) return 0.380649 ; 
 if (l < 7) return 0.102796 ; 
 if (l < 8) return 0.145283 ; 
 if (l < 9) return 0.0300307 ; 
 if (l < 10) return 0.0359344 ; 
 if (l < 11) return 0.126277 ; 
 if (l < 12) return 0.102242 ; 
 if (l < 13) return 0.0861625 ;
 return 1. ;
}
float Aux::Wei_3dL_NegTag(float l) {
   if (l < 0.2 ) return 2.01841 ; 
 if (l < 0.4 ) return 1.51145 ; 
 if (l < 0.6 ) return 1.51133 ; 
 if (l < 0.8 ) return 1.0865 ; 
 if (l < 1 ) return 1.11061 ; 
 if (l < 1.2 ) return 0.674839 ; 
 if (l < 1.4 ) return 0.733251 ; 
 if (l < 1.6 ) return 1.0853 ; 
 if (l < 1.8 ) return 0.57361 ; 
 if (l < 2 ) return 0.781758 ; 
 if (l < 2.2 ) return 1.10494 ; 
 if (l < 2.4 ) return 1.08924 ; 
 if (l < 2.6 ) return 0.966361 ; 
 if (l < 2.8 ) return 0.407493 ; 
 if (l < 3 ) return 0.567651 ; 
 if (l < 3.2 ) return 0.635312 ; 
 if (l < 3.4 ) return 0.737455 ; 
 if (l < 3.6 ) return 0.358787 ; 
 if (l < 3.8 ) return 0.721053 ; 
 if (l < 4 ) return 0.496498 ; 
 if (l < 4.2 ) return 0.787727 ; 
 if (l < 4.4 ) return 0.869944 ; 
 if (l < 4.6 ) return 0.777146 ; 
 if (l < 4.8 ) return 0.209785 ; 
 if (l < 5 ) return 0.535452 ; 
 if (l < 5.2 ) return 2.03152 ; 
 if (l < 5.4 ) return 0.443618 ; 
 if (l < 5.6 ) return 0.355401 ; 
 if (l < 5.8 ) return 1.09546 ; 
 if (l < 6 ) return 0.711523 ;
 return 1. ; 
}

float Aux::PtWeiTtEleMu1(float pt) { //this is used to reweight MC ttbar to data in e-mu sample
  if (pt < 35) return 0.935057 ; 
 if (pt < 40) return 0.960107 ; 
 if (pt < 45) return 0.974094 ; 
 if (pt < 50) return 1.04291 ; 
 if (pt < 55) return 1.02727 ; 
 if (pt < 60) return 0.987754 ; 
 if (pt < 65) return 1.05928 ; 
 if (pt < 70) return 1.10288 ; 
 if (pt < 75) return 1.05084 ; 
 if (pt < 80) return 1.06305 ; 
 if (pt < 85) return 1.06098 ; 
 if (pt < 90) return 0.99862 ; 
 if (pt < 95) return 1.0765 ; 
 if (pt < 100) return 0.94019 ; 
 if (pt < 105) return 0.884834 ; 
 if (pt < 110) return 0.934065 ; 
 if (pt < 115) return 1.058 ; 
 if (pt < 120) return 0.857756 ; 
 if (pt < 125) return 1.07018 ; 
 if (pt < 130) return 0.942179 ; 
 if (pt < 135) return 0.933167 ; 
 if (pt < 140) return 0.944398 ; 
 if (pt < 145) return 1.02009 ; 
 if (pt < 150) return 0.780214 ; 
 if (pt < 155) return 0.889864 ; 
 if (pt < 160) return 0.930977 ; 
 if (pt < 165) return 0.72888 ; 
 if (pt < 170) return 0.843085 ; 
 if (pt < 175) return 0.791974 ; 
 if (pt < 180) return 1.04317 ; 
 if (pt < 185) return 0.784289 ; 
 if (pt < 190) return 0.800223 ; 
 if (pt < 195) return 0.769548 ; 
 if (pt < 200) return 1.00633 ; 
 if (pt < 205) return 1.23527 ; 
 if (pt < 210) return 0.947384 ; 
 if (pt < 215) return 1.47638 ; 
 if (pt < 220) return 0.566084 ; 
 if (pt < 225) return 1.47683 ; 
 if (pt < 230) return 0.974754 ; 
 if (pt < 235) return 0.720175 ; 
 if (pt < 240) return 0.47924 ; 
 if (pt < 245) return 0.344468 ; 
 if (pt < 250) return 0.476621 ; 
 if (pt < 255) return 0.869688 ; 
 if (pt < 260) return 0.913201 ; 
 if (pt < 265) return 1.02615 ; 
 if (pt < 270) return 1.0418 ; 
 if (pt < 275) return 1.00743 ; 
 if (pt < 285) return 1.12084 ; 
 if (pt < 290) return 1.22004 ; 
 if (pt < 295) return 2.21302 ; 
 if (pt < 300) return 0.509762 ; 
 if (pt < 305) return 1.14924 ; 
 if (pt < 310) return 1.04691 ; 
 if (pt < 325) return 4.64746 ; 
 if (pt < 340) return 1.57168 ; 
 if (pt < 355) return 2.14703 ; 
 if (pt < 360) return 3.96095 ; 
 if (pt < 370) return 4.12307 ;
 return 1 ;
}

float Aux::bTagScale(BaseTree* r, vector<int> jetInds, TString jetType) { //jetType = "Jet" or "aJet"
  /*
  float bEff = 0.513013 ;
  float cEff = 0.0583687 ;
  float lEff = 0.00231977 ;
  vector<float> csv ;
  vector<float> scale ;
  vector<int> flavor ;
  
  for (unsigned int i = 0; i < jetInds.size() ; i++) {
    int jetInd = jetInds[i] ;
    if (jetType == "Jet") {
	    csv.push_back(r->Jet_btagCSV[jetInd]) ;
	    scale.push_back(r->Jet_SF_CSVT[jetInd]) ;
	    flavor.push_back(r->Jet_flavour[jetInd]) ;
    }
    if (jetType == "aJet") {
            csv.push_back(r->Jet_btagCSV[jetInd]) ;
	    scale.push_back(r->Jet_SF_CSVT[jetInd]) ;
	    flavor.push_back(r->Jet_flavour[jetInd]) ;
    }
  }
  float pMC = 1 ;
  float pData = 1 ;
  for (unsigned int i = 0; i < jetInds.size() ; i++) {
    float effTmp = bEff ;
    if (abs(flavor[i]) == 4) effTmp = cEff ;
    if (abs(flavor[i]) < 4 || flavor[i] == 21) effTmp = lEff ;
    if (csv[i] > GLOBC::CSVTCUT) {
	    pMC *= effTmp ;
	    pData *= scale[i]*effTmp ;
    }
    else {
	    pMC *= (1-effTmp) ;
	    pData *= (1-scale[i]*effTmp) ;
    }
  }

  //cout << "\n Scale is: " << pData/pMC ;

  return pData/pMC ;
  */ 
  return -1 ;
}

float Aux::weight2(int i){
  if(i<0) return 1;
  if(i>51) return 1;
  return GLOBC::data2[i]/GLOBC::mc2[i];
}

float Aux::weight2_up(int i){
  if(i<0) return 1;
  if(i>51) return 1;
  return GLOBC::data2_P[i]/GLOBC::mc2[i];
}

float Aux::weight2_down(int i){
  if(i<0) return 1;
  if(i>51) return 1;
  return GLOBC::data2_M[i]/GLOBC::mc2[i];
}
