#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    char elem;
    struct node *prev, *next;
} node;

typedef node *node_ptr;

typedef struct List
{
    node_ptr head, tail;
    int *count; // list에 존재하는 원소의 개수
} List;

void Add(List list, int r, char e);
void Delete(List list, int r);
char Get(List list, int r);
void Print(List list);
void FreeList(List list);

int main()
{
    int n;
    scanf("%d", &n);
    getchar();

    List list;

    list.head = NULL;
    list.tail = NULL;
    list.count = NULL;

    list.head = (node_ptr)calloc(1, sizeof(node));
    list.tail = (node_ptr)calloc(1, sizeof(node));
    list.count = (int*)calloc(1, sizeof(int));

    *list.count=0;

    list.head->prev = NULL;
    list.head->next = list.tail;
    list.tail->prev = list.head;
    list.tail->next = NULL;

    for (int i = 0; i < n; ++i)
    {
        char function, e;
        int r;

        scanf("%c", &function);

        switch (function)
        {
        case 'A':
            scanf("%d %c", &r, &e);
            getchar();
            if (*list.count < r - 1)
            {
                printf("invalid position\n");
            }
            else
            {
                Add(list, r, e);
            }
            break;

        case 'D':
            scanf("%d", &r);
            getchar();
            if (*list.count < r)
            {
                printf("invalid position\n");
            }
            else
            {
                Delete(list, r);
            }
            break;

        case 'G':
            scanf("%d", &r);
            getchar();
            if (*list.count < r)
            {
                printf("invalid position\n");
            }
            else
            {
                printf("%c\n", Get(list, r));
            }
            break;

        case 'P':
            getchar();
            Print(list);
            break;
        }
    }

    FreeList(list);

    return 0;
}

void Add(List list, int r, char e)
{
    node_ptr temp = NULL;
    temp = (node_ptr)calloc(1, sizeof(node));
    temp->elem = e;

    node_ptr target_node = list.head;
    for (int i = 0; target_node != list.tail; target_node = target_node->next, i++)
    {
        if (i == r - 1)
        {
            temp->next = target_node->next;
            temp->prev = target_node;
            target_node->next->prev = temp;
            target_node->next = temp;

            *list.count += 1;
            return;
        }
    }
}

void Delete(List list, int r)
{
    node_ptr target_node = list.head->next;
    for (int i = 1; target_node != list.tail; target_node = target_node->next, i++)
    {
        if (i == r)
        {
            target_node->prev->next = target_node->next;
            target_node->next->prev = target_node->prev;
            free(target_node);
            *list.count -= 1;
            return;
        }
    }
}

char Get(List list, int r)
{
    node_ptr target_node = list.head->next;
    char ret;
    for (int i = 1; target_node != list.tail; target_node = target_node->next, i++)
    {
        if (i == r)
        {
            ret = target_node->elem;
            break;
        }
    }

    return ret;
}

void Print(List list)
{
    for (node_ptr i = list.head->next; i != list.tail; i = i->next)
    {
        printf("%c", i->elem);
    }
    printf("\n");
}

void FreeList(List list)
{
    list.tail = NULL;

    while (list.head)
    {
        node_ptr temp = list.head;
        list.head = list.head->next;
        free(temp);
    }
}