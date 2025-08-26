#pragma once

#include "RenderCommand.h"

class Renderer {
   public:
    Renderer(GLFWwindow* window);
    ~Renderer();

    void SetViewport(int width, int height);

    void RenderMesh(const render_command& cmd);
    static vertex_layout CreateStandardLayout();

   private:
    GLFWwindow* m_Window;
    uint32_t m_DummyVAO;
};
