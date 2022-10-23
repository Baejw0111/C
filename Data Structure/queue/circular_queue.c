#include "D:\OneDrive\Coding\C\Data Structure\DS.h"

int main(){
    que q;
    printf("큐 사이즈 입력: ");
    int size;
    scanf("%d",&size);
    cque_init(&q,size);

    int sw=1;
    while(sw){
        int m,item;
        printf("choose mode(0:insert / 1:delete / 2: finish):");
        scanf("%d",&m);
        switch (m)
        {
        case 0:
            printf("insert element:");
            scanf("%d",&item);
            cque_insert(&q,item);
            break;
        
        case 1:
            cque_delete(&q);
            break;
        
        case 2:
            sw=0;
            break;
        }
        cque_print(q);
        printf("present array:");
        for(int j=0;j<q.size;j++){
            printf("%d ",q.queue[j]);
        }
        printf("\n\n");
    }

    free(q.queue);
    q.queue=NULL;

    return 0;
}