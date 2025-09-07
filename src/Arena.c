#include "Arena.h"

#include <assert.h>
#include <string.h>
#include <stdalign.h>
#include <stddef.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

Arena arena_init(size_t capacity) {
    return (Arena) {
        .next = NULL,
        .data = (uint8_t*)malloc(capacity),
        .capacity = capacity,
        .size = 0
    };
}

void arena_free(Arena *arena) {
    free(arena->data);

    // Free linked list of Arenas
    Arena *sentinel = arena->next;
    while (sentinel) {
        Arena *next = sentinel->next;
        free(sentinel->data);
        free(sentinel);
        sentinel = next;
    }

    memset(arena, 0, sizeof(Arena));
}

void arena_reset(Arena *arena) {
    arena->size = 0;

    Arena *sentinel = arena->next;
    while (sentinel) {
        sentinel->size = 0;
        sentinel = sentinel->next;
    }
}

void *arena_alloc(Arena *arena, size_t size) {
    return arena_alloc_aligned(arena, size, DEFAULT_ALIGNMENT);
}

void *arena_alloc_aligned(Arena *arena, size_t data_size, size_t alignment) {
    assert(arena->data);

    size_t current_offset = arena->size;
    size_t aligned_offset = (current_offset + alignment - 1) & ~(alignment - 1);

    if (aligned_offset + data_size <= arena->capacity) {
        void *data_position = &arena->data[aligned_offset];
        arena->size = aligned_offset + data_size;

        return data_position;
    }
    
    if (arena->next == NULL) {
        Arena *next_arena = (Arena*)malloc(sizeof(Arena));
        if (next_arena == NULL) return NULL;

        size_t new_capacity = MAX(arena->capacity * 2, data_size + alignment);

        next_arena->next = NULL;

        next_arena->data = (uint8_t*)malloc(sizeof(uint8_t) * new_capacity);
        if (next_arena->data == NULL) {
            free(next_arena);
            return NULL;
        }

        next_arena->capacity = new_capacity;
        next_arena->size = 0;
        arena->next = next_arena;
    }

    return arena_alloc(arena->next, data_size);
}

