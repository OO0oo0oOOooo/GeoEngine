#pragma once

#include <functional>
#include "Core/ComponentRegistry.h"
#include "Rendering/Renderer.h"
#include "Window.h"
#include "Core/SceneManager.h"

class Application {
   public:
    Application();
    ~Application();

    void Run();
    Scene* GetScene();

    void AddUpdateSystem(std::function<void(ComponentRegistry& reg, double deltaTime)> system) {
        m_UpdateSystems.push_back(system);
    }

    void AddRenderSystem(std::function<void(ComponentRegistry& reg, Renderer& renderer)> system) {
        m_RenderSystems.push_back(system);
    }

   private:
    Window m_Window;
    Renderer m_Renderer;
    SceneManager m_SceneManager;

    std::vector<std::function<void(ComponentRegistry&, double)>> m_UpdateSystems;
    std::vector<std::function<void(ComponentRegistry&, Renderer&)>> m_RenderSystems;
};
