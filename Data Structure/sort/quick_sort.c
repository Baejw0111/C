#include "D:\OneDrive\Coding\C\Data Structure\DS.h"

int main(){
    int n=10000;
    int *a=array_init(n);

    srand(time(NULL));
    for(int *i=a;i<a+n;i++){
        *i=rand();
    }

    quick_sort(a,0,n);

    for(int *i=a;i<a+n;i++){
        printf("%d\n",*i);
    }

    free(a);
    a=NULL;
    
    return 0;
}