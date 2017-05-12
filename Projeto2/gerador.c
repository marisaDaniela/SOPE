#include "resources.h"

// THREAD PARA GERAR PEDIDOS

// THREAD PARA ESCUTAR OS PEDIDOS REJEITADO

int main(int argc, char * argv[])
{
	int numRequests = atoi(argv[1]);
	int duration = atoi(argv[2]);
	int i;

	int fd; // descritor para o fifo

// Exemplo do professor

	if (mkfifo(FIFO_1,0660)<0)
 		if (errno==EEXIST) 
 			printf("FIFO '/tmp/entrada' already exists\n");
 		else 
 			printf("Can't create FIFO\n");
	else 
		printf("FIFO '/tmp/entrada' sucessfully created\n");

	if ((fd=open(FIFO_1,O_WRONLY)) !=-1)
 		printf("FIFO '/tmp/entrada' openned in O_WRONLY mode\n");

// ciclo para escrever no fifo pedidos aleatorios

	for(i = 0; i < numRequests; i++)
	{
	  Request *r = generateRequest(duration);
	  //printf("struct ID: %d\n", r->p);
	  //printf("struct gender: %s\n", &r->g);
	  //printf("struct duration: %d\n", r->t);
	  //printf("struct denials: %d\n", r->refusedTimes);
	  write(fd,r,sizeof(*r)); //Escrever no fifo
	}
	close(fd);

}
