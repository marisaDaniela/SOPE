// PROGRAMA p2.c
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void) 
{
 	printf("1");
 	if(fork() > 0) 
 	{
 		printf("%d",2);
 		printf("%d",3);
 	} 
 	else 
 	{
 		printf("%d",4);
 		printf("%d",5);
 	}
 	printf("\n");
 	return 0;
}
