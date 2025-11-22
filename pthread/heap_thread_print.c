#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


void *routine(void *arg)
{	
	int total = 0;

	while(1) {

		void *p = malloc(1024);
		if(p) *((char *)p) = 1;
		if(p) {

			total += 1024;
			printf("routine allocated:%d, total:%d\n", 1024, total);
			printf("current break: %p\n", sbrk(0));

		}	
		sleep(1);

	}
	return NULL;

}


void main()
{
	pthread_t th;
	int ret;

	printf("main now creating thread\n");

	ret = pthread_create(&th, NULL, routine, NULL);
	if(0 != ret) {
		printf("routine create err\n");
	}
	
	printf("main waiting for pthread to exit\n");
	pthread_join(th, NULL);
	printf("main received that routine had exited\n");

}




