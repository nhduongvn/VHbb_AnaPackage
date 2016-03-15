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
