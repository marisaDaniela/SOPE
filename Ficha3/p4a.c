// PROGRAMA p2.c
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void) 
{
	int status = 0;
 	if(fork() != 0) 
 	{
 		wait(&status); //para garantir que o filho execute primeiro;
 		printf(" world!\n");

 	} 
 	else 
 	{
 		printf("Hello");

 	}
 	return 0;
}