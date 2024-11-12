CC     := gcc
CFLAGS := -std=c2x \
		  -g -Og -DGARENA_DEBUG \
		  -Werror -Wall -Wextra -Wshadow -Wpedantic -Wconversion \
		  -fanalyzer -fsanitize=undefined

all: garena.o test.o
	$(CC) $(CFLAGS) test.o garena.o -o tests

silent-all:
	@$(MAKE) all > /dev/null 2>&1

test: silent-all
	./tests

clean:
	rm -f *.o
	rm -f tests

.PHONY: all clean test silent-all