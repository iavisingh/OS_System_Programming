#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void timer_handler(int sig) {
    printf("Timer expired! Caught SIGALRM.\n");
}

int main() {
    // Register signal handler to SIGLARM
    signal(SIGALRM, timer_handler);

    printf("Setting 3-second timer...\n");
    alarm(3);       // After 3 seconds, SIGALRM is sent

    printf("Waiting...\n");

    while (1) {
        sleep(1);
    }

    return 0;
}

