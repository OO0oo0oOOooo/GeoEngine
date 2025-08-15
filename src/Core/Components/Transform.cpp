#include "Transform.h"


#include <glm/gtc/matrix_inverse.hpp>

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
