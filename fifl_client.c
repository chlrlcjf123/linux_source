#include "common-1.h"

int main(void) {
	int fd;
	struct request req;

	if ((fd = open(FIFO_PATH, O_WRONLY)) < 0)
		err_sys("open error");

	req.action = ACT_RELOAD;
	if(write(fd, &req, sizeof(struct request)) != sizeof(struct request))
		err_sys("write error");

	exit(EXIT_SUCCESS);
}