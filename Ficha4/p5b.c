#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

void SIGCHLD_handler(int signo)
{
	int status;
	pid_t pid;

	pid = waitpid(-1, &status, WNOHANG);
	printf("Pai: filho com pid=%d terminando com codigo %d\n", pid, WEXITSTATUS(status));

}
int main(void)
{
	struct sigaction signalAction;

	sigfillset(&signalAction.sa_mask);
	signalAction.sa_handler = SIGCHLD_handler;
	signalAction.sa_flags = 0;

	if (sigaction(SIGCHLD, &signalAction, NULL) < 0)
	{
		fprintf(stderr, "I'm unable to install SIGCHLD handler ...\n");
		exit(1);
	}

	pid_t pid;
 	int i, n;
 	for (i=1; i<=3; i++) 
 	{
 		pid=fork(); 
 		if (pid == 0)
 		{
 			printf("CHILD no. %d (PID=%d) working ... \n",i,getpid());
 			sleep(i*7); // child working ...
 			printf("CHILD no. %d (PID=%d) exiting ... \n",i,getpid());
 			exit(0);
 		}
 	}

 	for (i=1 ;i<=4; i++ ) 
 	{
 		printf("PARENT: working hard (task no. %d) ...\n",i);

 		n=20; while((n=sleep(n))!=0);
 		printf("PARENT: end of task no. %d\n",i);
 	}
 exit(0);
} 