/* AUTHOR : LIBIN N GEORGE
 * Date:20-2-2017
 * Output format: If edge (u, v) is in every MST of G, output "yes" and output "no" otherwise.
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

//functions for creating Graph
Vertexptr CreateVertexes(int Num);//creates Vertex from 1 to Num
void CreatelistVertex(Vertexptr V, Vertexptr VertexNeibour, int weight);//adds adjacency list elements to the current adjacency list of V
Vertexptr Makelists(Vertexptr V, int Num);//Make adjacency list for each vertex
void DeleteEdge(Vertexptr u,Vertexptr v);//Delete direted edge from u to v

// Functions for heap operations
void DecreaseKey(HeapPtr A,int i,int NewKey);//decrease key of HeapArray at index i
struct Vertex* extractmin(HeapPtr A);//find and delete min
struct Vertex* FindMin(HeapPtr A);//finds min
void MinHeapify(HeapPtr A, int index);

void Swap(struct Vertex* *a,struct Vertex* *b);

int main(void)
{
    int Num,Wt1,Wt2,u,v;
    Vertexptr V=NULL;
    printf("\nEnter No of Vertex in the graph\n");
    scanf("%d",&Num);
    if(Num > 0)
    {
        V=CreateVertexes(Num);
        if(V!=NULL)
        {
            V = Makelists(V,Num);
            Wt1=PrimsAlgorithem(V,Num);
            printf("Enter the vertex numbers u and v (separated by a space) of the endpoints of the edge (u,v) whose membership in all MSTs is to be checked\n");
            scanf("%d",&u);
            scanf("%d",&v);
            DeleteEdge(V+u-1,V+v-1);
            DeleteEdge(V+v-1,V+u-1);
            Wt2=PrimsAlgorithem(V,Num);
            if(Wt1 == Wt2)
            {
                printf("\nNo\n");
            }
            else//if the graph is not conneted after deleting edge the total weight of graph can decrese
            {
                printf("\nYes\n");
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
void DeleteEdge(Vertexptr u,Vertexptr v)
{
    listptr Adjlist;
    listptr temp,prev;
    int flag=0;
    Adjlist=u->Neigh;
    while (Adjlist!=NULL)
    {
        if(Adjlist->Neighbours == v)
        {
            temp=Adjlist->Next;
            flag=1;
            if(temp!=NULL)
            {
                Adjlist->Neighbours = Adjlist->Next->Neighbours;
                Adjlist->edgewt = Adjlist->Next->edgewt;
                Adjlist->Next = Adjlist->Next->Next;
                free(temp);
                break;
            }
            else
            {
                if(prev==NULL)
                {
                    u->Neigh=NULL;
                }
                else
                {
                    prev->Next=NULL;//case in which the edge to be deleted is at the end of adjacency list
                }
                free(Adjlist);
                break;
            }
        }
        prev=Adjlist;
        Adjlist=Adjlist->Next;

    }
    if(flag==0)
        printf("\nEdge from u to v not found\n");
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
    int WeightOfGraph=0;
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

                if(u->dist==INF)
                {
                    return -10000;             //Disconneted Graph No MST can be formed
                }
                if(adjlist->Neighbours->HeapPosition < H->Heapsize && adjlist->edgewt < (*v)->dist)
                {
                    WeightOfGraph=WeightOfGraph + adjlist->edgewt;
                    (*v)->Prev=u;
                    DecreaseKey(H,(*v)->HeapPosition+1,adjlist->edgewt);
                }
                adjlist = adjlist->Next;
            }
        }
    }
    free(H);
    return WeightOfGraph;
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
