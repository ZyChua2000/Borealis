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
	Ref<Texture2D> Texture2D::Create(const uint32_t& width, const uint32_t& height)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: ENGINE_LOG_ERROR("RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return MakeRef<OpenGLTexture2D>(width,height);
		}
		ENGINE_LOG_ERROR("Unknown RendererAPI");
		return nullptr;

		return Ref<Texture2D>();
	}
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: ENGINE_LOG_ERROR("RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return MakeRef<OpenGLTexture2D>(path);
		}
		ENGINE_LOG_ERROR("Unknown RendererAPI");
		return nullptr;

		return Ref<Texture2D>();
	}
}
