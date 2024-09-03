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
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetPosition(const glm::vec3& position) { mPosition = position; UpdateViewMatrix (); }
		void SetRotation(float rotation) { mRotation = rotation; UpdateViewMatrix(); }

		const glm::vec3& GetPosition() const { return mPosition;}
		const float& GetRotation() const { return mRotation;}

		void SetProjection(float left, float right, float bottom, float top);

		const glm::mat4& GetProjectionMatrix() const { return mProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return mViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return mViewProjectionMatrix; }

	private:
		void UpdateViewMatrix();
		glm::mat4 mProjectionMatrix;
		glm::mat4 mViewMatrix;
		glm::mat4 mViewProjectionMatrix;
		glm::vec3 mPosition;
		float mRotation;
	};
}

#endif