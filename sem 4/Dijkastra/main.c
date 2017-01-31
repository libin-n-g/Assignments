
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#define INF INT_MAX
#define MAXHEAPLENGTH 100
#define FAIL -1

struct Vertex
{
    int VertexNumber;
    struct list* Neigh;
    int HeapPosition;
};
typedef struct Vertex* Vertexptr;

struct list
{
    struct Vertex* Neighbours;
    struct list* Next;
    int edgewt;
};

typedef struct list* listptr;

struct HeapElement
{
    struct Vertex* VertexIndex;
    int dist;
    struct Vertex* Prev;
};

struct Heap
{
    struct HeapElement Array[MAXHEAPLENGTH];
    int Heapsize;
};

typedef struct Heap* HeapPtr;


Vertexptr CreateVertexes(int Num);//creates Vertex from 1 to Num
void CreatelistVertex(Vertexptr V, Vertexptr VertexNeibour, int weight);//adds elements to the list
Vertexptr Makelists(Vertexptr V, int Num);//Make adjacency list for each entry
HeapPtr DijkstraAlgorithm(Vertexptr V, int Num, int Source);
void Print

void DecreaseKey(HeapPtr A,int i,int NewKey);
struct HeapElement extractmin(HeapPtr A);
struct HeapElement FindMin(HeapPtr A);
void DeleteMin(HeapPtr A);
void MinHeapify(HeapPtr A, int index);
void Swap(struct HeapElement *a,struct HeapElement *b);
int LeftChild(int i);
int RightChild(int i);
int Parent(int i);

int main(void)
{
    int Num,i=0,j=1,source;
    Vertexptr V=NULL;
    HeapPtr H=NULL;
    printf("\nEnter No of Vertex in the graph\n");
    scanf("%d",&Num);
    V=CreateVertexes(Num);
    if(V!=NULL)
    {
        V = Makelists(V,Num);
        printf("Enter the Source Vertex\n");
        scanf("%d",&source);
        H=DijkstraAlgorithm(V,Num,source);

    }
    else
    {
        printf("\nmemory not allocated\n");
        return 1;
    }
    return 0;
}
//adds elements to the list
void CreatelistVertex(Vertexptr V,Vertexptr VertexNeibour,int weight)
{
    listptr New=NULL;
    New = (listptr)malloc(sizeof (struct list));
    if (New != NULL)
    {
        if(V->Neigh==NULL)
        {
            New->Next=NULL;
        }
        else
        {
            New->Next=V->Neigh;
        }
        V->Neigh=New;
        New->Neighbours=VertexNeibour;
        New->edgewt=weight;
    }
    else
    {
        printf("\nMemory Allocation failed\n");
        exit(1);
    }
}
//creates Vertex from 1 to Num
Vertexptr CreateVertexes(int Num)
{
    Vertexptr V=NULL;
    int j;
    V = (Vertexptr) malloc(Num * sizeof(struct Vertex));
    if(V !=NULL)
    {
        for(j=0;j<Num;j++)
        {
            (V+j)->VertexNumber=j+1;
            (V+j)->Neigh=NULL;
        }
        return V;
    }
    else
    {
        printf("\nmemory not allocated\n");
        return V;
    }
}
//Make adjacency list for each entry
Vertexptr Makelists(Vertexptr V,int Num)
{
    int i,j,Neigh,temp,weight;

    Vertexptr nVertex;
    for(i=0;i<Num;i++)
    {
        printf("Enter Number of Neighbours of Vertex %d which are bigger than current vertex:\n",i+1);
        scanf("%d",&Neigh);
        if(Neigh<(Num-i))
        {
            if(Neigh!=0)
                printf("Enter Neighbours of Vertex %d which are bigger than current vertex along with edge weight:\n",i+1);

            nVertex=V+i;
            for(j=0;j<Neigh;j++)
            {
                scanf("%d",&temp);
                scanf("%d",&weight);
                if(temp<=Num && temp!= i+1 && temp > 0 && weight > 0)
                {
                    CreatelistVertex(nVertex,V+temp-1,weight);
                    CreatelistVertex(V+temp-1,nVertex,weight);
                }
                else
                {
                    if(weight==0)
                        printf("\n Edge Weight cannot be ZERO\n");
                    if(temp == i+1)
                        printf("\nVertex cannot be connected to itself.TRY AGAIN\n");
                    else
                        printf("\nThe Vertex you entered does not exist\nTry again\n");
                    j--;
                }
            }
        }
        else
        {
            printf("\nNumber Neighbours exceeds number of Vertex (less than current Vertex)\n");
            i--;
        }
    }
    return V;
}

