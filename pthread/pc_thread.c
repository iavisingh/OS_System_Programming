#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int count = 1;

void *producer(void *arg) 
{
	while(1) {
		count++;
		printf("producer: %d\n", count);
		sleep(1);
	}
}

void *consumer(void *arg)
{
	while(1) {
		count--;
		printf("\t\t\tconsumer: %d\n", count);
		sleep(1);
	}
}


void main()
{
	int ret;
	pthread_t th[2];

	pthread_create(&th[0], NULL, producer, NULL);
	pthread_create(&th[1], NULL, consumer, NULL);

	pthread_join(th[0], NULL);
	pthread_join(th[1], NULL);
}
