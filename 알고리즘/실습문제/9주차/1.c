#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    //노드의 키값. 노드가 버켓으로 쓰일 경우 해당 버켓에 키가 존재하는 지 여부를 나타냄.
    int key;
    //다음 노드 가리키는 포인터
    struct node *next;
} node;

typedef node *node_ptr;

int M;
node_ptr hashTable = NULL;

void insert(int x);
void search(int x);
void delete (int x);
void print();
//해시테이블 동적할당 해제
void freeTable();

int main()
{
    scanf("%d", &M);

    //해시테이블 초기화
    hashTable = (node_ptr)calloc(M, sizeof(node));
    for (int i = 0; i < M; ++i)
    {
        hashTable[i].key = 0;
        hashTable[i].next = NULL;
    }

    int s = 1, x;
    char mode;

    while (s)
    {
        getchar();
        scanf("%c", &mode);

        switch (mode)
        {
        case 'i':
            scanf("%d", &x);
            insert(x);
            break;

        case 's':
            scanf("%d", &x);
            search(x);
            break;

        case 'd':
            scanf("%d", &x);
            delete (x);
            break;

        case 'p':
            print(x);
            break;

        case 'e':
            s = 0;
            break;
        }
    }

    freeTable();
    return 0;
}

void insert(int x)
{
    node_ptr newKey = NULL;
    newKey = (node_ptr)calloc(1, sizeof(node));

    node_ptr bucket = hashTable + x % M;

    newKey->key = x;
    newKey->next = bucket->next;
    bucket->next = newKey;

    if (!bucket->key)
    {
        bucket->key = 1;
    }
}

void search(int x)
{
    node_ptr bucket = hashTable + x % M;
    int index = 1, find = 0;

    if (bucket->key)
    {
        node_ptr cur = bucket->next;

        for (; cur != NULL; cur = cur->next)
        {
            if (cur->key == x)
            {
                find = 1;
                break;
            }
            index += 1;
        }
    }

    if (find)
    {
        printf("%d\n", index);
    }
    else
    {
        printf("0\n");
    }
}

void delete (int x)
{
    node_ptr bucket = hashTable + x % M;
    int index = 1, find = 0;

    if (bucket->key)
    {
        node_ptr cur = bucket->next, prev = bucket;

        for (; cur != NULL; cur = cur->next, prev = prev->next)
        {
            if (cur->key == x)
            {
                prev->next = cur->next;
                free(cur);
                find = 1;
                break;
            }
            index += 1;
        }
    }

    if (find)
    {
        printf("%d\n", index);
    }
    else
    {
        printf("0\n");
    }
}

void print()
{
    for (int i = 0; i < M; ++i)
    {
        for (node_ptr cur = hashTable[i].next; cur != NULL; cur = cur->next)
        {
            printf(" %d", cur->key);
        }
    }
    printf("\n");
}

void freeTable()
{
    for (int i = 0; i < M; ++i)
    {
        node_ptr cur = hashTable[i].next;

        while (cur != NULL)
        {
            node_ptr tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }

    free(hashTable);
}