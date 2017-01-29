#include <stdio.h>
#include<stdlib.h>

struct Element
{
    int Index;
    int key;
    struct Element* Pointer;
};

struct Heap
{
    struct Element Array[100];
    int Length;
    int Heapsize;
};
typedef struct Heap* MinHeappointer;

void Swap(struct Element *a,struct Element* b);
int LeftChild(int i);
int RightChild(int i);
int Parent(int i);

void MinHeapify(MinHeappointer A,int index);
void BuildHeap(MinHeappointer );
struct Element FindMin(MinHeappointer A);
void DecreaseKey(MinHeappointer A,int index,int NewKey);
int main(void)
{
    int i,key=1;
    MinHeappointer A;
    A=(MinHeappointer)malloc(sizeof(struct Heap));
    A->Heapsize=0;
    while (1) {
    printf("1->Insert Elements to the Heap\n2->Output the Minimum(root) of the Heap Elements\n3->Delete the Root of the Heap\n0->Exit\nEnter the Option\n");
    scanf("%d",&key);
    if(key == 1)
    {
        //Insert(A,item)
    }
    else if (key==2) {
        FindMin(A);
    }
    else if (key == 3) {
        //DeleteMin
    }
    else if (key == 4) {
       // DecreaseKey(A,index,newkey);
    }
    else if (key == 0) {
        break;
    }
    else
    {
        printf("\nEnter Valid Option\n");
    }
    }
    return 0;
}

struct Element FindMin(MinHeappointer A)
{
    return A->Array[0];
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
        if(A->Array[r].key<A->Array[l].key)
        {
            s=r;
        }
        else
        {
            s=l;
        }
        if(A->Array[index].key>A->Array[s].key)
        {
            Swap(&A->Array[index],&A->Array[s]);
            MinHeapify(A,s);
        }
    }
}

void BuildHeap(MinHeappointer A)
{
    int i;
    for(i=(A->Heapsize/2);i>=0;i--)
    {
        MinHeapify(A,i);
    }
}

void DecreaseKey(MinHeappointer A,int index,int NewKey)
{
    A->Array[index].key = NewKey;
}

int LeftChild(int i)
{
    return 2*i;
}

int RightChild(int i)
{
    return 2*i+1;
}

int Parent(int i)
{
    return i/2;
}
void Swap(struct Element *a, struct Element *b)
{
    struct Element temp;
    temp=(*a);
    (*a)=(*b);
    (*b)=temp;
}
