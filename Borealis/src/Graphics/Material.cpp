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
	void Material::SetUniforms(Ref<Shader> shader)
	{
		shader->Bind();
        int textureUnit = 0;

        // Albedo Map
        if (mTextureMaps[Albedo])
        {
            shader->Set("u_Material.hasAlbedoMap", true);
            shader->Set("u_Material.albedoMap", textureUnit);
            mTextureMaps[Albedo]->Bind(textureUnit);
            textureUnit++;
		}
        else
		{
            shader->Set("u_Material.hasAlbedoMap", false);
            shader->Set("u_Material.albedoColor", {1.f, 0.f, 0.f, 1.f});
        }

        // Specular Map
        if (mTextureMaps[Specular])
        {
            shader->Set("u_Material.specularMap", textureUnit);
            mTextureMaps[Specular]->Bind(textureUnit);
            shader->Set("u_Material.hasSpecularMap", true);
            textureUnit++;
        }
        else
        {
            shader->Set("u_Material.hasSpecularMap", false);
			shader->Set("u_Material.specularColor", {1.0, 1.0, 1.0});
        }

        // Metallic
        if (mTextureMaps[Metallic])
        {
            shader->Set("u_Material.metallic", textureUnit);
            mTextureMaps[DetailMask]->Bind(textureUnit);
            shader->Set("u_Material.hasMetallicMap", true);
            textureUnit++;
        }
        else
        {
            shader->Set("u_Material.metallic", 0.5f);
            shader->Set("u_Material.hasMetallicMap", false);
        }

        // Emission Map
        if (mTextureMaps[Emission])
        {
            shader->Set("u_Material.emissionMap", textureUnit);
            mTextureMaps[Emission]->Bind(textureUnit);
            shader->Set("u_Material.hasEmission", true);
            textureUnit++;
        }
        else
        {
            shader->Set("u_Material.hasEmission", false);
            shader->Set("u_Material.emissionColor", mTextureMapColor[Emission]);
        }

        // Normal Map
        if (mTextureMaps[NormalMap])
        {
            shader->Set("u_Material.normalMap", textureUnit);
            mTextureMaps[NormalMap]->Bind(textureUnit);
            shader->Set("u_Material.hasNormalMap", true);
            textureUnit++;
        }

        // Height Map
        if (mTextureMaps[HeightMap])
        {
            shader->Set("u_Material.heightMap", textureUnit);
            mTextureMaps[HeightMap]->Bind(textureUnit);
            textureUnit++;
        }

        // Occlusion
        if (mTextureMaps[Occlusion])
        {
            shader->Set("u_Material.occlusionMap", textureUnit);
            mTextureMaps[Occlusion]->Bind(textureUnit);
            textureUnit++;
        }

        // Detail Mask
        if (mTextureMaps[DetailMask])
        {
            shader->Set("u_Material.detailMaskMap", textureUnit);
            mTextureMaps[DetailMask]->Bind(textureUnit);
            textureUnit++;
        }

        //// Set other properties
        shader->Set("u_Material.tiling", mProperties[Tiling]);
        shader->Set("u_Material.offset", mProperties[Offset]);
        shader->Set("u_Material.smoothness", mProperties[Smoothness]);
        shader->Set("u_Material.shininess", 100.f);
	}
}