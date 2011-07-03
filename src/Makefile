#
# Author: damicha of defect
#  (C) 2011
# 
#

CC = g++
CFLAGS = -g -O2 
OBJECTS = fieldLib.o baseObj.o baseObjField.o

all: fieldLib

fieldLib: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

clean:
	rm -f $(OBJECTS)
	rm -f fieldLib

#%.o: %.c
#	$(CC) $(CFLAGS) -c $<


