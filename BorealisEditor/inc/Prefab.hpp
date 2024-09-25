/******************************************************************************/
/*!
\file		Prefab.hpp
\author 	Yeo Jun Jie
\par    	email: junjie.yeo@digipen.edu
\date   	September 12, 2024
\brief		Declaration of Prefab class

The Prefab class is used to define reusable templates for creating
entities with specific components in the game engine.

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef PREFAB_HPP
#define PREFAB_HPP

#include <unordered_set>
#include <any>
#include <string>
#include <vector>
#include <typeindex>
#include <entt.hpp>
#include <Scene/Scene.hpp>
#include <Scene/Entity.hpp>
#include <Core/UUID.hpp>
#include <PrefabManager.hpp>
namespace Borealis
{

	class Prefab
	{
	public:
		Prefab(Entity entity);

		// Add a component to the prefab
		//template <typename T>
		//void AddComponent(const T& component) {
		//	mComponents[typeid(T)] = std::make_any<T>(component);
		//}

		// Retrieve a component from the prefab
		template <typename T>
		T& GetComponent() {
			return PrefabManager::GetRegistry().get<T>(mPrefabID);
		}

		// Update all instances of the prefab
		void UpdateAllInstances();

		void AddChild(Ref<Entity> entity);
		void RemoveChild(Ref<Entity> entity);

	private:
		entt::entity mPrefabID;
		std::unordered_set<Ref<Entity>> mChildren;
	};

}

#endif
