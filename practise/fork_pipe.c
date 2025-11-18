#include <unistd.h>
#include <stdio.h>
#include <string.h>


void main()
{
	int ret, pipefd[2] = {0};

	ret = pipe(pipefd);
	if (0 == ret) {
		printf("pipe created readfd:%d, writefd:%d\n", 
			pipefd[0], pipefd[1]);
	} else {
		printf("pipe create error: ret: %d\n", ret);
		return;
	}

	ret = fork();

	if(0 == ret) {
		
		char *str = "HELLO FROM CHILD";
		printf("Child process\n");
		ret = write(pipefd[1], str, strlen(str));
		printf("Child pipe write: %d, %s\n", ret, str);


	} else if (ret > 0) {

		char buffer[1024] = {0};
		printf("Parent process: Child PID:%d\n", ret);
		ret = read(pipefd[0], buffer, sizeof(buffer));
		if(ret > 0) {
			printf("Parent read: %d, %s\n", ret, buffer);
		} else {
			printf("Parent read: %d err\n", ret);
		}
	
	} else {
		printf("fork failure\n");

	}	

	close(pipefd[0]);
	close(pipefd[1]);

}
	
