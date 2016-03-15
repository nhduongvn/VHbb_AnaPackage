#ifndef AnaBaseSelector_h
#define  AnaBaseSelector_h
#include <iostream>
#include <sstream>
#include <string>


#include "inc/BaseTree.h"

class TList;

/*
  AnaBaseSelector is a base class for implementing an event processor
  that can be registred to e.g. SUSYTProcessor and su be run over the data
  in parallel with other AnaBaseSelector. The SlaveBegin, Process and
  SlaveTerminate will be called at the same stage of processing as in 
  a TSelector.
*/


class AnaBaseSelector
{
public:
  AnaBaseSelector(): m_IsData(false) {};
  virtual ~AnaBaseSelector() {};

  // These methods are called at the corresponding stage of processing of TSelector
  virtual void SlaveBegin(const BaseTree* r);
  virtual void Process(const BaseTree* r);
  virtual void SlaveTerminate(const BaseTree* r);
  virtual void Terminate(TList* mergedList);
  
  void setIsData(bool isData) { m_IsData = isData;}
  
  bool getIsData() { return(m_IsData);}


protected:
  bool m_IsData;

};
#endif

