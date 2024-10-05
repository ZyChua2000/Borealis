#include "Sandbox2D.hpp"
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), mCamera(1280.0f / 720.0f)
{
}

void Sandbox2D::Init()
{
	PROFILE_FUNCTION();
	mTexture = Borealis::Texture2D::Create("assets/textures/tilemap_packed.png");
	mSubTexture = Borealis::SubTexture2D::CreateFromCoords(mTexture, { 0,14 }, { 16,16 });

	Borealis::FrameBufferProperties props{ 1280, 720, false };
	mFrameBuffer = Borealis::FrameBuffer::Create(props);

}

void Sandbox2D::Free()
{
	PROFILE_FUNCTION();
}

void Sandbox2D::UpdateFn(float dt)
{
	PROFILE_FUNCTION();

	mCamera.UpdateFn(dt);
	
	Borealis::Renderer2D::ResetStats();

	{
		PROFILE_SCOPE("Renderer::Prep");
		Borealis::RenderCommand::Clear();
		Borealis::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	}

	{
		PROFILE_SCOPE("Renderer::Draw");
		Borealis::Renderer2D::Begin(mCamera.GetCamera());
		Borealis::Renderer2D::DrawRotatedQuad({ -1,-1 }, 30.f,{ 0.5f,0.5f }, { 0.0f,1.0f,0.5f,1.0f });
		Borealis::Renderer2D::DrawQuad({ 1,1 }, { 0.7f,0.7f }, { 0.8f,0.2f,1.0f,1.0f });
		Borealis::Renderer2D::DrawQuad({ 0.f,0.f ,-0.1f },{ 10.f,10.f }, mSubTexture,1.f, {0.5f,0.1f,0.2f,0.5f});

		Borealis::Renderer2D::End();
	}
}

void Sandbox2D::EventFn(Borealis::Event& e)
{
	mCamera.EventFn(e);
}

void Sandbox2D::ImGuiRender()
{
	PROFILE_FUNCTION();


	ImGui::Begin("Settings");

	uint32_t screenID = mFrameBuffer->GetColorAttachmentRendererID();

	auto stats = Borealis::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
	ImGui::End();

}
