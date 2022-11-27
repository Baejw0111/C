#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int u, v, cost;
} edge;

// 간선 정보를 저장할 배열
edge *bag;
// bagNum은 현재 bag에 들어있는 간선의 개수, total은 MST의 총 무게를 저장할 변수다.
int n, m, bagNum = 0, total = 0;
// graph는 그래프의 인접행렬, visited는 정점이 현재 MST에 포함되었는지의 여부를 저장한다.
int **graph, *visited;

// 초기화
void Init();
// 간선 정보 입력
void ScanEdge();
// bag 내의 두 원소의 위치 교환
void Swap(edge *a, edge *b);
// bag을 무게를 기준으로 오름차순으로 배열
void QuickSort(int left, int right);
// 간선 정보 bag에 넣기
void InsertEdge(int u, int v);
// bag으로부터 무게가 가장 작은 간선 제거해 반환
edge DeleteEdge();
// Prim-Jarnik 알고리즘
void Prim();
// 메모리 할당 해제
void FreeMemory();
// bag의 현재 상태 출력
//  void BagStatus();

int main()
{
    scanf("%d %d", &n, &m);
    Init();
    ScanEdge();
    Prim();
    return 0;
}

void Init()
{
    // 각 정점의 번호가 1부터 시작하므로 그래프와 관련된 배열은 편의를 위해 index 0은 사용하지 않는다.
    graph = (int **)calloc(n + 1, sizeof(int *));
    visited = (int *)calloc(n + 1, sizeof(int));
    bag = (edge *)calloc(m, sizeof(edge));

    // 각 배열 초기화
    for (int i = 0; i < n + 1; ++i)
    {
        graph[i] = (int *)calloc(n + 1, sizeof(int));
        for (int j = 0; j < n + 1; ++j)
        {
            graph[i][j] = 0;
        }
        visited[i] = 0;
    }
}

void ScanEdge()
{
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        scanf("%d", &graph[u][v]);
        graph[v][u] = graph[u][v];
    }
}

void Swap(edge *a, edge *b)
{
    edge tmp = *a;
    *a = *b;
    *b = tmp;
}

void QuickSort(int left, int right)
{
    if (left < right) // 해당 조건 불만족 시 재귀 종료
    {
        edge *pivot = bag + left;
        int i = left, j = right;

        do
        {
            // pivot 간선의 무게보다 큰 무게를 가진 간선 찾기
            do
            {
                i++;
            } while (i < right && bag[i].cost < (*pivot).cost);

            // pivot 간선의 무게보다 작은 무게를 가진 간선 찾기
            do
            {
                j--;
            } while (bag[j].cost > (*pivot).cost);

            if (i < j)
            {
                Swap(bag + i, bag + j);
            }

        } while (i < j);

        Swap(bag + j, pivot);
        QuickSort(left, j);
        QuickSort(j + 1, right);
    }
}

void InsertEdge(int u, int v)
{
    edge tmp = {u, v, graph[u][v]};
    bag[bagNum++] = tmp;

    // 해당 간선이 이미 bag에 들어가있거나 검토되었다는 것을 나타내기 위해 아래와 같이 바꿈
    graph[u][v] = -1;
    graph[v][u] = -1;

    QuickSort(0, bagNum);
}

edge DeleteEdge()
{
    edge tmp = bag[0];
    Swap(bag, bag + bagNum - 1);
    bagNum -= 1;
    QuickSort(0, bagNum);

    return tmp;
}

void Prim()
{
    int num = 1, curNode = 1;
    visited[1] = 1;
    edge nextEdge;
    printf(" 1");

    for (; num < n; ++num)
    {
        // printf("\ncurNode: %d\n\n",curNode);
        for (int i = 1; i <= n; ++i)
        {
            if (graph[curNode][i] > 0)
            {
                InsertEdge(curNode, i);
            }
        }
        /*
        printf("Insert done!\n");
        BagStatus();
        */

        do
        {
            nextEdge = DeleteEdge();
        } while (visited[nextEdge.u] && visited[nextEdge.v]);
        // 간선의 양 끝 정점이 둘다 MST에 저장되어 있는 경우 해당 간선 버림
        /*
        printf("Delete done!\n");
        BagStatus();
        */

        total += nextEdge.cost;
        if (curNode == nextEdge.v)
        {
            curNode = nextEdge.u;
        }
        else
        {
            curNode = nextEdge.v;
        }
        visited[curNode] = 1;
        printf(" %d", curNode);
    }

    printf("\n%d\n", total);
}

void FreeMemory()
{
    for (int i = 0; i < n + 1; ++i)
    {
        free(graph[i]);
    }
    free(graph);
    free(visited);
    free(bag);
}

/*
void BagStatus(){
    printf("\n**Bag Status**\n");
    for(int i=0;i<bagNum;++i){
        printf("u: %d  v: %d  w: %d\n",bag[i].u,bag[i].v,bag[i].cost);
    }
    printf("\n");
}
*/