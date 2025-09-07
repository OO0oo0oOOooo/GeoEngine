#pragma once

#include "Core/ComponentRegistry.h"
#include "Core/Components/Renderable.h"
#include "Core/Components/Transform.h"
#include "Core/Scene.h"
#include "Rendering/Renderer.h"
#include "Rendering/ResourceManager.h"

inline void default_render(Scene* scene, Renderer* renderer) {
    ResourceManager* rm = ResourceManager::GetResourceManager();

    for (uint32_t entity : scene->m_Registry.m_Entities) {
        transform* transform_c = scene->m_Registry.GetComponent<transform>(entity);
        renderable* render_c = scene->m_Registry.GetComponent<renderable>(entity);
        // transform* transform_c = scene->GetComponent<transform>(entity, "transform");
        // renderable* render_c = scene->GetComponent<renderable>(entity, "renderable");

        if (transform_c && render_c) {
            mesh* mesh_r = rm->GetMesh(render_c->mesh_handle);
            material* mat = rm->GetMaterial(render_c->material_handle);
            render_command cmd = mesh_create_render_command(mesh_r);

            glm::mat4 vp = get_vp_matrix(scene->m_ActiveCamera);
            glm::mat4 m = transform_get_matrix(transform_c);

            material_bind(mat, vp, m);
            renderer->RenderMesh(cmd);
        }
    }
}
