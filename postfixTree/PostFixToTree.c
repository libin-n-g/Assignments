/* LAST CHANGED : 20-09-2016
 * AUTHOR : LIBIN N GEORGE
 *  Convert a given postfix expression to its corresponding expression tree*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<string.h>

struct Node                     //structure for tree
{
    char Token[10];
    struct Node *Left;
    struct Node *Right;
};
typedef struct Node* Nodepointer;

struct StackNode                //structure for Stack
{
    struct Node *leafnode;
    struct StackNode* next;
};
typedef struct StackNode* StackPointer;

Nodepointer PushNode(char c[], Nodepointer Leftnode, Nodepointer Rightnode);
StackPointer PushStack(Nodepointer c, StackPointer PrevTop);  //push the value to the stack
StackPointer PopStack(StackPointer Top);             //delete the top StackNode
void PrintTree(int i,int j,int length,Nodepointer TopNode,char Mat[10][128]);
void clearArray(char Mat[10][128]);
void print(char Mat[10][128]);

int main(void)
{
    char PostFix[100],Token[2],Mat[10][128],Num[10];
    int i=0,j=0;
    StackPointer Top=NULL;
    Nodepointer TopNode=NULL,Nodeleaf=NULL;
    printf("Enter PostFix Notation\n");
    scanf("%[^\n]s",PostFix);
    clearArray(Mat);
    while (1)
    {
        Token[0]=PostFix[j++];
        Token[1]='\0';
        if(Token[0] == ' ')
        {
            if(i>0)                 //i=0 is a case of invalid number(space not after number)
            {
                Num[i++]='\0';
                Nodeleaf=PushNode(Num,NULL,NULL);
                Top=PushStack(Nodeleaf,Top);
                i=0;
            }
        }
        else if (isdigit(Token[0]))
        {
            Num[i++]=Token[0];//each digit entered is added into the array
        }
        else if ( Token[0] == '+' || Token[0] == '-' || Token[0] == '*' || Token[0] == '/' || Token[0] == '^' )
        {
            if (Top!=NULL && Top->next!=NULL)
            {
                TopNode=PushNode(Token,Top->next->leafnode,Top->leafnode);
            }
            Top=PopStack(Top);
            Top=PopStack(Top);
            Top=PushStack(TopNode,Top);
        }
        else if (Token[0] == '\0')
        {
             break;
        }
        else
        {
            printf("\nERROR:INVALID CHARACTER\n");
            break;
        }
    }
    if(i!=0 || isdigit(Top->leafnode->Token[0]))
        printf("ERROR : NO OPERATOR\n");
    free(Top);
    PrintTree(0,0,100,TopNode,Mat);
    print(Mat);
    return 0;
}

//push the value to the stack
StackPointer PushStack(Nodepointer c, StackPointer PrevTop)
{
    StackPointer Top;

    Top=(StackPointer)malloc(sizeof (struct StackNode));
    if(Top!=NULL)
    {
        Top->leafnode=c;
        Top->next=PrevTop;
        return Top;
    }
    else
    {
        printf("ERROR!\n");
        exit(1);
        return NULL;
    }
}
//delete the top StackNode
StackPointer PopStack(StackPointer Top)
{
    StackPointer temp;
    if(Top!=NULL)
    {
        temp=Top;
        Top=Top->next;
        free(temp);
        return Top;
    }
    else
    {
        printf("ERROR:Stack EMPTY: Operands for operations Not Found\n");
        exit(1);
        return Top;
    }
}
//create nodes having left and right childs
Nodepointer PushNode(char c[], Nodepointer Leftnode,Nodepointer Rightnode)
{
    Nodepointer Top=NULL;

    Top=(Nodepointer)malloc(sizeof (struct Node));
    if(Top!=NULL)
    {               
        strcpy(Top->Token,c);
        Top->Left = Leftnode;
        Top->Right = Rightnode;
        return Top;
    }
    else
    {
        printf("ERROR\n");
        exit(1);
        return Top;
    }

}
//printing Tokens in the Matrix
void PrintTree(int line,int nStart,int nEnd,Nodepointer TopNode,char Mat[10][128])
{
    int nMid,k,l;
    nMid=(nEnd+nStart)/2;
    if(TopNode!=NULL)
    {
        for(l=nStart;l<nEnd;l++)
        {
            if(l==nMid)
            {
                for(k=0;TopNode->Token[k]!='\0';k++,l++)
                {
                     Mat[line][l]=TopNode->Token[k];
                }
            }
        }
        PrintTree(line+1,nStart,nMid,TopNode->Left,Mat);
        PrintTree(line+1,nMid,nEnd,TopNode->Right,Mat);
    }
}
//print whole matrix
void print(char Mat[10][128])
{
    int i,j;
    for(i=0;i<10;i++)
    {
        for(j=0;j<128;j++)
        {
            printf("%c",Mat[i][j]);
        }
        printf("\n");
    }
}
//clear the whole array
void clearArray(char Mat[10][128])
{
    int i,j;
    for(i=0;i<10;i++)
    {
        for(j=0;j<128;j++)
        {
            Mat[i][j]=' ';
        }
    }
}
