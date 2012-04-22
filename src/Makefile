#===============================================================================
#=
#= File:    Makefile
#=
#= Project: sicherDigger
#= Author:  damicha of defect, (c) 2011-2012
#=
#= Description:
#=  Build binary file and doxygen generated documentation
#=  $ make              - build binary
#=  $ make ctags        - build ctags
#=  $ make doxygen      - build documentation
#=  $ make clean        - cleans up the source directory
#=
#= License: See license file in the main directory.
#=
#===============================================================================


#-------------------------------------------------------------------------------
CC = g++
CFLAGS = -g -O0 -Wall
INCLUDE_DIRS = -I.
OBJECTS =   sicherDigger.o \
            ObjField/Field.o ObjField/Entry.o \
            DOT/Base.o DOT/Exit.o DOT/Player.o\
            SDig_DataObject.o \
            SDig_TimeEngine.o \
            TextEngine.o \
            PhysicsEngine.o \
            GameEngine.o \
            LevelEngine.o
INCLUDES = $(wildcard *.h) $(wildcard ObjField/*.h) $(wildcard DOT/*.h)
LDFLAGS_NCURSES = -lncurses



#-------------------------------------------------------------------------------
sicherDigger: $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS_NCURSES) $(OBJECTS) -o $@

all: sicherDigger html
    

#-------------------------------------------------------------------------------
%.o: %.cpp $(INCLUDES)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@


#-------------------------------------------------------------------------------
html:
	doxygen

ctags:
	ctags -R *.cpp *.h

#-------------------------------------------------------------------------------
clean:
	rm -f $(OBJECTS)
	rm -f sicherDigger
	rm -rf html/ latex/
	rm -rf tags

.PHONY: html clean

