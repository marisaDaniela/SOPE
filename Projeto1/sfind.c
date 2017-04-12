#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h> 
#include <dirent.h>
#include <unistd.h>

char cwd[500];

void sigint_handler(int signo)
{	
	char a;
	
	printf("Are you sure you want to terminate(Y/N)?\n");
	scanf("%c", &a);
	
	if( a == 'y' || a == 'Y'){
		exit(1);
	} 
	else if( a== 'n' || a == 'N'){
		return;
	}
}

//Cenas para procurar o diretorio:
char * findDir(char * path){
	getcwd(cwd, sizeof(cwd));
	if(path[1]=='.'){
		int i;
		for(i = strlen(cwd)-1; cwd[i]!='/'; i--);{
			cwd[i] = '\0';
		}
		
	}
	return cwd;
}



int main(int argc, char* argv[]){
	struct sigaction action;
 	// prepare the 'sigaction struct'
  
  	action.sa_handler = sigint_handler;
 	sigemptyset(&action.sa_mask);
 	action.sa_flags = 0;
 
 	// install the handler
 	sigaction(SIGINT,&action,NULL); 
 	
	if(argc < 2)
	{
		printf("Wrong number of parameters!\n");
		exit(1);
	}
	
	//implementar opçoes: -name string, -type c: f-ficheiro normal, d-diretorio, l-ligacao, -perm mode
	//acoesToExecute: -print(mostra no ecra os ficheiros encontrados), -delete(apaga os ficheiros), -exec cmd
	
	char * path = argv[1];  // caminho atual
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
		
}		else
		{
			if((strncmp(actionToExecute, "-delete", 7))==0)
			{
				remove(filename);
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
