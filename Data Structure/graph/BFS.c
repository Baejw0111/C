#include "graph.h"

int main(){
    int n;
    printf("노드 개수 입력:");
    scanf("%d",&n);
    node_ptr g=data_init(n);
    if(g==NULL){
        return -1;
    }
    print_graph(g,n);

    bfs(g,0,n);

    free(g);
    g=NULL;

    return 0;
}