#include <Scene/Entity.hpp>
#include <Core/Core.hpp>
#include <PrefabManager.hpp>

namespace Borealis
{
	entt::registry PrefabManager::mPrefabRegistry;
	entt::entity PrefabManager::CreateEntity()
	{
		return mPrefabRegistry.create();
	}

}

