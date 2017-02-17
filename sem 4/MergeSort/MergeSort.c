/* AUTHOR : LIBIN N GEORGE
 * Last Changed:17-01-2017
 * program Implementing merge-sort on the input file input.bin and stores sorted output in a
 * human readable form in the file output.txt.
*/
#include<stdio.h>
#include<stdlib.h>
#define min(A,B) (A)<(B)?(A):(B)

void BottomUpMergeSort(char inputfile[], char outputfile[]);
void BottomUpMerge(FILE* fp1, FILE* fp2, FILE *fp3, int n);

FILE* OpenFile(char file[], char mode[]);//opens file and return pointer
int main()
{
    BottomUpMergeSort("input.bin","output.txt");
    return 0;
}
// SortMerge function
void BottomUpMergeSort(char inputfile[], char outputfile[])
{
    FILE *fp3, *fp2, *fp1, *fp4,*temp;
    char tempfile[]="temp.bin";
    int s=1,tempno,width=1,i=1,length;;
    fp1=OpenFile(inputfile,"rb+");
    fp3=OpenFile(tempfile,"wb+");
    if(fp1 == NULL || fp3 == NULL)
    {
    	remove(tempfile);
    	return;
    }
    fseek(fp1,0,SEEK_END);
    length=(ftell(fp1)/sizeof (int));
    for(width=1;width<length;width=width*2)
    {
        if(s%2==1)
            fp2=OpenFile(inputfile,"rb+");
        else
            fp2=OpenFile(tempfile,"rb+");
        if(fp2 == NULL)
    	{
    		return;
    	}
        fseek( fp1, 0, SEEK_SET );
        fseek( fp2, width*(sizeof (int)), SEEK_SET );
        for(i=0;i<length;i=i+2*width)
        {
            BottomUpMerge(fp1,fp2,fp3,min(i+2*width,length));
            fseek(fp1,(width-1)*(sizeof (int)),SEEK_CUR);
            fseek(fp2,(width-1)*(sizeof (int)),SEEK_CUR);
        }
        fseek( fp1, 0, SEEK_SET );
        temp=fp1;
        fp1=fp3;
        fp3=temp;
        s++;
        fclose(fp2);
    }
    fclose(fp3);
    remove(tempfile);
    fseek(fp1,0,SEEK_SET);
    fp4=OpenFile(outputfile,"wb+");
    if(fp4 == NULL)
   	{
   		return;
   	}
    while (fread(&tempno,sizeof(int),1,fp1)) 
    {
           fprintf(fp4,"%d\n",tempno);
    }
    fclose(fp4);
    fclose(fp1);
}
//Merge two lists starting with fp1 and fp2
void BottomUpMerge(FILE* fp1,FILE* fp2,FILE* fp3,int n)
{
    unsigned int pos1=0,pos2=0,end1;
    int temp1,temp2;
    end1=ftell(fp2);
    fread(&temp1,sizeof(int),1,fp1);
    fread(&temp2,sizeof(int),1,fp2);
    while (ftell(fp3) < n*sizeof(int))
    {
        if(!(feof(fp1)))
        {
            pos1 = ftell(fp1) - sizeof(int);   //in case of not EOF
        }
        else
        {
            pos1 = ftell(fp1);
        }
        if(!(feof(fp2)))
        {
            pos2 = ftell(fp2) - sizeof(int);     //in case of not EOF
        }
        else
        {
            pos2 = ftell(fp2);
        }
        if (pos1 < end1 && (pos2 >= (n*sizeof(int)) || temp1 <= temp2))
        {
            fwrite(&temp1,sizeof (int),1,fp3);
            fread(&temp1,sizeof(int),1,fp1);
        }
        else
        {
            fwrite(&temp2,sizeof (int),1,fp3);
            fread(&temp2,sizeof(int),1,fp2);
        }
    }
}
FILE* OpenFile(char file[],char mode[] )
{
    FILE* fp;
    fp=fopen(file,mode);
    if(fp == NULL)
    {
        printf("\nERROR: Unable to open File\n");
        return NULL;
    }
    return fp;

}
