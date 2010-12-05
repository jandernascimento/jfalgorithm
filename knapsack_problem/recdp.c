#include <stdio.h>
#include <stdlib.h>
#include "timer.h" 
#include "baselib.h"
#include "string.h"

instance_t instance;

int **knap;
int **cache;

int max(int num1,int num2){

  if(num1>num2) return num1;
  else return num2;

}

int recdp(instance_t instance ,int i, int j){
  int k=0;

  if(i==0||j==0){
    return 0;
  }
  
  if(cache[i-1][j-1]!=-1) return cache[i-1][j-1];

  if(instance.w[i-1]>j){
    int value=recdp(instance,i-1,j);
    cache[i-1][j-1]=value;
    return value;
  }

  else if(instance.w[i-1]<=j){
    int value=max(recdp(instance,i-1,j),instance.p[i-1]+recdp(instance,i-1,j-instance.w[i-1]));
    cache[i-1][j-1]=value;
    return value;
  }

}

void init_matrix(int n, int W){

   knap=malloc(sizeof(int *)*n);
   cache=malloc(sizeof(int *)*n);

   int i=0;
   for(i=0;i<n;i++){
     knap[i]=malloc(sizeof(int)*W);
     cache[i]=malloc(sizeof(int)*W);
   }
   
   for(i=0;i<n;i++){
     int j=0;
     for(j=0;j<W;j++){
       knap[i][j]=0;
       cache[i][j]=-1;
     }
   }
   

}

void free_matrix(int n, int W){

   int i=0;
   for(i=0;i<n;i++){
     free(knap[i]);
   //  cache[i];
   }

   free(knap);
   //free(cache);

}

int main ( int argc, char* argv[] )
{  int * pack;
   int * weight, * value;
   int k, n, maxWeight;

   if ( argc != 2 ) {
	printf ("./recdp instance_file\n");
	return 0 ;
   }

BEGIN_MAIN

   instance_t instance ;
   read_instance ( argv[1], &instance ) ;

BEGIN_EXPERIMENT

   init_matrix(instance.n,instance.W);

   int price=recdp(instance,instance.n,instance.W);

   int i=0;
   int counter=0;
   for(i=0;i<instance.n;i++){
     int j=0;
     for(j=0;j<instance.W;j++){
       if(cache[i][j]!=-1) counter++;//printf("processado %i %i\n",i,j);
       //else printf("nao processado %i %i valor:%i\n",i,j,cache[i][j]);
     } 
   }
   printf("ARRAY USAGE: %i/%i\n",counter,instance.n*instance.W);
   printf("BAG AGGREGATE VALUE; weight:%i price:%i\n",-1,price);

   free_matrix(instance.n,instance.W);

END_EXPERIMENT

END_MAIN
   return 0;
}
