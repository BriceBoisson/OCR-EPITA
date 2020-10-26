#include <err.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double sigmoid(double n)
{
    return 1/(1+exp(-n));
}

double primeSigmoid(double n)
{
    return (1/(1+ exp(-n))*(1-(1/(1 + exp(-n)))));
}

double errorFunc(double a, double b)
{
    return 0.5 * (a-b) * (a-b);
}

double errorFuncD(double a, double b)
{
    return a-b;
}

int expectedResult(int a, int b)
{
    int y;
    if (a==b)
    {
        y = 0;
    }
    else
    {
        y = 1;
    }
    return y;
}
