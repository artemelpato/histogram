export

CC = tcc
INCLUDE = $(shell realpath include)
CFLAGS = -Wall -Wextra -Werror -pedantic -g -I$(INCLUDE) -O2
LDFLAGS = -lm
BUILDDIR = $(shell realpath build)
EXE = $(BUILDDIR)/run

.PHONY.: clean all

all:
	$(MAKE) -C src --no-print-directory
	$(CC) $(LDFLAGS) $(BUILDDIR)/*.o -o $(EXE)

clean:
	@rm -fv $(BUILDDIR)/*
