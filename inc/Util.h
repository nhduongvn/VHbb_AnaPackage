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
    bool SelectJet() const ;
    bool SelectMet(float sig, const vector<Obj>& jets, TH1D* hTest, TH1D*, TH1D*) const ; 
    void Set(TString type, unsigned i, const BaseTree* r, bool doUseAobject=false) ; //type = "ele", "muon", "jet", "met"
    //bool SelectElec(BaseTree* r) ;
    //bool SelectMuon(BaseTree* r) ;
    bool SelectGenLep(BaseTree* r) ;
    //bool SelectJet(BaseTree* r) const ;
    bool SelectGenJet(BaseTree* r) ;
    bool SelectMet(BaseTree* r) ;
    bool SelectTagJet(BaseTree* r, double csv_cut, bool doUseAobject=false) const ;
    void ApplyJECshift(BaseTree* r, TString uncType, bool doUseAobject=false) ;
    void ApplyJER(BaseTree* r, TString uncType, bool doUseAobject=false) ;
} ;

class TagJet: public Obj { //currently don't use
 public:
   double m_csv ; 
   double m_vtxMass ; 
   virtual ~TagJet() {} ;
   TagJet() {} ;
   void Set(unsigned i, BaseTree* r) ; //type = "tagjet"
   bool SelectTagJet(BaseTree* r, double csv_cut) ;
   
} ;

//==contain histogram with basic information of objects==
class HistObj {
public:
	TH1D* pt ;
	TH1D* eta ;
	TH1D* phi ;

	HistObj() {} ;
	virtual ~HistObj() {} ;
	void Book(TString type, TString regionName) ;
  void Fill(BaseTree* r, const Obj& objIn, double w=1.) ;
  void Write() ;
} ;

//==contain histogram of Z candidate==
class HistZ {
  public:
  TH1D* lep_pt[2] ;
  TH1D* lep_eta[2] ;
  TH1D* lep_phi[2] ;
  TH1D* Zmass ;

  HistZ() {} ;
  virtual ~HistZ() {} ;
  void Book(TString regionName) ;
  void Fill(BaseTree* r, const vector<Obj>& leps, double w=1.) ;
  void Write() ;

} ;

//==contain histogram of final state of Z+b-tagged jets
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

class HistTaggedJet { //histogram of tagged jets
  public:
    TH1D* jet1_pt[5] ; //0: all, 1: from light jet, 2: from b-jet, 3: from c-jet, 4: other jets
    TH1D* jet1_eta[5] ;
    TH1D* jet1_phi[5] ;
    TH1D* jet1_csv[5] ;
    TH1D* jet1_vtxMass[5] ;
    TH1D* jet1_tche[5] ;
    TH1D* jet1_tchp[5] ;
    TH1D* jet1_pt_bjet_weighted ; //for testing vtx mass with weighted jet pt in ttbar events
    TH1D* jet1_vtxMass_bjet_weighted ; //for testing vtx mass with weighted jet pt in ttbar events

    HistTaggedJet() {} ;
    virtual ~HistTaggedJet () {} ;
    void Book(TString regionName) ;
    void Fill(BaseTree* r, const Obj& taggedJet, double w=1.) ;
    void Write() ;
} ;

//==contain histogram of efficiency study===
class HistEff { 
public:
	TH1D* jet_pt[4] ; //0: is for c-jet, 1: is for b-jet, 2: is for tagged jet from c, 3: is for tagged jet from b (numerator) 
	TH1D* jet_eta[4] ;
	TH1D* jet_phi[4] ;

	HistEff() {} ;
	virtual ~HistEff () {} ;
	void Book(TString regionName) ;
  void Fill(BaseTree* r, const vector<Obj>& jets, float CSVcut, double w=1.) ;
  void Write() ;
} ;

class HistBasicJet { //histogram of tagged jets
  public:
    TH1D* jet_pt[4] ; //0: all, 1: from light jet, 2: from b-jet, 3: from c-jets
    TH1D* jet_eta[4] ;
    TH1D* jet_vtxMass[4] ;
    TH1D* jet_csv[4] ;
    TH1D* jet_jp[4] ;

    HistBasicJet() {} ;
    virtual ~HistBasicJet () {} ;
    void Book(TString regionName) ;
    void Fill(BaseTree* r, int jetInd, double w=1.) ;
    void Write() ;
} ;

#endif
