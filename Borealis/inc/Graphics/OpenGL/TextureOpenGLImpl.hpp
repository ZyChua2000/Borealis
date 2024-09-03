/******************************************************************************/
/*!
\file		TextureOpenGLImpl.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 8, 2024
\brief		Declares the OpenGL classes for Textures

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef TEXTURE_OPENGL_IMPL_HPP
#define TEXTURE_OPENGL_IMPL_HPP
#include <Graphics/Texture.hpp>
#include <glad/glad.h>

namespace Borealis
{
	// Virtual Class for 2D Textures
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(const uint32_t& width, const uint32_t& height);
		~OpenGLTexture2D();

		void SetData(void* data, uint32_t size) override;

		uint32_t GetWidth() const override { return mWidth; }
		uint32_t GetHeight() const override { return mHeight; }
		uint32_t GetRendererID() const override { return mRendererID; }

		void Bind(uint32_t unit = 0) const override;

		bool operator==(const Texture& other) const override{return mRendererID == ((OpenGLTexture2D&)other).mRendererID;}
	private:
		std::string mPath;
		uint32_t mRendererID;
		uint32_t mWidth, mHeight, mChannels;
		GLenum mInternalFormat, mDataFormat;
	};
}

#endif