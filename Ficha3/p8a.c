// PROGRAMA p8.c

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
 	pid_t pid;
 
 	if (argc != 2) 
 	{
 		printf("usage: %s dirname\n",argv[0]);
 		exit(1);
 	}
 
 	pid=fork();
 
 	if (pid > 0)
 		printf("My child is going to execute command\"ls -laR %s\"\n", argv[1]);
 	else if (pid == 0)
 	{
 		execlp("ls", "ls", "-laR", argv[1], NULL);
 		printf("Command not executed !\n");
 		exit(1);
 	}
 	exit(0);
} 

/*"
this prototype:

  int execlp(const char *file, const char *arg, ...);

Says that execlp ìs a variable argument function. It takes 2 const char *. The rest of the arguments, if any, are the additional arguments to hand over to program we want to run - also char * - all these are C strings (and the last argument must be a NULL pointer)

So, the file argument is the path name of an executable file to be executed. arg is the string we want to appear as argv[0] in the executable. By convention, argv[0] is just the file name of the executable, normally it's set to the same as file.

The ... are now the additional arguments to give to the executable.

Say you run this from a commandline/shell:
	
	$ ls

That'd be execlp("ls", "ls", (char *)NULL); Or if you run

	$ ls -l /

That'd be execlp("ls", "ls", "-l", "/", (char *)NULL);

So on to execlp("/bin/sh", ..., "ls -l /bin/??", ...);

Here you are going to the shell, /bin/sh , and you're giving the shell a command to execute. That command is "ls -l /bin/??". You can run that manually from a commandline/shell:

 	$ ls -l /bin/??

Now, how do you run a shell and tell it to execute a command ? You open up the documentation/man page for your shell and read it.

What you want to run is:
	
	$ /bin/sh -c "ls -l /bin/??"

This becomes

  execlp("/bin/sh","/bin/sh", "-c", "ls -l /bin/??", (char *)NULL);
Side note: The /bin/?? is doing pattern matching, this pattern matching is done by the shell, and it expands to all files under /bin/ with 2 characters. If you simply did

  execlp("ls","ls", "-l", "/bin/??", (char *)NULL);
Probably nothing would happen (unless there's a file actually named /bin/??) as there's no shell that interprets and expands /bin/??
"*/