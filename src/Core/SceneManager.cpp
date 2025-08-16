#include "SceneManager.h"

#include "Components/Renderable.h"
#include "Components/Transform.h"
#include "../Rendering/ResourceHandle.h"
#include "../Rendering/ResourceManager.h"
#include "../Rendering/Vertex.h"

SceneManager::SceneManager() {
    ResourceManager::Init();
    ResourceManager* rm = ResourceManager::GetResourceManager();

    resource_handle shader_handle = rm->LoadShader("default_shader");
    resource_handle texture_handle = rm->CreateTexture(64 * 6, 64 * 4);
    resource_handle material_handle = rm->CreateMaterial(shader_handle, texture_handle);

    float v = 100;
    Vertex v1{glm::vec3{0, 0, 0}, glm::vec4{0, 0, 1, 1}, glm::vec2{0, 0}};
    Vertex v2{glm::vec3{0, v, 0}, glm::vec4{0, 1, 0, 1}, glm::vec2{0, 1}};
    Vertex v3{glm::vec3{v, 0, 0}, glm::vec4{1, 0, 0, 1}, glm::vec2{1, 0}};
    Vertex v4{glm::vec3{v, v, 0}, glm::vec4{1, 1, 0, 1}, glm::vec2{1, 1}};
    resource_handle mesh_handle = rm->CreateMesh(
        {v1, v2, v3, v4},
        {0, 1, 2, 2, 1, 3}
    );

    m_ActiveScene = new Scene;
    uint32_t ent = m_ActiveScene->CreateEntity();
    m_ActiveScene->AddTransform(ent, transform{});
    m_ActiveScene->AddRenderable(ent, renderable{mesh_handle, material_handle});
}

SceneManager::~SceneManager() {
    ResourceManager::Shutdown();
}

void SceneManager::Start() {
    m_ActiveScene->Start();
}

void SceneManager::Update() {
    m_ActiveScene->Update();
}

void SceneManager::Render(Renderer* renderer) {
    m_ActiveScene->Render(renderer);
}

void SceneManager::Load(std::string path) {}
void SceneManager::Switch(size_t index) {}
