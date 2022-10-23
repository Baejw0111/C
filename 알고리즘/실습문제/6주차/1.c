#include <stdio.h>
#include <stdlib.h>

// start는 왼쪽 끝 인덱스, end는 오른쪽 끝 인덱스이다.
void binary_search(int key, int *a, int start, int end);

int main()
{
    int n, key, *a = NULL;
    scanf("%d %d", &n, &key);

    a = (int *)calloc(n, sizeof(int));

    for (int i = 0; i < n; ++i)
    {
        scanf("%d", a + i);
    }

    binary_search(key, a, 0, n - 1);

    free(a);

    return 0;
}

void binary_search(int key, int *a, int start, int end)
{
    int mid = (end + start) / 2;

    //start==end가 되는 시점 없이 건너뛰는 경우가 있음
    if(start>end){
        printf(" %d\n",start-1);
        return;
    }

    if (a[mid] > key)
    {
        binary_search(key, a, start, mid - 1);
    }
    else if (a[mid] < key)
    {
        binary_search(key, a, mid + 1, end);
    }
    else
    {
        printf(" %d\n", mid);
    }

    return;
}