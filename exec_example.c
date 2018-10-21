#include <unistd.h>
#include <sys/wait.h>
#include "helpers.h"

char *env_init[] = {"USER=unknown", "TERM=xterm", NULL};

int main( void) {
	pid_t pid;
	
	if((pid = fork()) < 0) {
		err_sys(" fork error ");
	} else if(pid == 0) { /* child */
		if(execle("/tmp/echoall", "echoall", "foo", "BAR", NULL, env_init) < 0)
			err_sys("execle error");
	}
	if(wait(NULL) < 0)
		err_sys("wait error");
	if((pid = fork()) < 0) {
		err_sys("fork error");
	} else if(pid == 0) { /*file, no env */
		if(execlp("echoall", "echoall", "only 1 arg", NULL) < 0)
		err_sys("execlp error");
	}
	exit(EXIT_SUCCESS);
}