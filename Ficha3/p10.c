#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[], char *envp[])
{
	
	pid_t pid;
 	if (argc !=2 && argc !=3 ) 
 	{
 		printf("usage: %s dirname , <ficheiro>\n",argv[0]);
		exit(1);
	}
 	
 	pid=fork();

 	if (pid > 0)
 		printf("My child is going to execute command \"ls -laR %s\"\n", argv[1]);
 	
 	else if (pid == 0)
 	{
 		if(argc == 3){
 			//int f1 = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC, 0644 );
 			//int f2 = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC, 0644 );
 			//dup2(fileno(argv[2]), STDIN_FILENO);
 			//dup2(fileno(argv[2]), STDOUT_FILENO);
 			//fclose(f1);
 			//fclose(f2);
 			execlp("ls", "ls", "-laR", argv[1], NULL);

 		}
 		else
 			execlp("ls", "ls", "-laR", argv[1], NULL);

 		printf("Command not executed !\n");
 		exit(1);
 	}
	
	exit(0);
} 