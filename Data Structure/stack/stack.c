#include "D:\OneDrive\Coding\C\Data Structure\DS.h"


int main(){
    stk s;
    int size;
    printf("스택 사이즈 입력: ");
    scanf("%d",&size);
    stk_init(&s,size);

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
            stk_push(&s,item);
            break;
        
        case 1:
            stk_pop(&s);
            break;
        
        case 2:
            sw=0;
            break;
        }
        stk_print(s);
        printf("\n");
    }

    free(s.stack);
    s.stack=NULL;

    return 0;
}