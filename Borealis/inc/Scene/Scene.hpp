/******************************************************************************/
/*!
\file		Scene.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 12, 2024
\brief		Declares the class for Scene

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef SCENE_HPP
#define SCENE_HPP
#include <Core/UUID.hpp>
#include <entt.hpp>
#include <Graphics/EditorCamera.hpp>
namespace Borealis
{
	class Entity;

	class Scene
	{
	public:

		friend class Entity;
		friend class SceneHierarchyPanel;
		friend class Serialiser;

		Scene(std::string name = "newScene", std::string scenepath = "");
		virtual ~Scene();
		static Ref<Scene> Copy(const Ref<Scene>& other);

		void UpdateRuntime(float dt);
		void UpdateEditor(float dt, EditorCamera& camera);

		Entity CreateEntity(const std::string& name);
		Entity CreateEntityWithUUID(const std::string& name, uint64_t UUID);
		Entity GetEntityByUUID(UUID uuid);
		void DestroyEntity(Entity entity);
		void DuplicateEntity(Entity entity);

		void ResizeViewport(const uint32_t& width, const uint32_t& height);

		entt::registry& GetRegistry() { return mRegistry; }
		const std::string& GetName() const { return mName; }
		const std::string& GetScenePath() const { return mScenePath; }
		void SetName(const std::string& name) { mName = name; }
		void SetScenePath(const std::string& path) { mScenePath = path; }
		

		void RuntimeStart();
		void RuntimeEnd();

		Entity GetPrimaryCameraEntity();
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

		entt::registry mRegistry;
		uint32_t mViewportWidth = 0, mViewportHeight = 0;
		std::string mName;
		std::string mScenePath;
		std::unordered_map<UUID, entt::entity> mEntityMap;

		bool hasRuntimeStarted = false;

	};
}

#endif