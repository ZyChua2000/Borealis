/******************************************************************************/
/*!
\file		RendererAPI.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 7, 2024
\brief		Declares the class for Graphics Renderer API

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef RENDERER_API_HPP
#define RENDERER_API_HPP
#include <glm/glm.hpp>
#include <Graphics/VertexArray.hpp>
namespace Borealis
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1	
		};

		virtual ~RendererAPI() {};
		virtual void Init() = 0;
		virtual void Clear() = 0;
		virtual void SetClearColor(const float& r, const float& g, const float& b, const float& a) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void DrawElements(const Ref<VertexArray>& VAO, uint32_t indexCount = 0) = 0;
		virtual void DrawLines(const Ref<VertexArray>& VAO, uint32_t vertexCount = 0) = 0;
		virtual void SetViewport(const uint32_t& x, const uint32_t& y, const uint32_t& width, const uint32_t& height) = 0;
		virtual void SetLineThickness(const float& thickness) = 0;

		inline static API GetAPI() { return sAPI; }
	private:
		static API sAPI;
	};

}
#endif