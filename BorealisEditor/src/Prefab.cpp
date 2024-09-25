/******************************************************************************/
/*!
\file		Prefab.cpp
\author 	Yeo Jun Jie
\par    	email: junjie.yeo@digipen.edu
\date   	September 12, 2024
\brief		Definations of Prefab.h

Contains the definations of the Prefab class

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include <Scene/Components.hpp>
#include "Prefab.hpp"
#include <PrefabManager.hpp>
#include <iostream>  // For testing/debugging purposes
#include "PrefabComponent.hpp"

namespace Borealis {


#define AddPrefabComponent(ComponentName) \
	if (entity.HasComponent<ComponentName>()) \
	{ \
		PrefabManager::AddOrReplaceComponent<ComponentName>(mPrefabID, entity.GetComponent<ComponentName>()); \
	} \

	//Creates Prefab base on exisiting entity
	Prefab::Prefab(Entity entity)
	{
		mPrefabID = PrefabManager::CreateEntity();
		AddPrefabComponent(TransformComponent);
		AddPrefabComponent(TagComponent);
		AddPrefabComponent(IDComponent);
		// Add all components to prefab manager ECS
	}

	void Prefab::AddChild(Ref<Entity> entity)
	{
		//if the entity is valid and the it is not in list
		if (entity && mChildren.find(entity) == mChildren.end())
		{
			mChildren.insert(entity);
		}
	}
	void Prefab::RemoveChild(Ref<Entity> entity)
	{
		//if the entity is valid and if it is in the list
		if (entity && mChildren.find(entity) != mChildren.end())
		{
			mChildren.erase(entity);
		}
	}

	void Prefab::UpdateAllInstances()
	{

	}
	
	struct PrefabInstanceComponent
	{
		std::unordered_set<std::type_info> mEditedComponents;
		//HasComponentEdited
	};
}