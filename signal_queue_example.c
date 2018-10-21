#include <unistd.h>
#include <signal.h>

void sig_usr(int signo){
	printf ("caught signal %d\n", signo);
}

int main( void ) {
	sigset_t newmask, oldmask;

	if((signal(SIGUSR1, sig_usr) == SIG_ERR) || signal(SIGUSR2, sig_usr) == SIG_ERR)
		err_sys("signal error");

	sigemptyset(&newmask);
	sigaddset(&newmask, SIGUSR1);
	sigaddset(&newmask, SIGUSR2);

	if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0) /* block SIGUSR*/
		err_sys("SIG_BLOCK error");
	sleep(10); /* SIGUSR* here will remain pending */
	
	if(sigprocmask(SIG_SETMASK, &oldmask , NULL) < 0) /* unblocks SIGUSR*/
		err_sys("sigprocmask error");
	
	if(signal(SIGUSR1, SIG_DFL) == SIG_ERR)
		err_sys("signal error");
	
	if(signal(SIGUSR2, SIG_DFL) == SIG_ERR)
		err_sys("signal error");
	
	printf("SIGUSR* unblocked\n");
	while(1)
		pause();
	exit(EXIT_SUCCESS);
}