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

const double mc2[52]={4.8551E-07,
		1.74806E-06,
		3.30868E-06,
		1.62972E-05,
		4.95667E-05,
		0.000606966,
		0.003307249,
		0.010340741,
		0.022852296,
		0.041948781,
		0.058609363,
		0.067475755,
		0.072817826,
		0.075931405,
		0.076782504,
		0.076202319,
		0.074502547,
		0.072355135,
		0.069642102,
		0.064920999,
		0.05725576,
		0.047289348,
		0.036528446,
		0.026376131,
		0.017806872,
		0.011249422,
		0.006643385,
		0.003662904,
		0.001899681,
		0.00095614,
		0.00050028,
		0.000297353,
		0.000208717,
		0.000165856,
		0.000139974,
		0.000120481,
		0.000103826,
		8.88868E-05,
		7.53323E-05,
		6.30863E-05,
		5.21356E-05,
		4.24754E-05,
		3.40876E-05,
		2.69282E-05,
		2.09267E-05,
		1.5989E-05,
		4.8551E-06,
		2.42755E-06,
		4.8551E-07,
		2.42755E-07,
		1.21378E-07,
		4.8551E-08};

const double data2[52]={
  4.7027e-05,
  0.000281565,
  0.00028437,
  0.00038727,
  0.000569421,
  0.000952123,
  0.00319069,
  0.0203182,
  0.0699736,
  0.130068,
  0.180077,
  0.198876,
  0.174006,
  0.118772,
  0.06317,
  0.026531,
  0.00902068,
  0.00258006,
  0.000659883,
  0.000164919,
  4.46606e-05,
  1.44451e-05,
  5.83791e-06,
  2.78026e-06,
  1.40517e-06,
  7.0225e-07,
  3.36679e-07,
  1.53294e-07,
  6.60997e-08,
  2.69735e-08,
  1.04154e-08,
  3.80539e-09,
  1.31553e-09,
  4.30311e-10,
  1.3318e-10,
  3.90006e-11,
  1.08063e-11,
  2.83309e-12,
  7.02782e-13,
  1.64952e-13,
  3.66335e-14,
  7.69806e-15,
  1.53064e-15,
  2.87972e-16,
  5.12673e-17,
  8.63513e-18,
  1.37688e-18,
  2.04286e-19,
  3.72485e-20,
  0,
  0,
  0
};


const double data2_P[52]={
  4.02952e-05,
  0.000254497,
  0.000280989,
  0.000335717,
  0.00050839,
  0.000746426,
  0.00186153,
  0.0100804,
  0.0445114,
  0.0982319,
  0.150143,
  0.184585,
  0.184905,
  0.148911,
  0.0954775,
  0.0489179,
  0.020324,
  0.00701388,
  0.00208482,
  0.000564834,
  0.000150948,
  4.35228e-05,
  1.47302e-05,
  6.1078e-06,
  2.96971e-06,
  1.54517e-06,
  8.03286e-07,
  4.03918e-07,
  1.94127e-07,
  8.88486e-08,
  3.86863e-08,
  1.60215e-08,
  6.31045e-09,
  2.36387e-09,
  8.42156e-10,
  2.8534e-10,
  9.19462e-11,
  2.81777e-11,
  8.21254e-12,
  2.27642e-12,
  6.00106e-13,
  1.50456e-13,
  3.58753e-14,
  8.13565e-15,
  1.75469e-15,
  3.59936e-16,
  7.02215e-17,
  1.30278e-17,
  2.29864e-18,
  3.87514e-19,
  7.22359e-20,
  7.82805e-22
};


const double data2_M[52]={
  5.48234e-05,
  0.00031101,
  0.000294382,
  0.000447642,
  0.000648535,
  0.00130872,
  0.00642627,
  0.0386726,
  0.102155,
  0.165772,
  0.205682,
  0.198571,
  0.146521,
  0.0819434,
  0.0350992,
  0.0118095,
  0.00325042,
  0.000781694,
  0.000181477,
  4.58499e-05,
  1.41184e-05,
  5.55293e-06,
  2.58233e-06,
  1.26088e-06,
  6.01759e-07,
  2.73079e-07,
  1.16867e-07,
  4.70691e-08,
  1.78332e-08,
  6.35519e-09,
  2.13024e-09,
  6.71619e-10,
  1.99164e-10,
  5.55507e-11,
  1.45733e-11,
  3.59601e-12,
  8.34591e-13,
  1.82189e-13,
  3.74081e-14,
  7.22453e-15,
  1.31237e-15,
  2.24241e-16,
  3.60383e-17,
  5.44906e-18,
  7.76605e-19,
  1.04021e-19,
  1.24685e-20,
  0,
  0,
  0,
  0,
  0
};

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
  float weight2(int i) ;
  float weight2_up(int i) ;
  float weight2_down(int i) ;

  void GetSubjets(const BaseTree* r, Obj fatJet, vector<Obj>& subJets, float bTagSubjetCuts[], bool invert_csvCut=false, bool gtZero_csv=true) ;

  float Cal_Hmass(vector<Obj> jets) ; 

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
    bool SelectBoostedHjet(const BaseTree* r, double ptCut, double csv_cut = -1, bool invert_csvCut=false, bool gtZero_csv = false) ; //by pass csv_cut as default
    bool SubJetTag(Obj jet1, Obj jet2) ;
    bool SelectFatJet(const BaseTree* r, float ptCut, float dRcut=1.5) ;
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
    void Fill(const BaseTree* r, const Obj& lep1, const Obj& lep2, double w=1., float boostedH_mass=-1) ;
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
    TH1D* h_mass_subjets ; //H_mass from subjets
    TH1D* h_mass_fatJet ; //H_mass from fat jet

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
    void Fill(const BaseTree* r, const Obj& lep1, const Obj& lep2, const Obj& fatJet, const vector<Obj>& jets, double w=1., double boostedH_mass=-1) ;
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
