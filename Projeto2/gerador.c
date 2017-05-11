#include "resources.h"

static sem_t *semaphore; // para sincronizar com a sauna
static int log_file_generator; // descritor do ficheiro do gerador

int main(int argc , char *argv[]) 
{
	int num_requests, duration;
	int id = 1;
	pthread_t new_request;
	srand(time(NULL));

	if (argc != 3)
	{
        error("Wrong number of arguments. Usage: %s <num_requests> <duration>\n", argc);
	}

    if ((num_requests = atoi(argv[1])) == 0 || (duration = atoi(argv[2])) == 0) 
    {
        error("Invalid arguments, must be an integer!\n");
    }

    if ((log_file_generator = open("/tmp/ger.pid", O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) //O_WRONLY – abertura para escrita  
    {															//O_CREAT – Cria o ficheiro se não existe; requer o parâmetro mode
        error("Couldn't open '/tmp/ger.pid'!\n"); 			//O_TRUNC – Coloca o comprimento do ficheiro em 0, mesmo se já existir 
    }

    







}