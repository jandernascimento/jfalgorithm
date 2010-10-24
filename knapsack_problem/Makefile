#Author: Jander Nascimento
#License: LGPL

CC=gcc
CFLAGS=

all: generator read_instance greedy brute_force

generator: generator.c 
	$(CC) -o $@ $<

read_instance: read_instance.c 
	$(CC) -o $@ $< -lrt

greedy: greedy.c baselib.o 
	$(CC) $(CFLAGS) -o $@ $< baselib.o -lrt 

brute_force: brute_force.c baselib.o
	$(CC) $(CFLAGS) -o $@ $< baselib.o -lrt 

baselib.o: baselib.c
	$(CC) -c $<

clean:
	-rm greedy 
	-rm brute_force 
	-rm read_instance
	-rm generator
	-rm baselib.o 

.PHONY: clean
