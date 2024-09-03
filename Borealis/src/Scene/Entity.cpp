/******************************************************************************/
/*!
\file		Entity.cpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 12, 2024
\brief		Defines the Entity class

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include <BorealisPCH.hpp>
#include <Scene/Entity.hpp>

namespace Borealis
{
	Entity::Entity(entt::entity handle, Scene* scene) : mID(handle), mScene(scene)
	{
	}

}