#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#define INF INT_MAX
#define MAX 100
#define Parent(X) ((X)/2)
#define LeftChild(X) (2*(X))
#define RightChild(X) (2*(X)+1)

struct Vertex
{
    int VertexNumber;
    struct Vertex* Parent;
    int Rank;
};
typedef struct Vertex* Vertexptr;
struct Edge
{
    struct Vertex* VertexU;
    struct Vertex* VertexV;
    int EdgeWeight;
};
typedef struct Edge* Edgeptr;
struct Graph
{
    int nNumOfVertex;
    struct Vertex V[MAX];
    struct Edge E[MAX*MAX];
};

struct Heap
{
    struct Edge* EdgeArray[MAX*MAX];
    int Heapsize;
};
typedef struct Heap* MinHeapptr;

void KruskalsAlgorithm(MinHeapptr H,struct Graph G);

void BuildHeap(MinHeapptr A);
void MinHeapify(MinHeapptr A, int index);
Edgeptr FindMin(MinHeapptr A);
Edgeptr extractmin(MinHeapptr A);
void Swap(Edgeptr *a, Edgeptr *b);

struct Graph MakeSet(struct Graph G);
void Union(Vertexptr U,Vertexptr V);
Vertexptr Find(Vertexptr U);

struct Graph InitaliseVertices(struct Graph G);
struct Graph InitaliseEdges(struct Graph G);

int main(void)
{
    struct Graph G;


        printf("\nEnter Number of Vertices in the Graph\n");
        scanf("%d",&G.nNumOfVertex);
        G = InitaliseVertices(G);
        G = InitaliseEdges(G);
        G = MakeSet(G);

    return 0;
}
void KruskalsAlgorithm(MinHeapptr H,struct Graph G)
{

}

struct Graph InitaliseVertices(struct Graph G)
{
    int i;
    for(i=0;i<G.nNumOfVertex;i++)
    {
        G.V[i].VertexNumber=i+1;
    }
    return G;
}
struct Graph InitaliseEdges(struct Graph G)
{
    int i,nNumAdjVertices,j,temp,k=0;
    int weight;
    MinHeapptr H=NULL;
    H = (MinHeapptr)malloc(sizeof(struct Heap));
    if(H != NULL)
    {
        for(i=0;i<G.nNumOfVertex;i++)
        {
            printf("Enter Number of Neighbours of Vertex %d which are bigger than current vertex:\n",i+1);
            scanf("%d",&nNumAdjVertices);
            if(nNumAdjVertices >= 0)
            {
                for(j=0;j<nNumAdjVertices;j++)
                {
                    scanf("%d",&temp);
                    scanf("%d",&weight);
                    if(temp <= G.nNumOfVertex && temp != i+1 && temp > 0)
                    {
                        G.E[k].VertexU = &(G.V[i]);
                        G.E[k].VertexV = &(G.V[temp-1]);
                        G.E[k].EdgeWeight = weight;
                        H->EdgeArray[k] = &(G.E[k]);
                        k++;
                    }
                    else
                    {
                        if(temp == i+1)
                            printf("\nVertex cannot be connected to itself.TRY AGAIN\n");
                        else
                            printf("\nThe Vertex you entered does not exist\nTry again\n");
                        j--;
                    }
                }
                H->Heapsize=k;
            }
            else
            {
                printf("\nERROR: Memory allocation Falied\n");
            }
        }
        else
        {
            printf("\nError:Number of Adjacent Vertices cannot be negative");
            i--;
        }
    }
    BuildHeap(H);
    return G;
}
struct Graph MakeSet(struct Graph G)
{
    int i;
    for(i=0;i<G.nNumOfVertex;i++)
    {
        G.V[i].Parent = &(G.V[i]);
        G.V[i].Rank = 0;
    }
    return G;
}
void Union(Vertexptr U,Vertexptr V)
{
    Vertexptr RepU,RepV;
    RepU = Find(U);
    RepV = Find(V);
    if(RepU == RepV)
        return;
    if(RepU->Rank >= RepV->Rank)
    {
        RepV->Parent = RepU;
        if(RepU->Rank == RepV->Rank)
            RepU->Rank++;
    }
    else
    {
        RepU->Parent=RepV;
    }
}
Vertexptr Find(Vertexptr U)
{
    if(U->Parent != U)
        U->Parent=Find(U);
    return U->Parent;
}

// Build a heap given An Array A->Array
void BuildHeap(MinHeapptr A)
{
    int i;
    for(i=(A->Heapsize/2);i>=0;i--)
    {
        MinHeapify(A,i);
    }
}

// make Min Heap from two Heaps (as child)
void MinHeapify(MinHeapptr A, int index)
{
    int l,r,s;
    l = LeftChild(index);
    r = RightChild(index);
    if(index > (A->Heapsize)/2)
    {
        return;
    }
    else
    {
        if(r <= A->Heapsize && A->EdgeArray[r-1]->EdgeWeight < A->EdgeArray[l-1]->EdgeWeight)
        {
            s=r;
        }
        else
        {
            s=l;
        }
        if(A->EdgeArray[index-1]->EdgeWeight > A->EdgeArray[s-1]->EdgeWeight)
        {
            Swap(&A->EdgeArray[index-1],&A->EdgeArray[s-1]);
            MinHeapify(A,s);
        }
    }
}

//find and delete the min Element
Edgeptr extractmin(MinHeapptr A)
{
    Edgeptr minimum;
    minimum = FindMin(A);
    if(A->Heapsize<1)
    {
        printf("\nERROR:Heap Underflow\n");
        exit(1);
    }
    else
    {
        Swap(&(A->EdgeArray[0]),&(A->EdgeArray[A->Heapsize-1]));
        A->Heapsize--;
        MinHeapify(A,1);
    }
    return minimum;
}
//finds element having maximum priority(min Key)
Edgeptr FindMin(MinHeapptr A)
{
    if(A->Heapsize<1)
    {
        printf("\nERROR:Heap Underflow\n");
        exit(1);
    }
    else
    {
        return (A->EdgeArray[0]);
    }
}
void Swap(Edgeptr *a, Edgeptr *b)
{
    Edgeptr temp;
    temp=(*a);
    (*a)=(*b);
    (*b)=temp;
}
