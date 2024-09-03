/******************************************************************************/
/*!
\file		ContentBrowserPanel.cpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 13, 2024
\brief		Defines the class Content Browser in Level Editor

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 *
 /******************************************************************************/

#include <Panels/ContentBrowserPanel.hpp>
#include <Core/LoggerSystem.hpp>
#include <imgui.h>

namespace Borealis
{

	static std::string sAssetsDir = "assets";

	ContentBrowserPanel::ContentBrowserPanel() : mCurrDir(sAssetsDir)
	{
		mDirectoryIcon = Texture2D::Create("resources/Icons/directoryIcon.png");
	}

	void ContentBrowserPanel::ImGuiRender() 
	{
		ImGui::Begin("Content Browser");

		ImVec2 windowSize = ImGui::GetWindowSize();
		float scrollableHeight = windowSize.y - 100; // Adjust for the fixed bottom row
		ImGui::BeginChild("ScrollableRegion", ImVec2(windowSize.x, scrollableHeight), true);

		// Begin the upper scrollable section


		if (mCurrDir != std::filesystem::path(sAssetsDir))
		{
			if (ImGui::Button("<-"))
			{
				mCurrDir = mCurrDir.parent_path();
			}
		}

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int cellSize = mThumbnailSize + mPadding;
		int columnCount = (int)(panelWidth / cellSize);
		columnCount = columnCount < 1 ? 1 : columnCount;
		float printedThumbnailSize = (float)mThumbnailSize;
		bool dragDrop = false;

		if (mThumbnailSize != mMinThumbnailSize)
		{
			ImGui::Columns(columnCount);
			ImGui::PushStyleColor(ImGuiCol_Button, { 0,0,0,0 });
		}

		for (auto& entry : std::filesystem::directory_iterator(mCurrDir))
		{
		;
			const std::filesystem::path& path = entry.path();
			std::string filenameStr = path.filename().string();
			std::string extension = path.extension().string();
			ImGui::PushID(filenameStr.c_str());
			

			uint64_t screenID = 0;
			if (entry.is_directory())
			{
				screenID = static_cast<uint64_t>(mDirectoryIcon->GetRendererID());
			}
			else
			{
				if (extension == ".png" || extension == ".jpg" || extension == ".tiff" || extension == ".jpeg")
				{

				}
				else if (extension == ".txt")
				{

				}
				else if (extension == ".sc")
				{

				}
				else if (extension == ".glsl")
				{

				}
				else if (extension == ".ttf")
				{

				}
				else if (extension == ".prefab")
				{

				}
				else
				{
					// default case
				}
			}
			#
			if (mThumbnailSize == mMinThumbnailSize)
			{
				printedThumbnailSize = 0;
				ImGui::Image((ImTextureID)screenID, { ImGui::GetFontSize(), ImGui::GetFontSize() });
				ImGui::SameLine();
				ImGui::Button(filenameStr.c_str());
			}
			else
			{
				ImGui::ImageButton((ImTextureID)screenID, {printedThumbnailSize, printedThumbnailSize}, {0,1}, {1,0}, -1 , {0,0,0,0}, {1,1,1,1});
			}
			if (ImGui::BeginDragDropSource())
			{
				auto relativePath = std::filesystem::relative(path, sAssetsDir);
				std::string itemPath = relativePath.string();
				const char* itemPathcStr = itemPath.c_str();

				std::string payloadName;
				if (entry.is_directory())
				{

				}
				else
				{
					if (extension == ".png" || extension == ".jpg" || extension == ".jpeg")
					{
						payloadName = "DragDropImageItem";
					}
					else if (extension == ".sc")
					{
						payloadName = "DragDropSceneItem";
					}
				}

				ImGui::SetDragDropPayload(payloadName.c_str(), itemPathcStr, itemPath.length() + 1, ImGuiCond_Once);
				ImGui::EndDragDropSource();
			}
			
			
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				if (entry.is_directory())
				{
					mCurrDir /= path.filename();
				}
				else
				{

				}
			}


			if (mThumbnailSize != mMinThumbnailSize)
			{
				ImGui::TextWrapped(filenameStr.c_str());
				ImGui::NextColumn();
			}
			ImGui::PopID();
		}
		if (mThumbnailSize != mMinThumbnailSize)
		{
			ImGui::PopStyleColor();
			ImGui::Columns(1);
		}
		// End the upper scrollable section
		ImGui::EndChild();
		if (ImGui::SliderInt("##Thumbnail Size", &mThumbnailSize, mMinThumbnailSize, 512, "", ImGuiSliderFlags_NoInput))
		{
			mPadding = mThumbnailSize/10;
		}
		ImGui::End();
	}
}