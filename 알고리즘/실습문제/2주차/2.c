#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int n, int *a)
{ //삽입 정렬
    for (int *i = a + 1; i < a + n; i++)
    {
        int tmp=*i,*j=i-1;
        while(tmp<*j&&j>=a){
            *(j+1)=*j;
            --j;
        }

        *(j+1)=tmp;
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

    insertion_sort(n, a);

    for (int i = 0; i < n; ++i)
    {
        printf(" %d", a[i]);
    }

    free(a);
    return 0;
}