/******************************************************************************/
/*!
\file		VertexArray.cpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 7, 2024
\brief		Defines the Generic class for Vertex Array

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include <BorealisPCH.hpp>
#include <Graphics/Renderer.hpp>
#include <Graphics/OpenGL/VertexArrayOpenGLImpl.hpp>
#include <Core/LoggerSystem.hpp>


namespace Borealis
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: BOREALIS_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return MakeRef<OpenGLVertexArray>();
		}
		BOREALIS_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}