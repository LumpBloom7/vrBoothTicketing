# Project: Project1
# Makefile created by Dev-C++ 5.11

shell = cmd.exe
CPP      = g++.exe
CC       = gcc.exe
WINDRES  = windres.exe
strip    = strip.exe
OBJ      = $(OLDDIR)/main.o
LINKOBJ  = $(OLDDIR)/main.o
#-static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic
LIBS     = -g3 -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic
INCS     =
CXXINCS  = -I $(OLDDIR)/include/
OUTPUTDIR = $(OLDDIR)/bin/
BIN      = $(OUTPUTDIR)/Output.exe
CXXFLAGS = $(CXXINCS) $(GITDETAILS) -Ofast -std=c++17 -w -pedantic
CFLAGS   = $(INCS)
RM       = rm.exe -f
GITDETAILS = -D GIT_VERSION=\"$(GIT_VERSION)\" -D GIT_COMMIT=\"$(GIT_COMMIT)\" -D GIT_DATE=\"$(GIT_DATE)\" -D BUILD_DATE=\"$(BUILD_DATE)\"

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o $(BIN) $(LIBS)

main.o: $(OLDDIR)/main.cpp
	$(CPP) -c $(OLDDIR)/main.cpp -o $(OLDDIR)/main.o $(CXXFLAGS)
