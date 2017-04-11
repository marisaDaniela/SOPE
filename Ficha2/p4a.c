#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> 
#include <unistd.h> 

#define BUF_SIZE 512


int main(){
	int f1;
	
	if((f1=open("alunos.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600))==-1){
		perror("alunos.txt");
		exit(1);	
	}
	
	char nome[BUF_SIZE];
	int nota;
	printf("CTRL+C para terminar! \n \n");
	do{
		printf("Nome do estudante ? ");
		fgets(nome, BUF_SIZE, stdin);
		printf("Classificacao ? ");
		scanf("%d", &nota);

		char tempBuffer[16];

		sprintf(tempBuffer, "%d", nota);
		write(f1, nome, strlen(nome));
		write(f1, tempBuffer, strlen(tempBuffer));
		write(f1, "\n", 1);

		fgets(nome, BUF_SIZE, stdin);
		
	} while(1);
	
	close(f1);
	
}
