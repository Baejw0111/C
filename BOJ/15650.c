#include <stdio.h>

int n,m;

void permutation(int a[],int s,int c){
    if(c==m){
        int sum=0;
        for(int i=0;i<n;i++){
            sum+=a[i];
        }
        if(sum==m){
            for(int i=0;i<n;i++){
                if(a[i]==1){
                    printf("%d ",i+1);
                }
            }
            printf("\n");
        }

        return;
    }

    for(int i=s;i<n;i++){
        if(a[i]==1){
            continue;
        }
        int a1[8]={0};
        for(int j=0;j<n;j++){
            a1[j]=a[j];
        }
        a1[i]=1;
        permutation(a1,i,c+1);
    }
}

int main(){
    scanf("%d %d",&n,&m);

    int a[8]={0};
    permutation(a,0,0);

    return 0;
}