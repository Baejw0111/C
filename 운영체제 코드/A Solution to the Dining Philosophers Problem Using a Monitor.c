monitor dining_controller;
cond ForkReady[5];        //동기화를 위한 변수
boolean fork[5] = {true}; //포크 사용 여부. 사용 중이면 false다.

void get_forks(int pid)
//pid는 철학자 아이디(philoshpher id), i라고 생각하면 됨
{
    int left = pid;
    int right = (++pid) % 5;
    //왼쪽 포크 가져가기
    if (!fork[left])
        cwait(ForkReady[left]); //해당 상태 변수에 해당하는 큐로 이동
    fork(left) = false;
    //오른쪽 포크 가져가기
    if (!fork[right])
        cwait(ForkReady[right]); //해당 상태 변수에 해당하는 큐로 이동
    fork[right] = false:
}

void release_forks(int pid)
{
    int left = pid;
    int right = (++pid) % 5;
    //왼쪽 포크 놓기
    if (empty(ForkReady[left])) //해당 포크 기다리는 프로세스가 없는지 판단
        fork[left] = true;
    else //해당 포크 기다리는 프로세스가 있다면 다시 깨우기
        csignal(ForkReady[left]);
    //오른쪽 포크 놓기
    if (empty(ForkReady[right])) //해당 포크 기다리는 프로세스가 없는지 판단
        fork[right] = true;
    else //해당 포크 기다리는 프로세스 다시 깨우기
        csignal(ForkReady[right]);
}

void philosopher[k = 0 to 4] //철학자 5명
{
    while (true)
    {
        <think>;
        get_forks(k); //모니터로 포크 잡기 구현
        <eat spaghetti>;
        release_forks(k); //모니터로 포크 놓기 구현    
    }
}


