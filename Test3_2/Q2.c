/*
 * program for taking a directed graph and a pair of vertices v1 and v2 of the graph as input
 * and decide which of the following is true:
 * a. There is no directed path from v1 to v2 and there is no directed path from v2 to v1.
 * b. There is no directed path from v1 to v2 but there is a directed path from v2 to v1.
 * c. There is a directed path from v1 to v2 but there is no directed path from v2 to v1.
 * d. There is a directed path from v2 to v1 and there is a directed path from v1 to v2.
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
int Depthfirstsearch(Vertexptr V1,Vertexptr V2);//to do DFS of graph starting at Graph
void ResetVisit(Vertexptr Graph[], int Num);//reset the Value of Visit in each Node
int main(void)
{
    Vertexptr Graph[50];
    int Num,flag1,V1,V2,flag2;
    printf("enter number of vertices\n");
    scanf("%d",&Num);
    MakeVertex(Graph,Num);
    MakeAdjacList(Graph,Num);
    printf("\nEnter vertex numbers of the pair of vertices(V1 and V2) between which the conditions (a-d) are to be checked\n");
    scanf("%d %d",&V1,&V2);
    flag1 = Depthfirstsearch((Graph[V1-1]),Graph[V2-1]);
    ResetVisit(Graph,Num);
    flag2 = Depthfirstsearch((Graph[V2-1]),Graph[V1-1]);
    if(flag1 == 0 && flag2 == 0)
    {
        printf("\na. There is no directed path from v1 to v2 and there is no directed path from v2 to v1.\n");
    }
    else if(flag1 == 0 && flag2 == 1)
    {
        printf("\nb. There is no directed path from v1 to v2 but there is a directed path from v2 to v1.\n");
    }
    else if(flag1 == 1 && flag2 == 0)
    {
        printf("\nc. There is a directed path from v1 to v2 but there is no directed path from v2 to v1.\n");
    }
    else
    {
        printf("\nd. There is a directed path from v2 to v1 and there is a directed path from v1 to v2.\n");
    }
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
            if( temp>Num )
            {
                do{
                scanf("%c",&buf);
                }while(buf!='\n');
            }
            if(temp>0 && temp<=Num)
            {
                Graph[i]->Adlist=CreateListNode(Graph[temp-1],Graph[i]->Adlist);
            }
        }while(temp>0 && temp<=Num);
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
int Depthfirstsearch(Vertexptr V1,Vertexptr V2)
{
    listptr List=NULL;
    int temp=0;
    V1->visit=1;
    List = V1->Adlist;
    if(V1 == V2)
    {
        return 1;
    }
    while(List!=NULL)
    {
        if(List->Neib->visit==0)
        {
            temp=Depthfirstsearch(List->Neib,V2);
        }
        if(temp == 1)
            break;
        List=List->Next;
    }
    return temp;

}
void ResetVisit(Vertexptr Graph[],int Num)
{
    int i=0;
    for(i=0;i<Num;i++)
    {
        Graph[i]->visit=0;
    }
}
