CC=clang
CFLAGS=-Wall -Wextra -Werror -pedantic -g -I.
EXE=run

.PHONY.: clean all

all: run

run: main.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -fv vector
