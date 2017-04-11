//criar variavel de ambiente:
// "export USER_NAME="Marisa Daniela Quintal Oliveira"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[], char* envp[])
{
	if(argc == 1){
	printf("Hello %s !\n", getenv("USER_NAME"));
	}
	return 0;
} 
