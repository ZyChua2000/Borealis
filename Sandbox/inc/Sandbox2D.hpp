#pragma once
#include <Borealis.hpp>
#include <vector>
class Sandbox2D : public Borealis::Layer
{
public:
	Sandbox2D();
	~Sandbox2D() {}
	void Init() override;
	void Free() override;
	void UpdateFn(float dt) override;
	void EventFn(Borealis::Event& e) override;
	void ImGuiRender() override;
private:
	Borealis::OrthographicCameraController mCamera;
	Borealis::Ref<Borealis::Texture2D> mTexture;
	Borealis::Ref<Borealis::SubTexture2D> mSubTexture;
	Borealis::Ref<Borealis::FrameBuffer> mFrameBuffer;

	glm::vec4 m_Color = { 0.2f, 0.3f, 0.8f, 1.0f };
};