#include <time.h>
#include <stdlib.h>
#include<stdio.h>

FILE* GenerateRandomNumberFile(FILE* fp1);
int main()
{
    FILE * fp1;
    fp1 = fopen("input.bin","w");
    fp1 = GenerateRandomNumberFile(fp1);
    fclose(fp1);
    return 0;
}

FILE* GenerateRandomNumberFile(FILE *fp1)
{
    srand(time(NULL));
    int r;
    long int i=1000;
    while(i)
    {
        r = rand();
        fwrite(&r,sizeof (int),1,fp1);
        i--;
    }
    return fp1;
}

