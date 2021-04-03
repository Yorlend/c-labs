#include <stdio.h>

int div_sum(int num);

int main(void)
{
    for (int i = 1000; i <= 2000; i++)
    {
        int b = div_sum(i);
        if (div_sum(b) == i)
            printf("%d %d\n", i, b);
    }

    return 0;
}

int div_sum(int num)
{
    int res = 0;

    for (int i = 1; i < num; i++)
        if (num % i == 0)
            res += i;
    
    return res;
}