/******************************************************************************/
/*!
\file		ContentBrowserPanel.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 13, 2024
\brief		Declares the class Content Browser in Level Editor

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 *
 /******************************************************************************/

#ifndef CONTENT_BROWSER_PANEL_HPP
#define CONTENT_BROWSER_PANEL_HPP

#include <Scene/scene.hpp>
#include <Core/core.hpp>
#include <Scene/Entity.hpp>
#include <filesystem>
#include <Graphics/Texture.hpp>

namespace Borealis
{
	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();
		void ImGuiRender();

	private:
		 std::filesystem::path mCurrDir;
		 int mThumbnailSize = 256;
		 int mPadding = 2;
		 const int mMinThumbnailSize = 62;

		 Ref<Texture2D> mDirectoryIcon;
	};
}

#endif
