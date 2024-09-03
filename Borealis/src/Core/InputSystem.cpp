/******************************************************************************/
/*!
\file		InputSystem.cpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	February 19, 2024
\brief		Defines the InputSystem Class to manage input handles

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 *
 /******************************************************************************/

#include "BorealisPCH.hpp"
#include "Core/InputSystem.hpp"
#include <GLFW/glfw3.h>
#include <Core/ApplicationManager.hpp>

namespace Borealis
{

	bool InputSystem::IsKeyPressed(int key)
	{
		auto state = glfwGetKey(static_cast<GLFWwindow*>(ApplicationManager::Get().GetWindow()->GetNativeWindow()), key);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool InputSystem::IsMouseButtonPressed(int key)
	{
		auto state = glfwGetMouseButton(static_cast<GLFWwindow*>(ApplicationManager::Get().GetWindow()->GetNativeWindow()), key);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> InputSystem::GetMousePos()
	{
		double x, y;
		glfwGetCursorPos(static_cast<GLFWwindow*>(ApplicationManager::Get().GetWindow()->GetNativeWindow()), &x, &y);
		return { static_cast<float>(x), static_cast<float>(y) };
	}

	float InputSystem::GetMouseX()
	{
		auto [x,y] = GetMousePos();
		return x;
	}
	float InputSystem::GetMouseY()
	{
		auto [x, y] = GetMousePos();
		return y;
	}
} // End of namespace Borealis
