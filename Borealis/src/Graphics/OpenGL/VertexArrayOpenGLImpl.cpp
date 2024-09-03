/******************************************************************************/
/*!
\file		VertexArrayOpenGLImpl.cpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 6, 2024
\brief		Defines the OpenGL class for Graphics VertexArray

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include <BorealisPCH.hpp>
#include <Graphics/OpenGL/VertexArrayOpenGLImpl.hpp>
#include <glad/glad.h>
namespace Borealis {
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return GL_FLOAT;
		case ShaderDataType::Float2:   return GL_FLOAT;
		case ShaderDataType::Float3:   return GL_FLOAT;
		case ShaderDataType::Float4:   return GL_FLOAT;
		case ShaderDataType::Mat3:     return GL_FLOAT;
		case ShaderDataType::Mat4:     return GL_FLOAT;
		case ShaderDataType::Int:      return GL_INT;
		case ShaderDataType::Int2:     return GL_INT;
		case ShaderDataType::Int3:     return GL_INT;
		case ShaderDataType::Int4:     return GL_INT;
		case ShaderDataType::Bool:     return GL_BOOL;
		}
		BOREALIS_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}


	OpenGLVertexArray::OpenGLVertexArray()
	{
		PROFILE_FUNCTION();

		glGenVertexArrays(1, &mRendererID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &mRendererID);
	}
	void OpenGLVertexArray::Bind() const
	{
		PROFILE_FUNCTION();

		glBindVertexArray(mRendererID);
	}
	void OpenGLVertexArray::Unbind() const
	{
		PROFILE_FUNCTION();

		glBindVertexArray(0);
	}
	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& VBO)
	{
		PROFILE_FUNCTION();

		BOREALIS_CORE_ASSERT(!VBO->GetLayout().GetElements().empty(), "Vertex Buffer Layout is empty!");

		glBindVertexArray(mRendererID);
		VBO->Bind();

		uint32_t index = 0;
		for (const auto& element : VBO->GetLayout())
		{
			if (element.mType >= ShaderDataType::Int)
			{
				glEnableVertexAttribArray(index);
				glVertexAttribIPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.mType),
					VBO->GetLayout().GetStride(), (const void*)element.mOffset);
			}
			else

			{
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.mType),
					element.mNormalized ? GL_TRUE : GL_FALSE, VBO->GetLayout().GetStride(), (const void*)element.mOffset);
			}
			index++;
		}

		mVBOs.push_back(VBO);
	}
	void OpenGLVertexArray::SetElementBuffer(const Ref<ElementBuffer>& EBO)
	{
		PROFILE_FUNCTION();

		glBindVertexArray(mRendererID);
		EBO->Bind();
		mEBO = EBO;
	}
}