#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "D:\OneDrive\Coding\C\Data Structure\DS.h"

//------------------------------구조체 선언 및 기본 함수------------------------------

typedef struct
{
    int *queue;
    int size, rear, front;
} que;

typedef struct
{
    int *stack;
    int size, top;
} stk;

int *array_init(int n) //정수형 배열 만드는 함수
{
    int *a = NULL;
    a = (int *)calloc(n, sizeof(int));

    return a;
}

//------------------------------sort(정렬)------------------------------
//모든 정렬은 오름차순으로 이뤄진다.

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubble_sort(int n, int *a) //개선된 버블 정렬
{
    int s = 1; //각 단계에서 데이터 이동이 이뤄지지 않을 시 함수 종료

    for (int *i = a + n - 1; s; i--)
    {
        s = 0;
        for (int *j = a; j < i; j++)
        {
            if (*j > *(j + 1))
            {
                swap(j, j + 1);
                s = 1;
            }
        }
    }
}

void selection_sort(int n, int *a) //정수형 배열 선택 정렬
{
    for (int i = 0; i < n; i++)
    {
        int min = i; //가장 작은 값을 가진 인덱스
        for (int j = i; j < n; j++)
        {
            if (a[j] < a[min])
            {
                min = j;
            }
        }
        swap(a + i, a + min);
    }
}

void insertion_sort(int *a, int length) //삽입 정렬
{
    for (int i = 1; i < length; i++)
    {
        for (int j = i - 1; j >= 0 && a[j] > a[j + 1]; --j)
        {
            swap(a + j, a + j + 1);
        }
    }
}

void quick_sort(int *a, int left, int right) //퀵 정렬
{
    if (left < right) //해당 조건 불만족 시 재귀 종료
    {
        int *pivot = a + left, i = left, j = right;

        do
        {
            // pivot값보다 큰 수 찾기
            do
            {
                i++;
            } while (i < right && a[i] < *pivot);

            // pivot값보다 작은 수 찾기
            do
            {
                j--;
            } while (a[j] > *pivot);

            if (i < j)
            {
                swap(a + i, a + j);
            }

        } while (i < j);
        swap(a + j, pivot);
        quick_sort(a, left, j);
        quick_sort(a, j + 1, right);
    }
}

void random_quick_sort(int *a, int left, int right) //랜덤 함수 사용하는 퀵 정렬. 단 주의할 점은 첫 시작 때 전체 원소 개수를 right에 집어넣으면 안된다.
{
    if (left < right) //해당 조건 불만족 시 재귀 종료
    {
        srand(time(NULL));
        int k = left + rand() % (right - left);

        int pivot = a[k], i = left, j = right;

        do
        {
            while (a[i] < pivot)
            {
                ++i;
            }

            while (a[j] > pivot)
            {
                --j;
            }

            if (i <= j)
            {
                swap(a + i, a + j);
                ++i;
                --j;
            }

        } while (i < j);

        random_quick_sort(a, left, j);
        random_quick_sort(a, i, right);
    }
}

void heap_adjust(int n, int *a, int s) //힙 재조정. s는 노드 인덱스 값으로, 해당 노드가 내려가는 걸 계속 추적하며 반복한다.
{
    while (s < n)
    {
        int r = s;
        int left = 2 * s + 1, right = 2 * s + 2;
        if (left >= n && right >= n)
        {
            break;
        }

        if (right < n)
        {
            if (*(a + left) > *(a + right))
            {
                if (*(a + left) > *(a + s))
                {
                    swap(a + s, a + left);
                    s = left;
                }
            }
            else
            {
                if (*(a + right) > *(a + s))
                {
                    swap(a + s, a + right);
                    s = right;
                }
            }
        }
        else
        {
            if (*(a + left) > *(a + s))
            {
                swap(a + s, a + left);
                s = left;
            }
        }
        if (s == r)
        {
            break;
        }
    }
}

void heap_sort(int n, int *a)
{
    for (int i = n / 2; i >= 0; i--)
    {
        heap_adjust(n, a, i);
    }

    for (int i = n - 1; i > 0; i--)
    {
        swap(a, a + i);
        heap_adjust(i, a, 0);
    }
}

//------------------------------search(검색)------------------------------
void sequential_search(int size, int n, int *a) //선형 검색 함수.size는 받은 배열 a의 크기, n은 찾는 수
{
    for (int i = 0; i < size; i++)
    {
        if (a[i] == n)
        {
            printf("index: %d\n", i);
        }
    }
}

