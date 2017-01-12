/* LAST CHANGED : 31-10-2016
 * AUTHOR : LIBIN N GEORGE
 * program using DFS to find out the predecessor of every vertex during the traversal.
 * program detects if there at least one cycle in the graph, and if so,
 * as a witness of the cycle detection, print the vertices in a cycle detected.
 */

#include <stdio.h>
#include<stdlib.h>

struct Node
{
    int nElement;
    int visit;
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

Nodeptr CreateNodes(int Num);//creates nodes from 1 to Num
listptr CreatelistNode(Nodeptr Nodes, Nodeptr NodeNeibour, listptr Head);//adds elements to the list
Nodeptr Makelists(Nodeptr Nodes, int Num);//Make adjacency list for each entry
void DepthFirstSearch(Nodeptr Nodes, Nodeptr Predecessor, int *k);
int main(void)
{
    int Num,i=0,k=0;
    Nodeptr Nodes=NULL;
    printf("\nEnter No of Vertex in the graph\n");
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
        if((Nodes+i)->visit == 0)
        {
            DepthFirstSearch(Nodes+i,NULL,&k);
            printf("\n");
        }
        i++;
    }
    if(k == 0)
        printf("\nNO CYCLE IS DETECTED\n");
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
void DepthFirstSearch(Nodeptr Nodes ,Nodeptr Predecessor,int* k)
{
    listptr List=NULL;
    Nodeptr PRENode=NULL;
    printf("\t%d\t",Nodes->nElement);
    Nodes->visit=1;
    Nodes->predecessor=Predecessor;
    List=Nodes->Neigh;
    while(List!=NULL)
    {
        if(List->Neighbours->visit==0)
        {
            DepthFirstSearch(List->Neighbours,Nodes,k);
        }
        else
        {
            if((*k) == 0)
            {
                if(List->Neighbours != Nodes->predecessor)
                {

                        printf("\nA Cycle is detected with following Vertices\n\t%d\n",List->Neighbours->nElement);
                        PRENode=Nodes;
                        while (PRENode != NULL && PRENode!= List->Neighbours)
                        {
                            printf("\t%d\n",PRENode->nElement);
                            PRENode=PRENode->predecessor;
                        }
                        printf("\ncontinuing the transverse\n");
                        (*k)=1;
                }
            }
        }
        List=List->Next;
    }
}
