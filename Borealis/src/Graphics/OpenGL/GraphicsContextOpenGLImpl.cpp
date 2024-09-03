/******************************************************************************/
/*!
\file		GraphicsContextOpenGLImpl.cpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 7, 2024
\brief		Implements the OpenGl class for Graphics Context

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "BorealisPCH.hpp"
#include "Graphics/OpenGL/GraphicsContextOpenGLImpl.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <Core/LoggerSystem.hpp>
namespace Borealis
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : mWindowHandle(windowHandle)
	{
		if (!mWindowHandle)
		{
			BOREALIS_CORE_CRITICAL("Failed to create GLFW window!");
			glfwTerminate();
			return;
		}
	}
	void OpenGLContext::Init()
	{
		PROFILE_FUNCTION();

		glfwMakeContextCurrent(mWindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		if (status == 0)
		{
			BOREALIS_CORE_CRITICAL("Failed to initialize GLAD!");
			glfwTerminate();
			return;
		}

		BOREALIS_CORE_INFO("OpenGL Info:");
		BOREALIS_CORE_INFO("  Vendor: {}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
		BOREALIS_CORE_INFO("  Renderer: {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
		BOREALIS_CORE_INFO("  Version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
	}
	void OpenGLContext::SwapBuffers()
	{
		PROFILE_FUNCTION();
		glfwSwapBuffers(mWindowHandle);
	}
}