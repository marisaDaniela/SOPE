//Programa para apresentar no ecra todas as variaveis de ambiente

#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{
	int i = 0;
	
	if(argc != 1){
		return 1;
	}
	 
	while(envp[i] != NULL)
	{
		printf("%d -> %s \n", i, envp[i]);
		i++;
	}
	return 0;
}
