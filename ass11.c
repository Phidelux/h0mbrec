#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INITIAL_CAPACITY 3

int main(int argc, char *argv[])
{
    char choice[] = "y";

    double *scores = malloc(INITIAL_CAPACITY * sizeof(double));
    if(!scores) {
        fprintf(stderr, "Failed to allocate scores array.\n");
        return 1;
    }

    int capacity = INITIAL_CAPACITY;

    int numScores;

    for(numScores = 0; strcmp(choice, "y") == 0; ++numScores) {
        if(numScores == capacity) {
            capacity *= 2;
            scores = realloc(scores, capacity * sizeof(double));
            if(!scores) {
                fprintf(stderr, "Failed to allocate scores array.\n");
                return 1;
            }
        }

        printf("Enter a test score: ");
        scanf("%lf", &scores[numScores]);

        printf("Would you like to continue? y/n ");
        scanf("%s", &choice[0]);
    }

    double sum = 0;
    for(int i = 0; i < numScores; i++)
        sum += scores[i];

    printf("The average of your scores is %.2lf\n", sum / numScores);

    free(scores);

    return 0;
}
