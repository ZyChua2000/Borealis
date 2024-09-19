/******************************************************************************/
/*!
\file		Material.cpp
\author 	Vanesius Faith Cheong
\par    	email: vanesiusfaith.c\@digipen.edu
\date   	September 18, 2024
\brief		Declares the class for Material for rendering

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "BorealisPCH.hpp"
#include "Graphics/Material.hpp"

namespace Borealis
{
	void Material::SetUniforms()
	{
		mShader->Bind();
		// set all material uniforms

		mShader->Unbind();
	}
}