/******************************************************************************/
/*!
\file		RenderCommand.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 7, 2024
\brief		Declares the wrapper class for Graphics Render Commmand

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef RENDER_COMMAND_HPP
#define RENDER_COMMAND_HPP
#include "Graphics/RendererAPI.hpp"
#include <memory>

namespace Borealis
{
	class RenderCommand
	{
	public:
		inline static void Init() {
			PROFILE_FUNCTION();
			sRendererAPI->Init(); }
		inline static void DrawElements(const Ref<VertexArray>& VAO, uint32_t count = 0) { sRendererAPI->DrawElements(VAO, count); }
		inline static void DrawLines(const Ref<VertexArray>& VAO, uint32_t count = 0) { sRendererAPI->DrawLines(VAO, count); }
		inline static void Clear() { sRendererAPI->Clear(); }
		inline static void SetClearColor(const float& r, const float& g, const float& b, const float& a) { sRendererAPI->SetClearColor(r, g, b, a); }
		inline static void SetClearColor(const glm::vec4& color) { sRendererAPI->SetClearColor(color); }
		inline static void SetViewport(const uint32_t& x, const uint32_t& y, const uint32_t& width, const uint32_t& height) { sRendererAPI->SetViewport(x, y, width, height); }
		inline static void SetLineThickness(const float& thickness) { sRendererAPI->SetLineThickness(thickness); }
	private:
		static std::unique_ptr<RendererAPI> sRendererAPI;
	};
}
#endif