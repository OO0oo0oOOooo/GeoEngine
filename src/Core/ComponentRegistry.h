#pragma once

#include <cstddef>
#include <functional>
#include <sstream>

#include "Util/CSparseSet.h"

struct ComponentTypeInfo {
    std::string name;
    size_t size;
};

class ComponentRegistry {
   public:
    static constexpr uint32_t INVALID_TYPE = 0xFFFFFFFF;

   public:
    void RegisterComponent(std::string name, size_t componentSize,
                           void (*save)(const void* data, std::ofstream&),
                           void (*load)(std::string, void*)) {
        sparse_set ss;
        sparse_set_init(&ss, 1024 * 1024, componentSize);

        m_Components.push_back(ss);
        m_Save.push_back(save);
        m_Load.push_back(load);
        m_Info.push_back(ComponentTypeInfo{
            .name = name,
            .size = componentSize,
        });

        m_StrToId[name] = m_NextId;
        m_NextId++;
    }

    void AddComponent(uint32_t entity, const void* component, std::string typeName) {
        uint32_t typeID = StrToId(typeName);
        if (typeID == INVALID_TYPE) { return; }
        if (typeID >= m_Components.size()) { return; }
        sparse_set_insert(&m_Components[typeID], entity, &component);
    }

    void* GetComponent(uint32_t entity, std::string typeName) {
        uint32_t typeID = StrToId(typeName);
        if (typeID == INVALID_TYPE) { return nullptr; }
        if (typeID >= m_Components.size()) { return nullptr; }
        return sparse_set_get(&m_Components[typeID], entity);
    }

    void RemoveComponent(uint32_t entity, std::string typeName) {
        uint32_t typeID = StrToId(typeName);
        if (typeID == INVALID_TYPE) { return; }
        if (typeID >= m_Components.size()) { return; }
        sparse_set_remove(&m_Components[typeID], entity);
    }

    void RemoveAllComponents(uint32_t entity) {
        for (sparse_set& ss : m_Components) {
            if (sparse_set_contains(&ss, entity)) {
                sparse_set_remove(&ss, entity);
            }
        }
    }

    void LoadComponent(uint32_t entity, std::string line) {
        std::stringstream ss(line);
        std::string type;
        ss >> type;

        uint32_t typeID = StrToId(type);
        if (typeID == INVALID_TYPE) return;
        if (typeID >= m_Load.size()) return;
        if (typeID >= m_Info.size()) return;
        if (typeID >= m_Components.size()) return;

        size_t size = m_Info[typeID].size;
        uint8_t buffer[size];
        m_Load[typeID](line, buffer);

        sparse_set_insert(&m_Components[typeID], entity, buffer);
    }

    void SaveComponents(uint32_t entity, std::ofstream& file) {
        for (int i = 0; i < m_Components.size(); i++) {
            void* component = sparse_set_get(&m_Components[i], entity);
            if (i < m_Save.size() && component) {
                m_Save[i](component, file);
            }
        }
    }

    uint32_t StrToId(std::string type) {
        if (!m_StrToId.contains(type)) {
            return INVALID_TYPE;
        }

        return m_StrToId[type];
    }

   private:
    uint32_t m_NextId = 0;
    std::vector<sparse_set> m_Components;
    std::vector<std::function<void(const void*, std::ofstream&)>> m_Save;
    std::vector<std::function<void(std::string, void*)>> m_Load;
    std::vector<ComponentTypeInfo> m_Info;
    std::unordered_map<std::string, uint32_t> m_StrToId;
};
