/******************************************************************************/
/*!
\file		Buffer.cpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 6, 2024
\brief		Declares the generic class for Graphics Buffer

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/


#include <BorealisPCH.hpp>
#include <glad/glad.h>
#include <Graphics/Renderer.hpp>
#include <Graphics/OpenGL/BufferOpenGLImpl.hpp>
#include <Graphics/Buffer.hpp>
#include <Core/LoggerSystem.hpp>


namespace Borealis
{
	void BufferLayout::CalculateOffsetsAndStride()
	{
		uint32_t offset = 0;
		mStride = 0;
		for (auto& element : mElements)
		{
			element.mOffset = offset;
			offset += element.mSize;
			mStride += element.mSize;
		}
	}


	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: BOREALIS_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return MakeRef<OpenGLVertexBuffer>(size);
		}
		BOREALIS_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: BOREALIS_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return MakeRef<OpenGLVertexBuffer>(vertices, size);
		}
		BOREALIS_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
	
	Ref<ElementBuffer> ElementBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: BOREALIS_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return MakeRef<OpenGLElementBuffer>(indices, count);
		}
		BOREALIS_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
	uint32_t BufferElement::GetComponentCount() const
	{
		switch (mType)
		{
		case ShaderDataType::Float:    return 1;
		case ShaderDataType::Float2:   return 2;
		case ShaderDataType::Float3:   return 3;
		case ShaderDataType::Float4:   return 4;
		case ShaderDataType::Mat3:     return 3 * 3;
		case ShaderDataType::Mat4:     return 4 * 4;
		case ShaderDataType::Int:      return 1;
		case ShaderDataType::Int2:     return 2;
		case ShaderDataType::Int3:     return 3;
		case ShaderDataType::Int4:     return 4;
		case ShaderDataType::Bool:     return 1;
		}

		BOREALIS_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

}