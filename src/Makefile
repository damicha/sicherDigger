#
# Author: damicha of defect
#  (C) 2011
# 
#

CC = g++
CFLAGS = -g -O2 
OBJECTS = fieldLib.o # baseObj.o

all: fieldLib

fieldLib: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

clean:
	rm $(OBJECTS)
	rm fieldLib

#%.o: %.c
#	$(CC) $(CFLAGS) -c $<


