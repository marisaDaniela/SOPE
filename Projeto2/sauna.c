#include "resources.h"

char SAUNA_G; // genero atual da sauna
int CAPACITY;
int OCCUPIED = 0;

int fd1, fd2; // descritores para os fifos
clock_t start;

/**
Para guardar as estatisticas
inst – pid – tid – p: g – dur – tip
*/
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//inst – pid – tid – p: g – dur – tip
int toFile(int tid, Request * req, char* message)
{
	char LOG_FILE[] = "/tmp/bal.";
	int a = getpid();
	char b[sizeof(a)];

	sprintf(b, "%d", a);

	FILE *f;
	strcat(LOG_FILE, b);

	f = fopen(LOG_FILE, "a+");

	if (f == NULL){
		printf("\nError opening file %s!", LOG_FILE);
		return -1;
	}

	clock_t current = times(NULL);
	clock_t timeDif = (current - start) * TICKS_PER_SEC;
	pthread_mutex_lock(&mutex);
	fprintf(f, "%li - %d - %d - %d: %c - %d - %s\n", timeDif, getpid(), tid , req->p, req->g, req->t, message);
	pthread_mutex_unlock(&mutex);

	fclose(f);
	return 0;
}

/**
Thread responsavel por colocar um pedido na sauna durante i ms. 
Sempre que uma pessoa entrar na sauna cria esta thread. 
Responsavel por enviar uma notificaçao a thread principal quando o tempo do pedido acaba
*/
void * thrfunc (void * arg)
{
	Request* r = (Request*) arg;
	printf("------->>>>>>>Put request in sauna...\n");
	printRequestInfo(r);
	pthread_mutex_lock(&mutex);
	OCCUPIED++;
	pthread_mutex_unlock(&mutex);
	int i = *(int*) arg;
	i = i*1000;
	usleep(i);
	pthread_mutex_lock(&mutex);
	OCCUPIED--;
	pthread_mutex_unlock(&mutex);
	return arg;
}

/**
Esta thread vai ser responsavel por:
	.abrir fifo_1
	.ler fifo_1
	.mkfifo 2
	.escrever fifo_2
	.putIntoSauna
*/
void *thrRequestsHandler(void *arg)
{
	if ((fd1=open(FIFO_1,O_RDONLY)) !=-1)
 		printf("FIFO '/tmp/entrada' openned in O_RDONLY mode\n");

 	// cria fifo dos rejeitados

	if (mkfifo(FIFO_2,0660)<0)
 		if (errno==EEXIST) 
 			printf("FIFO '/tmp/rejeitados' already exists\n");
 		else 
 			printf("Can't create FIFO\n");
	else 
		printf("FIFO '/tmp/rejeitados' sucessfully created\n");

	while(1) 
	{

		Request *r = malloc(sizeof(Request));

		if(read(fd1, r, sizeof(Request)) != 0)
		{
			if (r == NULL)
			{
				printf("Fifo 'tmp/entrada' empty!");
				exit(1);
			}
			printf("Imprime pedidos todos:\n");
			printRequestInfo(r);
			
			if(OCCUPIED < CAPACITY) // Enquanto houver lugares livres
			{
				if((r->g == SAUNA_G) || (SAUNA_G == 'A')) // Se for do mesmo sexo ou sauna vazia 
				{
					SAUNA_G = r->g; // atualiza genero da sauna
					
					// criar a thread para por na sauna
					pthread_t tid;
					toFile(tid, r, "RECEBIDO");
					pthread_create(&tid, NULL, thrfunc,(void*)r);


				}
				else // rejeitados
				{
						// Abertura do FIFO '/tmp/rejeitados'
				  	if ((fd2=open(FIFO_2,O_WRONLY)) !=-1)
				  		{
				  			printf("FIFO '/tmp/rejeitados' openned in O_WRDONLY mode\n");
						}

					r->refusedTimes++;
					write(fd2, r, sizeof(Request)); // escrever nos rejeitados
					close(fd2);
				}
			}
			else
			{
				// sauna full (wait?)
				printf("Sauna full\n");
			}

		}
	}
	pthread_exit(NULL);
	close(fd1);
}


int main(int argc, char* argv[])
{
	CAPACITY = atoi(argv[1]); 				// Numero de lugares da sauna
	SAUNA_G = 'A'; 							// caracter para identificar que a sauna esta vazia

	if(argc != 2)
	{
	  	printf("Wrong number of arguments! Usage: %s <capacity>\n", argv[0]);
	  	exit(1);
	}

	pthread_t tid;

	pthread_create(&tid, NULL, thrRequestsHandler, NULL);

	pthread_join(tid, NULL);

	pthread_exit(NULL);

}
