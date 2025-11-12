#include <unistd.h>
#include <stdio.h>


void main()
{
	int ret;

	printf("print before fork\n");
	ret = fork();
	if(ret == 0) {
		printf("This is child process\n");
	} else if (ret > 0) {
		printf("This is parent process\n");
	} else {
		printf("fork fail\n");
	}
}
		
