#include <stdio.h>
#include <stdlib.h>
#include "timer.h" 
#include "baselib.h"

instance_t instance;

int exist_in_domain(int val, int dados[],int size){

	int j=0;
	for(j=0;j<size;j++){
		if(val==dados[j]) return 1;;
	}
	
	return 0;

}

int factorial(int val){

	if(val==1 || val==0 ) return 1;

	return val*factorial(val-1);

}


instance_t generate_instance(int* combination_set,instance_t instance){

	//int counter=0;
	//for(counter=0;counter<instance.n&&combination_set[counter]!=-1;counter++);

	instance_t result;
	result.n=0;
	result.W=instance.W;
	
	int j=0;
	for(j=0;j<instance.n;j++){
		if(combination_set[j]==-1) continue;
		unsigned int p;
		unsigned int w;
		p=instance.p[combination_set[j]];
		w=instance.w[combination_set[j]];
		instance_t one;
		one.w = (unsigned int*) malloc ( sizeof(unsigned int) ) ;
		one.p = (unsigned int*) malloc ( sizeof(unsigned int) ) ;
		one.w[0]=w;
		one.p[0]=p;
		
		result=add_instance(&result,one);	
	}

	return result;

}

int* best_combination_set;
unsigned int best_combination_price=0;
unsigned int best_combination_weight=0;
int is_set=0;

void print_combination(int combination[],int size){

	int j=0;	
	for(j=0;j<size;j++){
		printf("%i,",combination[j]);
	}
	printf("\n");
}

void test_combination(int combination[],int size){

	int tmp_combination[size];

	if(!is_set){
		best_combination_set=malloc(size*sizeof(int));
		best_combination_price=0;
		best_combination_weight=0;		
		is_set=1;
	}

	//printf("Test:");

	int j=0;
	unsigned int total_weight=0;
	unsigned int total_price=0;

	for(j=0;j<size;j++){
		
		//printf("%i, ",combination[j]);
	 	unsigned int tmp=(total_weight+(instance.w[combination[j]]));
		if((total_weight+(instance.w[combination[j]]))>instance.W){ 
			tmp_combination[j]=-1;
		}else{
			total_weight+=(instance.w[combination[j]]);
			total_price+=(instance.p[combination[j]]);
			tmp_combination[j]=combination[j];
		}
	}
	
	if(total_price>best_combination_price){
		for(j=0;j<size;j++){
			best_combination_set[j]=tmp_combination[j];
		}
		best_combination_price=total_price;
		best_combination_weight=total_weight;
	}

	//printf(" - SET \n");

}

int combinate(int itens,int dados[],int size,int dep){
	if(dep==itens){
		test_combination(dados,size);
		return 0;
	}
	int i;
	for (i=0;i<itens;i++){
		
		if(exist_in_domain(i,dados,size)) continue;
				
		int novo[size+1];
		
		int j=0;
		for(j=0;j<size;j++){
			novo[j]=dados[j];
		}
		novo[size]=i;

		combinate(itens,novo,size+1,dep+1);
	}

}

int main ( int argc, char** argv ) {
BEGIN_MAIN
	if ( argc != 2 ) {
		printf ("./read_instance instance_file\n");
		return 0 ;
	}
	read_instance ( argv[1], &instance ) ;
BEGIN_EXPERIMENT

	int dado[0];	
	unsigned int size=instance.n;
	combinate(size,dado,0,0);
	
	//printf("------ O melhor conjunto -----\n");
	instance_t result=generate_instance(best_combination_set,instance);
	//print_combination(best_combination_set,size);
	print_instance ( &result ) ;
	//printf("------ /O melhor conjunto -----\n");
	//print_instance ( &instance ) ;
END_EXPERIMENT
	free_instance ( &instance ) ;
END_MAIN
	return 0 ;
}


