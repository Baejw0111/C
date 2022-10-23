#include <stdio.h>

int n,m;

void permutation(int p[],int a[],int c){
    if(c==m){
        for(int i=0;i<m;i++){
            printf("%d ",p[i]+1);
        }
        printf("\n");
        return;
    }

    for(int i=0;i<n;i++){
        if(a[i]==1){
            continue;
        }
        int p1[8]={0};
        int a1[8]={0};
        for(int j=0;j<c;j++){
            p1[j]=p[j];
        }
        for(int j=0;j<n;j++){
            a1[j]=a[j];
        }
        p1[c]=i;
        a1[i]=1;
        permutation(p1,a1,c+1);
    }
}

int main(){
    scanf("%d %d",&n,&m);

    int p[8]={0},a[8]={0};
    permutation(p,a,0);

    return 0;
}