/* AUTHOR : LIBIN N GEORGE
 * LAST CHANGED:3-2-2017
 * Program Implementing Prim's Algorithm for computing Minimum Spanning Tree of the input graph using minheaps.
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
#define MAXHEAPLENGTH 100
#define Parent(X) ((X)/2)
#define LeftChild(X) (2*(X))
#define RightChild(X) (2*(X)+1)

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


struct Heap
{
    struct Vertex* HeapArray[MAXHEAPLENGTH];
    int Heapsize;
};

typedef struct Heap* HeapPtr;


int PrimsAlgorithem(Vertexptr V, int Num);
void PrintResult(Vertexptr A,int Num);//Display Results

//functions for creating Graph
Vertexptr CreateVertexes(int Num);//creates Vertex from 1 to Num
void CreatelistVertex(Vertexptr V, Vertexptr VertexNeibour, int weight);//adds adjacency list elements to the current adjacency list of V
Vertexptr Makelists(Vertexptr V, int Num);//Make adjacency list for each vertex

// Functions for heap operations
void DecreaseKey(HeapPtr A,int i,int NewKey);//decrease key of HeapArray at index i
struct Vertex* extractmin(HeapPtr A);//find and delete min
struct Vertex* FindMin(HeapPtr A);//finds min
void MinHeapify(HeapPtr A, int index);

void Swap(struct Vertex* *a,struct Vertex* *b);

int main(void)
{
    int Num,flag;
    Vertexptr V=NULL;
    printf("\nEnter No of Vertex in the graph\n");
    scanf("%d",&Num);
    if(Num > 0)
    {
        V=CreateVertexes(Num);
        if(V!=NULL)
        {
            V = Makelists(V,Num);
            flag=PrimsAlgorithem(V,Num);
            if(flag == 0)
                PrintResult(V,Num);
            else
                printf("\nThe Given Graph is Disconneted\n");
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
                if(temp<=Num && temp!= i+1 && temp > 0)
                {
                    CreatelistVertex(nVertex,V+temp-1,weight);//creating edge b/w nvertex and V+temp-1 inlist of nVertex
                    CreatelistVertex(V+temp-1,nVertex,weight);
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
    if(A->HeapArray[i-1]->dist < NewKey)
    {
        printf("\nERROR:NewKey is Greater than Current key\n");
    }
    else {
        A->HeapArray[i-1]->dist = NewKey;
        while ( i > 1 && A->HeapArray[Parent(i)-1]->dist > A->HeapArray[i-1]->dist)//condition for swaping and index checking
        {
            Swap(&(A->HeapArray[i-1]),&(A->HeapArray[Parent(i)-1]));
            i=Parent(i);
        }
    }

}

int PrimsAlgorithem(Vertexptr V,int Num)
{
    HeapPtr H;
    struct list* adjlist;
    struct Vertex* u;
    struct Vertex* *v;
    int flag=1;
    H = (HeapPtr)malloc(sizeof (struct Heap));
    if(H == NULL)
    {
        printf("\nERROR:Memory Allocation failed\n");
        return 1;
    }
    else {
        for(H->Heapsize=0;H->Heapsize<Num;H->Heapsize++)//Making the Heap
        {
            H->HeapArray[H->Heapsize] = V+H->Heapsize;
            (V+H->Heapsize)->HeapPosition=H->Heapsize;
            H->HeapArray[H->Heapsize]->dist=INF;
            H->HeapArray[H->Heapsize]->Prev=NULL;
        }
        H->HeapArray[0]->dist=0;

        while (H->Heapsize > 0) {
            u = extractmin(H);
            adjlist = u->Neigh;

            while ( adjlist!= NULL) {
                v=&(H->HeapArray[adjlist->Neighbours->HeapPosition]);
                flag=0;
                if(u->dist==INF)
                {
                    flag = 1;
                    return flag;             //Disconneted Graph No MST can be formed
                }
                if(adjlist->Neighbours->HeapPosition < H->Heapsize && adjlist->edgewt < (*v)->dist)
                {
                    (*v)->Prev=u;
                    DecreaseKey(H,(*v)->HeapPosition+1,adjlist->edgewt);
                }
                adjlist = adjlist->Next;
            }
        }
    }
    free(H);
    return flag;
}
//prints output
void PrintResult(Vertexptr A, int Num)
{
    int i;
    printf("\n-----------------------------------------------------------------------\n");
    printf("\t\t Edges\tEdgeWeight\n");
    for(i=0;i<Num;i++)
    {

        if((A+i)->Prev != NULL)
            printf("\t\t(%d, %d)\t\t%d\n",(A+i)->VertexNumber,(A+i)->Prev->VertexNumber,(A+i)->dist);


    }
    printf("\n-----------------------------------------------------------------------\n");
}

//find and delete the min Element
struct Vertex* extractmin(HeapPtr A)
{
    struct Vertex* minimum;
    minimum = FindMin(A);
    if(A->Heapsize<1)
    {
        printf("\nERROR:Heap Underflow\n");
        exit(1);
    }
    else
    {
        Swap(&(A->HeapArray[0]),&(A->HeapArray[A->Heapsize-1]));
        A->Heapsize--;
        MinHeapify(A,1);
    }
    return minimum;
}
//finds element having maximum priority(min Key)
struct Vertex* FindMin(HeapPtr A)
{
    if(A->Heapsize<1)
    {
        printf("\nERROR:Heap Underflow\n");
        exit(1);
    }
    else
    {
        return (A->HeapArray[0]);
    }
}
// make Min Heap from two Heaps (as child)
void MinHeapify(HeapPtr A, int index)
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
        if(r <= A->Heapsize && A->HeapArray[r-1]->dist < A->HeapArray[l-1]->dist)
        {
            s=r;
        }
        else
        {
            s=l;
        }
        if(A->HeapArray[index-1]->dist > A->HeapArray[s-1]->dist)
        {
            Swap(&A->HeapArray[index-1],&A->HeapArray[s-1]);
            MinHeapify(A,s);
        }
    }
}

void Swap(struct Vertex* *a,struct Vertex* *b)
{
    struct Vertex* temp;
    int postemp;
    postemp=(*a)->HeapPosition;
    (*a)->HeapPosition=(*b)->HeapPosition;
    (*b)->HeapPosition=postemp;
    temp=(*a);
    (*a)=(*b);
    (*b)=temp;
}
