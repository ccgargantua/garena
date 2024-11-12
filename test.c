#include "garena.h"
#include "test.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>


void test_arena_create()
{
    constexpr size_t arena_size = 1024;

    Arena *arena = arena_create(arena_size);
    TEST_EQUAL(arena->end - arena->begin, arena_size);
    arena_destroy(arena);
}


void test_arena_alloc()
{
    constexpr size_t arena_size     = 1024;
    constexpr size_t num_bytes      = 256;
    constexpr size_t num_more_bytes = 64;

    Arena *arena = arena_create(arena_size);

    char *bytes = arena_alloc(arena, num_bytes, 1);

    TEST_EQUAL(
        (ptrdiff_t)(arena->end - arena->begin),
        (ptrdiff_t)(arena_size - num_bytes));


    int *more_data = arena_alloc(arena, num_more_bytes, sizeof(int));

    TEST_EQUAL(
        (ptrdiff_t)(arena->end - arena->begin),
        (ptrdiff_t)(arena_size - (num_more_bytes * sizeof(int) + num_bytes)));

    TEST_EQUAL(
        bytes - (char *)more_data,
        num_bytes - num_bytes % sizeof(int));
    arena_destroy(arena);
}


void test_arena_alloc_aligned()
{
    constexpr size_t arena_size         = 1024;
    constexpr size_t allocation1        = 6;
    constexpr size_t allocation2        = 1;
    constexpr unsigned int alignment    = 4;
    constexpr ptrdiff_t expected_offset = alignof(size_t) % allocation1 + allocation2;

    Arena *arena = arena_create(arena_size);

    char *alloc1 = arena_alloc_aligned(arena, allocation1, 1, alignment);
    char *alloc2 = arena_alloc_aligned(arena, allocation2, 1, alignment);
    TEST_EQUAL(alloc2, alloc1 - expected_offset);

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
