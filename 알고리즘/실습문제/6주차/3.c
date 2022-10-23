#include <stdio.h>
#include <stdlib.h>

void binary_search_game(int a, int b, int n);

int main()
{
    int a, b, n;
    scanf("%d %d %d", &a, &b, &n);
    getchar();
    binary_search_game(a, b, n);
    return 0;
}

void binary_search_game(int a, int b, int n)
{
    for (int i = 0; i < n; ++i)
    {
        char c;
        int m = (a + b) / 2;
        scanf("%c", &c);

        if (c == 'Y')
        {
            a = m + 1;
        }
        else if (c == 'N')
        {
            b = m;
        }
    }

    printf("%d", a);

    return;
}