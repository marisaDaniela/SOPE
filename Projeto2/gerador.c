#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

char* INPUT_FIFO = "tmp/entrada";
char* REJECTED_FIFO = "tmp/rejeitados";

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

int main(int argc, char** argv) {

	if(argc != 3){
		printf("Wrong number of arguments. Usage:<numRequests><maxTime>\n");
	}

	if(mkfifo(INPUT_FIFO, O_RDWR ) != 0){ // nao sei se vao ser estas as permissoes do fifo de entrada 
		perror("Can't create FIFO 'tmp/entrada");
		exit(1);
	}

	int numRequests = atoi(argv[1]); //numero de pedidos
	int maxTime = atof(argv[2]); //max duracao de pedido
	int fd; 

	if(fd = open(INPUT_FIFO,O_WRONLY)==-1){
		perror("Oops!!");
		exit(1);
	}

	Person * p = generatePerson(maxTime);

	write(fd, p, sizeof(p));

	//INCOMPLETE

}
