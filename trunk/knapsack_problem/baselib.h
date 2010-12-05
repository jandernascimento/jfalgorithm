#include <stdio.h>
#include <stdlib.h>
#include "timer.h" 

typedef struct {
	unsigned int n ; // number of items
	unsigned int* w ; // weights
	unsigned int* p ; // profits
	unsigned int W ; // bag capacity
} instance_t ;


void switch_position(instance_t* instance,int from, int to);

instance_t add_instance (
	instance_t* instance,instance_t element
);

void read_instance (
	char* instance_file,
	instance_t* instance
);

void print_instance ( instance_t* instance );

void free_instance ( instance_t* instance );

/*
void init_matrix(int n, int W);

void free_matrix(int n, int W);
*/
