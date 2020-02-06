#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd = open("test.txt", O_WRONLY | O_CREAT, S_IRWXU);
    if(fd < 0) {
        fprintf(stderr, "Failed to open test.txt for writing!\n");
        return 1;
    }

    close(fd);

    return 0;
}
