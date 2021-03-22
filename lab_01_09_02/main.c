#include <stdio.h>
#include <math.h>

double expression(double x, int n);

int main(void)
{
    double g = 0, x;
    int n = 0;

    if (scanf("%lf", &x) != 1)
        return 1;

    while (x >= 0)
    {
        n++;
        g += expression(x, n);
        if (scanf("%lf", &x) != 1)
            return 1;
    }

    if (n == 0)
        return 1;
    
    g = g / n;

    printf("%lf\n", g);

    return 0;
}

double expression(double x, int n)
{
    return sqrt(n + x);
}