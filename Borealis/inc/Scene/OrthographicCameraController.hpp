/******************************************************************************/
/*!
\file		OrthographicCameraController.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 9, 2024
\brief		Declares the class for Orthographic Camera Controller for 
	 		Level Editor's internal camera

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef ORTHOGRAPHIC_CAMERA_CONTROLLER_HPP
#define ORTHOGRAPHIC_CAMERA_CONTROLLER_HPP
#include <Graphics/OrthographicCamera.hpp>
#include <Events/EventWindow.hpp>
#include <Events/EventInput.hpp>

namespace Borealis
{
	struct OrthographicCameraBounds
	{
		float Left, Right, Bottom, Top;

		float GetWidth() { return Right - Left; }
		float GetHeight() { return Top - Bottom; }
	};
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float width, float height, bool rotation = false);
		OrthographicCameraController(float aspectRatio, bool rotation = false);
		OrthographicCamera& GetCamera() { return mCamera; }
		const OrthographicCamera& GetCamera() const { return mCamera;  }
		void UpdateFn(float dt);
		void EventFn(Event& e);
		void Resize(float width, float height);

		const OrthographicCameraBounds& GetBounds() const { return mBounds; }
		void SetBounds(const OrthographicCameraBounds& bounds) { mBounds = bounds; }

		float GetZoomLevel() const { return mZoom; }
		void SetZoomLevel(float zoom) { mZoom = zoom; }

		float GetAspectRatio() const { return mAspectRatio; }
	private:
		bool OnMouseScrolled(EventMouseScrolled& e);
		bool OnWindowResized(EventWindowResize& e);	

		bool mRotation;
		float mAspectRatio;
		float mZoom;
		OrthographicCameraBounds mBounds;
		OrthographicCamera mCamera;
		

		glm::vec3 mCameraPosition;
		float mCameraRotation;
		float mCameraMoveSpeed;
		float mCameraRotSpeed;
	};
}

#endif