/******************************************************************************/
/*!
\file		BufferOpenGLImpl.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 6, 2024
\brief		Declares the OpenGL class for Graphics Buffer

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef BUFFER_OPENGL_IMPL_HPP
#define BUFFER_OPENGL_IMPL_HPP
#include <Graphics/Buffer.hpp>
namespace Borealis
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		OpenGLVertexBuffer(uint32_t size);
		~OpenGLVertexBuffer();

		void SetLayout(const BufferLayout& layout) override { mLayout = layout; }
		void SetData(const void* data, uint32_t size) override;
		const BufferLayout& GetLayout() const override { return mLayout; }

		void Bind() const override;
		void Unbind() const override;
	private:
		uint32_t mRendererID;
		BufferLayout mLayout;
	};

	class OpenGLElementBuffer : public ElementBuffer
	{
	public:
		OpenGLElementBuffer(uint32_t* indices, uint32_t count);
		~OpenGLElementBuffer();

		uint32_t GetCount() const override { return mCount; }

		void Bind() const override;
		void Unbind() const override;
	private:
		uint32_t mRendererID;
		uint32_t mCount;
	};

}


#endif