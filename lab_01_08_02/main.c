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
        dec_to_bin(x / 2);
        printf("%d", x % 2);
    }
}

unsigned int cycle_shift(unsigned int x, int n)
{
    for (int i = 0; i < n; i++)
        x = (x << 1) | ((x >> 31) & 1);
    
    return x;
}