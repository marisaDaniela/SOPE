#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include "sfind.h"

int main(int argc, char* argv[])
{
	/* We need to attach our signal handler to a signal
	 * for that we can use the syscall 'signal', however the syscall 'sigaction' should be used instead
	 * Signals are asynchronous!! */
	/* sigaction:  int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
	 * 		- signum: signal number, specifies the signal (ex: SIGINT) but it cant be either SIGKILL and SIGSTOP
	 *		- */
	struct sigaction new_sigaction;
	new_sigaction.sa_handler = signalHandler;
	new_sigaction.sa_flags = 0;

	/* handling SIGINT signal - Interrupt from keyboard Ctrl+C */
	sigaction(SIGINT, &new_sigaction, NULL);


	/* Command line options */
	/* Command example: find . -name hello.txt -print */
	char* path = argv[1];		/* path is the directory hierarchy on which we'll be searching */
	char* option = argv[2];
	char* filename = argv[3];
	char* actionToExecute = argv[4];

	if(argc < 2)	/* é necessario especificar, no minimo, o nome do comando, em que diretorio procurar, uma opcao, e o nome do ficheiro a procurar*/
	{
		printf("Wrong number of parameters!\n");
		exit(1);
	}

	if (argc == 2)
	{
		printAllFilesInDir(argv[1]);
	}
	else if(argc >=3)
	{
		if ((strncmp(option, "-name", 5)) == 0)
		{
			searchByName(path, filename, actionToExecute);
		}
		else if((strncmp(option, "-perm", 5))==0)
		{
			// filename = permissions required
			searchByPermissions(path, filename, actionToExecute);
		}
		else if((strncmp(option, "-type", 5))==0)
		{
			//ficheiro normal, diretorio, ligacao
			searchByType(path, filename[0], actionToExecute);
		}
		else
		{
			printf("Invalid option: %s", option);
		}
	}
	return 0;
}

void signalHandler (int signo)
{
	char choice;
	if (signo == SIGINT)
	{
		printf("\nAre you sure you want to terminate? (Y/N)\n");
		printf("-> ");

		while(1)
		{
			scanf("%c", &choice);

			if (choice == 'Y' || choice == 'y')
				exit(0);
			else if (choice == 'N' || choice == 'n')
				return;
		}
	}
}

void printAllFilesInDir(const char* path)
{
	DIR* p;
	struct dirent* pp;
	p = opendir (path);

	char* filenameInDir;

	if (p != NULL)
	{
		while ((pp = readdir (p))!=NULL)
		{ 
			printf("%s/", path);
			filenameInDir = pp->d_name;
			printf("%s\n", filenameInDir);
		}
		(void) closedir (p);
	}
	else
		printf("sfind: \"%s\" : File or directory not found\n", path);
}

/* Recursive */
void searchByName(const char* path,const char* filename,const char* actionToExecute)
{
	DIR* p;
	struct dirent* pp;
	p = opendir (path);

	char* filenameInDir;
	char fullPathFile[100] = "";
	strcat(fullPathFile, path);
	strcat(fullPathFile, "/");
	//struct stat *buf; 	// irá conter informacao sobre um ficheiro - usado para quando for definido -type

	if (p != NULL)
	{
		while ((pp = readdir (p))!=NULL)
		{
			// reset do fullPathFile
			strcpy(fullPathFile, "");
			strcat(fullPathFile, path);
			strcat(fullPathFile, "/");

			filenameInDir = pp->d_name;
			strcat(fullPathFile, filenameInDir);

			//if (strcmp(filenameInDir, filename) == 0)	// verificar se o nome de um ficheiro no diretorio corresponde ao procurado
			//{
				if (actionToExecute != NULL)
				{
					executeAction(fullPathFile, filename, actionToExecute);
				}
				else
				{
					printf("File found\n");
				}
			//}
		}
		(void) closedir (p);
	}
}

