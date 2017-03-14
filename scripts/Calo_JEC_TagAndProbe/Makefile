ObjSuf        = o
SrcSuf        = cpp
ExeSuf        =
DllSuf        = so
OutPutOpt     = -o
HeadSuf       = h

include $(CMSSW_RELEASE_BASE)/.SCRAM/$(SCRAM_ARCH)/MakeData/Tools/boost_header.mk

ROOFIT_INCLUDE := $(shell cd $(CMSSW_BASE); scram tool info roofitcore | grep INCLUDE= | sed 's|INCLUDE=||')

ROOFIT_LIBDIR := $(shell cd $(CMSSW_BASE); scram tool info roofitcore | grep LIBDIR= | sed 's|LIBDIR=||')

INCLUDES = -I$(ROOFIT_INCLUDE)/ -I$(CMSSW_BASE)/src/CMSDIJET/DijetRootTreeAnalyzer/include -I$(boost_header_EX_INCLUDE)

ROOTSYS  ?= ERROR_RootSysIsNotDefined

ROOTCFLAGS = $(shell root-config --cflags)
ROOTLIBS   = $(shell root-config --libs) -lMinuit -lRooFitCore -lRooFit

CXX           = g++ -g
CXXFLAGS	    = -std=c++0x -fPIC
LD			      = g++
LDFLAGS		    = $(shell root-config --ldflags) -Wl,--as-needed
SOFLAGS		    = 
AR            = ar
ARFLAGS       = -cq

LDDIR         = $(shell echo "-L" $$LD_LIBRARY_PATH | sed -e 's/:/ -L/g') -L$(ROOFIT_LIBDIR)/ -L../lib/

CXXFLAGS	   += $(ROOTCFLAGS) $(INCLUDES)
LIBS  		    = $(LDDIR) $(ROOTLIBS)# -lAnalysis -lTreeAnalyzer_PhotonJet
GLIBS	    	  = $(ROOTGLIBS)
#------------------------------------------------------------------------------
SOURCES		= $(wildcard *.$(SrcSuf))
OBJECTS		= $(SOURCES:.$(SrcSuf)=.$(ObjSuf))
DEPENDS		= $(SOURCES:.$(SrcSuf)=.d)
SOBJECTS	= $(SOURCES:.$(SrcSuf)=.$(DllSuf))

.SUFFIXES: .$(SrcSuf) .$(ObjSuf)

###

all: drawCaloJEC_TagAndProbe_SeparatedTrigger drawCaloJEC_TagAndProbe_TriggerComparison drawCaloJEC_TagAndProbe drawCaloJEC_ClosureTest drawCaloJEC_DifferentMethod drawCaloJEC_DifferentPileUp


clean:
	@rm *.o;


drawCaloJEC_TagAndProbe_SeparatedTrigger: drawCaloJEC_TagAndProbe_SeparatedTrigger.o
	$(LD) $(LIBS) $(SOFLAGS) $(LDFLAGS) $+ -o $@

drawCaloJEC_TagAndProbe_TriggerComparison: drawCaloJEC_TagAndProbe_TriggerComparison.o
	$(LD) $(LIBS) $(SOFLAGS) $(LDFLAGS) $+ -o $@

drawCaloJEC_TagAndProbe: drawCaloJEC_TagAndProbe.o
	$(LD) $(LIBS) $(SOFLAGS) $(LDFLAGS) $+ -o $@

drawCaloJEC_ClosureTest: drawCaloJEC_ClosureTest.o
	$(LD) $(LIBS) $(SOFLAGS) $(LDFLAGS) $+ -o $@

drawCaloJEC_DifferentMethod: drawCaloJEC_DifferentMethod.o
	$(LD) $(LIBS) $(SOFLAGS) $(LDFLAGS) $+ -o $@

drawCaloJEC_DifferentPileUp: drawCaloJEC_DifferentPileUp.o
	$(LD) $(LIBS) $(SOFLAGS) $(LDFLAGS) $+ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

#Make the dependencies
%.d: %.cpp
	@echo "Generating dependencies for $<"
	@set -e; $(CXX) -M $(CXXFLAGS) $< \
	| sed 's%\($*\)\.o[ :]*%\1.o $@ : %g' > $@; \
	[ -s $@ ] || rm -f $@

ifneq ($(MAKECMDGOALS), clean) 
-include $(DEPENDS) 
endif 
