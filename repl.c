#include "repl.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static repl_cmd
find_command(struct repl_table *table, const char *buffer)
{
	while (table->cmd) {
		if (strcmp(table->cmd, buffer) == 0)
			return table->func;
		else
			++table;
	}
	return NULL;
}

int
repl_run(struct repl_table *table, FILE *file, void *arg)
{
	char buffer[256], *term;
	int ret;

	fputs("> ", stdout);
	fflush(stdout);

	if (fgets(buffer, sizeof(buffer), file)) {
		if ((term = strchr(buffer, '\n')))
			*term = '\0';

		repl_cmd cmd = find_command(table, buffer);
		if (!cmd)
			return 0;
		ret = cmd(arg);
		if (ret > 0) {
			printf("--- %d\n", ret);
			return 0;
		} else
			return ret;
	}
	fputc('\n', stdout);
	return 1;
}

