#pragma once

// #include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

struct transform {
    glm::vec3 position = {0.0f, 0.0f, 0.0f};
    glm::quat rotation = {1.0f, 0.0f, 0.0f, 0.0f};
    glm::vec3 scale    = {1.0f, 1.0f, 1.0f};

    glm::mat4 cached_matrix = glm::mat4(1.0f);
    bool matrix_dirty = true;
};

glm::mat4 transform_get_matrix(transform* transform);
glm::vec3 transform_to_local_space(transform* transform, const glm::vec3& world_position);
glm::vec3 transform_to_world_space(transform* transform, const glm::vec3& local_position);
