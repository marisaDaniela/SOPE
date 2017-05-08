#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>



int ID = 1;

typedef struct Person {
	int id;
	char gender;
	int time;
	int refusedTimes;
} Person;


//Gerar pessoas aleatoriamente
Person* generatePerson(int maxTime) {
	Person* person = malloc(sizeof(Person));

	person->id = ID++;
	person->gender = (rand()%2)? 'M' : 'F';
	person->time = rand() % maxTime + 1;
	person->refusedTimes = 0;


	return person;
}

void write_person(void * arg){
					//meninas, ainda não sei fazer casts de variaveis, mas é preciso
	if(mkfifo( (char *) arg, O_RDWR ) != 0){ // nao sei se vao ser estas as permissoes do fifo de entrada 
		perror("Can't create FIFO 'tmp/entrada");
		exit(1);
		}	
		
        int fd; 

	if(fd = open( (char *) arg, O_WRONLY)==-1){
		perror("Oops!!");
		exit(1);
		}

	Person * p = generatePerson(maxTime);
		
	write(fd, p, sizeof(p));
	}

	
	

