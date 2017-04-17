#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> 
#include <unistd.h> 

#define BUF_SIZE 50

struct alunos
{
	char nome[BUF_SIZE];
	int nota;
	
}aluno;

int main(){

	struct alunos a1;
	int f1;
	char buf[BUF_SIZE];
	
	if((f1=open("alunos.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600))==-1){
		perror("alunos.txt");
		exit(1);	
	}

	do{
		printf("Nome do estudante ? ");
		fgets(buf, BUF_SIZE, stdin);
		strcpy(a1.nome, buf);

		printf("Classificacao ? ");
		scanf("%d", &a1.nota);

		write(f1, &a1, sizeof(aluno));

		fgets(buf, BUF_SIZE, stdin);
		
	} while(1);
	
	close(f1);
	
}
