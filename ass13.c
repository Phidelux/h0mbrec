#include <stdio.h>
#include <string.h>

#define NO_GAMES 4
#define NO_PLAYERS 5

int main(int argc, char *argv[])
{
    int scores[NO_GAMES][NO_PLAYERS];

    double totals[NO_PLAYERS];
    memset(&totals, 0, NO_PLAYERS * sizeof(double));

    for(int i = 0; i < NO_GAMES; i++) {
        printf("Game #%d\n", i+1);

        for(int j = 0; j < NO_PLAYERS; j++) {
            printf("Enter scoring total for Player #%d: ", j+1);
            scanf("%d", &scores[i][j]);

            totals[j] += scores[i][j];
        }
    }

    int maxTotal = 0;
    for(int i = 1; i < NO_PLAYERS; i++)
        if(totals[maxTotal] < totals[i])
            maxTotal = i;

    printf("Player #%d had the highest scoring average at %.2lf points per game.\n", maxTotal+1, totals[maxTotal] / NO_GAMES);

    return 0;
}
