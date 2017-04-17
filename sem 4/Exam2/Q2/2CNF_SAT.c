/* AUTHOR : LIBIN N GEORGE
 * Q2:2CNF_SAT
 * Program to determine whether an input boolean formula in 2-CNF form is satisfiable or not
 * and computes a satisfying assignment if the formula is true. This can be done by reducing the problem to
 * strongly connected components problem (Kosaraju Algorithem).
 * Converting in the O(m) where m is number of clauses
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define Max(A,B) (A)>(B)?(A):(B)
#define TRUE 1
#define FALSE 0
#define INVALID -1
struct Vertex
{
    int nElement;
    int nindexofX;
    int Valid;
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

Vertexptr KosarajuAlgorithem(Vertexptr GraphNode,int Num);

///FUNCTIONS FOR CREATIONG GRAPH
Vertexptr CreateNodes(int Num);
listptr CreatelistNode(Vertexptr Vertex, listptr List);
///FUNCTIONS FOR CREATIONG GRAPH AND CONVERTION OF CNF
Vertexptr InputCNFandConvert(Vertexptr Nodes, int Num, int *Maxindex);
///FUNCTION FOR REVERSING GRAPH
Vertexptr MakeReverseGraph(Vertexptr GraphNode,int Num);
///FUNCTIONS DOING DFS
listptr DepthFirstSearchToMakeQueue(Vertexptr Nodes, listptr stack);
void DepthFirstSearchToIdentifyComponents(Vertexptr Nodes, int ComponentNo, int X[]);//Also assigns value to the CNF variables (stored in X[])
int main(void)
{
    int Num;
    Vertexptr GraphNode=NULL;
    printf("\nEnter No of clauses in 2CNF \n");
    scanf("%d",&Num);
    GraphNode = CreateNodes(4*Num+1);

    if(GraphNode!=NULL)
    {
        GraphNode = KosarajuAlgorithem(GraphNode,Num);
        free(GraphNode);
    }
    else
    {
        printf("\nmemory not allocated\n");
    }
    return 0;
}
//Kosaraju Algorithem which convert 2CNF to graph and solves it
Vertexptr KosarajuAlgorithem(Vertexptr GraphNode,int Num)
{
    Vertexptr ReverseGraph = NULL;
    listptr stack=NULL;
    int i;
    int *Maxindex;
    Maxindex =malloc(sizeof(int));
    (*Maxindex) = 0;
    int X[100];

    GraphNode = InputCNFandConvert(GraphNode,Num,Maxindex);
    ReverseGraph = MakeReverseGraph(GraphNode,4*Num+1);
    for(i = -(*Maxindex) ;i <= (*Maxindex) ; i++)
    {
        if((ReverseGraph + 2*Num + i)->visit == false && (ReverseGraph+ 2*Num + i)->Valid == 1)
        {
            stack = DepthFirstSearchToMakeQueue((ReverseGraph + 2*Num +i),stack);
        }
    }
    for(i=0;i < (*Maxindex);i++)
    {
        X[i] = -1;
    }
    i = 0;
    while (stack!=NULL)         //STACK CONTAINS NODES IN THE DECRESING ORDER OF FINISH TIME OF FIRST DFS(IN REVERSED GRAPH)
    {
        if(((GraphNode+(stack->Neighbours->nElement-1))->visit == false) && ((GraphNode+(stack->Neighbours->nElement-1))->Valid == 1))
        {
            i++;
            DepthFirstSearchToIdentifyComponents(GraphNode+(stack->Neighbours->nElement-1),i,X);
        }
        stack = stack->Next;
    }
    for(i= 1 ; i <= (*Maxindex) ;i++)
    {
        if((GraphNode + 2*Num + i)->Component == (GraphNode + 2*Num - i)->Component)// x xbar has same component==> No solution
        {
            printf("\nThe Solution Doesnot Exist \n");
            return GraphNode;
        }
    }
    for(i= 1 ; i <= (*Maxindex) ;i++)
    {                                                        //Printing the Solution
        if(X[i-1] == 0)
        {
            printf("X[%d] = FALSE\n",i);
        }
        if(X[i-1] == 1)
        {
            printf("X[%d] = TRUE\n",i);
        }
    }
    return GraphNode;
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
            (Nodes+j)->Valid = 0;
        }
        return Nodes;
    }
    else
    {
        printf("\nmemory not allocated\n");
        return Nodes;
    }
}
//Take INput and Convert it into Graph
///In this notation, the clause (x 1 ∨ x2) will be encoded as +1 − 2 and (x 1 ∨ x 3 )will be encoded as −1 − 3 and so on.
Vertexptr InputCNFandConvert(Vertexptr GraphNodes,  int Num,int* Maxindex)
{
    int i;
    int u,v;
    Vertexptr GraphNode1u,GraphNode1v,GraphNode2u,GraphNode2v;
    printf("\n Enter Each Clause in following encoding\n Clause (x 1 ∨ x2) will be encoded as +1 − 2 and (x 1 ∨ x 3 )will\n be encoded as −1 − 3 and so on.\n");
    for(i=0;i<Num;i++)
    {
        scanf("%d",&u);
        scanf("%d",&v);
        GraphNode1u = GraphNodes + 2*Num + u; //+u
        GraphNode1u->Valid = 1;
        GraphNode1u->nindexofX = u;
        GraphNode2u = GraphNodes + 2*Num - u; //-u
        GraphNode2u->Valid = 1;
        GraphNode2u->nindexofX = -u;
        GraphNode1v = GraphNodes + 2*Num + v; //+v
        GraphNode1v->Valid = 1;
        GraphNode1v->nindexofX = v;
        GraphNode2v = GraphNodes + 2*Num - v; //-v
        GraphNode2v->Valid = 1;
        GraphNode2v->nindexofX = -v;
        GraphNode2u->AdjacencyList = CreatelistNode(GraphNode1v,GraphNode2u->AdjacencyList);
        GraphNode2v->AdjacencyList = CreatelistNode(GraphNode1u,GraphNode2v->AdjacencyList);
        (*Maxindex) = Max((*Maxindex),abs(u));
        (*Maxindex) = Max((*Maxindex),abs(v));
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
        for(i=0;i < Num;i++)
        {
            GraphVertex = GraphNode + i;

            List = GraphVertex->AdjacencyList;
            while(List!=NULL)
            {
                (ReverseGraph + List->Neighbours->nElement -1)->AdjacencyList = CreatelistNode(ReverseGraph+i,(ReverseGraph + List->Neighbours->nElement -1)->AdjacencyList);
                List=List->Next;
            }
            (ReverseGraph + i)->Valid = GraphVertex->Valid;
            (ReverseGraph + i)->nindexofX = GraphVertex->nindexofX;
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
///DEPTH FIRST SEARCH TO FIND COMPONENTS AND ASSIGN TRUTH VALUES TO X[i]
void DepthFirstSearchToIdentifyComponents(Vertexptr Nodes,int ComponentNo,int X[])
{
    listptr List=NULL;
    List = Nodes->AdjacencyList;
    Nodes->visit = true;
    Nodes->Component = ComponentNo;
    if(X[(abs(Nodes->nindexofX))-1] == INVALID)
    {
        if(Nodes->nindexofX < 0)
        {
            X[(abs(Nodes->nindexofX))-1] = FALSE;
        }
        else
        {
            X[(abs(Nodes->nindexofX))-1] = TRUE;
        }
    }
    while(List!=NULL)
    {
        if(List->Neighbours->visit == false)
        {

            DepthFirstSearchToIdentifyComponents(List->Neighbours,ComponentNo,X);
        }
        List=List->Next;
    }
}
