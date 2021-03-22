#include <stdio.h>

int main()
{
    int inp_sec, min, hour;

    printf("Input seconds to convert: ");
    scanf("%d", &inp_sec);

    hour = inp_sec / 3600;
    inp_sec %= 3600;
    min = inp_sec / 60;
    inp_sec %= 60;
    
    printf("Converted time is:\n%d hours %d minutes %d seconds\n",
    hour, min, inp_sec);

    return 0;
}