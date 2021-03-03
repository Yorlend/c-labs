#include <stdio.h>
#include <math.h>

double f(double x, double eps);

int main(void)
{
    double eps, x, f_aprox, f_exact, err_abs, err_rel;
    if (scanf("%lf%lf", &x, &eps) != 2 || (eps > 1 || eps <= 0) ||
        (x >= 1 || x <= -1))
        return 1;

    f_exact = 1 / ((1 + x) * (1 + x) * (1 + x));
    f_aprox = f(x, eps);

    err_abs = fabs(f_exact - f_aprox);
    err_rel = err_abs / fabs(f_exact);

    printf("%lf %lf %lf %lf\n", f_exact, f_aprox, err_abs, err_rel);

    return 0;
}


double f(double x, double eps)
{
    double result, element, tmp;
    int a = 2, b = 3;
    result = 1;
    tmp = 1;
    element = -(double)((a * b * x) / 2);
    while (1)
    {
        result += element;
        if (fabs(element - tmp) < eps)
            break;
        tmp = element;
        a++;
        b++;
        element *= -(double)((b * x) / (a - 1));
    }
    
    return result;
}