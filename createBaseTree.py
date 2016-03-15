import os,sys
import ROOT
from ROOT import TChain

path = "root://131.225.207.127:1094/" + sys.argv[1] + "/*.root"
dataType = sys.argv[2]

chain = TChain("tree")
chain.Add(path)
chain.MakeSelector("BaseTree")
os.system('mv BaseTree.h BaseTree/BaseTree_' + dataType + '.h')
os.system('mv BaseTree.C BaseTree/BaseTree_' + dataType + '.cxx')
