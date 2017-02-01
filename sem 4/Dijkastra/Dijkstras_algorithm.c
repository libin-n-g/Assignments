/* AUTHOR : LIBIN N GEORGE
 * LAST CHANGED:1-2-2017
 * Program which Implement Dijkstra's Algorithm for computing single source shortest path. Uses heaps for implementation.
 * Output format:Print the shortest path distances to each vertex from the source vertex and
 * the predecessor of every vertex on the shortest path to the source vertex.
 * Also detects If there is no path from source vertex to a certain vertex.
 */
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#define INF INT_MAX
#define MAXHEAPLENGTH 100
#define Parent(X) (X/2)
#define LeftChild(X) (2*X)
#define RightChild(X) (2*X+1)

struct Vertex
{
    int VertexNumber;
    struct list* Neigh;
    int HeapPosition;
    int dist;
    struct Vertex* Prev;
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
};

struct Heap
{
    struct HeapElement Array[MAXHEAPLENGTH];
    int Heapsize;
};

typedef struct Heap* HeapPtr;


void DijkstraAlgorithm(Vertexptr V, int Num, int Source);
void PrintResult(Vertexptr A,int Num);//Display Results

//functions for creating Graph
Vertexptr CreateVertexes(int Num);//creates Vertex from 1 to Num
void CreatelistVertex(Vertexptr V, Vertexptr VertexNeibour, int weight);//adds adjacency list elements to the current adjacency list of V
Vertexptr Makelists(Vertexptr V, int Num);//Make adjacency list for each vertex

// Functions for heap operations
void DecreaseKey(HeapPtr A,int i,int NewKey);//decrease key of HeapArray at index i
struct HeapElement extractmin(HeapPtr A);//find and delete min
struct HeapElement FindMin(HeapPtr A);//finds min
void MinHeapify(HeapPtr A, int index);

void Swap(struct HeapElement *a,struct HeapElement *b);

int main(void)
{
    int Num,source;
    Vertexptr V=NULL;
    printf("\nEnter No of Vertex in the graph\n");
    scanf("%d",&Num);
    if(Num > 0)
    {
        V=CreateVertexes(Num);
        if(V!=NULL)
        {
            V = Makelists(V,Num);
            printf("Enter the Source Vertex\n");
            scanf("%d",&source);
            if(source>0)
            {
            DijkstraAlgorithm(V,Num,source);
            PrintResult(V,Num);
            }
            else {
                printf("\nSOURCE DOES NOT EXIST\n");
            }
        }
        else
        {
            printf("\nmemory not allocated\n");
            return 1;
        }
    }
    else
    {
        printf("\nNUMBER OF VERTEX IS LESS THAN ZERO\n");
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
    if(A->Array[i-1].VertexIndex->dist < NewKey)
    {
        printf("\nERROR:NewKey is Greater than Current key\n");
    }
    else {
        A->Array[i-1].VertexIndex->dist = NewKey;
        while ( i > 1 && A->Array[Parent(i)-1].VertexIndex->dist > A->Array[i-1].VertexIndex->dist)//condition for swaping and index checking
        {
            Swap(&(A->Array[i-1]),&(A->Array[Parent(i)-1]));
            i=Parent(i);
        }
    }

}

void DijkstraAlgorithm(Vertexptr V,int Num,int Source)
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
        return;
    }
    else {
        H->Heapsize=0;
        for(i=0;i<Num;i++)//Making the Heap
        {
            H->Array[i].VertexIndex = V+i;
            (V+i)->HeapPosition=i;
            H->Array[i].VertexIndex->dist=INF;
            H->Array[i].VertexIndex->Prev=NULL;
            H->Heapsize++;
        }
        H->Array[Source-1].VertexIndex->dist=0;
        Swap(&(H->Array[Source-1]),&(H->Array[0]));//source as root

        while (H->Heapsize > 0) {
            u = extractmin(H);
            adjlist = u.VertexIndex->Neigh;

            while ( adjlist!= NULL) {
                v=&(H->Array[adjlist->Neighbours->HeapPosition]);
                if(u.VertexIndex->dist==INF)
                {
                    break;//Disconneted Graph
                }
                alt = u.VertexIndex->dist + adjlist->edgewt;
                if(alt < v->VertexIndex->dist)
                {
                    v->VertexIndex->Prev=u.VertexIndex;
                    DecreaseKey(H,v->VertexIndex->HeapPosition+1,alt);
                }
                adjlist = adjlist->Next;
            }
        }
    }
}
//prints output
void PrintResult(Vertexptr A, int Num)
{
    int i;
    printf("\n-----------------------------------------------------------------------\n");
    printf("\tDestination\tPredecessor Vertex\tShortestDistance\n");
    for(i=0;i<Num;i++)
    {
        if((A+i)->dist < INF)
        {
            if((A+i)->Prev != NULL)
                printf("\t\t%d\t\t%d\t\t%d\n",(A+i)->VertexNumber,(A+i)->Prev->VertexNumber,(A+i)->dist);
            else {
                printf("\t\t%d\t\tN.A\t\t%d\n",(A+i)->VertexNumber,(A+i)->dist);
            }
        }
        else
        {
            printf("\tNO PATH FOUND FROM SOURCE TO VERTEX %d\n",(A+i)->VertexNumber);
        }
    }
}

//find and delete the min Element
struct HeapElement extractmin(HeapPtr A)
{
    struct HeapElement minimum;
    minimum = FindMin(A);
    if(A->Heapsize<1)
    {
        printf("\nERROR:Heap Underflow\n");
        exit(1);
    }
    else
    {
        Swap(&(A->Array[0]),&(A->Array[A->Heapsize-1]));
        A->Heapsize--;
        MinHeapify(A,1);
    }
    return minimum;
}
//finds element having maximum priority(min Key)
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
// make Min Heap from two Heaps (as child)
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
        if(r <= A->Heapsize && A->Array[r-1].VertexIndex->dist < A->Array[l-1].VertexIndex->dist)
        {
            s=r;
        }
        else
        {
            s=l;
        }
        if(A->Array[index-1].VertexIndex->dist>A->Array[s-1].VertexIndex->dist)
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
