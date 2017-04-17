// PROGRAMA p2.c
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void) 
{
	pid_t pid  = getpid();

 	if(fork() != 0) 
 	{
 		printf("Hello ");

 	} 
 	else 
 	{
 		while(getppid() == pid){

 		}
 		printf("world!\n");

 	}
 	return 0;
}