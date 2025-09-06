#include "Application.h"

#include "Core/Systems/EngineRenderSystems.h"
#include "Time.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

Application::Application()
    : m_Window(), m_Renderer(m_Window.GetNativeWindow()), m_SceneManager() {}

Application::~Application() {
    glfwTerminate();
}

void Application::Run() {
    m_SceneManager.Start();

    AddRenderSystem(default_render);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_Window.GetNativeWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 430");

    while (!glfwWindowShouldClose(m_Window.GetNativeWindow())) {
        Time::Update();

        for (size_t i = 0; i < m_UpdateSystems.size(); i++) {
            m_UpdateSystems[i](m_SceneManager.GetActiveScene());
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        for (size_t i = 0; i < m_UpdateSystems.size(); i++) {
            m_RenderSystems[i](m_SceneManager.GetActiveScene(), &m_Renderer);
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // if(true)
        //     ImGui::ShowDemoWindow(&show_demo_window);

        {
            ImGui::Begin("FPS");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        m_Window.OnUpdate();
    }
}

Scene* Application::GetScene() {
    return m_SceneManager.GetActiveScene();
}
