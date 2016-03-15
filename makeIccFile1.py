import sys,os,string, commands

dataType = sys.argv[1] #DATA MCFILE
print dataType

if not (dataType == 'DATA' or dataType == 'MCFILE'):
  print 'No data type defined. Exit now!!!'
  sys.exit()

f = open('inc/BaseTree.h', 'r')
lines = f.readlines()
f.close()


#find a list of .cxx files
os.system("ls src/*.cxx > tmp.txt")
f = open("tmp.txt")
source_files = f.readlines()
f.close()
print source_files
source_file_lines = []
for source_file in source_files:
    if source_file != 'src/BaseTree.cxx\n':
      source_file = source_file.replace("\n", "")
      f = open(source_file)
      lines_tmp = f.readlines()
      f.close()
      for line in lines_tmp:
        source_file_lines.append(line)

#print source_file_lines

#print lines1
if dataType == 'DATA':
  f = open('inc/InitBranches_data.icc', 'w')
if dataType == 'MCFILE':
  f = open('inc/InitBranches_MC.icc', 'w')

for line in lines:
  if line.find("SetBranchAddress") != -1:
    a = line.split('",')[1].split(', ')[0].replace(' ','').replace('&','')
    for line1 in source_file_lines:
      if line1.find('//') > -1:
        continue
      if line1.find(a) != -1:
        b = line.replace('fChain->', '')
        print b 
        f.write(b)
        break	
f.close()

print 'done'
