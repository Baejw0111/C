#include <stdio.h>
#include <stdlib.h>

int **graph;

//간선 추가하는 함수
void add_edge(int node_num, int adjacent_node, int weight);
//그래프 초기화
void init_graph();
//노드에 인접한 노드들의 정보 출력
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
    graph[node_num][adjacent_node]=weight;
}

void init_graph()
{
    graph = NULL;
    //각 정점의 번호가 1부터 시작하므로 편의를 위해 index 0은 사용하지 않는다.
    graph = (int**)calloc(7, sizeof(int*));

    for (int i = 0; i < 7; ++i)
    {
        graph[i]=(int*)calloc(7,sizeof(int));
        for(int j=0;j<7;++j){
            graph[i][j]=0;
        }
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

    for(int i=1;i<7;++i){
        if(graph[node_num][i]!=0){
            printf(" %d %d",i,graph[node_num][i]);
        }
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

    add_edge(a,b,w);
    add_edge(b,a,w);
}

void free_graph()
{
    for (int i = 0; i < 7; ++i)
    {
        free(graph[i]);
    }

    free(graph);
}