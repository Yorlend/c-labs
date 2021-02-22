#include <stdio.h>

int main()
{
    double r1, r2, r3, r;

    printf("Input R1, R2, R3: ");
    scanf("%lf%lf%lf", &r1, &r2, &r3);

    r = r1*r2*r3/(r1*r2 + r1*r3 + r2*r3);
    printf("Circuit resistance:\n R=%.6lf Ohm\n", r);

    return 0;
}