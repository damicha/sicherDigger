#===============================================================================
#=
#= File: Makefile
#= Author: damicha of defect, (c) 2011
#=
#===============================================================================


#-------------------------------------------------------------------------------
CC = g++
CFLAGS = -g -O2 -Wall
OBJECTS = fieldLib.o objFieldEntry.o objField.o \
          SDig_TimeEngine.o \
          SDig_PhysicsEngine.o \
          baseDataObjectType.o
INCLUDES = $(wildcard *.h)
LDFLAGS_NCURSES = -lncurses

#-------------------------------------------------------------------------------
all: fieldLib
    
#-------------------------------------------------------------------------------
fieldLib: $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS_NCURSES) $(OBJECTS) -o $@

%.o: %.cpp $(INCLUDES)
	$(CC) $(CFLAGS) -c $<


#-------------------------------------------------------------------------------
doxygen:
	doxygen

#-------------------------------------------------------------------------------
clean:
	rm -f $(OBJECTS)
	rm -f fieldLib
	rm -rf html/ latex/


