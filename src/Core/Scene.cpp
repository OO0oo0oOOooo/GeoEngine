#include "Scene.h"
#include "Core/ComponentRegistry.h"
#include "Core/Systems/EngineRenderSystems.h"

void Scene::Start() {
    for (size_t i = 0; i < m_SystemRegistry.m_StartSystems.size(); i++) {
        m_SystemRegistry.m_StartSystems[i](m_ComponentRegistry);
    }
}

void Scene::Update() {
    for (size_t i = 0; i < m_SystemRegistry.m_UpdateSystems.size(); i++) {
        m_SystemRegistry.m_UpdateSystems[i](m_ComponentRegistry);
    }
}

void Scene::Render(Renderer* renderer) {
    for (size_t i = 0; i < m_SystemRegistry.m_RenderSystems.size(); i++) {
        m_SystemRegistry.m_RenderSystems[i](m_ComponentRegistry, renderer, m_ActiveCamera);
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
            entity = m_ComponentRegistry.CreateEntity();
        } else {
            m_ComponentRegistry.LoadComponent(entity, line);
        }
    }

    file.close();
}

void Scene::Save() {
    std::string filePath = "Assets/Scene/scene0.txt";
    std::ofstream file(filePath);
    if (!file.is_open()) std::cerr << "Error opening Scene file: " << filePath << std::endl;
    for (const auto& entity : m_ComponentRegistry.m_Entities) {
        entity_save(file);
        m_ComponentRegistry.SaveComponents(entity, file);
    }

    file.close();
}
