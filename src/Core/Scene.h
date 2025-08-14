#pragma once

#include "src/Core/Components/Camera.h"
#include "src/Rendering/Renderer.h"

#include "src/Util/SparseSet.h"
#include "src/Core/Components/Renderable.h"
#include "src/Core/Components/Transform.h"

class Scene {
   public:
    Scene() = default;
    ~Scene() = default;

    void Start();
    void Update();
    void Render(Renderer* renderer);

    uint32_t CreateEntity();
    void DeleteEntity(uint32_t entity);

    void AddTransform(uint32_t ent, const transform component);
    void RemoveTransform(uint32_t ent);
    transform* GetTransform(uint32_t ent);

    void AddRenderable(uint32_t ent, const renderable& component);
    void RemoveRenderable(uint32_t ent);
    renderable* GetRenderable(uint32_t ent);

   private:
    Camera m_ActiveCamera;

    uint32_t m_NextEntityID = 1;
    std::vector<uint32_t> m_Entities;

    SparseSet<transform> m_Transforms;
    SparseSet<renderable> m_Renderables;
};
