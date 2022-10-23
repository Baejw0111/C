#include <stdio.h>
#include <stdlib.h>

typedef struct queue 
{
    int data; 
    struct  queue *link;
} queue;

typedef queue *queue_ptr;

queue_ptr front=NULL,rear=NULL;

void insert(queue_ptr *front,queue_ptr *rear,int item){//리스트 맨 뒤에 노드 삽입
    queue_ptr temp=(queue_ptr)malloc(sizeof(queue));
    temp->data=item;
    temp->link=NULL;
    if(*front){
        (*rear)->link=temp;
    }
    else{
        *front=temp;
    }
    *rear=temp;
}

int delete(queue_ptr *front){//리스트 맨 앞의 노드를 삭제
    queue_ptr temp=*front;
    int item=temp->data;
    *front=(*front)->link;
    free(temp);
    temp=NULL;

    return item;
}

void print_list(){
    if(front){
        printf("현재 데이터: ");
        for(queue_ptr i=front;i;i=i->link){
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
    queue_ptr tmp=NULL;

    if(front){
        for(queue_ptr i=front;i;i=tmp){
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
    printf("==QUEUE==\n");
    printf("데이터 삽입은 맨 뒤에서 이뤄지며,\n데이터 삭제는 맨 앞에서 이뤄집니다.\n\n");
    int n,s=0,m,item;
    printf("저장할 정수 데이터의 개수 입력:");
    scanf("%d",&n);

    printf("저장할 정수 데이터들을 입력:");
    for(int i=0;i<n;i++){
        scanf("%d",&item);
        insert(&front,&rear,item);
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
                insert(&front,&rear,item);
                print_list();
                break;
                
            case 3:
                if(front){
                    delete(&front);
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