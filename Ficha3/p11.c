#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(void) 
{
	pid_t pid;
	pid_t pid_terminated;

	int status;
	char cmd[100];

	printf("minish> ");
	
	if (scanf("%s", cmd) < 1)
	{
		exit(1);
	}

	while (strcmp(cmd, "quit") != 0) 
	{
		pid = fork();

		if (pid > 0) 
		{
			pid_terminated = wait(&status);
			printf("PARENT: son %d terminated with exit code %d\n", pid_terminated, WEXITSTATUS(status));
		} 
		else 
		{
			execlp(cmd, cmd, NULL);
			printf("Command not found !!!\n");
			exit(1);
		}

		printf("minish> ");

		if (scanf("%s", cmd) < 1)
		{
			exit(1);
		}
	}

	return 0;
}
