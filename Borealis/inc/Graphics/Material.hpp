/******************************************************************************/
/*!
\file		Material.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 22, 2024
\brief		Declares the class for Material for rendering

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include <glm/glm.hpp>
#include <unordered_map>
#include <Graphics/Texture.hpp>
#include <Graphics/Shader.hpp>
#include <Core/Core.hpp>
namespace Borealis
{
	class Material
	{
	public:
		enum TextureMaps : uint8_t
		{
			Albedo,
			Specular,
			Metallic,
			NormalMap,
			HeightMap,
			Occlusion,
			DetailMask,
			Emission
		};

		enum Props : uint8_t
		{
			Tiling,
			Offset,
			Smoothness,
			HasEmission,
			HasHeightMap,
			HasNormalMap,
			HasOcclusion,
			HasDetailMask,
		};
	
		Material(Ref<Shader> shader) : mShader(shader) {};
		~Material() {};
	private:
		std::unordered_map<TextureMaps, Ref<Texture2D>> mTextureMaps;
		std::unordered_map<TextureMaps, glm::vec4> mTextureMapColor;
		std::unordered_map<TextureMaps, float> mTextureMapFloat;
		std::unordered_map<Props, float> mProperties;
		Ref<Shader> mShader;
	};
}
#endif