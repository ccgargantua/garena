CFLAGS = -std=c2x \
		 -g -Og \
		 -Wall -Wextra -Wshadow -Wpedantic -Wconversion \
		 -fanalyzer -fsanitize=undefined

all: tests

tests: CC = gcc
tests: garena.o test.o
	$(CC) $(CFLAGS) test.o garena.o -o tests

test: tests
	./tests

clean:
	rm -f garena.o
	rm -f tests

.PHONY: garena tests