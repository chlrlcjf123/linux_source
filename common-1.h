#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "helpers.h"

#define FIFO_PATH "fifo"
#define ACT_RELOAD 17

struct request {
	intaction; /* one of ACT_* macros */
};