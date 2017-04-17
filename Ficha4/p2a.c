#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sigint_handler(int signo)
{
	printf("Entering SIGINT handler ...\n");
 	sleep(10);
	printf("Exiting SIGINT handler ...\n");
}

int main(void)
{
	struct sigaction action;
	action.sa_handler = sigint_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	 
	if (sigaction(SIGINT,&action,NULL) < 0)
	{
		fprintf(stderr,"Unable to install SIGINT handler\n");
	 	exit(1);
	}
	 
	printf("Try me with CTRL-C ...\n");
	while(1) pause();
	exit(0);
} 

/*
marisa@marisa-VirtualBox:~/Desktop/SOPE_Projects/Ficha4$ cc -Wall p2a.c -o p2a
marisa@marisa-VirtualBox:~/Desktop/SOPE_Projects/Ficha4$ ./p2a
Try me with CTRL-C ...
^CEntering SIGINT handler ...
^C^C^C^C^CExiting SIGINT handler ...
Entering SIGINT handler ...
Exiting SIGINT handler ...

^CEntering SIGINT handler ...
Exiting SIGINT handler ...


*/