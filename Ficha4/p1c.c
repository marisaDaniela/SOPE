#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sigint_handler(int signo)
{
 	printf("In SIGINT handler ...\n");
}

int main(void)
{
	struct sigaction action;
  
	 if (signal(SIGINT,sigint_handler) < 0)
	 {
	 	fprintf(stderr,"Unable to install SIGINT handler\n");
	 	exit(1);
	 }
	 // prepare the 'sigaction struct'
 	action.sa_handler = sigint_handler;
 	sigemptyset(&action.sa_mask);
 	action.sa_flags = 0;
 	// install the handler
 	sigaction(SIGINT,&action,NULL);

	 printf("Sleeping for 30 seconds ...\n");
	 sleep(30);
	 printf("Waking up ...\n");
	 exit(0);
}