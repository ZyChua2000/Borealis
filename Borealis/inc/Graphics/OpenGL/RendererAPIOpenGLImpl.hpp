/******************************************************************************/
/*!
\file		RendererAPIOpenGLImpl.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 7, 2024
\brief		Declares the class for Graphics Renderer API

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef RENDERER_API_OPENGL_IMPL_HPP
#define RENDERER_API_OPENGL_IMPL_HPP
#include "Graphics/RendererAPI.hpp"

namespace Borealis
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		void Init() override;
		void Clear() override;
		void SetClearColor(const float& r, const float& g, const float& b, const float& a) override;
		void SetClearColor(const glm::vec4& color) override;
		void DrawElements(const Ref<VertexArray>& VAO, uint32_t indexCount = 0) override;
		void DrawLines(const Ref<VertexArray>& VAO, uint32_t vertexCount = 0) override;
		void SetViewport(const uint32_t& x, const uint32_t& y, const uint32_t& width, const uint32_t& height) override;
		void SetLineThickness(const float& thickness) override;

	};
}

#endif