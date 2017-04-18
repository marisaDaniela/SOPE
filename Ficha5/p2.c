#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define READ 0
#define WRITE 1
#define LENGTH 64

typedef struct {
	int a;
	int b;
} values;

typedef struct {
	int sum;
	int sub;
	int mul;
	double div;
	char invalid;
} result;

int main(int argc, char** argv) 
{
	int fd1[2];
	int fd2[2];

	values v;
	result r;
	pid_t pid;
	
	if ((pipe(fd1) != 0) | (pipe(fd2) != 0))
	{
		printf("%s: pipe creation failed\n", argv[0]);
		exit(1);
	}
		
	pid = fork();
	
	if (pid > 0)
	{
		close(fd1[READ]);
		close(fd2[WRITE]);
		
		printf("(a,b)=");
		scanf("%d%d", &v.a, &v.b);
		
		while (write(fd1[WRITE], &v, sizeof(v)) < 1)
		{
		}
				
		wait(NULL);
		
		while (read(fd2[READ], &r, sizeof(r)) < 1)
		{
		}
		
		char divisionResult[16];
		
		if (r.invalid)
		{
			sprintf(divisionResult, "NaN");
		}
		else
		{
			sprintf(divisionResult, "%.4f", r.div);
		}
		
		printf("(a,b)(+,-,*,/) = (%d,%d)(%d,%d,%d,%s)\n",
				v.a, v.b, r.sum, r.sub, r.mul, divisionResult);
		
		close(fd1[WRITE]);
		close(fd2[READ]);
	}
	else
	{
		close(fd1[WRITE]);
		close(fd2[READ]);
		
		while (read(fd1[READ], &v, sizeof(v)) < 1)
		{
		}
				
		r.sum = v.a + v.b;
		r.sub = v.a - v.b;
		r.mul = v.a * v.b;
		
		if (v.b == 0)
		{
			r.invalid = 1;
		}
		else
		{
			r.div = (double) v.a / v.b;
			r.invalid = 0;
		}
		
		while (write(fd2[WRITE], &r, sizeof(r)) < 1)
		{
		}
		
		close(fd1[READ]);
		close(fd2[WRITE]);
	}
	
	return 0;
}