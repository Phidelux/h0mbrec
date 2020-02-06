#include <stdio.h>

int main(int argc, char *argv[])
{
    int x = 13;
    int *xp = &x;

    printf("The value of our pointer is: %p\n", xp);

    return 0;
}
