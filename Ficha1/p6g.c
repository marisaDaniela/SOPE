// PROGRAMA p6a.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUF_LENGTH 256
int main(int argc, char* argv[])
{
	if(argc != 3)
	{	
	 printf("nope\n");
	 exit(1);
	}
	
	if(argv[1] == NULL || argv[2] == NULL)
	{	
		printf("nope\n");
		exit(1);
	}
	
	
	FILE *src, *dst;
	char buf[BUF_LENGTH];
	if ( ( src = fopen( argv[1], "r" ) ) == NULL )
	{
		printf("Errno: %d\n", errno);
	 	exit(1);
	}
	if ( ( dst = fopen( argv[2], "w" ) ) == NULL )
	{
		printf("Errno: %d\n", errno);
	 	exit(2);
	} 
	while( ( fgets( buf, BUF_LENGTH, src ) ) != NULL )
	{
	 	fputs( buf, dst );
	}
	fclose( src );
	fclose( dst );
	exit(0); // zero é geralmente indicativo de "sucesso"
}

//Ambas imprimem a mensagem

//Error in fopen(perror): No such file or directory
//Error in fopen(strerror): No such file or directory
