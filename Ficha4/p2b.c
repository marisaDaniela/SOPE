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


/* Terminal 1

 cc -Wall p2b.c -o p2b
marisa@marisa-VirtualBox:~/Desktop/SOPE_Projects/Ficha4$ ./p2b
Try me with CTRL-C ...
^CEntering SIGINT handler ...
^C^C^C^C^CExiting SIGINT handler ...
Entering SIGINT handler ...
Exiting SIGINT handler ...

^CEntering SIGINT handler ...
^CTerminado
marisa@marisa-VirtualBox:~/Desktop/SOPE_Projects/Ficha4$ 

*/

/* Terminal 2
ps u
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
marisa    9004  0.0  0.5  22772  5304 pts/2    Ss   15:36   0:00 bash
marisa    9284  0.0  0.5  22704  5336 pts/17   Ss   16:28   0:00 bash
marisa    9500  0.0  0.0   4356   728 pts/2    S+   16:53   0:00 ./p2a
marisa    9516  0.0  0.3  37408  3252 pts/17   R+   16:55   0:00 ps u
marisa@marisa-VirtualBox:~$ kill -s SIGTERM 9500
marisa@marisa-VirtualBox:~$ 

*/