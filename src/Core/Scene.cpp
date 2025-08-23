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
            mesh* mesh = rm->GetMesh(renderComp->mesh_handle);
            material* material = rm->GetMaterial(renderComp->material_handle);
            render_command cmd = mesh_create_render_command(mesh);

            glm::mat4 vp = get_vp_matrix(&m_ActiveCamera);
            glm::mat4 m = transform_get_matrix(transformComp);
            material_bind(material, vp, m);
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
            uint32_t typeID = m_Registry.StrToId(type);
            if (typeID == m_Registry.INVALID_TYPE) {
                continue;
            }

            if (typeID < m_Registry.m_Callbacks.size() && typeID < m_Registry.m_Components.size()) {
                auto component = m_Registry.m_Callbacks[typeID].load_func(line);
                sparse_set_insert(&m_Registry.m_Components[typeID], entity, component);
            }
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

        for (int i = 0; i < m_Registry.m_Components.size(); i++) {
            m_Registry.m_Callbacks[i].save_func(sparse_set_get(&m_Registry.m_Components[i], entity), file);
        }
    }

    file.close();
}

uint32_t Scene::CreateEntity() {
    uint32_t entity = m_NextEntityID++;
    m_Entities.push_back(entity);
    return entity;
}

void Scene::DeleteEntity(uint32_t entity) {
    for (sparse_set& ss : m_Registry.m_Components) {
        void* component = sparse_set_get(&ss, entity);
        if (component) {
            sparse_set_remove(&ss, entity);
        }
    }

    m_Entities.erase(std::remove(m_Entities.begin(), m_Entities.end(), entity), m_Entities.end());
}

void* Scene::GetComponent(uint32_t entity, std::string typeName) {
    uint32_t typeID = m_Registry.StrToId(typeName);
    if (typeID == m_Registry.INVALID_TYPE) {
        return nullptr;
    }

    if (typeID >= m_Registry.m_Components.size()) { return nullptr; }
    return sparse_set_get(&m_Registry.m_Components[typeID], entity);
}

void Scene::AddComponent(uint32_t entity, void* component, std::string typeName) {
    uint32_t typeID = m_Registry.StrToId(typeName);
    if (typeID == m_Registry.INVALID_TYPE) {
        return;
    }

    if (typeID >= m_Registry.m_Components.size()) { return; }
    sparse_set_insert(&m_Registry.m_Components[typeID], entity, component);
}
