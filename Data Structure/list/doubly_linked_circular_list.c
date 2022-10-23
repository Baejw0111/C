#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    int data_num;//head 노드에만 기록된다. 전체 데이터 개수가 저장된다.
    struct node *llink, *rlink;
} node;
//이중 연결리스트의 경우 양쪽으로 링크가 필요함

typedef node *list_ptr;

list_ptr create(int n) //연결 리스트 생성, n은 노드 개수
{
    list_ptr head = NULL,  tmp = NULL;

    head = (list_ptr)malloc(sizeof(node));
    head->data_num=n;
    tmp=head;

    for (int i = 0; i < n; i++)
    {
        tmp->rlink=NULL;
        tmp->rlink= (list_ptr)malloc(sizeof(node));
        tmp->rlink->llink=tmp;
        tmp=tmp->rlink;
        scanf("%d", &(tmp->data));
    }

    tmp->rlink = head;
    head->llink = tmp;

    return head;
}

void print_list(list_ptr head)
{ //리스트의 헤드 노드의 오른쪽 노드부터 출력
    if (head->data_num != 0)
    {
        printf("현재 데이터: ");
        for (list_ptr i = head->rlink; i != head; i = i->rlink)
        {
            printf("%d ", i->data);
        }
    }
    else
    {
        printf("데이터가 존재하지 않습니다.");
    }
    printf("\n");
    return;
}

list_ptr insert(list_ptr head)
{ // n번째 자리에 m값을 가진 데이터 삽입(n은 1부터)
    int n, m;
    printf("몇번째 자리에 데이터를 삽입하시겠습니까?: ");
    scanf("%d", &n);
    printf("삽입할 정수 데이터의 값을 입력해주십시오: ");
    scanf("%d", &m);

    if(n>head->data_num+1||n<1){
        printf("자릿수를 잘못 입력하셨습니다.\n");
    }
    else{
        list_ptr new = NULL;
        new = (list_ptr)malloc(sizeof(node));
        new->data = m;

        if(n==head->data_num+1){
            head->data_num+=1;
            new->rlink=head;
            new->llink=head->llink;
            head->llink->rlink=new;
            head->llink=new;
        }
        else{
            int j = 1;
            for (list_ptr i = head->rlink; i != head; i++, j++)
            {
                if (j == n)
                {
                    head->data_num+=1;
                    new->llink = i->llink;
                    new->rlink = i;
                    i->llink->rlink = new;
                    i->llink = new;

                    break;
                }
            }
        }
    }


    return head;
}

list_ptr delete (list_ptr head)// n값 가진 노드 삭제
{ 
    int n;
    printf("삭제할 정수 데이터의 값을 입력해주십시오: ");
    scanf("%d", &n);

    if (head->data_num != 0)
    {
        for (list_ptr i = head->rlink; i != head; i = i->rlink)
        {
            if (i->data == n)
            {
                head->data_num-=1;
                i->llink->rlink = i->rlink;
                i->rlink->llink = i->llink;
                free(i);
                i=NULL;

                printf("데이터 삭제 완료\n");
                return head;
            }
        }
    }

    printf("데이터 %d은(는) 존재하지 않습니다.\n", n);

    return head;
}

void reverse_print_list(list_ptr head)
{
    if (head->data_num != 0)
    {
        printf("현재 데이터 역순서로 출력: ");
        for (list_ptr i = head->llink; i != head; i = i->llink)
        {
            printf("%d ", i->data);
        }
    }
    else
    {
        printf("데이터가 존재하지 않습니다.");
    }
    printf("\n");
    return;
}

void free_list(list_ptr head)
{
    list_ptr tmp = NULL;
    head->llink->rlink=NULL;
    for (list_ptr i = head; i; i=tmp)
    {
        tmp = i->rlink;
        free(i);
        i=NULL;
    }
    printf("할당된 메모리가 모두 해제되었습니다.\n");

    return;
}

int main()
{
    int n, s = 0, m;
    printf("저장할 정수 데이터의 개수 입력:");
    scanf("%d", &n);

    printf("저장할 정수 데이터들을 입력:");
    list_ptr p = create(n);

    while (s == 0)
    {
        printf("\n===MENU===\n");
        printf("1: 현재 데이터 열람\n");
        printf("2: 데이터 삽입\n");
        printf("3: 데이터 삭제\n");
        printf("4: 현재 데이터 역순서로 출력\n");
        printf("5: 프로그램 끝내기\n");

        printf("선택할 메뉴 입력: ");
        scanf("%d", &m);
        printf("\n");

        switch (m)
        {
        case 1:
            print_list(p);
            break;

        case 2:
            p = insert(p);
            print_list(p);
            break;

        case 3:
            p = delete (p);
            print_list(p);
            break;

        case 4:
            reverse_print_list(p);
            break;
            
        case 5:
            s++;
            free_list(p);
            break;
        }
    }

    return 0;
}