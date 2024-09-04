/******************************************************************************/
/*!
\file		EventInput.cpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	February 17, 2024
\brief		Defines the functions and class for Input Events

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include <BorealisPCH.hpp>
#include <Events/EventInput.hpp>

namespace Borealis {

	/*!***********************************************************************
		\brief
			Converts the Key Pressed Event to a string.
		\return
			Returns the string representation of the Key Pressed Event.
	*************************************************************************/
	std::string EventKeyPressed::ToString() const
	{
		std::stringstream ss;
		ss << "EventKeyPressed: " << mKeyCode;
		return ss.str();
	}

	/*!***********************************************************************
		\brief
			Converts the Key Released Event to a string.
		\return
			Returns the string representation of the Key Released Event.
	*************************************************************************/
	std::string EventKeyReleased::ToString() const
	{
		std::stringstream ss;
		ss << "EventKeyReleased: " << mKeyCode;
		return ss.str();
	}

	/*!***********************************************************************
		\brief
			Converts the Key Triggered Event to a string.
		\return
			Returns the string representation of the Key Triggered Event.
	*************************************************************************/
	std::string EventKeyTriggered::ToString() const
	{
		std::stringstream ss;
		ss << "EventKeyTriggered: " << mKeyCode;
		return ss.str();
	}

	/*!***********************************************************************
		\brief
			Converts the Mouse Moved Event to a string.
		\return
			Returns the string representation of the Mouse Moved Event.
	*************************************************************************/
	std::string EventMouseMoved::ToString() const
	{
		std::stringstream ss;
		ss << "EventMouseMoved: " << mMouseX << ", " << mMouseY;
		return ss.str();
	}

	/*!***********************************************************************
		\brief
			Converts the Mouse Scrolled Event to a string.
		\return
			Returns the string representation of the Mouse Scrolled Event.
	*************************************************************************/
	std::string EventMouseScrolled::ToString() const
	{
		std::stringstream ss;
		ss << "EventMouseScrolled: " << mXOffset << ", " << mYOffset;
		return ss.str();
	}

	/*!***********************************************************************
		\brief
			Converts the MouseButton Released Event to a string.
		\return
			Returns the string representation of the MouseButton Released Event.
	*************************************************************************/
	std::string EventMouseButtonReleased::ToString() const
	{
		std::stringstream ss;
		ss << "EventMouseButtonReleased: " << mButton;
		return ss.str();
	}

	/*!***********************************************************************
		\brief
			Converts the MouseButton Triggered Event to a string.
		\return
			Returns the string representation of the MouseButton Triggered Event.
	*************************************************************************/
	std::string EventMouseButtonTriggered::ToString() const
	{
		std::stringstream ss;
		ss << "EventMouseButtonTriggered: " << mButton;
		return ss.str();
	}

	/*!***********************************************************************
		\brief
			Converts the MouseButton Typed Event to a string.
		\return
			Returns the string representation of the MouseButton Triggered Event.
	*************************************************************************/
	std::string EventKeyTyped::ToString() const
	{
		std::stringstream ss;
		ss << "EventKeyTyped: " << mKeyCode;
		return ss.str();
	}

	/*!***********************************************************************
		\brief
			Converts the MouseButton Pressed Event to a string.
		\return
			Returns the string representation of the MouseButton Triggered Event.
	*************************************************************************/
	std::string EventMouseButtonPressed::ToString() const
	{
		std::stringstream ss;
		ss << "EventMouseButtonPressed: " << mButton;
		return ss.str();
	}

} // End of namespace Borealis