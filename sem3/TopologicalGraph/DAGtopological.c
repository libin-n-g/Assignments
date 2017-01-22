/* LAST CHANGED : 8-11-2016
 * AUTHOR : LIBIN N GEORGE
 * a) topological ordering of the input graph,if the given graph is a DAG.
 * b) If the input graph is not a DAG,indicate this fact and give output the vertices of a directed cycle in
 *  the input graph
 */

#include <stdio.h>
#include<stdlib.h>

struct Node
{
    int nElement;
    int start_time;
    int End_time;
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

struct Stack
{
    int Nodelabel;
    struct Stack* Next;
};
typedef struct Stack* stackptr;
int time=-1;
Nodeptr CreateNodes(int Num);//creates nodes from 1 to Num
listptr CreatelistNode(Nodeptr Nodes, Nodeptr NodeNeibour, listptr Head);//adds elements to the list
Nodeptr Makelists(Nodeptr Nodes, int Num);//Make adjacency list for each entry
void DepthFirstSearch(Nodeptr Nodes, Nodeptr Predecessor, stackptr *Topological, stackptr *Cycles);
stackptr Push(int Num,stackptr Nodes);//push to stack
void printStack(stackptr Top);
int main(void)
{
    int Num,i=0;
    Nodeptr Nodes=NULL;
    stackptr Cycles=NULL,Topological=NULL;

    printf("\nEnter No of Nodes in the graph\n");
    scanf("%d",&Num);
    Nodes=CreateNodes(Num);
    if(Nodes!=NULL)
    {
        Nodes = Makelists(Nodes,Num);
        while(i < Num)
        {
            if((Nodes+i)->start_time == -1)
            {
                DepthFirstSearch(Nodes+i,NULL,&Topological,&Cycles);
            }
            i++;
        }
        if(Cycles == NULL)
        {
            printf("\nNO CYCLE IS DETECTED\n");
            printf("\nThe Topological ordeing is\n");
            printStack(Topological);
        }
        else
        {
            printf("\nthe input graph is not a DAG\nThe Cycle detected is\n");
            printStack(Cycles);
        }
    }
    else
    {
        printf("\nmemory allocation failed\n");
    }
    //PrintStartEndtime(Num,Nodes);
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
            (Nodes+j)->start_time = -1;
            (Nodes+j)->End_time = -1;
            (Nodes+j)->predecessor=NULL;
            (Nodes+j)->Neigh=NULL;
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
void DepthFirstSearch(Nodeptr Nodes , Nodeptr Predecessor, stackptr* Topological, stackptr* Cycles)
{
    Nodes->start_time=++time;
    listptr List=NULL;
    Nodeptr PRENode=NULL;
    Nodes->predecessor=Predecessor;
    List=Nodes->Neigh;
    while(List!=NULL)
    {
        if(List->Neighbours->start_time==-1)
        {
            DepthFirstSearch(List->Neighbours,Nodes,Topological,Cycles);
        }
        else
        {
            if(List->Neighbours->End_time == -1 && (*Cycles) == NULL)
            {
                (*Cycles)=Push(List->Neighbours->nElement,(*Cycles));
                PRENode=Nodes;
                while (PRENode != NULL && PRENode!= List->Neighbours)
                {
                    (*Cycles)=Push(PRENode->nElement,(*Cycles)) ;
                    PRENode=PRENode->predecessor;
                }
            }
        }
        List=List->Next;
    }
    (*Topological)=Push(Nodes->nElement,(*Topological));
    Nodes->End_time=++time;
}
//pushing to stack
stackptr Push(int Num,stackptr Nodes)
{
    stackptr New=NULL;
    New = (stackptr) malloc(sizeof(struct Stack));
    if(New !=NULL)
    {
        if(Nodes==NULL)
        {
            New->Nodelabel=Num;
            New->Next=NULL;
            return New;
        }
        else
        {
            New->Nodelabel=Num;
            New->Next=Nodes;
            return New;
        }
    }
    else
    {
        printf("\nmemory not allocated\n");
        return Nodes;
    }
}
void printStack(stackptr Top)
{
    stackptr temp=NULL;
    while(Top!=NULL)
    {
        printf("%d\n",Top->Nodelabel);
        temp=Top;
        Top = Top->Next;
        free(temp);
    }

}
