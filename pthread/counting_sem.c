#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>

sem_t stove_sem;


void *cook_thread(void *arg) 
{
	int cook_no =  *(int *)arg;
	printf("Cook no: %d ready\n", cook_no);

	while(1) {
		
		printf("Cook no: %d WAITING!!!\n", cook_no);
		sem_wait(&stove_sem);

		printf("Cook no: %d cooking ====>>>\n", cook_no);
		sleep(5);
		
		//printf("Cook no: %d LEFT!!! cooking\n", cook_no);
		sem_post(&stove_sem);

	}
	pthread_exit(NULL);
}


void main()
{
	int ret;
	pthread_t th[3];
	int cook[3] = {1,2,3};

	ret = sem_init(&stove_sem, 0, 2);
	if(0 != ret) {
		perror("sem create err\n");
		return;
	}

	for(int i = 0; i < 3; i++) {
		pthread_create(&th[i], NULL, cook_thread, (void *)&cook[i]);
	}

	for(int i = 0; i < 3; i++) {
		pthread_join(th[i], NULL);
	}
}

