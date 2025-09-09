#pragma once

#include <fstream>
#include <sstream>

#include "Rendering/Renderer.h"
#include "SystemRegistry.h"
#include "ComponentRegistry.h"
#include "Components/Entity.h"
#include "Components/Camera.h"

class Scene {
   public:
    camera* m_ActiveCamera;
    ComponentRegistry m_ComponentRegistry;
    SystemRegistry m_SystemRegistry;

   public:
    void Start();
    void Update();
    void Render(Renderer* renderer);

    void Save();
    void Load();

   private:
    static constexpr uint32_t INVALID_ENTITY = 0xFFFFFFFF;
};
