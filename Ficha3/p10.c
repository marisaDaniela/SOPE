#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[], char *envp[])
{
	int status = 0;
 	pid_t pid;
 
 	if (argc != 2 && argc!= 3)  
 	{
 		printf("usage: %s dirname filename\n",argv[0]);
 		exit(1);
 	}

 	pid=fork();

 	if(pid > 0 && argc !=3){
 		printf("My child is going to execute command\"ls -laR %s\"\n", argv[1]);
 	}
 	else if(pid == 0 && argc != 3){
 		execlp("ls", "ls", "-laR", argv[1], NULL);
 		printf("Command not executed !\n");
 		exit(1);
 	}

 	else if(pid > 0 && argc == 3){
 		printf("My child is going to execute command\"ls -laR %s\"\n", argv[1]);
 		wait(&status);
 	}

 	else if(pid == 0 && argc == 3){
 		int fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    	dup2(fd, 1);   // make stdout go to file
    	dup2(fd, 2);   // make stderr go to file - you 

    	execlp("ls", "ls", "-laR", argv[1], NULL);

    	close(fd); 

 	}
 	exit(0);
} 

