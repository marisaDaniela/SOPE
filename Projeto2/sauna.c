#include <stdio.h>

int main(int argc, char* argv[]){
	if(argc != 2){
		printf("Wrong number of arguments. Usage:<capacity>\n");
	}

	int capacity = atoi(argv[1]);
}