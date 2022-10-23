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

void insertion_sort(int n, int *a)
{ //삽입 정렬
    for (int *i = a + 1; i < a + n; i++)
    {
        int tmp = *i, *j = i - 1;
        while (tmp < *j && j >= a)
        {
            *(j + 1) = *j;
            --j;
        }

        *(j + 1) = tmp;
    }
}

void quick_sort(int *a, int left, int right)
{ //퀵 정렬
    // right는 배열의 마지막 인덱스여야 한다.
    if (left < right)
    { //해당 조건 불만족 시 재귀 종료
        srand(time(NULL));
        int k = left + rand() % (right - left);

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

        } while (i <= j);

        if (left < j)
        {
            quick_sort(a, left, j);
        }

        if (i < right)
        {
            quick_sort(a, i, right);
        }
    }
}

//힙 정렬