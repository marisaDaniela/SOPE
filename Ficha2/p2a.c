#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/times.h>

#define MAX_BUF 512

int main(int argc, char* argv[]){

    //medir os tempos (2c)
	clock_t programStart;
	clock_t programEnd;
	struct tms t;
	long clockTicks = sysconf(_SC_CLK_TCK);
	//**************************************
	
	if(argc != 3)
	{
		printf("Usage: <source><destination>\n");
		return 1;
	}
	
	FILE *f1;
	FILE *f2;
	char buf[MAX_BUF];
	
	f1 = fopen(argv[1], "r");
	f2 = fopen(argv[2], "w");
	
	//
	programStart = times(&t);
	
	while ((fgets(buf, MAX_BUF, f1)) != NULL) 
	{
		fputs(buf, f2);
	}
	
	//
	programEnd = times(&t);
	
	printf("Complete! ;) \n\n");
	
	////**************************************
	printf("Real time: %4.2f s\n", (double) (programEnd - programStart) / clockTicks);
	printf("User time: %4.2f s\n", (double) t.tms_utime / clockTicks);
	printf("System time: %4.2f s\n", (double) t.tms_stime / clockTicks);
	
	return 0;
}
