#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/times.h>

int main(int argc, char** argv) {
	clock_t programStart;
	clock_t programEnd;

	struct tms t;

	long clockTicks = sysconf(_SC_CLK_TCK);

	if (argc != 3) {
		printf("usage: <upper limit> <stop condition>\n");
		return 0;	
	}

	srand(time(NULL));

	int randomNumber = 0;
	int currentIteration = 0;
	int upperLimit = atoi(argv[1]);
	int stopCondition = atoi(argv[2]);
	
	if (upperLimit == 0) {
		return 0;
	}

	programStart = times(&t);

	while (randomNumber != stopCondition) {
		randomNumber = rand() % upperLimit;
		currentIteration++;

		printf("i=%d,n=%d\n", currentIteration, randomNumber);
	}

	programEnd = times(&t);

	printf("Clock: %4.2f s\n", (double)(programEnd-programStart)/clockTicks);
	printf("User time: %4.2f s\n", (double)t.tms_utime/clockTicks);
	printf("System time: %4.2f s\n", (double)t.tms_stime/clockTicks);
	printf("Children user time: %4.2f s\n", (double)t.tms_cutime/clockTicks);
	printf("Children system time: %4.2f s\n", (double)t.tms_cstime/clockTicks);

	return 0;
}

