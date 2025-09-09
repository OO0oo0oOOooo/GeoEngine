#include "ResourceManager.h"

#include <cstring>

static ResourceManager* s_instance = nullptr;

void ResourceManager::Init() {
    assert(s_instance == nullptr && "ResourceManager already initialized.");
    s_instance = new ResourceManager();

    s_instance->arena = arena_linear_init(1024 * 1024);
    s_instance->arena_texture_buffer = arena_linear_init(1024 * 1024);
    s_instance->arena_mesh_buffer = arena_linear_init(1024 * 1024);
};

void ResourceManager::Shutdown() {
    assert(s_instance != nullptr && "ResourceManager not initialized.");
    arena_linear_destroy(&s_instance->arena);
    arena_linear_destroy(&s_instance->arena_mesh_buffer);
    arena_linear_destroy(&s_instance->arena_texture_buffer);

    delete s_instance;
    s_instance = nullptr;
}

ResourceManager* ResourceManager::GetResourceManager() {
    assert(s_instance != nullptr && "ResourceManager not initialized.");
    return s_instance;
}

void* ResourceManager::GetResource(resource_handle handle) {
    uint16_t id = get_handle_id(handle);
    uint16_t ver = get_handle_meta(handle);

    if (slots[id].version == ver) {
        return slots[id].data;
    }

    return nullptr;
}

shader* ResourceManager::GetShader(resource_handle handle) {
    uint16_t id = get_handle_id(handle);
    uint16_t ver = get_handle_meta(handle);

    if (s_instance->slots[id].version == ver) {
        return (shader*)s_instance->slots[id].data;
    }

    return nullptr;
}

texture* ResourceManager::GetTexture(resource_handle handle) {
    uint16_t id = get_handle_id(handle);
    uint16_t ver = get_handle_meta(handle);

    if (s_instance->slots[id].version == ver) {
        return (texture*)s_instance->slots[id].data;
    }

    return nullptr;
}

mesh* ResourceManager::GetMesh(resource_handle handle) {
    uint16_t id = get_handle_id(handle);
    uint16_t ver = get_handle_meta(handle);

    if (s_instance->slots[id].version == ver) {
        return (mesh*)s_instance->slots[id].data;
    }

    return nullptr;
}

material* ResourceManager::GetMaterial(resource_handle handle) {
    uint16_t id = get_handle_id(handle);
    uint16_t ver = get_handle_meta(handle);

    if (s_instance->slots[id].version == ver) {
        return (material*)s_instance->slots[id].data;
    }

    return nullptr;
}

resource_handle ResourceManager::CreateMaterial(resource_handle shaderHandle,
                                               resource_handle textureHandle) {
    uint16_t id = s_instance->next_handle;
    uint32_t handleValue = ((uint32_t)id << 16) | s_instance->slots[id].version;
    s_instance->next_handle++;

    material* mat = (material*)arena_linear_alloc(&s_instance->arena, sizeof(material));
    material_init(mat, shaderHandle, textureHandle);

    s_instance->slots[id].data = mat;
    return resource_handle{handleValue};
}

resource_handle ResourceManager::CreateMesh(std::vector<Vertex> vertices,
                                           std::vector<unsigned int> indices) {
    uint16_t id = s_instance->next_handle;
    uint32_t handleValue = ((uint32_t)id << 16) | s_instance->slots[id].version;
    s_instance->next_handle++;

    mesh* data = (mesh*)arena_linear_alloc(&s_instance->arena, sizeof(mesh));

    size_t vertex_size = sizeof(Vertex) * vertices.size();
    size_t index_size = sizeof(unsigned int) * indices.size();

    uint8_t* vb =
        (uint8_t*)arena_linear_alloc(&s_instance->arena_mesh_buffer, vertex_size);
    uint8_t* ib =
        (uint8_t*)arena_linear_alloc(&s_instance->arena_mesh_buffer, index_size);

    memcpy(vb, vertices.data(), vertex_size);
    memcpy(ib, indices.data(), index_size);

    mesh_create_static(data, vb, vertex_size, ib, index_size, indices.size());
    mesh_upload_to_gpu(data);

    s_instance->slots[id].data = data;
    return resource_handle{handleValue};
}

resource_handle ResourceManager::CreateTexture(int width, int height) {
    uint16_t id = s_instance->next_handle;
    uint32_t handleValue = ((uint32_t)id << 16) | s_instance->slots[id].version;
    s_instance->next_handle++;

    size_t size = (width * height) * (sizeof(uint8_t) * 4);
    texture* data =
        (texture*)arena_linear_alloc(&s_instance->arena, sizeof(texture));
    uint8_t* buffer = (uint8_t*)arena_linear_alloc(&s_instance->arena_texture_buffer, size);

    for (int i = 0; i < size; i += 4) {
        buffer[i] = 0xFF;      // Red
        buffer[i + 1] = 0x00;  // Green
        buffer[i + 2] = 0xFF;  // Blue
        buffer[i + 3] = 0xFF;  // Alpha
    }

    texture_init(data, width, height, buffer);

    s_instance->slots[id].data = data;
    return resource_handle{handleValue};
}

resource_handle ResourceManager::LoadShader(std::string fileName) {
    uint16_t id = s_instance->next_handle;
    uint32_t handleValue = ((uint32_t)id << 16) | s_instance->slots[id].version;
    s_instance->next_handle++;

    shader* data = (shader*)arena_linear_alloc(&s_instance->arena, sizeof(shader));
    shader_init(data, fileName.c_str());

    s_instance->slots[id].data = data;
    return resource_handle{handleValue};
}

// ResourceHandle ResourceManager::LoadMesh(int count, uint8_t* vertexData, uint8_t* indiceData) {
//     uint16_t id = next_handle;
//     uint32_t handleValue = ((uint32_t)id << 16) | slots[id].version;
//     next_handle++;
//
//     size_t size = sizeof(uint8_t) * count;
//     MeshResource* mesh = (MeshResource*)arena_linear_alloc(&arena, sizeof(MeshResource));
//     uint8_t* vb = (uint8_t*)arena_linear_alloc(&arena_mesh_buffer, size);
//     uint8_t* ib = (uint8_t*)arena_linear_alloc(&arena_mesh_buffer, size);
//     memcpy(vb, vertexData, size);
//     memcpy(ib, indiceData, size);
//
//     mesh->indice = ib;
//     mesh->vertex = vb;
//     mesh->count = count;
//
//     slots[id].data = mesh;
//     return ResourceHandle{handleValue};
// }

// TODO: example for handle cleanup
// void ResourceManager::UnloadTexture(ResourceHandle handle) {
//     uint16_t id = get_handle_id(handle);
//     slots[id].data = nullptr;
//     slots[id].version++;
//
//     // Do some arena stuff here.
// }
