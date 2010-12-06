#include <stdio.h>
#include <stdlib.h>
#include "timer.h" 
#include "baselib.h"
#include "string.h"

instance_t instance;

int **knap;
int **take;

int max(int num1,int num2){

  if(num1>num2) return num1;
  else return num2;

}

int secdp(instance_t instance){

  int i=0;
  for(i=0;i<instance.W;i++) knap[0][i]=0;

  int k=0;
  for(k=1;k<=instance.n;k++){

    knap[k][0]=0;
    int y=0;
    for(y=1;y<=instance.W;y++){
      if(y<instance.w[k-1]){
        knap[k][y]=knap[k-1][y];
      }else if (y>=instance.w[k-1]){
	knap[k][y]=max(knap[k-1][y],instance.p[k-1]+knap[k-1][y-instance.w[k-1]]);
	if((knap[k-1][y])<(instance.p[k-1]+knap[k-1][y-instance.w[k-1]])){
		take[k][y]=1;
	}else {
		take[k][y]=0;
	}
      }
    }

  }

  return knap[instance.n][instance.W];

}

void showSelectedItens(int n, int w, instance_t instance){

	int k=w-1;
	int last_x=n;
	do{
		int x; 
		for(x=last_x-1;x>=0;x--){
			last_x=x;
			if(take[x][k]==1){
				printf("Item %i has profit %i and weigth %i\n",x,instance.p[x-1],instance.w[x-1]);
				k=k-instance.w[x-1];
				break;
			}
		}

	}while(k>0);


}

void init_matrix(int n, int W){

   knap=malloc(sizeof(int *)*n);
   take=malloc(sizeof(int *)*n);

   int i=0;
   for(i=0;i<n;i++){
     knap[i]=malloc(sizeof(int)*W);
     take[i]=malloc(sizeof(int)*W);
   }
   
   for(i=0;i<n;i++){
     int j=0;
     for(j=0;j<W;j++){
       knap[i][j]=0;
       take[i][j]=0;
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

int main ( int argc, char* argv[] )
{  int * pack;
   int * weight, * value;
   int k, n, maxWeight;

   if ( argc != 2 ) {
	printf ("./seqdp instance_file\n");
	return 0 ;
   }

BEGIN_MAIN

   instance_t instance ;
   read_instance ( argv[1], &instance ) ;

BEGIN_EXPERIMENT

   init_matrix(instance.n+1,instance.W+1);

   int price=secdp(instance);
   showSelectedItens(instance.n+1,instance.W+1,instance);
   printf("BAG AGGREGATE VALUE; weight:%i price:%i\n",-1,price);


END_EXPERIMENT

   free_matrix(instance.n+1,instance.W+1);

END_MAIN
   return 0;
}
