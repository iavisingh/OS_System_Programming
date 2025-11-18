#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    sem_t *sem = sem_open("/mysem", O_CREAT, 0666, 1);

    if (sem == SEM_FAILED) {
        perror("sem_open");
        return 1;
    }

    sem_wait(sem);
    printf("Writer: acquired semaphore\n");
    sleep(5);
    printf("Writer: releasing\n");
    sem_post(sem);

    sem_close(sem);
    return 0;
}

