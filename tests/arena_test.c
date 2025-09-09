#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#include "arena.h"

Arena arena;

static int is_aligned(void *ptr, size_t alignment) {
    return ((uintptr_t)ptr % alignment) == 0;
}

void test_arena_basic() {
    size_t capacity = 64;
    arena = arena_init(capacity);

    // Allocate 16 bytes
    void *ptr1 = arena_alloc(&arena, 16);
    (void)ptr1;
    assert(ptr1 != NULL);
    assert(is_aligned(ptr1, sizeof(max_align_t_c99)));

    // Allocate another 16 bytes
    void *ptr2 = arena_alloc(&arena, 16);
    (void)ptr2;
    assert(ptr2 != NULL);
    assert(is_aligned(ptr2, sizeof(max_align_t_c99)));
    assert(ptr2 > ptr1);

    // Allocate chunk that exceeds capacity of first arena (to test linked list allocation)
    void *ptr3 = arena_alloc(&arena, capacity * 2);
    (void)ptr3;
    assert(ptr3 != NULL);
    assert(is_aligned(ptr3, sizeof(max_align_t_c99)));
    assert(arena.next != NULL);

    // Reset the arena (should reset sizes of all linked arenas)
    arena_reset(&arena);
    assert(arena.size == 0);
    assert(arena.next->size == 0);

    // Allocate again after reset
    void *ptr4 = arena_alloc(&arena, 8);
    (void)ptr4;
    assert(ptr4 != NULL);
    assert(is_aligned(ptr4, sizeof(max_align_t_c99)));

    // Free the arena and its linked arenas
    arena_free(&arena);

    printf("All tests passed.\n");
}

int main(void) {
    test_arena_basic();
}
