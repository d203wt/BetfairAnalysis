CXX             = g++  
CXXFLAGS        = -O -Wall -fPIC -ggdb -m64
LD              = g++  
ROOTCFLAGS      = -I/usr/include/root  
ROOTLIBS        = -L/usr/lib64/root  $(shell /usr/bin/root-config --libs) 

INCLUDES        = `pwd`/Analysis 
# GRLDIR          = `pwd`/include/GoodRunsLists
# MUONSCALEDIR    = `pwd`/include/MuonQuality/MuonMomentumCorrections-00-05-00/share
# MUONEFFDIR    = `pwd`/include/MuonQuality/MuonEfficiencyCorrections-00-05-00/MuonEfficiencyCorrections
CXXFLAGS        += $(ROOTCFLAGS) 
# CXXFLAGS        += -I${GRLDIR}  
CXXFLAGS        += -I${INCLUDES}  
# CXXFLAGS        += -I${MUONMOMDIR}
# CXXFLAGS        += -I${MUONEFFDIR}
# CXXFLAGS        += -I${MUONSCALEDIR}
LIBS            = $(ROOTLIBS) 
OBJS            =  src/Analysis.o src/DataEntry.o
BUILDDIR 	= `pwd`/bin

PROGRAM         = BetfairAnalysis 

all:            $(PROGRAM)  

$(PROGRAM):     $(OBJS)   
	        $(CXX) $(CXXFLAGS) -g3 -pg -p -o $(BUILDDIR)/$(PROGRAM) $(OBJS) $(LIBS)  
			rm $(OBJS)


clean:;         @rm -f $(OBJS) core *.o *.out   

