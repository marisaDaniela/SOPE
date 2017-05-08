#include <stdio.h>
#include "gerador.c"


char* INPUT_FIFO = "tmp/entrada";
char* REJECTED_FIFO = "tmp/rejeitados";



int main(int argc, char* argv[]){

	if(argc != 3){
		printf("Wrong number of arguments. Usage:<numRequests><maxTime>\n");
	}

        int numRequests = atoi(argv[1]); //numero de pedidos
	int maxTime = atof(argv[2]); //max duracao de pedido
	
	clock_t start; 
 	struct tms t; 
 	long ticks; 
 	int k; 
	start = times(&t);                       /* início da medição de tempo */ 
	ticks = sysconf(_SC_CLK_TCK); 
 	
	Args* write = malloc(sizeof(Write_args));
	write->charpointer = INPUT_FIFO
	write->start = start;
	write->t = t;
       

	pthread_t[numRequests] tid;


	int i;
	int cycleL = numRequests * 2;
	for(i = 0; i < numResquests; i+=2){
         
	pthread_create(&tid[i], NULL, write_person, (Args) write);
	// pthread_create(&tid[i+1], NULL, process_person,           //a thread responsavel por gerir entrada de clientes na sauna
	
	
	 
}
