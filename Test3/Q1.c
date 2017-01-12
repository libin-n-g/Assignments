/* Write a program for checking whether an undirected graph given as input is a tree or not.
 * Assume vertex numbers are from 1 to n.
*/
#include <stdio.h>
#include <stdlib.h>

struct Vertex
{
    int Value;
    int visit;
    struct AdjaList *Adlist;
};

typedef struct Vertex* Vertexptr;
struct AdjaList
{
    struct Vertex *Neib;
    struct AdjaList *Next;
};
typedef struct AdjaList* listptr;

void MakeVertex(Vertexptr Graph[50],int Num);
void MakeAdjacList(Vertexptr Graph[], int Num);
listptr CreateListNode(Vertexptr Node,listptr list);
void IsTree(Vertexptr Graph,int *flag);//to do DFS of graph starting at Graph
int main(void)
{
    Vertexptr Graph[50];
    int Num,flag=0,i;
    printf("enter number of vertices\n");
    scanf("%d",&Num);
    MakeVertex(Graph,Num);
    MakeAdjacList(Graph,Num);
    IsTree((Graph[0]),&flag);
    if(flag==0)
    {
        for(i=0;i<Num;i++)
        {
            if(Graph[i]->visit == 0)
            {
                printf("\nNo\nDisconnected Graph Detected\n");
                flag=1;
                break;
            }
        }
    }
    if(flag == 0)
        printf("\nYes\n");
    return 0;
}
void MakeVertex(Vertexptr Graph[50],int Num)
{
    int i=0;
    for(i=0;i<Num;i++)
    {
        Graph[i]=(Vertexptr)malloc(sizeof (struct Vertex));
        if(Graph[i]==NULL)
        {
            printf("\nMemory Allocation failed\n");
            exit(1);
        }
        else
        {
            Graph[i]->Value=i+1;
            Graph[i]->visit=0;
            Graph[i]->Adlist=NULL;
        }
    }
}
void MakeAdjacList(Vertexptr Graph[50],int Num)
{
    int i=0,temp=0;
    char buf;
    for(i=0;i<Num;i++)
    {
        printf("Enter neibours of %d\n",i+1);
        do
        {
            scanf("%d",&temp);
            if( temp>-1 &&  temp<=(i+1) )
            {
                do{
                scanf("%c",&buf);
                }while(buf!='\n');
            }
            if( temp>Num )
            {
                do{
                scanf("%c",&buf);
                }while(buf!='\n');
            }
            if(temp>(i+1) && temp<=Num)
            {
                Graph[i]->Adlist=CreateListNode(Graph[temp-1],Graph[i]->Adlist);
            }
        }while(temp>(i+1) && temp<=Num);
    }
}
listptr CreateListNode(Vertexptr Node,listptr list)
{
    listptr New=NULL;
    New=(listptr)malloc(sizeof(struct AdjaList));
    if(New==NULL)
    {
        printf("\nMemory Allocation failed\n");
        exit(1);
    }
    else
    {
        if(list == NULL)
        {
            New->Neib=Node;
            New->Next=NULL;
        }
        else
        {
            New->Neib=Node;
            New->Next=list;
        }
        return New;
    }
}
void IsTree(Vertexptr Graph, int *flag)
{
    listptr List=NULL;
    Graph->visit=1;
    List = Graph->Adlist;
    while(List!=NULL)
    {
        if(List->Neib->visit==0)
            IsTree(List->Neib,flag);
        else
        {
            printf("\nNo\nCycle is detected\n");
            (*flag)=1;
        }
        if((*flag)==1)
        {
            break;
        }
        List=List->Next;
    }


}
