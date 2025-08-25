#pragma once

#include <cstring>
#include <fstream>
#include <sstream>

#include "../../Rendering/ResourceHandle.h"

struct renderable {
    resource_handle mesh_handle;
    resource_handle material_handle;
};

// TODO: cannot use old string handles
inline void renderable_load(std::string line, void* buffer) {
    renderable r {};

    std::stringstream ss(line);
    std::string type;
    ss >> type >> r.material_handle.handle >> r.mesh_handle.handle;

    memcpy(buffer, &r, sizeof(renderable));
}

inline void renderable_save(const void* data, std::ofstream& file) {
    const renderable* r = static_cast<const renderable*>(data);

    file << "R " << r->material_handle.handle << " " << r->mesh_handle.handle << "\n";
}