void binary_search(int n, int *a, int start, int end) //이진 탐색 함수.n이 찾는 수이다.이미 정렬된 리스트에서만 제대로 탐색할 수 있다.start는 왼쪽 끝 인덱스, end는 오른쪽 끝 인덱스이다.
{
    int mid = (end + start) / 2;
    if (start == end)
    {
        if (a[mid] == n)
        {
            printf("index: %d\n", mid);
        }

        else
        {
            printf("찾지 못함\n");
        }
        return;
    }

    if (a[mid] > n)
    {
        binary_search(n, a, start, mid - 1);
    }
    else if (a[mid] < n)
    {
        binary_search(n, a, mid + 1, end);
    }
    else
    {
        printf("index: %d\n", mid);
    }
}

//------------------------------스택------------------------------
void stk_init(stk *s, int size)
{ //스택 자료형 초기화 함수
    s->size = size;
    s->stack = array_init(s->size);
    s->top = -1;
}

int stk_isempty(stk s)
{ //비어있는 지 검사
    if (s.top < 0)
    {
        printf("stack is empty now\n");
        return 1;
    }
    else
    {
        return 0;
    }
}

int stk_isfull(stk s)
{ //가득 차 있는 지 검사
    if (s.top >= s.size - 1)
    {
        printf("stack is full now\n");
        return 1;
    }
    else
    {
        return 0;
    }
}

//스택에서 삽입과 삭제 모두 스택 맨 뒤에서 이뤄진다.
void stk_push(stk *s, int item)
{ //삽입
    if (stk_isfull(*s))
    {
        return;
    }
    s->stack[++s->top] = item;
}

int stk_pop(stk *s)
{ //삭제
    if (s->top == -1)
    {
        return stk_isempty(*s);
    }
    return s->stack[s->top--];
}

void stk_print(stk s)
{ //출력
    printf("present stack:");
    for (int i = 0; i < s.top + 1; i++)
    {
        printf("%d ", s.stack[i]);
    }
    printf("\n");
}

//------------------------------큐------------------------------
void que_init(que *q, int size)
{ //큐 자료형 초기화 함수
    q->size = size;
    q->queue = array_init(q->size);
    q->front = -1;
    q->rear = -1;
}

int que_isempty(que q)
{ //비어있는 지 검사
    if (q.rear == q.front)
    {
        printf("queue is empty now\n");
        return 1;
    }
    else
    {
        return 0;
    }
}

int que_isfull(que q)
{ //가득 차 있는 지 검사
    //큐가 가득 찼다는 건 front 값이 얼마이건 간에 배열이 꽉 차 있다는 것이 된다.
    //즉 삽입과 삭제를 반복하다보면 isfull과 isempty가 둘다 1인 경우가 발생한다.
    if (q.rear >= q.size - 1)
    {
        printf("queue is full now\n");
        return 1;
    }
    else
    {
        return 0;
    }
}

//큐에서 삽입은 끝, 삭제는 맨 앞에서 이뤄진다.
void que_insert(que *q, int item)
{ //삽입(enqueue)
    if (que_isfull(*q))
    {
        return;
    }
    q->queue[++q->rear] = item;
}

int que_delete(que *q)
{ //삭제(dequeue)
    if (q->rear == q->front)
    {
        return que_isempty(*q);
    }
    return q->queue[++q->front]; // front값이 (첫 원소 위치-1)
}

void que_print(que q)
{ //출력
    printf("present queue:");
    for (int j = q.front + 1; j <= q.rear; j++)
    {
        printf("%d ", q.queue[j]);
    }
    printf("\n");
}

//------------------------------원형 큐------------------------------
void cque_init(que *q, int size)
{ //원형 큐 자료형 초기화 함수
    q->size = size + 1;
    q->queue = array_init(q->size);
    q->front = 0;
    q->rear = 0;
}

int cque_isfull(que q)
{
    if ((q.rear + 1) % q.size == q.front)
    {
        printf("queue is full now\n");
        return 1;
    }
    else
    {
        return 0;
    }
}

void cque_insert(que *q, int item)
{ //삽입(enqueue)
    if (cque_isfull(*q))
    {
        return;
    }
    q->queue[(++q->rear) % q->size] = item;
}

int cque_delete(que *q)
{ //삭제(dequeue)
    if (q->rear == q->front)
    {
        return que_isempty(*q);
    }
    return q->queue[(++q->front) % q->size];
}

void cque_print(que q)
{ //출력
    printf("present queue:");
    for (int j = q.front + 1; j <= q.rear; j++)
    {
        printf("%d ", q.queue[j % q.size]);
    }
    printf("\n");
}