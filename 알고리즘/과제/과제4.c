#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define MAX 30

int A[MAX] = {0, 1}, H[MAX] = {0, 5};
int S[4] = {0, 2, 2, 1}, D[4] = {4, 5, 4, 28};
int n = 6;

// A와 H 초기화
void InitCostTable()
{
    for (int i = 2; i < MAX; ++i)
    {
        A[i] = A[i - 1] + A[i - 1] % 5 + 3;
        H[i] = (H[i - 1] + i) % 9 + 1;
    }
}

// 알고리즘은 모두 정방향 버전으로 구현하였다.
int airtelDC(int s, int d)
{
    if (d - s == 0)
    {
        return 0;
    }
    int ret = -1;

    for (int i = s; i < d; ++i)
    {
        int cost;
        // 경유 지점이 s인 경우 숙박료 제외해서 계산(s에서 숙박하지 않으므로)
        if (i == s)
        {
            cost = airtelDC(s, i) + A[d - i];
        }
        else
        {
            cost = airtelDC(s, i) + H[i] + A[d - i];
        }

        if (ret == -1 || ret > cost)
        {
            ret = cost;
        }
    }

    return ret;
}

int airtelDP(int index)
{
    int ret = -1;
    int m[MAX] = {0};

    for (int i = S[index] + 1; i <= D[index]; ++i)
    {
        m[i] = -1;
        for (int j = S[index]; j < i; ++j)
        {
            int cost;
            // 경유 지점이 s인 경우 숙박료 제외해서 계산(s에서 숙박하지 않으므로)
            if (j == S[index])
            {
                cost = m[j] + A[i - j];
            }
            else
            {
                cost = m[j] + H[j] + A[i - j];
            }

            if (m[i] == -1 || m[i] > cost)
            {
                m[i] = cost;
            }
        }
    }

    return m[D[index]];
}

int main()
{
    InitCostTable();
    int mincost;
    LARGE_INTEGER thicksPerSec;
    LARGE_INTEGER start, end, diff;
    printf(" n  s   d    mincost    version    cputime\n");

    for (int i = 0; i < 4; ++i)
    {
        // 테스트 실행 종료 후 n을 MAX 값으로 변경
        if (i == 3)
        {
            n = MAX;
        }

        for (int j = 0; j < 2; ++j)
        {
            printf("%2d %2d %3d    ", n, S[i], D[i]);

            QueryPerformanceFrequency(&thicksPerSec);
            QueryPerformanceCounter(&start);

            if (j == 0)
            {
                mincost = airtelDC(S[i], D[i]);
            }
            else
            {
                mincost = airtelDP(i);
            }

            QueryPerformanceCounter(&end);

            printf("%2d         ", mincost);

            diff.QuadPart = end.QuadPart - start.QuadPart;

            double t = (double)diff.QuadPart / (double)thicksPerSec.QuadPart;

            if (j == 0)
            {
                printf("DC");
            }
            else
            {
                printf("DP");
            }

            // ms 단위로 출력
            printf("      %13.8lfms\n", 1000 * t);
        }
    }
    return 0;
}