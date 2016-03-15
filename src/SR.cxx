#include "inc/SR.h"
#include "inc/Util.h"
#include <iostream>
#include <sstream>
#include <string>


SR::SR(int SR): 
  AnaBaseSelector() 
{
  std::stringstream s;
  s << "SR" << SR; 
  std::string sSR = s.str();
  
  m_signalRegion = SR; 
  
}

SR::~SR()
{
}


void SR::SlaveBegin(const BaseTree* r) 
{
  
  std::stringstream s;
  s << "SR" << m_signalRegion; 
  std::string sSR = s.str();
  hJet_pt = new TH1D("Jet_pt_SR", "", 1000, 0, 1000) ;
  hJet_selected_pt = new TH1D("Jet_selected_pt_SR", "", 1000, 0, 1000) ;
};

void SR::Process(const BaseTree* r)
{
  //cout << "\n======================" ;
  //cout << "\n " << r->EVENT_run << " " << r->EVENT_event ;
  //cout << "\n Jet are: " ;
  Obj objTmp ;
  std::vector<Obj> selJets ;
  for (int iJet = 0 ; iJet < r->nJet ; ++iJet) {
    cout << "\n " << iJet << "  " << r->Jet_pt[iJet] << "  " << r->Jet_eta[iJet] << "  " << r->Jet_phi[iJet] ;
    hJet_pt->Fill(r->Jet_pt[iJet]) ;
    objTmp.Set("jet", iJet, r) ;
    if (objTmp.SelectJet()) {
      selJets.push_back(objTmp) ; 
      hJet_selected_pt->Fill(r->Jet_pt[iJet]) ;
    }
  }
  //cout << endl ;

}

void SR::SlaveTerminate(const BaseTree* r) 
{  
};

void SR::Terminate(TList* mergedList) 
{
}
