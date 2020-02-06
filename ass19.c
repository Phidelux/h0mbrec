#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 16

int main(int argc, char *argv[])
{
    char *str = malloc(BUFFER_SIZE * sizeof(char));
    if(!str) {
        fprintf(stderr, "Failed to allocate buffer of size %d.\n", BUFFER_SIZE);
        return 1;
    }

    printf("Successfully allocated buffer of size %d.\n", BUFFER_SIZE);

    free(str);

    return 0;
}
