#ifndef ARENA_H
#define ARENA_H


#include <stdint.h>
#include <stddef.h>


typedef struct
{
    char *begin;
    char *end;
} Arena;


// Internal alloc/dealloc

// Set the malloc-like allocator for internal use
void arena_set_alloc( void * (*allocator)(size_t size) );

// Set the free-like deallocator for internal use
void arena_set_dealloc( void (*deallocator)(void *));

// Set the default alignment to be used in arena_alloc.
// Must be a power of 2.
//
// As is, this typically is the word alignment of your
// system.
void arena_set_default_alignment(unsigned int align);


// Actual utility functions

// Create an arena. This allocates memory for the arena pointer
// and for the memory of the region specified by `size`.
Arena *arena_create(size_t size);

// Allocate memory within the arena
void *arena_alloc(Arena *arena, size_t size);

// allocate within the arena with a specific alignment.
// alignment must be power of 2.
void *arena_alloc_aligned(Arena *arena, size_t size, unsigned int alignment);

// Deallocate memory associated with arena.
void arena_destroy(Arena *arena);


#endif
