/******************************************************************************/
/*!
\file		ScriptingExposedInternal.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	September 13, 2024
\brief		Declares the functions to expose to C# Scripting Environment

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/


#ifndef SCRIPTING_EXPOSED_INTERNAL_HPP
#define SCRIPTING_EXPOSED_INTERNAL_HPP
#include <glm/glm.hpp>
#include <mono/metadata/object.h>
#include <mono/metadata/reflection.h>
#include <Scene/Entity.hpp>
#include <Core/UUID.hpp>
namespace Borealis
{
	// Data structures
	using HasComponentFn = std::function<bool(Entity&)>;
	using AddComponentFn = std::function<void(Entity&)>;
	using RemoveComponentFn = std::function<void(Entity&)>;

	typedef struct GenericComponentFunctionMaps
	{
		static std::unordered_map<MonoType*, HasComponentFn> mHasComponentFunctions;
		static std::unordered_map<MonoType*, AddComponentFn> mAddComponentFunctions;
		static std::unordered_map<MonoType*, RemoveComponentFn> mRemoveComponentFunctions;
	} GCFM;

	/*!***********************************************************************
		\brief
			Registers all the internal functions that are written in this
			file
	*************************************************************************/
	void RegisterInternals();
	
	/*!***********************************************************************
		\brief
			Generates a UUID
		\return
			uint64_t of the generated UUID
	*************************************************************************/
	uint64_t GenerateUUID();

	/*!***********************************************************************
		\brief
			Logs a text to the console
		\param[in] text
			Text to log
	*************************************************************************/
	void Log(MonoString* text);

	/*!***********************************************************************
		\brief
			Creates an Entity
		\param[in] name
			Name of the Entity
		\return 
			uint64_t of the Entity ID
	*************************************************************************/
	uint64_t CreateEntity(MonoString* name);

	/*!***********************************************************************
		\brief
			Removes a Component from an Entity
		\param[in] entityID
			Entity ID to remove the component from
		\param[in] reflectionType
			Type of the component to remove
	*************************************************************************/
	void Entity_RemoveComponent(uint64_t entityID, MonoReflectionType* reflectionType);

	/*!***********************************************************************
		\brief
			Add a Component from an Entity
		\param[in] entityID
			Entity ID to add the component from
		\param[in] reflectionType
			Type of the component to add
	*************************************************************************/
	void Entity_AddComponent(uint64_t entityID, MonoReflectionType* reflectionType);

	/*!***********************************************************************
		\brief
			Checks if an Entity has a specific component
		\param[in] entityID
			Entity ID to check the component from
		\param[in] reflectionType
			Type of the component to check
		\return
			True if has, false if not
	*************************************************************************/
	bool Entity_HasComponent(uint64_t entityID, MonoReflectionType* reflectionType);


	void TransformComponent_GetTranslation(UUID uuid, glm::vec3* outTranslation);
	void TransformComponent_SetTranslation(UUID uuid, glm::vec3* translation);
	void TransformComponent_GetRotation(UUID uuid, glm::vec3* outRotation);
	void TransformComponent_SetRotation(UUID uuid, glm::vec3* rotation);
	void TransformComponent_GetScale(UUID uuid, glm::vec3* outScale);
	void TransformComponent_SetScale(UUID uuid, glm::vec3* scale);

	void SpriteRendererComponent_GetColor(UUID uuid, glm::vec4* outColor);
	void SpriteRendererComponent_SetColor(UUID uuid, glm::vec4* color);

	void ScriptComponent_AddComponent(uint64_t entityID, MonoReflectionType* reflectionType);
	void ScriptComponent_RemoveComponent(uint64_t entityID, MonoReflectionType* reflectionType);
	bool ScriptComponent_HasComponent(uint64_t entityID, MonoReflectionType* reflectionType);



}

#endif