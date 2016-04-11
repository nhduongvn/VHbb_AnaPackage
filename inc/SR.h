#ifndef SR_h
#define  SR_h

#include "TH1D.h"
#include "inc/AnaBaseSelector.h"
#include "inc/Util.h"

using namespace std ;

class SR: public AnaBaseSelector
{
public:
  SR() : AnaBaseSelector() {}
  SR(string region, bool isData, double wei) ;

  virtual ~SR();
  virtual void    SlaveBegin(const BaseTree* r);
  virtual void    Process(const BaseTree* r);
  virtual void    SlaveTerminate(const BaseTree* r);
  virtual void    Terminate(TList* mergedList); //virtual if overriden on derived class, the function of derived class will called if object of derived class was used ("late" binding or run-time binding), otherwise use base class function ("early" binding or compiler binding 
  
  void FillVH(const BaseTree* r, const vector<Obj>& vLeps, const vector<Obj>& hJets, HistVH& hist_ZeeH_lowVpt, HistVH& hist_ZeeH_highVpt, HistVH& hist_ZeeH_noVptCut, HistVH& hist_ZmmH_lowVpt, HistVH& hist_ZmmH_highVpt, HistVH& hist_ZmmH_noVptCut) ;

  void FillV_boostedH(const BaseTree* r, const vector<Obj>& vLeps, const Obj& fatJet, const vector<Obj>& boostedHjets_matched, HistVBoostedH& hist_ZeeBoostedH_highVpt, HistVBoostedH& hist_ZeeBoostedH_noVptCut, HistVBoostedH& hist_ZmmBoostedH_highVpt, HistVBoostedH& hist_ZmmBoostedH_noVptCut) ; 

 private:

  // histo stuff
  HistVH hist_ZeeH_lowVpt_dijet ;
  HistVH hist_ZmmH_lowVpt_dijet ;
  HistVH hist_ZeeH_highVpt_dijet ;
  HistVH hist_ZmmH_highVpt_dijet ;
  HistVH hist_ZeeH_noVptCut_dijet ;
  HistVH hist_ZmmH_noVptCut_dijet ;

  HistVH hist_ZeeH_lowVpt_dijet_boosted ;
  HistVH hist_ZmmH_lowVpt_dijet_boosted ;
  HistVH hist_ZeeH_highVpt_dijet_boosted ;
  HistVH hist_ZmmH_highVpt_dijet_boosted ;
  HistVH hist_ZeeH_noVptCut_dijet_boosted ;
  HistVH hist_ZmmH_noVptCut_dijet_boosted ;
  
  HistVH hist_ZeeH_lowVpt_dijet_only;
  HistVH hist_ZmmH_lowVpt_dijet_only;
  HistVH hist_ZeeH_highVpt_dijet_only;
  HistVH hist_ZmmH_highVpt_dijet_only;
  HistVH hist_ZeeH_noVptCut_dijet_only;
  HistVH hist_ZmmH_noVptCut_dijet_only;

  HistVBoostedH hist_ZeeBoostedH_noVptCut_boosted ;
  HistVBoostedH hist_ZmmBoostedH_noVptCut_boosted ;
  HistVBoostedH hist_ZeeBoostedH_highVpt_boosted ;
  HistVBoostedH hist_ZmmBoostedH_highVpt_boosted ;

  HistVBoostedH hist_ZeeBoostedH_noVptCut_dijet_boosted ;
  HistVBoostedH hist_ZmmBoostedH_noVptCut_dijet_boosted ;
  HistVBoostedH hist_ZeeBoostedH_highVpt_dijet_boosted ;
  HistVBoostedH hist_ZmmBoostedH_highVpt_dijet_boosted ;

  HistVBoostedH hist_ZeeBoostedH_noVptCut_boosted_only ;
  HistVBoostedH hist_ZmmBoostedH_noVptCut_boosted_only ;
  HistVBoostedH hist_ZeeBoostedH_highVpt_boosted_only ;
  HistVBoostedH hist_ZmmBoostedH_highVpt_boosted_only ;



  TH1D* hDr ;
  TH1D* hDr_test ;
  TH1D* hVpt_1 ;
  TH1D* hVpt_2 ;
  TH1D* hVpt_3 ;
  TH1D* hVpt_4 ;
  TH1D* hVpt_5 ;
  TH1D* hVpt_6 ;
  TH1D* h_nFatJet ;
  TH1D* hMassTest ;
  

  // Syste for Jets

};
#endif
