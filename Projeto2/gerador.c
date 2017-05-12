#include "resources.h"

#define LOG_FILE  "/tmp/ger.pid"

FILE * file;
int DURATION;
// THREAD PARA GERAR PEDIDOS

Request* requests[100]; // Lista para pedidos

void* thrCreateRequest(void * numRequests)
{
	int num = *(int*) numRequests;

	int fd; // descritor para o fifo

// Create log file

	file = fopen(LOG_FILE,"w");
	if (file == NULL)
		printf ("Couldn't create %s file\n", LOG_FILE);
	else
		fprintf(file,"   inst   –   pid    –     p:    g     –    dur    –    tip   \n");
	fclose(file);

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

	for (int i = 0; i < num; i++)
	{
		Request* person = malloc(sizeof(Request));

		person->p = ID++;
		person->g = (rand()%2) ? 'M' : 'F';
		person->t = rand() % DURATION + 1;
		person->refusedTimes = 0;

		requests[i] = person;
	}

	for(int i = 0; i < num; i++)
	{
	  Request *r = requests[i];
	  write(fd,r,sizeof(*r)); //Escrever no fifo
	}
  pthread_exit(NULL);
}

// THREAD PARA ESCUTAR OS PEDIDOS REJEITADO

int main(int argc, char * argv[])
{
	int numRequests = atoi(argv[1]);
	DURATION = atoi(argv[2]);

	time_t t;
  	srand((unsigned) time(&t));

  	if(argc != 3)
  	{
   		printf("Wrong number of arguments. USAGE: program_name <number of requests> <max duration>\n");
    	exit(1);
  	}
	

	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, thrCreateRequest, (void*) &numRequests);

	pthread_join(tid1,NULL);

	return 0;

}