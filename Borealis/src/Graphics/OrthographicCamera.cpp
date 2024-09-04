/******************************************************************************/
/*!
\file		OrthographicCamera.cpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 7, 2024
\brief		Implements the class for Orthographic Camera for 
	 		Level Editor's internal camera

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include <BorealisPCH.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Graphics/OrthographicCamera.hpp>

namespace Borealis
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) : mProjectionMatrix(glm::ortho(left,right,bottom,top,-1.0f,1.0f)),
		mRotation(0), mPosition(0), mViewMatrix(glm::identity<glm::mat4>())
	{
		PROFILE_FUNCTION();

		mViewProjectionMatrix = mProjectionMatrix * mViewMatrix;
	}
	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		PROFILE_FUNCTION();

		mProjectionMatrix = (glm::ortho(left, right, bottom, top, -1.0f, 1.0f));
		mViewProjectionMatrix = mProjectionMatrix * mViewMatrix;
	}
	void OrthographicCamera::UpdateViewMatrix()
	{
		PROFILE_FUNCTION();

		mViewMatrix = glm::inverse(
						glm::translate(glm::mat4(1.0f), mPosition) * 
						glm::rotate(glm::mat4(1.0f), glm::radians(mRotation), glm::vec3(0, 0, 1))
						);
		mViewProjectionMatrix = mProjectionMatrix * mViewMatrix;
	}
}	