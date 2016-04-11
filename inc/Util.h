#ifndef UTIL_h
#define UTIL_h
#include <iostream>
#include "TLorentzVector.h"
#include "TVector3.h"
#include <algorithm>
#include "TString.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"
#include "TString.h"
#include "TSelector.h"
#include "inc/BaseTree.h"
#include <vector>

using namespace std ;

namespace GLOBC {

const double GeV = 1. ; //already defined in FudgeMCTool
const Double_t WMass = 80.4*GeV;
const Double_t PHO_ISOCUT = 4 ; 
const Double_t MZ = 90.1*GeV ;
const Double_t JET_PT = 20 ;
const Double_t HJET_PT = 20 ;

const int NBIN_ETA = 600 ;
const float MIN_ETA = -3 ;
const float MAX_ETA = 3 ;
const int NBIN_PHI = 600 ;
const float MIN_PHI = -TMath::Pi() ;
const float MAX_PHI = TMath::Pi() ;
const int NBIN_PT = 500 ;
const float MAX_PT = 500 ;

const int NBIN_MASS = 1000 ;
const float MAX_MASS = 1000 ;

const int NBIN_CSV = 100 ;
const float MIN_CSV = 0 ;
const float MAX_CSV = 1 ;

const int NBIN_VTXMASS= 100 ;
const float MIN_VTXMASS = 0 ;
const float MAX_VTXMASS = 10 ;

const float CSVTCUT = 0.898 ;
const float CSVMCUT = 0.679 ;  

const int NBIN_TC = 400 ;
const float MAX_TC = 150 ;
const float MIN_TC = -50 ;

const int NBIN_NTRACKSSV = 10 ;
const float MAX_NTRACKSSV = 10 ;

const int NBIN_VTX3DL = 250 ;
const float MIN_VTX3DL = -5 ;
const float MAX_VTX3DL = 20 ;

const int NBIN_VTX3DLSIG = 250 ;
const float MIN_VTX3DLSIG = -5 ;
const float MAX_VTX3DLSIG = 20 ;

const int NBIN_JP = 200;
const float MAX_JP = 2 ;

const int NBIN_MT = 200 ;
const float MAX_MT = 200 ;

}


class Obj ;

//---------define struct-------
struct ObjStruct {
  int ind ;
  float eta ;
  float phi ;
  float e ;
  float pt ;
  int cat ; //1 tight+iso, 2 tight not iso, 3: not tight not iso, 4: not tight iso 
  float caloIso ;
  float trackIso ;
  //| 4 | 3 |
  //---------
  //|1  | 2 |
} ;

namespace Aux {
  double DeltaPhi(double, double) ;
  double DeltaPhi1(double, double) ;
  double DeltaEta(double, double) ;
  double DeltaR(double, double, double, double) ;
  double MT(double pTlep, double phiLep, double MET, double METphi) ;
  double MT(TLorentzVector ele_tlv, double MET, double METphi) ;
  double Mass2(double E1, double pt1, double eta1, double phi1, double E2, double pt2, double eta2, double phi2, bool isMass=0) ; 
  double Mass3(double E1, double pt1, double eta1, double phi1, double E2, double pt2, double eta2, double phi2, double E3, double pt3, double eta3, double phi3, bool isMass=0) ; 
  double Mass4(double E1, double pt1, double eta1, double phi1, double E2, double pt2, double eta2, double phi2, double E3, double pt3, double eta3, double phi3, double E4, double pt4, double eta4, double phi4, bool isMass=0) ;
  double METrel(double met_et, double met_phi, const vector<Obj>& leps, const vector<Obj>& jets) ;
  bool SortPt(ObjStruct i, ObjStruct j) ; 
  void SortPt(std::vector<int>& inds, float pts[]) ;
  int findPtBin(float pTin) ;
  void printBits(unsigned value, TString label) ;
  vector<float> XY(float t, float phi) ;
  float dRmin(double eta1, double phi1, vector<double> eta2s, vector<double> phi2s, bool doFindDrMax=false) ;
  float ResolutionBias_NOM(float eta) ; 
  float ResolutionBias_UP(float eta) ; 
  float ResolutionBias_DOWN(float eta) ; 
  float PtWei(float pt) ;
  float PtWei1(float pt) ;
  float PtWeiTtEleMu(float pt) ;
  float PtWeiTtEleMu1(float pt) ;
  float PtWeiNegTag(float pt) ;
  float NtrksSVwei(int nTrksSV) ; 
  float Wei_3dL_NegTag(float l) ;
  float Wei_3dL_JP(float l) ;

