/******************************************************************************/
/*!
\file		SceneCamera.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 13, 2024
\brief		Declares the class for Scene Camera editor interface

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef SCENE_CAMERA_HPP
#define SCENE_CAMERA_HPP
#include <Graphics/Camera.hpp>
namespace Borealis
{
	class SceneCamera : public Camera
	{
	public:
		enum class CameraType
		{
			Perspective = 0,
			Orthographic = 1
		};
		SceneCamera();
		~SceneCamera() = default;

		void SetOrtho(float size, float nearClip, float farClip);
		void SetPers(float fov, float nearClip, float farClip);
		void SetViewportSize(uint32_t width, uint32_t height);

		float GetOrthoSize() const { return mOrthoSize; }
		void SetOrthoSize(float size) { mOrthoSize = size; RecalculateProjection(); }
		float GetOrthoNear() const { return mOrthoNear; }
		void SetOrthoNear(float nearClip) { mOrthoNear = nearClip; RecalculateProjection(); }
		float GetOrthoFar() const { return mOrthoFar; }
		void SetOrthoFar(float farClip) { mOrthoFar = farClip; RecalculateProjection(); }


		float GetPerspFOV() const { return mPerspFOV; }
		void SetPerspFOV(float fov) { mPerspFOV = fov; RecalculateProjection(); }
		float GetPerspNear() const { return mPerspNear; }
		void SetPerspNear(float nearClip) { mPerspNear = nearClip; RecalculateProjection(); }
		float GetPerspFar() const { return mPerspFar; }
		void SetPerspFar(float farClip) { mPerspFar = farClip; RecalculateProjection(); }


		CameraType GetCameraType() const { return mCameraType; }
		void SetCameraType(CameraType type) { mCameraType = type; RecalculateProjection(); }

	private:
		void RecalculateProjection();

		CameraType mCameraType = CameraType::Orthographic;
		float mOrthoSize = 1000.0f;
		float mOrthoNear = -1.0f;
		float mOrthoFar = 1000.0f;

		float mPerspFOV = glm::radians(45.0f);
		float mPerspNear = 1.f;
		float mPerspFar = 1000.0f;

		float mAspectRatio = 1.78f;
	};
}

#endif