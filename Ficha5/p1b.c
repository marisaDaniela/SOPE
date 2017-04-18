#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <stdlib.h>
#include <wait.h>

#define READ 0
#define WRITE 1

typedef struct {
	int a;
	int b;
} numbers;

int main()
{
	int fd[2];
	pid_t pid;

	numbers n;

	pipe(fd);

	pid = fork();

	
	if(pid > 0) //pai
	{
		close(fd[READ]);
		printf("x y? ");
		scanf("%d%d", &n.a, &n.b);
		
		if (write(fd[WRITE], &n, sizeof(n)) < 0)
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
		
		while (read(fd[READ], &n, sizeof(n)) < 1)
		{
		}
		
		
		printf("\t%d + %d = %d\n", n.a, n.b, n.a + n.b);
		printf("\t%d - %d = %d\n", n.a, n.b, n.a - n.b);
		printf("\t%d * %d = %d\n", n.a, n.b, n.a * n.b);
		
		if (n.b == 0)
		{
			sprintf(divisionResult, "NaN");
		}
		else
		{
			sprintf(divisionResult, "%.4f", (double) n.a / n.b);
		}
		
		printf("\t%d / %d = %s\n", n.a, n.b, divisionResult);
		
		close(fd[READ]);

	}
}