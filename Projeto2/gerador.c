#include "resources.h"

#define LOG_FILE  "/tmp/ger.pid"

FILE * file;
int DURATION;
int DIS_M, DIS_F;

// THREAD PARA GERAR PEDIDOS

Request* requests[100]; // Lista para pedidos

void* thrCreateRequest(void * numRequests)
{
	int num = *(int*) numRequests;

	int fd; // descritor do FIFO

// Create log file

	file = fopen(LOG_FILE,"w");
	if(file == NULL)
            printf ("Couldn't create %s file\n", LOG_FILE);
	else
            fprintf(file,"   inst   –   pid    –     p:    g     –    dur    –    tip   \n");
	fclose(file);

// Exemplo do professor
// Criação do FIFO '/tmp/entrada' com validação de erros

	if (mkfifo(FIFO_1, 0660) < 0) 
        {
 		if (errno == EEXIST) 
                {
 			printf("FIFO '/tmp/entrada' already exists!\n");
                }
 		else 
                {
 			printf("Can't create FIFO!\n");
                }
        }
	else 
        {
		printf("FIFO '/tmp/entrada' sucessfully created!\n");
        }

// Abertura do FIFO '/tmp/entrada'

        fd = open(FIFO_1, O_WRONLY | O_NONBLOCK);
	if(fd == -1)
        {
            if(errno != ENXIO)
            {
 		printf("Error opening '/tmp/entrada' in O_WRONLY mode.\n");
                exit(1);                
            }
        }

// Escrita no FIFO '/tmp/entrada'
        
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
	    write(fd,r,sizeof(*r));
	}
	
	pthread_exit(NULL);
}

// THREAD PARA ESCUTAR OS PEDIDOS REJEITADOS

void* thrHandlerRejected(void *arg) //mete um cliente de novo na fila
{
	int fd, fd2;
        Request request;
        
	//Request * r = (Request*) arg;
        Request* r = malloc(sizeof(Request));

	if ((fd = open(FIFO_2,O_WRONLY)) != -1)
 		printf("FIFO '/tmp/entrada' openned in O_WRONLY mode!\n"); //entrada?
        
 	/*if ((fd2 = open(FIFO_1,O_WRONLY)) != -1) // COMENTEI!
 		printf("FIFO '/tmp/entrada' openned in O_WRONLY mode!\n");*/
        
        if ((fd2 = open(FIFO_1,O_RDONLY)) != -1) // ACRESCENTEI!
 		printf("FIFO '/tmp/rejeitados' openned in O_RDONLY mode!\n"); //rejeitados?

        while(read(fd2, r, sizeof(Request)) > 0)
        {
            r->refusedTimes++;
            
            request.p = r->p;
            request.g = r->g;
            request.t = r->t;
            request.refusedTimes = r->refusedTimes;
            
            if(r->refusedTimes < 3)
            {
                printf("Pedido com id %d foi rejeitado! Será recolocado na fila de pedidos e tentará novamente a sua sorte!\n", r->p);
                write(fd, &request, sizeof(Request));            
            }
            else
            {
                    printf("Pedido com id %d foi descartado! Terá de voltar outro dia!\n", r->p);
            }
        }
                
    	//write(fd2, r, sizeof(*r));  // Volta a colocar na fila, i guess
   
        close(fd);
        close(fd2);
        free(arg);
        free(r);
  	pthread_exit(NULL);
}

int main(int argc, char * argv[])
{
    int numRequests = atoi(argv[1]);
    DURATION = atoi(argv[2]);

    time_t t;
    srand((unsigned) time(&t));

    if(argc != 3)
    {
        printf("Wrong number of arguments! Usage: %s <number of requests> <max duration>\n", argv[0]);
        exit(1);
    }
	
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, thrCreateRequest, (void*) &numRequests);
   // pthread_create(&tid2, NULL, thrHandlerRejected, NULL);

    pthread_join(tid1,NULL);
   // pthread_join(tid2,NULL);

    return 0;

}
