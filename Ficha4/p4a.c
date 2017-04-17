// PROGRAMA p04a.c

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(void)
{
	pid_t pid;
 	int i, n, status;
 	for (i=1; i<=3; i++) 
 	{
 		pid=fork(); 
 		if (pid == 0)
 		{
 			printf("CHILD no. %d (PID=%d) working ... \n",i,getpid());
 			sleep(i*7); // child working ...
 			printf("CHILD no. %d (PID=%d) exiting ... \n",i,getpid());
 			exit(0);
 		}
 	}

 	for (i=1 ;i<=4; i++ ) 
 	{
 		printf("PARENT: working hard (task no. %d) ...\n",i);
 		n=20; while((n=sleep(n))!=0);
 		printf("PARENT: end of task no. %d\n",i);
 		printf("PARENT: waiting for child no. %d ...\n",i);
 		pid=wait(&status);
 		if (pid != -1)
 			printf("PARENT: child with PID=%d terminated with exit code %d\n",pid,WEXITSTATUS(status));
 	}
 exit(0);
} 

/*
marisa@marisa-VirtualBox:~$ ps u
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
marisa    9912  0.0  0.5  22808  5380 pts/17   Ss   17:51   0:00 bash
marisa   10034  0.0  0.5  22704  5208 pts/18   Ss   18:08   0:00 bash
marisa   10044  0.0  0.0   4356   724 pts/17   S+   18:08   0:00 ./p4a
marisa   10046  0.0  0.0      0     0 pts/17   Z+   18:08   0:00 [p4a] <defunct>
marisa   10047  0.0  0.0      0     0 pts/17   Z+   18:08   0:00 [p4a] <defunct>
marisa   10059  0.0  0.3  37408  3344 pts/18   R+   18:09   0:00 ps u
marisa@marisa-VirtualBox:~$ ps u
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
marisa    9912  0.0  0.5  22808  5380 pts/17   Ss   17:51   0:00 bash
marisa   10034  0.0  0.5  22704  5208 pts/18   Ss   18:08   0:00 bash
marisa   10044  0.0  0.0   4356   724 pts/17   S+   18:08   0:00 ./p4a
marisa   10047  0.0  0.0      0     0 pts/17   Z+   18:08   0:00 [p4a] <defunct>
marisa   10060  0.0  0.3  37408  3256 pts/18   R+   18:09   0:00 ps u
marisa@marisa-VirtualBox:~$ ps u
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
marisa    9912  0.0  0.5  22808  5380 pts/17   Ss   17:51   0:00 bash
marisa   10034  0.0  0.5  22704  5208 pts/18   Ss   18:08   0:00 bash
marisa   10044  0.0  0.0   4356   724 pts/17   S+   18:08   0:00 ./p4a
marisa   10047  0.0  0.0      0     0 pts/17   Z+   18:08   0:00 [p4a] <defunct>
marisa   10061  0.0  0.3  37408  3268 pts/18   R+   18:09   0:00 ps u
marisa@marisa-VirtualBox:~$ ps u
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
marisa    9912  0.0  0.5  22808  5380 pts/17   Ss   17:51   0:00 bash
marisa   10034  0.0  0.5  22704  5208 pts/18   Ss   18:08   0:00 bash
marisa   10044  0.0  0.0   4356   724 pts/17   S+   18:08   0:00 ./p4a
marisa   10047  0.0  0.0      0     0 pts/17   Z+   18:08   0:00 [p4a] <defunct>
marisa   10064  0.0  0.3  37408  3368 pts/18   R+   18:09   0:00 ps u
marisa@marisa-VirtualBox:~$ ps u
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
marisa    9912  0.0  0.5  22808  5380 pts/17   Ss   17:51   0:00 bash
marisa   10034  0.0  0.5  22704  5208 pts/18   Ss   18:08   0:00 bash
marisa   10044  0.0  0.0   4356   724 pts/17   S+   18:08   0:00 ./p4a
marisa   10047  0.0  0.0      0     0 pts/17   Z+   18:08   0:00 [p4a] <defunct>
marisa   10065  0.0  0.3  37408  3292 pts/18   R+   18:09   0:00 ps u
marisa@marisa-VirtualBox:~$ ps u
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
marisa    9912  0.0  0.5  22808  5380 pts/17   Ss   17:51   0:00 bash
marisa   10034  0.0  0.5  22704  5208 pts/18   Ss   18:08   0:00 bash
marisa   10044  0.0  0.0   4356   724 pts/17   S+   18:08   0:00 ./p4a
marisa   10047  0.0  0.0      0     0 pts/17   Z+   18:08   0:00 [p4a] <defunct>
marisa   10066  0.0  0.3  37408  3252 pts/18   R+   18:09   0:00 ps u
marisa@marisa-VirtualBox:~$ ps u
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
marisa    9912  0.0  0.5  22808  5380 pts/17   Ss   17:51   0:00 bash
marisa   10034  0.0  0.5  22704  5208 pts/18   Ss   18:08   0:00 bash
marisa   10044  0.0  0.0   4356   724 pts/17   S+   18:08   0:00 ./p4a
marisa   10067  0.0  0.3  37408  3292 pts/18   R+   18:09   0:00 ps u
marisa@marisa-VirtualBox:~$ ps u
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
marisa    9912  0.0  0.5  22808  5380 pts/17   Ss   17:51   0:00 bash
marisa   10034  0.0  0.5  22704  5208 pts/18   Ss   18:08   0:00 bash
marisa   10044  0.0  0.0   4356   724 pts/17   S+   18:08   0:00 ./p4a
marisa   10068  0.0  0.3  37408  3344 pts/18   R+   18:09   0:00 ps u
marisa@marisa-VirtualBox:~$ ps u
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
marisa    9912  0.0  0.5  22808  5380 pts/17   Ss   17:51   0:00 bash
marisa   10034  0.0  0.5  22704  5208 pts/18   Ss   18:08   0:00 bash
marisa   10044  0.0  0.0   4356   724 pts/17   S+   18:08   0:00 ./p4a
marisa   10069  0.0  0.3  37408  3264 pts/18   R+   18:09   0:00 ps u
marisa@marisa-VirtualBox:~$ ps u
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
marisa    9912  0.0  0.5  22808  5380 pts/17   Ss   17:51   0:00 bash
marisa   10034  0.0  0.5  22704  5208 pts/18   Ss   18:08   0:00 bash
marisa   10044  0.0  0.0   4356   724 pts/17   S+   18:08   0:00 ./p4a
marisa   10070  0.0  0.3  37408  3276 pts/18   R+   18:10   0:00 ps u
marisa@marisa-VirtualBox:~$ ps u
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
marisa    9912  0.0  0.5  22808  5380 pts/17   Ss   17:51   0:00 bash
marisa   10034  0.0  0.5  22704  5208 pts/18   Ss   18:08   0:00 bash
marisa   10044  0.0  0.0   4356   724 pts/17   S+   18:08   0:00 ./p4a
marisa   10071  0.0  0.3  37408  3272 pts/18   R+   18:10   0:00 ps u
marisa@marisa-VirtualBox:~$ ps u
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
marisa    9912  0.0  0.5  22808  5380 pts/17   Ss   17:51   0:00 bash
marisa   10034  0.0  0.5  22704  5208 pts/18   Ss   18:08   0:00 bash
marisa   10044  0.0  0.0   4356   724 pts/17   S+   18:08   0:00 ./p4a
marisa   10072  0.0  0.3  37408  3272 pts/18   R+   18:10   0:00 ps u
marisa@marisa-VirtualBox:~$ ps u
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
marisa    9912  0.0  0.5  22808  5380 pts/17   Ss+  17:51   0:00 bash
marisa   10034  0.0  0.5  22704  5208 pts/18   Ss   18:08   0:00 bash
marisa   10073  0.0  0.3  37408  3368 pts/18   R+   18:10   0:00 ps u
marisa@marisa-VirtualBox:~$ 

omd, kê?

*/