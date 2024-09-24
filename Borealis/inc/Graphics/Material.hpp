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
#include <unordered_map>
#include <glm/glm.hpp>
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
			Shininess,
			HasEmission,
			HasHeightMap,
			HasNormalMap,
			HasOcclusion,
			HasDetailMask,
		};

		/*!***********************************************************************
			\brief
				Constructor for a Material with a shader
			\param[in] shader
				Shader to be used for rendering
		*************************************************************************/
		Material(Ref<Shader> shader) : mShader(shader) {}

		/*!***********************************************************************
			\brief
				Destructor for Material
		*************************************************************************/
		~Material() {};

		// Setter for texture maps
		void SetTextureMap(TextureMaps map, Ref<Texture2D> texture) { mTextureMaps[map] = texture; }
		void SetTextureMapColor(TextureMaps map, const glm::vec4& color) { mTextureMapColor[map] = color; }
		void SetTextureMapFloat(TextureMaps map, float value) { mTextureMapFloat[map] = value; }
		void SetProperty(Props prop, float value) { mProperties[prop] = value; }

		void SetUniforms(Ref<Shader> shader);

	private:
		std::unordered_map<TextureMaps, Ref<Texture2D>> mTextureMaps; //Texture maps
		std::unordered_map<TextureMaps, glm::vec4> mTextureMapColor; //Texture map colors
		std::unordered_map<TextureMaps, float> mTextureMapFloat; //Texture map floats
		std::unordered_map<Props, float> mProperties; //Properties
		Ref<Shader> mShader; //Shader
		std::string name;
	}; //class Material
} //namespace Borealis
#endif