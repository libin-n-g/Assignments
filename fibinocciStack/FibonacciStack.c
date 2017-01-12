/* Last Changed : 20-08-2016
 * AUTHOR : LIBIN N GEORGE
 * program for computing the n-th fibonacci number using Stack*/
#include <stdio.h>
#include<stdlib.h>

struct Snapshot
{
    int n,nStage;
    struct Snapshot *Link;
};

typedef struct Snapshot* SnapShot;

long int fib(int n);
SnapShot AllocateMemory();

int main(void)
{
    int n;
    printf("Enter which term of fibinocci series you want to print:\n");
    scanf("%d",&n);
    if(n>0)
    {
        printf("The %d th number of fibinocci series is %ld\n",n,fib(n));
    }
    else
    {
        printf("ERROR\n");
    }
    return 0;
}
//function for finding n th fibonacci number(using Stack)
long int fib(int n)
{
    SnapShot CurrentSnapShot,NewSnapShot,StackTop=NULL;  //pointer to the structure Snapshot
    long int RetVal=0;

    CurrentSnapShot=AllocateMemory();
    CurrentSnapShot->n=n;
    CurrentSnapShot->nStage=0;
    CurrentSnapShot->Link=NULL;

    StackTop=CurrentSnapShot;

    while (StackTop !=NULL)
    {
        CurrentSnapShot=StackTop;
        StackTop=CurrentSnapShot->Link;

        switch (CurrentSnapShot->nStage)
        {
        case 0:
            if(CurrentSnapShot->n == 1)
            {
                RetVal= RetVal + 0;
                free(CurrentSnapShot);
                continue;
            }
            else if(CurrentSnapShot->n == 2)
            {
                RetVal=RetVal + 1;
                free(CurrentSnapShot);
                continue;
            }
            else
            {
            CurrentSnapShot->nStage=1;

            NewSnapShot=AllocateMemory();
            NewSnapShot->n=CurrentSnapShot->n-1;
            NewSnapShot->nStage=0;
            NewSnapShot->Link=CurrentSnapShot;

            StackTop=NewSnapShot;
            continue;
            }
            break;

        case 1:
            CurrentSnapShot->nStage=2;

            NewSnapShot=AllocateMemory();
            NewSnapShot->n=CurrentSnapShot->n-2;
            NewSnapShot->nStage=0;
            NewSnapShot->Link=CurrentSnapShot->Link;

            StackTop=NewSnapShot;
            free(CurrentSnapShot);
            continue;
            break;


        default:
            break;
        }

    }

    return RetVal;
}
//allocate memory for each stack
SnapShot AllocateMemory()
{
    SnapShot pointer;
    pointer=(SnapShot)malloc(sizeof (struct Snapshot));
    if(pointer==NULL)
    {
        printf("ERROR!:NO MEMORY ALLOCATED");
        exit(1);
    }
    return pointer;
}
