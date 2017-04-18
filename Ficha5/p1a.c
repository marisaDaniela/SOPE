#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <stdlib.h>
#include <wait.h>

#define READ 0
#define WRITE 1

int main()
{
	int fd[2];
	pid_t pid;
	int a, b;

	pipe(fd);

	pid = fork();

	
	if(pid > 0) //pai
	{
		close(fd[READ]);
		printf("x y? ");
		scanf("%d%d", &a, &b);
		
		if (write(fd[WRITE], &a, sizeof(int)) < 0)
		{
			perror("pipe write failed: ");
			exit(1);
		}
		
		if (write(fd[WRITE], &b, sizeof(b)) < 0)
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
		
		while (read(fd[READ], &a, sizeof(a)) < 1)
		{
		}
		
		while(read(fd[READ], &b, sizeof(b)) < 1)
		{
		}
		
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