#include<stdio.h>


void BottomUpMergeSort(FILE* fp1, FILE*fp2, FILE *fp3);
void BottomUpMerge(FILE* fp1, FILE* fp2, FILE *fp3, int n);
int main()
{
    FILE *fp1;
    FILE *fp2;
    FILE *fp3;
    fp1 = fopen("Input.bin","r+");
    fp2 = fopen("Input.bin","r+");
    fp3 = fopen("temp.bin","w+");
    int i;


    BottomUpMergeSort(fp1,fp2,fp3);
    return 0;
}
void BottomUpMergeSort(FILE* fp1, FILE*fp2, FILE *fp3)
{
    int width,i,length,temp1,temp2;
    //FILE *fpright,*fpEnd;
    fseek( fp1, 0, SEEK_END );
    i=ftell(fp1);
    length=(i/sizeof (int));
    printf("%d\n",length);
    fseek( fp1, 0, SEEK_SET );
    i=ftell(fp1);
    printf("%d\n",i);
    fread(&i,sizeof(int),1,fp1);
    printf("%d\n",i);
    fseek( fp1, 0, SEEK_SET );
   // (*fpright)=(*fp1);
    for(width=1;width<length;width++)
    {
//        fread(&i,sizeof(int),1,fp1);
//        printf("%d\n",i);
        for(i=0;i<length;i=i+2*width)
        {
            fseek(fp1,i*(sizeof (int)),SEEK_CUR);
            fseek(fp2,(i+width)*(sizeof (int)),SEEK_CUR);
            temp1=ftell(fp2);
            temp2=ftell(fp1);
            printf("width=%d--i=%d---fp2=%d----------%d\n",width,i,temp1/4,temp2/4);


        }
    }
    i=ftell(fp1);
    printf("%d\n",i);
}
//void BottomUpMerge(FILE* fp1,FILE* fp2,FILE* fp3,int n)
//{
//    while ((fp1!=EOF) || (fp2!=EOF))
//    {          //  If left run head exists and is <= existing right run head.
//           if ()//i < iRight && (j >= iEnd || A[i] <= A[j])
//           {
//               fread(&temp,sizeof(int),1,fp1);
//               fwrite(&temp,sizeof (int),1,fp3);
//               fseek();//i = i + 1;
//           } else
//           {
//               B[k] = A[j];
//               j = j + 1;
//           }
//       }
//}
