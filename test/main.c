#include<stdio.h>
#include<math.h>

typedef struct student
{
    int roll;
    float mark;
    char name[100];
}stdata;

stdata getdata(char c[200],FILE *fp);
double deviation(stdata stlist[],int n,double ave);
double average(stdata stlist[],int n);
void writetofile(char a[],stdata list1[],int n,char line[]);

void main(int argc,char *argv[])
{
    if(argc != 5)
        printf("input or output file name missing %s\n",argv[1]);

    stdata stlist[120],list1[120],list2[120],list3[120];
    char line[200];
    FILE *fp;
    int i=0,n,j=0,k=0,l=0;
    double ave,dev;

    fp=fopen(argv[1],"r");
    if(fp!=NULL)
    {
        fgets(line,200,fp);
        while(!feof(fp))
        {
            stlist[i]=getdata(line,fp);
            i++;
        }
        n=i-1;
        fclose(fp);
        ave=average(stlist,n);
        dev=deviation(stlist,n,ave);

        for(i=0;i<n;i++)
        {
            if(stlist[i].mark>=(ave+dev))
            {
                list1[j]=stlist[i];
                j++;
            }
            else if(stlist[i].mark<=(ave+dev) && stlist[i].mark>=(ave-dev))
            {
                list2[k]=stlist[i];
                k++;
            }
            else
            {
                list3[l]=stlist[i];
                l++;
            }
        }
        writetofile(argv[2],list1,j,line);
        writetofile(argv[3],list2,k,line);
        writetofile(argv[4],list3,l,line);
    }
    else
    {
    printf("ERROR");
    }
}


stdata getdata(char c[200],FILE *fp)
{
    stdata st;

    fscanf(fp,"%d",&st.roll);
    fgetc(fp);

    fscanf(fp,"%[^,]s",st.name);
    fgetc(fp);

    fscanf(fp,"%f",&st.mark);

    return st;
}
double deviation(stdata stlist[],int n,float ave)
{
    int i=0;
    double dev=0,dif;
    for (i=0;i<n;i++)
    {
        if(stlist[i].mark<ave)
        {
            dif=ave-stlist[i].mark;
        }
        else
        {
            dif=stlist[i].mark-ave;
        }
        dev=dev+dif;
    }
    dev=dev/n;
    dev=sqrt(dev);
    return dev;
}
double average(stdata stlist[],int n)
{
    double average=0;
    int i;
    for (i=0;i<n;i++)
    {
        average+=stlist[i].mark;
    }
    average=average/n;
    return average;
}
void writetofile(char a[],stdata list[],int n,char line[])
{
    FILE *fp;
    int i;
    fp=fopen(a,"w");
    if(fp!=NULL)
    {

        fprintf(fp,"%s",line);
        for(i=0;i<n;i++)
        {
            fprintf(fp,"%d,%s,%f\n",list[i].roll,list[i].name,list[i].mark);
        }
        fclose(fp);
    }
    else
    {
    printf("ERROR");
    }
}
