#ifndef AnaProcessor_h
#define AnaProcessor_h

#include "TSystem.h"
#include "inc/BaseTree.h"
#include "inc/AnaBaseSelector.h"
#include "TProofOutputFile.h"
#include "inc/AnaConf.h"
#include "inc/SR.h"
#include "inc/CR_ZLF.h"
#include "inc/CR_ZHF.h"
#include "inc/CR_TT.h"
#include <vector>

/*
  AnaProcessor is essentially a TSelector that will run through the
  data and execute the registered AnaBaseSelector in SlaveBegin, Process
  and SlaveTerminate and thus allows to run several selection in one
  pass over the data.
 */
using namespace std ;
class AnaProcessor: public BaseTree
{
public:
  AnaProcessor(TTree* t =0 );
  virtual ~AnaProcessor() {};
  virtual void    Begin(TTree *tree);
  virtual void    SlaveBegin(TTree *tree);
  virtual void    Init(TTree *tree);
  virtual Bool_t  Process(Long64_t entry);
  virtual void    SlaveTerminate();
  virtual void    Terminate();
  virtual void    SetBranches(TTree* tree) ;
  virtual void    SetBranchAddress(const char* bname, void* add, TBranch** ptr) ;
  

  void addSelection(AnaBaseSelector* sel) { m_selections.push_back(sel); }
  void set_LHE_HTcut(float lheHTcut) {m_lheHTcut = lheHTcut ; }

  //bool m_doRunProof ;
  string m_outputfilename ;
  //string m_dataType ;

  ClassDef(AnaProcessor,0);
private:
  void buildSelectionList() ;
  std::vector<AnaBaseSelector*> m_selections ;
  TProofOutputFile *m_fProofFile ;
  TFile* m_fFile ;
  TH1D* hProcessedEvent ;
  TH1D* hGenWeight ;
  TH1D* h_lheHT ;

  float m_lheHTcut ;
};

#endif
