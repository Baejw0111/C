#include <stdio.h>
#include <stdlib.h>

typedef struct edge
{
    // 간선을 통해 연결되는 노드의 번호
    int adjacent_node_num;
    // 다음 간선
    struct edge *next;
} edge;

typedef edge *edge_ptr;

edge_ptr graph;
int n, m, s;
int *visited;

// 간선 추가하는 함수
void add_edge(int node_num, int adjacent_node);
// 그래프 초기화
void init_graph();
void DFS(int node_num);
// 그래프 할당 해제
void free_graph();

int main()
{
    scanf("%d %d %d", &n, &m, &s);
    init_graph();
    DFS(s);

    free_graph();
    free(visited);
    return 0;
}

void add_edge(int node_num, int adjacent_node)
{
    edge_ptr pointer = graph + node_num;
    edge_ptr new_edge = (edge_ptr)calloc(1, sizeof(edge));

    new_edge->adjacent_node_num = adjacent_node;

    while (pointer->next)
    {
        // node number를 오름차순으로 정렬하기 위한 조건문
        if (pointer->next->adjacent_node_num > adjacent_node)
        {
            break;
        }
        pointer = pointer->next;
    }

    new_edge->next = pointer->next;
    pointer->next = new_edge;
}

void init_graph()
{
    graph = NULL;
    // 각 정점의 번호가 1부터 시작하므로 편의를 위해 index 0은 사용하지 않는다.
    graph = (edge_ptr)calloc(n + 1, sizeof(edge));
    visited = (int *)calloc(n + 1, sizeof(int));

    for (int i = 0; i < n + 1; ++i)
    {
        graph[i].next = NULL;
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

void DFS(int node_num)
{
    visited[node_num] = 1;
    printf("%d\n", node_num);

    for (edge_ptr pointer = graph[node_num].next; pointer != NULL; pointer = pointer->next)
    {
        int next_node = pointer->adjacent_node_num;
        if (!visited[next_node])
        {
            DFS(next_node);
        }
    }
}

void free_graph()
{
    for (int i = 1; i < n + 1; ++i)
    {
        edge_ptr pointer = graph[i].next;

        while (pointer)
        {
            edge_ptr tmp = pointer;
            pointer = pointer->next;

            free(tmp);
            tmp = NULL;
        }
    }

    free(graph);
}