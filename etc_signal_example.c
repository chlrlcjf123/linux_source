/*
strsignal 함수는 인자로 받은 시그널을 가리키는 이름을 문자열로 리턴합니다.
인자로 받은 시그널이 없으면 NULL을 리턴합니다.

sighold 함수는 인자로 받은 시그널을 프로세스의 시그널 마스크에 추가합니다. 
시그널 마스크에 추가된 시그널은 블록되어 해당 시그널을 받지 않습니다.

sigrelse 함수는 프로세스의 시그널 마스크에서 시그널을 해제합니다.
*/

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void handler(int signo) {
        char *s;
        s = strsignal(singo);
        printf("Received Signal : %s ", s);
}

int main(void) {
        if(sigset(SIGINT, handler) == SIG_ERR) {
                perror("sigset");
                exit(1);
        }

        sighold(SIGINT);
        pause();
        return 0;
}