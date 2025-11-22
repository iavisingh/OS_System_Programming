#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


void *thread1(void *arg)
{
	while(1) {
		printf("Thread 1\n");
		sleep(1);
	}
}

void *thread2(void *arg) 
{
	while(1) {
		printf("\t\t\t Thread 2\n");
		sleep(1);
	}
}

void main()
{
	pthread_t th[2];
	int ret;

	pthread_create(&th[0], NULL, thread1, NULL);
	pthread_create(&th[1], NULL, thread2, NULL);

	pthread_join(th[0], NULL);
	pthread_join(th[1], NULL);

}



