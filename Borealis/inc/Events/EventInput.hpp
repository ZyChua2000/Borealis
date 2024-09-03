/******************************************************************************/
/*!
\file		EventInput.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	February 17, 2024
\brief		Declares the functions and class for Input Events

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef EVENT_INPUT_HPP
#define EVENT_INPUT_HPP

#include <Core/EventSystem.hpp>

namespace Borealis
{
	/*!***********************************************************************
		\brief
			This is a base class for all key events. It contains the keycode.
	*************************************************************************/
	class BOREALIS_API EventKey : public Event
	{
	public:

		/*!***********************************************************************
			\brief
				Getter for the KeyCode.
			\return
				Returns the keycode of the key event.
		*************************************************************************/
		inline unsigned GetKeyCode() const { return mKeyCode; }

		SET_EVENT_CATEGORY(EventCategory::EventCategoryKeyboard | EventCategory::EventCategoryInput);
	protected:

		/*!***********************************************************************
			\brief
				Constructor of the Key Event.
			\param[in] keycode
				The keycode of the key event.
		*************************************************************************/
		EventKey(int keycode) : mKeyCode(keycode) {}
		unsigned mKeyCode;
	}; // End of class EventKey

	/*!***********************************************************************
		\brief
			This is a derived class for Key Pressed Event, inheriting Key Event.
	*************************************************************************/
	class BOREALIS_API EventKeyPressed : public EventKey
	{
	public:
		/*!***********************************************************************
			\brief
				Constructor of the Key Pressed Event.
			\param[in] keycode
				The keycode of the key event.
		*************************************************************************/
		EventKeyPressed(int keycode) : EventKey(keycode) {}

		/*!***********************************************************************
			\brief
				Converts the Key Pressed Event to a string.
			\return
				Returns the string representation of the Key Pressed Event.
		*************************************************************************/
		std::string ToString() const override;

		SET_EVENT_TYPE(KeyPressed);
	}; // End of class EventKeyPressed

	/*!***********************************************************************
		\brief
			This is a derived class for Key Released Event, inheriting Key Event.
	*************************************************************************/
	class BOREALIS_API EventKeyReleased : public EventKey
	{

	public:
		/*!***********************************************************************
			\brief
				Constructor of the Key Released Event.
			\param[in] keycode
				The keycode of the key event.
		*************************************************************************/
		EventKeyReleased(int keycode) : EventKey(keycode) {}

		/*!***********************************************************************
			\brief
				Converts the Key Released Event to a string.
			\return
				Returns the string representation of the Key Released Event.
		*************************************************************************/
		std::string ToString() const override;

		SET_EVENT_TYPE(KeyReleased);
	}; // End of class EventKeyReleased
	  
	/*!***********************************************************************
		\brief
			This is a derived class for Key Triggered Event, inheriting Key Event.
	*************************************************************************/
	class BOREALIS_API EventKeyTriggered : public EventKey
	{
	public:
		/*!***********************************************************************
			\brief
				Constructor of the Key Triggered Event.
			\param[in] keycode
				The keycode of the key event.
		*************************************************************************/
		EventKeyTriggered(int keycode) : EventKey(keycode) {}

		/*!***********************************************************************
			\brief
				Converts the Key Triggered Event to a string.
			\return
				Returns the string representation of the Key Triggered Event.
		*************************************************************************/
		std::string ToString() const override;
		SET_EVENT_TYPE(KeyTriggered);
	}; // End of class EventKeyTriggered

	/*!***********************************************************************
		\brief
			This is a derived class for Key Typed Event, inheriting Key Event.
	*************************************************************************/
	class BOREALIS_API EventKeyTyped : public EventKey
	{
	public:
		/*!***********************************************************************
			\brief
				Constructor of the Key Triggered Event.
			\param[in] keycode
				The keycode of the key event.
		*************************************************************************/
		EventKeyTyped(int keycode) : EventKey(keycode) {}

		/*!***********************************************************************
			\brief
				Converts the Key Triggered Event to a string.
			\return
				Returns the string representation of the Key Triggered Event.
		*************************************************************************/
		std::string ToString() const override;
		SET_EVENT_TYPE(KeyTyped);
	}; // End of class EventKeyTriggered


	/*!***********************************************************************
		\brief
			This is a derived class for Mouse Moved Event.
	*************************************************************************/
	class BOREALIS_API EventMouseMoved : public Event
	{
	public:

		/*!***********************************************************************
			\brief
				Constructor for Mouse Moved Event
			\param[in] x
				The x position of the mouse.
			\param[in] y
				The y position of the mouse.
		*************************************************************************/
		EventMouseMoved(double x, double y) : mMouseX(x), mMouseY(y) {}

		/*!***********************************************************************
			\brief
				Getter for the x position of the mouse.
			\return
				Returns the x position of the mouse.
		*************************************************************************/
		inline double GetX() const { return mMouseX; }

		/*!***********************************************************************
			\brief
				Getter for the y position of the mouse.
			\return
				Returns the y position of the mouse.
		*************************************************************************/
		inline double GetY() const { return mMouseY; }

		/*!***********************************************************************
			\brief
				Converts the Mouse Moved Event to a string.
			\return
				Returns the string representation of the Mouse Moved Event.
		*************************************************************************/
		std::string ToString() const override;

		SET_EVENT_TYPE(MouseMoved);
		SET_EVENT_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput);
	private:
		double mMouseX;
		double mMouseY;
	}; // End of class EventMouseMoved

	/*!***********************************************************************
		\brief
			This is a derived class for Mouse Scrolled Event.
	*************************************************************************/
	class BOREALIS_API EventMouseScrolled : public Event
	{
	public:

		/*!***********************************************************************
			\brief
				Constructor for Mouse Scrolled Event
			\param[in] xOffset
				The x offset of the mouse scroll.
			\param[in] yOffset
				The y offset of the mouse scroll.
		*************************************************************************/
		EventMouseScrolled(double xOffset, double yOffset) : mXOffset(xOffset), mYOffset(yOffset) {}

		/*!***********************************************************************
			\brief
				Getter for the x offset of the mouse scroll.
			\return
				Returns the x offset of the mouse scroll.
		*************************************************************************/
		inline double GetXOffset() const { return mXOffset; }

		/*!***********************************************************************
			\brief
				Getter for the y offset of the mouse scroll.
			\return
				Returns the y offset of the mouse scroll.
		*************************************************************************/
		inline double GetYOffset() const { return mYOffset; }

		/*!***********************************************************************
			\brief
				Converts the Mouse Scrolled Event to a string.
			\return
				Returns the string representation of the Mouse Scrolled Event.
		*************************************************************************/
		std::string ToString() const override;

		SET_EVENT_TYPE(MouseScrolled);
		SET_EVENT_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput);
	private:
		double mXOffset;
		double mYOffset;
	}; // End of class EventMouseScrolled

	/*!***********************************************************************
		\brief
			This is a base class for all mouse button events. It contains the
			button code.
	*************************************************************************/
	class BOREALIS_API EventMouseButton : public Event
	{
	public:
		/*!***********************************************************************
			\brief
				Getter for the MouseButton.
			\return
				Returns the button code of the mouse button event.
		*************************************************************************/
		inline unsigned GetMouseButton() const { return mButton; }

		SET_EVENT_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput);
	protected:

		/*!***********************************************************************
			\brief
				Constructor for the Mouse Button Event.
			\param[in] button
				The button code of the mouse button event.
		*************************************************************************/
		EventMouseButton(int button) : mButton(button) {}

		unsigned mButton;
	}; // End of class EventMouseButton

	
	/*!***********************************************************************
		\brief
			This is a derived class for mouse button released event. It inherits
			from EventMouseButton.
	*************************************************************************/
	class BOREALIS_API EventMouseButtonReleased : public EventMouseButton
	{
	public:
		/*!***********************************************************************
			\brief
				Constructor for the Mouse Button Released Event.
			\param[in] button
				The button code of the mouse button event.
		*************************************************************************/
		EventMouseButtonReleased(int button) : EventMouseButton(button) {}

		/*!***********************************************************************
			\brief
				Converts the Mouse Button Released Event to a string.
			\return
				Returns the string representation of the Mouse Button Released Event.
		*************************************************************************/
		std::string ToString() const override;
		SET_EVENT_TYPE(MouseReleased);
	}; // End of class EventMouseButtonReleased

	/*!***********************************************************************
		\brief
			This is a derived class for mouse button triggered event. It inherits
			from EventMouseButton.
	*************************************************************************/
	class BOREALIS_API EventMouseButtonTriggered : public EventMouseButton
	{
	public:
		/*!***********************************************************************
			\brief
				Constructor for the Mouse Button Triggered Event.
			\param[in] button
				The button code of the mouse button event.
		*************************************************************************/
		EventMouseButtonTriggered(int button) : EventMouseButton(button) {}

		/*!***********************************************************************
			\brief
				Converts the Mouse Button Triggered Event to a string.
			\return
				Returns the string representation of the Mouse Button Triggered Event.
		*************************************************************************/
		std::string ToString() const override;
		SET_EVENT_TYPE(MouseTriggered);
	}; // End of class EventMouseButtonTriggered

	/*!***********************************************************************
		\brief
			This is a derived class for mouse button Pressed event. It inherits
			from EventMouseButton.
	*************************************************************************/
	class BOREALIS_API EventMouseButtonPressed : public EventMouseButton
	{
	public:
		/*!***********************************************************************
			\brief
				Constructor for the Mouse Button Triggered Event.
			\param[in] button
				The button code of the mouse button event.
		*************************************************************************/
		EventMouseButtonPressed(int button) : EventMouseButton(button) {}

		/*!***********************************************************************
			\brief
				Converts the Mouse Button Pressed Event to a string.
			\return
				Returns the string representation of the Mouse Button Triggered Event.
		*************************************************************************/
		std::string ToString() const override;
		SET_EVENT_TYPE(MousePressed);
	}; // End of class EventMouseButtonTriggered

} // End of namespace Borealis

#endif