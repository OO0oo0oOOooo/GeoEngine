#include "Transform.h"

#include <cstring>
#include <sstream>
#include <fstream>

#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Core/ComponentRegistry.h"

glm::mat4 transform_get_matrix(transform* transform) {
    if (transform->matrix_dirty) {
        transform->cached_matrix = glm::translate(glm::mat4(1.0f), transform->position) *
                                   glm::mat4_cast(transform->rotation) *
                                   glm::scale(glm::mat4(1.0f), transform->scale);
        transform->matrix_dirty = false;
    }

    return transform->cached_matrix;
}

glm::vec3 transform_to_local_space(transform* transform, const glm::vec3& world_position) {
    glm::mat4 world_to_local = glm::inverse(transform_get_matrix(transform));
    glm::vec4 local_pos = world_to_local * glm::vec4(world_position, 1.0f);
    return glm::vec3(local_pos);
}

glm::vec3 transform_to_world_space(transform* transform, const glm::vec3& local_position) {
    glm::mat4 local_to_world = transform_get_matrix(transform);
    glm::vec4 world_pos = local_to_world * glm::vec4(local_position, 1.0f);
    return glm::vec3(world_pos);
}

void transform_print(transform* transform) {
    std::cout << "==========================" << "\n";
    std::cout << "Position: " << glm::to_string(transform->position) << "\n";
    std::cout << "Rotation: " << glm::to_string(transform->rotation) << "\n";
    std::cout << "Scale: " << glm::to_string(transform->scale) << "\n";
    std::cout << "Dirty?: " << transform->matrix_dirty << "\n";
    std::cout << "Matrix: " << glm::to_string(transform->cached_matrix) << "\n";
    std::cout << "==========================" << "\n";
}

void transform_save(const void* data, std::ofstream& file) {
    const transform* t = static_cast<const transform*>(data);

    file << "T " << t->position.x << " " << t->position.y << " " << t->position.z 
    << " " << t->rotation.w << " " << t->rotation.x << " " << t->rotation.y << " " << t->rotation.z << " " 
    << t->scale.x << " " << t->scale.y << " " << t->scale.z << "\n";
}

void transform_load(std::string line, void* buffer) {
    transform t {
        .matrix_dirty = true,
    };

    std::stringstream ss(line);
    std::string type;
    ss >> type >> t.position.x >> t.position.y >> t.position.z
    >> t.rotation.w >> t.rotation.x >> t.rotation.y >> t.rotation.z
    >> t.scale.x >> t.scale.y >> t.scale.z;

    memcpy(buffer, &t, sizeof(transform));
}
