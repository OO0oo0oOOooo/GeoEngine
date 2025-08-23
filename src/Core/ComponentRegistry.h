#pragma once

#include "Util/CSparseSet.h"

struct ComponentTypeInfo {
    std::string name;
    size_t size;
    void (*save_func)(const void* data, std::ofstream&);
    void* (*load_func)(std::string);
};

class ComponentRegistry {
   public:
    static constexpr uint32_t INVALID_TYPE = 0xFFFFFFFF;

   public:
    void RegisterComponent(std::string name, size_t componentSize, void (*save)(const void* data, std::ofstream&), void* (*load)(std::string)) {
        sparse_set ss;
        sparse_set_init(&ss, 1024, componentSize);
        m_Components.push_back(ss);

        m_StrToId[name] = m_NextId;

        m_Callbacks[m_NextId] = ComponentTypeInfo {
            .name = name,
            .size = componentSize,
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
    std::vector<sparse_set> m_Components;
    std::unordered_map<uint32_t, ComponentTypeInfo> m_Callbacks;
    std::unordered_map<std::string, uint32_t> m_StrToId;
};

// #include <functional>
// #include "Util/SparseSet.h"
//
// template <typename T>
// class ComponentRegistry {
//     static inline SparseSet<T> storage;
//     static inline std::function<void(const T*, std::ofstream&)> save_callback;
//     static inline std::function<T(std::string)> load_callback;
//
//    public:
//     static void RegisterCallbacks(std::function<void(const T*, std::ofstream&)> save_func, std::function<T(std::string)> load_func) {
//         save_callback = save_func;
//         load_callback = load_func;
//     }
//
//     static T& Get(uint32_t entity) {
//         return storage.Get(entity);
//     }
//
//     static bool Contains(uint32_t entity) {
//         storage.Contains(entity);
//     }
//
//     static void Add(uint32_t entity, T& component) {
//         storage.Insert(entity, &component);
//     }
//
//     static void Remove(uint32_t entity) {
//         storage.Remove(entity);
//     }
//
//     static void Save(uint32_t entity, std::ofstream& file) {
//         T* component = Get(entity);
//         if (component) {
//             ComponentSave(component, file);
//         }
//     }
//
//     static void Load() {}
// };
//
//
