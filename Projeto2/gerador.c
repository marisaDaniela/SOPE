#include "resources.h"

#define LOG_FILE  "/tmp/ger.pid"

FILE * file;
int DURATION;
int DISCARDED = 0;

Request* requests[100]; // Lista para pedidos

/**
Esta thread sera responsavel por efectuar a geração aleatoria de pedidos e
apresenta-los a sauna;
*/
void* thrCreateRequest(void * numRequests)
{
	int num = *(int*) numRequests;

	int fd; // descritor para o fifo

// Create log file (inacabado!)

	file = fopen(LOG_FILE,"w");
	if (file == NULL)
		printf ("Couldn't create %s file\n", LOG_FILE);
	else
		fprintf(file,"   inst   –   pid    –     p:    g     –    dur    –    tip   \n");
	fclose(file);

// cria fifo de entrada 

	if (mkfifo(FIFO_1,0660)<0)
 		if (errno==EEXIST) 
 			printf("FIFO '/tmp/entrada' already exists\n");
 		else 
 			printf("Can't create FIFO\n");
	else 
		printf("FIFO '/tmp/entrada' sucessfully created\n");

// abre fifo de entrada

	if ((fd=open(FIFO_1,O_WRONLY)) !=-1)
 		printf("FIFO '/tmp/entrada' openned in O_WRONLY mode\n");

// geracao de pedidos aleatorios 

	for (int i = 0; i < num; i++)
	{
		Request* person = malloc(sizeof(Request));

		person->p = ID++;
		person->g = (rand()%2) ? 'M' : 'F';
		person->t = rand() % DURATION + 1;
		person->refusedTimes = 0;

		requests[i] = person;
	}

// colocar os pedidos no fifo de entrada

	for(int i = 0; i < num; i++)
	{
	  Request *r = requests[i];
	  write(fd,r,sizeof(*r)); //Escrever no fifo
	}

	close(fd);
  	pthread_exit(NULL);
}

/**
Este thread  vai ser responsavel por escutar os pedidos rejeitados e os recolocar na fila de pedidos (no caso de o
numero de rejeicoes de um dado pedido não exceder 3); 
no caso de ser igual a 3, descarta o pedido!
*/

void * thrRejectHandler(void * arg)
{
	int fd;
	Request * r = malloc(sizeof(Request));

	while((fd = open(FIFO_2, O_RDONLY)) == -1)
	{
		if (errno == ENOENT) // no such file or directory //https://www.gnu.org/software/libc/manual/html_node/Error-Codes.html
		{	 
			printf("No such file or directory!\n");
		}
		sleep(1); 
	}

	while(read(fd, r, sizeof(Request)) != 0)
	{
		printf("numRequest: %d\nGender: %c\nDuration: %d\nRefusedTimes: %d\n\n", r->p, r->g, r->t, r->refusedTimes);
		//NUMREQ = NUMREQ+1;
		if (r == NULL)
		{
			printf("Fifo 'tmp/rejeitados' empty!");
			exit(1);
		}
		if(r->refusedTimes >= 3)
		{
			// descarta
			DISCARDED++;
		}
		else
		{
			// volta a por na fila
			// Escrever no fifo de entrada
			// Todo: open(fifo1)
			// 		 write(fifo1)
		}
	}
	close(fd);
}

/**
Main function: responsavel por criar as threads

*/
int main(int argc, char * argv[])
{
	int numRequests = atoi(argv[1]); // numero de pedidos
	DURATION = atoi(argv[2]); // duracao maxima

	time_t t;
  	srand((unsigned) time(&t)); // por causa da cena random

  	if(argc != 3)
  	{
   		printf("Wrong number of arguments! Usage: %s <number of requests> <max duration>\n", argv[0]);
    	exit(1);
  	}
	

	pthread_t tid1, tid2;

	pthread_create(&tid1, NULL, thrCreateRequest, (void*) &numRequests);
	pthread_create(&tid2, NULL, thrRejectHandler, NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2, NULL);

	return 0;

}

