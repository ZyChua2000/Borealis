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
		/*!***********************************************************************
			\brief
				Destructor for Virtual Class VertexArray
		*************************************************************************/
		virtual ~VertexArray() {};

		/*!***********************************************************************
			\brief
				Binds the VertexArray
		*************************************************************************/
		virtual void Bind() const = 0;

		/*!***********************************************************************
			\brief
				Unbinds the VertexArray
		*************************************************************************/
		virtual void Unbind() const = 0;

		/*!***********************************************************************
			\brief
				Adds a VertexBuffer to the VertexArray
			\param vertexBuffer
				The VertexBuffer to be added
		*************************************************************************/
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;

		/*!***********************************************************************
			\brief
				Sets the ElementBuffer of the VertexArray
			\param vertexBuffer
				The ElementBuffer to be set
		*************************************************************************/
		virtual void SetElementBuffer(const Ref <ElementBuffer>& vertexBuffer) = 0;

		/*!***********************************************************************
			\brief
				Returns the VertexBuffers of the VertexArray
			\return
				A vector of VertexBuffers
		*************************************************************************/
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;

		/*!***********************************************************************
			\brief
				Returns the ElementBuffer of the VertexArray
			\return
				The ElementBuffer
		*************************************************************************/
		virtual const Ref<ElementBuffer> GetElementBuffer() const = 0;

		/*!***********************************************************************
			\brief
				Creates a VertexArray based on the Graphics API
			\return
				A reference to the created VertexArray
		*************************************************************************/
		static Ref<VertexArray> Create();
	}; // class VertexArray
} // namespace Borealis
#endif