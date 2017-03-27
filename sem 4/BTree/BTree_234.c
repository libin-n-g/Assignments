/* AUTHOR : LIBIN N GEORGE
 * LAST CHANGED:27-3-2017
 * Program Implementing a 2-3-4 tree with search, insert, delete operations.
 * Initially Program asks for the number of elements to be inserted and make a B-Tree
 * by inserting these elements one by one.
 * After this four choices are given ,  1=>insert, 2=>search, 3=>delete, 4=>exit.
 * When a search is done, Program displays all the elements in the path traced from the root of the tree to the searched key
*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define MinDegree 2

struct Node
{
    bool ISLeaf;
    int NumOfKeys;
    int Keys[(2*MinDegree)-1];
    struct Node *chlidren[2*MinDegree];
};
typedef struct Node* Nodeptr;
Nodeptr CreateLeafNode();

///FUNCTIONS FOR INSERT
Nodeptr Insert(Nodeptr x, int k);
void InsertNonFull(Nodeptr x,int k);
void SplitChild(Nodeptr x,int i);

void Search(Nodeptr x,int k);

///FUNCTIONS FOR DELETE
Nodeptr DeleteKey(Nodeptr x,int k);
int FindPredecessorAndDelete(Nodeptr x);
int FindSuccessorAndDelete(Nodeptr x);
void Mergewithkeyk(Nodeptr y,int k, Nodeptr z,Nodeptr Root,int iKey);
void RestructuringwithRightSibling(Nodeptr Expectedsubtree,Nodeptr RightSibling,Nodeptr x,int i);
void RestructuringwithLeftSibling(Nodeptr Expectedsubtree,Nodeptr LeftSibling,Nodeptr x,int i);
void DeleteFromInternalNode(Nodeptr x, int k, int i);
Nodeptr RestructuringChildToDelete(Nodeptr x,int i);
int main(void)
{
    int InputKey=1,Key,n,i;
    Nodeptr Root;
    Root = CreateLeafNode();
    printf("\nEnter the Number of elements to be inserted to 2-3-4 Tree\n");
    scanf("%d",&n);
    printf("\nEnter %d keys to be inserted\n",n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&Key);
        Root = Insert(Root,Key);
    }
    do
    {
        printf("\n 1.insert. \n 2.search. \n 3.delete.\n 4.exit.\nEnter valid Choices \n");
        scanf("%d",&InputKey);
        switch (InputKey) {
        case 1:
            printf("\nEnter Key To Insert\n");
            scanf("%d",&Key);
            Root = Insert(Root,Key);
            break;
        case 2:
            printf("\nEnter Key to search\n");
            scanf("%d",&Key);
            Search(Root,Key);
            break;
        case 3:
            printf("\nEnter Key to Delete\n ");
            scanf("%d",&Key);
            Root = DeleteKey(Root,Key);
            break;
        case 4:
            break;
        default:
            printf("\n InValid choice\n");
            break;
        }
    }while(InputKey != 4 );
    return 0;
}
void Search(Nodeptr x,int k)
{
    int i=1;
    printf("Entering Node\n");
    while ((i <= x->NumOfKeys) && (k > x->Keys[i-1]))
    {
        printf("\t%d",x->Keys[i-1]);
        i++;
    }
    printf("\n");
    if((i <= x->NumOfKeys) && (k == x->Keys[i-1]))
    {
        printf("\nKey %d Found\n",k);
    }
    else if (x->ISLeaf)
    {
        printf("\nkey %d Not Found\n",k);
    }
    else
    {
        Search(x->chlidren[i-1],k);
    }
}

Nodeptr CreateLeafNode()
{
    Nodeptr pLeaf=NULL;
    pLeaf = (Nodeptr)malloc(sizeof(struct Node));
    if(pLeaf!=NULL)
    {
        pLeaf->ISLeaf = true;
        pLeaf->NumOfKeys = 0;
    }
    else
    {
        printf("\nERROR : Memory Allocation Failed\n");
        exit(1);
    }
    return pLeaf;
}
Nodeptr Insert(Nodeptr Root,int k)
{
    Nodeptr NewRoot;
    if(Root->NumOfKeys == ((2*MinDegree)-1))
    {
        NewRoot = CreateLeafNode();
        NewRoot->ISLeaf = false;
        NewRoot->NumOfKeys = 0;
        NewRoot->chlidren[0] = Root;
        SplitChild(NewRoot,1);
        InsertNonFull(NewRoot,k);
        return NewRoot;
    }
    else
    {
        InsertNonFull(Root,k);
        return Root;
    }

}

void SplitChild(Nodeptr x,int i)
{
    int j;
    Nodeptr z;
    Nodeptr y = x->chlidren[i-1];
    z = CreateLeafNode();
    z->ISLeaf = y->ISLeaf;
    z->NumOfKeys = MinDegree - 1;
    for(j=0;j < MinDegree-1;j++)
    {
        z->Keys[j] = y->Keys[j + MinDegree];
    }
    if(!(y->ISLeaf))
    {
        for(j = 0;j < MinDegree;j++)
        {
            z->chlidren[j] = y->chlidren[j+MinDegree];
        }
    }
    y->NumOfKeys = MinDegree - 1;
    for(j = x->NumOfKeys;j > (i-1);j--)
    {
        x->chlidren[j+1]=x->chlidren[j];
    }
    x->chlidren[i] = z;
    for(j = x->NumOfKeys-1 ; j > (i-2) ; j-- )
    {
        x->Keys[j+1] = x->Keys[j];
    }
    x->Keys[i-1] = y->Keys[MinDegree-1];
    x->NumOfKeys = x->NumOfKeys + 1;
}
void InsertNonFull(Nodeptr x,int k)
{
    int i = x->NumOfKeys;
    if(x->ISLeaf)
    {
        while ((i > 0) && (k < x->Keys[i-1]))
        {
            x->Keys[i] = x->Keys[i-1];
            i--;
        }
        x->Keys[i] = k;
        x->NumOfKeys = x->NumOfKeys + 1;
    }
    else
    {
        while ((i > 0) && (k < x->Keys[i-1]))
        {
            i--;
        }
        i++;
        if(x->chlidren[i-1]->NumOfKeys == ((2*MinDegree)-1))
        {
            SplitChild(x,i);
            if(k > x->Keys[i-1])
            {
                i++;
            }
        }
        InsertNonFull(x->chlidren[i-1],k);
    }
}
Nodeptr DeleteKey(Nodeptr x,int k)
{
    Nodeptr temp;
    int i=1,j;
    while ((i <= x->NumOfKeys) && (k > x->Keys[i-1]))
    {
        i++;
    }
    if((i <= x->NumOfKeys) && (k == x->Keys[i-1]))
    {
        if(x->ISLeaf)
        {           
            for(j = (i-1);j < (x->NumOfKeys-1);j++)////Delete Key CASE 1
            {
                x->Keys[j]=x->Keys[j+1];
            }
            x->NumOfKeys = x->NumOfKeys-1;
            x->Keys[x->NumOfKeys] = 0;
        }
        else             /////CASE 2
        {            
            DeleteFromInternalNode(x,k,i);
        }
    }
    else if (x->ISLeaf)
    {
        printf("\nkey %d Not Found\n",k);
    }
    else
    {        
        if(x->chlidren[i-1]->NumOfKeys > (MinDegree-1))////////////// CASE 3
        {
            DeleteKey(x->chlidren[i-1],k);
        }
        else
        {
            Nodeptr Expectedsubtree;
            Expectedsubtree = RestructuringChildToDelete(x,i);
            DeleteKey(Expectedsubtree,k);
        }
    }
    if(x->NumOfKeys == 0)
    {
        temp = x->chlidren[0];
        free(x);
        return temp;
    }
    else
        return x;
}


int FindPredecessorAndDelete(Nodeptr x)
{
    int k;
    if(x->ISLeaf)
    {
        k = x->Keys[x->NumOfKeys-1];
        DeleteKey(x,k);
        return k;
    }
    else
    {
        if(x->chlidren[x->NumOfKeys]->NumOfKeys > (MinDegree-1))
        {
            return FindPredecessorAndDelete(x->chlidren[x->NumOfKeys]);
        }
        else
        {
            return FindPredecessorAndDelete(RestructuringChildToDelete(x,(x->NumOfKeys)+1));
        }
    }
}
int FindSuccessorAndDelete(Nodeptr x)
{
    int k;
    if(x->ISLeaf)
    {
        k = x->Keys[0];
        DeleteKey(x,k);
        return k;
    }
    else
    {
        if(x->chlidren[0]->NumOfKeys > (MinDegree-1))
            return FindSuccessorAndDelete(x->chlidren[0]);
        else
        {
            return FindSuccessorAndDelete(RestructuringChildToDelete(x,1));
        }
    }
}
void Mergewithkeyk(Nodeptr y,int k, Nodeptr z,Nodeptr Root,int iKey)
{
    int j;
    y->Keys[y->NumOfKeys] = k;
    y->chlidren[y->NumOfKeys + 1] = z->chlidren[0];
    y->NumOfKeys++;
    for(j = 0;j < z->NumOfKeys;j++)
    {
        y->Keys[j+y->NumOfKeys] = z->Keys[j];
        y->chlidren[j + y->NumOfKeys + 1] = z->chlidren[j+1];
    }
    y->NumOfKeys = y->NumOfKeys + z->NumOfKeys;
    free(Root->chlidren[iKey]);/////////////////////////////////////////
    for(j = iKey;j < Root->NumOfKeys;j++)
    {
        Root->Keys[j-1] = Root->Keys[j];
        Root->chlidren[j] = Root->chlidren[j+1];
    }
    Root->Keys[Root->NumOfKeys-1] = 0;
    Root->NumOfKeys--;
}
void RestructuringwithRightSibling(Nodeptr Expectedsubtree,Nodeptr RightSibling,Nodeptr x,int i)
{
    int j;
    Expectedsubtree->Keys[Expectedsubtree->NumOfKeys] = x->Keys[i-1];
    Expectedsubtree->NumOfKeys++;
    Expectedsubtree->chlidren[Expectedsubtree->NumOfKeys] = RightSibling->chlidren[0];
    x->Keys[i-1] = RightSibling->Keys[0];
    for(j=0;j < RightSibling->NumOfKeys;j++)
    {
        RightSibling->Keys[j] = RightSibling->Keys[j+1];
        RightSibling->Keys[j+1] = 0;
        RightSibling->chlidren[j] = RightSibling->chlidren[j+1];
    }
    RightSibling->NumOfKeys--;
}
void RestructuringwithLeftSibling(Nodeptr Expectedsubtree,Nodeptr LeftSibling,Nodeptr x,int i)
{
    int j;
    for(j = Expectedsubtree->NumOfKeys;j > 0;j--)
    {
        Expectedsubtree->Keys[j] = Expectedsubtree->Keys[j-1];
        Expectedsubtree->chlidren[j+1] = Expectedsubtree->chlidren[j];
    }
    Expectedsubtree->chlidren[1] = Expectedsubtree->chlidren[0];/////
    Expectedsubtree->Keys[0] = x->Keys[i-2];
    Expectedsubtree->NumOfKeys++;
    Expectedsubtree->chlidren[0] = LeftSibling->chlidren[LeftSibling->NumOfKeys];
    x->Keys[i-2] = LeftSibling->Keys[LeftSibling->NumOfKeys-1];
    LeftSibling->Keys[LeftSibling->NumOfKeys-1] = 0;
    LeftSibling->NumOfKeys--;
}
void DeleteFromInternalNode(Nodeptr x, int k, int i)
{
    Nodeptr PrevChildToKeyK = x->chlidren[i-1];
    Nodeptr NextChildToKeyK = x->chlidren[i];
    if(PrevChildToKeyK->NumOfKeys > (MinDegree-1))                      /// case 2a
    {
        x->Keys[i-1] = FindPredecessorAndDelete(PrevChildToKeyK); //Finding Predecessor
    }
    else if(NextChildToKeyK->NumOfKeys > (MinDegree-1))            /// case 2b
    {
        x->Keys[i-1] = FindSuccessorAndDelete(NextChildToKeyK);//finding successor
    }
    else/// case 2c
    {
        Mergewithkeyk(PrevChildToKeyK,k,NextChildToKeyK,x,i);   /////Merging             //deleting key k from node x and child after key k
        DeleteKey(PrevChildToKeyK,k);
    }
}
Nodeptr RestructuringChildToDelete(Nodeptr x,int i)
{
    Nodeptr Tempptr,RightSibling,LeftSibling,Expectedsubtree;
    Tempptr = CreateLeafNode();
    RightSibling = Tempptr;
    LeftSibling = Tempptr;
    Expectedsubtree = x->chlidren[i-1];
    if(i >= 2 )                                             ///Left sibling exists
    {
        LeftSibling = x->chlidren[i-2];
    }
    if(i <= x->NumOfKeys)                                   ////Right sibling exists
    {
        RightSibling = x->chlidren[i];
    }
    if(RightSibling->NumOfKeys > (MinDegree-1))             ///case 3a
    {
        RestructuringwithRightSibling(Expectedsubtree,RightSibling,x,i);
    }
    else if(LeftSibling->NumOfKeys > (MinDegree-1))
    {
        RestructuringwithLeftSibling(Expectedsubtree,LeftSibling,x,i);
    }
    else                                                     ///case 3b
    {
        if(RightSibling->NumOfKeys != 0)
        {
            Mergewithkeyk(Expectedsubtree,x->Keys[i-1],RightSibling,x,i);///Merging
        }
        else
        {
            Mergewithkeyk(LeftSibling,x->Keys[i-2],Expectedsubtree,x,i-1);
            return LeftSibling;
        }
    }
    free(Tempptr);
    return Expectedsubtree;
}
