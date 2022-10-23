#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data; 
    struct node *link;
} node;
//자기참조 구조체의 경우 typedef 선언시 이렇게 한꺼번에 선언해야 에러가 나지 않는다.
//구조체 내의 필드에 해당 구조체가 존재하기 때문.

typedef node *list_ptr;

list_ptr create(int n)//연결 리스트 생성, n은 노드 개수
{
    int *list=NULL;//데이터 받을 임시 배열 포인터
    list=(int *)calloc(n,sizeof(int));
    for(int *i=list;i<list+n;i++){
        scanf("%d",i);
    }

    list_ptr temp=NULL,before=NULL;
    for(int *i=list+n-1;i>=list;i--){
        temp=(list_ptr)malloc(sizeof(node));
        temp->data=*i;
        temp->link=before;
        before=temp;
        //끝 노드부터 거꾸로 생성함
    }

    free(list);

    return temp;
}

void print_list(list_ptr p){//리스트의 데이터 순서대로 출력
    if(p!=NULL){
        printf("현재 데이터: ");
        for(list_ptr i=p;i;i=i->link){
            printf("%d ",i->data);
        }
    }
    else{
        printf("데이터가 존재하지 않습니다.");
    }
    printf("\n");
    return;
}

list_ptr insert(list_ptr p){//n번째 자리에 m값을 가진 데이터 삽입(n은 1부터)
    int n,m;
    printf("몇번째 자리에 데이터를 삽입하시겠습니까?: ");
    scanf("%d",&n);
    printf("삽입할 정수 데이터의 값을 입력해주십시오: ");
    scanf("%d",&m);

    list_ptr new=NULL;
    new=(list_ptr)malloc(sizeof(node));
    new->data=m;

    if(p!=NULL){
        if(n==1){
            new->link=p;
            return new;
        }

        else{
            int j=1;
            for(list_ptr i=p;i;i=i->link,j++){
                if(j==n-1){
                        new->link=i->link;
                        i->link=new;
                        return p;
                }
            }
        }
    }

    printf("자릿수를 잘못 입력하셨습니다.\n");

    return p;
}

list_ptr delete(list_ptr p){//n값 가진 노드 삭제
    int n;  
    printf("삭제할 정수 데이터의 값을 입력해주십시오: ");
    scanf("%d",&n);
    
    list_ptr before=NULL;

    if(p!=NULL){
        for(list_ptr i=p;i;i=i->link){
            if(i->data==n){
                if(i==p){
                    p=p->link;
                }
                else{
                    before->link=i->link;
                    free(i);
                    i=NULL;
                }

                printf("데이터 삭제 완료\n");

                return p;
            }
            before=i;
        }
    }

    printf("데이터 %d은(는) 존재하지 않습니다.\n",n);

    return p;
}

void free_list(list_ptr p){
    list_ptr tmp=NULL;

    if(p!=NULL){
        for(list_ptr i=p;i;i=tmp){
            tmp=i->link;
            free(i);
            i=NULL;
        }
        printf("할당된 메모리가 모두 해제되었습니다.");
    }
    else{
        printf("데이터가 존재하지 않습니다.");
    }
    printf("\n");

    return;
}

int main()
{
    int n,s=0,m;
    printf("저장할 정수 데이터의 개수 입력:");
    scanf("%d",&n);

    printf("저장할 정수 데이터들을 입력:");
    list_ptr p = create(n);

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
                print_list(p);
                break;

            case 2:
                p=insert(p);
                print_list(p);
                break;
                
            case 3:
                p=delete(p);
                print_list(p);
                break;

            case 4:
                s++;
                free_list(p);
                break;
        }

    }


    return 0;
}