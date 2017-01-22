/* LAST CHANGED : 12-09-2016
 * AUTHOR : LIBIN N GEORGE
 * program for evaluating a postfix expression*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

struct StackNode
{
    int operand;
    struct StackNode* next;
};

typedef struct StackNode* StackPointer;

StackPointer Push(int c,StackPointer PrevTop);  //push the value to the stack
StackPointer Pop(StackPointer Top);             //delete the top StackNode
int ConvertToNumber(int num[10],int n);         //convert array of digits to number(int)

int main(void)
{
    StackPointer Top=NULL;
    char Token,PostFix[100];
    int *Num;
    int i=0,j=0,a,b;
    Num=(int*)malloc(10 * sizeof (int));
    printf("Enter Postfix Expression to calculate (keep space between numbers \n and press ENTER at the end of expression):\n");
    scanf("%[^\n]s",PostFix);
    while (1)
    {
        Token=PostFix[j++];
        if(Token == ' ')
        {
            if(i!=0)                 //i=0 is a case of invalid number(space not after number)
            {
                Top=Push(ConvertToNumber(Num,i),Top);
                i=0;
            }
        }
        else if (isdigit(Token))
        {
            Num[i++]=Token-'0';//each digit entered is added into the arrray
        }
        else if ( Token== '+' || Token== '-' || Token== '*' || Token== '/' || Token == '^' )
        {
            if (Top!=NULL)
            b=Top->operand;
            Top=Pop(Top);
            if (Top!=NULL)
            a=Top->operand;
            Top=Pop(Top);
            switch (Token)
            {
            case '+':
                Top=Push(a+b,Top);
                break;
            case '-':
                Top=Push(a-b,Top);
                break;
            case '*':
                Top=Push(a*b,Top);
                break;
            case '/':
                Top=Push(a/b,Top);
                break;
            case '^':
                Top=Push(pow(a,b),Top);
                break;
            default:
                break;
            }
        }
        else if (Token == '\0')
        {
             break;
        }
        else
        {
            printf("\nERROR:INVALID CHARACTER\n");
            break;
        }
    }
    free(Num);
    if(Top->next==NULL)
    {
        printf("ans=%d\n",Top->operand);
        Top=Pop(Top);
    }
    else
        printf("ERROR:operator missing\n");
    return 0;
}
//push the value to the stack
StackPointer Push(int c, StackPointer PrevTop)
{
    StackPointer Top;
    if(PrevTop==NULL)
    {
        Top=(StackPointer)malloc(sizeof (struct StackNode));

        Top->operand=c;
        Top->next=NULL;
        return Top;
    }
    else
    {
        Top=(StackPointer)malloc(sizeof (struct StackNode));
        Top->operand=c;
        Top->next=PrevTop;
        return Top;
    }
}
//convert array of digits to number(int)
int ConvertToNumber(int num[10], int n)
{
    int i, k = 0;
    for (i = 0; i<n; i++)
        k = 10 * k + num[i];
    return k;
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
        printf("ERROR:Stack EMPTY: Operands for operations Not Found\n");
        exit(1);
        return Top;
    }
}
