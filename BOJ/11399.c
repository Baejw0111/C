#include <stdio.h>

int main(){
    int n,a[1000]={0};
    scanf("%d",&n);

    for(int *i=a;i<a+n;i++){
        scanf("%d",i);
    }

    for(int *i=a;i<a+n-1;i++){
        for(int *j=a;j<a+n-1;j++){
            if(*j>*(j+1)){
                int tmp=*j;
                *j=*(j+1);
                *(j+1)=tmp;
            }
        }
    }

    int s=0;
    for(int *i=a;i<a+n;i++){
        int s1=0;
        for(int *j=a;j<i;j++){
            s1+=*j;
        }
        s+=s1+*i;
    }

    printf("%d",s);


    return 0;
}