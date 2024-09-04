/******************************************************************************/
/*!
\file		Framebuffer.cpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 11, 2024
\brief		Defines the Generic class for Frame buffers

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include <BorealisPCH.hpp>
#include <Core/Core.hpp>
#include <Graphics/Framebuffer.hpp>
#include <Graphics/Renderer.hpp>
#include <Graphics/OpenGL/FrameBufferOpenGLImpl.hpp>
namespace Borealis
{
	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferProperties& properties)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    BOREALIS_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL:  return MakeRef<OpenGLFrameBuffer>(properties);
		}

		BOREALIS_CORE_ASSERT(false,  "Unknown RendererAPI");
		return nullptr;
	}
}
