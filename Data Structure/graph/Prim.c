#include "graph.h"

int main(){
    int n=7;//노드 수 입력하기 귀찮으니까 그냥 코드에 적을 것
    node_ptr g=data_init(n);
    if(g==NULL){
        return -1;
    }

    Prim(g,n);

    free(g);
    g=NULL;

    return 0;
}