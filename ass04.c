#include <stdio.h>
#include <math.h>

#define PIE M_PI

int main(int argc, char *argv[])
{
    double radius;

    printf("Enter the radius of your circle: ");
    scanf("%lf", &radius);

    double area = M_PI * pow(radius, 2);

    printf("The area of your circle is %.2lf\n", area);

    return 0;
}
