/***************************************************************************
 *            main.cxx
 *
 *  Fri Sep 21 15:05:23 2007
 *  Copyright  2007  chekanov
 *  chekanov@mail.desy.de
 ****************************************************************************/



#include<iostream>
#include<fstream>
#include<stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <vector>

#include <TROOT.h>
#include <TSystem.h>
#include <TEnv.h>
#include <TTree.h>
#include <TChain.h>
#include <TFile.h>
#include "TObject.h"
#include "TMath.h"
#include "TRandom.h"
#include "TThread.h"
#include "TChain.h"
#include "TProof.h"
#include "TProofLog.h"
#include "TProofMgr.h"
#include "TFileCollection.h"
#include "TString.h"
#include "TSystem.h"
#include "TString.h"

#include "inc/AnaProcessor.h"
#include "inc/SR.h"
#include "inc/AnaConf.h"

//#include "Global.h" 

using namespace std;


//Global glob;


int main(int argc, char **argv)
{


   // user global variables

   int nworkers=8;
   Int_t cacheSize = 10*1024*1024;
   const char *treeName = "tree";
   const char* server = "";

   TString dataTypeIn = argv[1] ;  //DATA MCFILE
   dataTypeIn.ToUpper() ;
   TString runMode = argv[2] ; //ProofLite, NoProof
   runMode.ToUpper() ;
   TString infiles_list = argv[3] ;
   TString out_file_name = argv[4] ;
   TString uncertainty = argv[5] ;
   uncertainty.ToUpper() ;

   //===Print out inputs===
  cout << "\n================= INPUTS ==================================" ;
  cout << "\n Data type:        " << dataTypeIn ;
  cout << "\n Run mode:         " << runMode ;
  cout << "\n File list:        " << infiles_list ;
  cout << "\n Output file name: " << out_file_name ;
  cout << "\n Uncertainty:      " << uncertainty ;
  cout << "\n===========================================================" ;
  
  bool runProof=false;
  if (runMode == "PROOFLITE") runProof = true ;

  const char* workDir(gSystem->WorkingDirectory());
  // get dictinary for vector
  gROOT->ProcessLine("#include <vector>");

  //gSystem->Load(TString(workDir)+"/lib/libMyLib.so");
  //gSystem->AddIncludePath("-I./lib_ext/");
  //gSystem->Setenv("WORK_DIR",TString(workDir));
  //cout << "Working directory = " << TString(workDir) << endl;


  // in case of large outputs, keep in in tmp
  //gEnv->SetValue( "ProofServ.Sandbox", "/uscmst1b_scratch/lpc1/lpctrig/duong/Output_proof"); -->set in $HOME/.rootrc

  MemInfo_t memInfo;
  gSystem->GetMemInfo(&memInfo);
  cout << " Mem Total = " << memInfo.fMemTotal << endl; 
  cout << " Mem Used = " << memInfo.fMemUsed << endl; 
  cout << " Mem Swapped = " << memInfo.fSwapUsed << endl; 
  int mStart=(int)memInfo.fMemUsed;


   //glob.getIni();
   // read list of ntuples
   //glob.getNtuples();
    // print cuts
   //glob.print_init();
   //const int Nfiles = glob.ntup.size();
   //cout << " -> No of files to read:" << Nfiles << endl;
   //nworkers=glob.Ncores;
   //runProof=glob.IsProof;

    TChain chain(treeName);
    TFileCollection fc("fc","list of input root files",infiles_list);
    chain.AddFileInfoList(fc.GetList());
    //int Nfiles = 10 ;
    //for (int i = 0; i < Nfiles; i++) {
      // float donefiles= (float)i / (float)Nfiles;
       //cout << "\nfile to read:" << glob.ntup[i] << endl;
       //chain.Add(glob.ntup[i].c_str(),-1); // do not add non-recovebale
    //}


   TProof* proof=0;
   TProof::AddEnvVar("PROOF_NWORKERS",TString::Format("%d",nworkers));

    if (runProof) {
      TString str_server(server);
      if (str_server.Length() == 0) {
        if (nworkers>0) {
          str_server = TString::Format("workers=%d",nworkers);
        }
      }

      proof = TProof::Open(str_server.Data());
      //proof= TProof::Open("lite://");
      //proof->Load("inc/AnaConf.h+",kTRUE);
      chain.SetProof();
      TString tmpStr = "gSystem->Load(\""+TString(workDir)+"/lib/libMyLib.so\") ;" ;
      proof->Exec(tmpStr);  //without this no event loop
      TProof::AddEnvVar("WORK_DIR",TString(workDir)); //need this otherwise crash, not sure why
//    proof->SetLogLevel(7); // to debug 

      proof->Print();
//    proof->Print("a"); // more details

    } else {
    // chain->SetParallelUnzip(); // known broken
      chain.SetCacheSize(cacheSize);
      chain.SetCacheLearnEntries(5);
    }


  cout << "Process..." << endl;
  TString xproof="0";
  if (runProof) xproof="1";  
  TString xdebug="0";
  
  
  AnaConf sr_conf("SR0");
  if (dataTypeIn == "DATA") sr_conf.setIsData("true");
  if (dataTypeIn == "MCFILE") sr_conf.setIsData("false");
  
  TNamed* fOutName = new TNamed("outputfilename", out_file_name.Data()) ;
  //TNamed* dataType = new TNamed("DATA_TYPE", dataTypeIn) ;
  TList* inputList = new TList() ;
  if (runProof) {
    proof->AddInput(&sr_conf);
    proof->AddInput(fOutName) ;
    //proof->AddInput(dataType) ;
  }
  else {
    //gDirectory->Add(&sr_conf) ;--> this works too but causing confusion related to what dirrectory is the current directory
    inputList->Add(&sr_conf) ;
    inputList->Add(fOutName) ;
    //inputList->Add(dataType) ;
  }
  
  AnaProcessor analysis;
  //analysis.m_doRunProof = runProof ;
  //analysis.m_outputfilename = "test.root" ;
  if (!runProof) analysis.SetInputList(inputList) ;
  chain.Process(&analysis, "", 100) ;
  //chain.Process(&analysis) ;
  
  //if (glob.debug) xdebug="1";
  //TString syst = TString::Format("%d",glob.systematics);
  //TString stype = TString::Format("%d",glob.type); 
  //TString  moption= syst+","+stype+","+xdebug+","+xproof; 
  //chain.Process("analysis.C+",moption,glob.MaxEvents);




  gSystem->GetMemInfo(&memInfo);
  cout << " Mem Total = " << memInfo.fMemTotal << endl;
  cout << " Mem Used = " << memInfo.fMemUsed << endl;
  cout << " Mem Swapped = " << memInfo.fSwapUsed << endl;
  int mEnd=(int)memInfo.fMemUsed;
  cout << "###  Mem Used for the program= " << mEnd-mStart << endl;


    cout << "Number of events processed=" <<
    //glob.nev << " Events requested=" << glob.MaxEvents << endl;
    // write histograms  
    // h.finalize();
    // cout << "Total input events=" <<  glob.TotalEvents << endl;
    endl ;


// write out log file on Proof master/worker nodes
  if (runProof) {
    TProofLog *pl = proof->GetManager()->GetSessionLogs();
    pl->Save("*", "/uscms_data/d3/duong/Output/HVbb-AnaPackage/main_proof.log");

  }


 cout << " --- All done! ---" << endl;


  return 0;
}
