#include <stdio.h>

unsigned int cycle_shift(unsigned int x, int n);
void dec_to_bin(unsigned int x);

int main(void)
{
    unsigned int a, res;
    int n;

    if (scanf("%u%d", &a, &n) != 2)
    {
        printf("Error: 1\n");
        return 1;
    }

    if (n < 0)
    {
        printf("Error: 2\n");
        return 2;
    }

    res = cycle_shift(a, n);

    printf("Result: ");
    dec_to_bin(res);
    printf("\n");

    return 0;
}

void dec_to_bin(unsigned int x)
{
    if (x < 2)
        printf("%d", x);
    else
    {
        dec_to_bin(x >> 1);
        printf("%d", x % 2);
    }
}

unsigned int cycle_shift(unsigned int x, int n)
{
    return (x << n) | (x >> (32 - n));
}
