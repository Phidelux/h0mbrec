#include <stdio.h>

typedef struct type {
    int i;
    char c;
    float f;
} type_t;

int main(int argc, char *argv[])
{
    type_t t = {
        .i = 13,
        .c = 'X',
        .f = 12.34
    };

    printf("This is the int: %d\n", t.i);
    printf("This is the char: %c\n", t.c);
    printf("This is the float: %.2f\n", t.f);

    return 0;
}
