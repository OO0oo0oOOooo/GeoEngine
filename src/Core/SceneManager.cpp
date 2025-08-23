#include "SceneManager.h"

#include "Components/Renderable.h"
#include "Components/Transform.h"
#include "../Rendering/ResourceHandle.h"
#include "../Rendering/ResourceManager.h"
#include "../Rendering/Vertex.h"

SceneManager::SceneManager() {
    ResourceManager::Init();
    m_ActiveScene = new Scene;
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
