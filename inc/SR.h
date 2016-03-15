#ifndef SR_h
#define  SR_h

#include "TH1D.h"
#include "inc/AnaBaseSelector.h"

using namespace std ;

class SR: public AnaBaseSelector
{
public:
  SR(int SR);

  virtual ~SR();
  virtual void    SlaveBegin(const BaseTree* r);
  virtual void    Process(const BaseTree* r);
  virtual void    SlaveTerminate(const BaseTree* r);
  virtual void    Terminate(TList* mergedList);

 private:

  int m_signalRegion ;

  // histo stuff
  TH1D* hJet_pt ;
  TH1D* hJet_selected_pt ;

  // Syste for Jets

};
#endif
