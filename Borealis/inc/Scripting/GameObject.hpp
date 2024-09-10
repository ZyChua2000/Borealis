/******************************************************************************/
/*!
\file		GameObject.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	September 07, 2024
\brief		Declares the class for GameObject Scripts

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <Scripting/Object.hpp>
#include <Scene/Entity.hpp>
namespace Borealis
{
	class GameObject : public Object
	{
	public:
		GameObject() { mInstanceID = ++Object::mInstanceCounter; activeSelf = true; }
		GameObject(Entity entity) { mEntity = entity; mInstanceID = ++Object::mInstanceCounter; activeSelf = true; }

		bool activeSelf;
		// tag
		// transform
		template <typename T>
		T& AddComponent(T& component) { component.mInstanceID = this->mInstanceID; return mEntity.AddComponent<T>(component); };
		template <typename T>
		T& AddComponent() { mEntity.AddComponent<T>().mInstanceID = this->mInstanceID; return mEntity.GetComponent<T>(); };

		//compare tag
		template <typename T>
		T& GetComponent() { return mEntity.GetComponent<T>(); };

		//static void Destroy(Object obj, float t);
		//static void DestroyImmediate(Object obj, bool allowDestroyingAssets = false);
		//static void DontDestroyOnLoad(Object target);
		//static Object Instantiate(Object original);

		//operator bool() const;
		bool operator==(const Object& rhs) const
		{
			return mInstanceID == rhs.GetInstanceID();
		}
		bool operator!=(const Object& rhs) const
		{
			return mInstanceID != rhs.GetInstanceID();
		}
	private:
		Entity mEntity;
	};
}

#endif