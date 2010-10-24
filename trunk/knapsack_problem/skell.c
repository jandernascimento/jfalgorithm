#include <stdio.h>
#include <stdlib.h>
#include "timer.h" 
#include "baselib.h"

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


