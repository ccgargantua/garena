#ifndef GARENA_H
#define GARENA_H


#include <stdint.h>
#include <stddef.h>


typedef struct
{
    char *begin;
    char *end;
} Arena;


void garena_set_alloc    ( void * (*allocator)(size_t size) );
void garena_set_dealloc  ( void (*deallocator)(void *));
void garena_set_alignment(unsigned int align);


Arena *arena_create       (size_t size);
void  *arena_alloc        (Arena *arena, size_t size);
void  *arena_alloc_aligned(Arena *arena, size_t size, unsigned int alignment);
void  arena_destroy       (Arena *arena);


#endif