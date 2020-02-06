#include <stdio.h>

int main(int argc, char *argv[])
{
    int intvar = 5;
    float floatvar = 3.140000;
    char *string = "Hello, World!";

    printf("%d is an integer!\n", intvar);
    printf("%f is a float!\n", floatvar);
    printf("'%s' is a string!\n", string);

    return 0;
}
