#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int elem;         //원소
    struct node *next; //다음 노드 가리키는 포인터
} node;

typedef node *node_ptr;

typedef struct list
{
    node_ptr head;
    int count; // list에 존재하는 원소의 개수
} list;

typedef list *List;

List allocList(int n); //리스트 만드는 함수
List partition(List L, int k);
void freeList(List L); //동적 할당된 메모리 해제
void merge(List L1, List L2);
void mergeSort(List L);

int main()
{
    int n;
    scanf("%d", &n);

    List L=allocList(n);

    mergeSort(L);

    node_ptr tmp = L->head;
    while (tmp!=NULL)
    {
        printf(" %d", tmp->elem);
        tmp = tmp->next;
    }

    freeList(L);

    return 0;
}

List allocList(int n)
{ //리스트 만드는 함수
    List L = NULL;
    L=(List)calloc(1,sizeof(list));
    L->head=NULL;
    L->count = n;

    node_ptr prev = NULL; //리스트 끝노드
    for (int i = 0; i < n; ++i)
    {
        node_ptr tmp = NULL;
        tmp = (node_ptr)calloc(1, sizeof(node));
        scanf("%d", &tmp->elem);

        if (i == 0)
        {
            L->head = tmp;
        }
        else
        {
            prev->next = tmp;
        }
        prev = tmp;
    }
    prev->next = NULL;

    return L;
}

List partition(List L, int k)
{
    node_ptr tmp = NULL;
    for (int i = 0; i < k; ++i)
    {
        if (i == 0)
        {
            tmp = L->head;
        }
        else
        {
            tmp = tmp->next;
        }
    }

    List L2=NULL;
    L2=(List)calloc(1,sizeof(list));
    L2->head = tmp->next; // L의 k번째 노드의 다음 노드를 L2의 첫 노드로 만든 후 연결 끊기
    tmp->next = NULL;

    //따라서 L에는 k개의 노드만 남고, L2에는 |L|-k개의 노드가 있다.
    L2->count = L->count - k;
    L->count = k;

    return L2;
}

void freeList(List L)
{ //동적 할당된 메모리 해제
    node_ptr tmp = NULL;

    while (L->head)
    {
        tmp = L->head;
        L->head = L->head->next;
        free(tmp);
    }

    free(L);
    L=NULL;
}

void merge(List L1, List L2)
{
    L1->count += L2->count;
    node_ptr newHead=NULL,prev = NULL; // newHead: 새 리스트의 첫 노드, prev: 새 리스트의 끝 노드를 가리키는 포인터
    //newHead에 노드들을 정렬시키며 연결해 L1의 head로 만드는 식으로 L2를 L1에 합병시킨다.

    while (L1->head && L2->head)
    {
        node_ptr tmp=NULL;
        if (L1->head->elem < L2->head->elem)
        {
            //각 리스트의 첫 노드의 원소를 비교해 작은 것을 떼어낸다.
            tmp = L1->head;
            L1->head = L1->head->next;
            tmp->next = NULL;
        }
        else
        {
            tmp = L2->head;
            L2->head = L2->head->next;
            tmp->next = NULL;
        }

        if (newHead==NULL)
        {
            newHead = tmp;
            prev = newHead;
        }
        else
        {
            prev->next = tmp;
            prev = prev->next;
        }
    }

    //한쪽 리스트의 노드가 존재하지 않게 될 시 남은 리스트의 노드를 L에 연결
    while (L1->head)
    {
        prev->next = L1->head;
        L1->head = NULL;
    }
    
    while (L2->head)
    {
        prev->next = L2->head;
        L2->head = NULL;
    }

    L1->head=newHead;
    freeList(L2);
}

void mergeSort(List L)
{
    if (L->count > 1){
        List L2 = partition(L, L->count / 2);
        mergeSort(L);
        mergeSort(L2);
        merge(L, L2);
    }
}