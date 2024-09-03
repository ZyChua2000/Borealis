/******************************************************************************/
/*!
\file		Renderer.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 6, 2024
\brief		Declares the class for Graphics Renderer

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <Graphics/RenderCommand.hpp>
#include <Graphics/OrthographicCamera.hpp>
#include <Graphics/Shader.hpp>
#include <memory>
namespace Borealis 
{
	class Renderer
	{
	public:
		static void Init();
		static void Free();
		static void Begin(OrthographicCamera& camera);
		static void End();
		static void Push(const Ref<VertexArray>& VAO, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		static void onWindowResize(const uint32_t& width, const uint32_t& height);
	private:
		struct Scene
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static std::unique_ptr<Scene> sSceneData;
	};

}
#endif