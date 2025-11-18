#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 100   // shared memory size

int main() {
    key_t key;
    int shmid;
    char *data;

    // Create a unique key using ftok()
    key = ftok("/tmp", 'S');   // file must exist; /tmp always exists
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create shared memory segment
    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    printf("Shared memory created, ID = %d\n", shmid);

    // Attach to the shared memory
    data = (char *)shmat(shmid, NULL, 0);
    if (data == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    // ---------------- WRITE ----------------
    const char *msg = "Hello from shared memory!";
    strcpy(data, msg);
    printf("Written to shared memory: %s\n", msg);

    // ---------------- READ ----------------
    printf("Read from shared memory: %s\n", data);

    // Detach from memory
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(1);
    }

    // Delete shared memory
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }

    printf("Shared memory deleted.\n");

    return 0;
}

