#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_BUF 512

int main(int argc, char* argv[]){

	int f1, f2;
	char buf[MAX_BUF];
	
	if((argc != 2) && (argc != 3)) {
		printf("Usage: <nomeFicheiro> ou \nUsage: <nomeFicheiro1> <nomeFicheiro2> \n");
		exit(1);
	}
	
	if((f1 = open(argv[1], O_RDONLY))==-1)
	{
		perror(argv[1]);
		exit(1);
	}
	
	if(argc == 3){
	
		if((f2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644))==-1){
			perror(argv[2]);
			exit(1);
			}
		dup2(f2, STDOUT_FILENO);
	}
	
	int r, w;
	
	while((r=(read(f1, buf, MAX_BUF))) > 0){
		if((w=write(STDOUT_FILENO, buf, r)) <= 0 || w != r)
		{
			if (argc == 3)
			{
				perror(argv[2]);
				close(f2);
			}
			else
			{
				perror(argv[0]);
			}
			
			close(f1);
			exit(1);
		}
	}
	
	close(f1);

	if (argc == 3)
	{
		close(f2);
	}

	return 0;
}
