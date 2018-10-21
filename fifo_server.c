#include "common-1.h"
#define BUFFSIZE 4096
#define MOTD_PATH "/etc/motd"

void print_motd (void) {
	int fd, n;
	char buf[BUFFSIZE];
	if((fd = open(MOTD_PATH, O_RDONLY)) < 0)
		err_sys("open error");
	while((n = read(fd, buf, BUFFSIZE)) > 0)
		if(write(STDOUT_FILENO, buf, n) != n)
			err_sys("write error");
	close(fd);
}

int main( void ) {
	int fd;
	struct request req ;
	
	if(mkfifo(FIFO_PATH, S_IRUSR | S_IWUSR) < 0 && errno != EEXIST )
		err_sys("fifo error");
	if((fd = open( FIFO_PATH, O_RDWR)) < 0)
		err_sys("open error");
	print_motd();
	for(;;) {
		if(read(fd, &req, sizeof(struct request)) != sizeof(struct request))
			continue; /* part ial read or error */
		switch(req.action) {
			case ACT_RELOAD:
				printf(" **** reload ****\n");
				print_motd();
				break;
			default :
				printf(" **** invalid request ****\n");
				break;
		}
	}
	exit(EXIT_SUCCESS);
}