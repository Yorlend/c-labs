#include <stdio.h>

int main()
{
    double r1, r2, r3, r;

    scanf("%lf%lf%lf", &r1, &r2, &r3);

    r = r1 * r2 * r3 / (r1 * r2 + r1 * r3 + r2 * r3);
    printf("Circuit resistance:\n %.6lf\n", r);

    return 0;
}