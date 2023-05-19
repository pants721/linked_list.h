CC = gcc

CFLAGS = -std=c11 -O3 -Wall -Wextra -Wpedantic -Wstrict-aliasing
CFLAGS += -Wno-pointer-arith -Wno-newline-eof -Wno-unused-parameter -Wno-gnu-statement-expression
CFLAGS += -Wno-gnu-compound-literal-initializer -Wno-gnu-zero-variadic-macro-arguments

INCFLAGS = -Imunit/munit.h

.PHONY: build clean

build: munit/munit.h munit/munit.c tests.c
	$(CC) $(CFLAGS) -o tests munit/munit.c tests.c

test: build
	./tests

clean:
	rm -f tests

all: build
