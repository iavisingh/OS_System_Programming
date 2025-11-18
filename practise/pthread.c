#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* routine(void *arg)
{
	int count = 0;
	
	/*address of int var captured in arg*/
	printf("argument in routine: %p\n", arg);

	for(;;) {
		
		++count;
		printf("Thread:%d(s)\n", count);
		sleep(1);

		if(count > 10) {
			/*exit thread*/
			pthread_exit(NULL);
		}

	}
}

void main()
{
	pthread_t thread_id;
	int ret;
	int var; //local variable to pass to thread
	printf("local var: %p\n", &var);

	/*ret, to check if thread create success or failure
	thread_id, handle to control , wait its deletion, etc.
	routine, function thread to be created.
	&var, address to be passed in thread as arguments*/
	ret = pthread_create(&thread_id, NULL, routine, &var); 
	if(0 == ret) {
		printf("thread created\n");
	} else {
		printf("thread create err: %d\n", ret);
		return;
	}
	
	/*use handle of thread created to wait for it deletion*/
	ret = pthread_join(thread_id, NULL);
	if(0 == ret) {
		printf("thread joined\n");
	} else {
		printf("thread join err: %d\n", ret);
		return;
	}
	
	printf("main exited with thread joined\n");
}
