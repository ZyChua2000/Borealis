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
    void Material::Init()
    {
        glm::vec4 defaultColor(0.0f, 0.0f, 0.0f, 1.0f);
        for (int i = TextureMaps::Albedo; i <= TextureMaps::Emission; ++i)
        {
            mTextureMapColor[static_cast<TextureMaps>(i)] = defaultColor;
        }

        mPropertiesVec2[Tiling] = { 1.f, 1.f };
        mPropertiesFloat[Smoothness] = 0.01f;
        mPropertiesFloat[Shininess] = 1.f;
    }

	void Material::SetUniforms(Ref<Shader> shader)
	{
		shader->Bind();
        int textureUnit = 0;

        // Albedo Map
        if (mTextureMaps[Albedo])
        {
            shader->Set("u_Material.hasAlbedoMap", true);
            shader->Set("u_Material.albedoMap", textureUnit);
            shader->Set("u_Material.albedoColor", mTextureMapColor[Albedo]);
            mTextureMaps[Albedo]->Bind(textureUnit);
            textureUnit++;
		}
        else
		{
            shader->Set("u_Material.hasAlbedoMap", false);
            shader->Set("u_Material.albedoColor", mTextureMapColor[Albedo]);
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
			shader->Set("u_Material.specularColor", mTextureMapColor[Specular]);
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
            shader->Set("u_Material.metallic", mTextureMapFloat[Metallic]);
            shader->Set("u_Material.hasMetallicMap", false);
        }

        // Emission Map
        if (mTextureMaps[Emission])
        {
            shader->Set("u_Material.emissionMap", textureUnit);
            mTextureMaps[Emission]->Bind(textureUnit);
            shader->Set("u_Material.hasEmissionMap", true);
            textureUnit++;
        }
        else
        {
            shader->Set("u_Material.hasEmissionMap", false);
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

        // Set other properties
        shader->Set("u_Material.tiling", mPropertiesVec2[Tiling]);
        shader->Set("u_Material.offset", mPropertiesVec2[Offset]);
        shader->Set("u_Material.smoothness", mPropertiesFloat[Smoothness]);
        shader->Set("u_Material.shininess", mPropertiesFloat[Shininess]);
	}

    std::string Material::TextureMapToString(TextureMaps map)
    {
        switch (map)
        {
        case Albedo:      return "Albedo";
        case Specular:    return "Specular";
        case Metallic:    return "Metallic";
        case NormalMap:   return "Normal Map";
        case HeightMap:   return "Height Map";
        case Occlusion:   return "Occlusion";
        case DetailMask:  return "Detail Mask";
        case Emission:    return "Emission";
        default:          return "Unknown";
        }
    }

    std::string Material::PropsToString(Props prop)
    {
        switch (prop)
        {
        case Tiling:          return "Tiling";
        case Offset:          return "Offset";
        case Smoothness:      return "Smoothness";
        case Shininess:       return "Shininess";
        case HasEmission:     return "Has Emission";
        case HasHeightMap:    return "Has Height Map";
        case HasNormalMap:    return "Has Normal Map";
        case HasOcclusion:    return "Has Occlusion";
        case HasDetailMask:   return "Has Detail Mask";
        default:              return "Unknown";
        }
    }
}
