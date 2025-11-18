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

	pipe = open(PIPE_PATH, O_RDONLY);
	if(pipe < 0) {
		printf("pipe: %s, open err: %d\n", PIPE_PATH, pipe);
		return;
	} else {
		printf("pipe: %s, openfd: %d\n", PIPE_PATH, pipe);
	}
	
	printf("pipe: %s, Reading \n", PIPE_PATH);

	while(1) {
		
		ret = read(pipe, buffer, sizeof(buffer));
		if(ret > 0) {
			printf("Read: %d, Buffer: %s\n", ret, buffer);
		}

	}	
}

