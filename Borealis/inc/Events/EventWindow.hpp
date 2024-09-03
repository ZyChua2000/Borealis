/******************************************************************************/
/*!
\file		EventWindow.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	February 17, 2024
\brief		Declares the functions and class for Window Events

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef EVENT_WINDOW_HPP
#define EVENT_WINDOW_HPP

#include <Core/EventSystem.hpp>

namespace Borealis
{
	/*!***********************************************************************
		\brief
			Class for Window Close Event.
	*************************************************************************/
	class BOREALIS_API EventWindowClose : public Event
	{
	public:

		/*!***********************************************************************
			\brief
				Default Constructor for Window Close Event.
		*************************************************************************/
		EventWindowClose() {};

		SET_EVENT_CATEGORY(EventCategory::EventCategoryWindow);
		SET_EVENT_TYPE(WindowClose);
	}; // End of Class EventWindowClose

	/*!***********************************************************************
		\brief
			Class for Window Resize Event.
	*************************************************************************/
	class BOREALIS_API EventWindowResize : public Event
	{
	public:
		/*!***********************************************************************
			\brief
				Constructor for Window Resize Event.
			\param width
				Width of the window.
			\param height
				Height of the window.
		*************************************************************************/
		EventWindowResize(int width, int height) : mWidth(width), mHeight(height) {}

		/*!***********************************************************************
			\brief
				Get the width of the window.
			\return
				Width of the window.
		*************************************************************************/
		inline int GetWidth() const { return mWidth; }

		/*!***********************************************************************
			\brief
				Get the height of the window.
			\return
				Height of the window.
		*************************************************************************/
		inline int GetHeight() const { return mHeight; }

		/*!***********************************************************************
			\brief
				Convert the Event to a string.
			\return
				String representation of the Event.
		*************************************************************************/
		std::string ToString() const override;

		SET_EVENT_CATEGORY(EventCategory::EventCategoryWindow);
		SET_EVENT_TYPE(WindowResize);
	private:
		int mWidth;
		int mHeight;
	}; // End of Class EventWindowResize

	/*!***********************************************************************
		\brief
			Class for Window Focus Event.
	*************************************************************************/
	class BOREALIS_API EventWindowFocus : public Event
	{
	public:

		/*!***********************************************************************
			\brief
				Default Constructor for Window Focus Event.
		*************************************************************************/
		EventWindowFocus() {};

		SET_EVENT_CATEGORY(EventCategory::EventCategoryWindow);
		SET_EVENT_TYPE(WindowFocus);
	}; // End of Class EventWindowFocus

	/*!***********************************************************************
		\brief
			Class for Window Lost Focus Event.
	*************************************************************************/
	class BOREALIS_API EventWindowLostFocus : public Event
	{
	public:
		/*!***********************************************************************
			\brief
				Default Constructor for Window Lost Focus Event.
		*************************************************************************/
		EventWindowLostFocus() {};

		SET_EVENT_CATEGORY(EventCategory::EventCategoryWindow);
		SET_EVENT_TYPE(WindowLostFocus);
	}; // End of Class EventWindowLostFocus

	/*!***********************************************************************
		\brief
			Class for Window Moved Event.
	*************************************************************************/
	class BOREALIS_API EventWindowMoved : public Event
	{
	public:
		/*!***********************************************************************
			\brief
				Default Constructor for Window Moved Event.
		*************************************************************************/
		EventWindowMoved() {};

		SET_EVENT_CATEGORY(EventCategory::EventCategoryWindow);
		SET_EVENT_TYPE(WindowMoved);
	}; // End of Class EventWindowMoved


} // End of namespace Borealis

#endif