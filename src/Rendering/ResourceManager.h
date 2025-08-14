#pragma once

#include "ArenaLinear.h"
#include "ResourceHandle.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Vertex.h"

struct ResourceSlot {
    void* data;
    uint16_t version;
};

class ResourceManager {
   public:
    static void Init();
    static void Shutdown();

    static ResourceManager* GetResourceManager();

    void* GetResource(resource_handle handle);
    mesh* GetMesh(resource_handle handle);
    shader* GetShader(resource_handle handle);
    texture* GetTexture(resource_handle handle);
    material* GetMaterial(resource_handle handle);

    resource_handle CreateMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    resource_handle CreateTexture(int width, int height);
    resource_handle CreateMaterial(resource_handle shaderHandle, resource_handle textureHandle);

    resource_handle LoadShader(std::string fileName);

    // void UnloadMesh(resource_handle handle);
    // void UnloadShader(resource_handle handle);
    // void UnloadTexture(resource_handle handle);
    // void UnloadMaterial(resource_handle handle);

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
   private:
    ResourceManager() = default;
    ~ResourceManager() = default;

    arena_linear arena;
    arena_linear arena_texture_buffer;
    arena_linear arena_mesh_buffer;
    ResourceSlot slots[1000] = {0};
    uint16_t next_handle = 1;
};
