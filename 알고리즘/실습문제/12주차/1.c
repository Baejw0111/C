#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *queue;
    int rear, front;
} que;

que q;
int n, m;
// vertexName: 각 정점들의 이름을 저장할 배열
// ans: 위상 순서를 저장할 배열
char *vertexName, *ans;
// inCount: 각 정점의 진입 차수를 저장할 배열
// outCount: 각 정점의 진출 차수를 저장할 배열
int **graph, *inCount, *outCount;

// 큐 초기화
void que_init();
// 큐가 비어있는 지 검사
int que_isempty();
// 큐 끝에 원소 삽입
void que_insert(int item);
// 큐 앞의 원소 삭제
int que_delete();

//정점들의 이름을 입력받는 함수
void init_vertex();
//간선들의 정보를 저장하는 함수
void add_edge(char node_name, char adjacent_node_name);
// 그래프 초기화
void init_graph();
// 메모리 할당 해제
void free_memory();

void topologicalSort();

int main()
{
    scanf("%d", &n);
    init_vertex();
    que_init();
    init_graph();
    topologicalSort();

    free_memory();

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

void init_vertex()
{
    vertexName = (char *)calloc(n, sizeof(char));

    for (int i = 0; i < n; ++i)
    {
        getchar();
        scanf("%c", vertexName + i);
    }
}

void add_edge(char node_name, char adjacent_node_name)
{
    int node_num = -1, adjacent_node_num = -1;
    for (int i = 0; i < n; ++i)
    {
        if (node_name == vertexName[i])
        {
            node_num = i;
        }
        else if (adjacent_node_name == vertexName[i])
        {
            adjacent_node_num = i;
        }

        if (node_num != -1 && adjacent_node_num != -1)
        {
            break;
        }
    }

    //간선 추가하는 동시에 진입차수, 진출차수 갱신
    graph[node_num][outCount[node_num]] = adjacent_node_num;
    inCount[adjacent_node_num] += 1;
    outCount[node_num] += 1;
}

void init_graph()
{
    ans = (char *)calloc(n, sizeof(char));
    inCount = (int *)calloc(n, sizeof(int));
    outCount = (int *)calloc(n, sizeof(int));
    graph = (int **)calloc(n, sizeof(int *));

    //각 배열 초기화
    for (int i = 0; i < n; ++i)
    {
        graph[i] = (int *)calloc(n, sizeof(int));
        for (int j = 0; j < n; ++j)
        {
            graph[i][j] = 0;
        }
        inCount[i] = 0;
        outCount[i] = 0;
    }

    scanf("%d", &m);

    for (int i = 0; i < m; ++i)
    {
        // 간선 정보
        char a, b;
        getchar();
        scanf("%c %c", &a, &b);

        add_edge(a, b);
    }
}

void free_memory()
{
    for (int i = 0; i < n; ++i)
    {
        free(graph[i]);
    }

    free(graph);
    free(vertexName);
    free(ans);
    free(inCount);
    free(outCount);
}

void topologicalSort()
{
    //정점 번호 순서대로 진입 간선 개수가 0인 정점 찾기
    for (int i = 0; i < n; ++i)
    {
        if (inCount[i] == 0)
        {
            que_insert(i);
        }
    }

    //위상 순서 배열에 저장된 원소들의 개수 카운트
    int order = 0;

    while (!que_isempty())
    {
        int cur_node = que_delete();
        ans[order] = vertexName[cur_node];
        order += 1;

        //각 정점에 가장 최근에 진출 간선으로 연결된 정점부터 조사
        for (int i = outCount[cur_node] - 1; i >= 0; --i)
        {
            int opp_node = graph[cur_node][i];

            if (inCount[opp_node] > 0)
            {
                inCount[opp_node] -= 1;
                if (inCount[opp_node] == 0)
                {
                    que_insert(opp_node);
                }
            }
        }
    }

    //뱡향 사이클 존재할 경우 0 출력
    if (order < n)
    {
        printf("0\n");
    }
    else
    {
        for (int i = 0; i < n; ++i)
        {
            printf("%c ", ans[i]);
        }
    }
}