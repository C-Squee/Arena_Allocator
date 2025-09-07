#ifndef ARENA_H
#define ARENA_H
#include <stdlib.h>

typedef union {
    long long ll;
    long double ld;
    void *p;
} max_align_t_c99;

typedef struct Arena {
    struct Arena *next;
    uint8_t *data;
    size_t capacity;
    size_t size;
} Arena;

Arena arena_init(size_t capacity);

void arena_free(Arena *arena);

void arena_reset(Arena *arena);

void *arena_alloc(Arena *arena, size_t size);

#endif // ARENA_H
