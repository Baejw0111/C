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
    int n=10,*a=NULL,*b=NULL;
    int A[5][2]={0},B[5][2]={0},C[5][2]={0};
    clock_t start,finish;

    for(int i=0;i<5;++i){
        n*=10;
        printf("\nn=%d\n",n);

        a = (int*)calloc(n, sizeof(int));
        b = (int*)calloc(n, sizeof(int));

        srand(time(NULL));
        for(int j=0;j<n;j++){
            int tmp=rand();
            *(a+j)=tmp;
            *(b+j)=tmp;
        }

        //A
        start=clock();
        selection_sort(n,a);
        finish=clock();
        A[i][0]=finish-start;
        printf("test A-선택 정렬:%dms\n",A[i][0]);

        start=clock();
        insertion_sort(n,b);
        finish=clock();
        A[i][1]=finish-start;
        printf("test A-삽입 정렬:%dms\n",A[i][1]);

        //B
        start=clock();
        selection_sort(n,a);
        finish=clock();
        B[i][0]=finish-start;
        printf("test B-선택 정렬:%dms\n",B[i][0]);

        start=clock();
        insertion_sort(n,b);
        finish=clock();
        B[i][1]=finish-start;
        printf("test B-삽입 정렬:%dms\n",B[i][1]);

        reverse_selection_sort(n,a);
        reverse_selection_sort(n,b);

        //C
        start=clock();
        selection_sort(n,a);
        finish=clock();
        C[i][0]=finish-start;
        printf("test C-선택 정렬:%dms\n",C[i][0]);

        start=clock();
        insertion_sort(n,b);
        finish=clock();
        C[i][1]=finish-start;
        printf("test C-삽입 정렬:%dms\n",C[i][1]);

        free(a);
        free(b);

        a=NULL;
        b=NULL;
    }

    FILE *fp;
    fp=fopen("test A.csv","w");

    for(int i=0;i<5;++i){
        fprintf(fp,"%d, ",A[i][0]);
    }
    fprintf(fp,"\n");
    for(int i=0;i<5;++i){
        fprintf(fp,"%d, ",A[i][1]);
    }

    fclose(fp);

    fp=fopen("test B.csv","w");

    for(int i=0;i<5;++i){
        fprintf(fp,"%d, ",B[i][0]);
    }
    fprintf(fp,"\n");
    for(int i=0;i<5;++i){
        fprintf(fp,"%d, ",B[i][1]);
    }

    fclose(fp);

    fp=fopen("test C.csv","w");

    for(int i=0;i<5;++i){
        fprintf(fp,"%d, ",C[i][0]);
    }
    fprintf(fp,"\n");
    for(int i=0;i<5;++i){
        fprintf(fp,"%d, ",C[i][1]);
    }

    fclose(fp);

    return 0;
}