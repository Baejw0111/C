#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *queue;
    int rear, front;
} que;

que q;
int n, m, s;
int **graph, *visited;

// 큐 초기화
void que_init();
// 큐가 비어있는 지 검사
int que_isempty();
// 큐 끝에 원소 삽입
void que_insert(int item);
// 큐 앞의 원소 삭제
int que_delete();

// 간선 추가하는 함수
void add_edge(int node_num, int adjacent_node);
// 그래프 초기화
void init_graph();
// 그래프 할당 해제
void free_graph();

void BFS();

int main()
{
    scanf("%d %d %d", &n, &m, &s);
    que_init();
    init_graph();
    BFS();

    free_graph();
    free(visited);

    return 0;
}

void que_init()
{
    q.queue = (int *)calloc(n, sizeof(int));
    q.front = -1;
    q.rear = -1;
}

int que_isempty()
{
    if (q.rear == q.front)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void que_insert(int item)
{
    q.queue[++q.rear] = item;
}

int que_delete()
{
    return q.queue[++q.front];
}

void add_edge(int node_num, int adjacent_node)
{
    graph[node_num][adjacent_node] = 1;
}

void init_graph()
{
    graph = NULL;
    // 각 정점의 번호가 1부터 시작하므로 편의를 위해 index 0은 사용하지 않는다.
    graph = (int **)calloc(n + 1, sizeof(int *));
    visited = (int *)calloc(n + 1, sizeof(int));

    for (int i = 0; i < n + 1; ++i)
    {
        graph[i] = (int *)calloc(n + 1, sizeof(int));
        for (int j = 0; j < n + 1; ++j)
        {
            graph[i][j] = 0;
        }
        visited[i] = 0;
    }

    for (int i = 0; i < m; ++i)
    {
        // 간선의 양 끝 정점 번호
        int a, b;
        scanf("%d %d", &a, &b);

        add_edge(a, b);
        add_edge(b, a);
    }
}

void free_graph()
{
    for (int i = 0; i < n + 1; ++i)
    {
        free(graph[i]);
    }

    free(graph);
}

void BFS()
{
    que_insert(s);
    visited[s] = 1;

    while (!que_isempty())
    {
        int node = que_delete();
        printf("%d\n", node);

        for (int i = 1; i < n + 1; ++i)
        {
            // 인접 노드인 동시에 방문하지 않은 노드일 경우 큐에 넣는다.
            if (graph[node][i] && !visited[i])
            {
                que_insert(i);
                visited[i] = 1;
            }
        }
    }
}