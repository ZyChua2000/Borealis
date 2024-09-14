#include "BorealisPCH.hpp"
#include "Scene/SceneManager.hpp"

namespace Borealis
{
    Entity SceneManager::GetEntity(uint64_t entityID)
    {
        return mActiveScene->GetEntityByUUID(entityID);
    }

    void SceneManager::SetActiveScene(Ref<Scene> scene)
    {
        mActiveScene = scene;
    }
}