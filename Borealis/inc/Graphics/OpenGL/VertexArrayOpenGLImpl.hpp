/******************************************************************************/
/*!
\file		VertexArrayOpenGLImpl.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 7, 2024
\brief		Declares the OpenGL class for Vertex Array

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/


#ifndef VERTEX_ARRAY_OPENGL_IMPL_HPP
#define VERTEX_ARRAY_OPENGL_IMPL_HPP
#include <Graphics/VertexArray.hpp>
#include <vector>
namespace Borealis
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray() override;

		void Bind() const override;
		void Unbind() const override;

		void AddVertexBuffer(const Ref<VertexBuffer>& VBO) override;
		void SetElementBuffer(const Ref<ElementBuffer>& EBO) override;

		const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return mVBOs; }
		const Ref<ElementBuffer> GetElementBuffer() const override { return mEBO; }
	private:
		std::vector<Ref<VertexBuffer>> mVBOs;
		Ref<ElementBuffer> mEBO;
		uint32_t mRendererID;
	};
}

#endif

