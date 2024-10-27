#include "garena.h"


#include <stdlib.h>
#include <assert.h>


// Primarily used for assertions of bounds
static inline ptrdiff_t ptr_diff(void *p1, void *p2)
{
    return (ptrdiff_t)p1 - (ptrdiff_t)p2;
}


// Internal allocation/deallocation
static void * (*alloc)(size_t size) = malloc;
static void (*dealloc)(void *)      = free;


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


// this should typically be platform's word alignment
static unsigned int default_alignment = _Alignof(void *);

void garena_set_default_alignment(unsigned int align)
{
    assert( (align & (align - 1)) == 0 ); // assert alignment is power of 2
    default_alignment = align;
}


Arena *arena_create(size_t size)
{
    assert(size > 0);

    Arena *arena = alloc(sizeof(Arena));
    assert(arena);

    arena->begin = alloc(size);
    assert(arena->begin);

    arena->end = arena->begin + size;

    return arena;
}


void *arena_alloc(Arena *arena, size_t size)
{
    return arena_alloc_aligned(arena, size, default_alignment);
}


void *arena_alloc_aligned(Arena *arena, size_t size, unsigned int align)
{
    assert(arena);
    assert( (align & (align - 1)) == 0 );          // assert align is power of 2

    arena->end -= size;                            // unaligned

    arena->end += (uintptr_t)(arena->end) % align; // TODO get fancy here
    assert( ptr_diff(arena->end, arena->begin) > 0 );

    return arena->end;
}


void arena_destroy(Arena *arena)
{
    assert(arena);
    dealloc(arena->begin);
    dealloc(arena);
}