# S.Chekanov
# ANL analysis tutorial 
#include ${ROOTSYS}/test/Makefile.arch
include $(ROOTSYS)/etc/Makefile.arch


# Root variables
ROOTCFLAGS    = $(shell root-config --nonew --cflags)
ROOTLIBS      = $(shell root-config --nonew --libs)
ROOTGTTLIBS   = $(shell root-config --nonew --glibs)
# Assign or add variables
CXXFLAGS     += $(ROOTCFLAGS)
#CXXFLAGS     += -D MCFILE
LIBS         += $(ROOTLIBS) -lProof

SOURCE_FILES := $(shell ls -1 *.cxx)
SOURCE_FILES += $(shell ls -1 src/*.cxx)

LIB_FILES += $(shell ls -1 src/*.cxx)

INCLUDE1= -I./inc
INCLUDE2= -I.


# build object files 
objects       = $(patsubst %.cxx,%.o,$(SOURCE_FILES))
libobjects       = $(patsubst %.cxx,%.o,$(LIB_FILES))


%.o: %.cxx
	$(CXX) $(OPT) $(CXXFLAGS) $(INCLUDE1) $(INCLUDE2) -o $@ -c $<

Tasks: mydict main lib

mydict: inc/BaseTree.h inc/AnaProcessor.h inc/AnaBaseSelector.h inc/SR.h inc/AnaConf.h
	@rm -f ./*_dict_rdict.pcm
	@rm -f src/*_dict*
	@rm -f inc/*_dict*
#	@rm -f src/BaseTree_dict*
#	@rm -f inc/BaseTree_dict*
#	@rm -f src/AnaProcessor_dict*
#	@rm -f inc/AnaProcessor_dict*
#	@rm -f src/AnaBaseSelector_dict*
#	@rm -f inc/AnaBaseSelector_dict*
#	@rm -f src/SR_dict*
#	@rm -f inc/SR_dict*
#	@rm -f inc/AnaConf_dict*
#	@rm -f src/AnaConf_dict*
	@rootcint src/BaseTree_dict.cxx -c inc/BaseTree.h
	@rootcint src/AnaProcessor_dict.cxx -c inc/AnaProcessor.h
	@rootcint src/AnaBaseSelector_dict.cxx -c inc/AnaBaseSelector.h
	@rootcint src/AnaConf_dict.cxx -c inc/AnaConf.h
	@rootcint src/SR_dict.cxx -c inc/SR.h
	@rootcint src/CR_ZLF_dict.cxx -c inc/CR_ZLF.h
	@rootcint src/CR_ZHF_dict.cxx -c inc/CR_ZHF.h
	@rootcint src/CR_TT_dict.cxx -c inc/CR_TT.h
	@cp src/*_dict_rdict.pcm ./

main: $(objects)
	$(LD) $(LDFLAGS) $^ $(LIBS) $(OutPutOpt)$@

lib: $(libobjects)
	@rm -f lib/*_dict_rdict.pcm
	@cp src/*_dict_rdict.pcm lib/
	$(LD) $(LDFLAGS) -shared -fPIC $(libobjects) -o lib/libMyLib.so
	

clean:
	  @rm -f *.o  main *~ src/*.o src/*~ inc/*~; echo "Clear.." 

print-%  : ; @echo $* = $($*)
#use this command to print out variable value: make print-VARIABLE
