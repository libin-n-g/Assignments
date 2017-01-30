
#include <stdio.h>
#include <limits.h>
#define INF INT_MAX

struct Vertex
{
    int VertexNumber;
    struct list* Neigh;
};
typedef struct Vertex* Vertexptr;

struct list
{
    struct Vertex* Neighbours;
    struct list* Next;
    int edgewt;
};

typedef struct list* listptr;

Vertexptr CreateVertexes(int Num);//creates Vertex from 1 to Num
listptr CreatelistVertex(Vertexptr V, Vertexptr VertexNeibour, int weight, listptr Head);//adds elements to the list
Vertexptr Makelists(Vertexptr V, int Num);//Make adjacency list for each entry

int main(void)
{
    int Num,i=0,j=1;
    Vertexptr V=NULL;
    printf("\nEnter No of Vertex in the graph\n");
    scanf("%d",&Num);
    V=CreateVertexes(Num);
    if(V!=NULL)
    {
        V = Makelists(V,Num);
    }
    else
    {
        printf("\nmemory not allocated\n");
        return 1;
    }
    return 0;
}
//adds elements to the list
listptr CreatelistVertex(Vertexptr V,Vertexptr VertexNeibour,int weight, listptr Head)
{
    listptr New=NULL;
    New = (listptr)malloc(sizeof (struct list));
    if (New != NULL)
    {
        if(Head == NULL)
        {
            V->Neigh = New;
            V->Neigh->Neighbours=VertexNeibour;
            V->Neigh->Next=NULL;
            V->Neigh->edgewt=weight;
            return V->Neigh;
        }
        else
        {

            Head->Next=New;
            New->Neighbours=VertexNeibour;
            New->Next=NULL;
            New->edgewt=weight;
            return New;
        }
    }
    else
    {
        printf("\nMemory Allocation failed\n");
        return NULL;
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
    listptr listVertex=NULL;
    Vertexptr nVertex;
    for(i=0;i<Num;i++)
    {
        printf("Enter Number of Neighbours of Vertex %d which are bigger than current vertex:\n",i+1);
        scanf("%d",&Neigh);
        if(Neigh<Num)
        {
            if(Neigh!=0)
                printf("Enter Neighbours of Vertex %d which are bigger than current vertex along with edge weight:\n",i+1);
            listVertex=NULL;
            nVertex=V+i;
            for(j=0;j<Neigh;j++)
            {
                scanf("%d",&temp);
                scanf("%d",&weight);
                if(temp<=Num && temp!= i+1 && temp > 0 && weight > 0)
                {
                    listVertex = CreatelistVertex(nVertex,V+temp-1,listVertex);
                    listVertex = CreatelistVertex(nVertex,V+temp-1,listVertex);
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
            printf("\nNumber Neighbours exceeds number of Vertex\n");
            i--;
        }


            //        printf("Enter Number of Neighbours of Vertex %d :\n",i+1);
//        scanf("%d",&Neigh);
//        if(Neigh<Num)
//        {
//            if(Neigh!=0)
//                printf("Enter Neighbours of Vertex %d :\n",i+1);
//            listVertex=NULL;
//            nVertex = V+i;


//
//    }
    return V;
}
