#include "resources.h"

#define STATISTICS "/tmp/bal.pid"

// imprimir info do pedido

void printRequestInfo (Request *r)
{
	printf("numRequest: %d\nGender: %c\nDuration: %d\nRefusedTimes: %d\n", r->p, r->g, r->t, r->refusedTimes);
}


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
	int capacity = atoi(argv[1]); 				// Numero de lugares da sauna
  	int fd;			

  	Request *r = malloc(sizeof(Request));

	if(argc != 2)
	{
	  	printf("Wrong number of arguments! Usage: %s <capacity>\n", argv[0]);
	  	exit(1);
	}

	while((fd = open(FIFO_1, O_RDONLY)) == -1)
	{
		if (errno == ENOENT) // no such file or directory //https://www.gnu.org/software/libc/manual/html_node/Error-Codes.html
		{ 
			printf("No such file or directory!\n");
		}
		sleep(1); 
  	}
  	while(read(fd, r, sizeof(Request)) != 0)
  	{
    	if (r == NULL) 
    		exit(1);
    	printRequestInfo(r);
    	
  	}

}
