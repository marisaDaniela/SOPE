// PROGRAMA p7.c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(int argc, char *argv[]) 
{
 	char prog[20];

 	sprintf(prog,"%s.c",argv[1]);
 	execlp("gcc","gcc",prog,"-Wall","-o",argv[1],NULL);

 	printf("Hello!\n");
 	exit(0);
} 
/*

The C library function int sprintf(char *str, const char *format, ...) sends formatted output to a string pointed to, by str.


	str − This is the pointer to an array of char elements where the resulting C string is stored.

	format − This is the String that contains the text to be written to buffer. It can optionally contain embedded format tags that are replaced by the values specified in subsequent additional arguments and formatted as requested. Format tags prototype: %[flags][width][.precision][length]specifier, as explained below −
*/

/*
O programa serve para compilar. Recebe como argumento o nome de um ficheiro, por exemplo p5 e através disso executa o comando gcc -Wall p5.c -o p5 

man execl
p*/