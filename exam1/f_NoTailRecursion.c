
/*AUTHOR:LIBIN N GEORGE
 * ROLL NO :111501015
 * Lab Interim Evaluation 1 - Q1
 * Tail Recursion Elimination by while loop
 */
#include<stdio.h>

int f(int, int);

int main()
{
    int a, b, result;
    printf("Give a, b \n");
    scanf("%d%d", &a, &b);
    result=f(a, b);
    printf("result is %d \n",result);
    return 0;
}

int f(int x, int y)
{
    while(y>1)//eliminating tail recursion
    {
        x=x*(y+1);
        y=y-2;
    }
    return x;
}
