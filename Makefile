CC=clang
CFLAGS=-Wall -Wextra -Werror -pedantic -g 
EXE=run

.PHONY.: clean all

all: vector

vector: vector.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -fv vector
