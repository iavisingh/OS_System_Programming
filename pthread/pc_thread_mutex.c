#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>


int count = 1;
pthread_mutex_t mutex;
sem_t can_produce, can_consume;

void *producer(void *arg) 
{
	int ret = 0;
	printf("PRODUCER THREAD\n");
	while(1) {
		
	//	sem_wait(&can_produce);

		//ret = pthread_mutex_lock(&mutex);	
		count++;
		printf("producer: %d\n", count);
		//ret = pthread_mutex_unlock(&mutex);
		
	//	sem_post(&can_consume);
		
		//usleep(500);


	}
}

void *consumer(void *arg)
{
	int ret;
	printf("\t\t\tCONSUMER THREAD\n");
	while(1) {
		
	//	sem_wait(&can_consume);

		//ret = pthread_mutex_lock(&mutex);
		count--;
		printf("\t\t\tconsumer: %d\n", count);
		//ret = pthread_mutex_unlock(&mutex);
		
	//	sem_post(&can_produce);
		//usleep(500);

	}
}


void main()
{
	int ret;
	pthread_t th[2];
	
	ret = sem_init(&can_produce, 0, 1);
	ret = sem_init(&can_consume, 0, 0);

	ret = pthread_mutex_init(&mutex, NULL);
	if(0 == ret) {
		printf("mutex created\n");
	} else {
		perror("mutex create err\n");
		exit(1);
	}

	ret = pthread_create(&th[0], NULL, producer, NULL);
	if(0 == ret) {
		printf("producer created\n");
	} else {
		perror("producer create err\n");
	}
	
	ret = pthread_create(&th[1], NULL, consumer, NULL);
	if(0 == ret) {
		printf("consumer created\n");
	} else {
		perror("consumer create err\n");
	}

	ret = pthread_join(th[0], NULL);
	ret = pthread_join(th[1], NULL);
}
