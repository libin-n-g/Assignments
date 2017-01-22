/* LAST CHANGED : 4-11-2016
 * AUTHOR : LIBIN N GEORGE
 * DFS to detect if there is a directed cycle in the input graph
 * and print the vertices of a directed cycle (if there is one)
 * DFS program also find the start and finish times of traversal
 *  of each vertex in the traversal of a directed graph
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

int time=-1;//globel time variable

Nodeptr CreateNodes(int Num);//creates nodes from 1 to Num
listptr CreatelistNode(Nodeptr Nodes, Nodeptr NodeNeibour, listptr Head);//adds elements to the list
Nodeptr Makelists(Nodeptr Nodes, int Num);//Make adjacency list for each entry
void DepthFirstSearch(Nodeptr Nodes, Nodeptr Predecessor, int *flag);
void PrintStartEndtime(int Num,Nodeptr Nodes);\

int main(void)
{
    int Num,i=0,flag=0;
    Nodeptr Nodes=NULL;
    printf("\nEnter No of Nodes in the graph\n");
    scanf("%d",&Num);
    Nodes=CreateNodes(Num);
    if(Nodes!=NULL)
    {
        Nodes = Makelists(Nodes,Num);
    }
    else
    {
        printf("\nmemory not allocated\n");
    }
    while(i < Num)
    {
        if((Nodes+i)->start_time == -1)
        {
            DepthFirstSearch(Nodes+i,NULL,&flag);
        }
        i++;
    }
    if(flag == 0)
        printf("\nNO CYCLE IS DETECTED\n");
    PrintStartEndtime(Num,Nodes);
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
void DepthFirstSearch(Nodeptr Nodes ,Nodeptr Predecessor,int* flag)
{
    Nodes->start_time=++time;
    listptr List=NULL;
    Nodeptr PRENode=NULL;
    Nodes->predecessor=Predecessor;
    List=Nodes->Neigh;
    int Cycles[20];
    int i=0;
    while(List!=NULL)
    {
        if(List->Neighbours->start_time==-1)
        {
            DepthFirstSearch(List->Neighbours,Nodes,flag);
        }
        else
        {
            if(List->Neighbours->End_time == -1 && (*flag) == 0)
            {       (*flag)=1;
                    Cycles[i++]=List->Neighbours->nElement;
                    PRENode=Nodes;
                    while (PRENode != NULL && PRENode!= List->Neighbours)
                    {
                        Cycles[i++]=PRENode->nElement;
                        PRENode=PRENode->predecessor;
                    }
                    printf("The Cycle detected is \n");
                    i--;
                    while(i >= 0)
                    {
                        printf("\t%d\t",Cycles[i--]);
                    }

            }
        }
        List=List->Next;
    }
    Nodes->End_time=++time;
}
void PrintStartEndtime(int Num,Nodeptr Nodes)
{
    int i;
    for(i=0;i<Num;i++)
    {
        printf("\nVertex:%d\tStart time:%d\tEnd Time:%d\n",Nodes[i].nElement,Nodes[i].start_time,Nodes[i].End_time);
    }
}
