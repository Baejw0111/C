#include <stdio.h>
#include <stdlib.h>

// arrLen은 배열의 길이다.
void binary_search(int key, int *a, int arrLen);

int main()
{
    int n, key, *a = NULL;
    scanf("%d %d", &n, &key);

    a = (int *)calloc(n, sizeof(int));

    for (int i = 0; i < n; ++i)
    {
        scanf("%d", a + i);
    }

    binary_search(key, a, n);

    free(a);

    return 0;
}

void binary_search(int key, int *a, int arrLen)
{
    int start = 0, end = arrLen - 1;

    while (start <= end)
    {
        int mid = (end + start) / 2;

        if (a[mid] == key)
        {
            printf(" %d\n", mid);
            break;
        }
        else if (a[mid] > key)
        {
            end = mid - 1;
        }
        else
        {
            start = mid + 1;
        }
    }
    if (start > end)
    {
        printf(" %d\n", end + 1);
        return;
    }

    return;
}