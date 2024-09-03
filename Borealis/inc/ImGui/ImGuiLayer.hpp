/******************************************************************************/
/*!
\file		ImGuiLayer.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	February 19, 2024
\brief		Declares the ImGui Layer class that will be used to render the ImGui
			elements on the screen.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 *
 /******************************************************************************/

#ifndef IMGUI_LAYER_HPP
#define IMGUI_LAYER_HPP
#include <Core/Layer.hpp>
#include <Events/EventInput.hpp>
#include <Events/EventWindow.hpp>
namespace Borealis
{
	/*!***********************************************************************
		\brief
			Class derived off Layer for ImGui rendering.
	*************************************************************************/
	class BOREALIS_API ImGuiLayer : public Layer
	{
	public:
		/*!***********************************************************************
			\brief
				Constructor for ImGuiLayer.
		*************************************************************************/
		ImGuiLayer();

		/*!***********************************************************************
			\brief
				Destructor for ImGuiLayer.
		*************************************************************************/
		~ImGuiLayer();

		/*!***********************************************************************
			\brief
				Initializes the ImGuiLayer.
		*************************************************************************/
		void Init();

		/*!***********************************************************************
			\brief
				Frees the ImGuiLayer.
		*************************************************************************/
		void Free();

		void BeginFrame();
		void EndFrame();

		void ImGuiRender() override;

		void EventFn(Event& e) override;

		void SetBlockEvents(bool block) { mBlockEvents = block; }

		void onWindowResize(float width, float height);

		static void SetDarkThemeColours();
		static void SetLightThemeColours();

	private:
		bool mBlockEvents = true;
		float mTime;
	};
} // End of namespace Borealis

#endif