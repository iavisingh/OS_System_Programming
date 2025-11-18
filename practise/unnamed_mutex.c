#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* worker(void *arg) {
    pthread_mutex_lock(&lock);
    printf("Thread got lock\n");
    sleep(1);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t t;
    pthread_create(&t, NULL, worker, NULL);

    pthread_mutex_lock(&lock);
    printf("Main got lock\n");
    sleep(1);
    pthread_mutex_unlock(&lock);

    pthread_join(t, NULL);
    return 0;
}

