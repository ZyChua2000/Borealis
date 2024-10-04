/******************************************************************************/
/*!
\file		ImGuiFontLib.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 14, 2024
\brief		Defines all the enums for level editor fonts

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 *
 /******************************************************************************/

#include <BorealisPCH.hpp>
#include <ImGui/ImGuiFontLib.hpp>

namespace Borealis

{
	std::map <int, const char*> sImGuiFontLib
	{
		{ImGuiFonts::bold, "resources/fonts/OpenSans-Bold.ttf"},
		{ImGuiFonts::regular, "resources/fonts/OpenSans-Regular.ttf"}
	};

	std::map <int, ImVec4> sImGuiDarkColours{};

	std::map <int, ImVec4> sImGuiLightColours{};
}
