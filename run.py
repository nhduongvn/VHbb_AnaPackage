#! user/bin/env python
#this file can be used for create small ntuples with only needed branches.
#input includes:
#1. a text file containing the name of input skim data set from grid skim jobs
#2. number of files to be merged
#3. a swich (doSkim) to switch between do or don't do skim
#The input files for particular run is written in a text file in "Run" directory
#The output ntuple are writen to /data4/nguyend/SmallerSkim
#The log, lumi summary are written to "Run" directory

import sys,os,string, commands
import time

CWD = os.getcwd()
os.chdir(CWD)

runDir = '/uscms/home/duong/HVbb/AnaPackage/'
inDS = 'dataList.txt'
outFilePrenameAna = "test" #prename for skim jobs is ds
runMode = sys.argv[1] #NoProof or ProofLite 

base_tree_data = "BaseTree/BaseTree_data_V15"
base_tree_MC = "BaseTree/BaseTree_MC"

#==uncertainty===
#NOM, JECU, JECD, PUU, PUD
uncertainty = sys.argv[2] 


datalist = []
dsfile = []
dsfile.append(inDS)
for f in dsfile:
    for line in open(f, 'r'):
        if line.find('#') == -1:
            datalist.append(line)

#datalist = ['/uscmst1b_scratch/lpc1/lpctrig/duong/ZplusC_data/DataFiles/elec.root\n']

#tree name

dsType = ''
previous_dsType = '' # to decide whether to compile or not

for line in datalist:
    ds = line.replace('\n','')
    print 'current data list is: ', ds

#identify data type
    if line.find('SingleElectron') != -1 or line.find('DoubleEG') != -1:
      dsType = 'DATA'
      print 'Runing on ', dsType
    else:
      dsType = 'MCFILE'
      print 'Runing on ', dsType

#compile code
    if dsType != previous_dsType:
      previous_dsType = dsType
      os.system('make clean')
      if dsType == 'DATA':
        os.system('cp ' + base_tree_data + '.h inc/BaseTree.h')
        os.system('cp ' + base_tree_data + '.cxx src/BaseTree.cxx')
        os.system('make -f Makefile')
        os.system("python makeIccFile1.py DATA")
      if dsType == 'MCFILE':
        os.system('cp ' + base_tree_MC + '.h inc/BaseTree.h')
        os.system('cp ' + base_tree_MC + '.cxx src/BaseTree.cxx')
        os.system('make -f MakefileMC')
        os.system("python makeIccFile1.py MCFILE")

#create filelist
    infiles = 'anafiles_tmp.txt'
    os.system('rm ' + infiles)
    com = ''
    if ds.find('store/') == -1:
      if ds.find('.root') != -1:
        com = 'ls ' + ds + ' >> ' + infiles
      else:
        com = 'ls ' + ds + '/*.root >> ' + infiles
    else:
      if ds.find('.root') != -1:
        a = ds.split('/')
        b = a[len(a)-1]
        c = ds.split(b)[0]
        print a, b, c
        com = 'xrdfs root://cmseos.fnal.gov ls -u ' + c + ' | grep ' + b + ' >> ' + infiles
      else:
        com = 'xrdfs root://cmseos.fnal.gov ls -u ' + ds + ' >> ' + infiles
       
    print com
    os.system(com)

#run over file list

#get output filename
    a = ds.split('/')
    outnamepre = (runDir + "/Output/" + outFilePrenameAna + '_' + a[len(a)-3]).replace('\n','') 
    outname = outnamepre + '_' + uncertainty + '_all.root'
    if outname.find('*') != -1:
      outname = outname.replace('*','')
    print outname
    os.system('rm ' + outname) 

#run option
    inputs = dsType + '  ' + runMode + '  ' + infiles + '  ' + outname + '  ' + uncertainty 
    
    com = './main ' + inputs
    
    print com 
    os.system(com)
