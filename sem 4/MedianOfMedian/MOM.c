/* AUTHOR : LIBIN N GEORGE
 * LAST CHANGED:
 * Implement the divide and conquer algorithm for finding median of a list of n numbers in linear time.
 * Implement the partition function in-place (i.e., do not use separate L, C and R arrays).
 * You may use an additional array for storing the medians of each group of 5.
 * Input format :Assume that first line of the input will be an integer holding the value of n and
 *  next 'n' lines will contain one integer each.
*/

#include <stdio.h>
#include<stdlib.h>

int ithSmallest(int* Array, int Lower, int Upper, int i);
int MedianAfterSort(int* Array,int lower,int Upper);
void swap(int* a,int* b);
int Partition();

int Min(int a,int b);

int main(void)
{
    int *Numbers;
    int n,i;
    printf("Enter Number of Integers (n) for which you want to find the Median Followed by n Integers\n");
    scanf("%d",&n);
    Numbers = (int*)malloc(n*(sizeof(int)));
    for(i=0;i<n;i++)
    {
        scanf("%d",Numbers+i);
    }
    printf("\n-------%d---------\n",ithSmallest(Numbers,0,n-1,n/2));
    return 0;
}
int ithSmallest(int* Array,int Lower,int Upper,int i)
{
    int j,k=0,MedianOfMedian;
    int *Medians;
//    if((Upper-Lower)<=5)
//    {
//        return MedianAfterSort(Array,Lower,Upper);
//    }
    Medians = (int*)malloc((((Upper-Lower)/5)+1)*(sizeof(int)));
    for(j=Lower;j<Upper;j=j+5)
    {
        (*(Medians+k)) = MedianAfterSort(Array,j,Min(j+5,Upper));
        k++;
    }
    MedianOfMedian = ithSmallest(Medians,0,k,k/2);

}
int MedianAfterSort(int* Array,int lower,int Upper)
{
    int A[5];
    int i,j,lowest=lower;

    for(j=0;j<(Upper-lower);j++)
    {
            A[j]=(*(Array+j+lower));
    }
    for(i=1;i<(Upper-lower);i++)
    {
        j=i;
        while (j>0 && A[j]<A[j-1]) {
           swap(&A[j],&A[j-1]);
           j--;
        }
    }
printf("%d",A[((Upper-lower)/2)]);
    return A[((Upper-lower)/2)];
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
