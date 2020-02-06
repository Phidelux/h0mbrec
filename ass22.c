#include <stdio.h>

#define NO_PLAYERS 5

typedef struct stats {
    int points;
    int games;
} stats_t;

int main(int argc, char *argv[])
{
    stats_t players[NO_PLAYERS];

    for(int i = 0; i < NO_PLAYERS; i++) {
        printf("Enter Player %d's point total: ", i+1);
        scanf("%d", &players[i].points);
        printf("Enter Player %d's game total: ", i+1);
        scanf("%d", &players[i].games);
    }

    puts("");

    for(int i = 0; i < NO_PLAYERS; i++)
        printf("Player %d's scoring average was %.2lf ppg.\n",
                i+1, ((double)players[i].points) / players[i].games);

    return 0;
}
