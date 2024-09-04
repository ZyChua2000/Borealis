/******************************************************************************/
/*!
\file		GraphicsContext.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 7, 2024
\brief		Declares the Generic class for Graphics Context

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef GRAPHICS_CONTEXT_HPP
#define GRAPHICS_CONTEXT_HPP
namespace Borealis
{
	class GraphicsContext
	{
	public:

		/*!***********************************************************************
			\brief
				Destructor of the Graphics Context
		*************************************************************************/
		virtual ~GraphicsContext() {};

		/*!***********************************************************************
			\brief
				Initializes the Graphics Context
		*************************************************************************/
		virtual void Init() = 0;

		/*!***********************************************************************
			\brief
				Swap the Buffers
		*************************************************************************/
		virtual void SwapBuffers() = 0;
	}; // class GraphicsContext
} // namespace Borealis
#endif