include Makefile.arch
#----------------------------------------------------------------------------------
#TESTS           := nTuple_analyzer_emu.C
#TESTS           := nTuple_analyzer_muon.C
TESTS           := tupelanalyzer.C
#TESTS           := zjanalyzr.C
#TESTS           := npileup.C
#TESTS           := parton_analyzer.C
TESTO           := $(TESTS:.C=.o)
#TEST            := nTuple_analyzer_emu
#TEST            := nTuple_analyzer_muon
TEST            := tupelanalyzer
#TEST            := zjanalyzr
#TEST            := npileup
#TEST            := parton_analyzer

OBJ             = $(TESTO)
PROGRAMS        = $(TEST)

CXXFLAGS      += 
CXXFLAGS      += 
GLIBS         += 
#----------------------------------------------------------------------------------
.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf)

all:            $(PROGRAMS)

$(TEST):        $(TESTO)
		$(LD) $(LDFLAGS) $^ $(GLIBS) $(OutPutOpt)$@
		@echo "$@ done"

clean:
		@rm -f $(OBJ) $(TESTO) core *~ src/*~ include/*~

.$(SrcSuf).$(ObjSuf):
		$(CXX) $(CXXFLAGS) -c $< -o $@
