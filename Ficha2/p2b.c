#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/times.h>
#include <time.h>

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
	
	int f1;
	int f2;
	
	char buf[MAX_BUF];
	
	f1 = open(argv[1], O_RDONLY);
	f2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC | O_SYNC, 0644);
	
	
	int bytesRead = 0;
	int bytesWritten = 0;

    //
	programStart = times(&t);
	
	while ((bytesRead = read(f1, buf, MAX_BUF)) > 0) 
	{
		if ((bytesWritten = write(f2, buf, bytesRead)) <= 0 || bytesRead != bytesWritten) 
		{
			perror(argv[2]);
			close(f1);
			close(f2);
			exit(1);
		}
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
