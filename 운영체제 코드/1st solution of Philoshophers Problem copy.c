semaphore fork[5] = {1};
//각 포크의 초기값은 1
int i;

void philosopher(int i)
{
    while (true)
    {
        think();
        wait(fork[i]);//왼쪽 포크
        wait(fork[(i + 1) mod 5]);//오른쪽 포크
        eat();
        signal(fork[(i + 1) mod 5]);
        signal(fork[i]);
        //시그널 순서는 상관 없다.
    }
}

void main()
{
    parbegin(philosopher(0), philosopher(1),
             philosopher(2), philosopher(3),
             philosopher(4));
}


