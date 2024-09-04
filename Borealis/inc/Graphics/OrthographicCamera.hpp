/******************************************************************************/
/*!
\file		OrthographicCamera.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 7, 2024
\brief		Declares the class for Orthographic Camera for 
	 		Level Editor's internal camera

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef ORTHOGRAPHIC_CAMERA_HPP
#define ORTHOGRAPHIC_CAMERA_HPP
#include <glm/glm.hpp>

namespace Borealis
{
	class OrthographicCamera
	{
	public:

		/*!***********************************************************************
			\brief
				Constructor for Orthographic Camera
			\param left
				Left bound of the camera
			\param right
				Right bound of the camera
			\param bottom
				Bottom bound of the camera
			\param top
				Top bound of the camera
		*************************************************************************/
		OrthographicCamera(float left, float right, float bottom, float top);

		/*!***********************************************************************
			\brief
				Set the position of the camera
			\param position
				Position to set the camera to
		*************************************************************************/
		void SetPosition(const glm::vec3& position) { mPosition = position; UpdateViewMatrix (); }

		/*!***********************************************************************
			\brief
				Set the rotation of the camera
			\param rotation
				Rotation to set the camera to
		*************************************************************************/
		void SetRotation(float rotation) { mRotation = rotation; UpdateViewMatrix(); }
		
		/*!***********************************************************************
			\brief
				Get the position of the camera
			\return
				Position of the camera
		*************************************************************************/
		const glm::vec3& GetPosition() const { return mPosition;}

		/*!***********************************************************************
			\brief
				Get the rotation of the camera
			\return
				Rotation of the camera
		*************************************************************************/
		const float& GetRotation() const { return mRotation;}

		/*!***********************************************************************
			\brief
				Set the projection of the camera
			\param left
				Left bound of the camera
			\param right
				Right bound of the camera
			\param bottom
				Bottom bound of the camera
			\param top
				Top bound of the camera
		*************************************************************************/
		void SetProjection(float left, float right, float bottom, float top);

		/*!***********************************************************************
			\brief
				Get the projection matrix of the camera
			\return
				Projection matrix of the camera
		*************************************************************************/
		const glm::mat4& GetProjectionMatrix() const { return mProjectionMatrix; }

		/*!***********************************************************************
			\brief
				Get the view matrix of the camera
			\return
				View matrix of the camera
		*************************************************************************/
		const glm::mat4& GetViewMatrix() const { return mViewMatrix; }

		/*!***********************************************************************
			\brief
				Get the view projection matrix of the camera
			\return
				View projection matrix of the camera
		*************************************************************************/
		const glm::mat4& GetViewProjectionMatrix() const { return mViewProjectionMatrix; }

	private:
		/*!***********************************************************************
			\brief
				Update the view matrix of the camera
		*************************************************************************/
		void UpdateViewMatrix();
		glm::mat4 mProjectionMatrix; // Orthographic Projection Matrix
		glm::mat4 mViewMatrix; // View Matrix
		glm::mat4 mViewProjectionMatrix; // View Projection Matrix
		glm::vec3 mPosition; // Position of the camera
		float mRotation; // Rotation of the camera
	};
}

#endif