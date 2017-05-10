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

//GERADOR: 
	/*
	FIFOS: /tmp/entrada
		   /tmp/rejeitados

	THREADS:
		1) Gerar pedidos aleatoriamente e apresenta-los a sauna
		2) Escutar os pedidos rejeitados e recoloca-los na fila de pedidos (se rejeicao>3-->descarta)

	FICHEIROS txt:
		/tmp/ger.pid
		Documentar toda a atividade
		Estatiscitcas: num pedidos gerados
					   num rejeiçoes recebidas
					   num rejeiçoes descartadas 
					      						----por genero

					    inst - pid - p : g - dur - tip    ------ tip : PEDIDO / REJEITADO / DESCARTADO
*/

int ID = 1;

char*  FIFO_1 = "/tmp/entrada";
char*  FIFO_2 = "/tmp/rejeitados";

typedef struct Person 
{
	int id; 
	char gender;
	int time;
	int refusedTimes;
} Person;

typedef struct Args 
{
	char * charpointer;
	clock_t start;
	struct tms t; 
} Args;

// Gerar pedidos aleatoriamente

Person* generatePerson(int maxTime) 
{
	Person* person = malloc(sizeof(Person));

	person->id = ID++;
	person->gender = (rand()%2)? 'M' : 'F';
	person->time = rand() % maxTime + 1;
	person->refusedTimes = 0;

	return person;
}

//Gerar pedidos aleatorios e apresenta-los a sauna, i think 
void* makeRequest(int *maxTime)
{
	int fd; 
	int value = *(int *) maxTime; 
	if(mkfifo(FIFO_1, O_RDWR ) != 0){ // nao sei se vao ser estas as permissoes do fifo de entrada 
		perror("Can't create FIFO 'tmp/entrada'");
		exit(1);
		}	
		
	if((fd = open(FIFO_1, O_WRONLY | O_NONBLOCK))==-1){
		perror("Oops!!");
		exit(1);
		}
	
	Person * p = generatePerson(value);

	write(fd, p, sizeof(p));
}


void rejectedRequest()
{
	
    
    
    
    
    
    
    

} 



int main(int argc, char* argv[])
{

	if(argc != 3)
        {
            printf("Wrong number of arguments! Usage: <numRequests> <maxTime>\n");
	}

    int numRequests = atoi(argv[1]); //numero de pedidos
	int maxTime = atof(argv[2]); //max duracao de pedido

	pthread_t tid1, tid2;

	pthread_create(&tid1, NULL, makeRequest, &maxTime); //thread1
	pthread_create(&tid2, NULL, rejectedRequest, NULL); //thread2

	/*
	char * usage = (Args) arg->charpointer;
	clock_t start = (Args) arg->start;
	struct tms t = (Args) arg->t
	*/

	

	//double delta = times(&t) - start;  //isto é o delta entre inicio do programa e corrente tempo para escrever no log.
}