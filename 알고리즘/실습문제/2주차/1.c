#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void selection_sort(int n, int *a)
{ //선택 정렬
    for (int i = n - 1; i > 0; i--)
    {
        int max = i; //가장 큰 값을 가진 인덱스
        for (int j = i; j >= 0; j--)
        {
            if (*(a + j) > *(a + max))
            {
                max = j;
            }
        }
        swap(a + i, a + max);
    }
}

int main()
{
    int n, *a = NULL;

    scanf("%d", &n);
    a = (int *)calloc(n, sizeof(int));

    for (int i = 0; i < n; ++i)
    {
        scanf("%d", a + i);
    }

    selection_sort(n, a);

    for (int i = 0; i < n; ++i)
    {
        printf(" %d", a[i]);
    }

    free(a);
    return 0;
}