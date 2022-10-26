#include <stdio.h>
#include <stdlib.h>

int M, n;
int *hashTable = NULL;

void insert(int x);
void search(int x);

int main()
{
    scanf("%d %d", &M, &n);

    //해시테이블 초기화
    hashTable = (int *)calloc(M, sizeof(int));

    for (int i = 0; i < M; ++i)
    {
        hashTable[i] = 0;
    }

    int s = 1, x, count = 0;
    char mode;

    while (s)
    {
        getchar();
        scanf("%c", &mode);

        switch (mode)
        {
        case 'i':
            scanf("%d", &x);
            if (count < n)
            {
                insert(x);
                ++count;
            }
            break;

        case 's':
            scanf("%d", &x);
            search(x);
            break;

        case 'e':
            s = 0;
            break;
        }
    }

    free(hashTable);
    return 0;
}

void insert(int x)
{
    int bucket_index = x % M;

    while (hashTable[bucket_index] != 0)
    {
        printf("C");
        bucket_index = (bucket_index + 1) % M;
    }

    hashTable[bucket_index] = x;
    printf("%d\n", bucket_index);
}

void search(int x)
{
    int bucket_index = x % M, ret = -1;

    while (hashTable[bucket_index] != 0)
    {
        if (hashTable[bucket_index] == x)
        {
            ret = bucket_index;
            break;
        }
        bucket_index = (bucket_index + 1) % M;

        //한 바퀴 돌았을 경우
        if (bucket_index == x % M)
        {
            break;
        }
    }

    printf("%d", ret);
    if (ret != -1)
    {
        printf(" %d", x);
    }

    printf("\n");
}