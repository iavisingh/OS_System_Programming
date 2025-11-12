#include <unistd.h>

int main() {
    if (fork() == 0) {
        execl("/bin/ls", "ls", "-l", NULL);
    }
    return 0;
}
