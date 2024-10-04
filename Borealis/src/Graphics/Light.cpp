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

		glm::vec2 innerOuterSpot = glm::vec2{ cos(glm::radians(mLight.InnerOuterSpot.x)), cos(glm::radians(mLight.InnerOuterSpot.y)) };

		shader->Set("u_Light.position", mTranslate);
		shader->Set("u_Light.ambient", mLight.ambient);
		shader->Set("u_Light.diffuse", mLight.diffuse);
		shader->Set("u_Light.specular", mLight.specular);
		shader->Set("u_Light.direction", mLight.direction);
		//->Set("u_Light.range", mLight.Range);
		shader->Set("u_Light.innerOuterAngle", innerOuterSpot);
		shader->Set("u_Light.linear", mLight.linear);
		shader->Set("u_Light.quadratic", mLight.quadratic);
		shader->Set("u_Light.type", static_cast<int>(mLight.type));

		shader->Unbind();
	}
}