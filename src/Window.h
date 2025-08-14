#pragma once

class Window {
   public:
    Window();
    ~Window();

    void OnUpdate();
    void Close();

    inline int GetWidth() {
        return m_WindowWidth;
    }
    inline int GetHeight() {
        return m_WindowHeight;
    }
    inline void SetWidth(int w) {
        m_WindowWidth = w;
    }
    inline void SetHeight(int h) {
        m_WindowHeight = h;
    }

    inline const char* GetTitle() {
        return m_Title;
    }
    inline GLFWwindow* GetNativeWindow() {
        return m_NativeWindow;
    }

   private:
    void Init();
    void Shutdown();

    int m_WindowWidth = 1920;
    int m_WindowHeight = 1080;
    const char* m_Title = "Sand Simulation";
    GLFWwindow* m_NativeWindow;
};
