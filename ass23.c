#include <stdio.h>

typedef struct simple {
    int i;
} simple_t;

int main(int argc, char *argv[])
{
    simple_t s;
    simple_t *sp = &s;

    s.i = 13;
    printf("%d\n", s.i);

    (*sp).i = 14;
    printf("%d\n", s.i);

    sp->i = 15;
    printf("%d\n", s.i);

    return 0;
}
