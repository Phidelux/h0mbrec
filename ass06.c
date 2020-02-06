#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int numerator, denominator;

    printf("Enter a numerator: ");
    scanf("%d", &numerator);

    printf("Enter a denominator: ");
    scanf("%d", &denominator);

    if(numerator % denominator != 0)
        printf("There is a remainder!\n");
    else
        printf("There is NOT a remainder!\n");

    return 0;
}
