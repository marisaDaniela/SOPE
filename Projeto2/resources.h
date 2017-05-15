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
#include <semaphore.h>
#include <sys/sem.h>
#include <string.h>
#include <signal.h>

#define TICKS_PER_SEC  60L


int ID = 1;
char*  FIFO_1 = "/tmp/entrada";
char*  FIFO_2 = "/tmp/rejeitados";

typedef struct 
{
	int p; 
	char g;
	int t;
	int refusedTimes;
} Request;


void printRequestInfo (Request *r)
{
	printf("numRequest: %d\nGender: %c\nDuration: %d\nRefusedTimes: %d\n\n", r->p, r->g, r->t, r->refusedTimes);
}
