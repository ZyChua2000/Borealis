/******************************************************************************/
/*!
\file		ImGuiFontLib.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 14, 2024
\brief		Declares all the enums for level editor fonts

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 *
 /******************************************************************************/

#ifndef IMGUI_FONT_LIB_HPP
#define IMGUI_FONT_LIB_HPP
#include <map>
#include <imgui.h>
namespace Borealis
{
    class ImGuiFonts {
    public:
        enum Value {
            bold,
            regular,
        };

        ImGuiFonts(Value v) : value(v) {}

        // Implicit conversion to int
        operator int() const { return value; }

    private:
        Value value;
    };

	extern std::map <int, const char*> sImGuiFontLib;

    class ImGuiColours {
    public:
        enum Value {
            ImGuiCol_Text,
            ImGuiCol_TextDisabled,
            ImGuiCol_WindowBg,              // Background of normal windows
            ImGuiCol_ChildBg,               // Background of child windows
            ImGuiCol_PopupBg,               // Background of popups, menus, tooltips windows
            ImGuiCol_Border,
            ImGuiCol_BorderShadow,
            ImGuiCol_FrameBg,               // Background of checkbox, radio button, plot, slider, text input
            ImGuiCol_FrameBgHovered,
            ImGuiCol_FrameBgActive,
            ImGuiCol_TitleBg,               // Title bar
            ImGuiCol_TitleBgActive,         // Title bar when focused
            ImGuiCol_TitleBgCollapsed,      // Title bar when collapsed
            ImGuiCol_MenuBarBg,
            ImGuiCol_ScrollbarBg,
            ImGuiCol_ScrollbarGrab,
            ImGuiCol_ScrollbarGrabHovered,
            ImGuiCol_ScrollbarGrabActive,
            ImGuiCol_CheckMark,             // Checkbox tick and RadioButton circle
            ImGuiCol_SliderGrab,
            ImGuiCol_SliderGrabActive,
            ImGuiCol_Button,
            ImGuiCol_ButtonHovered,
            ImGuiCol_ButtonActive,
            ImGuiCol_Header,                // Header* colors are used for CollapsingHeader, TreeNode, Selectable, MenuItem
            ImGuiCol_HeaderHovered,
            ImGuiCol_HeaderActive,
            ImGuiCol_Separator,
            ImGuiCol_SeparatorHovered,
            ImGuiCol_SeparatorActive,
            ImGuiCol_ResizeGrip,            // Resize grip in lower-right and lower-left corners of windows.
            ImGuiCol_ResizeGripHovered,
            ImGuiCol_ResizeGripActive,
            ImGuiCol_TabHovered,            // Tab background, when hovered
            ImGuiCol_Tab,                   // Tab background, when tab-bar is focused & tab is unselected
            ImGuiCol_TabSelected,           // Tab background, when tab-bar is focused & tab is selected
            ImGuiCol_TabSelectedOverline,   // Tab horizontal overline, when tab-bar is focused & tab is selected
            ImGuiCol_TabDimmed,             // Tab background, when tab-bar is unfocused & tab is unselected
            ImGuiCol_TabDimmedSelected,     // Tab background, when tab-bar is unfocused & tab is selected
            ImGuiCol_TabDimmedSelectedOverline,//..horizontal overline, when tab-bar is unfocused & tab is selected
            ImGuiCol_DockingPreview,        // Preview overlay color when about to docking something
            ImGuiCol_DockingEmptyBg,        // Background color for empty node (e.g. CentralNode with no window docked into it)
            ImGuiCol_PlotLines,
            ImGuiCol_PlotLinesHovered,
            ImGuiCol_PlotHistogram,
            ImGuiCol_PlotHistogramHovered,
            ImGuiCol_TableHeaderBg,         // Table header background
            ImGuiCol_TableBorderStrong,     // Table outer and header borders (prefer using Alpha=1.0 here)
            ImGuiCol_TableBorderLight,      // Table inner borders (prefer using Alpha=1.0 here)
            ImGuiCol_TableRowBg,            // Table row background (even rows)
            ImGuiCol_TableRowBgAlt,         // Table row background (odd rows)
            ImGuiCol_TextLink,              // Hyperlink color
            ImGuiCol_TextSelectedBg,
            ImGuiCol_DragDropTarget,        // Rectangle highlighting a drop target
            ImGuiCol_NavHighlight,          // Gamepad/keyboard: current highlighted item
            ImGuiCol_NavWindowingHighlight, // Highlight window when using CTRL+TAB
            ImGuiCol_NavWindowingDimBg,     // Darken/colorize entire screen behind the CTRL+TAB window list, when active
            ImGuiCol_ModalWindowDimBg,      // Darken/colorize entire screen behind a modal window, when one is active
        };

        ImGuiColours(Value v) : value(v) {}

        // Implicit conversion to int
        operator int() const { return value; }

    private:
        Value value;
    };

    extern std::map <int, ImVec4> sImGuiDarkColours;
    extern std::map <int, ImVec4> sImGuiLightColours;


} // End of namespace Borealis

#endif