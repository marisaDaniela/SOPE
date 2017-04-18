#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define READ 0
#define WRITE 1
#define LENGTH 512

int main(int argc, char** argv) 
{
	if (argc != 2)
	{
		printf("%s: invalid number of arguments.\n", argv[0]);
		exit(1);
	}
	
	int fd;
	int pd[2];
	
	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		perror(argv[1]);
		exit(1);
	}
	
	if (pipe(pd) != 0)
	{
		exit(1);
	}
	
	pid_t pid = fork();
	
	if (pid > 0) 
	{
		char buffer[LENGTH];
		int nr;
		
		close(pd[READ]);
		
		while ((nr = read(fd, buffer, LENGTH)) > 0)
		{
			write(pd[WRITE], buffer, nr);
		}
		
		close(pd[WRITE]);
		close(fd);
		wait(NULL);
	}
	else
	{
		close(pd[WRITE]);
		dup2(pd[READ], STDIN_FILENO);
		execlp("sort", "sort", NULL);
	}
	
	return 0;
}
