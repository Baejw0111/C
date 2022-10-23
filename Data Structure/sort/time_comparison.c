#include "D:\OneDrive\Coding\C\Data Structure\DS.h"

int main(){
    int size=100000;
    int* a[5];
    for(int i=0;i<5;i++){
        a[i]=array_init(size);
    }

    srand(time(NULL));
    for(int i=0;i<size;i++){
        *(a[0]+i)=rand();
        for(int j=1;j<5;j++){
            *(a[j]+i)=*(a[0]+i);
        }
    }

    for(int i=0;i<5;i++){
        clock_t start,finish;

        start=clock();
        switch(i){
            case 0:
                printf("버블 정렬 ");
                bubble_sort(size,a[i]);
            break;

            case 1:
                printf("선택 정렬 ");
                selection_sort(size,a[i]);
            break;

            case 2:
                printf("삽입 정렬 ");
                insertion_sort(size,a[i]);
            break;

            case 3:
                printf("퀵 정렬 ");
                quick_sort(a[i],0,size);
            break;

            case 4:
                printf("힙 정렬 ");
                heap_sort(size,a[i]);
                break;
        }
        finish=clock();

        double duration=(double)(finish-start);
        printf("실행 시간: %.3lf초\n",duration/1000);

    }

    for(int i=0;i<5;i++){
        free(a[i]);
        a[i]=NULL;
    }
    
    return 0;
}