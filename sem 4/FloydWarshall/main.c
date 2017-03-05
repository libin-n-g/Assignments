/* AUTHOR : LIBIN N GEORGE
 * LAST CHANGED:05-03-2017
 * Program Implementing Floyd Warshall algorithm (O(n^3)) for displaying the shortest distance
 * between every pair of vertices (v_i, v_j) in an undirected weighted graph with n vertices.
 * Also, display the respective predecessors pred(v_i,v_j) which is the predecessor of the vertex v_j
 * in the shortest path from the vertex v_i to the vertex v_j.
 */
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#define INF (INT_MAX/3)
#define MAX 50
#define NIL -1

struct Graph
{
    int nNumOfVertex;
    int WeightedAdjacencyMatrix[MAX][MAX];
    int Predecessor[MAX][MAX];
    int Dist[MAX][MAX];
};
typedef struct Graph* Graphptr;

void InitalisePredecessor(Graphptr G);//Initalise Matrix elements into NIL
void InitaliseEdgeWeightMatrix(Graphptr G);//Initalise Matrix elements into INF
void UpdateWeightedAdjacencyMatrix(Graphptr G);
void FloydWarshall(Graphptr G);
void CopyMatrix(int Source[MAX][MAX],int Destination[MAX][MAX],int Upperlimit);
void PrintResult(Graphptr G);

int main(void)
{
    Graphptr G;
    G = (Graphptr)malloc(sizeof(struct Graph));
    if(G != NULL)
    {
        printf("\nEnter Number of Vertices in the Graph\n");
        scanf("%d",&G->nNumOfVertex);
        InitaliseEdgeWeightMatrix(G);
        InitalisePredecessor(G);
        UpdateWeightedAdjacencyMatrix(G);
        FloydWarshall(G);
        PrintResult(G);
        free(G);
    }
    else
    {
        printf("\nERROR:Memory allocation Failed\n");
    }
    return 0;
}
void InitaliseEdgeWeightMatrix(Graphptr G)
{
    int v_i,v_j;
    for(v_i = 0;v_i < G->nNumOfVertex;v_i++)
    {
        for(v_j = 0;v_j < G->nNumOfVertex;v_j++)
        {
            G->WeightedAdjacencyMatrix[v_i][v_j] = INF;
        }
    }
}
void InitalisePredecessor(Graphptr G)
{
    int v_i,v_j;
    for(v_i = 0;v_i < G->nNumOfVertex;v_i++)
    {
        for(v_j = 0;v_j < G->nNumOfVertex;v_j++)
        {
            G->Predecessor[v_i][v_j] = NIL;
        }
    }
}
void UpdateWeightedAdjacencyMatrix(Graphptr G)
{
    int v_i,nNumAdjVertices,j,temp;
    int weight;
    for(v_i=0;v_i<G->nNumOfVertex;v_i++)
    {
        printf("Enter Number of Neighbours of Vertex %d which are bigger than current vertex:\n",v_i+1);
        scanf("%d",&nNumAdjVertices);
        if(nNumAdjVertices >= 0)
        {
            if(nNumAdjVertices!=0)
                printf("Enter Neighbours of Vertex %d which are bigger than current vertex along with edge weight:\n",v_i+1);
            for(j=0;j<nNumAdjVertices;j++)
            {
                scanf("%d",&temp);              //TEMP STORES ADJACENT VERTEX INDEX (DISCARDED IF INVALID)
                scanf("%d",&weight);
                if(temp <= G->nNumOfVertex && temp > v_i+1 && temp > 0)
                {
                    G->WeightedAdjacencyMatrix[v_i][temp-1] = weight;
                    G->WeightedAdjacencyMatrix[temp-1][v_i] = weight;
                    G->Predecessor[v_i][temp-1] = v_i+1;
                    G->Predecessor[temp-1][v_i] = temp;
                }
                else
                {
                    if(temp >= v_i+1)
                        printf("\nVertex you entered is greater than or equal to current Vertex.TRY AGAIN\n");
                    else
                        printf("\nThe Vertex you entered does not exist\nTry again\n");
                    j--;
                }
            }
        }
        else
        {
            printf("\nError:Number of Adjacent Vertices cannot be negative");
            v_i--;
        }
        G->WeightedAdjacencyMatrix[v_i][v_i]=0;              //initalising diagonal elements
    }
}

void FloydWarshall(Graphptr G)
{
    int v_k,v_i,v_j;
    CopyMatrix(G->WeightedAdjacencyMatrix,G->Dist,G->nNumOfVertex);
    for(v_k = 0;v_k < G->nNumOfVertex;v_k++)
    {
        for(v_i = 0;v_i < G->nNumOfVertex;v_i++)
        {
            for(v_j = 0;v_j < G->nNumOfVertex;v_j++)
            {
                if(G->Dist[v_i][v_j] > (G->Dist[v_i][v_k] + G->Dist[v_k][v_j]))
                {
                    G->Dist[v_i][v_j] = (G->Dist[v_i][v_k] + G->Dist[v_k][v_j]);
                    G->Predecessor[v_i][v_j] = G->Predecessor[v_k][v_j];
                }
            }
        }
    }
}
void CopyMatrix(int Source[MAX][MAX],int Destination[MAX][MAX],int Upperlimit)
{
    int i,j;
    for(i = 0;i < Upperlimit;i++)
    {
        for(j = 0;j < Upperlimit;j++)
        {
            Destination[i][j] = Source[i][j];
        }
    }
}


//prints output
void PrintResult(Graphptr G)
{
    int v_i,v_j;
    for(v_i = 0;v_i < G->nNumOfVertex;v_i++)
    {
        for(v_j = 0;v_j < G->nNumOfVertex;v_j++)
        {
            if(G->Predecessor[v_i][v_j] != NIL)
                printf("\n\t (%d,%d):-\tDistance = %d\tPredecessor = %d\n",v_i+1,v_j+1,G->Dist[v_i][v_j],G->Predecessor[v_i][v_j]);
            else
            {
                if(v_i!=v_j)
                    printf("\nPath between %d and %d Not Found\n",v_i+1,v_j+1);
            }
        }
    }
}
