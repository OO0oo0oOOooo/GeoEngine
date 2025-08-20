#include "Scene.h"

#include "../Rendering/Material.h"
#include "../Rendering/Mesh.h"
#include "../Rendering/RenderCommand.h"
#include "../Rendering/ResourceManager.h"

#include "Events/Broadcast.h"
#include "Events/EventDefs.h"

void Scene::Start() {
    camera_init();
    SystemEvents::listen(EVENT_WINDOW_RESIZE, set_window_size, &m_ActiveCamera);
}

void Scene::Update() {}

void Scene::Render(Renderer* renderer) {
    ResourceManager* rm = ResourceManager::GetResourceManager();

    uint32_t entity = m_Entities[0];
    transform* transform = GetTransform(entity);
    renderable* render_comp = GetRenderable(entity);

    // assert(transform);
    // assert(render_comp);

    for (uint32_t entity : m_Entities) {
        if (transform && render_comp) {
            mesh* mesh = rm->GetMesh(render_comp->mesh_handle);
            material* material = rm->GetMaterial(render_comp->material_handle);

            // assert(mesh);
            // assert(material);

            render_command cmd = mesh_create_render_command(mesh);

            glm::mat4 vp = get_vp_matrix(&m_ActiveCamera);
            glm::mat4 m = transform_get_matrix(transform);
            material_bind(material, vp, m);
            renderer->RenderMesh(cmd);
        }
    }
}

void Scene::Load() {
    std::string filePath = "Assets/Scene/scene0.txt";
    std::ifstream file(filePath);
    if (!file.is_open()) std::cerr << "Error opening Scene file: " << filePath << std::endl;

    std::string line;
    while (std::getline(file, line)) {
        uint32_t entity = 69420;
        if (line[0] == 'E') { entity = entity_parse_id(line); }
        else if (line[0] == 'T') { transform t = transform_load(line); m_Transforms.Insert(entity, t); }
        else if (line[0] == 'R') { renderable r = renderable_load(line); m_Renderables.Insert(entity, r); }


    }

    file.close();
}

void Scene::Save() {
    std::string filePath = "Assets/Scene/scene0.txt";
    std::ofstream file(filePath);
    if (!file.is_open()) std::cerr << "Error opening Scene file: " << filePath << std::endl;
    for (auto& e : m_Entities) {
        entity_save(e, file);
        transform_save(&m_Transforms.Get(e), file);
        renderable_save(&m_Renderables.Get(e), file);
    }

    file.close();
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

void Scene::AddTransform(uint32_t ent, const transform& component) {
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
