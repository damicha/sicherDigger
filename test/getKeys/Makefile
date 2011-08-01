#
# Author: damicha of defect
#  (C) 2011
# 
#

CC = g++
CFLAGS = -g -O2 
LDFLAGS = -lncurses
OBJECTS = getKey.o
INCLUDES = $(wildcard *.h)

all: getKey
    
getKey: $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cpp $(INCLUDES)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS)
	rm -f poly


