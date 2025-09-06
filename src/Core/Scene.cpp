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
            entity = m_Registry.CreateEntity();
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
    for (const auto& entity : m_Registry.m_Entities) {
        entity_save(file);
        m_Registry.SaveComponents(entity, file);
    }

    file.close();
}

// void* Scene::GetComponent(uint32_t entity, std::string typeName) {
//     return m_Registry.GetComponent(entity, typeName);
// }
//
// void Scene::AddComponent(uint32_t entity, void* component, std::string typeName) {
//     m_Registry.AddComponent(entity, component, typeName);
// }
