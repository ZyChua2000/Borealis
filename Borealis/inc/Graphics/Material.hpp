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
		/*!***********************************************************************
			\brief
				Setter for texture maps
			\param[in] map
				Type of map
			\texture[in] texture
				The texture map
		*************************************************************************/
		void SetTextureMap(TextureMaps map, Ref<Texture2D> texture) { mTextureMaps[map] = texture; }

		/*!***********************************************************************
			\brief
				Setter for texture map color
			\param[in] map
				Type of map
			\texture[in] color
				The color
		*************************************************************************/
		void SetTextureMapColor(TextureMaps map, const glm::vec4& color) { mTextureMapColor[map] = color; }

		/*!***********************************************************************
			\brief
				Setter for texture map floats 
			\param[in] map
				Type of map
			\texture[in] value
				float to set
		*************************************************************************/
		void SetTextureMapFloat(TextureMaps map, float value) { mTextureMapFloat[map] = value; }

		/*!***********************************************************************
			\brief
				Setter for properties
			\param[in] prop
				Type of property
			\texture[in] value
				The value to set
		*************************************************************************/
		void SetProperty(Props prop, float value) { mPropertiesFloat[prop] = value; }

		/*!***********************************************************************
			\brief
				This function sets the uniforms in the material's shader
			\param[in] shader
				Temp variable to take in same shader as renderer
		*************************************************************************/
		void SetUniforms(Ref<Shader> shader);

		void SetName(std::string name) { mName = name; }
		std::string GetName() const { return mName; }
		std::unordered_map<TextureMaps, Ref<Texture2D>> GetTextureMaps() const { return mTextureMaps; }
		std::unordered_map<TextureMaps, glm::vec4> GetTextureMapColor() const { return mTextureMapColor; }
		std::unordered_map<TextureMaps, float> GetTextureMapFloats() const { return mTextureMapFloat; }
		std::unordered_map<Props, float> GetPropertiesFloats() const { return mPropertiesFloat; }
		std::unordered_map<Props, glm::vec2> GetPropertiesVec2() const { return mPropertiesVec2; }

		static std::string TextureMapToString(TextureMaps map);
		static std::string PropsToString(Props prop);

	private:
		std::unordered_map<TextureMaps, Ref<Texture2D>> mTextureMaps; //Texture maps
		std::unordered_map<TextureMaps, glm::vec4> mTextureMapColor; //Texture map colors
		std::unordered_map<TextureMaps, float> mTextureMapFloat; //Texture map floats
		std::unordered_map<Props, float> mPropertiesFloat; //Properties
		std::unordered_map<Props, glm::vec2> mPropertiesVec2; //Properties
		Ref<Shader> mShader; //Shader
		std::string mName;
	}; //class Material
} //namespace Borealis
#endif