#include "garena.h"
#include "test.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>


void test_arena_create()
{
    Arena *arena = arena_create(1024);
    TEST_EQUAL(arena->end - arena->begin, 1024);
    arena_destroy(arena);
}


void test_arena_alloc()
{
    const size_t arena_size = 1024;
    Arena *arena = arena_create(arena_size);

    const size_t num_bytes = 256;

    __attribute__((unused))
        char *bytes = arena_alloc(arena, num_bytes);

    TEST_EQUAL(
        (ptrdiff_t)(arena->end - arena->begin),
        (ptrdiff_t)(arena_size - num_bytes));

    const size_t num_more_bytes = 64;

    __attribute__((unused))
        int *more_data = arena_alloc(arena, num_more_bytes * sizeof(int));

    TEST_EQUAL(
        (ptrdiff_t)(arena->end - arena->begin),
        (ptrdiff_t)(arena_size - (num_more_bytes * sizeof(int) + num_bytes)));
    arena_destroy(arena);
}


void test_arena_alloc_aligned()
{
    Arena *arena = arena_create(1024);
    char *alloc1 = arena_alloc_aligned(arena, 6, 4);
    char *alloc2 = arena_alloc_aligned(arena, 1, 4);
    TEST_EQUAL(alloc2, alloc1 - 3);
    arena_destroy(arena);
}


int main()
{
    SUITE(test_arena_create);
    SUITE(test_arena_alloc);
    SUITE(test_arena_alloc_aligned);
    WRAP_UP();
    return 0;
}
