struct state {
    int resource[m];
    int available[m];
    int claim[n][m];
    int alloc[n][m];
};


if (alloc [i,*] + request [*] > claim [i,*])
// *은 모든 자원을 의미한다.
// 현재 i에게 할당된 자원량+i가 현재 요청하는 자원량 > i가 요청할 전체 자원량
    <error>;
//원래 요청하기로 한 전체 자원량보다 더 많이 요구하는 것이니 에러가 난다.

else if (request [*] > available [*])
    <suspend process>;//프로세스 block

else {     
    <define newstate by:
    alloc [i,*] = alloc [i,*] + request [*];
    available [*] = available [*] - request [*]>;
}

if (safe (newstate)) //safe 상태 여부 판단
    <carry out allocation>;
else {
    <restore original state>;
    <suspend process>;
}

boolean safe (state S) {
    int currentavail[m];
    process rest[<number of processes>];//프로세스 집합
    currentavail = available;
    rest = {all processes};
    possible = true;

    while (possible) {
        <find a process Pk in rest such that
            claim [k,*] - alloc [k,*]<= currentavail;>
        //프로세스 실행 가능 여부 판단

        if (found) { /* simulate execution of Pk */
            //프로세스 실행 후 종료 시
            currentavail = currentavail + alloc [k,*];
            rest = rest - {Pk};
        }
        else possible = false;
    }

    return (rest == null);
    //rest가 비어있다는 것은 모든 프로세스가 무사히 실행됐다는 의미.
    //즉 safe
}