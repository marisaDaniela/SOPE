#include "resources.h"

static sem_t *sem; // para sincronizar com a sauna
static int log_file_generator; // descritor do ficheiro do gerador

char * fifos[2] = {"/tmp/entrada","/tmp/rejeitados"};

void * makeRequest(int *duration)
{
	int value = *(int *)duration;
	Request * r = generateRequest(value);
	

	int fd;

	if(mkfifo(fifos[0], 0666) != 0)
	{
		perror("Can't create FIFO 'tmp/entrada'!");
		exit(1);
	}

	if((fd = open(fifos[0], 0666))==-1)
	{
		perror("Oops!!");
		exit(1);
	}

	if(write(fd,r,sizeof(r)) == -1)
	{
        perror("Error on writing to fifo!\n");
        exit(1);
	}

}

int main(int argc, char *argv[]) 
{
	int num_requests, duration;
	pthread_t new_request;
	srand(time(NULL));

	char info[256]; // numero de caracteres por linha (?????????????????????????????????????????????????????????????)

	if (argc != 3)
	{
       printf("Wrong number of arguments! Usage: %s <num_requests> <duration>\n", argv[0]);
       exit(1);
	}

   /* else if ((num_requests = atoi(argv[1])) == 0 || (duration = atoi(argv[2])) == 0) 
    {
        printf("Invalid arguments, must be an integer!\n");
        exit(1);
    }

   /* if ((log_file_generator = open("/tmp/ger.pid", O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) //O_WRONLY – abertura para escrita  
    {															//O_CREAT – Cria o ficheiro se não existe; requer o parâmetro mode
        perror("Couldn't open '/tmp/ger.pid'!\n"); 			//O_TRUNC – Coloca o comprimento do ficheiro em 0, mesmo se já existir 
    }

    // Escrita no ficheiro /tmp/ger.pid

    sprintf(info,"   inst   -    pid   -    p:    g     -    dur   -    tip   \n");

    if(write(log_file_generator,info,strlen(info)) == -1)
    {
        perror("Can't write on the log_file_generator!\n");
    }

      /*
     * sem (GERADOR<=>SAUNA)
     */

    /*sem = malloc(sizeof(sem_t));
    
   if((sem = sem_open("sem", O_CREAT | O_EXCL, 0666, 1)) == SEM_FAILED)
    {
        if(errno == EEXIST)
        {
            if((sem = sem_open("sem", 0)) == SEM_FAILED) 
            {
                error("Couldn't create semaphore!\n");
            }
        }
        else
        {
            error("Couldn't create semaphore!\n");
        }
    }*/

    pthread_create(new_request, NULL, makeRequest, duration);

   // makeRequest(duration);

}