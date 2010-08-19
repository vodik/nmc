#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include "repl.h"

static int fd;
static int cmd_list(void *arg);

struct repl_table table[] = {
	{ "list", cmd_list },
	{ NULL,   NULL }
};

static int
cmd_list(void *arg)
{
	return write(fd, "LIST", 5);
}

int main()
{
	struct sockaddr_un addr;
	size_t addr_len;
	int ret;

	fd = socket(PF_UNIX, SOCK_STREAM, 0);
	if (fd < 0) {
		perror("socket");
		exit(1);
	}

	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path, "/tmp/nmd_ctrl");
	addr_len = sizeof(addr);

	if (connect(fd, (struct sockaddr *)&addr, addr_len) != 0) {
		perror("connect");
		exit(1);
	}

	while (1) {
		if ((ret = repl_run(table, stdin, NULL)) != 0)
			exit(ret);
	}

	close(fd);
	return 0;
}
