#include <stdio.h>
int main(int argc, char *argv[])
{
 int i;

 if(argv[1]==NULL)
 	return 1;
 
 printf("Hello ");
 for(i=1; i < argc; i++)
 {
 	printf("%s ", argv[i]);
 }
 printf("!\n");
 return 0;
} 
