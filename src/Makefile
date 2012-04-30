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
SRC =   sicherDigger.cpp \
        ObjField/Field.cpp ObjField/Entry.cpp \
        DOT/Base.cpp DOT/Exit.cpp DOT/Player.cpp \
        SDig_DataObject.cpp \
        SDig_TimeEngine.cpp \
        TextEngine.cpp \
        PhysicsEngine.cpp \
        GameEngine.cpp \
        LevelEngine.cpp LevelConfig.cpp LevelConfigSet.cpp
OBJECTS = $(SRC:.cpp=.o)

LDFLAGS_NCURSES = -lncurses



#-------------------------------------------------------------------------------
sicherDigger: $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS_NCURSES) $(OBJECTS) -o $@

all: sicherDigger html
    

#-------------------------------------------------------------------------------
# create dependencies
depend:
	gcc -M $(INCLUDE_DIRS) $(SRC) > depend

-include depend

#-------------------------------------------------------------------------------
%.o: %.cpp
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
	rm -rf depend

.PHONY: html clean

