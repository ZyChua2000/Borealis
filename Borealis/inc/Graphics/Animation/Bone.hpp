/******************************************************************************/
/*!
\file		Bone.hpp
\author 	Vanesius Faith Cheong
\par    	email: vanesiusfaith.c\@digipen.edu
\date   	September 15, 2024
\brief		Declares the class for Bone for rendering

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#ifndef BONE_HPP
#define BONE_HPP

#include <glm/glm.hpp>
#include <string>

namespace Borealis 
{
	struct Bone 
	{
		std::string name;
		int id;
		glm::mat4 offsetMatrix; // xform matrix for the bone
	};
}
#endif