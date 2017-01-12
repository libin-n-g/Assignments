/* DATE : 15-08-2016
 * AUTHOR : LIBIN N GEORGE
 * Linked List with function to Reverse the order of Linked List(Recursive)*/

#include<stdio.h>
#include<stdlib.h>

struct node
{
    int nValue;
    struct node* Next;
};

typedef struct node* nodeptr;

nodeptr CreateNode(int nValue);
nodeptr DeleteNode(nodeptr);
void Print(nodeptr);
nodeptr ReverseList(nodeptr,nodeptr);

int main(void)
{
    nodeptr prev ,Tail=NULL,Head=NULL;
    int op=0,nValue;


    while(op!=5)
    {
        printf("1->insertion\n2->deletion\n3->printing\n4->Reverse linked list\n5->exit\nEnter the operation no you want to do:");
        scanf("%d",&op);
        switch(op)
        {
            case 1:
                printf("enter the value you want insert to queue");
                scanf("%d",&nValue);
                if(Tail!=NULL)
                {
                    prev=Tail;
                    Tail=CreateNode(nValue);
                    prev->Next=Tail;
                }
                else
                {
                    Tail=CreateNode(nValue);
                    Head=Tail;
                }
                break;
            case 2:
                Head=DeleteNode(Head);
                if(Head==NULL)
                    Tail=NULL;
                break;
            case 3:
                Print(Head);
                break;
            case 4:
                Head=ReverseList(Head,NULL);
                break;
            case 5:
                break;
            default:
                printf("ERROR:ENTER VALID OPTION\n");
                break;
        }
    }
    return 0;
}
//create Node and stores value
nodeptr CreateNode(int nValue)
{
    nodeptr p=NULL;
    p=(nodeptr)malloc(sizeof(struct node));
    if(p!=NULL)
    {
        p->nValue=nValue;
        p->Next=NULL;
        return p;
    }
    else
    {
        printf("ERROR:NO NODE CREATED\n");
        return NULL;
    }
}
//delates node at head position
nodeptr DeleteNode(nodeptr Head)
{
    nodeptr newHead;
    if(Head!=NULL)
    {
        newHead=Head->Next;
        printf("the element %d is deleted\n",Head->nValue);
        free(Head);
        return newHead;
    }
    else
    {
        puts("No element found to delete");
        return NULL;
    }
}
//print linked list
void Print(nodeptr Head)
{
    nodeptr nod;
    nod=Head;
    if(nod==NULL)
    {
        puts("ERROR:no elemets to Print");
    }
    else
    {
    while(nod!=NULL)
    {
        printf("%d\n",nod->nValue);
        nod=nod->Next;
    }
    }
}
// Reverse the order of Linked List by Recursion
nodeptr ReverseList(nodeptr Head,nodeptr prev)
{
    nodeptr Next;
    if(Head!=NULL)
    {
        Next=Head->Next;
        Head->Next=prev;
        prev=ReverseList(Next,Head);
    }

    return prev;
}
