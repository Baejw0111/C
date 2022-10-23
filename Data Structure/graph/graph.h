#include "D:\OneDrive\Coding\C\Data Structure\DS.h"
#include <string.h>
#define FALSE 0
#define TRUE 1

//--------------------------그래프 알고리즘 관련 구조체 및 기본 함수들--------------------------
typedef struct node
{
    int vertex;
    struct node *link;
    int cost;
    short int visited;
} node;

typedef node *node_ptr;

typedef struct
{
    int u, v, cost;
} edge;

typedef struct
{
    int root_vertex, root_level; // root_vertex는 해당 노드의 부모 노드. root_level는 해당 노드의 레벨. 여기서 레벨은 "같은 레벨"의 부속 트리가 합쳐질 때 높아진다.(뿌리 노드에만 해당)
} root_node;

node_ptr data_init(int n)
{ // node ptr 자료형 2차원 배열 생성
    char str_tmp[1024], *p;
    FILE *fp = NULL;

    node_ptr a = NULL;
    a = (node_ptr)calloc(n, sizeof(node));
    int num = 0;

    // char f[10];
    //  printf("파일명 입력:");
    //  scanf("%s",f);
    fp = fopen("test.csv", "r");
    if (fp == NULL)
    {
        printf("Couldn't open this file!");
        fclose(fp);
        return a;
    }
    else if (fp != NULL)
    {
        for (node_ptr i = a; i < a + n || !feof(fp); i++, num++)
        {
            node_ptr before = i;
            int linknum = 0;

            i->vertex = num;
            i->visited = FALSE;

            fgets(str_tmp, 1024, fp);
            p = strtok(str_tmp, ",");

            while (p != NULL)
            {
                if (*p != ' ')
                {
                    int cost = atoi(p);

                    node_ptr new = NULL;
                    new = (node_ptr)malloc(sizeof(node));
                    new->vertex = linknum;
                    new->cost = cost;
                    new->visited = FALSE;
                    new->link = NULL;
                    before->link = new;
                    before = new;
                }
                p = strtok(NULL, ",");
                linknum++;
            }
        }
    }

    fclose(fp);
    return a;
}

edge *edge_sort(node_ptr graph, int n, int *s)
{ //간선의 비용을 기준으로 오름차순으로 정렬한 배열을 반환하는 함수. n은 노드 개수, s는 간선 개수를 받을 포인터 변수
    int size = 0;
    edge *e = NULL;

    for (node_ptr i = graph; i < graph + n; i++)
    {
        for (node_ptr j = i; j; j = j->link)
        {
            if (i->vertex >= j->vertex)
            { //중복 간선 생성 방지
                continue;
            }
            edge new = {i->vertex, j->vertex, j->cost};
            e = (edge *)realloc(e, (size + 1) * sizeof(edge));
            *(e + size) = new;
            size++;
        }
    }
    *s = size;

    for (edge *i = e; i < e + size; i++)
    {
        edge *min = i; //가장 작은 비용을 가진 간선
        for (edge *j = i; j < e + size; j++)
        {
            if (j->cost < min->cost)
            {
                min = j;
            }
        }
        edge tmp = *i;
        *i = *min;
        *min = tmp;
    }

    return e;
}

void print_graph(node_ptr graph, int n)
{//그래프 출력 함수. 각 노드별로 이어진 노드를 출력한다.
    for (node_ptr i = graph; i < graph + n; i++)
    {
        printf("%d: ", i->vertex);
        for (node_ptr j = i->link; j; j = j->link)
        {
            printf("%d(%d) ", j->vertex, j->cost);
        }
        printf("\n");
    }
}

//--------------------------탐색 알고리즘--------------------------
void dfs(node_ptr graph, int v)
{
    (graph + v)->visited = TRUE;

    printf("%d ", v);
    for (node_ptr i = graph + v; i; i = i->link)
    {
        if (!(graph + i->vertex)->visited)
        {
            dfs(graph, i->vertex);
        }
    }
}

void bfs_visit(node_ptr graph, que q, int v)
{
    printf("%d ", v);
    (graph + v)->visited = TRUE;

    for (node_ptr i = graph + v; i; i = i->link)
    {
        if (!(graph + i->vertex)->visited)
        {
            que_insert(&q, i->vertex);
            (graph + i->vertex)->visited = TRUE;
        }
    }

    if (q.front != q.rear)
    {
        bfs_visit(graph, q, que_delete(&q));
    }
}

