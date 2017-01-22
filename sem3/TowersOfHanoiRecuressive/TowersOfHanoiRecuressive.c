/* DATE : 15-08-2016
 * AUTHOR : LIBIN N GEORGE
 * Recursive program for solving the Towers of Hanoi puzzile*/
#include <stdio.h>

int Tower(int nDisk,int nDestination,int nAuxillary,int nSource);

int main(void)
{
    int nDisk;
    int nDestination=1,nAuxillary=2,nSource=3;
    printf("Enter The Number of Disks to be transfed to 3rd pole from 1st pole:\n");
    scanf("%d",&nDisk);
    if(nDisk>0)
        Tower(nDisk,nDestination,nAuxillary,nSource);
    else
        printf("Error: NO DISKS TO MOVE");
    return 0;
}
//Recursive function for solving Towers of Hanoi puzzile for n disks
int Tower(int nDisk,int nDestination,int nAuxillary,int nSource)
{
    if(nDisk==1)
    {
        printf("Move Disk From pole %d to pole %d\n",nSource,nDestination);
        return 0;
    }
    Tower(nDisk-1,nAuxillary,nDestination,nSource);
    printf("Move Disk From pole %d to pole %d\n",nSource,nDestination);
    Tower(nDisk-1,nDestination,nSource,nAuxillary);
    return 0;
}
