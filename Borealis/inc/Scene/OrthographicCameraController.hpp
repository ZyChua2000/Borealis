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
		float Left, Right, Bottom, Top; // Bounds of the camera
		/*!***********************************************************************
			\brief
				Get the width of the camera bounds
			\return
				Width of the camera bounds
		*************************************************************************/
		float GetWidth() { return Right - Left; } 

		/*!***********************************************************************
			\brief
				Get the height of the camera bounds
			\return
				Height of the camera bounds
		*************************************************************************/
		float GetHeight() { return Top - Bottom; }
	};
	class OrthographicCameraController
	{
	public:

		/*!***********************************************************************
			\brief
				Constructor for Orthographic Camera Controller
			\param[in] width
				Width of the camera
			\param[in] height
				Height of the camera
			\param[in] rotation
				Whether the camera can rotate
		*************************************************************************/
		OrthographicCameraController(float width, float height, bool rotation = false); 

		/*!***********************************************************************
			\brief
				Constructor for Orthographic Camera Controller
			\param[in] aspectRatio
				Aspect ratio of the camera
			\param[in] rotation
				Whether the camera can rotate
		*************************************************************************/
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		/*!***********************************************************************
			\brief
				Get the camera
			\return
				Orthographic Camera
		*************************************************************************/
		OrthographicCamera& GetCamera() { return mCamera; }

		/*!***********************************************************************
			\brief
				Get the camera
			\return
				Orthographic Camera
		*************************************************************************/
		const OrthographicCamera& GetCamera() const { return mCamera;  }

		/*!***********************************************************************
			\brief
				Update function for the camera controller
			\param[in] dt
				Delta time
		*************************************************************************/
		void UpdateFn(float dt);

		/*!***********************************************************************
			\brief
				Event function for the camera controller
			\param[in] e
				Event
		*************************************************************************/
		void EventFn(Event& e);

		/*!***********************************************************************
			\brief
				Resize the camera
			\param[in] width
				Width of the camera
			\param[in] height
				Height of the camera
		*************************************************************************/
		void Resize(float width, float height);

		/*!***********************************************************************
			\brief
				Get the bounds of the camera
			\return
				Orthographic Camera Bounds
		*************************************************************************/
		const OrthographicCameraBounds& GetBounds() const { return mBounds; }

		/*!***********************************************************************
			\brief
				Set the bounds of the camera
			\param[in] bounds
				Orthographic Camera Bounds
		*************************************************************************/
		void SetBounds(const OrthographicCameraBounds& bounds) { mBounds = bounds; }

		/*!***********************************************************************
			\brief
				Get the Zoom level of the camera
			\return
				Zoom level of the camera
		*************************************************************************/
		float GetZoomLevel() const { return mZoom; }

		/*!***********************************************************************
			\brief
				Set the Zoom level of the camera
			\param[in] zoom
				Zoom level of the camera
		*************************************************************************/
		void SetZoomLevel(float zoom) { mZoom = zoom; }

		/*!***********************************************************************
			\brief
				Get the aspect ratio of the camera
			\return
				Aspect ratio of the camera
		*************************************************************************/
		float GetAspectRatio() const { return mAspectRatio; }
	private:

		/*!***********************************************************************
			\brief
				Mouse Scrolled Event
			\param[in] e
				Mouse Scrolled Event
		*************************************************************************/
		bool OnMouseScrolled(EventMouseScrolled& e);

		/*!***********************************************************************
			\brief
				Window Resized Event
			\param[in] e
				Window Resized Event
		*************************************************************************/
		bool OnWindowResized(EventWindowResize& e);	

		bool mRotation; // Whether the camera can rotate
		float mAspectRatio; // Aspect ratio of the camera
		float mZoom; // Zoom level of the camera
		OrthographicCameraBounds mBounds; // Bounds of the camera
		OrthographicCamera mCamera; // Camera
		

		glm::vec3 mCameraPosition; // Position of the camera
		float mCameraRotation; // Rotation of the camera
		float mCameraMoveSpeed; // Speed of the camera
		float mCameraRotSpeed; // Rotation speed of the camera
	};
}

#endif