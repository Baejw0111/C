#include <stdio.h>
#include <stdlib.h>

typedef struct edge
{
    //간선을 통해 연결되는 노드의 번호
    int adjacent_node_num;
    //가중치
    int weight;
    //다음 간선
    struct edge *next;
} edge;

typedef edge *edge_ptr;

edge_ptr graph;

//간선 추가하는 함수
void add_edge(int node_num, int adjacent_node, int weight);
//간선 삭제하는 함수
void delete_edge(int node_num, int adjacent_node);
//그래프 초기화
void init_graph();
//노드에 인접한 노드의 정보 출력
void print_adjacent(int node_num);
//간선 정보 수정
void modify(int a, int b, int w);
//그래프 할당 해제
void free_graph();

int main()
{
    int s = 1, num, a, b, w;
    char mode;

    init_graph();

    while (s)
    {
        scanf("%c", &mode);

        switch (mode)
        {
        case 'a':
            scanf("%d", &num);
            getchar();
            print_adjacent(num);
            break;

        case 'm':
            scanf("%d %d %d", &a, &b, &w);
            getchar();
            modify(a, b, w);
            break;

        case 'q':
            s = 0;
            break;
        }
    }
    return 0;
}

void add_edge(int node_num, int adjacent_node, int weight)
{
    edge_ptr pointer = graph + node_num;
    edge_ptr new_edge = (edge_ptr)calloc(1, sizeof(edge));

    new_edge->adjacent_node_num = adjacent_node;
    new_edge->weight = weight;

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

void delete_edge(int node_num, int adjacent_node)
{
    edge_ptr pointer = graph[node_num].next, prev = graph + node_num;

    //어짜피 간선이 존재할 경우에만 쓰일 함수이므로 조건문은 다음과 같다.
    while (pointer->adjacent_node_num != adjacent_node)
    {
        prev = prev->next;
        pointer = pointer->next;
    }

    prev->next = pointer->next;
    free(pointer);
}

void init_graph()
{
    graph = NULL;
    //각 정점의 번호가 1부터 시작하므로 편의를 위해 index 0은 사용하지 않는다.
    graph = (edge_ptr)calloc(7, sizeof(edge));

    for (int i = 0; i < 7; ++i)
    {
        graph[i].next = NULL;
    }

    add_edge(1, 2, 1);
    add_edge(1, 3, 1);
    add_edge(1, 4, 1);
    add_edge(1, 6, 2);

    add_edge(2, 1, 1);
    add_edge(2, 3, 1);

    add_edge(3, 1, 1);
    add_edge(3, 2, 1);
    add_edge(3, 5, 4);

    add_edge(4, 1, 1);

    add_edge(5, 3, 4);
    add_edge(5, 5, 4);
    add_edge(5, 6, 3);

    add_edge(6, 1, 2);
    add_edge(6, 5, 3);
}

void print_adjacent(int node_num)
{
    if (node_num < 1 || node_num > 6)
    {
        printf("-1\n");
        return;
    }

    for (edge_ptr pointer = graph[node_num].next; pointer != NULL; pointer = pointer->next)
    {
        printf(" %d %d", pointer->adjacent_node_num, pointer->weight);
    }
    printf("\n");
}

void modify(int a, int b, int w)
{
    if (a < 1 || a > 6 || b < 1 || b > 6)
    {
        printf("-1\n");
        return;
    }

    //간선 (a,b)의 존재 여부
    int find = 0;

    edge_ptr pointer = graph[a].next;

    //간선 (a,b) 찾기
    while (pointer)
    {
        //존재할 경우 간선 삭제 또는 가중치 수정
        if (pointer->adjacent_node_num == b)
        {
            if (w == 0)
            {
                delete_edge(a, b);
                //루프의 경우도 고려해야 한다.
                if (a != b)
                {
                    delete_edge(b, a);
                }

                return;
            }
            else
            {
                pointer->weight = w;
                if (a == b)
                {
                    return;
                }
                find = 1;

                break;
            }
        }
        else if (pointer->adjacent_node_num > b)
        {
            break;
        }

        pointer = pointer->next;
    }

    //간선 (a,b)가 존재하지 않고 w는 0이 아닐 경우
    if (!find)
    {
        add_edge(a, b, w);

        if (a != b)
        {
            add_edge(b, a, w);
        }

        return;
    }

    //간선 (a,b)가 존재하고 루프가 아닐 경우
    pointer = graph[b].next;

    while (pointer)
    {
        if (pointer->adjacent_node_num == a)
        {
            pointer->weight = w;
            break;
        }

        pointer = pointer->next;
    }
}

void free_graph()
{
    for (int i = 1; i < 7; ++i)
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