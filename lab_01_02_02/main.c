#include <stdio.h>
#include <math.h>

int main()
{
    double x_a, x_b, x_c, y_a, y_b, y_c, ab, ac, bc, p;
    printf("Enter coordinates of the triangle:\n");
    scanf("%lf%lf%lf%lf%lf%lf", &x_a, &y_a, &x_b, &y_b, &x_c, &y_c);

    ab = sqrtf((x_a - x_b) * (x_a - x_b) + (y_a - y_b) * (y_a - y_b));
    bc = sqrtf((x_b - x_c) * (x_b - x_c) + (y_b - y_c) * (y_b - y_c));
    ac = sqrtf((x_a - x_c) * (x_a - x_c) + (y_a - y_c) * (y_a - y_c));

    p = ab + bc + ac;
    printf("Perimeter of a triangle is: %.6lf\n", p);

    return 0;
}
