CC = clang
CFLAGS = -Wall -Werror -pedantic -std=gnu99 -O0 -g
LDFLAGS =

SRC = nmc.c repl.c
OBJ = ${SRC:.c=.o}

all: nmc

nmc: ${OBJ}
	@echo CC -o $@
	@${CC} ${LDFLAGS} -o $@ ${OBJ}

%.o: %.c
	@echo CC $@
	@${CC} -o $@ -c $< ${CFLAGS}

clean:
	@echo cleaning...
	@rm nmc ${OBJ}

.PHONY: all clean
