#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int seconds;

    printf("Please enter number of seconds: ");
    scanf("%d", &seconds);

    int secs = seconds % 60;

    int hours = seconds / 3600;

    int minutes = (seconds - hours * 3600) / 60;

    printf("\n%d seconds is equal to %d hours, %d minutes, and %d seconds.\n", seconds, hours, minutes, secs);

    return 0;
}
