/*
int sigpause(int sig);
sig - 시그널이 올 때까지 대기할 시그널

sigpause 함수는 인자로 지정한 시그널을 프로세스의 시그널 마스크에서 제거하고 프로세스가 시그널을 받을 때까지 기다립니다.

int sigsuspend(const sigset_t *set);
set - 기다리려는 시그널을 지정한 시그널 집합의 주소

sigsuspend 함수는 인자로 지정한 시그널 집합에 설정된 시그널들로 프로세스의 시그널 마스크를 교체하고, 블록되지 않은 시그널이 도착할 때까지 프로세스의 수행을 멈추고 기다립니다. 시그널이 도착하면 프로세스의 시그널 마스크는 이전 설정으로 되돌아갑니다.
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