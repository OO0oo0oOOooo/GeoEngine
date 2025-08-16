#include "Window.h"

#include "Events/Broadcast.h"
#include "Events/EventDefs.h"
#include "Events/EventManager.h"

Window::Window() {
    Init();
}

Window::~Window() {
    Shutdown();
}

void Window::Init() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        assert(false);
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

    GLFWmonitor* monitor = nullptr;  // glfwGetPrimaryMonitor();
    m_NativeWindow = glfwCreateWindow(m_WindowWidth, m_WindowHeight, m_Title, monitor, NULL);
    if (!m_NativeWindow) {
        glfwTerminate();
    }

    // Context
    glfwMakeContextCurrent(m_NativeWindow);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;  // Fix error message
        assert(false);
        exit(EXIT_FAILURE);
    }

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    // Callbacks
    glfwSetWindowUserPointer(m_NativeWindow, this);
    // glfwSwapInterval(0); // VSync

    glfwSetWindowSizeCallback(m_NativeWindow, [](GLFWwindow* window, int width, int height) {
        Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
        win->SetHeight(height);
        win->SetWidth(width);
        glViewport(0, 0, width, height);
        // EventManager::GetInstance().WindowResizeEvent(width, height);

        edata8_u resize_data;
        resize_data.f[0] = (float)width;
        resize_data.f[1] = (float)height;
        SystemEvents::broadcast(EVENT_WINDOW_RESIZE, &resize_data);

    });

    glfwSetWindowCloseCallback(
        m_NativeWindow, [](GLFWwindow* window) { EventManager::GetInstance().WindowCloseEvent(); });

    glfwSetKeyCallback(m_NativeWindow,
                       [](GLFWwindow* window, int key, int scancode, int action, int mods) {
                           Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));

                           EventManager::GetInstance().KeyEvent(key, scancode, action, mods);

                           switch (action) {
                               case GLFW_PRESS:
                                   EventManager::GetInstance().KeyDownEvent(key);
                                   break;
                               case GLFW_RELEASE:
                                   EventManager::GetInstance().KeyUpEvent(key);
                                   break;
                               case GLFW_REPEAT:
                                   EventManager::GetInstance().KeyRepeatEvent(key);
                                   break;
                           }

                           if (key == GLFW_KEY_ESCAPE) {
                               win->Close();
                           }
                       });

    glfwSetMouseButtonCallback(
        m_NativeWindow, [](GLFWwindow* window, int button, int action, int mods) {
            EventManager::GetInstance().MouseButtonEvent(button, action, mods);

            switch (action) {
                case GLFW_PRESS:
                    EventManager::GetInstance().MouseButtonDownEvent(button);
                    break;
                case GLFW_RELEASE:
                    EventManager::GetInstance().MouseButtonUpEvent(button);
                    break;
                case GLFW_REPEAT:
                    EventManager::GetInstance().MouseButtonRepeatEvent(button);
                    break;
            }
        });

    glfwSetCursorPosCallback(m_NativeWindow, [](GLFWwindow* window, double xpos, double ypos) {
        Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));

        EventManager::GetInstance().MouseMoveEvent(xpos, win->GetHeight() - ypos);
    });

    glfwSetScrollCallback(m_NativeWindow, [](GLFWwindow* window, double xoffset, double yoffset) {
        EventManager::GetInstance().MouseScrollEvent(xoffset, yoffset);
    });

    /*glfwSetFramebufferSizeCallback(m_NativeWindow, [](GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);

        Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));

        win->m_WindowWidth = width;
        win->m_WindowHeight = height;
    });*/
}

void Window::Shutdown() {
    glfwDestroyWindow(m_NativeWindow);
}

void Window::OnUpdate() {
    glfwPollEvents();
    glfwSwapBuffers(m_NativeWindow);
}

void Window::Close() {
    if (m_NativeWindow != nullptr) glfwSetWindowShouldClose(m_NativeWindow, GLFW_TRUE);
}
