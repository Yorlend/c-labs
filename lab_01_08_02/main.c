#include <stdio.h>
#include <stdint.h>

unsigned int cycle_shift(unsigned int x, int n);
void dec_to_bin(unsigned int x);

int main(void)
{
    uint32_t a, res;
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
    for (int i = 31; i >= 0; i--)
        printf("%d", (x >> i) % 2);
}

unsigned int cycle_shift(unsigned int x, int n)
{
    return (x << n) | (x >> (32 - n));
}
