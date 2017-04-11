// PROGRAMA p6a.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUF_LENGTH 256
int main(void)
{
	FILE *src, *dst;
	char buf[BUF_LENGTH];
	if ( ( src = fopen( "infile.txt", "r" ) ) == NULL )
	{
		perror("Error in fopen(perror)");
		printf("Error in fopen(strerror): %s\n", strerror(errno));
	 	exit(1);
	}
	if ( ( dst = fopen( "outfile.txt", "w" ) ) == NULL )
	{
		perror("Error in fopen(perror)");
		printf("Error in fopen(strerror): %s\n", strerror(errno));
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
