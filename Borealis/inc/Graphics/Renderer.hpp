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

#include <memory>
#include <Core/Core.hpp>
#include <Graphics/RenderCommand.hpp>
#include <Graphics/OrthographicCamera.hpp>
#include <Graphics/Shader.hpp>

namespace Borealis 
{
	class Renderer
	{
	public:
		/*!***********************************************************************
			\brief
				Initialise the Renderer
		*************************************************************************/
		static void Init();

		/*!***********************************************************************
			\brief
				Free the Renderer
		*************************************************************************/
		static void Free();

		/*!***********************************************************************
			\brief
				Begin the Scene
			\param[in] camera
				The camera to use
		*************************************************************************/
		static void Begin(OrthographicCamera& camera);

		/*!***********************************************************************
			\brief
				End the Scene
		*************************************************************************/
		static void End();

		/*!***********************************************************************
			\brief
				Submit a VertexArray to the Renderer
			\param[in] VAO
				The VertexArray to submit
			\param[in] shader
				The Shader to use
			\param[in] transform
				The transformation matrix
		*************************************************************************/
		static void Push(const Ref<VertexArray>& VAO, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

		/*!***********************************************************************
			\brief
				Get the RendererAPI being used
			\return
				The RendererAPI being used
		*************************************************************************/
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		/*!***********************************************************************
			\brief
				Window Resize Event Function
			\param[in]
				The width of the window
			\param[in]
				The height of the window
		*************************************************************************/
		static void OnWindowResize(const uint32_t& width, const uint32_t& height);
	private:
		struct Scene
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<Scene> sSceneData; //!< Scene Data
	};

}
#endif