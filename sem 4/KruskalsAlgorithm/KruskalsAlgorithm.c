/* AUTHOR : LIBIN N GEORGE
 * LAST CHANGED:23-2-2017
 * Program Implementing  Kruskal's Algorithm for computing Minimum Spanning Tree of the input graph using
 * Disjoint set data structure with path compression and union by rank.
 * Input format:
 * First line : n (number of vertices of the graph)
 * Second line : d1 (Number of neighbours of v1 whose vertex numbers are bigger than v1).
 * Next d1 lines : vertex number of a higher numbered neighbour of v1 and the edge-weight of the corresponding edge
 * (separated by a space). Assume the neighbors are given increasing order of vertex numbers.
 * and so on..
 * Output format:
 * Print the edges of an MST along with the edge weights. If the graph is not connected, print a message indicating that.
 */
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
    struct Vertex* VParent;
    int Rank;
};
typedef struct Vertex* Vertexptr;
struct Edge
{
    struct Vertex* VertexU;
    struct Vertex* VertexV;
    int EdgeWeight;
    int PresentinMST;
};
typedef struct Edge* Edgeptr;
struct Graph
{
    int nNumOfVertex;
    int nNumOfEdge;
    struct Vertex V[MAX];
    struct Edge E[MAX*MAX];
};
typedef struct Graph* Graphptr;

struct Heap
{
    struct Edge EdgeArray[MAX*MAX];
    int Heapsize;
};
typedef struct Heap* MinHeapptr;

int KruskalsAlgorithm(Graphptr G);//returns 1 if graph is conneted;returns 0 when Graph is not connected
void PrintResult(struct Graph G);

///FUNCTIONS FOR CREATING GRAPH G(V,E)
void InitaliseVertices(Graphptr G);
void InitaliseEdges(Graphptr G);

///FUNCTIONS USED IN HEAPSORT
void SortEdges(MinHeapptr H,Graphptr G);//function which uses heapsort to make Edgeset in incresing order of weight
void BuildHeap(MinHeapptr A);
void MinHeapify(MinHeapptr A, int index);
struct Edge FindMin(MinHeapptr A);
struct Edge ExtractMin(MinHeapptr A);
inline void Swap(Edgeptr a, Edgeptr b);

///FUNCTIONS USED IN DISJOINT SET DATA STRUCTURE HAVING VERTEX AS ELEMENTS
void MakeSet(Vertexptr G);
void Union(Vertexptr U,Vertexptr V);
Vertexptr FindRep(Vertexptr U);



int main(void)
{
    Graphptr G;
    int ConnectedGraph;
    G = (Graphptr)malloc(sizeof(struct Graph));
    if(G != NULL)
    {
        printf("\nEnter Number of Vertices in the Graph\n");
        scanf("%d",&G->nNumOfVertex);
        InitaliseVertices(G);
        InitaliseEdges(G);
        ConnectedGraph = KruskalsAlgorithm(G);
        if(ConnectedGraph)
            PrintResult(*G);
        else
            printf("\nGraph is Not Connected\n");
    }
    else {
        printf("\nERROR:Memory allocation Failed\n");
    }
    return 0;
}
int KruskalsAlgorithm(Graphptr G)
{
    int i,nEdgesinMST=0;
    for(i=0;i<G->nNumOfVertex;i++)
    {
        MakeSet(&(G->V[i]));
    }
    for(i=0;i<(G->nNumOfEdge);i++)
    {
        if((FindRep(G->E[i].VertexU)) != FindRep(G->E[i].VertexV))                  //edges sorted in increasing order
        {
            nEdgesinMST++;
            G->E[i].PresentinMST = 1;
            Union(G->E[i].VertexU,G->E[i].VertexV);
        }
    }
    if(nEdgesinMST == (G->nNumOfVertex-1))
        return 1;
    else {
        return 0;
    }
}
//prints output
void PrintResult(struct Graph G)
{
    int i;
    printf("\n-----------------------------------------------------------------------\n");
    printf("\t\t Edges\t\tEdgeWeight\n");
    for(i=0;i < G.nNumOfEdge;i++)
    {
        if(G.E[i].PresentinMST == 1)
            printf("\t\t(%d, %d)\t\t%d\n",G.E[i].VertexU->VertexNumber,G.E[i].VertexV->VertexNumber,G.E[i].EdgeWeight);
    }
    printf("\n-----------------------------------------------------------------------\n");
}

