/* Last Changed : 20-08-2016
 * AUTHOR : LIBIN N GEORGE
 * program for computing the n-th fibonacci number using Recursion*/
#include <stdio.h>

long int fib(int n);

int main(void)
{
    int n;
    printf("Enter which term of fibinocci series you want to print:\n");
    scanf("%d",&n);
    if(n>0)
    {
        printf("The %d th number of fibinocci series is %ld\n",n,fib(n));
    }
    else
    {
        printf("ERROR:Invalid Number\n");
    }
    return 0;
}
//function for finding n th fibonacci number by Recursion
long int fib(int n)
{
    if(n==1)
    {
        return 0;
    }
    else if(n==2)
    {
        return 1;
    }
    else
    {
        return fib(n-1)+fib(n-2);
    }
}
