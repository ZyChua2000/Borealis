/******************************************************************************/
/*!
\file		InputSystem.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	February 19, 2024
\brief		Declares the InputSystem Class to manage input handles

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 *
 /******************************************************************************/

#ifndef INPUT_SYSTEM_HPP
#define INPUT_SYSTEM_HPP
#include <Core/Core.hpp>
#include <utility>
namespace Borealis
{
	class BOREALIS_API InputSystem
	{
	public:
		/*!***********************************************************************
			\brief
				Checks if a key is pressed
			\param key
				Keycode of the key
			\return
				True if pressed, false if not
		*************************************************************************/
		static bool IsKeyPressed(int key);

		/*!***********************************************************************
			\brief
				Checks if a mouse button is pressed
			\param key
				Keycode of the mouse button
			\return
				True if pressed, false if not
		*************************************************************************/
		static bool IsMouseButtonPressed(int key);

		/*!***********************************************************************
			\brief
				Get the current mouse position
			\return
				Pair of x and y floats of the mouse position
		*************************************************************************/
		static std::pair<float, float> GetMousePos();

		/*!***********************************************************************
			\brief
				Get the current mouse x position
			\return
				y position of the mouse
		*************************************************************************/
		static float GetMouseX();

		/*!***********************************************************************
			\brief
				Get the current mouse y position
			\return
				y position of the mouse
		*************************************************************************/
		static float GetMouseY();
	};

} // End of namespace Borealis

#endif //INPUT_SYSTEM_HPP