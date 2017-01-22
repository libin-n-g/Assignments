/*#include <stdio.h>
#include<stdlib.h>

struct Snapshot
{
    int n;
    int stage;
    struct Snapshot* Link;
};

typedef struct Snapshot Snapshot;

int main(void)
{
    Snapshot *Current;
    Snapshot *Top;
    Top=(Snapshot*)malloc(sizeof Snapshot);
    int ReVal=1;
    Current=Top;
    Current->stage=0;
    while(Current->stage)
    return 0;
}

*/
#include<stdio.h>
struct Snapshot
{
     int n, stage;
};

int factorial(int n);

int main()
{
  int n, fact;
  printf("enter n\n");
  scanf("%d", &n);
  fact=factorial(n);
  printf("%d \n", fact);
  return 0;
}

int factorial(int n)
{

  struct Snapshot snapshotStack[100],currentSnapshot,newSnapshot;
  int stacktop=-1, retVal=1;

  currentSnapshot.n=n;
  currentSnapshot.stage=0;

  /*push initial values*/
  stacktop=0;
  snapshotStack[stacktop]=currentSnapshot;

  while(stacktop>=0)
  {
    /* pop current values to be used */
    currentSnapshot=snapshotStack[stacktop];
    stacktop--;

     switch(currentSnapshot.stage)
     {
        case 0: if(currentSnapshot.n<=1)
                {  retVal=1;
                   continue;
                }

                else
                {
                 currentSnapshot.stage=1; //stage to continue, after returning from recursion
                 stacktop++;
                 snapshotStack[stacktop]=currentSnapshot; //push the details to be used after returning from recursion

                 newSnapshot.n=currentSnapshot.n - 1;
                 newSnapshot.stage=0;

                 stacktop++;
                 snapshotStack[stacktop]=newSnapshot;
                 continue;
                }

                 break;


        case 1: retVal=currentSnapshot.n * retVal;
                continue;
                break;
     }

  }
  return retVal;

}

