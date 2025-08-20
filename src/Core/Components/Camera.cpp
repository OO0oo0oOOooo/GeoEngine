#include "Camera.h"

#include <fstream>
#include <sstream>

#include "Events/EventDefs.h"

camera camera_init(glm::vec3 position, glm::quat rotation, float near_plane, float far_plane) {
    glm::mat4 v = glm::inverse(glm::translate(glm::mat4(1.0f), position));
    glm::mat4 p = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, near_plane, far_plane);

    camera cam{
        .position = position,
        .rotation = rotation,
        .near_plane = near_plane,
        .far_plane = far_plane,

        .view_matrix = v,
        .projection_matrix = p,
        .cached_vp_matrix = p * v,
        .matrix_dirty = false,
    };

    return cam;
}

glm::mat4 get_vp_matrix(camera* camera) {
    if (camera->matrix_dirty) {
        camera->view_matrix = glm::inverse(glm::translate(glm::mat4(1.0f), camera->position) * glm::mat4_cast(camera->rotation));

        camera->cached_vp_matrix = camera->projection_matrix * camera->view_matrix;
        camera->matrix_dirty = false;
    }

    return camera->cached_vp_matrix;
}

void set_window_size(void* context, void* data) {
    camera* cam = (camera*)context;
    edata8_u* event = (edata8_u*)data;
    float width = event->f[0];
    float height = event->f[1];
    cam->projection_matrix = glm::ortho(0.0f, width, 0.0f, height, cam->near_plane, cam->far_plane);
    cam->matrix_dirty = true;
}

camera camera_load(std::string line) {
    camera c {
        .projection_matrix = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f),
        .matrix_dirty = true,
    };

    std::stringstream ss(line);
    std::string type;
    ss >> type >> c.position.x >> c.position.y >> c.position.z >>
    c.rotation.w >> c.rotation.x >> c.rotation.y >> c.rotation.z >>
    c.near_plane >> c.far_plane >> c.fov >> c.aspect_ratio;

    return c;
}

void camera_save(camera* c, std::ofstream& file) {
    file << "C " << c->position.x << " " << c->position.y << " " << c->position.z << " " 
    << c->rotation.w << " " << c->rotation.x << " " << c->rotation.y << " " << c->rotation.z << " " 
    << c->near_plane << " " << c->far_plane << " " << c->fov << " " << c->aspect_ratio << "\n";
}
