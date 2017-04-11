#include <stdio.h>
#include <stdlib.h>

void exitHandler1()
{
	printf("Executing exit handler 1\n");
	exit(0);
}

void exitHandler2()
{
	printf("Executing exit handler 2\n");

}

int main(){

	atexit(exitHandler1);
	atexit(exitHandler2);
	

	printf("Main done!\n");
	
	return 0;
	

}
