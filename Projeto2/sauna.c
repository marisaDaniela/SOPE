#include "resources.h"

#define STATISTICS "/tmp/bal.pid"

char SAUNA_G; // genero atual da sauna
int CAPACITY;
int OCCUPIED = 0;

// imprimir info do pedido

// thread principal: sempre que entrar uma pessoa na sauna vai criar uma thread nova 
// 						arg = tempo
//						entra: incrementa o numero de lugares
//						passa o tempo
//						decrementa quando sai

void thrfunc (void * arg)
{
	OCCUPIED++;
	int i = *(int*) arg;
	i = i*1000;
	usleep(i);
	OCCUPIED--;
}

void printRequestInfo (Request *r)
{
	printf("numRequest: %d\nGender: %c\nDuration: %d\nRefusedTimes: %d\n\n", r->p, r->g, r->t, r->refusedTimes);
}

/*void putIntoSauna(Request *r)
{
	pthread_t tid;
	int fd;
	if(OCCUPIED != CAPACITY)
	{
		if(SAUNA_G == r->g)
		{
			printf("numRequest: %d\nGender: %c\nDuration: %d\nRefusedTimes: %d\n", r->p, r->g, r->t, r->refusedTimes);
			pthread_create(&tid, NULL, thrfunc, (void*) &r->t);
		}
		else
		{
			if ((fd=open(FIFO_2,O_WRONLY)) !=-1)
			{
 				printf("FIFO '/tmp/rejeitados' openned in O_WRONLY mode\n");
			}
			r->refusedTimes++;
			write(fd, r, sizeof(Request));
		}
	}
	else //se a sauna estiver cheia
	{
		printf("FULL!");
	}
}*/

/*int numParkingSpaces, openingTime, freeSpaces;*/
clock_t start;


//inst – pid – tid – p: g – dur – tip
int toFile(int tid, int id, char gender, char* message){
	FILE *f;

	f = fopen(STATISTICS, "a+");

	if (f == NULL){
		printf("\nError opening file %s.", STATISTICS);
		return -1;
	}

	

	clock_t current = times(NULL);
	clock_t timeDif = (current - start) * TICKS_PER_SEC;
	int a = times(NULL) * TICKS_PER_SEC;

	fprintf(f, "%d - %d - %d - %d: %c - %f - %s\n", a, getpid(), tid , id, gender, timeDif, message);

	fclose(f);
	return 0;
}

int main(int argc, char* argv[])
{
	CAPACITY = atoi(argv[1]); 				// Numero de lugares da sauna
  	int fd, fd2;			

  	Request *r = malloc(sizeof(Request));

	if(argc != 2)
	{
	  	printf("Wrong number of arguments! Usage: %s <capacity>\n", argv[0]);
	  	exit(1);
	}

// Criacao do fifo dos rejeitados

	if (mkfifo(FIFO_2,0660)<0)
 		if (errno==EEXIST) 
 			printf("FIFO '/tmp/rejeitados' already exists\n");
 		else 
 			printf("Can't create FIFO\n");
	else 
		printf("FIFO '/tmp/rejeitados' sucessfully created\n");

// Leitura do fifo de entrada

	while((fd = open(FIFO_1, O_RDONLY)) == -1)
	{
		if (errno == ENOENT) // no such file or directory //https://www.gnu.org/software/libc/manual/html_node/Error-Codes.html
		{ 
			printf("No such file or directory!\n");
		}
		sleep(1); 
  	}

  	while((fd2 = open(FIFO_2, O_WRONLY)) == -1)
	{
		if (errno == ENOENT) // no such file or directory //https://www.gnu.org/software/libc/manual/html_node/Error-Codes.html
		{ 
			printf("No such file or directory!\n");
		}
		sleep(1); 
  	}

  	while(read(fd, r, sizeof(Request)) != 0)
  	{
  		//NUMREQ = NUMREQ+1;
    	if (r == NULL)
    	{
    		printf("Fifo 'tmp/entrada' empty!");
    		exit(1);
    	}
    	printRequestInfo(r);
    	write(fd2, r, sizeof(Request));
    	//putIntoSauna(r);


  	}

  	SAUNA_G = r->g; 
  	

  	
}