#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd = open("all_in_one.bin", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) return 1;

    char buffer[4096];
    memset(buffer, 'A', sizeof(buffer));

    // One single write() system call
    write(fd, buffer, sizeof(buffer));

    close(fd);
    return 0;
}
