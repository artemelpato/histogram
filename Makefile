CC=clang
CFLAGS=-Wall -Wextra -Werror -pedantic -g -I. -O2
EXE=run

.PHONY.: clean all

all: $(EXE)

$(EXE): main.c histogram.h vector.h histogram.c
	$(CC) $(CFLAGS) -o $@ main.c histogram.c

clean:
	rm -fv $(EXE)
