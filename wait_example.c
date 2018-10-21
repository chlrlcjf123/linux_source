#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "helpers.h"

int main(void) {
	pid_t pid;
	int status;

	if((pid = fork()) < 0)
		err_sys ( " fork error " ) ;
	else if(pid == 0) {
		printf("hi from child\n");
		exit(7);
	} else { /* parent */
		if(wait(&status) != pid)
			err_sys("wait error");
			printf("hi from parent\n");
		if(WIFEXITED(status))
			printf("normal termination , exit status = %d\n", WEXITSTATUS(status));
		else if(WIFSIGNALED(status))
			printf("abnormal termination, signal number = %d\n", WTERMSIG(status));
	}
	exit(EXIT_SUCCESS);
}