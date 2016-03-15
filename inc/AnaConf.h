#ifndef AnaConf_h
#define AnaConf_h

#include <string>
#include <vector>
#include <iostream>

#include "TNamed.h"

/*
  A class that describes the configuration of the processor to be run
  with SUSYTConfProcessor. Names are predefined see SUSYTConfProcessor
  for details.

  Instances of this class need to be put in the input list for 
  SUSYTConfProcessor so that the corresponding processor are run.
*/


class AnaConf: public TNamed
{

public:
  AnaConf(const char * name = "None"):
    TNamed(name,""),
    m_IsData(false) 
  {
  }

  virtual ~AnaConf(){}

  void setIsData(bool isData) { m_IsData = isData;}
  
  const std::string SelectionName() const { return std::string(this->GetName()); }
  bool IsData() const { return m_IsData; }
  void dump() const ;

  ClassDef(AnaConf,1)

private:
  bool m_IsData;

};



#endif
