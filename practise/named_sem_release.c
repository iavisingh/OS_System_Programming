#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    sem_t *sem = sem_open("/mysem", 0);

    if (sem == SEM_FAILED) {
        perror("sem_open");
        return 1;
    }

    printf("Reader: waiting for semaphore...\n");
    sem_wait(sem);
    printf("Reader: got the semaphore!\n");

    sem_post(sem);
    sem_close(sem);

    return 0;
}

