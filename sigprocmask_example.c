/*
int sigprocmask(int how, const sigset_t *restrict set, sigset_t *restrict oset);

how - 시그널을 블록할 것인지, 해제할 것인지 여부
set - 블록하거나 해제할 시그널 집합의 주소
oset - NULL 또는 이전 설정값을 저장할 시그널 집합의 주소

sigprocmask 함수는 set에 지정한 시그널 집합을 블록할 것인지, 해제할 것인지를 how에 지정해 호출합니다. 

첫 번째 인자인 how에 올 수 있는 값은 다음과 같습니다.
SIG_BLOCK - set에 지정한 시그널 집합을 시그널 마스크에 추가한다.
SIG_UNBLOCK - set에 지정한 시그널 집합을 시그널 마스크에서 제거한다.
SIG_SETMASK - set에 지정한 시그널 집합으로 현재 시그널 마스크를 대체한다.
*/

#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int main(void) {
        sigset_t new;

        sigemptyset(&new);
        sigaddset(&new, SIGINT);
        sigaddset(&new, SIGQUIT);
        sigprocmask(SIG_BLOCK, &new, (sigset_t *)NULL);

        printf("Blocking Signals : SIGINT, SIGQUIT ");
        printf("Send SIGQUIT ");
        kill(getpid(), SIGQUIT);

        printf("UnBlocking Signals ");

        sigprocmask(SIG_UNBLOCK, &new, (sigset_t *)NULL);

        return 0;
}

