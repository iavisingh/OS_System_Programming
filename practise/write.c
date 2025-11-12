#include <unistd.h>

int main() {
    write(1, "Hello World\n", 12); // 1 = STDOUT file descriptor
    return 0;
}

