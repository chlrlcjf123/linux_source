//atexit() 함수 설명 : 프로그램이 종료되거나 exit()함수에 의해 종료될때 atexit()에 등록한 함수를 실행한다.
//참고 : atexit()와 _exit()함수의 차이점은 _exit() 함수는 시그널 위에서 등록한 콜백 함수 등을 무시하고 바로 종료한다.
#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"

void my_exit1 (void) { printf("first exit handler\n"); }
void my_exit2 (void) { printf("second exit handler\n"); }

int main(void){
	if(atexit(my_exit2) != 0)
		err_sys("can’t register my_exit2");
	if(atexit (my_exit1) != 0)
		err_sys("can’t register my_exit1");
	if( atexit (my_exit1) != 0)
		err_sys("can’t register my_exit1");
	printf("main is done\n");
	return(0);
}