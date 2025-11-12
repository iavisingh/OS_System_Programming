#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *routine(void *arg) 
{
	int itr = 0;
	printf("routine entry\n");
	while(1) 
	{
		++itr;
		printf("routine: %d\n", itr);
		sleep(1);
		
		if(itr >= 10) {
			pthread_exit(NULL);
		}
	}
}


void main()
{
	pthread_t thread;
	printf("main application\n");
	pthread_create(&thread, NULL, routine, NULL);
	pthread_join(thread, NULL);
	printf("main app exit\n");
}
