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
    Arena *arena = arena_create(1024);
    char *bytes = arena_alloc(arena, 256);
    TEST_EQUAL(arena->end - arena->begin, 1024 - 256);
    TEST_EQUAL(arena->end - arena->begin, 1024 - 256);
    arena_destroy(arena);
}


int main()
{
    SUITE(test_arena_create);
    SUITE(test_arena_alloc);
    WRAP_UP();
    return 0;
}