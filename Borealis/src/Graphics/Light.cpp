/******************************************************************************/
/*!
\file		Light.cpp
\author 	Vanesius Faith Cheong
\par    	email: vanesiusfaith.c\@digipen.edu
\date   	September 30, 2024
\brief		Declares the class for Light for rendering

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "BorealisPCH.hpp"
#include "Graphics/Light.hpp"

namespace Borealis
{
	Light::Light(const TransformComponent& transformComponent, const LightComponent& lightComponent)
	{
		mLight = lightComponent;
		mTranslate = transformComponent.Translate;
	}

	void Light::SetUniforms(Ref<Shader> shader) const
	{
		shader->Bind();

		shader->Set("u_Light.position", mTranslate);
		shader->Set("u_Light.ambient", mLight.ambient);
		shader->Set("u_Light.diffuse", mLight.diffuse);
		shader->Set("u_Light.specular", mLight.specular);

		shader->Unbind();
	}
}