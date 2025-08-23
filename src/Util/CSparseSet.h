#pragma once

#include <cstring>

#include "Rendering/ArenaSlab.h"

#define SPARSE_SET_INVALID 0xFFFFFFFF

// TODO: remove vectors?
struct sparse_set {
    arena_slab arena;
    size_t capacity;
    size_t component_size;

    std::vector<void*> dense;
    std::vector<uint32_t> sparse;
    std::vector<uint32_t> entities;
};

inline void ensure_capacity(sparse_set* ss, uint32_t entity) {
    if (entity >= ss->sparse.size()) {
        ss->sparse.resize(entity + 1, SPARSE_SET_INVALID);
    }
}

inline void sparse_set_init(sparse_set* ss, size_t capacity, size_t component_size) {
    ss->capacity = capacity;
    ss->component_size = component_size;
    ss->arena = arena_slab_init(capacity, component_size);

    ss->dense.reserve(128);
    ss->entities.reserve(128);
    ss->sparse.resize(128, SPARSE_SET_INVALID);
}

inline bool sparse_set_contains(sparse_set* ss, uint32_t entity) {
    if (entity >= ss->sparse.size()) return false;

    uint32_t index = ss->sparse[entity];
    return index != SPARSE_SET_INVALID && index < ss->dense.size() && ss->entities[index] == entity;
}

inline void* sparse_set_get(sparse_set* ss, uint32_t entity) {
    ensure_capacity(ss, entity);
    if(!sparse_set_contains(ss, entity)) {
        return nullptr;
    }

    uint32_t dense_index = ss->sparse[entity];
    return ss->dense[dense_index];
}

inline void sparse_set_insert(sparse_set* ss, uint32_t entity, void* component_data) {
    ensure_capacity(ss, entity);
    uint32_t dense_index = ss->dense.size();

    void* data = arena_slab_alloc(&ss->arena);
    memcpy(data, component_data, ss->component_size);

    ss->dense.push_back(data);
    ss->entities.push_back(entity);
    ss->sparse[entity] = dense_index;
}

inline void sparse_set_remove(sparse_set* ss, uint32_t entity) {
    if (!sparse_set_contains(ss, entity)) return;
    uint32_t dense_index = ss->sparse[entity];
    uint32_t last_index = ss->dense.size() - 1;

    if (dense_index != last_index) {
        ss->dense[dense_index] = ss->dense[last_index];
        ss->entities[dense_index] = ss->entities[last_index];
        ss->sparse[ss->entities[dense_index]] = dense_index;
    }

    arena_slab_free(&ss->arena, ss->dense[dense_index]);
    ss->dense.pop_back();
    ss->entities.pop_back();
    ss->sparse[entity] = SPARSE_SET_INVALID;
}
