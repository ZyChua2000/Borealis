/******************************************************************************/
/*!
\file		Texture.cpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 8, 2024
\brief		Declares the Generic class for Textures

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include <BorealisPCH.hpp>
#include <Graphics/Texture.hpp>
#include <Graphics/Renderer.hpp>
#include <Graphics/OpenGL/TextureOpenGLImpl.hpp>
namespace Borealis
{
	Ref<Texture2D> Texture2D::Create(const TextureInfo& textureInfo)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: BOREALIS_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return MakeRef<OpenGLTexture2D>(textureInfo);
		}
		BOREALIS_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;

		return Ref<Texture2D>();
	}
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: BOREALIS_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return MakeRef<OpenGLTexture2D>(path);
		}
		BOREALIS_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;

		return Ref<Texture2D>();
	}
}
