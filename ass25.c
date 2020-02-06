#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int fd = open("test.txt", O_WRONLY | O_CREAT, S_IRWXU);
    if(fd < 0) {
        fprintf(stderr, "Failed to open test.txt for writing!\n");
        return 1;
    }

    char *msg = "Hello, World!\n";

    size_t written = write(fd, msg, strlen(msg));
    if(written != strlen(msg)) {
        fprintf(stderr, "Failed to write msg to test.txt!\n");
        return 1;
    }

    if(close(fd) != 0) {
        fprintf(stderr, "Failed to close test.txt!\n");
        return 1;
    }

    return 0;
}
