#include "BorealisPCH.hpp"
#include "Scene/SceneManager.hpp"

namespace Borealis
{
    Ref<Scene> SceneManager::mActiveScene;
    std::vector<Ref<Scene>> SceneManager::mScenes;
    Entity SceneManager::GetEntity(uint64_t entityID)
    {
        return mActiveScene->GetEntityByUUID(entityID);
    }

    void SceneManager::SetActiveScene(Ref<Scene> scene)
    {
        mActiveScene = scene;
    }
}