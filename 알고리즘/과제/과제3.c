#include <stdio.h>
#include <stdlib.h>

#define M 23
#define Q 19

typedef enum cellTag
{
    empty,
    active,
    inactive
} cellTag;

// 편의를 위해 e=k로 정했다.
typedef struct cell
{
    int key;
    cellTag tag;
} cell;

cell *hashTable = NULL;

void createHashTable();
int hashFunction1(int k);
int hashFunction2(int k);
int findElement(int k);
void insertItem(int k);
void removeElement(int k);
void showHashTable();

int main()
{
    createHashTable();

    //s는 반복문 제어용 변수, k는 입력받을 key를 저장할 변수, tmp는 탐색 결과를 저장할 변수다.
    int s = 1, k, tmp;
    //mode는 명령어를 입력받을 변수다.
    char mode;

    while (s)
    {
        scanf("%c", &mode);

        switch (mode)
        {
        case 'f':
            scanf("%d", &k);
            tmp = findElement(k);
            if (tmp == -1)
            {
                printf("There is NO such key!\n");
            }
            else
            {
                printf("%d\n", tmp);
            }
            break;

        case 'i':
            scanf("%d", &k);
            insertItem(k);
            showHashTable();
            break;

        case 'r':
            scanf("%d", &k);
            removeElement(k);
            showHashTable();
            break;

        case 'q':
            s = 0;
            break;
        }

        getchar();
    }

    free(hashTable);
    return 0;
}

void createHashTable()
{
    hashTable = (cell *)calloc(M, sizeof(cell));

    for (int i = 0; i < M; ++i)
    {
        hashTable[i].key = -1;
        hashTable[i].tag = empty;
    }

    for (int i = 0; i < 20; ++i)
    {
        int k = rand() % 100;
        while (findElement(k) != -1)
        {
            k = rand() % 100;
        }
        insertItem(k);
    }

    //필요 시 초기화가 어떻게 되었는 지 확인하고 싶다면 주석 풀 것.
    //showHashTable();
}

int hashFunction1(int k)
{
    return k % M;
}

int hashFunction2(int k)
{
    return Q - k % Q;
}

int findElement(int k)
{
    int bucket_index = hashFunction1(k);

    // 셀이 비어있다면 탐색 실패
    while (hashTable[bucket_index].tag != empty)
    {
        // 활성 셀인 경우에 조사
        if (hashTable[bucket_index].tag == active && hashTable[bucket_index].key == k)
        {
            return hashTable[bucket_index].key;
        }

        //다음 셀로 이동
        bucket_index = (bucket_index + hashFunction2(k)) % M;

        // 한 바퀴 돌았을 경우
        if (bucket_index == hashFunction1(k))
        {
            break;
        }
    }

    return -1;
}

void insertItem(int k)
{
    int bucket_index = hashFunction1(k);

    // 셀이 활성화 되어있는 상태가 아닐 경우 반복문 끝내고 해당 셀에 정보 저장 및 활성화
    while (hashTable[bucket_index].tag == active)
    {
        // 같은 키가 테이블에 존재할 경우
        if (hashTable[bucket_index].key == k)
        {
            printf("There is SAME KEY in table!\n");
            return;
        }
        bucket_index = (bucket_index + hashFunction2(k)) % M;

        // 한 바퀴 돌았을 경우
        if (bucket_index == hashFunction1(k))
        {
            printf("Table is FULL!\n");
            return;
        }
    }

    hashTable[bucket_index].key = k;
    hashTable[bucket_index].tag = active;
}

void removeElement(int k)
{
    int bucket_index = hashFunction1(k);

    // 셀이 비어있다면 탐색 실패
    while (hashTable[bucket_index].tag != empty)
    {
        // 활성 셀인 경우에 조사
        if (hashTable[bucket_index].tag == active && hashTable[bucket_index].key == k)
        {
            hashTable[bucket_index].tag = inactive;
            return;
        }
        bucket_index = (bucket_index + hashFunction2(k)) % M;

        // 한 바퀴 돌았을 경우
        if (bucket_index == hashFunction1(k))
        {
            break;
        }
    }

    printf("There is NO such key!\n");
}

void showHashTable()
{
    for (int i = 0; i < M; ++i)
    {
        printf(" %2d", i);
    }
    printf("\n");

    for (int i = 0; i < M; ++i)
    {
        if (hashTable[i].tag == active)
        {
            printf(" %2d", hashTable[i].key);
        }
        else
        {
            printf("  .");
        }
    }
    printf("\n");
}