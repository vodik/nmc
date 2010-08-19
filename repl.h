#ifndef REPL_H
#define REPL_H

#include <stdio.h>

typedef int (*repl_cmd)(void *arg);

struct repl_table {
	const char *cmd;
	repl_cmd func;
};

int repl_run(struct repl_table *table, FILE *file, void *arg);

#endif
