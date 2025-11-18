#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define PIPE_PATH "/tmp/my_pipe"

void main()
{
	int ret, pipe = 0;
	char buffer[1024] = {0};

	ret = mkfifo(PIPE_PATH, 0666);
	if(0 == ret) {
		printf("pipe: %s, create success\n", PIPE_PATH);
	} else {
		int err = errno;
		printf("pipe: %s, create err: %d, %s\n", 
				PIPE_PATH, err, strerror(errno));
		if(err != 17)
			return;
	}

	pipe = open(PIPE_PATH, O_WRONLY);
	if(pipe < 0) {
		printf("pipe: %s, open err: %d\n", PIPE_PATH, pipe);
		return;
	} else {
		printf("pipe: %s, openfd: %d\n", PIPE_PATH, pipe);
	}
	
	printf("pipe: %s, Writing \n", PIPE_PATH);
	
	int count = 0;
	while(1) {
		
		memset(buffer, 0, sizeof(buffer));
		sprintf(buffer, "MSG count: %d", count);


		ret = write(pipe, buffer, sizeof(buffer));
		if(ret > 0) {
			printf("Write: %d, Buffer: %s\n", ret, buffer);
			++count;
		}
		sleep(1);
	}


	//unlink(PIPE_PATH);	
}

