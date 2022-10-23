#include "D:\OneDrive\Coding\C\Data Structure\DS.h"

int main(){
    int size;
    scanf("%d",&size);

    int *a=array_init(size);

    for(int i=0;i<size;i++){
        a[i]=i+1;
    }

    int n;
    scanf("%d",&n);

    clock_t start,finish;

    start=clock();
    sequential_search(size,n,a);
    finish=clock();

    double duration=(double)(finish-start);
    printf("실행 시간: %.lf\n",duration);
    
    return 0;
}