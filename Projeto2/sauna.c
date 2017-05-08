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


	pthread_t[numRequests] tid;


	/*int 
	while()*/
	pthread_create(&tid[], NULL, write_person, char * INPUT_FIFO);
	
	
	 
}
