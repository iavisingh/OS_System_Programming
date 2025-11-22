#include <stdio.h>
#include <unistd.h>
#include <string.h>

void main()
{

	int ret;

	while(1) {

		/*declaration in loop but the buffer is
		 * created only once when function main() is called
		 * instead with each loop buffer is initialised to 0
		 * and this allow us to avoid explicit memset()
		 * to zero the buffer*/
		char buffer[1024] ={0};

		/*read system call on fd 0 stdin*/
		ret = read(0, buffer, sizeof(buffer));

		/*ret > 0 mean value received
		 * notice-> read only unblock when \n is pressed
		 * this is due to stdin being line buffered meaning 
		 * after \n is pressed all the data is received here 
		 * at that time*/
		if(ret > 0) {
			//ret holds how much data is received from stdin
			printf("read:%d from stdin:\n%s",ret, buffer);
			
			/*printf to stdout fd 1, 
			 * note printf calls write at fd 1 internally 
			 * which is buffered and only flushes out when
			 * than buffer is full, \n is there , 
			 * fflush(stdout) is done, or program exits*/
			printf("now writing to stdout:\n");
			write(1, buffer, ret);
			/*stderr is unbuffered so it doesnt depends on 
			 * buffer full ,\n etc*/
			printf("now writing to sterr:\n");
			write(2, buffer, ret);
		} else {
			perror("read fail from stdin\n");
		}
	}
}

