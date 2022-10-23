#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a,int *b);
void quick_sort(int *a,int left,int right);

int main()
{
    int *arr=NULL,n;
    scanf("%d",&n);
    arr=(int*)calloc(n,sizeof(int));

    for(int i=0;i<n;++i){
        scanf("%d",arr+i);
    }

    quick_sort(arr,0,n-1);

    for(int i=0;i<n;++i){
        printf(" %d",arr[i]);
    }

    free(arr);
    return 0;
}

void swap(int *a,int *b){
    int tmp=*a;
    *a=*b;
    *b=tmp;
}

void quick_sort(int *a,int left,int right){//퀵 정렬
    if(left<right){//해당 조건 불만족 시 재귀 종료
        srand(time(NULL));
        int k=left+rand()%(right-left);
        
        int pivot=a[k],i=left,j=right;

        do{
            while(a[i]<pivot){
                ++i;
            }

            while(a[j]>pivot){
                --j;
            }

            if(i<=j){
                swap(a+i,a+j);
                ++i;
                --j;
            }

        }while(i<=j);

        if(left<j){
            quick_sort(a,left,j);
        }

        if(i<right){
            quick_sort(a,i,right);
        }
    }
}