
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

void DeleteKey(Nodeptr x,int k);
int FindPredecessorAndDelete(Nodeptr x);
int FindSuccessorAndDelete(Nodeptr x);
int main(void)
{
    return 0;
}
void Search(Nodeptr x,int k)
{
    int i=1;
    while ((i <= x->NumOfKeys) && (k > x->Keys[i-1]))
    {
        i++;
    }
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
        printf("\t%d",x->Keys[i-1]);
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
    x->Keys[i-1] = x->Keys[MinDegree-1];
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
void DeleteKey(Nodeptr x,int k)
{
    int i=1,j;
    while ((i <= x->NumOfKeys) && (k > x->Keys[i-1]))
    {
        i++;
    }
    if((i <= x->NumOfKeys) && (k == x->Keys[i-1]))
    {
        if(x->ISLeaf)
        {
            ////Delete Key CASE 1
            for(j = (i-1);j < (x->NumOfKeys-1);j++)
            {
                x->Keys[j]=x->Keys[j+1];
            }
            x->NumOfKeys = x->NumOfKeys-1;
            x->Keys[x->NumOfKeys] = 0;
        }
        else
        {
            /////CASE 2
            Nodeptr PrevChildToKeyK = x->chlidren[i-1];
            Nodeptr NextChildToKeyK = x->chlidren[i];
            /// case 2a
            if(PrevChildToKeyK->NumOfKeys > (MinDegree-1))
            {
                x->Keys[i-1] = FindPredecessorAndDelete(PrevChildToKeyK); //Finding Predecessor
            }
            /// case 2b
            else if(NextChildToKeyK->NumOfKeys > (MinDegree-1))
            {
                x->Keys[i-1] = FindSuccessorAndDelete(NextChildToKeyK);//finding successor
            }
            /// case 2c
            else
            {/////////////////////Merging
                PrevChildToKeyK->Keys[PrevChildToKeyK->NumOfKeys] = k;
                PrevChildToKeyK->chlidren[PrevChildToKeyK->NumOfKeys + 1] = NextChildToKeyK->chlidren[0];
                PrevChildToKeyK->NumOfKeys++;
                for(j = 0;j < NextChildToKeyK->NumOfKeys;j++)
                {
                    PrevChildToKeyK->Keys[j+PrevChildToKeyK->NumOfKeys] = NextChildToKeyK->Keys[j];
                    PrevChildToKeyK->chlidren[j + PrevChildToKeyK->NumOfKeys + 1] = NextChildToKeyK->chlidren[j+1];
                }
                PrevChildToKeyK->NumOfKeys = PrevChildToKeyK->NumOfKeys + NextChildToKeyK->NumOfKeys;
                //deleting key k from node x and child after key k
                free(x->chlidren[i]);///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                for(j = i;j < x->NumOfKeys;j++)
                {
                    x->Keys[j-1] = x->Keys[j];
                    x->chlidren[j] = x->chlidren[j+1];
                }
                x->Keys[x->NumOfKeys-1] = 0;
                x->NumOfKeys--;
                DeleteKey(PrevChildToKeyK,k);
            }
        }
    }
    else if (x->ISLeaf)
    {
        printf("\nkey %d Not Found\n",k);
    }
    else
    {
        ////////////// CASE 3    x->chlidren[i-1]
        if(x->chlidren[i-1]->NumOfKeys > (MinDegree-1))
        {
            DeleteKey(x->chlidren[i-1],k);
        }
        else
        {
            Nodeptr RightSibling,LeftSibling,Expectedsubtree;
            Expectedsubtree = x->chlidren[i-1];
            if(i >= 2)
            {
                LeftSibling = x->chlidren[i-2];
                if(i <= x->NumOfKeys)
                {
                    RightSibling = x->chlidren[i];
                    ///case 3a
                    if(RightSibling->NumOfKeys > (MinDegree-1))
                    {
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
                    else if(LeftSibling->NumOfKeys > (MinDegree-1))
                    {
                        //////////
                        for(j = Expectedsubtree->NumOfKeys;j > 0;j--)
                        {
                            Expectedsubtree->Keys[j] = Expectedsubtree->Keys[j-1];
                            Expectedsubtree->chlidren[j+1] = Expectedsubtree->chlidren[j];
                        }
                        Expectedsubtree->chlidren[1] = Expectedsubtree->chlidren[0];
                        ///////////////////
                        Expectedsubtree->Keys[0] = x->Keys[i-2];
                        Expectedsubtree->NumOfKeys++;
                        Expectedsubtree->chlidren[0] = LeftSibling->chlidren[LeftSibling->NumOfKeys];
                        x->Keys[i-2] = LeftSibling->Keys[LeftSibling->NumOfKeys-1];
                        LeftSibling->Keys[LeftSibling->NumOfKeys-1] = 0;
                        LeftSibling->NumOfKeys--;
                    }
                    ///case 3b
                    else
                    {
                            ///////////////Merging
                            ///
                    }
                }
                else
                {
                    if(LeftSibling->NumOfKeys > (MinDegree-1))
                    {

                    }
                    ///case 3b
                    else
                    {

                    }
                }
            }
            else if(i <= x->NumOfKeys)
            {

                RightSibling = x->chlidren[i];
                ///case 3a
                if(RightSibling->NumOfKeys > (MinDegree-1))
                {

                }
                ///case 3b
                else
                {

                }
            }
        }
    }
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
        return FindPredecessorAndDelete(x->chlidren[x->NumOfKeys]);
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
        return FindSuccessorAndDelete(x->chlidren[0]);
    }
}
