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


typedef struct Request
{
	int p; // numero de serie do pedido 
	char g; // gender (F/M)
	int t; // duracao da utilizacao do pedido (ms)
	int refusedTimes;
} Resquest;




