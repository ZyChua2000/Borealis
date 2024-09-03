/******************************************************************************/
/*!
\file		RenderCommand.cpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 7, 2024
\brief		Implements the wrapper class for Graphics Render Commmand

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include <BorealisPCH.hpp>
#include <Graphics/RenderCommand.hpp>
#include <Graphics/RendererAPI.hpp>
#include <Graphics/OpenGL/RendererAPIOpenGLImpl.hpp>


namespace Borealis
{
	std::unique_ptr<RendererAPI> RenderCommand::sRendererAPI = std::make_unique<OpenGLRendererAPI>();
}