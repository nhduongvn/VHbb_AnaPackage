#include "inc/BaseTree.h"
#include "inc/AnaProcessor.h"

AnaProcessor::AnaProcessor(TTree* t)
{
}

void AnaProcessor::Init(TTree *tree)
{
  //BaseTree::Init(tree);
  SetBranches(tree);
}


void AnaProcessor::SetBranches(TTree *tree)
{
  cout << "\n Come to AnaProcessor::SetBranches" << endl;

  if (!tree) return;
  fChain = tree ;
  fChain->SetMakeClass(1);
  fChain->SetBranchStatus("*", 0) ;

  //cout << "\n dataType is: " << m_dataType ;

#ifdef MCFILE
  cout << "\n I am using InitBranches_MC.icc" ;
  #include "inc/InitBranches_MC.icc"
#else
  cout << "\n I am using InitBranches_data.icc" ;
  #include "inc/InitBranches_data.icc"
#endif

}

void AnaProcessor::SetBranchAddress(const char* bname, void* add, TBranch** ptr)
{
  fChain->SetBranchStatus(bname, 1) ;
  fChain->SetBranchAddress(bname, add, ptr);
//  if (!BranchesInitDone) {
//    fBranchesUsed.push_back(ptr);
//  }
}


void AnaProcessor::Begin(TTree *tree)
{
}

void AnaProcessor::SlaveBegin(TTree *tree)
{
  //const char* outputfilename = gSystem->Getenv("OutFileName") ;
  //cout << "\n Outfile is: " << printf("%s", outputfilename) ;
 TNamed* opt = (TNamed*) fInput->FindObject("outputfilename");
 if ( opt ) m_outputfilename = opt->GetTitle(); 
 cout << "\n Outfile is: " << m_outputfilename ;
 m_fProofFile = new TProofOutputFile(m_outputfilename.c_str());
 if (!(m_fFile = m_fProofFile->OpenFile("RECREATE"))) {
   Warning("SlaveBegin", "problems creating file: %s/%s", m_fProofFile->GetDir(), m_fProofFile->GetFileName());
 }

  //opt =  (TNamed*) fInput->FindObject("DATA_TYPE") ;
  //if (opt ) m_dataType = opt->GetTitle() ;

 if ( m_selections.empty() ) buildSelectionList();  
 for ( std::vector<AnaBaseSelector*>::iterator it = m_selections.begin(); it != m_selections.end(); it++  )
  {
    (*it)->SlaveBegin(this);
  }
  
  

}

Bool_t  AnaProcessor::Process(Long64_t entry)
{
  //cout << "\n Entry is " << entry ;
  //cout << "\n Number of selection is " << m_selections.size() ;
  BaseTree::GetEntry(entry);
  for ( std::vector<AnaBaseSelector*>::iterator it = m_selections.begin(); 
	it != m_selections.end(); it++  )
  {
    //cout << "\n I am inside selection loop" ;
    (*it)->Process(this);
  }
  return kTRUE;
}

void AnaProcessor::SlaveTerminate()
{

  for ( std::vector<AnaBaseSelector*>::iterator it = m_selections.begin(); 
	it != m_selections.end(); it++  )
  {
    (*it)->SlaveTerminate(this);
  }

  
  if (m_fFile) {
    m_fFile->cd();
    m_fFile->Write("",TObject::kOverwrite);
    m_fProofFile->Print();
    fOutput->Add(m_fProofFile);
    m_fFile->Close();
  }

}

void AnaProcessor::Terminate()
{
  for ( std::vector<AnaBaseSelector*>::iterator it = m_selections.begin(); 
	it != m_selections.end(); it++  )
  {
    (*it)->Terminate(fOutput);
  }

}

void AnaProcessor::buildSelectionList()
{

  //===this works but causing some confusion of which gDirectory is current===
  //TList* obj_list = (TList*) gDirectory->GetList() ;
  //TIter next(obj_list) ;
  //TIter next1((TList*) obj_list) ;
  //TIter next2(fInput) ;
  //TIter next(next1) ;
  //cout << "\n m_doRunProof is: " << m_doRunProof << std::endl ;
  //if (m_doRunProof) next = next2 ; 
  TIter next(fInput) ; 
  while(TObject* obj = next() ) {
    TString objtype = obj->IsA()->GetName();
    if ( objtype == "AnaConf" )
    {
      const AnaConf* conf = dynamic_cast<AnaConf*>(obj);
      conf->dump();
      if (conf->SelectionName() == "SR0") {
        SR* sel = new SR(0);
        AnaBaseSelector* selection = 0;
        selection = dynamic_cast<AnaBaseSelector*>(sel);
        if ( ! selection ) throw std::invalid_argument("Unknown selection type");
        selection->setIsData(conf->IsData());
        m_selections.push_back(selection) ;
      }
    }
  }
}
