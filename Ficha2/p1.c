#include <termios.h>
#include <unistd.h>
#include <string.h>

#define MAX_PASSWD_LEN 20

int main(void)
{
 struct termios term, oldterm;
 int i;
 char pass[MAX_PASSWD_LEN+1], ch;
 char echo = '*';

 write(STDOUT_FILENO, "\nPassword? ", 11);
 
 tcgetattr(STDIN_FILENO, &oldterm); //preenche uma estrutura terminos com o endereço passado em oldterm, com as caracteristicas de stdin_fileno
 
 term = oldterm;
 term.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON);
 
 tcsetattr(STDIN_FILENO, TCSAFLUSH, &term); //modifica as caracteristicas da consola stdin_fileno com os valores previamente colocados numa estrutura termios cujo endereço e passado em term, e 
 // TCSAFLUSH --> a modificacao e feita depois de se esgotar o buffer de saida

 i=0;
 while (i < MAX_PASSWD_LEN && read(STDIN_FILENO, &ch, 1) && ch != '\n') {
  pass[i++] = ch;
  write(STDOUT_FILENO, &echo, 1);
 }
 pass[i] = 0;

 tcsetattr(STDIN_FILENO, TCSANOW, &oldterm);
 //TCSANOW --> A modificacao e feita imediatamente
 
 write(STDOUT_FILENO, "\n\nPassword: ", 12);
 write(STDOUT_FILENO, pass, strlen(pass));
 write(STDOUT_FILENO, "\n", 1);

 return 0;
}
