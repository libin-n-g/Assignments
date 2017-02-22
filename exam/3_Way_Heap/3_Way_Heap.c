/* AUTHOR : LIBIN N GEORGE
 * Date:20-2-1017
 * Given a positive number n and a list of n non-negative integers,
 * build a 3-way-min-heap H of these list elements and print the elements of
 * the heap in the order of their heap positions.  After this, ask the user
 * repeatedly for elements that are to be inserted to the heap and print the elements
 * of the heap after inserting each of these new elements. Stop when the user enters a -1.
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define INF INT_MAX
#define MAXHEAPLENGTH 100
#define Parent(X) (((X)+1)/3)
#define LeftChild(X) (3*(X)-1)
#define MiddleChild(X) (3*(X))
#define RightChild(X) (3*(X)+1)

struct Heap
{
    int Array[MAXHEAPLENGTH];
    int Heapsize;
};
typedef struct Heap* MinHeappointer;

void MinHeapInsert(MinHeappointer A,int key);
void BuildHeap(MinHeappointer A);
void MinHeapify(MinHeappointer A, int index);
void DecreaseKey(MinHeappointer A,int i,int NewKey);
void DisplayHeap(MinHeappointer A);

void Swap(int *a, int *b);
int main(void)
{
    int n,Num,i;
    MinHeappointer A;
    printf("Enter a positive number n and a list of n non-negative integers\n");
    scanf("%d",&n);
    A=(MinHeappointer)malloc(sizeof(struct Heap));
    if(A!=NULL)
    {
        A->Heapsize=0;
        for(i=0;i<n;i++)
        {
            scanf("%d",&Num);
            if(Num >= 0)
            {
                A->Array[i]=Num;
                A->Heapsize++;
            }
            else
            {
                printf("\nPlease enter NonNegative Integers\n");
                i--;
            }
        }
        BuildHeap(A);
        DisplayHeap(A);
        Num=0;
        while (Num != -1)
        {
            printf("Enter the new Element to Inset to Heap (-1 to end the process)");
            scanf("%d",&Num);
            if(Num != -1)
            {
                MinHeapInsert(A,Num);
                DisplayHeap(A);
            }
        }
    }
    else
    {
        printf("\nMemory Allocation Failed\n");
    }
    return 0;
}
//Insert New element
void MinHeapInsert(MinHeappointer A,int key)
{
    A->Heapsize++;
    A->Array[A->Heapsize-1]=INF;
    DecreaseKey(A,A->Heapsize,key);
}
//Decrease the key of an element having index i
void DecreaseKey(MinHeappointer A,int i,int NewKey)
{
    if(A->Array[i-1] < NewKey)
    {
        printf("\nERROR:NewKey is Greater than Current key\n");
    }
    else {
        A->Array[i-1] = NewKey;
        while ( i > 1 && A->Array[Parent(i)-1] > A->Array[i-1])
        {
            Swap(&(A->Array[i-1]),&(A->Array[Parent(i)-1]));
            i=Parent(i);
        }
    }
}
// Build a heap given An Array A->Array
void BuildHeap(MinHeappointer A)
{
    int i;
    for(i=(((A->Heapsize)+1)/3);i>=0;i--)
    {
        MinHeapify(A,i);
    }
}
void MinHeapify(MinHeappointer A, int index)
{
    int l,r,m,s;
    l = LeftChild(index);
    r = RightChild(index);
    m = MiddleChild(index);
    if(index > (((A->Heapsize)+1)/3))
    {
        return;
    }
    else
    {
        if(r <= A->Heapsize && A->Array[r-1] < A->Array[l-1])
        {
            s=r;
        }
        else
        {
            s=l;
        }
        if(m <= A->Heapsize && A->Array[m-1] < A->Array[s-1])
        {
            s=m;
        }
        if(A->Array[index-1]>A->Array[s-1])
        {
            Swap(&A->Array[index-1],&A->Array[s-1]);
            MinHeapify(A,s);
        }
    }
}
void DisplayHeap(MinHeappointer A)//display heap
{
    int i;
    if(A->Heapsize>0)
    {
        for(i=0;i<A->Heapsize;i++)
        {
            printf("Element%d : %d\n",i+1,A->Array[i]);
        }
    }
    else
    {
        printf("Heap is Empty\n");
    }
}
void Swap(int *a, int *b)
{
    int temp;
    temp=(*a);
    (*a)=(*b);
    (*b)=temp;
}
