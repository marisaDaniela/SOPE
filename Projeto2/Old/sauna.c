#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/times.h>
#include <errno.h>
#include <pthread.h>

#define MAX_MSG_LEN 20

//SAUNA
	/*
	FIFO
		/tmp.entrada recebe e encaminha para lugares vagos
		se nao forem aceites:
			/tmp/rejeitados
		se forem do mesmo genero
			espera que fique vago


	THREADS
		1) Principal: receçao e processamento de pedidos (acesso a sauna e rejeiçao)
				quando nao houver mais pedidos (FIFO fecha no lado da escrita) aguarda que todos os seus threads terminem e imprime estatisticas antes de terminar
		2) Esperam pela conclusao de cada pedido na sauna
				antes de terminarem notificam a thread principal que ha um lugar livre

	FICHEIROS TXT:
		/tmp/bal.pid

		documentar o desenrolar da atividade

		inst - pid - tid - p : g - dur - tip   ..... tip: RECEBIDO, REJEITADO, SERVIDO
	*/

char*  FIFO_1 = "/tmp/entrada";
char*  FIFO_2 = "/tmp/rejeitados";

void *receivedRequest(void *threadId);

int main(int argc, char * argv[])
{
	if(argc != 2)
        {
            printf("Wrong number of arguments! Usage: <numPlaces>\n");
            exit(1);
        }

   	/*clock_t start; 
 	struct tms t; 
 	long ticks; 
 	int k; 
	start = times(&t);                    */   /* início da medição de tempo */ 
	/*ticks = sysconf(_SC_CLK_TCK); 
 	
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
	
        */
   	
        int numPlaces = atoi(argv[1]);
        
        pthread_t tid[numPlaces];
        int rc, t; // return code from pthread_create
        for(t=1; t<=numPlaces; t++) 
        {
            rc = pthread_create(&tid[t-1], NULL, receivedRequest, (void *)t);
            if(rc)
            {
                printf("ERRO; return code from pthread_create() if %d\n", rc);
                exit(1);
            }
        }
        pthread_exit(NULL);
}

void *receivedRequest(void *threadId) 
{
    int fd;
    char str[MAX_MSG_LEN];
    
    if ((fd = open(FIFO_1, O_RDONLY | O_NONBLOCK)) == -1)
    {
        perror("Oops!!");
        exit(1);        
    }
    
    while(1)
    {
    	if(read(fd, &str, MAX_MSG_LEN)>0)
    	{
    		printf("%s\n",str );
    	} //?
    }
    
    close(fd);
  
    //inc
    
    
    
}
























