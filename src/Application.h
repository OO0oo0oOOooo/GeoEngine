#pragma once

#include "Rendering/Renderer.h"
#include "Window.h"
#include "Core/SceneManager.h"

class Application {
   public:
    Application();
    ~Application();

    void Run();

   private:
    Window m_Window;
    Renderer m_Renderer;
    SceneManager m_SceneManager;
};
