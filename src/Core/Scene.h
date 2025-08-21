#pragma once

#include <cstdint>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "../Rendering/Renderer.h"
#include "../Util/SparseSet.h"
#include "Components/Entity.h"
#include "Components/Camera.h"
#include "Components/Renderable.h"
#include "Components/Transform.h"

struct ComponentTypeInfo {
    void (*save_func)(void* data, std::ofstream&);
    void* (*load_func)(std::string);
};

// TODO: this is horrible for memory layout
class ComponentRegistry {
   public:
    const uint32_t INVALID_TYPE = 0xFFFFFFFF;

   public:
    void RegisterComponent(std::string name, void (*save)(void* data, std::ofstream&), void* (*load)(std::string)) {
        m_Components.resize(m_NextId + 1);
        m_StrToId[name] = m_NextId;
        m_Callbacks[m_NextId] = ComponentTypeInfo {
            .save_func = save,
            .load_func = load
        };

        m_NextId++;
    }

    uint32_t StrToId(std::string type) {
        if (!m_StrToId.contains(type)) {
            return INVALID_TYPE;
        }

        return m_StrToId[type];
    }

    uint32_t m_NextId = 0;
    std::vector<SparseSet<void*>> m_Components;
    std::unordered_map<uint32_t, ComponentTypeInfo> m_Callbacks;
    std::unordered_map<std::string, uint32_t> m_StrToId;
};

class Scene {
   public:
    ComponentRegistry m_Registry;

   public:
    Scene() = default;
    ~Scene() = default;

    void Start();
    void Update();
    void Render(Renderer* renderer);

    void Save();
    void Load();

    uint32_t CreateEntity();
    void DeleteEntity(uint32_t entity); // TODO:


    // TODO: could use template with typeid(T).name
    void* GetComponent(uint32_t entity, std::string typeName);
    void AddComponent(uint32_t entity, void* component, std::string typeName);

    // template<typename T>
    // T& GetComponent(uint32_t entity) {
    //     return GetComponentStorage<T>().Get(entity);
    // }

    // template<typename T>
    // void AddComponent(uint32_t entity, const T& component) {
    //     return GetComponentStorage<T>().Insert(entity, component);
    // }

    // template<typename T>
    // SparseSet<T>& GetComponentStorage() {
    //     static SparseSet<T> storage;
    //     return storage;
    // }

   private:
    camera m_ActiveCamera;

    uint32_t m_NextEntityID = 1;
    std::vector<uint32_t> m_Entities;
};
