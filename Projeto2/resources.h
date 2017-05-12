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

#define TICKS_PER_SEC  60L
#define NUM_MAX_REQ 100


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

// Vai gerar pedidos aleatorios: ex: 1 F 1 0