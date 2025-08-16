#include "Window.h"

#include "Events/Broadcast.h"
#include "Events/EventDefs.h"

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

        edata8_u resize_data;
        resize_data.f[0] = (float)width;
        resize_data.f[1] = (float)height;
        SystemEvents::broadcast(EVENT_WINDOW_RESIZE, &resize_data);
    });

    glfwSetWindowCloseCallback(m_NativeWindow, [](GLFWwindow* window) {
        SystemEvents::broadcast(EVENT_WINDOW_CLOSE, nullptr);
    });

    glfwSetKeyCallback(m_NativeWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));

        edata16_u keyData;
        keyData.i[0] = key;
        keyData.i[1] = scancode;
        keyData.i[2] = action;
        keyData.i[3] = mods;
        SystemEvents::broadcast(EVENT_KEY_BUTTON, &keyData);

        edata4_u keyId;
        keyId.i[0] = key;
        switch (action) {
            case GLFW_PRESS:
                SystemEvents::broadcast(EVENT_KEY_BUTTON_DOWN, &keyId);
                break;
            case GLFW_RELEASE:
                SystemEvents::broadcast(EVENT_KEY_BUTTON_UP, &keyId);
                break;
            case GLFW_REPEAT:
                SystemEvents::broadcast(EVENT_KEY_BUTTON_REPEAT, &keyId);
                break;
        }
    });

    glfwSetMouseButtonCallback(m_NativeWindow, [](GLFWwindow* window, int key, int action, int mods) {
        edata16_u keyData;
        keyData.i[0] = key;
        keyData.i[1] = action;
        keyData.i[2] = mods;
        SystemEvents::broadcast(EVENT_MOUSE_BUTTON, &keyData);

        edata4_u keyId;
        keyId.i[0] = key;
        switch (action) {
            case GLFW_PRESS:
                SystemEvents::broadcast(EVENT_MOUSE_BUTTON_DOWN, &keyId);
                break;
            case GLFW_RELEASE:
                SystemEvents::broadcast(EVENT_MOUSE_BUTTON_UP, &keyId);
                break;
            case GLFW_REPEAT:
                SystemEvents::broadcast(EVENT_MOUSE_BUTTON_REPEAT, &keyId);
                break;
        }
    });

    glfwSetCursorPosCallback(m_NativeWindow, [](GLFWwindow* window, double xpos, double ypos) {
        Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
        edata16_u data;
        data.d[0] = xpos;
        data.d[1] = win->GetHeight() - ypos;
        SystemEvents::broadcast(EVENT_MOUSE_MOVE, &data);
    });

    glfwSetScrollCallback(m_NativeWindow, [](GLFWwindow* window, double xoffset, double yoffset) {
        edata16_u data;
        data.d[0] = xoffset;
        data.d[1] = yoffset;
        SystemEvents::broadcast(EVENT_MOUSE_SCROLL, &data);
    });
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
