#ifndef CR_ZHF_h
#define  CR_ZHF_h

#include "TH1D.h"
#include "inc/AnaBaseSelector.h"
#include "inc/Util.h"

using namespace std ;

class CR_ZHF: public AnaBaseSelector
{
public:
  CR_ZHF():AnaBaseSelector() {}
  CR_ZHF(string region, bool isData, double wei);

  virtual ~CR_ZHF();
  virtual void    SlaveBegin(const BaseTree* r);
  virtual void    Process(const BaseTree* r);
  virtual void    SlaveTerminate(const BaseTree* r);
  virtual void    Terminate(TList* mergedList);

 private:

  //histo stuff
  HistVH hist_ZeeH ;
  HistVH hist_ZmmH ;
  HistVBoostedH hist_ZeeBoostedH_boosted ;
  HistVBoostedH hist_ZmmBoostedH_boosted ;

  // Syste for Jets

};
#endif
