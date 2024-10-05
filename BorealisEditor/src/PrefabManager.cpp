#include <Scene/Entity.hpp>
#include <Core/Core.hpp>
#include <PrefabManager.hpp>
#include <Prefab.hpp>

namespace Borealis
{
	std::unordered_map<UUID, Ref<Prefab>> PrefabManager::mPrefabs;
	Scene PrefabManager::mPrefabScene;
	entt::entity PrefabManager::CreateEntity()
	{
		return mPrefabScene.GetRegistry().create();
	}

	void PrefabManager::Register(Ref<Prefab> prefab)
	{
		mPrefabs[prefab->GetUUID()] = prefab;
	}

}

