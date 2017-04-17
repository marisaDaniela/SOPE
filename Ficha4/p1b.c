// PROGRAMA p01a.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

// evita ctrl-c

int main(void)
{
	void (*oldhandler)(int);

 	if ((oldhandler = signal(SIGINT,SIG_IGN))< 0)
 	{
 		fprintf(stderr,"Unable to install SIGINT handler\n");
 		exit(1);
 	}
 	printf("Sleeping for 30 seconds ...\n");
 	sleep(30);
 	printf("Waking up ...\n");
 	exit(0);
}