/******************************************************************************/
/*!
\file		EventSystem.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	February 16, 2024
\brief		Declares the functions for Event System of the Borealis

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef EVENT_SYSTEM_HPP
#define EVENT_SYSTEM_HPP

#include <BorealisPCH.hpp>
#include <Core/Core.hpp>

namespace Borealis {

	/*!***********************************************************************
		\brief
			Enum Class that defines the different types of events that can be
			triggered in the engine
	*************************************************************************/
	enum class EventType
	{
		None = 0,
		// Window Events
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		// Key Events
		KeyPressed, KeyReleased, KeyTriggered, KeyTyped,
		// Mouse Events
		MouseReleased, MouseTriggered, MouseMoved, MouseScrolled, MousePressed
	}; // End of enum class EventType

	/*!***********************************************************************
		\brief
			Enum that defines the different categories of events that
			can be triggered in the engine
	*************************************************************************/
	enum EventCategory
	{
		None = 0,
		EventCategoryWindow			= (1 << 0),
		EventCategoryInput			= (1 << 1),
		EventCategoryKeyboard		= (1 << 2),
		EventCategoryMouse			= (1 << 3),
		EventCategoryMouseButton	= (1 << 4)
	}; // End of enum EventCategory

	/*!***********************************************************************
		\brief
			Macro that defines the functions that are required for an event
			to be used in the engine
	*************************************************************************/
	#define SET_EVENT_TYPE(type)			static EventType GetStaticType() { return EventType::##type; }\
											virtual EventType GetEventType() const override { return GetStaticType(); }\
											virtual const char* GetName() const override { return #type; }
	#define SET_EVENT_CATEGORY(category)	virtual int GetCategoryFlags() const override { return category; }

	/*!***********************************************************************
		\brief
			Base class for all events in the engine
	*************************************************************************/
	class BOREALIS_API Event
	{
		friend class EventDispatcher;
	public:
		/*!***********************************************************************
			\brief
				Pure virtual functions that must be implemented by all events
		*************************************************************************/
		bool isDoneHandling = false;

		virtual EventType GetEventType() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual const char* GetName() const = 0;

		/*!***********************************************************************
			\brief
				Function that returns the name of the event
			\return
				The name of the event
		*************************************************************************/
		virtual std::string ToString() const { return GetName(); }

		/*!***********************************************************************
			\brief
				Checks if an event is in a specific category
			\param[in] category
				The category to check if the event is in
			\return
				True if the event is in the category, false otherwise
		*************************************************************************/
		inline bool IsInCategory(EventCategory category) const { return GetCategoryFlags() & category;}
		
	}; // End of class Event

	/*!***********************************************************************
		\brief
			Class that defiens the event dispatcher for events. The dispatcher
			is used to dispatch events to the correct functions
	*************************************************************************/
	class EventDispatcher
	{
		template <typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		/*!***********************************************************************
			\brief
				Constructor for the event dispatcher
			\param[in] event
				The event to dispatch
		*************************************************************************/
		EventDispatcher(Event& event) : mEvent(event) {}

		/*!***********************************************************************
			\brief
				Dispatches the event to the correct function
			\param[in] func
				The function to dispatch the event to
			\return
				True if the event was dispatched, false otherwise
		*************************************************************************/
		template <typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (mEvent.GetEventType() == T::GetStaticType())
			{
				mEvent.isDoneHandling = func(*(T*)&mEvent);
				return true;
			}
			return false;
		}

	private:
		Event& mEvent;
	}; // End of class EventDispatcher

	/*!***********************************************************************
		\brief
			Overloaded operator for the << operator for events
	*************************************************************************/
	inline std::ostream& operator<<(std::ostream& os, const Event& e) { return os << e.ToString();}
} // End of namespace Borealis

#endif