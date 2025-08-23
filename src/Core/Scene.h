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
    ComponentRegistry m_Registry;

   public:
    void Start();
    void Update();
    void Render(Renderer* renderer);

    void Save();
    void Load();

    uint32_t CreateEntity();
    void DeleteEntity(uint32_t entity);

    // TODO: could use template with typeid(T).name
    void* GetComponent(uint32_t entity, std::string typeName);
    void AddComponent(uint32_t entity, void* component, std::string typeName);

    // TODO: could use template with typeid(T).name
    template <typename T>
    T* GetComponent(uint32_t entity, std::string typeName) {
        uint32_t typeID = m_Registry.StrToId(typeName);
        if (typeID == m_Registry.INVALID_TYPE) {
            return nullptr;
        }

        if (typeID >= m_Registry.m_Components.size()) { return nullptr; }
        return static_cast<T*>(sparse_set_get(&m_Registry.m_Components[typeID], entity));
    }

    template <typename T>
    void AddComponent(uint32_t entity, const T& component, std::string typeName) {
        uint32_t typeID = m_Registry.StrToId(typeName);
        if (typeID == m_Registry.INVALID_TYPE) {
            return;
        }

        if (typeID >= m_Registry.m_Components.size()) { return; }
        sparse_set_insert(&m_Registry.m_Components[typeID], entity, &component);
    }

   private:
    camera m_ActiveCamera;

    static constexpr uint32_t INVALID_ENTITY = 0xFFFFFFFF;
    uint32_t m_NextEntityID = 0;
    std::vector<uint32_t> m_Entities;
};
