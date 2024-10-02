#include <Scene/Entity.hpp>
#include <Core/Core.hpp>
#include <PrefabManager.hpp>

namespace Borealis
{
	Scene PrefabManager::mPrefabScene;
	entt::entity PrefabManager::CreateEntity()
	{
		return mPrefabScene.GetRegistry().create();
	}

}

