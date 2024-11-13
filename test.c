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
    constexpr size_t arena_size         = 1024;
    constexpr size_t num_bytes          = 256;
    constexpr size_t num_more_bytes     = 64;

    constexpr ptrdiff_t expected_offset = (arena_size - (num_more_bytes * sizeof(int) + num_bytes));

    Arena *arena = arena_create(arena_size);

    char *bytes = arena_alloc(arena, num_bytes, 1);


    TEST_EQUAL(
        (ptrdiff_t)(arena->end - arena->begin),
        (ptrdiff_t)(arena_size - num_bytes));


    int *more_data = arena_alloc(arena, num_more_bytes, sizeof(int));


    TEST_EQUAL(
        (ptrdiff_t)(arena->end - arena->begin),
        expected_offset);


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


void test_failures()
{
    TEST_FALSE(garena_set_default_alignment(3));
    TEST_NULL(arena_create(0));
    TEST_NULL(arena_alloc(NULL, 0, 0));
    TEST_NULL(arena_alloc_aligned(NULL, 0, 0, 0));

    constexpr size_t arena_size = 10;

    Arena *arena = arena_create(arena_size);
    char *end = arena->end;


    TEST_NULL(arena_alloc_aligned(arena, 0, 0, 3));


    arena_alloc(arena, arena_size, 1);


    TEST_NULL(arena_alloc(arena, 1, 1));


    arena->end = end;


    TEST_NULL(arena_alloc(arena, (size_t)PTRDIFF_MAX + 1, 1));
    TEST_NULL(arena_alloc(arena, arena_size + 1, 1));

    TEST_NULL(arena_alloc_aligned(arena, 0, 0, 3));
    TEST_NULL(arena_alloc_aligned(arena, (size_t)PTRDIFF_MAX + 1, 1, 0));
    TEST_NULL(arena_alloc_aligned(arena, arena_size + 1, 1, 0));



    arena_destroy(arena);
}


int main()
{
    SUITE(test_arena_create);
    SUITE(test_arena_alloc);
    SUITE(test_arena_alloc_aligned);
    SUITE(test_failures);
    WRAP_UP();
    return 0;
}
