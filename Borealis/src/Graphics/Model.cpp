/******************************************************************************/
/*!
\file		Model.cpp
\author 	Chan Guo Geng Gordon
\par    	email: g.chan\@digipen.edu
\date   	September 12, 2024
\brief		Declares the class for Model for rendering

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include <BorealisPCH.hpp>
#include <Graphics/Model.hpp>

namespace Borealis
{
	void Model::Load()
	{

	}

	void Model::Draw(const glm::mat4& transform, Ref<Shader> shader)
	{
		for (auto mesh : mMeshes)
		{
			mesh.Draw(transform, shader);
		}
	}
}