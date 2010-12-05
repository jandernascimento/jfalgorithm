#Author: Jander Nascimento
#License: LGPL
#Date: 25 Oct 2010

CC=gcc
CFLAGS=

all: generator read_instance greedy brute_force dynamic_recursive seqdp recdp

generator: generator.c 
	$(CC) -o $@ $<

read_instance: read_instance.c 
	$(CC) -o $@ $< -lrt

greedy: greedy.c baselib.o 
	$(CC) $(CFLAGS) -o $@ $< baselib.o -lrt 

brute_force: brute_force.c baselib.o
	$(CC) $(CFLAGS) -o $@ $< baselib.o -lrt 

dynamic_recursive: dynamic_recursive.c baselib.o
	$(CC) $(CFLAGS) -o $@ $< baselib.o -lrt 

seqdp: seqdp.c baselib.o
	$(CC) $(CFLAGS) -o $@ $< baselib.o -lrt 

recdp: recdp.c baselib.o
	$(CC) $(CFLAGS) -o $@ $< baselib.o -lrt 

baselib.o: baselib.c
	$(CC) -c $<

clean:
	-rm greedy 
	-rm brute_force 
	-rm read_instance
	-rm generator
	-rm baselib.o 
	-rm recdp 
	-rm seqdp 

.PHONY: clean
