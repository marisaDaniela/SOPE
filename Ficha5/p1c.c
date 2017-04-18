#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <stdlib.h>
#include <wait.h>

#define READ 0
#define WRITE 1
#define LENGTH 64

int main()
{
	int fd[2];
	pid_t pid;
	char n[LENGTH];

	pipe(fd);

	pid = fork();

	
	if(pid > 0) //pai
	{
		close(fd[READ]);
		printf("x y? ");
		fgets(n, LENGTH,stdin);
		
		if (write(fd[WRITE], &n, LENGTH * sizeof(char)) < 0)
		{
			perror("pipe write failed: ");
			exit(1);
		}
	
		close(fd[WRITE]);
		wait(NULL);
	}

	else //filho
	{
		char divisionResult[16];
		
		close(fd[WRITE]);
		
		while (read(fd[READ], &n, LENGTH * sizeof(char)) < 1)
		{
		}

		int a;
		int b;
		
		sscanf(n, "%d%d", &a, &b);
		
		printf("\t%d + %d = %d\n", a, b, a + b);
		printf("\t%d - %d = %d\n", a, b, a - b);
		printf("\t%d * %d = %d\n", a, b, a * b);
		
		if (b == 0)
		{
			sprintf(divisionResult, "NaN");
		}
		else
		{
			sprintf(divisionResult, "%.4f", (double) a / b);
		}
		
		printf("\t%d / %d = %s\n", a, b, divisionResult);
		
		close(fd[READ]);
	}
}