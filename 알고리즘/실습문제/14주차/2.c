#include <stdio.h>
#include <stdlib.h>

#define MAX 30000

typedef struct
{
    int u, v, w;
} edge;

int n, m, s;
// 출발 정점으로부터 각 정점까지의 최단거리를 저장할 배열
int *dist;
// 간선 정보들을 저장할 배열
edge *edges;

// 초기화
void Init();
// 간선 정보 입력
void ScanEdge();
// BellmanFord 알고리즘
void BellmanFord();
// 메모리 할당 해제
void FreeMemory();

int main()
{
    scanf("%d %d %d", &n, &m, &s);
    Init();
    ScanEdge();
    BellmanFord();
    FreeMemory();
    return 0;
}

void Init()
{
    // 각 정점의 번호가 1부터 시작하므로 편의를 위해 index 0은 사용하지 않는다.
    dist = (int *)calloc(n + 1, sizeof(int));
    edges = (edge *)calloc(m, sizeof(edge));

    // 배열 초기화
    for (int i = 0; i < n + 1; ++i)
    {
        dist[i] = MAX;
    }

    dist[s] = 0;
}

void ScanEdge()
{
    for (int i = 0; i < m; ++i)
    {
        edge new;
        scanf("%d %d %d", &new.u, &new.v, &new.w);
        edges[i] = new;
    }
}

void BellmanFord()
{
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            edge cur_edge = edges[j];
            if (dist[cur_edge.u]!=MAX && dist[cur_edge.u] + cur_edge.w < dist[cur_edge.v])
            {
                dist[cur_edge.v] = dist[cur_edge.u] + cur_edge.w;
            }
        }
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
    free(dist);
    free(edges);
}