#pragma once

#include "Core/ComponentRegistry.h"
#include "Core/Components/Camera.h"
#include "Core/Components/Renderable.h"
#include "Core/Components/Transform.h"
#include "Rendering/Renderer.h"
#include "Rendering/ResourceManager.h"

inline void default_render(ComponentRegistry& registry, Renderer* renderer, camera* camera_c) {
    for (uint32_t entity : registry.m_Entities) {
        transform* transform_c = registry.GetComponent<transform>(entity);
        renderable* render_c = registry.GetComponent<renderable>(entity);

        if (transform_c && render_c) {
            mesh* mesh_r = ResourceManager::GetMesh(render_c->mesh_handle);
            material* mat = ResourceManager::GetMaterial(render_c->material_handle);
            render_command cmd = mesh_create_render_command(mesh_r);

            glm::mat4 vp = get_vp_matrix(camera_c);
            glm::mat4 m = transform_get_matrix(transform_c);

            material_bind(mat, vp, m);
            renderer->RenderMesh(cmd);
        }
    }
}
