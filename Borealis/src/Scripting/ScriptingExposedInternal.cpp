/******************************************************************************/
/*!
\file		ScriptingExposedInternal.cpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	September 13, 2024
\brief		Defines the functions to expose to C# Scripting Environment

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include <BorealisPCH.hpp>
#include <Scripting/ScriptingExposedInternal.hpp>
#include <Scene/SceneManager.hpp>
#include <Core/UUID.hpp>
#include <Core/LoggerSystem.hpp>


namespace Borealis
{
	std::unordered_map<MonoType*, HasComponentFn> GCFM::mHasComponentFunctions;
	std::unordered_map<MonoType*, AddComponentFn> GCFM::mAddComponentFunctions;
	std::unordered_map<MonoType*, RemoveComponentFn> GCFM::mRemoveComponentFunctions;
#define BOREALIS_ADD_INTERNAL_CALL(Name) mono_add_internal_call("Borealis.InternalCalls::" #Name, Name)
	void RegisterInternals()
	{
		//BOREALIS_ADD_INTERNAL_CALL(GetComponent<TransformComponent>);
		BOREALIS_ADD_INTERNAL_CALL(GenerateUUID);
		BOREALIS_ADD_INTERNAL_CALL(Log);
		BOREALIS_ADD_INTERNAL_CALL(CreateEntity);

		BOREALIS_ADD_INTERNAL_CALL(Entity_AddComponent);
		BOREALIS_ADD_INTERNAL_CALL(Entity_HasComponent);
		BOREALIS_ADD_INTERNAL_CALL(Entity_RemoveComponent);

		BOREALIS_ADD_INTERNAL_CALL(TransformComponent_GetTranslation);
		BOREALIS_ADD_INTERNAL_CALL(TransformComponent_SetTranslation);
		BOREALIS_ADD_INTERNAL_CALL(TransformComponent_GetRotation);
		BOREALIS_ADD_INTERNAL_CALL(TransformComponent_SetRotation);
		BOREALIS_ADD_INTERNAL_CALL(TransformComponent_GetScale);
		BOREALIS_ADD_INTERNAL_CALL(TransformComponent_SetScale);

		BOREALIS_ADD_INTERNAL_CALL(SpriteRendererComponent_GetColor);
		BOREALIS_ADD_INTERNAL_CALL(SpriteRendererComponent_SetColor);
	}
	uint64_t GenerateUUID()
	{
		return UUID();
	}
	void Log(MonoString* text)
	{
		char* message = mono_string_to_utf8(text);
		std::string logMessage = message;
		mono_free(message);
		BOREALIS_CORE_TRACE(logMessage.c_str());
	}

	uint64_t CreateEntity(MonoString* text)
	{
		char* name = mono_string_to_utf8(text);
		std::string strName = name;
		return SceneManager::GetActiveScene()->CreateEntity(strName).GetUUID();
	}

	void Entity_RemoveComponent(uint64_t entityID, MonoReflectionType* reflectionType)
	{
		auto Entity = SceneManager::GetEntity(entityID);

		if (!Entity)
		{
			BOREALIS_CORE_WARN("Entity does not exist: Entity.RemoveComponent");
			return;
		}

		if (reflectionType == nullptr)
		{
			BOREALIS_CORE_WARN("Reflection type is null: Entity.RemoveComponent");
			return;
		}

		MonoType* CPPType = mono_reflection_type_get_type(reflectionType);
		if (GCFM::mRemoveComponentFunctions.find(CPPType) != GCFM::mRemoveComponentFunctions.end())
		{
			GCFM::mRemoveComponentFunctions.at(CPPType)(Entity);
		}
		else
		{
			BOREALIS_CORE_WARN("Failed to create component: Entity.RemoveComponent");
			char* typeName = mono_type_get_name(CPPType);
			mono_free(typeName);
			return;
		}
	}

	void Entity_AddComponent(uint64_t entityID, MonoReflectionType* reflectionType)
	{
		auto Entity = SceneManager::GetEntity(entityID);

		if (!Entity)
		{
			BOREALIS_CORE_WARN("Entity does not exist: Entity.AddComponent");
			return;
		}

		if (reflectionType == nullptr)
		{
			BOREALIS_CORE_WARN("Reflection type is null: Entity.AddComponent");
			return;
		}

		MonoType* CPPType = mono_reflection_type_get_type(reflectionType);
		if (GCFM::mAddComponentFunctions.find(CPPType) != GCFM::mAddComponentFunctions.end())
		{
			GCFM::mAddComponentFunctions.at(CPPType)(Entity);
		}
		else
		{
			BOREALIS_CORE_WARN("Failed to create component: Entity.AddComponent");
			char* typeName = mono_type_get_name(CPPType);
			mono_free(typeName);
			return;
		}
	}

	bool Entity_HasComponent(uint64_t entityID, MonoReflectionType* reflectionType)
	{
		auto Entity = SceneManager::GetEntity(entityID);

		if (!Entity)
		{
			BOREALIS_CORE_WARN("Entity does not exist: Entity.HasComponent");
			return false;
		}

		if (reflectionType == nullptr)
		{
			BOREALIS_CORE_WARN("Reflection type is null: Entity.HasComponent");
			return false;
		}

		MonoType* CPPType = mono_reflection_type_get_type(reflectionType);
		if (GCFM::mHasComponentFunctions.find(CPPType) != GCFM::mHasComponentFunctions.end())
		{
			return GCFM::mHasComponentFunctions.at(CPPType)(Entity);
		}
		else
		{
			BOREALIS_CORE_WARN("Failed to create component: Entity.HasComponent");
			char* typeName = mono_type_get_name(CPPType);
			mono_free(typeName);
			return false;
		}
	}
	void TransformComponent_GetTranslation(UUID uuid, glm::vec3* outTranslation)
	{
		Scene* scene = SceneManager::GetActiveScene().get();
		BOREALIS_CORE_ASSERT(scene, "Scene is null");
		Entity entity = scene->GetEntityByUUID(uuid);
		BOREALIS_CORE_ASSERT(entity, "Entity is null");
		*outTranslation = entity.GetComponent<TransformComponent>().Translate;
	}
	void TransformComponent_SetTranslation(UUID uuid, glm::vec3* translation)
	{
		Scene* scene = SceneManager::GetActiveScene().get();
		BOREALIS_CORE_ASSERT(scene, "Scene is null");
		Entity entity = scene->GetEntityByUUID(uuid);
		BOREALIS_CORE_ASSERT(entity, "Entity is null");
		entity.GetComponent<TransformComponent>().Translate = *translation;
	}
	void TransformComponent_GetRotation(UUID uuid, glm::vec3* outRotation)
	{
		Scene* scene = SceneManager::GetActiveScene().get();
		BOREALIS_CORE_ASSERT(scene, "Scene is null");
		Entity entity = scene->GetEntityByUUID(uuid);
		BOREALIS_CORE_ASSERT(entity, "Entity is null");
		*outRotation = entity.GetComponent<TransformComponent>().Rotation;
	
	}
	void TransformComponent_SetRotation(UUID uuid, glm::vec3* rotation)
	{
		Scene* scene = SceneManager::GetActiveScene().get();
		BOREALIS_CORE_ASSERT(scene, "Scene is null");
		Entity entity = scene->GetEntityByUUID(uuid);
		BOREALIS_CORE_ASSERT(entity, "Entity is null");
		entity.GetComponent<TransformComponent>().Rotation = *rotation;
	}
	void TransformComponent_GetScale(UUID uuid, glm::vec3* outScale)
	{
		Scene* scene = SceneManager::GetActiveScene().get();
		BOREALIS_CORE_ASSERT(scene, "Scene is null");
		Entity entity = scene->GetEntityByUUID(uuid);
		BOREALIS_CORE_ASSERT(entity, "Entity is null");
		*outScale = entity.GetComponent<TransformComponent>().Scale;
	}
	void TransformComponent_SetScale(UUID uuid, glm::vec3* scale)
	{
		Scene* scene = SceneManager::GetActiveScene().get();
		BOREALIS_CORE_ASSERT(scene, "Scene is null");
		Entity entity = scene->GetEntityByUUID(uuid);
		BOREALIS_CORE_ASSERT(entity, "Entity is null");
		entity.GetComponent<TransformComponent>().Scale = *scale;
	}
	void SpriteRendererComponent_GetColor(UUID uuid, glm::vec4* outColor)
	{
		Scene* scene = SceneManager::GetActiveScene().get();
		BOREALIS_CORE_ASSERT(scene, "Scene is null");
		Entity entity = scene->GetEntityByUUID(uuid);
		BOREALIS_CORE_ASSERT(entity, "Entity is null");
		entity.GetComponent<SpriteRendererComponent>().Colour = *outColor;
	}
	void SpriteRendererComponent_SetColor(UUID uuid, glm::vec4* color)
	{
		Scene* scene = SceneManager::GetActiveScene().get();
		BOREALIS_CORE_ASSERT(scene, "Scene is null");
		Entity entity = scene->GetEntityByUUID(uuid);
		BOREALIS_CORE_ASSERT(entity, "Entity is null");
		entity.GetComponent<SpriteRendererComponent>().Colour = *color;
	}
}