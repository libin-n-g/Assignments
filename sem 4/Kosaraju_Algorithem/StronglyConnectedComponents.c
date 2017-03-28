/* AUTHOR : LIBIN N GEORGE
 * LAST CHANGED:28-3-2017
 * Program Implementing Kosaraju's Algorithm for computing strongly connected components in a directed graph.
 * Input format:First line : n (number of vertices of the graph)
 * Next line : neighbours of v1 separated by a space and ended by -1
 * Next line : neighbours of v2 separated by a space and ended by -1   and so on..
 * Output : List of vertices in each strongly connected component of G with their respective component numbers.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Vertex
{
    int nElement;
    bool visit;
    struct list* AdjacencyList;
    int Component;
};
typedef struct Vertex* Vertexptr;

struct list
{
    struct Vertex* Neighbours;
    struct list* Next;
};

typedef struct list* listptr;
///FUNCTIONS FOR CREATIONG GRAPH
Vertexptr CreateNodes(int Num);
listptr CreatelistNode(Vertexptr Vertex, listptr List);
Vertexptr Makelists(Vertexptr Nodes, int Num);
///FUNCTION FOR REVERSING GRAPH
Vertexptr MakeReverseGraph(Vertexptr GraphNode,int Num);
///FUNCTIONS DOING DFS
listptr DepthFirstSearchToMakeQueue(Vertexptr Nodes, listptr stack);
void DepthFirstSearchToIdentifyComponents(Vertexptr Nodes,int ComponentNo);
int main(void)
{
    int Num,i=0;
    Vertexptr GraphNode=NULL,ReverseGraph = NULL;
    listptr stack=NULL;
    printf("\nEnter No of Nodes in the graph\n");
    scanf("%d",&Num);
    GraphNode = CreateNodes(Num);
    if(GraphNode!=NULL)
    {
        GraphNode = Makelists(GraphNode,Num);
        ReverseGraph = MakeReverseGraph(GraphNode,Num);
        for(i=0 ;i < Num; i++)
        {
            if((ReverseGraph + i)->visit == false)
            {
                stack = DepthFirstSearchToMakeQueue((ReverseGraph + i),stack);
            }
        }
        i = 0;
        while (stack!=NULL)         //STACK CONTAINS NODES IN THE DECRESING ORDER OF FINISH TIME OF FIRST DFS(IN REVERSED GRAPH)
        {
            if((GraphNode+(stack->Neighbours->nElement-1))->visit == false)
            {
                i++;
                printf("\n List of vertices in strongly connected component %d\n",i);
                DepthFirstSearchToIdentifyComponents(GraphNode+(stack->Neighbours->nElement-1),i);
            }
            stack = stack->Next;
        }
    }
    else
    {
        printf("\nmemory not allocated\n");
    }
    return 0;
}
//creates nodes from 1 to Num
Vertexptr CreateNodes(int Num)
{
    Vertexptr Nodes=NULL;
    int j;
    Nodes = (Vertexptr) malloc(Num * sizeof(struct Vertex));
    if(Nodes !=NULL)
    {
        for(j=0;j<Num;j++)
        {
            (Nodes+j)->nElement=j+1;
            (Nodes+j)->visit = false;
            (Nodes+j)->AdjacencyList=NULL;
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
Vertexptr Makelists(Vertexptr GraphNodes,  int Num)
{
    int i,Neighbour;
    Vertexptr GraphNode;//,ReverseGraphNode;
    for(i=0;i<Num;i++)
    {
        GraphNode = GraphNodes + i;
        //ReverseGraphNode = (*ReverseGraph) + i;
        printf("Enter the Neighbours of Vertex %d (followed by -1)\n",i+1);
        scanf("%d",&Neighbour);
        while(Neighbour!=-1)
        {
            if((Neighbour <= Num) && Neighbour > 0)
            {
                GraphNode->AdjacencyList = CreatelistNode(GraphNodes+Neighbour-1,GraphNode->AdjacencyList);
                //(ReverseGraphNode+Neighbour-1)->AdjacencyList = CreatelistNode(ReverseGraphNode,(ReverseGraphNode+Neighbour-1)->AdjacencyList);
            }
            else
            {
                printf("\nThe Vertex you entered does not exist\nTry again\n");
            }
            scanf("%d",&Neighbour);
        }
    }
    return GraphNodes;
}
//MAKE REVERSEGRAPH FORM GIVEN GRAPH
Vertexptr MakeReverseGraph(Vertexptr GraphNode,int Num)
{
    listptr List=NULL;
    Vertexptr ReverseGraph = NULL,GraphVertex;
    int i;
    ReverseGraph = CreateNodes(Num);
    if(ReverseGraph!=NULL)
    {
        for(i=0;i< Num;i++)
        {
            GraphVertex = GraphNode + i;
            List = GraphVertex->AdjacencyList;
            while(List!=NULL)
            {
                (ReverseGraph + List->Neighbours->nElement -1)->AdjacencyList = CreatelistNode(ReverseGraph+i,(ReverseGraph + List->Neighbours->nElement -1)->AdjacencyList);
                List=List->Next;
            }
        }
    }
    return ReverseGraph;
}

//adds elements to the list
listptr CreatelistNode(Vertexptr Node,listptr AdjList)
{
    listptr New=NULL;
    New = (listptr)malloc(sizeof(struct list));
    if(New==NULL)
    {
        printf("\nMemory Allocation failed\n");
        exit(1);
    }
    else
    {
        New->Neighbours = Node;
        New->Next = AdjList;
        return New;
    }
}
//FIRST DFS AND INSERTS NODES INTO STACK WHEN NODE IS FINISHED(STACK CONTAINS DECRESING ORDER OF FINISH TIME i.e LAST IN FIRST OUT)
listptr DepthFirstSearchToMakeQueue(Vertexptr Nodes, listptr stack)
{
    listptr List=NULL;
    Nodes->visit = true;
    List = Nodes->AdjacencyList;
    while(List!=NULL)
    {
        if(List->Neighbours->visit == false)
        {

            stack = DepthFirstSearchToMakeQueue(List->Neighbours,stack);
        }
        List=List->Next;
    }
    stack = CreatelistNode(Nodes,stack);
    return stack;
}
///DEPTH FIRST SEARCH TO FIND COMPONENTS
void DepthFirstSearchToIdentifyComponents(Vertexptr Nodes,int ComponentNo)
{
    listptr List=NULL;
    List = Nodes->AdjacencyList;
    Nodes->visit = true;
    Nodes->Component = ComponentNo;
    printf("\t%d",Nodes->nElement);
    while(List!=NULL)
    {
        if(List->Neighbours->visit == false)
        {

            DepthFirstSearchToIdentifyComponents(List->Neighbours,ComponentNo);
        }
        List=List->Next;
    }
}
