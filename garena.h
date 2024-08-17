#ifndef GARENA_H
#define GARENA_H


#include <stddef.h>


typedef struct
{
    char *begin;
    char *end;
} Arena;


void garena_set_alloc  ( void * (*allocator)(size_t size) );
void garena_set_dealloc( void (*deallocator)(void *));


Arena *arena_create(ptrdiff_t size);
void *arena_alloc  (Arena *arena, ptrdiff_t size);
void arena_destroy (Arena *arena);


#endif