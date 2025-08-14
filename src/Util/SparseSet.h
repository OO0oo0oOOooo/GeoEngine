#pragma once

template <typename T>
class SparseSet {
   public:
    SparseSet() {
        m_Dense.reserve(128);
        m_Entities.reserve(128);
        m_Sparse.resize(128, INVALID);
    }

    T& Get(uint32_t id) {
        EnsureCapacity(id);
        assert(Contains(id));
        uint32_t dense_index = m_Sparse[id];
        return m_Dense[dense_index];
    }

    bool Contains(uint32_t id) {
        if (id >= m_Sparse.size()) return false;

        uint32_t index = m_Sparse[id];
        return index != INVALID &&
               index < m_Dense.size() &&
               m_Entities[index] == id;
    }

    void Insert(uint32_t id, const T& component) {
        EnsureCapacity(id);
        uint32_t dense_index = m_Dense.size();
        m_Dense.push_back(component);
        m_Entities.push_back(id);
        m_Sparse[id] = dense_index;
    }

    void Remove(uint32_t id) {
        if (!Contains(id)) return;
        uint32_t dense_index = m_Sparse[id];
        uint32_t last_index = m_Dense.size() - 1;

        if (dense_index != last_index) {
            m_Dense[dense_index] = m_Dense[last_index];
            m_Entities[dense_index] = m_Entities[last_index];
            m_Sparse[m_Entities[dense_index]] = dense_index;
        }

        m_Dense.pop_back();
        m_Entities.pop_back();
        m_Sparse[id] = INVALID;
    }

   private:
    static constexpr uint32_t INVALID = 0xFFFFFFFF;
    std::vector<T> m_Dense;
    std::vector<uint32_t> m_Sparse;
    std::vector<uint32_t> m_Entities;

    void EnsureCapacity(uint32_t id) {
        if (id >= m_Sparse.size()) {
            m_Sparse.resize(id + 1, INVALID);
        }
    }
};
