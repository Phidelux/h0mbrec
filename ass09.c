#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if(argc != 3) {
        fprintf(stderr, "%s: Invalid number of arguments!\n", argv[0]);
        return 1;
    }

    printf("Hello, %s %s!\n", argv[1], argv[2]);

    return 0;
}
