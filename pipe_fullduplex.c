#include <ctype.h>
#include <unistd.h>
#include "helpers.h"

#define MAXLINE 1024

int main(void) { // EXERCISE : improve error handling !
	int n, p2c[2] ,c2p[2];
	pid_t pid ;
	char line[MAXLINE];

	if(pipe(p2c) < 0 || pipe(c2p) < 0)
		err_sys("pipe error");
	if((pid = fork()) < 0){
		err_sys("fork error");
	} else if( pid > 0) { /* parent */
		close(p2c[0]);
		close(c2p[1]);
		write(p2c[1],"HELLO, WORLD! \n", 14);
		n = read(c2p[0], line, MAXLINE);
		write(STDOUT_FILENO, line ,n);
	} else { /* chi ld */
		close (p2c[1]);
		close (c2p[0]);
		n = read(p2c[0], line, MAXLINE);
		line[0] = tolower(line[0]);
		write(c2p[1], line, n);
	}
	exit(EXIT_SUCCESS);
}