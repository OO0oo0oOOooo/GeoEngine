#pragma once

#include "Core/ComponentRegistry.h"
#include "Core/Components/Camera.h"
#include "Rendering/Renderer.h"

class SystemRegistry {
   public:
    std::vector<std::function<void(ComponentRegistry& registry)>> m_StartSystems;
    std::vector<std::function<void(ComponentRegistry& registry)>> m_UpdateSystems;
    std::vector<std::function<void(ComponentRegistry& registry, Renderer*, camera*)>> m_RenderSystems;

   public:
    void AddStartSystem(void (*start_system)(ComponentRegistry& registry)) {
        m_StartSystems.push_back(start_system);
    }

    void AddUpdateSystem(void (*update_system)(ComponentRegistry& registry)) {
        m_UpdateSystems.push_back(update_system);
    }

    void AddRenderSystem(void (*render_system)(ComponentRegistry& registry, Renderer* renderer, camera* camera_c)) {
        m_RenderSystems.push_back(render_system);
    }
};
