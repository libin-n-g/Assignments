/* DATE : 08-08-2016
 * AUTHOR : LIBIN N GEORGE
 
 * recursive program to implement extended Euclidean algorithm
 * to find the gcd of two positive integers*/

#include <stdio.h>

//function declaration
int gcd(int a ,int b,int *nAlpha,int *nBeta,int *nQ);

int main(void)
{
   int a, b, t;
   int nAlpha,nBeta,nGcdno,nQ;
   printf("Enter two numbers:");
   scanf("%d %d",&a, &b);
   if(a<=0 || b<=0)
   {
       printf("Error:Entered number is less than or Equal to Zero!\n");
       return 1;
   }
   if(a>b)
   {
       t=a;
       a=b;
       b=t;
   }
   nGcdno=gcd(a,b,&nAlpha,&nBeta,&nQ);
   printf("For a=%d ,b=%d \nAlpha= %d\nBeta=%d\nGCD=%d\n",a,b,nAlpha,nBeta,nGcdno);
   return 0;
}

//Recursive function for finding GCD
int gcd(int a ,int b,int *nAlpha,int *nBeta,int *nQ)
{
    int t,nGcdno;
    if(a%b == 0)
    {
        nGcdno=b;
        *nBeta=1;
        *nAlpha=0;
        return nGcdno;
    }
    nGcdno=gcd(b,a%b,nAlpha,nBeta,nQ);
    *nQ=a/b;
    t=*nAlpha;
    *nAlpha=*nBeta;
    *nBeta=t-((*nBeta)*(*nQ));
    return nGcdno;
}
