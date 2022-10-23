#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a,int *b){
    int tmp=*a;
    *a=*b;
    *b=tmp;
}

void selection_sort(int n,int* a){//선택 정렬
    for(int i=n-1;i>=0;i--){
        int max=i;//가장 큰 값을 가진 인덱스
        for(int j=i;j>=0;j--){
            if(*(a+j)>*(a+max)){
                max=j;
            }
        }
        swap(a+i,a+max);
    }
}

void insertion_sort(int n, int *a)
{ //삽입 정렬
    for (int *i = a + 1; i < a + n; i++)
    {
        int tmp=*i,*j=i-1;
        while(tmp<*j&&j>=a){
            *(j+1)=*j;
            --j;
        }

        *(j+1)=tmp;
    }
}

void reverse_selection_sort(int n,int* a){//역순 선택 정렬
    for(int i=n-1;i>=0;i--){
        int min=i;//가장 작은 값을 가진 인덱스
        for(int j=i;j>=0;j--){
            if(*(a+j)<*(a+min)){
                min=j;
            }
        }
        swap(a+i,a+min);
    }
}

int main(){
    int n=10000,*a=NULL,*b=NULL;
    clock_t start,finish;
    int A[50][2]={0},B[50][2]={0},C[50][2]={0};

    a = (int*)calloc(n, sizeof(int));
    b = (int*)calloc(n, sizeof(int));

    for(int i=0;i<50;++i){
        printf("%d%%\n",i*2);
        srand(time(NULL));
        for(int i=0;i<n;i++){
            int tmp=rand();
            *(a+i)=tmp;
            *(b+i)=tmp;
        }


        //A
        start=clock();
        selection_sort(n,a);
        finish=clock();
        A[i][0]=finish-start;

        start=clock();
        insertion_sort(n,b);
        finish=clock();
        A[i][1]=finish-start;

        //B
        start=clock();
        selection_sort(n,a);
        finish=clock();
        B[i][0]=finish-start;

        start=clock();
        insertion_sort(n,b);
        finish=clock();
        B[i][1]=finish-start;

        reverse_selection_sort(n,a);
        reverse_selection_sort(n,b);

        //C
        start=clock();
        selection_sort(n,a);
        finish=clock();
        C[i][0]=finish-start;

        start=clock();
        insertion_sort(n,b);
        finish=clock();
        C[i][1]=finish-start;
    }

    free(a);
    free(b);

    FILE *fp;
    fp=fopen("test A1.csv","w");

    for(int i=0;i<50;++i){
        fprintf(fp,"%d, ",A[i][0]);
    }
    fprintf(fp,"\n");
    for(int i=0;i<50;++i){
        fprintf(fp,"%d, ",A[i][1]);
    }

    fclose(fp);

    fp=fopen("test B1.csv","w");

    for(int i=0;i<50;++i){
        fprintf(fp,"%d, ",B[i][0]);
    }
    fprintf(fp,"\n");
    for(int i=0;i<50;++i){
        fprintf(fp,"%d, ",B[i][1]);
    }

    fclose(fp);

    fp=fopen("test C1.csv","w");

    for(int i=0;i<50;++i){
        fprintf(fp,"%d, ",C[i][0]);
    }
    fprintf(fp,"\n");
    for(int i=0;i<50;++i){
        fprintf(fp,"%d, ",C[i][1]);
    }

    fclose(fp);
    
    return 0;
}