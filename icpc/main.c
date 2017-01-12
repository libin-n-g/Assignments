#include <stdio.h>

int check(long long int a[100000], long long int b, long n);

int main(void)
{
    long int T,n,i,j,l,m,k;
    long long int a[100000];
    long long int b;
    int flag=0;
    char word[1000000][3];
    scanf("%li",&T);
    for(i=0;i<T;i++)
    {
        scanf("%li",&n);
        for(j=0;j<n;j++)
        {
            scanf("%lli",&a[j]);
        }
        flag=0;
        for(l=0;l<n-1;l++)
        {
            for(m=l+1;m<n;m++)
            {
                b=a[l]*a[m];
                if(check(a,b,n)==1)
                {
                    flag=1;
                }
                if(flag==1)
                {
                    break;
                }
            }
            if(flag==1)
            {
                break;
            }
        }
        if(flag==0)
        {
            word[i][0]='y';
            word[i][1]='e';
            word[i][2]='s';
            word[i][3]='\0';
        }
        else
        {
            word[i][0]='n';
            word[i][1]='o';
            word[i][2]='\0';
        }
    }
    for(k=0;k<T;k++)
    {
        printf("%s\n",word[k]);
    }
    return 0;
}


int check(long long int a[100000],long long int b,long int n)
{
    int m;
    for(m=0;m<n;m++)
    {
        if(a[m]==b)
        {
            return 0;
        }
    }
    return 1;
}