void InitaliseVertices(Graphptr G)
{
    int i;
    for(i=0;i<G->nNumOfVertex;i++)
    {
        G->V[i].VertexNumber=i+1;
    }
}
void InitaliseEdges(Graphptr G)
{
    int i,nNumAdjVertices,j,temp;
    int weight;
    MinHeapptr H=NULL;
    H = (MinHeapptr)malloc(sizeof(struct Heap));
    if(H != NULL)
    {
        H->Heapsize = 0;
        for(i=0;i<G->nNumOfVertex;i++)
        {
            printf("Enter Number of Neighbours of Vertex %d which are bigger than current vertex:\n",i+1);
            scanf("%d",&nNumAdjVertices);
            if(nNumAdjVertices >= 0)
            {
                if(nNumAdjVertices!=0)
                    printf("Enter Neighbours of Vertex %d which are bigger than current vertex along with edge weight:\n",i+1);
                for(j=0;j<nNumAdjVertices;j++)
                {
                    scanf("%d",&temp);//TEMP STORES ADJACENT VERTEX INDEX (DISCARDED IF )
                    scanf("%d",&weight);
                    if(temp <= G->nNumOfVertex && temp > i+1 && temp > 0)
                    {
                        H->EdgeArray[H->Heapsize].VertexU = &(G->V[i]);
                        H->EdgeArray[H->Heapsize].VertexV = &(G->V[temp-1]);
                        H->EdgeArray[H->Heapsize].EdgeWeight = weight;
                        H->Heapsize++;
                    }
                    else
                    {
                        if(temp >= i+1)
                            printf("\nVertex you entered is greater than or equal to current Vertex.TRY AGAIN\n");
                        else
                            printf("\nThe Vertex you entered does not exist\nTry again\n");
                        j--;
                    }
                }
            }
            else
            {
                printf("\nError:Number of Adjacent Vertices cannot be negative");
                i--;
            }
        }
        SortEdges(H,G);//Sorting edges in the increasing order of weights
        free(H);
    }
    else
    {
        printf("\nERROR: Memory allocation Falied\n");
        exit(1);
    }
}
void SortEdges(MinHeapptr H,Graphptr G)
{
    int j;
    G->nNumOfEdge = H->Heapsize;
    BuildHeap(H);
    for(j=0;j < G->nNumOfEdge;j++)              ///HEAPSORT
    {
        G->E[j] = ExtractMin(H);
        G->E[j].PresentinMST = 0;//initalising edges so that no edges are present in MST
    }
    free(H);
}

void MakeSet(Vertexptr V)
{
    V->VParent = (V);
    V->Rank = 0;
}

void Union(Vertexptr U,Vertexptr V)
{
    Vertexptr RepU,RepV;
    RepU = FindRep(U);
    RepV = FindRep(V);
    if(RepU == RepV)
        return;
    if(RepU->Rank >= RepV->Rank)
    {
        RepV->VParent = RepU;
        if(RepU->Rank == RepV->Rank)
            RepU->Rank++;
    }
    else
    {
        RepU->VParent=RepV;
    }
}
//Finds repesentative of Set with path compression
Vertexptr FindRep(Vertexptr U)
{
    if(U->VParent != U)
        U->VParent=FindRep(U->VParent);
    return U->VParent;
}
// Build a heap given An Array A->Array
void BuildHeap(MinHeapptr A)
{
    int i;
    for(i=(A->Heapsize/2);i > 0;i--)
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
        if(r <= A->Heapsize && A->EdgeArray[r-1].EdgeWeight < A->EdgeArray[l-1].EdgeWeight)
        {
            s=r;
        }
        else
        {
            s=l;
        }
        if(A->EdgeArray[index-1].EdgeWeight > A->EdgeArray[s-1].EdgeWeight)
        {
            Swap(&A->EdgeArray[index-1],&A->EdgeArray[s-1]);
            MinHeapify(A,s);
        }
    }
}

//find and delete the min Element
struct Edge ExtractMin(MinHeapptr A)
{
    struct Edge minimum;
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
struct Edge FindMin(MinHeapptr A)
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
inline void Swap(Edgeptr a, Edgeptr b)
{
    struct Edge temp;
    temp=(*a);
    (*a)=(*b);
    (*b)=temp;
}
