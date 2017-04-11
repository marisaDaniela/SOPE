#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_BUF 1000
int main(int argc, char* argv[]){

	int f1;
	char buf[MAX_BUF];
	
	if(argc != 2){
		printf("Usage: <nomeFicheiro>\n");
		exit(1);
	}
	
	f1 = open(argv[1], O_RDONLY);
	
	
	while(read(f1, buf, MAX_BUF) > 0){
		write(STDOUT_FILENO, buf, read(f1, buf, MAX_BUF));
	}
	
	close(f1);

	return 0;
}
