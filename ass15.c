#include <stdio.h>

int main(int argc, char *argv[])
{
    int x = 13;
    int *xp = &x;

    printf("The value of int variable is: %d\n", x);
    printf("The value of the pointer to the int variable is: %p\n", xp);
    printf("The memory address of the int variable is: %p\n", &x);
    printf("The value held at the memory location that the pointer is pointing to is: %d\n", *xp);

    return 0;
}
