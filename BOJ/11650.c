#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int x,y;
}coor;

void swap(coor *a,coor *b){
    coor tmp=*a;
    *a=*b;
    *b=tmp;
}

coor* array_init(int n){
    coor *a=NULL;
    a=(coor*)calloc(n,sizeof(coor));

    return a;
}

void heap_adjust(int n,coor *a,int s){//힙 재조정. s는 노드 인덱스 값으로, 해당 노드가 내려가는 걸 계속 추적하며 반복한다.
    while(s<n){
        int r=s;
        int left=2*s+1,right=2*s+2;
        if(left>=n&&right>=n){
            break;
        }

        if(right<n){
            if((a+left)->x>(a+right)->x){
                if((a+left)->x>(a+s)->x){
                    swap(a+s,a+left);
                    s=left;
                }
                else if((a+left)->x==(a+s)->x){
                    if((a+left)->y>(a+s)->y){
                        swap(a+s,a+left);
                        s=left;
                    }
                }
            }
            else if((a+left)->x==(a+right)->x){
                if((a+left)->y>(a+right)->y){
                    swap(a+s,a+left);
                    s=left;
                }
                else{
                    swap(a+s,a+right);
                    s=right;
                }
            }
            else{
                if((a+right)->x>(a+s)->x){
                    swap(a+s,a+right);
                    s=right;
                }
                else if((a+right)->x==(a+s)->x){
                    if((a+right)->y>(a+s)->y){
                        swap(a+s,a+right);
                        s=right;
                    }
                }

            }
        }
        else{
            if((a+left)->x>(a+s)->x){
                swap(a+s,a+left);
                s=left;
            }
            else if((a+left)->x==(a+s)->x){
                if((a+left)->y>(a+s)->y){
                    swap(a+s,a+left);
                    s=left;
                }
            }
        }
        if(s==r){
            break;
        }
    }
}

void heap_sort(int n,coor *a){
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
    coor *a=array_init(n);

    for(coor *i=a;i<a+n;i++){
        scanf("%d %d",&i->x,&i->y);
    }

    heap_sort(n,a);

    for(coor *i=a;i<a+n;i++){
        printf("%d %d\n",i->x,i->y);
    }

    free(a);
    a=NULL;
    
    return 0;
}