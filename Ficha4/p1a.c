// PROGRAMA p01a.c
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
	 if (signal(SIGINT,sigint_handler) < 0)
	 {
	 	fprintf(stderr,"Unable to install SIGINT handler\n");
	 	exit(1);
	 }

	 printf("Sleeping for 30 seconds ...\n");
	 sleep(30);
	 printf("Waking up ...\n");
	 exit(0);
}

/*
marisa@marisa-VirtualBox:~/Desktop/SOPE_Projects/Ficha4$ ./p1a
Sleeping for 30 seconds ...
^CIn SIGINT handler ...
Waking up ...
marisa@marisa-VirtualBox:~/Desktop/SOPE_Projects/Ficha4$ echo $?
0

kill -s SIGINT nºprocesso
kill -s SIGUSR1  nºprocesso


marisa@marisa-VirtualBox:~/Desktop/SOPE_Projects/Ficha4$ ./p1a
Sleeping for 30 seconds ...
Sinal 1 definido pelo utilizador
marisa@marisa-VirtualBox:~/Desktop/SOPE_Projects/Ficha4$ echo $?
138

*/