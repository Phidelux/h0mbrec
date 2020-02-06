#include <stdio.h>

void test1();
void test2();

void test1()
{
    char array[] = {72, 101, 108, 108, 111, 44, 32, 87, 111, 114, 108, 100, 33};
    printf("%s", array);
    puts(array);
}

void test2()
{
    char array[] = {72, 101, 108, 108, 111, 44, 32, 87, 111, 114, 108, 100, 33, '\0'};

    printf("%s", array);
    puts(array);
}

int main(int argc, char *argv[])
{
    printf("Test non-terminated string:\n");
    test1();
    printf("Test null-terminated string:\n");
    test2();

    return 0;
}
