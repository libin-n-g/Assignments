#include <stdio.h>
#define INF -1
struct Vertex
{
    int VertexNo;
    int List[50][2];
};

void CreateLinkedList(struct Vertex V[50],int NoOfNeibours,int index);
void AddToList(int );
int main(void)
{
    struct Vertex V[50];
    int i,NoOfVertex,NoOfNeibours;
    printf("Enter the Number Of Vertices:\n");
    scanf("%d",&NoOfVertex);
    for(i=0;i<NoOfVertex;i++)
    {
        printf("Enter the number of Neibours of Node %d for which the neibours bigger than current Vertex\n",i);
        scanf("%d",&NoOfNeibours);
        CreateLinkedList(V[i].List,NoOfNeibours);
    }
    return 0;
}
void CreateLinkedList(Vertex V[], int NoOfNeibours, int index)
{
    int i,weight,neibour;
    for(i=0;i<NoOfNeibours;i++)
    {
        printf("Enter the Adjacent Vertex followed by its weight");
        scanf("%d %d",&neibour,&weight);
        if(neibour<=index)
        {
            printf("Please Enter The Neibouring Vertex having biggeer index than currentVertex\nTRY AGAIN/n");
            NoOfNeibours--;
        }
        else
        {
            AddToList()
        }

    }
}
