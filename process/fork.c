#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


void main() 
{
	pid_t pid;
	
	pid = fork();
	
	if(pid == 0) {
		sleep(1);
		printf("child pid: %d\n",getpid());
	       	printf("child ppid: %d\n",getppid());	
		exit(EXIT_SUCCESS);
	} else if (pid == -1) {
		perror("fork err\n");
	} else {
		int stat_loc;
		printf("parent pid: %d\n",getpid());
		printf("parent ppid: %d\n",getppid());
		wait(&stat_loc);
		printf("child exit stat: %d\n",stat_loc);
		exit(EXIT_SUCCESS);
	}

}
