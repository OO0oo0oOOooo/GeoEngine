#include "Scene.h"

// #include "glm/fwd.hpp"
// #include "src/Core/Components/Transform.h"
#include "../Rendering/Material.h"
#include "../Rendering/Mesh.h"
#include "../Rendering/RenderCommand.h"
#include "../Rendering/ResourceManager.h"

void Scene::Start() {}
void Scene::Update() {}

void Scene::Render(Renderer* renderer) {
    ResourceManager* rm = ResourceManager::GetResourceManager();

    uint32_t entity = m_Entities[0];
    transform* transform = GetTransform(entity);
    renderable* render_comp = GetRenderable(entity);

    assert(transform);
    assert(render_comp);

    if (transform && render_comp) {
        mesh* mesh = rm->GetMesh(render_comp->mesh_handle);
        material* material = rm->GetMaterial(render_comp->material_handle);

        assert(mesh);
        assert(material);

        render_command cmd = mesh_create_render_command(mesh);

        glm::mat4 vp = m_ActiveCamera.GetViewProjectionMatrix();
        glm::mat4 m = transform_get_matrix(transform);
        material_bind(material, vp, m);
        renderer->RenderMesh(cmd);
    }

    // for (uint32_t entity : m_Entities) {
    // }
}

uint32_t Scene::CreateEntity() {
    uint32_t entity = m_NextEntityID++;
    m_Entities.push_back(entity);
    return entity;
}

void Scene::DeleteEntity(uint32_t entity) {
    m_Transforms.Remove(entity);
    m_Renderables.Remove(entity);
    m_Entities.erase(std::remove(m_Entities.begin(), m_Entities.end(), entity), m_Entities.end());
}

void Scene::AddTransform(uint32_t ent, const transform component) {
    if (!m_Transforms.Contains(ent)) {
        m_Transforms.Insert(ent, component);
    }
}

void Scene::RemoveTransform(uint32_t ent) {
    if (m_Transforms.Contains(ent)) {
        m_Transforms.Remove(ent);
    }
}

transform* Scene::GetTransform(uint32_t ent) {
    if (m_Transforms.Contains(ent)) {
        return &m_Transforms.Get(ent);
    }

    return nullptr;
}

void Scene::AddRenderable(uint32_t ent, const renderable& component) {
    if (!m_Renderables.Contains(ent)) {
        m_Renderables.Insert(ent, component);
    }
}

void Scene::RemoveRenderable(uint32_t ent) {
    if (m_Renderables.Contains(ent)) {
        m_Renderables.Remove(ent);
    }
}

renderable* Scene::GetRenderable(uint32_t ent) {
    if (m_Renderables.Contains(ent)) {
        return &m_Renderables.Get(ent);
    }

    return nullptr;
}
