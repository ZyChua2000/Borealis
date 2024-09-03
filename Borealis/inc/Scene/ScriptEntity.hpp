/******************************************************************************/
/*!
\file		ScriptEntity.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 12, 2024
\brief		Declares the Script Entity class

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef SCRIPT_ENTITY_HPP
#define SCRIPT_ENTITY_HPP
#include <Scene/Entity.hpp>
namespace Borealis
{
	class ScriptEntity
	{
		friend class Scene;
	public:
		virtual ~ScriptEntity() {};

		virtual void Start() {};
		virtual void Update(float dt) {};
		virtual void End() {};

		template <typename T>
		T& GetComponent()
		{
			return mEntity.GetComponent<T>();
		}

		template <typename T>
		bool HasComponent()
		{
			return mEntity.HasComponent<T>();
		}

		template <typename T>
		void AddComponent(T component)
		{
			mEntity.AddComponent<T>(component);
		}

		template <typename T>
		void RemoveComponent()
		{
			mEntity.RemoveComponent<T>();
		}
	private:
		Entity mEntity;
		
	};

}
#endif