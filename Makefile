CC=clang
CFLAGS=-Wall -Wextra -Werror -pedantic -g -I.
EXE=run

.PHONY.: clean all

all: $(EXE)

$(EXE): main.c histogram.h vector.h
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -fv $(EXE)
