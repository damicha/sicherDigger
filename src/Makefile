#===============================================================================
#=
#= File:    Makefile
#=
#= Project: sicherDigger
#= Author:  damicha of defect, (c) 2011-2012
#=
#= Description:
#=  Build binary file and doxygen generated documentation
#=  $ make              - builds binary
#=  $ make doxygen      - builds documentation
#=  $ make clean        - cleans up the source directory
#=
#= License: See license file in the main directory.
#=
#===============================================================================


#-------------------------------------------------------------------------------
CC = g++
CFLAGS = -g -O0 -Wall
OBJECTS =   sicherDigger.o \
            objFieldEntry.o objField.o \
            SDig_TimeEngine.o \
            SDig_TextEngine.o \
            SDig_PhysicsEngine.o \
            SDig_GameEngine.o \
            SDig_LevelEngine.o \
            SDig_BaseDOT.o
INCLUDES = $(wildcard *.h) $(wildcard ObjField/*.h)
LDFLAGS_NCURSES = -lncurses



#-------------------------------------------------------------------------------
sicherDigger: $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS_NCURSES) $(OBJECTS) -o $@

all: sicherDigger html
    

#-------------------------------------------------------------------------------
%.o: %.cpp $(INCLUDES)
	$(CC) $(CFLAGS) -c $<


#-------------------------------------------------------------------------------
html:
	doxygen

#-------------------------------------------------------------------------------
clean:
	rm -f $(OBJECTS)
	rm -f sicherDigger
	rm -rf html/ latex/

.PHONY: html clean

