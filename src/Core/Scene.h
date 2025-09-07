#pragma once

#include <cstddef>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "../Rendering/Renderer.h"
#include "ComponentRegistry.h"
#include "Components/Entity.h"
#include "Components/Camera.h"
#include "Components/Renderable.h"
#include "Components/Transform.h"

class Scene {
   public:
    camera* m_ActiveCamera;
    ComponentRegistry m_Registry;

   public:
    void Start();
    void Update();

    void Save();
    void Load();

    // template <typename T>
    // T* GetComponent(uint32_t entity, std::string typeName) {
    //     return static_cast<T*>(m_Registry.GetComponent(entity, typeName));
    // }
    //
    // template <typename T>
    // void AddComponent(uint32_t entity, T component, std::string typeName) {
    //     m_Registry.AddComponent(entity, &component, typeName);
    // }

   private:
    static constexpr uint32_t INVALID_ENTITY = 0xFFFFFFFF;
};
