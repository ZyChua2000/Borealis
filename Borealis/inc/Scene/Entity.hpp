/******************************************************************************/
/*!
\file		Entity.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 12, 2024
\brief		Declares the Entity class

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <entt.hpp>
#include <Scene/Scene.hpp>
#include <Scene/Components.hpp>

namespace Borealis
{
	class Entity
	{
	public:
		Entity() : mID(entt::null), mScene(nullptr) {};
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		template <typename T, typename ...Args>
		T& AddComponent(Args&&... args)
		{
			T& Component = mScene->mRegistry.emplace<T>(mID, std::forward<Args>(args)...);
			mScene->OnComponentAdded(*this, Component);
			return Component;
			
		}

		template<typename T>
		bool HasComponent()
		{
			return mScene->mRegistry.storage<T>().contains(mID);
		}

		template<typename T>
		T& GetComponent()
		{
			return mScene->mRegistry.get<T>(mID);
		}

		template<typename T>
		void RemoveComponent()
		{
			mScene->mRegistry.remove<T>(mID);
		}

		template <typename T, typename...Args>
		T& AddOrReplaceComponent(Args&& ... args)
		{
			T& Component= mScene->mRegistry.emplace_or_replace<T>(mID, std::forward<Args>(args)...);
			mScene->OnComponentAdded(*this, Component);
			return Component;
		}

		uint64_t GetUUID() 
		{
			return GetComponent<IDComponent>().ID;
		}
		
		std::string GetName()
		{
			return GetComponent<TagComponent>().Tag;
		}

		bool IsValid()
		{
			return mScene->mRegistry.valid(mID);
		}

		operator bool() const { return mID != entt::null; }
		operator uint32_t() const { return (uint32_t)mID; }

		bool operator==(const Entity& other) const
		{
			return mID == other.mID && mScene == other.mScene;
		}

		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}

		operator entt::entity() const { return mID; }
	private:
		entt::entity mID;
		Scene* mScene;
	};

}
#endif