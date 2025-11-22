#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void main() {

	int ret;

	printf("Process before fork:pid: %d,ppid: %d\n",
		getpid(), getppid());

	sleep(2);

	ret = fork();

	if(0 == ret) {
		
		int count = 0;
		while(count < 20) {

			count++;
			printf("\t\t\t\tChild Process:pid: %d,ppid: %d\n",
					getpid(), getppid());
			sleep(1);
		}
		printf("\t\t\t\tCHILD TERMINATED NOW\n");

	} else if (0 < ret) {
		
		int count = 0;
		while(count < 10) {
			
			count++;
			printf("Parent Process:pid: %d,ppid: %d\n",
				getpid(), getppid());
			sleep(1);
		}
		printf("PARENT WAITING FOR CHILD TO TERMINATE...\n");
		wait(NULL);
		printf("PARENT UNBLOCKED\n");
		printf("PARENT TERMINATED NOW\n");
	
	} else {

		printf("fork failure\n");
	
	}
}
