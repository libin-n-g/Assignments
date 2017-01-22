/* DATE : 08-08-2016
 * AUTHOR : LIBIN N GEORGE
 * recursive program to implement quicksort*/

#include <stdio.h>
#include<stdlib.h>

void QuickSort(int *Num,int nStart, int nEnd);
void Swap(int *Num,int i,int j);
int Partition(int *Num,int nStart,int nEnd);                 //function to make partition about the Pivot by arranging elemets

int main(void)
{
    int *Num;
    int i,nStart=0,nEnd,n;

    printf("Enter number of integers you want to sort:");
    scanf("%d",&n);
    nEnd=n;
    if(n>0)
        Num=(int *)malloc(n*sizeof (int));
    if(Num==0 || n<1)
    {
        printf("ERROR");
        return 1;
    }
    printf("Enter %d numbers:\n",n);

    for(i=0;i<n;i++)
    {
        scanf("%d",&Num[i]);
    }

    QuickSort(Num, nStart,nEnd);
    printf("the sorted numbers are:\n");

    for(i=0;i<n;i++)
    {
        printf("%d\n",Num[i]);
    }
    free(Num);
    return 0;
}

//Recursive function to sort from nStart to nEnd
void QuickSort(int *Num,int nStart, int nEnd)
{
    int nPivot;

    if(nStart<nEnd)
    {
        nPivot=Partition(Num,nStart,nEnd);
        QuickSort(Num,nStart,nPivot);
        QuickSort(Num,nPivot+1,nEnd);
    }
}

//fuction to swap elements at 'i'th and 'j'th position
void Swap(int *Num, int i, int j)
{
    int temp;

    temp=Num[i];
    Num[i]=Num[j];
    Num[j]=temp;
}

//function to make partition about the Pivot by arranging elemets less
//than pivot in the left and greater than pivot in the right
int Partition(int *Num,int nStart,int nEnd)
{
    int i,j,nRank=nStart;

    for(i=nStart;i<nEnd;i++)
    {                                   //loop to find Rank of Pivot(first element)
        if(Num[i]<Num[nStart])
        {
            nRank++;
        }
    }

    Swap(Num,nStart,nRank);
    j=(nRank+1);
    i=nStart;

    for(;i<nRank;i++)
    {
        if(Num[i]>=Num[nRank])
        {
            for(;j<nEnd;j++)
            {
                if(Num[j]<Num[nRank])
                {
                    Swap(Num,j,i);
                    break;
                }
            }
        }
    }
    return nRank;
}
