CC = gcc
CFLAGS = -std=c11 -pedantic

garena:
	$(CC) $(CFLAGS) garena.c -c -o garena.o

tests: garena
	$(CC) $(CFLAGS) test.c garena.o -o tests

debug: CFLAGS += -DGARENA_DEBUG -O0 -g -fsanitize=undefined
debug: garena

release: CFLAGS += -O3 -Werror -Wall -Wextra
release: garena

clean:
	rm -f garena.o
	rm -f tests

.PHONY: garena tests debug release