  float bTagScale(BaseTree* r, vector<int> jetInds, TString jetType = "aJet") ;

} 


class Obj {
  public:
    int m_ind ;
    TString m_type ;
    double m_e ;
    double m_pt ;
    double m_eta ;
    double m_phi ;
    double m_mass ;
    int m_charge ;
    int m_softLep_type ; //for jet
    virtual ~Obj() {} ;
    Obj() {} ;
    bool operator > (const Obj&) const;
    bool SelectElec() ; 
    bool SelectMuon() ; 
    bool SelectLepton(const BaseTree* r) ;
    bool SelectJet(float ptCut) const ;
    bool SelectMet(float sig, const vector<Obj>& jets, TH1D* hTest, TH1D*, TH1D*) const ; 
    void Set(TString type, unsigned i, const BaseTree* r, bool doUseVobject=false) ; //type = "ele", "muon", "jet", "met"
    //bool SelectElec(BaseTree* r) ;
    //bool SelectMuon(BaseTree* r) ;
    bool SelectGenLep(BaseTree* r) ;
    //bool SelectJet(BaseTree* r) const ;
    bool SelectGenJet(BaseTree* r) ;
    bool SelectMet(BaseTree* r) ;
    bool SelectTagJet(const BaseTree* r, double ptCut, double csv_cut=0, bool invert_csvCut = false, bool gtZero_csv = false) ;
    bool SelectBoostedHjet(const BaseTree* r, double ptCut, double csv_cut=0, bool invert_csvCut=false, bool gtZero_csv = false) ;
    bool SubJetTag(Obj jet1, Obj jet2) ;
    void ApplyJECshift(BaseTree* r, TString uncType, bool doUseAobject=false) ;
    void ApplyJER(BaseTree* r, TString uncType, bool doUseAobject=false) ;
} ;

//==contain histogram with basic information of objects==
class HistObj {
public:
	TString m_type ; //jet1, jet2, ele1, ele2, muon1, muon2 ...
  TH1D* pt ;
	TH1D* eta ;
	TH1D* phi ;

	HistObj() {m_type = "unknown" ; } ;
	HistObj(TString type) : m_type(type) {} ;
	virtual ~HistObj() {} ;
	void Book(TString regionName) ;
  void Fill(const BaseTree* r, const Obj& objIn, double w=1.) ;
  void Write() ;
} ;

class HistJet : public HistObj {
  public:
    TH1D* csv ;
    
    HistJet() {} ;
    HistJet(TString type) : HistObj(type) {} ;
	  virtual ~HistJet() {} ;
    void Book(TString regionName) ;
    void Fill(const BaseTree* r, const Obj& objIn, double w=1.) ;
    void Write() {} ; 
} ;

//class HistBoostedJet : public HistObj {
  //public:
    //TH1D* csv ;
    
    //HistBoostedJet() {} ;
    //HistBoostedJet(TString type) : HistObj(type) {} ;
	  //virtual ~HistBoostedJet() {} ;
    //void Book(TString regionName) ;
    //void Fill(const BaseTree* r, const Obj& objIn, double w=1.) ;
    //void Write() ;
//} ;


//==Contain histograms of Z==========================
class HistZ {
  public:
    TString m_type ;
    HistObj m_l1 ;
    HistObj m_l2 ; 
    TH1D* vpt ;
    TH1D* vpt_Hmass_cut ;

    HistZ() {} ;

    void set(TString type) { //Zee or Zmm

      m_type = type ;
      if (m_type == "Zee") {
        m_l1.m_type = "ele1" ;
        m_l2.m_type = "ele2" ;
      }
      if (m_type == "Zmm") {
        m_l1.m_type = "muon1" ;
        m_l2.m_type = "muon2" ;
      } 

    } ;
    
    virtual ~HistZ() {} ;
    void Book(TString regionName) ;
    void Fill(const BaseTree* r, const Obj& lep1, const Obj& lep2, double w=1.) ;
    void Write() ;
} ;

class HistH {
  public:
    HistJet m_j1 ;
    HistJet m_j2 ;
    TH1D* hcsv_mass ;
    TH1D* hcsv_reg_mass ;
    TH1D* h_mass ;
    TH1D* h_reg_mass ;

