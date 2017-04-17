#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

// Hello my friends

int main(void) 
{
	int status = 0;

	pid_t processo = fork();

	if(processo > 0)
	{
		printf("Hello ");
		exit(0);
	}

	waitpid(processo, &status, 0); // garante que o processo do fork inicial termine

	processo = fork(); //novo processo;

	if(processo > 0)
	{
		printf("my ");
		exit(0);
	}

	waitpid(processo, &status, 0);

	processo = fork();

	if(processo > 0)
	{
		printf("friends! \n");
		exit(0);
	}

	waitpid(processo, &status, 0);

 	return 0;

}