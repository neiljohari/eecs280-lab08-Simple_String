# Output file name
EXECUTABLE  = solution

# enables c++17 on CAEN 
PATH := /usr/um/gcc-6.2.0/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/gcc-6.2.0/lib64
LD_RUN_PATH := /usr/um/gcc-6.2.0/lib64

# This is the path from the CAEN home folder to where projects will be
# uploaded. (eg. /home/njohari/eecs280-lab08-simple-string/)
# Change this if you prefer a different path.
# REMOTE_BASEDIR := f20/eecs280   # /home/njohari/f20/eecs280/
REMOTE_BASEDIR := eecs280-lab08-simple-string

# designate which compiler to use
CXX         = g++

# list of sources used in project
SOURCES     = $(wildcard *.cpp)
# list of objects used in project
OBJECTS     = $(SOURCES:%.cpp=%.o)

#Default Flags (we prefer -std=c++17 but Mac/Xcode/Clang doesn't support)
CXXFLAGS = -std=c++1z -Wconversion -Wall -Werror -Wextra -pedantic 


release: CXXFLAGS += -O3 
release: $(EXECUTABLE)

# make debug - will compile sources with $(CXXFLAGS) and the -g3 flag
#              also defines DEBUG, so "#ifdef DEBUG /*...*/ #endif" works
debug: CXXFLAGS += -g3 -DDEBUG
debug:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE)_debug

all: release debug

$(EXECUTABLE): $(OBJECTS)
ifeq ($(EXECUTABLE), executable)
	@echo Edit EXECUTABLE variable in Makefile.
	@echo Using default a.out.
	$(CXX) $(CXXFLAGS) $(OBJECTS)
else
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE)
endif


# rule for creating objects
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $*.cpp

# make clean - remove .o files, executables, tarball
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(EXECUTABLE)_debug
	rm -Rf *.dSYM

sync2caen: REMOTE_PATH := ${REMOTE_BASEDIR}_${EXECUTABLE}_sync
sync2caen:
	# Synchronize local files into target directory on CAEN
	rsync \
      -av \
      --exclude '.git*' \
      --exclude '.vs*' \
      --exclude '*.code-workspace' \
      --filter=":- .gitignore" \
      "."/ \
			"njohari@login.engin.umich.edu:'${REMOTE_PATH}/'" # TODO: change this to your uniqname
	echo "Files synced to CAEN at ~/${REMOTE_PATH}/"


# THE COMPILER CAN GENERATE DEPENDENCIES FROM SOURCE CODE
# % g++ -MM *.cpp
Simple_String.o: Simple_String.cpp Simple_String.h
main.o: main.cpp Simple_String.h

# these targets do not create any files
.PHONY: debug clean sync2caen 
# disable built-in rules
.SUFFIXES:
