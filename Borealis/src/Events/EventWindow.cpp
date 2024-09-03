/******************************************************************************/
/*!
\file		EventWindow.cpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	February 17, 2024
\brief		Defines the functions and class for Window Events

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "BorealisPCH.hpp"
#include <Events/EventWindow.hpp>


namespace Borealis
{
	/*!***********************************************************************
		\brief
			Converts the Event Window Close to a string representation.
		\return
			Returns the string representation of the Event Window Resize.
	*************************************************************************/
	std::string EventWindowResize::ToString() const
	{
		std::stringstream ss;
		ss << "WindowResizeEvent: " << mWidth << ", " << mHeight;
		return ss.str();
	}
} // End of namespace Borealis