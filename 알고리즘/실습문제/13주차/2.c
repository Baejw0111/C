#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int u, v, w;
} edge;

typedef struct
{
    edge *queue;
    int rear, front;
} que;

// 간선 정보를 저장할 우선순위큐
que edgeQueue;
// total은 MST의 총 무게를 저장할 변수다.
int n, m, total = 0;
// bagNum은 각 노드별로 어떤 bag에 들어가 있는지를 나타내는 배열이다.
int *bagNum;

// 큐 초기화
void que_init();
// 큐 끝에 원소 삽입
void que_insert(int u, int v, int w);
// 큐 앞의 원소 삭제
edge que_delete();

// 초기화
void Init();
// 간선 정보 입력
void ScanEdge();
// edgeQueue 내의 두 원소의 위치 교환
void Swap(edge *a, edge *b);
// edgeQueue을 무게를 기준으로 오름차순으로 배열
void QuickSort(edge *arr, int left, int right);
// 정점의 현재 소속 반환
int FindRoot(int num);
// Kruskal 알고리즘
void Kruskal();
// 메모리 할당 해제
void FreeMemory();

int main()
{
    scanf("%d %d", &n, &m);
    Init();
    que_init();
    ScanEdge();
    QuickSort(edgeQueue.queue, 0, m);
    Kruskal();
    FreeMemory();
    return 0;
}

void que_init()
{
    edgeQueue.queue = (edge *)calloc(m, sizeof(edge));
    edgeQueue.front = -1;
    edgeQueue.rear = -1;
}

void que_insert(int u, int v, int w)
{
    edge new = {u, v, w};
    edgeQueue.queue[++edgeQueue.rear] = new;
}

edge que_delete()
{
    return edgeQueue.queue[++edgeQueue.front];
}

void Init()
{
    // 각 정점의 번호가 1부터 시작하므로 편의를 위해 index 0은 사용하지 않는다.
    bagNum = (int *)calloc(n + 1, sizeof(int));

    // 배열 초기화
    for (int i = 0; i < n + 1; ++i)
    {
        bagNum[i] = i;
    }
}

void ScanEdge()
{
    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        que_insert(u, v, w);
    }
}

void Swap(edge *a, edge *b)
{
    edge tmp = *a;
    *a = *b;
    *b = tmp;
}

void QuickSort(edge *arr, int left, int right)
{
    if (left < right) // 해당 조건 불만족 시 재귀 종료
    {
        edge *pivot = arr + left;
        int i = left, j = right;

        do
        {
            // pivot 간선의 무게보다 큰 무게를 가진 간선 찾기
            do
            {
                i++;
            } while (i < right && arr[i].w < (*pivot).w);

            // pivot 간선의 무게보다 작은 무게를 가진 간선 찾기
            do
            {
                j--;
            } while (arr[j].w > (*pivot).w);

            if (i < j)
            {
                Swap(arr + i, arr + j);
            }

        } while (i < j);

        Swap(arr + j, pivot);
        QuickSort(arr, left, j);
        QuickSort(arr, j + 1, right);
    }
}

int FindRoot(int num)
{
    if (bagNum[num] != num)
    {
        FindRoot(bagNum[num]);
    }
    else
    {
        return num;
    }
}

void Kruskal()
{
    for (int i = 0; i < n - 1; ++i)
    {
        edge newEdge;
        int u, v, w;

        do
        {
            newEdge = que_delete();
            u = newEdge.u;
            v = newEdge.v;
            w = newEdge.w;
        } while (FindRoot(u) == FindRoot(v));

        if (FindRoot(u) < FindRoot(v))
        {
            bagNum[FindRoot(v)] = FindRoot(u);
        }
        else
        {
            bagNum[FindRoot(u)] = FindRoot(v);
        }

        total += w;
        printf(" %d", w);
    }

    printf("\n%d", total);
}

void FreeMemory()
{
    free(bagNum);
    free(edgeQueue.queue);
}