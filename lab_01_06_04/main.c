#include <stdio.h>
#include <math.h>

#define EPS 1e-8

int check_dot(double x_q, double y_q, double x_r, double y_r,
double x_p, double y_p);
double distance(double x_1, double y_1, double x_2, double y_2);

int main(void)
{
    double x_q, y_q, x_r, y_r, x_p, y_p;
    int res, scnf;
    scnf = scanf("%lf%lf%lf%lf%lf%lf", &x_q, &y_q, &x_r, &y_r, &x_p, &y_p);   
    if ((scnf < 6) || distance(x_q, y_q, x_r, y_r) < EPS)
        return 1;

    res = check_dot(x_q, y_q, x_r, y_r, x_p, y_p);
    printf("%d", res);

    return 0;
}


int check_dot(double x_q, double y_q, double x_r, double y_r,
double x_p, double y_p)
{
    double qr, pq, pr;
    qr = distance(x_q, y_q, x_r, y_r);
    pq = distance(x_p, y_p, x_q, y_q);
    pr = distance(x_p, y_p, x_r, y_r);

    if ((pr + pq - qr) < EPS)
        return 1;

    return 0;
}


double distance(double x_1, double y_1, double x_2, double y_2)
{
    return sqrt((x_1 - x_2) * (x_1 - (x_2)) + (y_1 - y_2) * (y_1 - y_2));
}
