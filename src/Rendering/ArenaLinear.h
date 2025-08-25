#pragma once

#include <cassert>
#include <cstdio>

struct arena_linear {
    uint8_t* data;
    size_t capacity;
    size_t size;
    size_t alignment;
};

inline arena_linear arena_linear_init(size_t capacity, size_t alignment = 16) {
    assert(alignment > 0 && (alignment & (alignment - 1)) == 0);
    uint8_t* data = (uint8_t*)aligned_alloc(alignment, capacity);
    assert(data != NULL);

    return arena_linear{
        data,
        capacity,
        0,
        alignment,
    };
}

inline void* arena_linear_alloc(arena_linear* arena, size_t size) {
    assert(size > 0);
    size_t aligned_offset = (arena->size + arena->alignment - 1) & ~(arena->alignment - 1);
    assert(aligned_offset + size <= arena->capacity && "Allocation exceeds arena capacity");

    void* ptr = &arena->data[aligned_offset];
    arena->size = aligned_offset + size;

    return ptr;
}

inline void arena_linear_reset(arena_linear* arena) {
    arena->size = 0;
}

inline void arena_linear_destroy(arena_linear* arena) {
    free(arena->data);
    arena->data = nullptr;
    arena->capacity = 0;
    arena->size = 0;
    arena->alignment = 0;
}

inline void arena_linear_print(arena_linear* arena) {
    printf("Capacity: %zu | Size: %zu\n", arena->capacity, arena->size);
}
