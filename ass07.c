#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[])
{
    double a, b, c;

    printf("Enter the value of variable 'A': ");
    scanf("%lf", &a);
    printf("Enter the value of variable 'B': ");
    scanf("%lf", &b);
    printf("Enter the value of variable 'C': ");
    scanf("%lf", &c);

    double r1 = (-b + sqrt(pow(b, 2) - 4*a*c)) / (2*a);
    double r2 = (-b - sqrt(pow(b, 2) - 4*a*c)) / (2*a);

    double x1 = a * pow(r1, 2) + b * r1 + c;
    double x2 = a * pow(r2, 2) + b * r2 + c;

    printf("The first solution is: %lf\n", r1);
    if(x1 != 0)
        printf("But you might want to double-check that ...\n");

    printf("The second solution is: %lf\n", r2);
    if(x2 != 0)
        printf("But you might want to double-check that ...\n");

    return 0;
}
