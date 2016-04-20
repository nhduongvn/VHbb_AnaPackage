To compile
1. Edit Makefile. If changing from MC to DATA and vice versus, edit CXX flag and do "make clean" before "make"
2. Do make

======HVbb ntuple====
https://github.com/vhbb/cmssw/tree/vhbbHeppy74X/VHbbAnalysis/Heppy
https://twiki.cern.ch/twiki/bin/view/CMS/VHiggsBB
The actual stored variables for an object are specified in VHbbAnalysis/Heppy/python/vhbbobj.py and PhysicsTools/Heppy/python/analyzers/objects/autophobj.py, where the first contains VHbb extensions to the standard Heppy objects
The variable we actually store are specified in VHbbAnalysis/Heppy/test/vhbb.py with something like:

selLepton : lepton passing preselection (LepAna step in test/vhbb.py)
vLepton: lepton associated with vector boson
See: https://github.com/vhbb/cmssw/blob/vhbbHeppy74X/VHbbAnalysis/Heppy/python/VHbbAnalyzer.py

python run.py NoProof NOM
./main DATA  NoProof  anafiles_test.txt  /uscms/home/duong/HVbb/AnaPackage//Output/test.root  NOM


Vtype: defined in classifyEvent in VHbbAnalyzer.py

selected and inclusive lepton defined in here:
https://github.com/vhbb/cmssw/blob/vhbbHeppy74X/PhysicsTools/Heppy/python/analyzers/objects/LeptonAnalyzer.py

aLepton and vLepton defined in here:
https://github.com/vhbb/cmssw/blob/vhbbHeppy74X/VHbbAnalysis/Heppy/python/VHbbAnalyzer.py

inclusive -> selected -> vLepton
aLepton = inclusive - vLepton

HCSV: given by def doHiggsHighCSV(self,event) in VHbbAnalyzer: constructed from two highest CSV
H: given by def doHiggsHighPt(self,event) : in VHbbAnalyzer: constructed from twe highest Pt

root://131.225.207.127:1094//store/group/lpchbb/HeppyNtuples/V21/DoubleMuon/VHBB_HEPPY_V21_DoubleMuon__Run2015C_25ns-16Dec2015-v1/160318_132228/0000/tree_1.root
root://131.225.207.127:1094//store/group/lpchbb//HeppyNtuples/V21/SingleElectron/VHBB_HEPPY_V21_SingleElectron__Run2015D-16Dec2015-v1/160318_140448/0000/tree_992.root
root://131.225.207.127:1094//store/group/lpchbb//HeppyNtuples/V21/ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8/VHBB_HEPPY_V21_ZH_HToBB_ZToLL_M125_13TeV_powheg_Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160316_150654/0000/tree_1.root
