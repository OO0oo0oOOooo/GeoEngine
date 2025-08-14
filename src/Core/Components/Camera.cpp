#include "Camera.h"

#include "src/Events/EventManager.h"

Camera::Camera() {
    m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);

    m_ProjectionMatrix = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, m_NearPlane, m_FarPlane);
    m_ViewMatrix = glm::inverse(glm::translate(glm::mat4(1.0f), m_Position));

    EventManager::GetInstance().WindowResizeEvent +=
        std::bind(&Camera::SetWindowSize, this, std::placeholders::_1, std::placeholders::_2);
}

glm::mat4 Camera::GetViewProjectionMatrix() {
    return m_ProjectionMatrix * m_ViewMatrix;
}
