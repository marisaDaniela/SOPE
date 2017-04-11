#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	if(argc != 3){
		printf("Numero errado de parametros");
		return 1;	
	}
	
	//Para o p8b
	clock_t start, end;
	struct tms t;
	long ticks;
	start = times(&t);   			// Inicio da medicao do tempo
	ticks = sysconf(_SC_CLK_TCK);
	
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
   
   
   end = times(&t);
   
   printf("Clock: %4.2fss\n", (double)(end-start)/ticks);
   printf("User time: %4.2f s\n", (double)t.tms_utime/ticks);
   printf("System time: %4.2f s\n", (double)t.tms_stime/ticks);
   printf("Children user time: %4.2f s\n", (double)t.tms_cutime/ticks);
   printf("Children system time: %4.2f s\n", (double)t.tms_cstime/ticks);
   
   return 0;
	

}
