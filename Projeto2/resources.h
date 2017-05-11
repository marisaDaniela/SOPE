#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>
#include <time.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>

int ID = 1;

typedef struct Request
{
	int p; // numero de serie do pedido 
	char g; // gender (F/M)
	int t; // duracao da utilizacao do pedido (ms)
	int refusedTimes;
} Request;

Request* generateRequest(int t) 
{
	Request* r = malloc(sizeof(Request));

	r->p = ID++;
	r->g = (rand()%2) ? 'M' : 'F';
	r->t = rand() % t + 1;
	r->refusedTimes = 0;

	return r;
}




