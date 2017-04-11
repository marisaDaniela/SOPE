#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]){
	if(argc != 3){
		printf("Numero errado de parametros");
		return 1;	
	}
	int num1, num2, num;
	int i = 0;
	
	num1 = atoi(argv[1]);
	num2 = atoi(argv[2]);	
    srand(time(NULL));
   //use srand() para garantir que, em cada execução, são geradas sequências de números aleatórios diferentes.
   
   do{
   i++;
   num = rand() %num1;
   printf("%d -> %d\n",i,num);
   }
   while(num != num2); 
   
   return 0;
	

}
