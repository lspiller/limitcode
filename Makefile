ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs)
ROOTGLIBS     = $(shell root-config --glibs)

CXX           = g++
CXXFLAGS      =-I$(ROOTSYS)/include -O -Wall -fPIC -I$(PWD)  
LD            = g++
LDFLAGS       = -g
SOFLAGS       = -shared

CXXFLAGS     += $(ROOTCFLAGS)
LIBS          = $(ROOTLIBS) 
GLIBS         = $(ROOTGLIBS)


#program_C_SRCS 	= $(wildcard *.c)
program_C_SRCS 	=  
program_C_OBJS 	= ${program_C_SRCS:.c=.o}

OBJS	= PrintWS.o

PrintWS: $(OBJS)
	$(CXX) $(program_C_SRCS) -o $@ $(OBJS) $(CXXFLAGS) $(LIBS)
	#$(CXX) -c $(program_C_SRCS) $(CXXFLAGS) $(LIBS)

# suffix rule
.cc.o:
	#$(CXX) -c $(program_C_SRCS) $(CXXFLAGS) $(GDBFLAGS) $(LIBS) $<
	$(CXX) -c $(CXXFLAGS) $(GDBFLAGS) $<
# clean
clean:
	rm -f *~ *.o *.o~ core