/* Recursive */
void searchByType(const char* path,const char filetype,const char* actionToExecute)
{
	DIR* p;
	struct dirent* pp;
	p = opendir (path);

	char* filenameInDir;
	char fullPathFile[100] = "";
	strcat(fullPathFile, path);
	strcat(fullPathFile, "/");
	//struct stat *buf; 	// irá conter informacao sobre um ficheiro - usado para quando for definido -type

	if (p != NULL)
	{
		while ((pp = readdir (p))!=NULL)
		{
			// reset do fullPathFile
			strcpy(fullPathFile, "");
			strcat(fullPathFile, path);
			strcat(fullPathFile, "/");

			filenameInDir = pp->d_name;
			strcat(fullPathFile, filenameInDir);
			//printf("%s\n", fullPathFile);
			if (filetype == 'f' && isRegularFile(filenameInDir))	// verificar se um ficheiro é um regular file
			{
				if (actionToExecute != NULL)
				{
					executeAction(fullPathFile, filenameInDir, actionToExecute);
				}
				else
				{
					printf("File found\n");
				}
			}
			else if (filetype == 'd' && isDirectory(filenameInDir))	// verificar se um ficheiro é um diretorio
			{
				if (actionToExecute != NULL)
				{
					executeAction(fullPathFile, filenameInDir, actionToExecute);
				}
				else
				{
					printf("File found\n");
				}
			}
			else if (filetype == 'l' && isSymbolicLink(filenameInDir))	// verificar se um ficheiro é symbolic link
			{
				if (actionToExecute != NULL)
				{
					executeAction(fullPathFile, filenameInDir, actionToExecute);
				}
				else
				{
					printf("File found\n");
				}
			}
		}
		(void) closedir (p);
	}
}

void searchByPermissions(const char* path,const char* permsRequired,const char* actionToExecute)
{
	DIR* p;
	struct dirent* pp;
	p = opendir (path);

	char* filenameInDir;
	char fullPathFile[100] = "";
	strcat(fullPathFile, path);
	strcat(fullPathFile, "/");

	if (p != NULL)
	{
		while ((pp = readdir (p))!=NULL)
		{
			// reset do fullPathFile
			strcpy(fullPathFile, "");
			strcat(fullPathFile, path);
			strcat(fullPathFile, "/");

			filenameInDir = pp->d_name;
			strcat(fullPathFile, filenameInDir);
			//printf("%s\n", fullPathFile);
			if (comparePermissions(fullPathFile, permsRequired))	// verificar se um ficheiro é um regular file
			{
				printf("hello2\n");
				if (actionToExecute != NULL)
				{
					executeAction(fullPathFile, filenameInDir, actionToExecute);
				}
				else
				{
					printf("File found\n");
				}
			}
		}
		(void) closedir (p);
	}
}

/* as permissoes sao em octal, e recebemos do argumento um array char de 4 digitos,ex: 0543, onde cada digito corresponde a 3 bits */
int comparePermissions(const char *path, const char* permissions)
{
	/*struct stat path_stat;
    stat(path, &path_stat);

	const char *permissionsString = "rwxrwxrwx";
	// transformar a variavel permissions em mode_t
	int currentNumber;
	int i;

	currentNumber = atoi(permissions[0]);

	if (currentNumber)

	printf("File Permissions: \t");
    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n\n");





	const char *perm = "rwxrwxrwx";
	mode_t mode = 0;

	if (perm[0] == 'r')
	  mode |= 0400;
	if (perm[1] == 'w')
	  mode |= 0200;
	if (perm[2] == 'x')
	  mode |= 0100;
	if (perm[3] == 'r')
	  mode |= 0040;
	if (perm[4] == 'w')
	  mode |= 0020;
	if (perm[5] == 'x')
	  mode |= 0010;
	if (perm[6] == 'r')
	  mode |= 0004;
	if (perm[7] == 'w')
	  mode |= 0002;
	if (perm[8] == 'x')
	  mode |= 0001;



	  // quero comparar mode_t's



	// temos de colocar espaco para o \0, os restantes sao para o numero em octal - as permissoes
	char filePermissions[6];
	//sprintf(filePermissions,"%1d", path_stat.st_mode);		// convert int to char array

	itoa(3, filePermissions, 8);	// converter de octal para string

	printf("-----\n");
	printf("Full path: %s\n", path);
	printf("permission: %s\n", permissions);
	printf("mode: %c\n", filePermissions[0]);
	printf("-----\n");

	if (strcmp(filePermissions, permissions) == 0)
		return 1;
	else
		return 0;*/
		return 0;
}

void executeAction(const char* path,const char* filename,const char* actionToExecute)
{
	//printf("hello3");
	if ((strncmp(actionToExecute, "-delete", 7))==0)
	{
		int ret = remove(filename);		// so remove no diretorio atual

		if(ret == 0)
		{
			printf("File deleted successfully\n");
		}
		else
		{
			printf("Error: unable to delete the file\n");
		}
	}
	else if ((strncmp(actionToExecute, "-print", 6))==0)
	{
		printf("%s/%s\n",path, filename);
	}
	else if ((strncmp(actionToExecute, "-exec", 5))==0)
	{
		system(strcat("./",filename));
	}
	else
		exit(1);
}

int isRegularFile(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return (path_stat.st_mode & S_IFREG)==S_IFREG;
}

int isDirectory(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
	return (path_stat.st_mode & S_IFDIR)==S_IFDIR;
}

int isSymbolicLink(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
	return (path_stat.st_mode & S_IFLNK)==S_IFLNK;
}
