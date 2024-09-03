/******************************************************************************/
/*!
\file		EditorCamera.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 15, 2024
\brief		Declares the class for Editor Camera

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef EDITOR_CAMERA_HPP
#define EDITOR_CAMERA_HPP
#include <glm/glm.hpp>
#include <Events/EventInput.hpp>
#include <Core/EventSystem.hpp>
#include <Graphics/Camera.hpp>

namespace Borealis
{
	class EditorCamera : public Camera
	{
	public:
		EditorCamera() {};
		EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);

		void UpdateFn(float dt);
		void EventFn(Event& e);

		inline float GetDistance() const { return mDistance; }
		inline void SetDistance(float distance) { mDistance = distance; }

		inline void SetViewportSize(float width, float height) { mViewportWidth = width; mViewportHeight = height; UpdateProjection(); }

		const glm::mat4& GetViewMatrix() const { return mViewMatrix; }
		glm::mat4 GetViewProjectionMatrix() const { return mProjectionMatrix * mViewMatrix; }

		glm::vec3 GetUpDirection() const;
		glm::vec3 GetRightDirection() const;
		glm::vec3 GetForwardDirection() const;
		const glm::vec3& GetPosition() const { return mPosition; }
		glm::quat GetOrientation() const;

		float GetPitch() const { return mPitch; }
		float GetYaw() const { return mYaw; }

	private:
		void UpdateProjection();
		void UpdateView();

		bool OnMouseScroll(EventMouseScrolled& e);

		void MousePan(const glm::vec2& delta);
		void MouseRotate(const glm::vec2& delta);
		void MouseZoom(float delta);

		glm::vec3 CalculatePosition() const;

		std::pair<float, float> PanSpeed() const;
		float RotationSpeed() const;
		float ZoomSpeed() const;

		glm::mat4 mViewMatrix;
		glm::vec3 mPosition = { 0.0f, 0.0f, 0.0f };
		glm::vec3 mFocalPoint = { 0.0f, 0.0f, 0.0f };
		glm::vec2 mInitialMousePosition = { 0.0f, 0.0f };

		float mFOV = 45.0f;
		float mAspectRatio = 1.778f;
		float mNearClip = 0.1f;
		float mFarClip = 1000.0f;
		float mDistance = 10.0f;
		float mPitch = 0.0f;
		float mYaw = 0.0f;
		float mViewportWidth = 1920;
		float mViewportHeight = 1080;
	};
}

#endif