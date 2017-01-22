/* LAST CHANGED : 20-09-2016
 * AUTHOR : LIBIN N GEORGE
 * Program to convert a given infix expression to its corresponding expression tree */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<string.h>

#define LEFT_ASSOCIATIVITY -1
#define RIGHT_ASSOCIATIVITY 1
struct StackNode
{
    char Operator;
    struct StackNode* next;
};

typedef struct StackNode* StackPointer;
struct Node                     //structure for tree
{
    char Token[10];
    struct Node *Left;
    struct Node *Right;
};
typedef struct Node* Nodepointer;
struct StackTwo               //structure for Stack
{
    struct Node *leafnode;
    struct StackTwo* next;
};
typedef struct StackTwo* StackTwoPointer;

void clearArray(char Mat[10][128]);
void print(char Mat[10][128]);
void PrintTree(int line,int nStart,int nEnd,Nodepointer TopNode,char Mat[10][128]);
struct oper
{
    int Precedence;
    int associative;
};
StackTwoPointer PopStack(StackTwoPointer Top);
StackPointer Push(char c, StackPointer PrevTop);  //push the value to the stack
StackPointer Pop(StackPointer Top);             //delete the top StackNode
struct oper Property(char op);
StackPointer OperatorManage(char Token[] , StackPointer TopStack, StackTwoPointer *Top);
StackPointer Manageclosing(StackPointer TopStack,StackTwoPointer *Top);
Nodepointer ManageEnd(StackPointer TopStack, StackTwoPointer *Top);
Nodepointer ConvertToTree(char Infix[]);
int main(void)
{
    char Infix[100],Mat[10][128];
    Nodepointer Root=NULL;
    printf("Enter InFix Expression(Only Positive Numbers):");
    scanf("%[^\n]s",Infix);
    Root=ConvertToTree(Infix);
    clearArray(Mat);
    PrintTree(0,0,128,Root,Mat);
    print(Mat);
    return 0;
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

StackTwoPointer PushStack(Nodepointer c, StackTwoPointer PrevTop)
{
    StackTwoPointer Top;

    Top=(StackTwoPointer)malloc(sizeof (struct StackNode));
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

Nodepointer ConvertToTree(char Infix[])
{
    StackPointer TopStack=NULL;
    int Stage=0,i=0,j=0;
    char Token[2],Num[10];
    Nodepointer LeafNode=NULL,TopNode=NULL;
    StackTwoPointer Top=NULL;
    while (1)
    {
        Token[0] = Infix[j++];
        Token[1] = '\0';
        if(Stage==0)
        {
            printf("The expression tree is:\n");
        }
        if (isdigit(Token[0]))                                                                                         //CASE OF DIGITS
        {
            if(Stage==0 || Stage==1 || Stage==2 || Stage==3)
            {
                Num[i++]=Token[0];
                Stage=1;
            }
        }
        else if ( Token[0]== '+' || Token[0]== '-' || Token[0]== '*' || Token[0]== '/' || Token[0]=='^')                           //CASE OF OPERATORS
        {

            if(Stage==1 || Stage==4)
            {
                if(Stage==1)
                {
                    Num[i++]='\0';
                    LeafNode=PushNode(Num,NULL,NULL);
                    Top=PushStack(LeafNode,Top);
                    i=0;
                }
               TopStack = OperatorManage(Token,TopStack,&Top);
               Stage=2;
            }
            else
            {
                printf("\nERROR : No 'operands'  or ')'  before operators\n");
                break;
            }
        }
        else if(Token[0]=='(')                                                                             //CASE OF '('
        {
            if(Stage==0 || Stage==2 || Stage==3)
            {
                TopStack=Push(Token[0],TopStack);
                Stage=3;
            }
            else
            {
                printf("\nERROR : Operands before (\n");
                break;
            }
        }
        else if (Token[0] == ')')                                                                        //CASE OF ')'
        {
            if(Stage==1 || Stage==4)
            {
                if(Stage==1)
                {
                    Num[i++]='\0';
                    LeafNode=PushNode(Num,NULL,NULL);
                    Top=PushStack(LeafNode,Top);
                    i=0;
                }
                TopStack = Manageclosing(TopStack,&Top);
                Stage=4;
            }
            else
            {
                printf("\nERROR : No operands before )\n");
                break;
            }
        }
        else if (Token[0] == '\0')                                                                 //CASE OF END OF INFIX NOTATION
        {
            if(Stage==1 || Stage==4)
            {
                if(Stage==1)
                {
                    Num[i++]='\0';
                    LeafNode=PushNode(Num,NULL,NULL);
                    Top=PushStack(LeafNode,Top);
                    i=0;
                }
                TopNode = ManageEnd(TopStack,&Top);
                break;
            }
            else
            {
                printf("\nERROR : No operands or ) in the end\n");
                break;
            }
        }
        else if (Token[0] == ' ');                                                                 //CASE OF SPACE
        else                                                                                    //CASE OF INVALID CHARECTOR
        {
            printf("ERROR:INVALID CHARACTER\n");
            break;
        }
    }
    return TopNode;
}

Nodepointer ManageEnd(StackPointer TopStack, StackTwoPointer *Top)
{
    Nodepointer TopNode=NULL;
    char TokenTree[2];
    TokenTree[1]='\0';
    while (TopStack!=NULL)
    {
        TokenTree[0]=TopStack->Operator;
        if(TopStack->Operator== '(')
        {
            printf("\nERROR : Mismatched parentheses Found\n");
            exit(1);
        }
        if ((*Top)!=NULL && (*Top)->next!=NULL)
        {
            TopNode=PushNode(TokenTree,(*Top)->next->leafnode,(*Top)->leafnode);
        }
        (*Top)=PopStack((*Top));
        (*Top)=PopStack((*Top));
        (*Top)=PushStack(TopNode,(*Top));
        TopStack=Pop(TopStack);
    }
    return TopNode;
}

StackPointer OperatorManage(char Token[] ,StackPointer TopStack,StackTwoPointer* Top)
{
    Nodepointer TopNode;
    struct oper O1,O2;
    char TokenTree[2];
    TokenTree[1]='\0';
    if(TopStack!=NULL)
    {
        while (TopStack->Operator != '(')
        {
            TokenTree[0]=TopStack->Operator;
            O1=Property(Token[0]);                   //token is o1
            O2=Property(TopStack->Operator);      //operator token o2, found at the top of the operator stack
            if((O1.Precedence <= O2.Precedence) && O1.associative == LEFT_ASSOCIATIVITY )
            {
                if ((*Top)!=NULL && (*Top)->next!=NULL)
                {
                    TopNode=PushNode(TokenTree,(*Top)->next->leafnode,(*Top)->leafnode);
                }
                (*Top)=PopStack((*Top));
                (*Top)=PopStack((*Top));
                (*Top)=PushStack(TopNode,(*Top));
                TopStack=Pop(TopStack);
            }
            else if ((O1.Precedence < O2.Precedence) && O1.associative == RIGHT_ASSOCIATIVITY)
            {
                if ((*Top)!=NULL && (*Top)->next!=NULL)
                {
                    TopNode=PushNode(TokenTree,(*Top)->next->leafnode,(*Top)->leafnode);
                }
                (*Top)=PopStack((*Top));
                (*Top)=PopStack((*Top));
                (*Top)=PushStack(TopNode,(*Top));
                TopStack=Pop(TopStack);
            }
            else
            {
                TopStack=Push(Token[0],TopStack);
                break;
            }
            if(TopStack==NULL)
            {
                TopStack=Push(Token[0],TopStack);
                break;
            }
        }
        if(TopStack->Operator=='(')
        {
            TopStack=Push(Token[0],TopStack);
        }
    }
    else
    {
        TopStack=Push(Token[0],TopStack);
    }
    return TopStack;
}
//delete the top StackNode
StackTwoPointer PopStack(StackTwoPointer Top)
{
    StackTwoPointer temp;
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
StackPointer Manageclosing(StackPointer TopStack,StackTwoPointer *Top)
{
    Nodepointer TopNode;
    char TokenTree[2];
    TokenTree[1]='\0';
    if(TopStack == NULL)
    {
        printf("\nERROR : mismatched parentheses found \n");
        exit(1);
    }
    while (TopStack->Operator!='(')
    {
        TokenTree[0]=TopStack->Operator;
        if ((*Top)!=NULL && (*Top)->next!=NULL)
        {
            TopNode=PushNode(TokenTree,(*Top)->next->leafnode,(*Top)->leafnode);
        }
        (*Top)=PopStack((*Top));
        (*Top)=PopStack((*Top));
        (*Top)=PushStack(TopNode,(*Top));
        TopStack=Pop(TopStack);
        if(TopStack==NULL)
        {
            printf("\nERROR : mismatched parentheses found \n");
            break;
        }
    }
    TopStack=Pop(TopStack);
    return TopStack;
}

StackPointer Push(char c, StackPointer PrevTop)
{
    StackPointer Top;
    if(PrevTop==NULL)
    {
        Top=(StackPointer)malloc(sizeof (struct StackNode));

        Top->Operator=c;
        Top->next=NULL;
        return Top;
    }
    else
    {
        Top=(StackPointer)malloc(sizeof (struct StackNode));
        Top->Operator=c;
        Top->next=PrevTop;
        return Top;
    }
}
//delete the top StackNode
StackPointer Pop(StackPointer Top)
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
        printf("ERROR:Stack EMPTY\n");
        exit(1);
        return Top;
    }

}
//function to assign Precidence and associativity
struct oper Property(char op)
{
    struct oper value;
    switch (op)
    {
    case '+':
        value.Precedence=2;
        value.associative=LEFT_ASSOCIATIVITY;
        break;
    case '-':
        value.Precedence=2;
        value.associative=LEFT_ASSOCIATIVITY;
        break;
    case '*':
        value.Precedence=3;
        value.associative=LEFT_ASSOCIATIVITY;
        break;
    case '/':
        value.Precedence=3;
        value.associative=LEFT_ASSOCIATIVITY;
        break;
    case '^':
        value.Precedence=4;
        value.associative=RIGHT_ASSOCIATIVITY;
        break;
    default:
        break;
    }
    return value;
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
