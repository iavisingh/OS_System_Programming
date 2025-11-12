#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <fcntl.h>
#include <semaphore.h>
#include "sem.h"

void* routine(void *arg) 
{
	sem_t *sem;

	sem = sem_open(SEMAPHORE1, O_CREAT, 0666, 0);//by default empty semaphore
	if(sem == SEM_FAILED) {
		perror("sem_open");
		pthread_exit(NULL);
	}

	while(1) {
		printf("post sem\n");
		sem_post(sem);
		sleep(5);
	
	}
}




int main(int argc, char *argv[])
{
	pthread_t thread;
	int ret;
	
	ret = pthread_create(&thread, NULL, routine, NULL);
	if(0 != ret) {
		perror("pthread");
		return 1;
	}
	
	printf("routine thread create success\n");
	pthread_join(thread, NULL);
	
	printf("main exit\n");
	return 0;

}
