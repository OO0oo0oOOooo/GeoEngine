#pragma once

#include <fstream>
#include <sstream>
#include <unordered_map>

#include "../Rendering/Renderer.h"
#include "../Util/SparseSet.h"
#include "Components/Entity.h"
#include "Components/Camera.h"
#include "Components/Renderable.h"
#include "Components/Transform.h"

class ComponentRegistry {
   public:
    void RegisterComponent(std::string name, void (*save)(void* data, std::ofstream&), void* (*load)(std::string)) {
        save_callbacks[name] = save;
        load_callbacks[name] = load;
    }

    template<typename T>
    void GetSave() {
    }

    std::unordered_map<std::string, void (*)(void*, std::ofstream&)> save_callbacks;
    std::unordered_map<std::string, void* (*)(std::string)> load_callbacks;
};


// TODO: Saving and loading generic components
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
    void DeleteEntity(uint32_t entity);

    void AddTransform(uint32_t ent, const transform& component);
    void RemoveTransform(uint32_t ent);
    transform* GetTransform(uint32_t ent);

    void AddRenderable(uint32_t ent, const renderable& component);
    void RemoveRenderable(uint32_t ent);
    renderable* GetRenderable(uint32_t ent);

    template<typename T>
    T& GetComponent(uint32_t entity) {
        return GetComponentStorage<T>().Get(entity);
    }

    template<typename T>
    void AddComponent(uint32_t entity, const T& component) {
        return GetComponentStorage<T>().Insert(entity, component);
    }

    template<typename T>
    SparseSet<T>& GetComponentStorage() {
        static SparseSet<T> storage;
        return storage;
    }

   private:
    camera m_ActiveCamera;

    uint32_t m_NextEntityID = 1;
    std::vector<uint32_t> m_Entities;

    SparseSet<transform> m_Transforms;
    SparseSet<renderable> m_Renderables;
};
