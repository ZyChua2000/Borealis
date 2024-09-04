/******************************************************************************/
/*!
\file		Renderer.cpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 6, 2024
\brief		Defines the class for Graphics Renderer

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include <BorealisPCH.hpp>
#include <Core/Core.hpp>
#include <Graphics/Renderer.hpp>
#include <Graphics/OpenGL/ShaderOpenGLImpl.hpp>
#include <Graphics/Renderer2D.hpp>

namespace Borealis
{
	 Scope<Renderer::Scene> Renderer::sSceneData = MakeScope<Renderer::Scene>();
	 void Renderer::Init()
	 {
		 PROFILE_FUNCTION();

		 RenderCommand::Init();
		 Renderer2D::Init();
	 }
	 void Renderer::Free()
	 {
		 Renderer2D::Free();
	 }
	 void Renderer::Begin(OrthographicCamera& camera)
	 {
		 sSceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	 }
	 void Renderer::End()
	 {
	 }
	 void Renderer::Push(const Ref<VertexArray>& VAO, const Ref<Shader>& shader, const glm::mat4& transform)
	 {
		 shader->Bind();
		 shader->Set("u_ViewProjection", sSceneData->ViewProjectionMatrix);
		 shader->Set("u_Transform", transform);
		 VAO->Bind();
		 RenderCommand::DrawElements(VAO);
	 }
	 void Renderer::OnWindowResize(const uint32_t& width, const uint32_t& height)
	 {
		 RenderCommand::SetViewport(0, 0, width, height);
	 }
}