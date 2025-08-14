#pragma once

struct resource_handle final {
    uint32_t handle;
    bool IsValidHandle() const {
        return handle != 0;
    }
};

inline uint16_t get_handle_id(resource_handle handle) {
    uint16_t id = handle.handle >> 16;
    return id;
}

inline uint16_t get_handle_meta(resource_handle handle) {
    uint16_t version = handle.handle & 0xFFFF;
    return version;
}
