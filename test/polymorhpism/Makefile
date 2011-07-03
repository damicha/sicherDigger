#
# Author: damicha of defect
#  (C) 2011
# 
#

CC = g++
CFLAGS = -g -O2 
OBJECTS = poly.o
INCLUDES = $(wildcard *.h)

all: poly
    
poly: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

%.o: %.cpp $(INCLUDES)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS)
	rm -f poly


