/* AUTHOR : LIBIN N GEORGE
 * LAST CHANGED:1-2-2017
 * Program which Implement a min-heap with standard operations
 * (buildHeap, findMin, extractMin, decreaseKey, insert).
 * and heapsort.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define INF INT_MAX
#define MAXHEAPLENGTH 100
#define FAIL -1000
#define Parent(X) (X/2)
#define LeftChild(X) (2*X)
#define RightChild(X) (2*X+1)

struct Heap
{
    int Array[MAXHEAPLENGTH];
    int Heapsize;
};
typedef struct Heap* MinHeappointer;

void Swap(int *a,int* b);

void MinHeapify(MinHeappointer A,int index);
void BuildHeap(MinHeappointer A);
int FindMin(MinHeappointer A);
void DecreaseKey(MinHeappointer A, int i, int NewKey);
void DisplayHeap(MinHeappointer A);
int extractmin(MinHeappointer A);
void MinHeapInsert(MinHeappointer A,int key);

int HeapSort(MinHeappointer A,int sorted[MAXHEAPLENGTH]);

void Build(MinHeappointer A);//function which calls Buildheap after taking the array
void DecreaseKeyOfHeap(MinHeappointer A);//function which calls Decreasekey after taking inputs
int main(void)
{
    int i,Input,key,minimum,n;
    int sorted[MAXHEAPLENGTH];
    MinHeappointer A;
    A=(MinHeappointer)malloc(sizeof(struct Heap));
    A->Heapsize=0;
    do {
        printf("\n1=>Buildheap \n2=>findMin\n3=>extractMin \n4=>decreaseKey \n5=>insert \n6=>Display elements \n7=>exit(also prints sorted list using heapsort)\nEnter the Option\n");
        scanf("%d",&Input);
        switch (Input) {
        case 1:
            Build(A);
            break;
        case 2:
            minimum=FindMin(A);
            if(minimum!=FAIL)//Error checking
            {
                printf("The Minimum element is %d\n",minimum);
            }
            break;
        case 3:
            minimum=extractmin(A);
            if(minimum!=FAIL)//Error checking
            {
                printf("The Minimum element is %d\n",minimum);
            }
            break;
        case 4:
            DecreaseKeyOfHeap(A);
            break;
        case 5:
            printf("\nEnter the Element You Want to Insert\n");
            scanf("%d",&key);
            MinHeapInsert(A,key);
            break;
        case 6:
            DisplayHeap(A);
            break;
        case 7:
            if(A->Heapsize>0)
            {
                n=HeapSort(A,sorted);
                printf("\nThe Sorted Array is\n");
                for(i=0;i<n;i++)
                {
                    printf("%d\n",sorted[i]);
                }
            }
            else {
                printf("Nothing To Sort\n");
            }
            break;
        default:
            printf("\nEnter Valid Option\n");
            break;
        }
    }while(Input != 7);
    return 0;
}

//find and delete the min Element
int extractmin(MinHeappointer A)
{
    int minimum;
    minimum = FindMin(A);
    if(minimum!=FAIL)
    {
        if(A->Heapsize<1)
        {
            printf("\nERROR:Heap Underflow\n");
            return 0;
        }
        else
        {
            Swap(&(A->Array[0]),&(A->Array[A->Heapsize-1]));
            (A->Array[A->Heapsize-1])=0;
            A->Heapsize--;
            MinHeapify(A,1);
        }
        return minimum;
    }
    return FAIL;
}
//insert a new element to the heap
void MinHeapInsert(MinHeappointer A,int key)
{
    A->Heapsize++;
    A->Array[A->Heapsize-1]=INF;
    DecreaseKey(A,A->Heapsize,key);
}
//function which calls Buildheap after taking the array
void Build(MinHeappointer A)
{
    int i;
    char c = 'Y';
    if(A->Heapsize>0)
    {
        printf("\nDo you want to delete the existing heap and Make a New Heap(Y or N)\n");
        scanf("\n%c",&c);
    }
    if(c == 'N' || c == 'n')
    {
        return;
    }
    if(c == 'Y' || c == 'y')
    {
        printf("\nEnter the Number of Elements in the Heap you want to Build\n");
        scanf("%d",&(A->Heapsize));
        if(A->Heapsize>0 && A->Heapsize <= MAXHEAPLENGTH)
        {
            printf("Enter the elements of the heap\n");
            for(i=0;i<A->Heapsize;i++)
            {
                scanf("%d",&(A->Array[i]));
            }
            BuildHeap(A);
        }
        else
        {
            printf("\nEnter Number of Elements between %d and %d\n",0,MAXHEAPLENGTH);
            A->Heapsize=0;
        }
    }

}
//function which calls Decreasekey after taking inputs
void DecreaseKeyOfHeap(MinHeappointer A)
{
    int index,newkey;
    if(A->Heapsize<1)
    {
        printf("\nERROR:Heap Underflow\n");
        return;
    }
    printf("Enter The Index of the Array(Heap) whose key you want to decrease(Array starts from index=1)\n");
    scanf("%d",&index);
    if(index>A->Heapsize || index<0)
    {
        printf("\nERROR:index not in Range\n");
        return;
    }
    printf("Enter The NewKey(should be less than the old key(%d))",A->Array[index-1]);
    scanf("%d",&newkey);
    DecreaseKey(A,index,newkey);
}
//finds min element
int FindMin(MinHeappointer A)
{
    if(A->Heapsize<1)
    {
        printf("\nERROR:Heap Underflow\n");
        return FAIL;
    }
    else
    {
        return A->Array[0];
    }
}

void MinHeapify(MinHeappointer A, int index)
{
    int l,r,s;
    l=LeftChild(index);
    r=RightChild(index);
    if(index > (A->Heapsize)/2)
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
        if(A->Array[index-1]>A->Array[s-1])
        {
            Swap(&A->Array[index-1],&A->Array[s-1]);
            MinHeapify(A,s);
        }
    }
}
// Build a heap given An Array A->Array
void BuildHeap(MinHeappointer A)
{
    int i;
    for(i=(A->Heapsize/2);i>=0;i--)
    {
        MinHeapify(A,i);
    }
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
        while ( i > 1 && A->Array[Parent(i)-1] > A->Array[i-1]) {
            Swap(&(A->Array[i-1]),&(A->Array[Parent(i)-1]));
            i=Parent(i);
        }
    }

}
// displays elements in the order of array
void DisplayHeap(MinHeappointer A)
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
//sorts the array
int HeapSort(MinHeappointer A,int sorted[MAXHEAPLENGTH])
{
    int i=0;
    while (A->Heapsize) {
        sorted[i]=extractmin(A);
        i++;
    }
    return i;
}

void Swap(int *a, int *b)
{
    int temp;
    temp=(*a);
    (*a)=(*b);
    (*b)=temp;
}
