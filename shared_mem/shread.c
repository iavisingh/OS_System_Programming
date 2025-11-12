#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define SHARED_MEM_FILE 	"shmfile"
#define PROJECT_ID 		'A'
#define SHM_MEM_SIZE 		(1024U)

int main(int argc, char *argv[])
{
	FILE *shmfile;
	key_t key;
	int shmid;
	void *mem;

	shmfile = fopen(SHARED_MEM_FILE, "a");
	if(!shmfile) {
		perror("shm fopen");
		exit(EXIT_FAILURE);
	}

	fclose(shmfile);

	key = ftok(SHARED_MEM_FILE, PROJECT_ID);
	if(-1 == key) {
		perror("ftok");
		exit(EXIT_SUCCESS);
	}

	shmid = shmget(key, SHM_MEM_SIZE, 0666 | IPC_CREAT);
	if(-1 == shmid) {
		perror("shmget");
		exit(EXIT_SUCCESS);
	}

	mem = shmat(shmid, NULL, 0);
	if((void *)(-1) == mem) {
		perror("shmat");
	}

	printf("read memory:%s\n",(char *)mem);
	shmdt(mem);
	
	shmctl(shmid, IPC_RMID, NULL);
	exit(EXIT_SUCCESS);

}
