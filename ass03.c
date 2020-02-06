#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *firstname;
    char *lastname;

    printf("Enter your first name: ");
    scanf("%ms", &firstname);

    printf("Enter your last name: ");
    scanf("%ms", &lastname);

    printf("Hello, %s %s!\n", firstname, lastname);

    free(firstname);
    free(lastname);

    return 0;
}
