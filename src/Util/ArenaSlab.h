#pragma once

#include <cassert>
#include <cstdio>

struct free_slot {
    free_slot* next;
};

struct arena_slab {
    uint8_t* data;
    free_slot* free_head;
    size_t slot_size;
    size_t slot_count;
    size_t free_count;
};

inline arena_slab arena_slab_init(size_t capacity, size_t data_size, size_t alignment = 16) {
    assert(capacity > 0);
    assert(data_size > 0);
    assert(alignment > 0 && (alignment & (alignment - 1)) == 0);

    size_t aligned_size = (data_size + alignment - 1) & ~(alignment - 1);
    assert(aligned_size <= capacity);

    // NOTE: This might need changing if you run this game on a smartmop
    if (aligned_size < sizeof(free_slot*)) {
        aligned_size = sizeof(free_slot*);
    }

    size_t slot_count = capacity / aligned_size;
    size_t actual_capacity = slot_count * aligned_size;
    uint8_t* data = (uint8_t*)aligned_alloc(alignment, actual_capacity);
    assert(data != NULL);

    free_slot* current = (free_slot*)data;
    for (size_t i = 0; i < slot_count - 1; i++) {
        free_slot* next = (free_slot*)((uint8_t*)current + aligned_size);
        current->next = next;
        current = next;
    }
    current->next = NULL;

    return arena_slab{
        data, (free_slot*)data, aligned_size, slot_count, slot_count,
    };
};

inline void* arena_slab_alloc(arena_slab* arena) {
    if (!arena->free_head) return NULL;

    void* slot = arena->free_head;
    arena->free_head = arena->free_head->next;
    arena->free_count--;
    return slot;
}

inline void arena_slab_free(arena_slab* arena, void* ptr) {
    free_slot* slot = (free_slot*)ptr;
    slot->next = arena->free_head;
    arena->free_head = slot;
    arena->free_count++;
}

inline void arena_slab_reset(arena_slab* arena) {
    free_slot* current = (free_slot*)arena->data;
    for (size_t i = 0; i < arena->slot_count - 1; i++) {
        free_slot* next = (free_slot*)((uint8_t*)current + arena->slot_size);
        current->next = next;
        current = next;
    }
    current->next = NULL;

    arena->free_head = (free_slot*)arena->data;
    arena->free_count = arena->slot_count;
}

inline void arena_slab_destroy(arena_slab* arena) {
    free(arena->data);
    arena->data = NULL;
    arena->free_head = NULL;
    arena->slot_count = 0;
    arena->free_count = 0;
}

inline void arena_slab_print(arena_slab* arena){
    printf("Capacity: %zu | Size: %zu\n", arena->slot_count, arena->free_count);
}
