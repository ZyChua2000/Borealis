/******************************************************************************/
/*!
\file		Camera.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 7, 2024
\brief		Declares the class for Camera

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <glm/glm.hpp>

namespace Borealis
{
	class Camera
	{
	public:
		Camera() : mProjectionMatrix(glm::mat4(1.0f)) {};
		Camera(glm::mat4 projection) : mProjectionMatrix(projection) {};
		virtual ~Camera() = default;

		void SetProjectionMatrix(const glm::mat4& projectionMatrix) { mProjectionMatrix = projectionMatrix; };
		const glm::mat4& GetProjectionMatrix() const { return mProjectionMatrix; };
	protected:
		glm::mat4 mProjectionMatrix;
	};
}

#endif