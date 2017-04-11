#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
 int i;
 int num; 
 
 num =  atoi(argv[1]);
 
 if(argv[1]==NULL || argv[2] == NULL){
 	printf("Usage: <numTimes><name>");
 	return 1;
 	}
 
 while(num != 0){
 	printf("Hello ");
 	for(i=2; i < argc; i++)
 	{
 		printf("%s ", argv[i]);

 	}
 	printf("!\n");
 	num= num-1;
 }
 return 0;
} 
