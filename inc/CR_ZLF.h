#ifndef CR_ZLF_h
#define  CR_ZLF_h

#include "TH1D.h"
#include "inc/AnaBaseSelector.h"
#include "inc/Util.h"

using namespace std ;

class CR_ZLF: public AnaBaseSelector
{
public:
  CR_ZLF():AnaBaseSelector() {}
  CR_ZLF(string region, bool isData, double wei);

  virtual ~CR_ZLF();
  virtual void    SlaveBegin(const BaseTree* r);
  virtual void    Process(const BaseTree* r);
  virtual void    SlaveTerminate(const BaseTree* r);
  virtual void    Terminate(TList* mergedList);

 private:

  // histo stuff
  HistVH hist_ZeeH ;
  HistVH hist_ZmmH ; 
  HistVBoostedH hist_ZeeBoostedH_boosted ;
  HistVBoostedH hist_ZmmBoostedH_boosted ;
  
  TH1D* hCutFlow[2] ; //ele, muon
  TH1D* h_lheHT ;

  // Syste for Jets

};
#endif
