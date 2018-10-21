#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include "helpers.h"

#define BUFFSIZE 4096
#define FIFO_PATH "fifo"

int main(void) {
	int n, fd;
	char buf[BUFFSIZE];
	
	if(mkfifo(FIFO_PATH, S_IRUSR|S_IWUSR) < 0 && errno != EEXIST)
		err_sys("fifo error");

		printf("opening %s...\n", FIFO_PATH);

	if((fd = open(FIFO_PATH, O_RDONLY)) < 0)
		err_sys("open error");

		printf("entering main loop...\n");

	while((n = read(fd, buf, BUFFSIZE)) > 0)
		if(write(STDOUT_FILENO, buf, n) != n)
			err_sys(" write error");

	if(n < 0) err_sys("read error");
		exit(EXIT_SUCCESS);
}