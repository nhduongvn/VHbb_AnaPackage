#ifndef CR_TT_h
#define  CR_TT_h

#include "TH1D.h"
#include "inc/AnaBaseSelector.h"
#include "inc/Util.h"

using namespace std ;

class CR_TT: public AnaBaseSelector
{
public:
  CR_TT():AnaBaseSelector() {}
  CR_TT(string region, bool isData, double wei);

  virtual ~CR_TT();
  virtual void    SlaveBegin(const BaseTree* r);
  virtual void    Process(const BaseTree* r);
  virtual void    SlaveTerminate(const BaseTree* r);
  virtual void    Terminate(TList* mergedList);

 private:

  // histo stuff
  HistVH hist_ZeeH ;
  HistVH hist_ZmmH ;

  // Syste for Jets

};
#endif
