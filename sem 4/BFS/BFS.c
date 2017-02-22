/* LAST CHANGED :08-01-2017
 * AUTHOR : LIBIN N GEORGE
 * program which Implement Breadth First Search of an undirected graph and
 *  print the BFS visit order of the vertices and the distances of each vertex from the source node
 */

#include <stdio.h>
#include<stdlib.h>
#define INFINITY -1

struct Node
{
    int nElement;
    int visit;
    int Distance;
    struct Node* predecessor;
    struct list* Neigh;
};
typedef struct Node* Nodeptr;

struct list
{
    struct Node* Neighbours;
    struct list* Next;
};

typedef struct list* listptr;

struct Queue
{
    Nodeptr Data;
    struct Queue* NextData;
};

typedef struct Queue* Queueptr;

Queueptr QInsertQueue(Queueptr Rear, Queueptr *Front, Nodeptr Item);
Nodeptr NRemoveQueue(Queueptr* Front);

Nodeptr CreateNodes(int Num);//creates nodes from 1 to Num
listptr CreatelistNode(Nodeptr Nodes, Nodeptr NodeNeibour, listptr Head);//adds elements to the list
Nodeptr Makelists(Nodeptr Nodes, int Num);//Make adjacency list for each entry
void BreadthFirstSearch(Nodeptr Root,Queueptr Rear, Queueptr *Front);
int main(void)
{
    int Num,i=0,Source;
    Nodeptr Nodes=NULL;
    printf("\nEnter No of Vertex in the graph\n");
    scanf("%d",&Num);
    Nodes=CreateNodes(Num);
    Queueptr Rear=NULL,Front=NULL;
    if(Nodes!=NULL)
    {
        Nodes = Makelists(Nodes,Num);
    }
    else
    {
        printf("\nmemory not allocated\n");
    }
    printf("\nEnter the Source Node: ");
    scanf("%d",&Source);
    printf("\nBFS visit order of the vertices:\n");
    if(Source <= Num && Source > 0)
    {
        BreadthFirstSearch(Nodes+Source-1,Rear,&Front);
        printf("\n");
    }
    for(i = 0;i < Num;i++)
    {
        if( ((Nodes+i)->Distance) != INFINITY)
        {
            printf("\nDistance of Node %d From Node %d is %d\n",i+1,Source,((Nodes+i)->Distance));
        }
        else                                                                                                //In case of disconnected Graph
        {
            printf("\nDistance of Node %d From Node %d is INFINITY\n",i+1,Source);
        }
    }
    return 0;
}
//adds elements to the list
listptr CreatelistNode(Nodeptr Nodes,Nodeptr NodeNeibour, listptr Head)
{
    listptr New=NULL;
    New = (listptr)malloc(sizeof (struct list));
    if (New != NULL)
    {
        if(Head == NULL)
        {
            Nodes->Neigh = New;
            Nodes->Neigh->Neighbours=NodeNeibour;
            Nodes->Neigh->Next=NULL;
            return Nodes->Neigh;
        }
        else
        {

            Head->Next=New;
            New->Neighbours=NodeNeibour;
            New->Next=NULL;
            return New;
        }
    }
    else
    {
        printf("\nMemory Allocation failed\n");
        return NULL;
    }
}
//creates nodes from 1 to Num
Nodeptr CreateNodes(int Num)
{
    Nodeptr Nodes=NULL;
    int j;
    Nodes = (Nodeptr) malloc(Num * sizeof(struct Node));
    if(Nodes !=NULL)
    {
        for(j=0;j<Num;j++)
        {
            (Nodes+j)->nElement=j+1;
            (Nodes+j)->visit=0;
            (Nodes+j)->Neigh=NULL;
            (Nodes+j)->Distance=INFINITY;
            (Nodes+j)->predecessor=NULL;
        }
        return Nodes;
    }
    else
    {
        printf("\nmemory not allocated\n");
        return Nodes;
    }
}
//Make adjacency list for each entry
Nodeptr Makelists(Nodeptr Nodes,int Num)
{
    int i,j,Neigh,temp;
    listptr listnode=NULL;
    Nodeptr nNode;
    for(i=0;i<Num;i++)
    {

        printf("Enter Number of Neighbours of Node %d :\n",i+1);
        scanf("%d",&Neigh);
        if(Neigh<Num)
        {
            if(Neigh!=0)
                printf("Enter Neighbours of Node %d :\n",i+1);
            listnode=NULL;
            nNode = Nodes+i;
            for(j=0;j<Neigh;j++)
            {
                scanf("%d",&temp);
                if(temp<=Num && temp!= i+1 && temp > 0)
                    listnode = CreatelistNode(nNode,Nodes+temp-1,listnode);
                else
                {
                    if(temp == i+1)
                        printf("\nNode cannot be connected to itself.TRY AGAIN\n");
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
    }
    return Nodes;
}
//function for Breath First Search
void BreadthFirstSearch(Nodeptr Root , Queueptr Rear, Queueptr *Front)
{
    listptr List=NULL;

    Nodeptr currentNode=NULL;
    printf("\t%d\t",Root->nElement);
    Root->visit = 1;
    Root->Distance = 0;
    Rear=QInsertQueue(Rear,Front,Root);
    while((*Front)!=NULL)
    {
        currentNode = NRemoveQueue(Front);
        List=currentNode->Neigh;
        while (List!=NULL)
        {
            if(List->Neighbours->visit == 0)
            {
                printf("\t%d\t",List->Neighbours->nElement);
                List->Neighbours->visit=1;
                List->Neighbours->Distance=currentNode->Distance+1;
                List->Neighbours->predecessor=currentNode;
                Rear = QInsertQueue(Rear,Front,List->Neighbours);
            }
            List = List->Next;
        }
    }

}
//inserting an element to the Queue
Queueptr QInsertQueue(Queueptr Rear,Queueptr *Front,Nodeptr Item)
{
    Queueptr New=NULL;
    New = (Queueptr)malloc(sizeof (struct Queue));

    if(New !=NULL)
    {
        New->Data=Item;
        New->NextData=NULL;
        if((Rear!=NULL) && ((*Front)!=NULL))
            Rear->NextData = New;
        else
        {
            (*Front)=New;
            Rear=New;
        }
    }
    else
    {
        printf("\nmemory not allocated\n");
    }
    return New;
}
//Removing an element to the Queue
Nodeptr NRemoveQueue(Queueptr* Front)
{
    Queueptr TempQ=NULL;
    Nodeptr Temp=NULL;
    TempQ=(*Front);
    Temp=(*Front)->Data;
    (*Front)=(*Front)->NextData;
    free(TempQ);
    return Temp;
}
