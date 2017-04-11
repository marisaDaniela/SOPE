#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[], char* envp[])
{

	int i = 0;
	
	if(argc == 1){
	while(envp[i]!=NULL)
	{
		if(strncmp(envp[i], "USER", 4)==0) //int strncmp(const char *str1, const char *str2, size_t n) 
		{
			printf("Hello %s !\n", strstr(envp[i], "=")+1);
		}
		i++;
	}
	}
	
 return 0;
} 
