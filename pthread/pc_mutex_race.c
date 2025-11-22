#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>


int count = 0;
#define MAX_COUNT (1000000)

pthread_mutex_t mutex;

void *thread(void *arg) 
{
	int ret = 0;
	printf("THREAD ENTERED ==>>\n");

	for (int i = 0; i < MAX_COUNT; i++) {
	
		pthread_mutex_lock(&mutex);	
		count++;
		pthread_mutex_unlock(&mutex);	
	}
}

void main()
{
	int ret;
	pthread_t th[2];
	

	ret = pthread_mutex_init(&mutex, NULL);
	if(0 == ret) {
		printf("mutex created\n");
	} else {
		perror("mutex create err\n");
		exit(1);
	}

	ret = pthread_create(&th[0], NULL, thread, NULL);
	ret = pthread_create(&th[1], NULL, thread, NULL);

	ret = pthread_join(th[0], NULL);
	ret = pthread_join(th[1], NULL);

	printf("MAIN: Counter Value: %d, expected: %d\n", count,2 * MAX_COUNT);
}
