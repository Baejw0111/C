#include <stdio.h>
#include <stdlib.h>

int heap[100] = {0}, n = 0;

int max(int i);
//인자는 힙 배열의 인덱스 1개. 해당 인덱스의 키 값과 자식 노드들의 키 값을을 비교해 최대값을 가진 인덱스를 반환한다.
void swap(int a, int b);
//인자는 힙 배열의 인덱스 2개. 두 인덱스의 키 값을 교환한다.
void insertItem(int key);
int removeMax();
void upHeap(int i);
void downHeap(int i);
void printHeap();

int main()
{
    char mode;
    int key;

    while (1)
    {
        scanf("%c", &mode);
        if (mode == 'q')
        {
            break;
        }
        else
        {
            switch (mode)
            {
            case 'i':
                scanf("%d", &key);
                insertItem(key);
                break;

            case 'd':
                removeMax();
                break;

            case 'p':
                printHeap();
                break;
            }
        }
    }

    return 0;
}

int max(int i)
{
    int ret;                             //반환할 값
    int left = 2 * i, right = 2 * i + 1; //왼쪽 자식 노드, 오른쪽 자식 노드
    if (heap[i] > heap[left])
    {
        ret = i;
    }
    else
    {
        ret = left;
    }

    if (right <= n)
    {
        if (heap[ret] < heap[right])
        {
            ret = right;
        }
    }

    return ret;
}

void swap(int a, int b)
{
    int tmp = heap[a];
    heap[a] = heap[b];
    heap[b] = tmp;
}

void insertItem(int key)
{
    n += 1;
    heap[n] = key;
    upHeap(n);

    printf("0\n");
}

int removeMax()
{
    int maxKey = heap[1];
    heap[1] = heap[n];
    n -= 1;
    downHeap(1);

    printf("%d\n", maxKey);
}

void upHeap(int i)
{
    if (i == 1 || heap[i / 2] >= heap[i])
    {
        return;
    }
    else
    {
        swap(i / 2, i);
        upHeap(i / 2);
    }

    return;
}

void downHeap(int i)
{
    if (2 * i > n)
    {
        return;
    }
    int maxIndex = max(i);

    if (heap[i] == heap[maxIndex])
    {
        return;
    }
    else
    {
        swap(i, maxIndex);
        downHeap(maxIndex);
    }

    return;
}

void printHeap()
{
    for (int i = 1; i <= n; ++i)
    {
        printf(" %d", heap[i]);
    }
    printf("\n");
}