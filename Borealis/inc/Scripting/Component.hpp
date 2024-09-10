/******************************************************************************/
/*!
\file		Component.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	September 07, 2024
\brief		Declares the class for Component Scripts

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include <Core/Core.hpp>
#include <Scripting/Object.hpp>

#ifndef COMPONENT_HPP
#define COMPONENT_HPP
namespace Borealis
{
	class GameObject;
	struct TransformComponent;
	class Component : public Object
	{
	public:
		friend class GameObject;
		Component() : gameObject(nullptr), transform(nullptr) { mInstanceID = 0; } // No instance ID until attached to a gameObject
		Ref<GameObject> gameObject;
		//Ref<std::string> tag; // Reference to gameObject's tag
		Ref<TransformComponent> transform; // Reference to gameObject's transform

	private:

	};
}

#endif