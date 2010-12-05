#include <stdio.h>
#include <stdlib.h>
#include "timer.h" 
#include "baselib.h"



void switch_position(instance_t* instance,int from, int to){
	//switching p
        unsigned int holder_p=instance->p[to];	
	instance->p[to]=instance->p[from];
	instance->p[from]=holder_p;

	//switching w
        unsigned int holder_w=instance->w[to];	
	instance->w[to]=instance->w[from];
	instance->w[from]=holder_w;
}

instance_t add_instance (
	instance_t* instance, 
	instance_t element
) {

	instance_t newone;

	newone.w = (unsigned int*) malloc ( (instance->n+1)*sizeof(unsigned int) ) ;
	newone.p = (unsigned int*) malloc ( (instance->n+1)*sizeof(unsigned int) ) ;
	newone.n = instance->n+1;
	newone.W = instance->W;
	int j;
	for ( j=0; j<instance->n ; ++j ) {
		newone.p[j]=instance->p[j];
		newone.w[j]=instance->w[j];
	}
	newone.w[newone.n-1]=element.w[0];
	newone.p[newone.n-1]=element.p[0];

	//pode ser um erro comentar esta linha
	//free_instance(instance);

	return newone;

}

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
	
	unsigned int total_weight=0;
	unsigned int total_price=0;
	for ( j=0 ; j<instance->n ; ++j ){
		//printf("valor1:%i valor2:%i == %f\n",instance->p[j],instance->w[j],(double)instance->p[j]/(double)instance->w[j]); 
		//printf ("item %d has profit %d and weigth %d \n", j+1, instance->p[j], instance->w[j]) ;
		printf ("item %d has profit %d and weigth %d profit/weigth %f\n", j+1, instance->p[j], instance->w[j],(float)instance->p[j]/(float)instance->w[j]) ;
		total_weight+=instance->w[j];
		total_price+=instance->p[j];
	}
	printf("BAG AGGREGATE VALUE; weight:%i price:%i\n",total_weight,total_price);
}

void free_instance ( instance_t* instance ) {
	free ( instance->p ) ;
	free ( instance->w ) ;
}

/*
void init_matrix(int n, int W){

   knap=malloc(sizeof(int *)*n);

   int i=0;
   for(i=0;i<n;i++){
     knap[i]=malloc(sizeof(int)*W);
   }
   
   for(i=0;i<n;i++){
     int j=0;
     for(j=0;j<W;j++){
       knap[i][j]=0;
     }
   }
   

}

void free_matrix(int n, int W){

   int i=0;
   for(i=0;i<n;i++){
     free(knap[i]);
   }

   free(knap);

}
*/

/*
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

*/
