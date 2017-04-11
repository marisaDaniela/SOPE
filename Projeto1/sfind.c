#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


void functionCTRL_Z()
{	
	char a;
	
	printf("Are you sure you want to terminate(Y/N)?\n");
	scanf("%c", &a);
	
	if( a == 'y' || a == 'Y'){
		//TODO
	} 
	else if( a== 'n' || a == 'N'){
		//TODO
	}
}

int main(int argc, char* argv[]){
	if(argc < 2)
	{
		printf("Wrong number of parameters!\n");
		exit(1);
	}
	
	//implementar opçoes: -name string, -type c: f-ficheiro normal, d-diretorio, l-ligacao, -perm mode
	//acoesToExecute: -print(mostra no ecra os ficheiros encontrados), -delete(apaga os ficheiros), -exec cmd
	
	char * path = argv[1];
    char * option = argv[2]; //-name, -type
	char * filename = argv[3];
	char * actionToExecute = argv[4]; //print, delete, exec cmd
	
	
	int f1;
	
	if((strncmp(option, "-name", 5)) == 0) 
	{
		if((f1 = open(filename, O_RDONLY) == -1))
		{
			perror(option);
			exit(1);
		}
		else
		{
			if((strncmp(actionToExecute, "-delete", 7))==0)
			{
				//TODO: elimina os ficheiros
			}
			else if((strncmp(actionToExecute, "-print", 6))==0)
			{
				//TODO: imprime na consola os ficheiros que encontrou
			}
			else if((strncmp(actionToExecute, "-exec", 5))==0)
			{
				//TODO: executa o comando encontrado
			}
		}
	}
	else if((strncmp(option, "-perm", 5))==0)
	{
		//permissoes do ficheiro
	}
	else if((strncmp(option, "-type", 5))==0)
	{
		//ficheiro normal, diretorio, ligacao
	}
	
	return 0;
}
