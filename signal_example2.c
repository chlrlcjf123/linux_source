#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sig_quit(int signo) {
	printf("caught SIGQUIT\n");
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		err_sys("can’t reset SIGQUIT");
}

int main(void) {
	sigset_t newmask, oldmask , pendmask;

	if (signal(SIGQUIT, sig_quit) == SIG_ERR )
		err_sys("can’t catch SIGQUIT");

	sigemptyset (&newmask);
	sigaddset (&newmask, SIGQUIT); /* block SIGQUIT */

	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask ) < 0)
		err_sys("SIG_BLOCK error");

	sleep(5); /* SIGQUIT here wi l l remain pending */

	if(sigpending(&pendmask) < 0)
		err_sys("sigpending error");

	if(sigismember(&pendmask, SIGQUIT))
		printf("\nSIGQUIT pending\n");
	
	/* Reset signal mask which unblocks SIGQUIT */
	if(sigprocmask(SIG_SETMASK, &oldmask , NULL) < 0)
		err_sys("SIG_SETMASK error");

	printf("SIGQUIT unblocked\n");
	sleep(5); /* SIGQUIT here wi l l core dump */
	exit(EXIT_SUCCESS);
}