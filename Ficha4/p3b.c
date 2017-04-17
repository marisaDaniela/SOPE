#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

//SIGUSR1
//SIGUSR2

int main(){

	srand(time(NULL)); 

	int val = 0;

	pid_t pid = fork();

	if(pid != 0){
		int i = rand()%2;
		if(i == 0){
			kill(pid, SIGUSR1);
			val++;
		}
		else
		{
			kill(pid, SIGUSR2);
			val--;
		}
		sleep(1);
	}
	else if(pid == 0)
	{
		while(val < 50)
		{

			printf("Valor: %d\n", val); //o \n faz diferença, whaaaat
		}
	}

	return 0;

}