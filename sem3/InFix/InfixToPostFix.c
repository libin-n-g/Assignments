/* LAST CHANGED : 13-09-2016
 * AUTHOR : LIBIN N GEORGE
 *  Shunting-yard algorithm to convert Infix notation to Postfix notetion */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define LEFT_ASSOCIATIVITY -1
#define RIGHT_ASSOCIATIVITY 1

struct StackNode
{
    char Operator;
    struct StackNode* next;
};

typedef struct StackNode* StackPointer;
struct oper
{
    int Precedence;
    int associative;
};

StackPointer Push(char c, StackPointer PrevTop);  //push the value to the stack
StackPointer Pop(StackPointer Top);             //delete the top StackNode
struct oper Property(char op);
StackPointer ManageToken(StackPointer TopStack, int Stage, char Token, char PostFix[], int *i);
StackPointer ManageEnd(StackPointer TopStack,int Stage,char PostFix[],int *i);
StackPointer ManageCloseingParanthesis(StackPointer TopStack,int Stage,char PostFix[],int *i);
void InfixToPostFix(char Infix[100],char PostFix[100]);
int main(void)
{
    char PostFix[100],Infix[100];
    printf("Enter InFix Expression(Only Positive Numbers and space will not be counted):\n");
    scanf("%[^\n]s",Infix);
    InfixToPostFix(Infix,PostFix);
    printf("%s\n",PostFix);
    return 0;
}
void InfixToPostFix(char Infix[100],char PostFix[100])
{
    StackPointer TopStack=NULL;
    int Stage=0,i=0,j=0;
    char Token;
    while (1)
    {
        Token = Infix[j++];
        if(Stage==0)
        {
            printf("The postFix expression  is:\n");
        }
        if (isdigit(Token))                                                                                         //CASE OF DIGITS
        {
            if(Stage==0 || Stage==1 || Stage==2 || Stage==3)
            {
                PostFix[i++]=Token;
                Stage=1;
            }
        }
        else if ( Token== '+' || Token== '-' || Token== '*' || Token== '/' || Token=='^')                           //CASE OF OPERATORS
        {
            if(Stage==1 || Stage==4)
            {
                TopStack=ManageToken(TopStack,Stage,Token,PostFix,&i);
                Stage=2;
            }
            else
            {
                printf("\nERROR : No 'operands'  or ')'  before operators\n");break;
            }
        }
        else if(Token=='(')                                                                             //CASE OF '('
        {
            if(Stage==0 || Stage==2 || Stage==3)
            {
                TopStack=Push(Token,TopStack);
                Stage=3;
            }
            else
            {
                printf("\nERROR : Operands before (\n");
                break;
            }
        }
        else if (Token == ')')                                                                          //CASE OF ')'
        {
            if(Stage==1 || Stage==4)
            {
                TopStack=ManageCloseingParanthesis(TopStack,Stage,PostFix,&i);
                Stage=4;
            }
            else
            {
                printf("\nERROR : No operands before )\n");
                break;
            }
        }
        else if (Token == '\0')                                                                 //CASE OF END OF INFIX NOTATION
        {
            if(Stage==1 || Stage==4)
            {
                TopStack=ManageEnd(TopStack,Stage,PostFix,&i);
                Stage=5;break;
            }
            else
            {
                printf("\nERROR : No operands or ) in the end\n");
                break;
            }
        }
        else if (Token == ' ');                                                                 //CASE OF SPACE
        else                                                                                    //CASE OF INVALID CHARECTOR
        {
            printf("ERROR:INVALID CHARACTER\n");
            break;
        }
    }
}

StackPointer ManageToken(StackPointer TopStack,int Stage,char Token,char PostFix[],int *i)
{
    struct oper O1,O2;
    if(Stage==1)
    {
        PostFix[(*i)++]=' ';
    }
    if(TopStack!=NULL)
    {
        while (TopStack->Operator != '(')
        {
            O1=Property(Token);                   //token is o1
            O2=Property(TopStack->Operator);      //operator token o2, found at the top of the operator stack
            if((O1.Precedence <= O2.Precedence) && O1.associative == LEFT_ASSOCIATIVITY )
            {
                PostFix[(*i)++] = TopStack->Operator;
                PostFix[(*i)++]=' ';
                TopStack=Pop(TopStack);
            }
            else if ((O1.Precedence < O2.Precedence) && O1.associative == RIGHT_ASSOCIATIVITY)
            {
                PostFix[(*i)++] = TopStack->Operator;
                PostFix[(*i)++]=' ';
                TopStack=Pop(TopStack);
            }
            else
            {
                TopStack=Push(Token,TopStack);
                break;
            }
            if(TopStack==NULL)
            {
                TopStack=Push(Token,TopStack);
                break;
            }
        }
        if(TopStack->Operator=='(')
        {
            TopStack=Push(Token,TopStack);
        }
    }
    else
        TopStack=Push(Token,TopStack);
    return TopStack;
}

StackPointer ManageCloseingParanthesis(StackPointer TopStack,int Stage,char PostFix[],int *i)
{
    if(Stage==1)
    {
        PostFix[(*i)++]=' ';
    }
    while (TopStack->Operator!='(')
    {
        PostFix[(*i)++]=TopStack->Operator;
        PostFix[(*i)++]=' ';
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

StackPointer ManageEnd(StackPointer TopStack,int Stage,char PostFix[],int *i)
{
    if(Stage==1)
    {
        PostFix[(*i)++]=' ';
    }
    while (TopStack!=NULL)
    {
        if(TopStack->Operator== '(')
        {
            printf("\nERROR : Mismatched parentheses Found\n");
            exit(1);
        }
        PostFix[(*i)++]=TopStack->Operator;
        PostFix[(*i)++]=' ';
        TopStack=Pop(TopStack);
    }
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
