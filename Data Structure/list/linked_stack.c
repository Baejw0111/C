#include <stdio.h>
#include <stdlib.h>

typedef struct stack 
{
    int data; 
    struct  stack *link;
} stack;

typedef stack *stack_ptr;

stack_ptr top=NULL;

void push(stack_ptr *top,int item){//리스트 맨 앞에 노드 삽입
    stack_ptr temp=(stack_ptr)malloc(sizeof(stack));
    temp->data=item;
    temp->link=*top;
    *top=temp;
}

int pop(stack_ptr *top){//리스트 맨 앞의 노드를 삭제
    stack_ptr temp=*top;
    int item=temp->data;
    *top=(*top)->link;
    free(temp);
    temp=NULL;

    return item;
}

void print_list(){
    if(top){
        printf("현재 데이터: ");
        for(stack_ptr i=top;i;i=i->link){
            printf("%d ",i->data);
        }
    }
    else{
        printf("데이터가 존재하지 않습니다.");
    }
    printf("\n");
    return;
}

void free_list(){
    stack_ptr tmp=NULL;

    if(top!=NULL){
        for(stack_ptr i=top;i;i=tmp){
            tmp=i->link;
            free(i);
            i=NULL;
        }
        printf("할당된 메모리가 모두 해제되었습니다.");
    }
    else{
        printf("데이터가 이미 모두 삭제되었습니다.");
    }
    printf("\n");

    return;
}

int main()
{
    printf("==STACK==\n");
    printf("데이터 삽입과 삭제 모두 맨 앞에서 이뤄집니다.\n\n");
    int n,s=0,m,item;
    printf("저장할 정수 데이터의 개수 입력:");
    scanf("%d",&n);

    printf("저장할 정수 데이터들을 입력:");
    for(int i=0;i<n;i++){
        scanf("%d",&item);
        push(&top,item);
    }

    while(s==0){
        printf("\n===MENU===\n");
        printf("1: 현재 데이터 열람\n");
        printf("2: 데이터 삽입\n");
        printf("3: 데이터 삭제\n");
        printf("4: 프로그램 끝내기\n");

        printf("선택할 메뉴 입력: ");
        scanf("%d",&m);
        printf("\n");

        switch (m)
        {
            case 1:
                print_list();
                break;

            case 2:
                printf("저장할 정수 데이터 입력:");
                scanf("%d",&item);
                push(&top,item);
                print_list();
                break;
                
            case 3:
                if(top){
                    pop(&top);
                }
                print_list();
                break;

            case 4:
                s++;
                free_list();
                break;
        }

    }
    return 0;
}