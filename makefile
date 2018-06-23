# Project: Project1
# Makefile created by Dev-C++ 5.11
BASH     = $(GITDIR)/usr/bin
GIT      = $(GITDIR)/bin/git.exe
CPP      = g++.exe
CC       = gcc.exe
WINDRES  = windres.exe
strip    = strip.exe
OBJ      = $(PROJECTDIR)/obj/main.o
LINKOBJ  = $(PROJECTDIR)/obj/main.o
#-static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic
LIBS     = -g3 -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic
INCS     =
CXXINCS  = -I $(PROJECTDIR)/include/
OUTPUTDIR = $(PROJECTDIR)/bin/
BIN      = $(OUTPUTDIR)/Output.exe
CXXFLAGS = $(CXXINCS) $(GITDETAILS) -Ofast -std=c++17 -w -Wall -Wextra -pedantic
CFLAGS   = $(INCS)
RM       = rm.exe -f

GIT_VERSION := $(shell $(GIT) -C $(PROJECTDIR) --no-pager describe --tags --always)
GIT_COMMIT  := $(shell $(GIT) -C $(PROJECTDIR) rev-parse --verify HEAD)
GIT_DATE    := $(firstword $(shell $(GIT) -C $(PROJECTDIR) --no-pager show --date=iso-strict --format="%ad" --name-only))
BUILD_DATE  := $(shell $(BASH)/date --iso=seconds)

ifneq ($(strip $(shell $(GIT) -C $(PROJECTDIR) status --porcelain)),)
 GIT_VERSION := $(GIT_VERSION)-D
endif

GITDETAILS = -D GIT_VERSION=\"$(GIT_VERSION)\" -D GIT_COMMIT=\"$(GIT_COMMIT)\" -D GIT_DATE=\"$(GIT_DATE)\" -D BUILD_DATE=\"$(BUILD_DATE)\"

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

executable: $(bin)
object: $(OBJ)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o $(BIN) $(LIBS)

$(OBJ): $(PROJECTDIR)/main.cpp
	$(CPP) -c $(PROJECTDIR)/main.cpp -o $(OBJ) $(CXXFLAGS)
