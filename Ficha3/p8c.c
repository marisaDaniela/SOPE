#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
 	pid_t pid;

 	char *array[] ={"ls", "-laR", argv[1], NULL};
 
 	if (argc != 2) 
 	{
 		printf("usage: %s dirname\n",argv[0]);
 		exit(1);
 	}
 
 	pid=fork();
 
 	if (pid > 0)
 		printf("My child is going to execute command\"ls -laR %s\"\n", argv[1]);
 	else if (pid == 0)
 	{
 		execvp("ls", array);
 		printf("Command not executed !\n");
 		exit(1);
 	}
 	exit(0);
} 

/*

The first argument is the file you wish to execute, and the second argument is an array of null-terminated strings that represent the appropriate arguments to the file as specified in the man page.

For example:

char *cmd = "ls";
char *argv[3];
argv[0] = "ls";
argv[1] = "-la";
argv[2] = NULL;

execvp(cmd, argv); //This will run "ls -la" as if it were a command
*/