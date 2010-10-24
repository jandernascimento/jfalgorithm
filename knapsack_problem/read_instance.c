#include <stdio.h>
#include <stdlib.h>

#include "timer.h" 

typedef struct {
	unsigned int n ; // number of items
	unsigned int* w ; // weights
	unsigned int* p ; // profits
	unsigned int W ; // bag capacity
} instance_t ;

void read_instance (
	char* instance_file,
	instance_t* instance
) {
	FILE* in ;
	in = fopen ( instance_file, "r" ) ;
	if ( in == NULL ) {
		printf ( "error while opening file %s\n", instance_file ) ;
		return ;
	}
	fscanf ( in, "%d", &instance->n ) ;
	instance->w = (unsigned int*) malloc ( instance->n * sizeof(unsigned int) ) ;
	instance->p = (unsigned int*) malloc ( instance->n * sizeof(unsigned int) ) ;
	unsigned int j ;
	for ( j=0; j<instance->n ; ++j ) {
		int tmp ;
		fscanf ( in, "%d %d %d", &tmp, instance->p+j, instance->w+j ) ;
		if ( tmp != j+1 ) {
			printf("bad file format\n");	
			fclose ( in ) ;
			return ;
		}
	}
	fscanf ( in, "%d", &instance->W ) ;
	fclose ( in ) ;
}

void print_instance ( instance_t* instance ) {
	printf ( "n=%d\tW=%d\n", instance->n, instance->W ) ;
	unsigned int j ;
	for ( j=0 ; j<instance->n ; ++j )
		printf ("item %d has profit %d and weigth %d\n", j+1, instance->p[j], instance->w[j] ) ;
}

void free_instance ( instance_t* instance ) {
	free ( instance->p ) ;
	free ( instance->w ) ;
}

int main ( int argc, char** argv ) {
BEGIN_MAIN
	if ( argc != 2 ) {
		printf ("./read_instance instance_file\n");
		return 0 ;
	}
	instance_t instance ;
	read_instance ( argv[1], &instance ) ;
BEGIN_EXPERIMENT
	print_instance ( &instance ) ;
END_EXPERIMENT
	free_instance ( &instance ) ;
END_MAIN
	return 0 ;
}


