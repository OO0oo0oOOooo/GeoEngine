#pragma once

#include <fstream>
#include <sstream>

struct entity {
    uint32_t id;
};

inline void entity_save(std::ofstream& file) {
    file << "E " << "\n";
}
