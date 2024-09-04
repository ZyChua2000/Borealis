/******************************************************************************/
/*!
\file		SubTexture2D.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 11, 2024
\brief		Declares the class for Subtexture 2D

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef SUB_TEXTURE_2D_HPP
#define SUB_TEXTURE_2D_HPP
#include <glm/glm.hpp>
#include <Core/Core.hpp>
#include <Graphics/Texture.hpp>

namespace Borealis
{
	class SubTexture2D
	{
	public :
		/*!***********************************************************************
			\brief
				Constructor of SubTexture2D
			\param[in] texture
				Texture to be used
			\param[in] min
				Minimum texture coordinates
			\param[in] max
				Maximum texture coordinates
		*************************************************************************/
		SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);

		/*!***********************************************************************
			\brief
				Get the texture
			\return
				Texture
		*************************************************************************/
		const Ref<Texture2D>& GetTexture() const { return m_Texture; }

		/*!***********************************************************************
			\brief
				Get the texture coordinates
			\return
				Texture coordinates
		*************************************************************************/
		const glm::vec2* GetTexCoords() const { return m_TexCoords; }

		/*!***********************************************************************
			\brief
				Create a subtexture from a texture and a set of coordinates
			\param[in] texture
				Texture to be used
			\param[in] min
				Minimum texture coordinates
			\param[in] max
				Maximum texture coordinates
			\return
				Subtexture
		*************************************************************************/
		static Ref<SubTexture2D> CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize = {1,1});
	private:
		Ref<Texture2D> m_Texture; //!< Texture
		glm::vec2 m_TexCoords[4]; //!< Texture coordinates
	};
}

#endif