//Decrease the key of an element having index i
void DecreaseKey(HeapPtr A,int i,int NewKey)
{
    if(A->Array[i-1].dist < NewKey)
    {
        printf("\nERROR:NewKey is Greater than Current key\n");
    }
    else {
        A->Array[i-1].dist = NewKey;
        while ( i > 1 && A->Array[Parent(i)-1].dist > A->Array[i-1].dist) {
            Swap(&(A->Array[i-1]),&(A->Array[Parent(i)-1]));
            i=Parent(i);
        }
    }

}

HeapPtr DijkstraAlgorithm(Vertexptr V,int Num,int Source)
{
    HeapPtr H;
    int i,alt;
    struct list* adjlist;
    struct HeapElement u;
    struct HeapElement *v;
    H = (HeapPtr)malloc(sizeof (struct Heap));
    if(H == NULL)
    {
        printf("\nERROR:Memory Allocation failed\n");
        return NULL;
    }
    else {
        H->Heapsize=0;
        for(i=0;i<Num;i++)
        {
            H->Array[i].VertexIndex = V+i;
            (V+i)->HeapPosition=i;
            H->Array[i].dist=INF;
            H->Array[i].Prev=NULL;
            H->Heapsize++;
        }
        H->Array[Source-1].dist=0;//source
        Swap(&(H->Array[Source-1]),&(H->Array[0]));

        while (H->Heapsize > 0) {
            u = extractmin(H);
            adjlist = u.VertexIndex->Neigh;

            while ( adjlist!= NULL) {
                v=&(H->Array[adjlist->Neighbours->HeapPosition]);
                alt = u.dist + adjlist->edgewt;
                if(alt < v->dist)
                {
                    v->Prev=u.VertexIndex;
                    DecreaseKey(H,v->VertexIndex->HeapPosition+1,alt);
                }
                adjlist = adjlist->Next;
            }
        }
    }
    return H;
}

//find and delete the min Element
struct HeapElement extractmin(HeapPtr A)
{
    struct HeapElement minimum;
    minimum = FindMin(A);
    DeleteMin(A);
    return minimum;
}

struct HeapElement FindMin(HeapPtr A)
{
    if(A->Heapsize<1)
    {
        printf("\nERROR:Heap Underflow\n");
        exit(1);
    }
    else
    {
        return (A->Array[0]);
    }
}

//Delete the min element
void DeleteMin(HeapPtr A)
{
    if(A->Heapsize<1)
    {
        printf("\nERROR:Heap Underflow\n");
        return;
    }
    else
    {
        Swap(&(A->Array[0]),&(A->Array[A->Heapsize-1]));
        A->Heapsize--;
        MinHeapify(A,1);
    }
}

void MinHeapify(HeapPtr A, int index)
{
    int l,r,s;
    l=LeftChild(index);
    r=RightChild(index);
    if(index >= (A->Heapsize+1)/2)
    {
        return;
    }
    else
    {
        if(r <= A->Heapsize && A->Array[r-1].dist < A->Array[l-1].dist)
        {
            s=r;
        }
        else
        {
            s=l;
        }
        if(A->Array[index-1].dist>A->Array[s-1].dist)
        {
            Swap(&A->Array[index-1],&A->Array[s-1]);
            MinHeapify(A,s);
        }
    }
}
void Swap(struct HeapElement *a,struct HeapElement *b)
{
    struct HeapElement temp;
    int postemp;
    postemp=(*a).VertexIndex->HeapPosition;
    (*a).VertexIndex->HeapPosition=(*b).VertexIndex->HeapPosition;
    (*b).VertexIndex->HeapPosition=postemp;
    temp=(*a);
    (*a)=(*b);
    (*b)=temp;    
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
