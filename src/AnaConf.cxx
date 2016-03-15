#include "inc/AnaConf.h"

/*
  A class that describes the configuration of the processor to be run
  with SUSYTConfProcessor. Names are predefined see SUSYTConfProcessor
  for details.

  Instances of this class need to be put in the input list for 
  SUSYTConfProcessor so that the corresponding processor are run.
*/


void AnaConf::dump() const
  {
    using std::cout;
    using std::endl;
    cout << "-------------------- Configuration  --------------------" << endl;
    cout << "- Name               " <<  this->GetName() << endl;
    cout << "- is data            " <<  m_IsData << endl;
    cout << "--------------------------------------------------------" << endl;
  }

