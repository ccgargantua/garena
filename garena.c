#include "garena.h"


#include <stdlib.h>



#ifndef GARENA_TEST
    #include <assert.h>
#else
    #define GARENA_DEBUG
    #define assert(cond, msg)
#endif



_Static_assert(__STDC_VERSION__ >= 201112L,
               "Must compile for C11 or above");



// Debug utilities
#ifdef GARENA_DEBUG

    #include <stdio.h>
    #include <stdarg.h>

    void dbg_printf(const char *format, ...)
    {
            va_list args;
            va_start(args, format);
            fprintf(stderr, format, args);
            va_end(args);
    }

#else
    void dbg_printf(const char *format, ...) { (void) format; }
#endif



// Internal allocation/deallocation
static void * (*alloc)(size_t size) = malloc;
static void (*dealloc)(void *) = free;

void garena_set_alloc( void * (*allocator)(size_t size) )
{
    assert(allocator);
    alloc = allocator;
}

void garena_set_dealloc( void (*deallocator)(void *))
{
    assert(deallocator);
    dealloc = deallocator;
}



Arena *arena_create(ptrdiff_t size)
{
    assert(size > 0);

    Arena *arena = alloc(sizeof(Arena));
    assert(arena);

    arena->begin = alloc(size);
    assert(arena->begin);

    arena->end = arena->begin + size;

    return arena;
}


void *arena_alloc(Arena *arena, ptrdiff_t size)
{
    assert(arena);
    assert(arena->end - size > arena->begin);
    return ( arena->end -= size );
}


void arena_destroy(Arena *arena)
{
    assert(arena);
    assert(arena->begin);
    dealloc(arena->begin);
    dealloc(arena);
}