// PROGRAMA p8.c

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(int argc, char *argv[], char *envp[])
{
 	pid_t pid;
 	int status;
 
 	if (argc != 2) 
 	{
 		printf("usage: %s dirname\n",argv[0]);
 		exit(1);
 	}
 
 	pid=fork();
 
 	if (pid > 0){
 		printf("My child is going to execute command\"ls -laR %s\"\n", argv[1]);
 		waitpid(pid, &status, 0);
 		printf("My child has finished! Value: %d\n", WEXITSTATUS(status));
 	}
 	else if (pid == 0)
 	{
 		execlp("ls", "ls", "-laR", argv[1], NULL);
 		printf("Command not executed !\n");
 		exit(1);
 	}
 	exit(0);
} 

//WEXISTATUS: é avaliada como código de terminação do filho (exit_code)

/*
	Caso 1: diretorio existente:

marisa@marisa-VirtualBox:~/Desktop/SOPE/Ficha3$ ./p9a teste
My child is going to execute command"ls -laR teste"
teste:
total 8
drwxrwxr-x 2 marisa marisa 4096 Abr 12 22:56 .
drwxrwxr-x 3 marisa marisa 4096 Abr 13 22:56 ..
My child has finished! Value: 0

Quando adicionei novos ficheiros:

My child is going to execute command"ls -laR teste"
teste:
total 12
drwxrwxr-x 3 marisa marisa 4096 Abr 13 23:00 .
drwxrwxr-x 3 marisa marisa 4096 Abr 13 23:02 ..
-rw-rw-r-- 1 marisa marisa    0 Abr 13 22:59 cenas
-rw-rw-r-- 1 marisa marisa    0 Abr 13 22:59 cenas (10ª cópia)
-rw-rw-r-- 1 marisa marisa    0 Abr 13 22:59 cenas (11ª cópia)
-rw-rw-r-- 1 marisa marisa    0 Abr 13 22:59 cenas2
-rw-rw-r-- 1 marisa marisa    0 Abr 13 22:59 cenas2 (10ª cópia)
-rw-rw-r-- 1 marisa marisa    0 Abr 13 22:59 cenas2 (11ª cópia)
-rw-rw-r-- 1 marisa marisa    0 Abr 13 22:59 cenas2 (3ª cópia)
-rw-rw-r-- 1 marisa marisa    0 Abr 13 22:59 cenas2 (4ª cópia)
-rw-rw-r-- 1 marisa marisa    0 Abr 13 22:59 cenas2 (5ª cópia)
-rw-rw-r-- 1 marisa marisa    0 Abr 13 22:59 cenas2 (6ª cópia)
-rw-rw-r-- 1 marisa marisa    0 Abr 13 22:59 cenas2 (7ª cópia)
-rw-rw-r-- 1 marisa marisa    0 Abr 13 22:59 cenas2 (8ª cópia)
-rw-rw-r-- 1 marisa marisa    0 Abr 13 22:59 cenas2 (9ª cópia)
-rw-rw-r-- 1 marisa marisa    0 Abr 13 22:59 cenas2 (cópia)
-rw-rw-r-- 1 marisa marisa    0 Abr 13 22:59 cenas2 (outra cópia)
-rw-rw-r-- 1 marisa marisa    0 Abr 13 22:59 cenas (3ª cópia)
-rw-rw-r-- 1 marisa marisa    0 Abr 13 22:59 cenas (4ª cópia)
-rw-rw-r-- 1 marisa marisa    0 Abr 13 22:59 cenas (5ª cópia)
-rw-rw-r-- 1 marisa marisa    0 Abr 13 22:59 cenas (6ª cópia)
-rw-rw-r-- 1 marisa marisa    0 Abr 13 22:59 cenas (7ª cópia)
-rw-rw-r-- 1 marisa marisa    0 Abr 13 22:59 cenas (8ª cópia)
-rw-rw-r-- 1 marisa marisa    0 Abr 13 22:59 cenas (9ª cópia)
-rw-rw-r-- 1 marisa marisa    0 Abr 13 22:59 cenas (cópia)
-rw-rw-r-- 1 marisa marisa    0 Abr 13 22:59 cenas (outra cópia)
drwxrwxr-x 3 marisa marisa 4096 Abr 13 23:01 kk

teste/kk:
total 12
drwxrwxr-x 3 marisa marisa 4096 Abr 13 23:01 .
drwxrwxr-x 3 marisa marisa 4096 Abr 13 23:00 ..
-rw-rw-r-- 1 marisa marisa    0 Abr 13 22:59 cenas
-rw-rw-r-- 1 marisa marisa    0 Abr 13 22:59 cenas2
-rw-rw-r-- 1 marisa marisa    0 Abr 13 22:59 cenas2 (cópia)
-rw-rw-r-- 1 marisa marisa    0 Abr 13 22:59 cenas (cópia)
drwxrwxr-x 2 marisa marisa 4096 Abr 13 23:01 snssn

teste/kk/snssn:
total 56
drwxrwxr-x 2 marisa marisa  4096 Abr 13 23:01 .
drwxrwxr-x 3 marisa marisa  4096 Abr 13 23:01 ..
-rw-rw-r-- 1 marisa marisa  5176 Abr 13 23:01 cenas
-rw-rw-r-- 1 marisa marisa 25876 Abr 13 23:01 cenas2
-rw-rw-r-- 1 marisa marisa 10351 Abr 13 23:01 cenas2 (cópia)
-rw-rw-r-- 1 marisa marisa     0 Abr 13 22:59 cenas (cópia)
My child has finished! Value: 0




	Caso 2: diretorio inexistente


marisa@marisa-VirtualBox:~/Desktop/SOPE/Ficha3$ ./p9a kkk
My child is going to execute command"ls -laR kkk"
ls: impossível aceder a 'kkk': Ficheiro ou directoria inexistente
My child has finished! Value: 2



	Caso 3: terminar com kill (noutro terminal) ps u // kill numeroProcesso

./p9a /usr

My child is going to execute command"ls -laR kkk"

...


gpack/nl/simple-scan/scanning.page

/usr/share/help/nl/simple-scan/figures:
total 8
drwxr-xr-x 2 root root 4096 Jul 19  2016 .
drwxr-xr-x 3 root root 4096 Jul 19  2016 ..
lrwxrwxrwx 1 root root   39 Fev 13 15:35 icon.png -> ../../../C/simple-scan/figures/icon.png
lrwxrwxrwx 1 root root   46 Fev 13 15:35 preferences.png -> ../../../C/simple-scan/figures/preferences.png
lrwxrwxrwx 1 root root   47 Fev 13 15:35 scan_toolbar.png -> ../../../C/simple-scan/figures/scan_toolbar.png

/usr/share/help/nl/ubuntu-help:
My child has finished! Value: 0



*/