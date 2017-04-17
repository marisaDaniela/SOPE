#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

//SIGUSR1
//SIGUSR2

int ordemCrescente = 1; //se for 0, a ordem e decrescente

static void sig_usr(int signo)
{
	if(signo == SIGUSR1)
	{
		printf("Eu sou o SIGUSR1, e com o poder investido em mim ordeno que a ordem seja crescente!!\n");
		ordemCrescente = 1;
	}
	else if(signo == SIGUSR2)
	{
		printf("Eu sou o SIGUSR2, e com o poder investido em mim ordeno que a ordem seja decrescente!!\n");
		ordemCrescente = 0;

	}
	else
	{
		fprintf(stderr, "received signal %d\n", signo);
		exit(2);
	}
	
}

int main(){
	int val = 0;

	struct sigaction action;

	action.sa_handler = sig_usr;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;

	if(signal(SIGUSR1, sig_usr) == SIG_ERR){
		fprintf(stderr, "Can't catch SIGUSR1\n");
		exit(1);
	}
	if(signal(SIGUSR2, sig_usr) == SIG_ERR){
		fprintf(stderr, "Can't catch SIGUSR2\n");
		exit(1);
	}

	while(1)
	{
		printf("Valor: %d\n", val); //o \n faz diferença, whaaaat?

		if(ordemCrescente)
		{
			val++;
		}
		else
		{
			val--;
		}
		sleep(1);

	}

	return 0;

}