#ifndef ARENA_H
#define ARENA_H
#include <stdlib.h>
#include <stdint.h>

#define DEFAULT_ALIGNMENT (sizeof(max_align_t_c99))

/*
 * max_align_t_c99 - Union to ensure maximum alignment in C99
 *
 * This union contains types known to require strict alignment on most platforms:
 *   - `long long`: typically requires 8-byte alignment (or more on some systems).
 *   - `long double`: often has the largest alignment requirements among scalar types.
 *   - `void *`: pointer types, to ensure pointer alignment compatibility.
 */
typedef union {
    long long ll;
    long double ld;
    void *p;
} max_align_t_c99;

/**
 * @struct Arena
 * @brief Simple memory arena allocator structure.
 *
 * @var Arena::next
 * Pointer to the next Arena block, allowing linked arenas for growth.
 *
 * @var Arena::data
 * Pointer to the allocated memory buffer.
 *
 * @var Arena::capacity
 * Total size of the memory buffer in bytes.
 *
 * @var Arena::size
 * Current offset into the buffer, i.e., how much memory is used.
 */
typedef struct Arena {
    struct Arena *next;
    uint8_t *data;
    size_t capacity;
    size_t size;
} Arena;

/**
 * @brief Initialize an Arena with a given capacity.
 *
 * Allocates a new Arena with an internal buffer of @p capacity bytes.
 *
 * @param capacity Number of bytes to allocate for the arena.
 * @return Arena struct ready for allocations.
 */
Arena arena_init(size_t capacity);

/**
 * @brief Free all resources associated with the Arena.
 *
 * Frees the memory buffer and any linked Arena blocks.
 * After this call, the Arena should not be used.
 *
 * @param arena Pointer to the Arena to free.
 */
void arena_free(Arena *arena);

/**
 * @brief Reset the Arena to empty state.
 *
 * Resets the @c size field to zero, making the entire buffer available
 * for reuse without actually freeing memory.
 * Useful for quickly discarding all allocations.
 *
 * @param arena Pointer to the Arena to reset.
 */
void arena_reset(Arena *arena);

/**
 * @brief Allocate memory from the Arena with default alignment.
 *
 * Allocates @p size bytes from the arena's buffer, if enough space exists.
 * Returns a pointer to the allocated memory, or NULL if out of space.
 * The allocated memory is not initialized.
 *
 * @param arena Pointer to the Arena struct.
 * @param size Number of bytes to allocate.
 * @return Pointer to allocated memory, or NULL on failure.
 */
void *arena_alloc(Arena *arena, size_t size);

/**
 * @brief Allocate memory from the Arena with set alignment.
 *
 * Allocates @p size bytes from the arena's buffer, if enough space exists.
 * Returns a pointer to the allocated memory, or NULL if out of space.
 * The allocated memory is not initialized.
 *
 * @param arena Pointer to the Arena struct.
 * @param size Number of bytes to allocate.
 * @return Pointer to allocated memory, or NULL on failure.
 */
void *arena_alloc_aligned(Arena *arena, size_t size, size_t alignment);

#endif // ARENA_H
