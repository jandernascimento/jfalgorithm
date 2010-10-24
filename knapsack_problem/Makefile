#Author: Jander Nascimento
#License: LGPL

CC=gcc
CFLAGS=

all: greedy brute_force

greedy: greedy.c baselib.o 
	$(CC) $(CFLAGS) -o $@ $< baselib.o -lrt 

brute_force: brute_force.c baselib.o
	$(CC) $(CFLAGS) -o $@ $< baselib.o -lrt 

baselib.o: baselib.c
	$(CC) -c $<

clean:
	-rm greedy 
	-rm brute_force 
	-rm baselib.o 

.PHONY: clean
