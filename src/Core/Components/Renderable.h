#pragma once

#include <fstream>
#include <sstream>

#include "../../Rendering/ResourceHandle.h"

struct renderable {
    resource_handle mesh_handle;
    resource_handle material_handle;
};

// TODO: cannot use old string handles
inline renderable renderable_load(std::string line) {
    renderable r {};

    std::stringstream ss(line);
    std::string type;
    ss >> type >> r.material_handle.handle >> r.mesh_handle.handle;

    return r;
}

inline void renderable_save(renderable* r, std::ofstream& file) {
    file << "R " << r->material_handle.handle << " " << r->mesh_handle.handle << "\n";
}
