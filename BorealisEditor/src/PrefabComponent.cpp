/******************************************************************************/
/*!
\file		Components.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 12, 2024
\brief		Declares the component structs and classes

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <unordered_set>
#include <typeindex>
#include "entt.hpp"

namespace Borealis
{
	struct PrefabComponent
	{
		entt::entity mPrefabID;
		std::unordered_set<std::type_index> mEditedComponentList;
		
	};
}

#endif