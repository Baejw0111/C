#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *queue;
    int rear, front;
} Que;

typedef struct Edge
{
    int v, w;          // v: 간선으로 연결된 반대편 정점, w는 간선의 가중치
    struct Edge *next; // 다음 간선 가리키는 포인터
} Edge;

typedef Edge *EdgePtr;

// n은 정점의 개수, m은 간선의 개수
int n = 6, m = 9;

// 아직 방문하지 않은 정점를 저장할 우선순위큐
Que vertice;

// dist는 출발 정점로부터 각 정점까지의 최단 거리를 저장할 배열이다.
int dist[6] = {0};

// count는 각 정점 별 최단 경로의 수를 저장할 배열이다.
int count[6] = {0};

// graph는 문제에서 주어진 그래프의 정보를 저장할 인접 리스트다.
Edge graph[6];
// int graph[6][6] = {{0, 8, 1, 4, 0, 0},
//                    {8, 0, 7, 0, 4, 0},
//                    {1, 7, 0, 5, 3, 9},
//                    {4, 0, 5, 0, 0, 4},
//                    {0, 4, 3, 0, 0, 0},
//                    {0, 0, 9, 4, 0, 0}};

// 문제에서 주어진 정점쌍
char pair[4][2] = {{'C', 'A'},
                   {'C', 'F'},
                   {'F', 'C'},
                   {'B', 'D'}};

// 큐 초기화
void QueInit();
// 큐 끝에 원소 삽입
void QueInsert(int v);
// 큐 앞의 원소 삭제 및 반환
int QueDelete();
// 큐가 비어있는지 확인
int QueIsEmpty();

// 간선 정보 그래프에 넣기
void InsertEdge(int u, int v, int w);

// 그래프 초기화
void GraphInit();

// 정점 큐 내의 두 원소의 위치 교환
void Swap(int *a, int *b);

// 두 수 a,b를 비교해 b가 더 크면 1, 아니면 0 반환(MAX 값일 경우를 -1로 설정했기 때문에 해당 함수를 따로 만듦)
int Compare(int a, int b);

// 정점 s로부터 각 정점까지의 최단 거리를 기준으로 오름차순으로 배열
void QuickSort(int left, int right);

// Dijkstra 확장 알고리즘
void Dijkstra(EdgePtr graph, int s, int t);

// 그래프에 할당된 메모리 해제
void FreeGraph();

int main()
{
    GraphInit();
    for (int i = 0; i < 4; ++i)
    {
        int s = pair[i][0] - 'A', t = pair[i][1] - 'A';
        Dijkstra(graph, s, t);
    }

    FreeGraph();
    return 0;
}

void QueInit()
{
    vertice.queue = (int *)calloc(n, sizeof(int));
    vertice.front = -1;
    vertice.rear = -1;
}

void QueInsert(int v)
{
    vertice.queue[++vertice.rear] = v;
}

int QueDelete()
{
    return vertice.queue[++vertice.front];
}

int QueIsEmpty()
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

void InsertEdge(int u, int v, int w)
{
    EdgePtr new1 = (EdgePtr)calloc(1, sizeof(Edge));
    new1->next = NULL;
    new1->v = v;
    new1->w = w;

    EdgePtr cur = graph + u;
    while (cur->next)
    {
        cur = cur->next;
    }
    cur->next = new1;

    EdgePtr new2 = (EdgePtr)calloc(1, sizeof(Edge));
    new2->next = NULL;
    new2->v = u;
    new2->w = w;

    cur = graph + v;
    while (cur->next)
    {
        cur = cur->next;
    }
    cur->next = new2;
}

void GraphInit()
{
    for (int i = 0; i < n; ++i)
    {
        graph[i].next = NULL;
    }

    InsertEdge(0, 1, 8);
    InsertEdge(0, 2, 1);
    InsertEdge(0, 3, 4);
    InsertEdge(1, 2, 7);
    InsertEdge(1, 4, 4);
    InsertEdge(2, 3, 5);
    InsertEdge(2, 4, 3);
    InsertEdge(2, 5, 9);
    InsertEdge(3, 5, 4);
}

void Swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int Compare(int a, int b)
{
    if (b != -1)
    {
        if (a == -1)
        {
            return 0;
        }
        else
        {
            return a < b;
        }
    }
    else
    {
        if (a == -1)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
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
            } while (i < right && Compare(dist[vertice.queue[i]], dist[*pivot]));

            // pivot 간선의 무게보다 작은 무게를 가진 간선 찾기
            do
            {
                j--;
            } while (Compare(dist[*pivot], dist[vertice.queue[j]]));

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

void Dijkstra(EdgePtr graph, int s, int t)
{
    // printf("------------------------------------------\n");
    // printf("%d %d\n",s,t);
    QueInit();

    for (int i = 0; i < n; ++i)
    {
        // -1은 MAX 값을 의미한다.
        dist[i] = -1;
        count[i] = 0;
        QueInsert(i);
    }

    dist[s] = 0;
    count[s] = 1;

    QuickSort(0, n);

    while (!QueIsEmpty())
    {
        int cur_node = QueDelete();

        // printf("cur_node: %d // dist: %d // count[%d]: %d\n",cur_node,dist[cur_node],cur_node,count[cur_node]);

        for (EdgePtr next_node = graph[cur_node].next; next_node != NULL; next_node = next_node->next)
        {
            if (Compare(dist[cur_node] + next_node->w, dist[next_node->v]))
            {
                dist[next_node->v] = dist[cur_node] + next_node->w;
                count[next_node->v] = count[cur_node];
                // printf("changed node: %d // dist: %d // count[%d]: %d\n",next_node->v,dist[next_node->v],next_node->v,count[next_node->v]);
            }
            else if (dist[cur_node] + next_node->w == dist[next_node->v])
            {
                // 거리 같을 시 경로 수 갱신
                count[next_node->v] += count[cur_node];
                // printf("changed node: %d // dist: %d // count[%d]: %d\n",next_node->v,dist[next_node->v],next_node->v,count[next_node->v]);
            }
        }
        // printf("\n");

        if (cur_node == t)
        {
            break;
        }
        QuickSort(vertice.front + 1, vertice.rear + 1);
    }

    printf("%c, %c : 최단거리 = %d, 최단경로 수 = %d\n", s + 'A', t + 'A', dist[t], count[t]);

    free(vertice.queue);
}

void FreeGraph()
{
    for (int i = 0; i < n; ++i)
    {
        EdgePtr cur = graph[i].next;
        while (cur)
        {
            EdgePtr tmp = cur;
            cur = cur->next;
            free(tmp);
            tmp = NULL;
        }
    }
}