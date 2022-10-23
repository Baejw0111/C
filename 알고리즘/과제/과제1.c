#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *buildList(int n, int min, int max);

//인자는 포인터 2개. 두 포인터에 연결된 변수에 저장된 값을 서로 교환한다.
void swap(int *a, int *b);

//새 키의 인덱스 i를 크기에 맞는 위치로 이동
void upHeap(int *L, int i);

//인자는 리스트 포인터와 힙 배열의 인덱스 1개,힙 구조 내 노드 개수. 해당 인덱스의 키 값과 자식 노드들의 키 값을을 비교해 최소값을 가진 노드의 인덱스를 반환한다.
int retMin(int *L, int i, int heapNum);

// maxkey를 배열 가장 뒤쪽으로 보내어 힙 구조에서 해당 노드 제거
int removeMin(int *L, int heapNum);

//힙 구조 정리
void downHeap(int *L, int i, int heapNum);

int findKthSmallest(int *L, int n, int k);

int main()
{
    int *L = buildList(10, 1, 100);

    // write list
    for (int i = 0; i < 10; ++i)
    {
        printf("%d ", L[i]);
    }
    printf("\n");

    // mini test run
    for (int i = 1; i <= 3; ++i)
    {
        printf("%d\n", findKthSmallest(L, 10, i));
    }

    L = buildList(100000, 1, 1000000);

    int k[4] = {1, 100, 99900, 99999};
    int ans[4] = {0};
    clock_t start, finish;

    // main test run
    for (int i = 0; i < 4; ++i)
    {
        start = clock();
        ans[i] = findKthSmallest(L, 100000, k[i]);
        finish = clock();

        printf("result(k=%d): %d || execution time: %dms\n", k[i], ans[i], finish - start);
    }

    free(L);
    return 0;
}

int *buildList(int n, int min, int max)
{
    srand(time(NULL));

    int *L = NULL;
    L = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i)
    {
        L[i] = min + rand() % (max - min);
        upHeap(L,i);
    }

    return L;
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void upHeap(int *L, int i)
{
    if (i == 0 || L[(i - 1) / 2] <= L[i])
    {
        return;
    }
    else
    {
        swap(L + (i - 1) / 2, L + i);
        upHeap(L, (i - 1) / 2);
    }

    return;
}

int retMin(int *L, int i, int heapNum)
{
    int ret;                                 //반환할 값
    int left = 2 * i + 1, right = 2 * i + 2; //왼쪽 자식 노드, 오른쪽 자식 노드
    if (L[i] < L[left])
    {
        ret = i;
    }
    else
    {
        ret = left;
    }

    if (right < heapNum)
    {
        if (L[ret] > L[right])
        {
            ret = right;
        }
    }

    return ret;
}

int removeMin(int *L, int heapNum)
{
    int minKey = L[0];
    L[0] = L[heapNum - 1];
    L[heapNum - 1] = minKey;
    heapNum -= 1;
    downHeap(L, 0, heapNum);
}

void downHeap(int *L, int i, int heapNum)
{
    if (2 * i + 1 >= heapNum)
    {
        return;
    }
    int minIndex = retMin(L, i, heapNum);

    if (L[i] == L[minIndex])
    {
        return;
    }
    else
    {
        swap(L + i, L + minIndex);
        downHeap(L, minIndex, heapNum);
    }

    return;
}

int findKthSmallest(int *L, int n, int k)
{
    //힙 구조 형태의 L을 여기에 복사 (시간 복잡도: O(n))
    int *heapifiedList = NULL;
    heapifiedList = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i)
    {
        heapifiedList[i] = L[i];
    }

    int heapNum = n;
    //시간 복잡도: O(klogn)
    for (int i = 0; i < k; ++i)
    {
        removeMin(heapifiedList, heapNum);
        --heapNum;
    }

    int ret = heapifiedList[n - k];
    free(heapifiedList);

    return ret;
}