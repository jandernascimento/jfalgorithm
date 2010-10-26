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
	
	//switch_position(&instance,1,0);
	//printf("JANDER---> %d\n",instance.p[1]);	
	//instance_t jander;
	//jander.w = (unsigned int*) malloc ( sizeof(unsigned int) ) ;
	//jander.p = (unsigned int*) malloc ( sizeof(unsigned int) ) ;
	//jander.w[0]=400;
	//jander.p[0]=600;	
	//instance=add_instance(&instance,jander);	

BEGIN_EXPERIMENT
	unsigned int size=instance.n;
 	int x;
	for(x=0;x<size;x++){
 		int y;
			for(y=0;y<size;y++){
				double peso_1=(double)instance.p[x]/(double)instance.w[x];
				double peso_2=(double)instance.p[y]/(double)instance.w[y];
				if(peso_1>peso_2){
					switch_position(&instance,x,y);
				}			

			}
	}
	
	unsigned int W=instance.W;
	unsigned int R=W;
	int n=instance.n;
	

	instance_t result;
	result.n=0;
	result.W=W;
	
	int y;
	for(y=0;y<size;y++){
		unsigned int p;
		unsigned int w;
		p=instance.p[y];
		w=instance.w[y];
		
		if(R>w){
			instance_t one;
			one.w = (unsigned int*) malloc ( sizeof(unsigned int) ) ;
			one.p = (unsigned int*) malloc ( sizeof(unsigned int) ) ;
			one.w[0]=w;
			one.p[0]=p;
			
			R-=w;
			
			result=add_instance(&result,one);	
	
		}			

	}	
	print_instance ( &result ) ;

END_EXPERIMENT
	free_instance ( &result ) ;
END_MAIN
	return 0 ;
}


