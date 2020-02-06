#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int num;

    printf("Enter a number between 1 and 500: \n");
    scanf("%d", &num);

    if(num < 1)
        printf("Your number was not in any of our ranges.\n");
    else if(num < 100)
        printf("Your number is between 1 and 100: \n");
    else if(num < 200)
        printf("Your number is between 101 and 200: \n");
    else if(num < 300)
        printf("Your number is between 201 and 300: \n");
    else if(num < 400)
        printf("Your number is between 301 and 400: \n");
    else if(num < 500)
        printf("Your number is between 401 and 500: \n");
    else
        printf("Your number was not in any of our ranges.\n");

    return 0;
}
