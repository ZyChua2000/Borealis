#pragma once
#include <unordered_map>
#include <unordered_set>
#include <Scene/Entity.hpp>
#include <Core/Core.hpp>
#include <entt.hpp>

//PrefabManager creates the ECS to store all prefabs as ECS objects
namespace Borealis
{
	class Prefab;
	class PrefabManager
	{
	public:
		static entt::registry& GetRegistry() { return mPrefabRegistry; }
		static entt::entity CreateEntity();

		template <typename T, typename ...Args>
		static T& AddComponent(entt::entity mPrefabID, Args&&... args)
		{
			T& Component = mPrefabRegistry.emplace<T>(mPrefabID, std::forward<Args>(args)...);
			return Component;
		}

		template<typename T>
		static bool HasComponent(entt::entity mPrefabID)
		{
			return mPrefabRegistry.storage<T>().contains(mPrefabID);
		}

		template<typename T>
		static T& GetComponent(entt::entity mPrefabID)
		{
			return mPrefabRegistry.get<T>(mPrefabID);
		}

		template<typename T>
		static void RemoveComponent(entt::entity mPrefabID)
		{
			mPrefabRegistry.remove<T>(mPrefabID);
		}

		template <typename T, typename...Args>
		static T& AddOrReplaceComponent(entt::entity mPrefabID, Args&& ... args)
		{
			T& Component = mPrefabRegistry.emplace_or_replace<T>(mPrefabID, std::forward<Args>(args)...);
			return Component;
		}

		void Register(Ref<Prefab>prefab);

	private:
		static entt::registry mPrefabRegistry;
	};
}
