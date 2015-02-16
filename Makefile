# set compiler and compile options
EXEC = ai-optimizer
CXX = g++                                # use the GNU C++ compiler
OPTS = -O0 -Wall -g -Wno-write-strings   # use some optimization, report all warnings and enable debugging
CFLAGS = $(OPTS)                         # add compile flags
LDFLAGS = -lcairo                        # specify link flags here
 
# set a list of directories
INCDIR =./include
OBJDIR = ./obj
BINDIR = ./bin
SRCDIR = ./src
 
# set the include folder where the .h files reside
CFLAGS += -I$(INCDIR) -I$(INCDIR_LAMMPS) -I$(SRCDIR)
 
# add here the source files for the compilation
SOURCES = ai-optimizer.cpp marching_squares.cpp color_scheme.cpp mcmc.cpp optimizer.cpp \
trial_function.cpp genalg.cpp plotter.cpp
 
# create the obj variable by substituting the extension of the sources
# and adding a path
_OBJ = $(SOURCES:.cpp=.o)
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))
 
all: $(BINDIR)/$(EXEC)
 
$(BINDIR)/$(EXEC): $(OBJ)
	$(CXX) -o $(BINDIR)/$(EXEC) $(OBJ) $(LDFLAGS)
 
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c -o $@ $< $(CFLAGS)

test: $(BINDIR)/$(EXEC)
	$(BINDIR)/$(EXEC)
 
clean:
	rm -vf $(BINDIR)/$(EXEC) $(OBJ)