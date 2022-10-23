#include <stdio.h>

typedef struct{
    int start,end;
}meeting;

int n,c=0;
meeting m[100000]={0};

int meeting_time(int start,int end,int count,meeting *p){
    int return_count=count;
    for(meeting *i=p+1;i<m+n;i++){
        if(i->start>=end){
            int r=meeting_time(i->start,i->end,count+1,i);
            if(r>return_count){
                return_count=r;
            }
        }
    }
    return return_count;
}

int main(){
    scanf("%d",&n);

    for(meeting *i=m;i<m+n;i++){
        scanf("%d %d",&i->start,&i->end);
    }

    for(meeting *i=m;i<m+n-1;i++){
        for(meeting *j=m;j<m+n-1;j++){
            if(j->start>(j+1)->start){
                meeting tmp=*j;
                *j=*(j+1);
                *(j+1)=tmp;
            }
        }
    }

    for(meeting *i=m;i<m+n;i++){
        int t=meeting_time(i->start,i->end,1,i);
        if(t>c){
            c=t;
        }
    }

    printf("%d",c);

    return 0;
}