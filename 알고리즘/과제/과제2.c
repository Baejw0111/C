#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int n = 100000;
int Limits[4] = {1, 100, 500, 1000};
int limit;

// 0부터 n까지의 난수를 반환하는 함수. rand() 함수의 최대값이 100000보다 아래이기 때문에 이와 같은 함수가 필요함.
int random();
// a와 b의 값을 바꾸는 함수
void swap(int *a, int *b);
//삽입 정렬
void insertion_sort(int *a, int left, int right);
//중앙값 반환
int median(int a, int b, int c);

//퀵정렬 함수들

//결정적1 버전
void deterministic1_quick_sort(int *a, int left, int right);
//무작위1 버전
void randomized1_quick_sort(int *a, int left, int right);
//결정적3 버전
void deterministic3_quick_sort(int *a, int left, int right);
//무작위1 버전
void randomized3_quick_sort(int *a, int left, int right);

int main()
{
    //함수 포인터 배열 설정
    void (*quick_sort[4])(int *, int, int) = {deterministic1_quick_sort,
                                              deterministic3_quick_sort,
                                              randomized1_quick_sort,
                                              randomized3_quick_sort};

    //초기 입력 배열 생성
    int *original_arr = NULL;
    original_arr = (int *)calloc(n, sizeof(int));

    srand(time(NULL));
    for (int i = 0; i < n; ++i)
    {
        original_arr[i] = random() % (n + 1);
    }

    // original_arr 복사본으로 쓸 배열 초기화
    int *a = NULL;
    a = (int *)calloc(n, sizeof(int));

    printf("Limit    결정적1         결정적3         무작위1         무작위3\n");

    for (int i = 0; i < 4; ++i)
    {
        limit = Limits[i];
        printf("%4d", limit);

        for (int j = 0; j < 4; ++j)
        {

            //초기 입력 배열 복사
            for (int k = 0; k < n; ++k)
            {
                a[k] = original_arr[k];
            }

            //시간 측정
            LARGE_INTEGER thicksPerSec;
            LARGE_INTEGER start, end, diff;
            QueryPerformanceFrequency(&thicksPerSec);
            QueryPerformanceCounter(&start);

            quick_sort[j](a, 0, n - 1);

            QueryPerformanceCounter(&end);
            diff.QuadPart = end.QuadPart - start.QuadPart;

            double t = (double)diff.QuadPart / (double)thicksPerSec.QuadPart;

            // ms 단위로 출력
            printf("%13.8lfms ", 1000*t);
        }

        printf("\n");
    }

    free(original_arr);
    free(a);
    return 0;
}

int random()
{
    return (rand() << 2) | rand();
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void insertion_sort(int *a, int left, int right)
{
    for (int i = left; i < right + 1; i++)
    {
        for (int j = i - 1; j >= 0 && a[j] > a[j + 1]; --j)
        {
            swap(a + j, a + j + 1);
        }
    }
}

int median(int a, int b, int c)
{
    int tmp[3] = {a, b, c};
    insertion_sort(tmp, 0, 2);
    return tmp[1];
}

void deterministic1_quick_sort(int *a, int left, int right)
{
    if (left < right) //해당 조건 불만족 시 재귀 종료
    {
        if (limit >= right - left + 1)
        {
            insertion_sort(a, left, right);
        }
        else
        {
            int pivot = a[right], i = left, j = right;

            do
            {
                while (a[i] < pivot)
                {
                    ++i;
                }

                while (a[j] > pivot)
                {
                    --j;
                }

                if (i <= j)
                {
                    swap(a + i, a + j);
                    ++i;
                    --j;
                }

            } while (i < j);

            deterministic1_quick_sort(a, left, j);
            deterministic1_quick_sort(a, i, right);
        }
    }
}

void randomized1_quick_sort(int *a, int left, int right)
{
    if (left < right) //해당 조건 불만족 시 재귀 종료
    {
        if (limit >= right - left + 1)
        {
            insertion_sort(a, left, right);
        }
        else
        {
            srand(time(NULL));
            int k = left + random() % (right - left);
            int pivot = a[k], i = left, j = right;

            do
            {
                while (a[i] < pivot)
                {
                    ++i;
                }

                while (a[j] > pivot)
                {
                    --j;
                }

                if (i <= j)
                {
                    swap(a + i, a + j);
                    ++i;
                    --j;
                }

            } while (i < j);

            randomized1_quick_sort(a, left, j);
            randomized1_quick_sort(a, i, right);
        }
    }
}

void deterministic3_quick_sort(int *a, int left, int right)
{
    if (left < right) //해당 조건 불만족 시 재귀 종료
    {
        if (limit >= right - left + 1)
        {
            insertion_sort(a, left, right);
        }
        else
        {
            int pivot, i = left, j = right;
            if (right - left < 2)
            {
                //부배열 크기가 2 이하일 시 맨 앞 원소를 피벗으로 쓴다.
                pivot = a[left];
            }
            else
            {
                //그 외의 경우
                pivot = median(a[left], a[(left + right) / 2], a[right]);
            }

            do
            {
                while (a[i] < pivot)
                {
                    ++i;
                }

                while (a[j] > pivot)
                {
                    --j;
                }

                if (i <= j)
                {
                    swap(a + i, a + j);
                    ++i;
                    --j;
                }

            } while (i < j);

            deterministic3_quick_sort(a, left, j);
            deterministic3_quick_sort(a, i, right);
        }
    }
}

void randomized3_quick_sort(int *a, int left, int right)
{
    if (left < right) //해당 조건 불만족 시 재귀 종료
    {
        if (limit >= right - left + 1)
        {
            insertion_sort(a, left, right);
        }
        else
        {
            int pivot, i = left, j = right;
            if (right - left < 2)
            {
                pivot = a[left];
            }
            else
            {
                srand(time(NULL));
                int k = left + 1 + random() % (right - left - 1);
                pivot = median(a[left], a[k], a[right]);
            }

            do
            {
                while (a[i] < pivot)
                {
                    ++i;
                }

                while (a[j] > pivot)
                {
                    --j;
                }

                if (i <= j)
                {
                    swap(a + i, a + j);
                    ++i;
                    --j;
                }

            } while (i < j);

            randomized3_quick_sort(a, left, j);
            randomized3_quick_sort(a, i, right);
        }
    }
}