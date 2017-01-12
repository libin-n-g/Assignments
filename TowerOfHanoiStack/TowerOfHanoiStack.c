/*Last Changed : 22-08-2016
 * AUTHOR : LIBIN N GEORGE
 * program that iteratively solves the tower of Hanoi program, obtained by eliminating recursion using stack*/
#include <stdio.h>
#include<stdlib.h>

struct Snapshot
{
     int nDisc, Stage, nDestination,nAuxillary,nSource;
     struct Snapshot *Link;
};

typedef struct Snapshot* SnapShot;

void Tower(int nDisc);
SnapShot AllocateMemory();

int main(void)
{
    int nDisc;
    printf("Enter The Number of Discs to be transfed to 3rd pole from 1st pole:\n");
    scanf("%d",&nDisc);
    if(nDisc>0)
        Tower(nDisc);
    else
        printf("Error: NO DISKS TO MOVE");
    return 0;
}

//function for solving Towers of Hanoi puzzile for n disks(using stack)
void Tower(int nDisc)
{
    SnapShot currentSnapshot;
    SnapShot newSnapshot;
    SnapShot StackTop=NULL;

    currentSnapshot=AllocateMemory();

    currentSnapshot->nDestination=3;
    currentSnapshot->nAuxillary=2;
    currentSnapshot->nSource=1;
    currentSnapshot->nDisc=nDisc;
    currentSnapshot->Stage=0;
    currentSnapshot->Link=NULL;

    StackTop=currentSnapshot;

    while (StackTop!=NULL)
    {
        currentSnapshot=StackTop;
        StackTop=StackTop->Link;

        switch (currentSnapshot->Stage)
        {
        case 0:
            if(currentSnapshot->nDisc<=1)
            {
                 printf("Move Disk From pole %d to pole %d\n",currentSnapshot->nSource,currentSnapshot->nDestination);
                 free(currentSnapshot);
                 continue;
            }
            else
            {
                currentSnapshot->Stage=1;

                newSnapshot=AllocateMemory();

                newSnapshot->nDestination=currentSnapshot->nAuxillary;
                newSnapshot->nAuxillary=currentSnapshot->nDestination;
                newSnapshot->nSource=currentSnapshot->nSource;
                newSnapshot->Stage=0;
                newSnapshot->nDisc=(currentSnapshot->nDisc)-1;
                newSnapshot->Link=currentSnapshot;

                StackTop=newSnapshot;
                continue;
            }
            
            break;
        case 1:
                printf("Move Disk From pole %d to pole %d\n",currentSnapshot->nSource,currentSnapshot->nDestination);

                newSnapshot=AllocateMemory();

                newSnapshot->nDestination=currentSnapshot->nDestination;
                newSnapshot->nAuxillary=currentSnapshot->nSource;
                newSnapshot->nSource=currentSnapshot->nAuxillary;
                newSnapshot->Stage=0;
                newSnapshot->nDisc=(currentSnapshot->nDisc)-1;
                newSnapshot->Link=currentSnapshot->Link;

                free(currentSnapshot);
                StackTop=newSnapshot;

                continue;
                break;
        default:
            break;
        }
    }
}
//allocates memory
SnapShot AllocateMemory()
{
    SnapShot pointer=NULL;
    pointer=(SnapShot)malloc(sizeof (struct Snapshot));
    if(pointer==NULL)
    {
        printf("ERROR!:NO MEMORY ALLOCATED");
        exit(1);
    }
    return pointer;
}
