#pragma once

#include <glm/gtx/quaternion.hpp>

struct camera {
    glm::vec3 position = {0, 0, 0};
    glm::quat rotation = {1, 0, 0, 0};

    float fov = 100.0f;
    float aspect_ratio = 1.0f;
    float width = 1920.0f;
    float height = 1080.0f;
    float near_plane = -1.0f;
    float far_plane = 1.0f;

    glm::mat4 view_matrix = glm::mat4(1.0f);
    glm::mat4 projection_matrix = glm::mat4(1.0f);
    glm::mat4 cached_vp_matrix = glm::mat4(1.0f);
    bool matrix_dirty = true;
};

camera camera_init(glm::vec3 position = {0, 0, 0}, glm::quat rotation = {1, 0, 0, 0}, float width = 1920.0f, float height = 1080.0f, float near_plane = -1.0f, float far_plane = 1.0f);
glm::mat4 get_vp_matrix(camera* camera);

void set_window_size(void* context, void* data);
