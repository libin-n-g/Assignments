/* AUTHOR : LIBIN N GEORGE
 * LAST CHANGED:23-1-2017
 * Implement the divide and conquer algorithm for finding median of a list of n numbers in linear time.
 * Implement the partition function in-place (i.e., do not use separate L, C and R arrays).
 * You may use an additional array for storing the medians of each group of 5.
 * Input format :Assume that first line of the input will be an integer holding the value of n and
 *  next 'n' lines will contain one integer each.
*/

#include <stdio.h>
#include<stdlib.h>

struct LCR
{
    int Lend;
    int Cend;
};

int ithSmallest(int* Array, int Lower, int Upper, int i);
int ithInGroupof5(int* Array, int lower, int Upper, int index);
struct LCR Partition(int* Array,int lower,int Upper,int pivot);
void swap(int* a,int* b);
int Min(int a,int b);

int main(void)
{
    int *Numbers;
    int n,i;
    printf("Enter Number of Integers (n) for which you want to find the Median Followed by n Integers\n");
    scanf("%d",&n);
    Numbers = (int*)malloc(n*(sizeof(int)));
    if(Numbers==NULL)
    {
        printf("\nERROR:MEMORY ALLOCATION FAILED\n");
    }
    else
    {
        for(i=0;i<n;i++)
        {
            scanf("%d",Numbers+i);
        }
        printf("\nMedian is %d \n",ithSmallest(Numbers,0,n,n/2));
    }
    return 0;
}
//function for finding ith smallest number
int ithSmallest(int* Array,int Lower,int Upper,int i)
{
    int j,k=0,MedianOfMedian,center;
    int *Medians;
    struct LCR Index;
    if((Upper-Lower)<=5)
    {
        return ithInGroupof5(Array,Lower,Upper,i);
    }
    Medians = (int*)malloc((((Upper-Lower)/5)+1)*(sizeof(int)));//for storing medians
    if(Medians==NULL)
    {
        printf("\nERROR:MEMORY ALLOCATION FAILED\n");
        return -1;
    }
    for(j=Lower;j<Upper;j=j+5)
    {
        center=(Upper-j)/2;
        (*(Medians+k)) = ithInGroupof5(Array,j,Min(j+5,Upper),center);
        k++;
    }
    MedianOfMedian = ithSmallest(Medians,0,k,k/2);
    Index = Partition(Array,Lower,Upper,MedianOfMedian);
    if(i < Index.Lend)
    {
        return ithSmallest(Array,0,Index.Lend,i);
    }
    else if(i < Index.Cend)
    {
        return MedianOfMedian;
    }
    else
    {
        return ithSmallest(Array,Index.Cend,Upper,i-Index.Cend);
    }
}
//function for finding ith element after sorting 5 elements
int ithInGroupof5(int* Array,int lower,int Upper,int index)
{
    int i,j;

    for(i=lower+1;i<Upper;i++)
    {
        j=i;
        while (j>lower && (*(Array+j))<(*(Array+j-1))) {
           swap(Array+j,Array+j-1);
           j--;
        }
    }
    return (*(Array+index+lower));
}
//function to partition the Array
struct LCR Partition(int* Array,int lower,int Upper,int pivot)
{
    struct LCR Index;
    int i,j;
    j=lower;
    for(i=lower;i<(Upper-1);i++)//partitioning into 2parts(less than and Greaterthan or equalto)
    {
        if((*(Array+i)) < pivot)
        {
            swap(Array+i,Array+j);
            j++;
        }
    }
    Index.Lend=j;
    j=lower+j;
    for(i=j;i<Upper;i++)//patitioning 2nd partition
    {
        if((*(Array+i)) == pivot)
        {
            swap(Array+i,Array+j);
            j++;
        }
    }
    Index.Cend=j;
    return Index;
}

void swap(int* a,int* b)
{
    int temp;
    temp=(*a);
    (*a)=(*b);
    (*b)=(temp);
}
int Min(int a,int b)
{
    return a < b ? a : b ;
}
