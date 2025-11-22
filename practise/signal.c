#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("Caught signal %d once. Restoring default...\n", sig);

    // Restore default action for next time
    //signal(sig, SIG_DFL);
}

int main() {
    // Install handler once
    signal(SIGINT, handler);

    printf("PID = %d. Press Ctrl+C twice.\n", getpid());

    while (1) {
        printf("Running...\n");
        sleep(1);
    }

    return 0;
}

