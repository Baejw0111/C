#include <stdio.h>

int main(){
    int n,k,c[10],count=0,total=0;
    scanf("%d %d",&n,&k);

    for(int i=0;i<n;i++){
        scanf("%d",&c[i]);
    }
    
    for(int i=n-1;i>=0;i--){
        while(total+c[i]<=k){
            total+=c[i];
            count++;
        }
        if(total==k){
            break;
        }
    }
    printf("%d",count);

    return 0;
}