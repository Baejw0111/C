#include <stdio.h>
#include <stdlib.h>

int heap[100] = {0}, n = 0, listNum = 0; // n은 힙의 노드 개수,listNum은 리스트 내 원소의 개수

void swap(int a, int b); //인자는 힙 배열의 인덱스 2개. 두 인덱스의 키 값을 교환한다.
int max(int i);          //인자는 힙 배열의 인덱스 1개. 해당 인덱스의 키 값과 자식 노드들의 키 값을을 비교해 최대값을 가진 노드의 인덱스를 반환한다.
int removeMax();         // maxkey를 배열 가장 뒤쪽으로 보내어 힙 구조에서 해당 노드 제거
void upHeap(int i);      //새키의 인덱스 i를 크기에 맞는 위치로 이동
void downHeap(int i);    //힙 구조 정리
void inPlaceHeapSort();  //힙 구조로 되어 있는 배열의 원소들을 정렬

int main()
{
    scanf("%d", &n);
    listNum = n;

    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", heap + i);
        upHeap(i);
    }

    inPlaceHeapSort();

    for (int i = 1; i <= listNum; ++i)
    {
        printf(" %d", heap[i]);
    }

    return 0;
}

void swap(int a, int b)
{
    int tmp = heap[a];
    heap[a] = heap[b];
    heap[b] = tmp;
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

int removeMax()
{
    int maxKey = heap[1];
    heap[1] = heap[n];
    heap[n] = maxKey;
    n -= 1;
    downHeap(1);
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

void inPlaceHeapSort()
{
    while (n != 1)
    {
        removeMax();
    }
}