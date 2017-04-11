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
		printf("Numero errado de parametros!\n");
		exit(1);
	}
	
	
	char * path = argv[1];
    char * option = argv[2];
	char * filename = argv[3];
	char * actionToExecute = argv[4];
	
	
	int f1;
	
	if((strncmp(option, "-name", 5)) == 0) {
		if((f1 = open(filename, O_RDONLY) == -1))
		{
			perror(option);
			exit(1);
		}
		else
		{
			if((strncmp(actionToExecute, "-delete", 7))==0)
			{
			}
			else if((strncmp(actionToExecute, "-print", 6))==0)
			{
			}
			else if((strncmp(actionToExecute, "-exec", 5))==0)
			{
			}
		}
	}
	else if((strncmp(option, "-perm", 5)==0)
	{
	}
	else if((strncmp(option, "-type", 5)==0)
	{
	}
	
	return 0;
}
