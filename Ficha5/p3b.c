#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

int main(int argc, char** argv) 
{
	if (argc != 2)
	{
		printf("%s: invalid number of arguments.\n", argv[0]);
		exit(1);
	}
	
	int fd[2];

	if (pipe(fd) != 0)
	{
		exit(1);
	}
	
	pid_t pid = fork();
	
	if (pid > 0) 
	{	
		close(fd[READ]);
		
		if (fork() > 0)
		{
			wait(NULL);
		}
		else
		{
			dup2(fd[WRITE], STDOUT_FILENO);
			execlp("cat", "cat", argv[1], NULL);
		}
		
		close(fd[WRITE]);
		wait(NULL);
	}
	else
	{
		close(fd[WRITE]);
		dup2(fd[READ], STDIN_FILENO);
		execlp("sort", "sort", NULL);
	}
	
	return 0;
}
