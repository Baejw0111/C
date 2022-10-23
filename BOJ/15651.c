#include <stdio.h>

int n,m;

void permutation(int p[],int c){
    if(c==m){
        for(int i=0;i<m;i++){
            printf("%d ",p[i]+1);
        }
        printf("\n");

        return;
    }

    for(int i=0;i<n;i++){
        int p1[8]={0};
        for(int j=0;j<n;j++){
            p1[j]=p[j];
        }
        p1[c]=i;
        permutation(p1,c+1);
    }
}

int main(){
    scanf("%d %d",&n,&m);

    int p[8]={0};
    permutation(p,0);

    return 0;
}