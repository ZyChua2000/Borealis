/******************************************************************************/
/*!
\file		VertexArray.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 7, 2024
\brief		Declares the Generic class for Vertex Array

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP
#include <Graphics/Buffer.hpp>
#include <Core/Core.hpp>
namespace Borealis
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetElementBuffer(const Ref <ElementBuffer>& vertexBuffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<ElementBuffer> GetElementBuffer() const = 0;

		static Ref<VertexArray> Create();

	};
}
#endif