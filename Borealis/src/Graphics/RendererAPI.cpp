/******************************************************************************/
/*!
\file		RendererAPI.cpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 7, 2024
\brief		Declares the class for Graphics Renderer API

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include <BorealisPCH.hpp>
#include <Graphics/RendererAPI.hpp>

namespace Borealis
{
	RendererAPI::API RendererAPI::sAPI = RendererAPI::API::OpenGL;
}