    HistH() {} ;

    void set() {m_j1.m_type = "jet1" ; m_j2.m_type = "jet2" ;} ; 

    virtual ~HistH() {} ;
    void Book(TString regionName) ;
    void Fill(const BaseTree* r, const Obj& jet1, const Obj& jet2, double w=1.) ;
    void Write() ;
} ;

class HistVH {
  public:
    TString m_type ; //ZeeH, ZmmH, WH
    HistZ m_Z ;
    HistH m_H ;

    HistVH() {} ;
    void set(TString type) { //type = ZeeH or ZmmH
      m_type = type ;
      if (type.Contains("ZeeH")) m_Z.set("Zee") ;
      if (type.Contains("ZmmH")) m_Z.set("Zmm") ;
      m_H.set() ;
    } ; 
    virtual ~HistVH() {} ;
    void Book(TString regionName) ;
    void Fill(const BaseTree* r, const Obj& lep1, const Obj& lep2, const Obj& jet1, const Obj& jet2, double w=1.) ;
    void Write() ;
} ;

class HistBoostedH {
  public:
    HistJet m_fatJet ;
    HistJet m_j1 ; //subjets
    HistJet m_j2 ;
    HistJet m_j3 ;
    TString m_type ;
    TH1D* h_mass ;

    HistBoostedH() {} ;

    void set(TString type) {m_type = type ; m_fatJet.m_type = "fatJet_" + type ; m_j1.m_type = "jet1_" + type ; m_j2.m_type = "jet2_" + type ; m_j3.m_type = "jet3_" + type ; } ; 

    virtual ~HistBoostedH() {} ;
    void Book(TString regionName) ;
    void Fill(const BaseTree* r, const Obj& fatJet, const vector<Obj>& jets, double w=1.) ;
    void Write() {} ;
} ;

class HistVBoostedH {
  public:
    TString m_type ; //ZeeBoostedH_subjetCA15pruned, ZmmBoostedH_subjetCA15pruned, WH
    HistZ m_Z ;
    HistBoostedH m_H ;

    HistVBoostedH() {} ;
    void set(TString type) { //type = ZeeBoostedH_subjetCA15pruned or ZmmBoostedH_subjetCA15pruned
      m_type = type ;
      if (type.Contains("ZeeBoostedH")) m_Z.set("Zee") ;
      else if (type.Contains("ZmmBoostedH")) m_Z.set("Zmm") ;
      else {
        cout << "\n Warning: unknown Z type in HistVBoostedH class" ;
        m_Z.set("unknown") ;
      }
      
      if (type.Contains("subjetCA15pruned")) m_H.set("subjetCA15pruned") ;
      else {
        cout << "\n Warning: unknown H type in HistVBoostedH class" ;
        m_H.set("unknown") ;
      }

    } ; 
    virtual ~HistVBoostedH() {} ;
    void Book(TString regionName) ;
    void Fill(const BaseTree* r, const Obj& lep1, const Obj& lep2, const Obj& fatJet, const vector<Obj>& jets, double w=1.) ;
    void Write() {} ;
} ;


//==contain histograms for BDT=======================
class HistBasic { //===TODO add Njet distribution and 
public:
	TH1D* lep_pt[2] ;
	TH1D* lep_eta[2] ;
	TH1D* lep_phi[2] ;
        TH1D* Zmass ;
        TH1D* jet1_pt[5] ; //leading tagged jets, 0: all, 1: from light jet, 2: from b-jet, 3: from c-jet, 4: other jets
        TH1D* jet1_eta[5] ;
        TH1D* jet1_phi[5] ;
        TH1D* jet1_csv[5] ;
        TH1D* jet1_vtxMass[5] ;
        TH1D* jet1_nTracksSV[5] ;
        TH1D* jet1_vtx3dL[5] ;
        TH1D* jet1_tche[5] ;
        TH1D* jet1_tchp[5] ;
        TH1D* jet1_vtxMass_negtche[5] ;
	TH2D* jet1_pt_vtxMass_bjet ;

	HistBasic() {} ;
	virtual ~HistBasic() {} ;
	void Book(TString regionName) ;
  void Fill(BaseTree* r, const vector<Obj>& leps, const vector<Obj>& taggedJets, double w=1.) ;
  void Write() ;
} ;


#endif
