#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sem;

void* worker(void *arg) {
    sem_wait(&sem);
    printf("Worker got the semaphore\n");
    sem_post(&sem);
    return NULL;
}

int main() {
    pthread_t t;

    sem_init(&sem, 0, 1);   // pshared = 0 means semaphore is shared between threads

    pthread_create(&t, NULL, worker, NULL);

    sem_wait(&sem);
    printf("Main got the semaphore\n");
    sleep(1);
    sem_post(&sem);

    pthread_join(t, NULL);

    sem_destroy(&sem);
    return 0;
}

