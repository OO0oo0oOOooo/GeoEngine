#include "Scene.h"

#include "../Rendering/Material.h"
#include "../Rendering/Mesh.h"
#include "../Rendering/RenderCommand.h"
#include "../Rendering/ResourceManager.h"

#include "Events/Broadcast.h"
#include "Events/EventDefs.h"
#include "Util/CSparseSet.h"

void Scene::Start() {
    camera_init();
    SystemEvents::listen(EVENT_WINDOW_RESIZE, set_window_size, &m_ActiveCamera);
}

void Scene::Update() {}

void Scene::Render(Renderer* renderer) {
    ResourceManager* rm = ResourceManager::GetResourceManager();

    for (uint32_t entity : m_Entities) {
        transform* transformComp = GetComponent<transform>(entity, "transform");
        renderable* renderComp = GetComponent<renderable>(entity, "renderable");

        if (transformComp && renderComp) {
            mesh* mesh_r = rm->GetMesh(renderComp->mesh_handle);
            material* mat = rm->GetMaterial(renderComp->material_handle);
            render_command cmd = mesh_create_render_command(mesh_r);

            glm::mat4 vp = get_vp_matrix(&m_ActiveCamera);
            glm::mat4 m = transform_get_matrix(transformComp);

            material_bind(mat, vp, m);
            renderer->RenderMesh(cmd);
        }
    }
}

void Scene::Load() {
    std::string filePath = "Assets/Scene/scene0.txt";
    std::ifstream file(filePath);
    if (!file.is_open()) std::cerr << "Error opening Scene file: " << filePath << std::endl;

    uint32_t entity = 0;
    std::string line;
    while (std::getline(file, line)) {
    std::stringstream ss(line);
        std::string type;
        ss >> type;

        if (type == "E") {
            entity = CreateEntity();
        } else {
            m_Registry.LoadComponent(entity, line);
        }
    }

    file.close();
}

void Scene::Save() {
    std::string filePath = "Assets/Scene/scene0.txt";
    std::ofstream file(filePath);
    if (!file.is_open()) std::cerr << "Error opening Scene file: " << filePath << std::endl;
    for (const auto& entity : m_Entities) {
        entity_save(file);
        m_Registry.SaveComponents(entity, file);
    }

    file.close();
}

uint32_t Scene::CreateEntity() {
    uint32_t entity = m_NextEntityID++;
    m_Entities.push_back(entity);
    return entity;
}

void Scene::DeleteEntity(uint32_t entity) {
    m_Registry.RemoveAllComponents(entity);
    m_Entities.erase(std::remove(m_Entities.begin(), m_Entities.end(), entity), m_Entities.end());
}

void* Scene::GetComponent(uint32_t entity, std::string typeName) {
    return m_Registry.GetComponent(entity, typeName);
}

void Scene::AddComponent(uint32_t entity, void* component, std::string typeName) {
    m_Registry.AddComponent(entity, component, typeName);
}
