/* LAST CHANGED : 28-08-2016
 * AUTHOR : LIBIN N GEORGE
 * Implement a binary search tree data structure having insertion,deletion,search and transverse*/
#include <stdio.h>
#include<stdlib.h>

struct TreeNode
{
    int Num;
    struct TreeNode* Left;
    struct TreeNode* Right;
};

typedef struct TreeNode* NodePointer;

NodePointer Insert(int Num ,NodePointer Root);
NodePointer BinarySearch(int Num, NodePointer Root);
NodePointer Push(int Num,NodePointer left,NodePointer Right);
NodePointer DeleteElement(int Num,NodePointer Root);
NodePointer LeftMostElement(NodePointer Element);
void Transverse(NodePointer Root);
void PreorderTransverse(NodePointer Root);
void InorderTransverse(NodePointer Root);
void PostorderTransverse(NodePointer Root);

int main(void)
{
    int Num,op=1;
    NodePointer Root=NULL;
    while(op!=0)
    {
        printf("\nEnter the option you what to do \nInsertion=1\nSearch=2\nDeletion=3\nTransverse=4\nExit=0\n");
        scanf("%d",&op);
        switch(op)
        {
        case 0:
            break;
        case 1:
            printf("\nEnter the Number you want to insert:\n");
            scanf("%d",&Num);
            Root=Insert(Num,Root);
            break;
        case 2:
            printf("\nEnter the Number you want to search:\n");
            scanf("%d",&Num);
            BinarySearch(Num,Root);
            break;
        case 3:
            printf("\nEnter element to delete\n");
            scanf("%d",&Num);
            if(BinarySearch(Num,Root)!=NULL)
            {
                Root=DeleteElement(Num,Root);
                printf("\nElement is deleted\n");
            }
            else
                printf("\nElement is not deleted\n");
            break;
        case 4:
            Transverse(Root);
            break;
        default:
            printf("\nEnter valid option\n");
            break;
        }
    }
    return 0;
}
//function for inserting the new number to the tree
NodePointer Insert(int Num ,NodePointer Root)
{
    if(Root==NULL)
    {
        Root=Push(Num,NULL,NULL);
        if(Root==NULL)
            exit(1);
    }
    else if(Num<Root->Num)
    {
        Root->Left=Insert(Num,Root->Left);
    }
    else
    {
        Root->Right=Insert(Num,Root->Right);
    }
    return Root;
}
//function for searching
NodePointer BinarySearch(int Num,NodePointer Root)
{
    if(Root!=NULL)
    {
        if(Num < Root->Num)
        {
            return BinarySearch(Num,Root->Left);
        }
        else if(Num == Root->Num)
        {
            printf("\n%d IS FOUND\n",Num);
            return Root;

        }
        else
        {
            return BinarySearch(Num,Root->Right);
        }
    }
    printf("\n%d NOT FOUND\n",Num);
    return NULL;
}
//function to add an element to tree
NodePointer Push(int Num,NodePointer left,NodePointer Right)
{
    NodePointer Root;
    Root=(NodePointer)malloc(sizeof (struct TreeNode));
    if(Root!=NULL)
    {
        Root->Num=Num;
        Root->Left=left;
        Root->Right=Right;
        return Root;
    }
    else
    {
        printf("\nERROR:memory allocation failed\n");
        return NULL;
    }
}
//function to delete element
NodePointer DeleteElement(int Num,NodePointer Root)
{
    NodePointer SuccessorNode=NULL,Element=NULL;
    if(Num<Root->Num)
    {
        Root->Left=DeleteElement(Num,Root->Left);
    }
    else if(Num>Root->Num)
    {
        Root->Right=DeleteElement(Num,Root->Right);
    }
    else
    {
        if(Root->Left==NULL)                    //case of No Child and one child
        {
            Element=Root->Right;    //Root->Right=NULL in case of No child
            free(Root);
            return Element;
        }
        else if(Root->Right==NULL)   //case of one child
        {
            Element=Root->Left;
            free(Root);
            return Element;
        }
        else        //case of two child
        {
            SuccessorNode=LeftMostElement(Root->Right);
            Root->Num=SuccessorNode->Num;
            Root->Right=DeleteElement(SuccessorNode->Num,Root->Right);
        }
    }
    return Root;
}
//find Sucessur node to replce the node to be deleted
NodePointer LeftMostElement(NodePointer Element)
{
    if(Element->Left == NULL)
    {
        return Element;
    }
    else
    {
        return LeftMostElement(Element->Left);
    }
}
//functions for finding transverse
void Transverse(NodePointer Root)
{
    int op=1;
    if(Root==NULL)
    {
        printf("\nNo element in the tree\n");
        return ;
    }
    while (op)
    {
        printf("\nEnter the option you want to do\n1-->Pre-order\n2-->In-order\n3-->Post-order\n");
        scanf("%d",&op);
        printf("\n");
        switch (op)
        {
        case 1:
            PreorderTransverse(Root);
            op=0;
            break;
        case 2:
            InorderTransverse(Root);
            op=0;
            break;
        case 3:
            PostorderTransverse(Root);
            op=0;
            break;
        default:
            printf("\nPlease Enter Valid option\n");
            op=1;
            break;
        }
    }
}
//function for printing Preorder transverse
void PreorderTransverse(NodePointer Root)
{
    if(Root!=NULL)
    {
        printf("%d\t",Root->Num);
        PreorderTransverse(Root->Left);
        PreorderTransverse(Root->Right);
    }
}
//function for printing Inorder transverse
void InorderTransverse(NodePointer Root)
{
    if(Root!=NULL)
    {
        InorderTransverse(Root->Left);
        printf("%d\t",Root->Num);
        InorderTransverse(Root->Right);
    }
}
//function for printing Postorder transverse
void PostorderTransverse(NodePointer Root)
{
    if(Root!=NULL)
    {
        PostorderTransverse(Root->Left);
        PostorderTransverse(Root->Right);
        printf("%d\t",Root->Num);
    }
}
