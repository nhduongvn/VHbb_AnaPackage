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
#include <fstream>
#include <vector>
#include <string>

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
#include "inc/AnaConf.h"
#include "inc/SR.h"
#include "inc/CR_ZLF.h"

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
   //string lheHTcutIn = argv[6] ;
   //float lheHTcut(10000) ;
   //if (lheHTcutIn != "") lheHTcut = stof(lheHTcutIn) ;
   string use_lheHTcut = argv[6] ;
   TString proofLog = argv[7] ;
   proofLog.ToUpper() ;

   //===Print out inputs===
  cout << "\n================= INPUTS ==================================" ;
  cout << "\n Data type:        " << dataTypeIn ;
  cout << "\n Run mode:         " << runMode ;
  cout << "\n File list:        " << infiles_list ;
  cout << "\n Output file name: " << out_file_name ;
  cout << "\n Uncertainty:      " << uncertainty ;
  cout << "\n Use LHE HT cut:   " << use_lheHTcut ;
  cout << "\n ProofLog:         " << proofLog ;
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
      TString tmpStr = "gSystem->Load(\"$ROOTSYS/lib/libPhysics.so\") ;" ;
      proof->Exec(tmpStr) ;
      tmpStr = "gSystem->Load(\""+TString(workDir)+"/lib/libMyLib.so\") ;" ;
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
  
  
  AnaConf sr_conf("SR_ZH");
  if (dataTypeIn == "DATA") sr_conf.setIsData(true);
  if (dataTypeIn == "MCFILE") {
    sr_conf.setIsData(false);
  }
 
  AnaConf cr_zhf_conf("CR_ZH_ZHF") ;
  if (dataTypeIn == "DATA") cr_zhf_conf.setIsData(true);
  if (dataTypeIn == "MCFILE") {
    cr_zhf_conf.setIsData(false);
  }
  
  AnaConf cr_zlf_conf("CR_ZH_ZLF") ;
  if (dataTypeIn == "DATA") cr_zlf_conf.setIsData(true);
  if (dataTypeIn == "MCFILE") {
    cr_zlf_conf.setIsData(false);
  }
  
  AnaConf cr_tt_conf("CR_ZH_TT") ;
  if (dataTypeIn == "DATA") cr_tt_conf.setIsData(true);
  if (dataTypeIn == "MCFILE") {
    cr_tt_conf.setIsData(false);
  }

 
  TNamed* fOutName = new TNamed("outputfilename", out_file_name.Data()) ;
  //TNamed* dataType = new TNamed("DATA_TYPE", dataTypeIn) ;
  TList* inputList = new TList() ;
  if (runProof) {
    proof->AddInput(&sr_conf);
    proof->AddInput(&cr_zhf_conf) ;
    proof->AddInput(&cr_zlf_conf) ;
    proof->AddInput(&cr_tt_conf) ;

    proof->AddInput(fOutName) ;
    //proof->AddInput(dataType) ;
  }
  else {
    //gDirectory->Add(&sr_conf) ;--> this works too but causing confusion related to what dirrectory is the current directory
    inputList->Add(&sr_conf) ;
    inputList->Add(&cr_zhf_conf) ;
    inputList->Add(&cr_zlf_conf) ;
    inputList->Add(&cr_tt_conf) ;

    inputList->Add(fOutName) ;
    //inputList->Add(dataType) ;
  }
  
  AnaProcessor analysis;
  //analysis.set_LHE_HTcut(lheHTcut) ;
  //analysis.m_doRunProof = runProof ;
  //analysis.m_outputfilename = "test.root" ;
  if (!runProof) analysis.SetInputList(inputList) ;

  TString option = "" ;
  if (use_lheHTcut == "TRUE") option = "USE_LHE_CUT" ; 
  //chain.Process(&analysis, "", 100) ;
  chain.Process(&analysis, option) ;
  
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
    if (proofLog == "") {
      pl->Save("*", "/uscms_data/d3/duong/Output/HVbb-AnaPackage/main_proof.log");
    }
    else {
      pl->Save("*", "/uscms_data/d3/duong/Output/HVbb-AnaPackage/" + proofLog + ".log");
    }

  }

 //===Add some histograms to output files===
 //int Nfiles = fc.GetNFiles() ;
    //for (int i = 0; i < Nfiles; i++) {
      // float donefiles= (float)i / (float)Nfiles;
       //cout << "\nfile to read:" << glob.ntup[i] << endl;
       //chain.Add(glob.ntup[i].c_str(),-1); // do not add non-recovebale
    //}

  //TIter next(fc.GetList()) ; 
  //while(TObject* obj = next() ) {
    //TString objName = obj->GetName();
    //cout << "\n Filename: " << objName << "  " << obj->IsA()->GetName() ;
  //}
  if (dataTypeIn == "MCFILE") { 
  TH1D* hChainEntry = new TH1D("ChainEntries", "", 1, 0, 2) ;
  hChainEntry->SetBinContent(1, chain.GetEntries()) ;

  std::ifstream infile_listTmp(infiles_list) ;
  std::string line;
  TH1D* hCount = new TH1D("TotalCount", "", 4, 0, 4) ;
  hCount->GetXaxis()->SetBinLabel(1, "Count") ;
  hCount->GetXaxis()->SetBinLabel(2, "Count_pos_weight") ;
  hCount->GetXaxis()->SetBinLabel(3, "Count_neg_weight") ;
  hCount->GetXaxis()->SetBinLabel(4, "Count_pos_minus_neg_weight") ;
  double counts[4] = {0,0,0,0} ;
  TFile* fTmp ;
  while (std::getline(infile_listTmp, line))
  {
    std::istringstream iss(line);
    string fileName ;
    if (!(iss >> fileName)) { cout << "\n Error while getting plot name " << line << endl ; break; } // error
    cout << fileName << endl ;
    fTmp = TFile::Open(TString(fileName), "READ") ;
    if (fTmp) { 
      TH1D* h = (TH1D*)fTmp->Get("Count") ;
      counts[0] += h->GetBinContent(1) ;
      h = (TH1D*)fTmp->Get("CountPosWeight") ;
      counts[1] += h->GetBinContent(1) ;
      h = (TH1D*)fTmp->Get("CountNegWeight") ;
      counts[2] += h->GetBinContent(1) ;
    }
    fTmp->Close() ;
    delete fTmp ;
  }

  counts[3] = counts[1] - counts[2] ;
    
   for (int i = 0; i <4; i++) {
     hCount->SetBinContent(i+1, counts[i]) ;
     cout << "\n" << hCount->GetXaxis()->GetBinLabel(i+1) << "\t" << hCount->GetBinContent(i+1) << endl ;
   }
  
  fTmp = TFile::Open(out_file_name.Data(), "UPDATE") ;
  fTmp->cd() ;
  hCount->Write() ;
  hChainEntry->Write() ;
  fTmp->Close() ;
  } //end if (dataType == "MCFILE")
  cout << " --- All done! ---" << endl;


  return 0;
}
