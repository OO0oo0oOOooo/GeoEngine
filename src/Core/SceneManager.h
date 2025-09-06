#pragma once

#include "Scene.h"

class SceneManager {
   public:
    SceneManager();
    ~SceneManager();

    void Start();
    void Update();

    void Load(std::string path);
    void Switch(size_t index);

    size_t GetActiveSceneIndex() { return m_ActiveIndex; }
    Scene* GetActiveScene() { return m_ActiveScene; }

   private:
    size_t m_ActiveIndex;
    Scene* m_ActiveScene;
    std::vector<Scene*> m_Scenes;
};
