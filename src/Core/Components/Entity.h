#pragma once

#include <fstream>
#include <sstream>

struct entity {
    uint32_t id;
};

inline uint32_t entity_parse_id(std::string line) {
    std::stringstream ss(line);
    std::string type;
    uint32_t id;
    ss >> type >> id;
    return id;
}

inline void entity_save(uint32_t id, std::ofstream& file) {
    file << "E " << id << "\n";
}
