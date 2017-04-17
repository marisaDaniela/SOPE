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

void sigterm_handler(int signo)
{
	printf("Entering SIGTERM handler ...\n");
	sleep(10);
	printf("Exiting SIGTERM handler ...\n");
}

int main(void)
{
	struct sigaction action;
	action.sa_handler = sigint_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;

	signal(SIGTERM,sigterm_handler); 
	 
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
marisa@marisa-VirtualBox:~/Desktop/SOPE_Projects/Ficha4$ ./p2c
Try me with CTRL-C ...
^CEntering SIGINT handler ...
Entering SIGTERM handler ...
Exiting SIGTERM handler ...
Exiting SIGINT handler ...
^CEntering SIGINT handler ...

*/

/*
marisa@marisa-VirtualBox:~$ ps u
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
marisa    9004  0.0  0.5  22772  5304 pts/2    Ss   15:36   0:00 bash
marisa    9284  0.0  0.5  22704  5336 pts/17   Ss   16:28   0:00 bash
marisa    9553  0.0  0.0   4356   624 pts/2    S+   17:00   0:00 ./p2c
marisa    9554  0.0  0.3  37408  3288 pts/17   R+   17:00   0:00 ps u
marisa@marisa-VirtualBox:~$ kill -s SIGTERM 9553

*/


