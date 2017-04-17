// PROGRAMA p8.c

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(int argc, char *argv[], char *envp[])
{
 	pid_t pid;
 	int status;
 
 	if (argc != 2) 
 	{
 		printf("usage: %s dirname\n",argv[0]);
 		exit(1);
 	}
 
 	pid=fork();
 
 	
 	if (pid > 0){
 		printf("My child is going to execute command\"ls -laR %s\"\n", argv[1]);
 		waitpid(pid, &status, 0);
 		printf("My child has finished! Value: %d\n", WEXITSTATUS(status));

 		
		if (WIFEXITED(status))
		{
			printf("My child has terminated normally.\n");
		}
		else if (WIFSIGNALED(status))
		{
			printf("My child has terminated abruptedly.\n");
		}

 	}
 	else if (pid == 0)
 	{
 		execlp("ls", "ls", "-laR", argv[1], NULL);
 		printf("Command not executed !\n");
 		exit(1);
 	}
 	exit(0);
}
/*
// WIFEXITED(status) - e avaliada como verdadeira se o filho terminou normalmente

// WIFSIGNALED(status) - e avaliada como verdadeira se o filho terminou anormalmente

*/