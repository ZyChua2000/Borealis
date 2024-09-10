/******************************************************************************/
/*!
\file		Behaviour.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	September 07, 2024
\brief		Declares the class for Behaviour Scripts

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef BEHAVIOUR_HPP
#define BEHAVIOUR_HPP
#include <Scripting/Component.hpp>

namespace Borealis {
	class Behaviour : public Component
	{
	public:
		bool enabled;
		bool isActiveAndEnabled;
	};
}
#endif