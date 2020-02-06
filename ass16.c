#include <stdio.h>

int main(int argc, char *argv[])
{
    int array[10];

    printf("%p\n", array);
    printf("%p\n", &array[0]);

    return 0;
}
