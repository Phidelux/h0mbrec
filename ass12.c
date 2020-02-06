#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int coinFlips, heads = 0, tails = 0;

    time_t t;

    /* Seed the random number generator */
    srand((unsigned) time(&t));

    printf("How many times would you like to flip the coin? ");
    scanf("%d", &coinFlips);

    for(int i = 0; i < coinFlips; i++) {
        if(rand() % 2 == 0)
            heads++;
        else
            tails++;
    }

    printf("After flipping the coin 5000 times, the results were\n");
    printf("%d heads\n%d tails\n", heads, tails);

    return 0;
}
