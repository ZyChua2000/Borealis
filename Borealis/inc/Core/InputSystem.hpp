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
		static bool IsKeyPressed(int key);
		static bool IsMouseButtonPressed(int key);
		static std::pair<float, float> GetMousePos();
		static float GetMouseX();
		static float GetMouseY();
	};

} // End of namespace Borealis

#endif //INPUT_SYSTEM_HPP