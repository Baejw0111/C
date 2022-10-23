#include <stdio.h>
#include <stdlib.h>

void swap(int *a,int *b){
    int tmp=*a;
    *a=*b;
    *b=tmp;
}

int* array_init(int n){//정수형 배열 만드는 함수
    int *a=NULL;
    a=(int*)calloc(n,sizeof(int));

    return a;
}

void heap_adjust(int n,int *a,int s){//힙 재조정. s는 노드 값으로, 해당 값이 내려가는 걸 계속 추적하며 반복한다.
    while(s<n){
        int r=s;
        int left=2*s+1,right=2*s+2;
        if(left>=n&&right>=n){
            break;
        }

        if(right<n){
            if(*(a+left)>*(a+right)){
                if(*(a+left)>*(a+s)){
                    swap(a+s,a+left);
                    s=left;
                }
            }
            else{
                if(*(a+right)>*(a+s)){
                    swap(a+s,a+right);
                    s=right;
                }

            }
        }
        else{
            if(*(a+left)>*(a+s)){
                swap(a+s,a+left);
                s=left;
            }
        }
        if(s==r){
            break;
        }
    }
}

void heap_sort(int n,int *a){
    for(int i=n/2;i>=0;i--){
        heap_adjust(n,a,i);
    }

    for(int i=n-1;i>0;i--){
        swap(a,a+i);
        heap_adjust(i,a,0);
    }
}

int main(){
    int n;
    scanf("%d",&n);
    int *a=array_init(n);

    for(int *i=a;i<a+n;i++){
        scanf("%d",i);
    }

    heap_sort(n,a);

    for(int *i=a;i<a+n;i++){
        printf("%d\n",*i);
    }

    free(a);
    a=NULL;
    
    return 0;
}