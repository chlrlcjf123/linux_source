#include <unistd.h>
#include "helpers.h"

int main(void) {
	pid_t pid;
	
	printf("before fork (%d)\n", getpid());
	if((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {
		/* child */
		printf("hi from parent! (%d)\n", getpid());
	}
	printf("bye (%d)\n", getpid());
	exit(EXIT_SUCCESS);
}