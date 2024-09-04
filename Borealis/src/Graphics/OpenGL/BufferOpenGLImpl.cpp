/******************************************************************************/
/*!
\file		BufferOpenGLImpl.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 6, 2024
\brief		Defines the OpenGL class for Graphics Buffer

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/


#include <BorealisPCH.hpp>
#include <glad/glad.h>
#include <Graphics/OpenGL/BufferOpenGLImpl.hpp>

namespace Borealis
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
	{
		PROFILE_FUNCTION();

		glGenBuffers(1, &mRendererID);
		glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		PROFILE_FUNCTION();

		glGenBuffers(1, &mRendererID);
		glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		PROFILE_FUNCTION();

		glDeleteBuffers(1, &mRendererID);
	}
	void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}
	void OpenGLVertexBuffer::Bind() const
	{
		PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
	}
	void OpenGLVertexBuffer::Unbind() const
	{
		PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}






	OpenGLElementBuffer::OpenGLElementBuffer(uint32_t* indices, uint32_t count) : mCount(count)
	{
		PROFILE_FUNCTION();

		glGenBuffers(1, &mRendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}
	OpenGLElementBuffer::~OpenGLElementBuffer()
	{
		PROFILE_FUNCTION();

		glDeleteBuffers(1, &mRendererID);
	}
	void OpenGLElementBuffer::Bind() const
	{
		PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
	}
	void OpenGLElementBuffer::Unbind() const
	{
		PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
