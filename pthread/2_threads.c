#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

void *thread1(void *arg)
{
	int count = 0;
	while(1) {
		printf("Thread 1: %d\n", count);
		sleep(1);

		count++;
		if(count == 5) {
			pthread_exit(NULL);
		}
	}
}

void *thread2(void *arg) 
{
	int count = 0;
	while(1) {
		printf("\t\t\t Thread 2: %d\n", count);
		sleep(1);
		
		count++;
		if(count == 10) {
			pthread_exit(NULL);
		}
	}
}

void main()
{
	pthread_t th[2];
	int ret;

	pthread_create(&th[0], NULL, thread1, NULL);
	pthread_create(&th[1], NULL, thread2, NULL);
	
	//sleep(2);
	
	printf("main waiting for thread1 \n");
	pthread_join(th[0], NULL);
	printf("main received exit from thread1\n");

	printf("main waiting for thread2\n");
	pthread_join(th[1], NULL);
	printf("main received exit from thread 2\n");
	//pthread_detach(th[0]);
	//pthread_detach(th[1]);
}



