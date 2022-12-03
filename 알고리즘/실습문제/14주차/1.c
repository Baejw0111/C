#include <stdio.h>
#include <stdlib.h>

#define MAX 30000

typedef struct
{
    int *queue;
    int rear, front;
} que;

// 아직 방문하지 않은 노드를 저장할 우선순위큐
que vertice;
int n, m, s;
// dist는 출발 노드로부터 각 노드까지의 최단 거리를 저장할 배열이다. graph는 그래프의 간선들의 정보를 저장할 인접 행렬이다.
int *dist, **graph;

// 큐 초기화
void que_init();
// 큐 끝에 원소 삽입
void que_insert(int v);
// 큐 앞의 원소 삭제
int que_delete();
// 큐가 비어있는지 확인
int que_isempty();

// 초기화
void Init();
// 간선 정보 입력
void ScanEdge();
// vertice 내의 두 원소의 위치 교환
void Swap(int *a, int *b);
// vertice까지의 최단 거리를 기준으로 오름차순으로 배열
void QuickSort(int left, int right);
// Dijkstra 알고리즘
void Dijkstra();
// 메모리 할당 해제
void FreeMemory();

int main()
{
    scanf("%d %d %d", &n, &m, &s);
    que_init();
    Init();
    ScanEdge();
    QuickSort(0, n);
    Dijkstra();
    FreeMemory();
    return 0;
}

void que_init()
{
    vertice.queue = (int *)calloc(n, sizeof(int));
    vertice.front = -1;
    vertice.rear = -1;
}

void que_insert(int v)
{
    vertice.queue[++vertice.rear] = v;
}

int que_delete()
{
    return vertice.queue[++vertice.front];
}

int que_isempty()
{
    if (vertice.rear == vertice.front)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Init()
{
    // 각 정점의 번호가 1부터 시작하므로 편의를 위해 index 0은 사용하지 않는다.
    graph = (int **)calloc(n + 1, sizeof(int *));
    dist = (int *)calloc(n + 1, sizeof(int));

    // 배열 초기화
    for (int i = 0; i < n + 1; ++i)
    {
        graph[i] = (int *)calloc(n + 1, sizeof(int));
        for (int j = 0; j < n + 1; ++j)
        {
            graph[i][j] = 0;
        }
        dist[i] = MAX;
    }

    dist[s] = 0;

    for (int i = 1; i <= n; ++i)
    {
        que_insert(i);
    }

    QuickSort(vertice.front + 1, vertice.rear + 1);
}

void ScanEdge()
{
    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = graph[v][u] = w;
    }
}

void Swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void QuickSort(int left, int right)
{
    if (left < right) // 해당 조건 불만족 시 재귀 종료
    {
        int *pivot = vertice.queue + left;
        int i = left, j = right;

        do
        {
            // pivot 간선의 무게보다 큰 무게를 가진 간선 찾기
            do
            {
                i++;
            } while (i < right && dist[vertice.queue[i]] < dist[*pivot]);

            // pivot 간선의 무게보다 작은 무게를 가진 간선 찾기
            do
            {
                j--;
            } while (dist[vertice.queue[j]] > dist[*pivot]);

            if (i < j)
            {
                Swap(vertice.queue + i, vertice.queue + j);
            }

        } while (i < j);

        Swap(vertice.queue + j, pivot);
        QuickSort(left, j);
        QuickSort(j + 1, right);
    }
}

void Dijkstra()
{
    while (!que_isempty())
    {
        int cur_node = que_delete();

        // printf("cur_node: %d // dist: %d\n",cur_node,dist[cur_node]);

        for (int i = 1; i <= n; ++i)
        {
            if (graph[cur_node][i] > 0)
            {
                if (dist[cur_node] + graph[cur_node][i] < dist[i])
                {
                    dist[i] = dist[cur_node] + graph[cur_node][i];
                    // printf("changed node: %d // dist: %d\n",i,dist[i]);
                }
            }
        }
        // printf("\n");
        QuickSort(vertice.front + 1, vertice.rear + 1);
    }

    for (int i = 1; i <= n; ++i)
    {
        if (i == s || dist[i] == MAX)
        {
            continue;
        }
        printf("%d %d\n", i, dist[i]);
    }
}

void FreeMemory()
{
    for (int i = 0; i < n + 1; ++i)
    {
        free(graph[i]);
    }
    free(dist);
    free(vertice.queue);
}