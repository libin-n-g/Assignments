#include <stdio.h>

void binSearch(int [],int ,int ,int );
int main(void)
{
    int array[15];
    int i, nEnd, nItem;
    printf("Enter Number of integers you need in sorted array:\n");
    scanf("%d",&nEnd);
    if(nEnd<1 || nEnd>15)
    {
        printf("Number of Elements in the array should be less than 15");
        return 1;
    }
    printf("Enter array in ascending order:\n");
    for(i=0;i<nEnd;i++)
    {
        scanf("%d",&array[i]);
    }
    printf("Enter the Element you what to search:\n");
    scanf("%d",&nItem);
    binSearch(array,0,nEnd,nItem);
}
void binSearch(int A[],int nStart ,int nEnd,int nItem)
{
    int nMid;
    nMid=nStart+((nEnd-nStart)/2);
    while(A[nMid]!=nItem && nEnd != nStart)
    {
        nMid=nStart+((nEnd-nStart)/2);

        if(A[nMid]>nItem)
        {
            nEnd=nMid;
        }
        else
        {
            nStart=nMid+1;
        }

    }
    if(A[nMid]==nItem)
    {
        printf("The item is at position %d\n",nMid+1);
    }
    else
    {
        printf("Element not found\n");
    }


}
