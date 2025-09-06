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

    // void AddUpdateSystem(void(*update_system)(ComponentRegistry& reg, double deltaTime)) {
    //     m_UpdateSystems.push_back(update_system);
    // }
    void AddUpdateSystem(void(*update_system)(Scene* scene)) {
        m_UpdateSystems.push_back(update_system);
    }

    void AddRenderSystem(void(*render_system)(Scene* scene, Renderer* renderer)) {
        m_RenderSystems.push_back(render_system);
    }

   private:
    Window m_Window;
    Renderer m_Renderer;
    SceneManager m_SceneManager;

    // std::vector<std::function<void(ComponentRegistry&, double)>> m_UpdateSystems;
    // std::vector<std::function<void(ComponentRegistry&, Renderer&)>> m_RenderSystems;
    std::vector<std::function<void(Scene*)>> m_UpdateSystems;
    std::vector<std::function<void(Scene*, Renderer*)>> m_RenderSystems;
};
