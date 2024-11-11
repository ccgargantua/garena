CFLAGS = -std=c2x -Wall -Wextra -Wshadow -Wpedantic -Wconversion -fanalyzer -fsanitize=undefined

garena:
	$(CC) $(CFLAGS) garena.c -c -o garena.o

tests: CC = gcc
tests: garena
	$(CC) $(CFLAGS) test.c garena.o -o tests

test: tests
	./tests

debug: CFLAGS += -DGARENA_DEBUG -Og -g
debug: garena

release: CFLAGS += -O3 -Werror -Wall -Wextra
release: garena

clean:
	rm -f garena.o
	rm -f tests

.PHONY: garena tests debug release