void bfs(node_ptr graph, int v, int n)
{
    que q;
    que_init(&q, n);

    bfs_visit(graph, q, v);

    free(q.queue);
    q.queue = NULL;
}

//--------------------------신장 트리 알고리즘--------------------------

int find_root(root_node *r, int v)
{//노드 v가 속한 부속 트리의 뿌리 노드를 구하는 함수
    int root = (r + v)->root_vertex;
    if (root == v)
    {
        return v;
    }
    return find_root(r, root);
}

void Kruskal(edge *e, int n, int e_num)
{ //크루스칼 알고리즘. n은 노드의 개수, e_num은 전체 간선 개수
    int total = 0;

    root_node *node_list = NULL;
    node_list = (root_node *)calloc(n, sizeof(node_list));

    edge *edge_list = NULL;
    int size = 0;

    for (int i = 0; i < n; i++)
    {
        (node_list + i)->root_vertex = i; //연결된 노드가 없다면 노드의 뿌리는 자기 자신이다.
        (node_list + i)->root_level = 0;
    }

    for (edge *i = e; i < e + e_num || size < n - 1; i++)
    { //간선의 비용을 기준으로 정렬된 상태이기 때문에 굳이 최소값을 찾지 않아도 된다.
        int root_u = find_root(node_list, i->u);
        int root_v = find_root(node_list, i->v);

        if (root_u != root_v)
        { //간선의 u와 v가 같은 부속 트리에 속하지 않은 경우 두 트리를 합친다.
            edge_list = (edge *)realloc(edge_list, (size + 1) * sizeof(edge));
            *(edge_list + size) = *i;
            total += i->cost;
            size++;
            //부속 트리 합칠 시 두 노드의 각 뿌리 노드 중 레벨이 높은 노드에 레벨을 맞춘다.
            if ((node_list + root_u)->root_level < (node_list + root_v)->root_level)
            {
                (node_list + root_u)->root_vertex = root_v;
            }
            else if ((node_list + root_u)->root_level > (node_list + root_v)->root_level)
            {
                (node_list + root_v)->root_vertex = root_u;
            } //뿌리 레벨이 서로 같을 시 통합시키고 레벨을 한단계 높인다.
            else
            {
                (node_list + root_v)->root_vertex = root_u;
                (node_list + root_u)->root_level += 1;
            }
        }
    }

    printf("각 노드의 레벨: ");
    for (root_node *i = node_list; i < node_list + n; i++)
    {
        printf("%d ", i->root_level);
    }
    printf("\n사용된 간선: ");
    for (edge *i = edge_list; i < edge_list + n - 1; i++)
    {
        printf(" {%d, %d} ", i->u, i->v);
    }

    printf("\n총 비용: %d", total);

    free(node_list);
    node_list = NULL;
    free(edge_list);
    edge_list = NULL;
}

void Prim(node_ptr graph, int n)
{//프림 알고리즘. n은 노드의 개수이다.
    int total = 0, num = 1;
    int *node_list = NULL;
    node_list = (int *)calloc(n, sizeof(int));
    node_list[0] = 0;
    graph->visited = TRUE;

    while (num != n)
    {
        int cost_min = -1;
        int next_node;

        for (int i = 0; i < num; i++)
        {
            for (node_ptr j = graph + node_list[i]; j; j = j->link)
            {
                node_ptr connected_node = graph + (j->vertex);
                if (!connected_node->visited)
                {
                    if (cost_min == -1 || cost_min > j->cost)
                    {
                        cost_min = j->cost;
                        next_node = j->vertex;
                    }
                }
            }
        }

        if (cost_min == -1)
        {
            printf("No spanning tree");
            free(node_list);
            node_list = NULL;
            return;
        }

        total += cost_min;
        (graph + next_node)->visited = TRUE;
        node_list[num++] = next_node;
    }

    printf("노드 순서: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", node_list[i]);
    }
    printf("\n총 비용: %d\n", total);

    free(node_list);
    node_list = NULL;
}