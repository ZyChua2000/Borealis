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
#include <imgui.h>
#include <Panels/ContentBrowserPanel.hpp>
#include <Core/LoggerSystem.hpp>
#include <Scene/SceneManager.hpp>

namespace Borealis
{
	enum iconList
	{
		DirectoryIcon = 0,
		TTFIcon,
		SCIcon,
		TXTIcon,
		CSIcon
	};

	static ImVec2 latestMousePos;
	ContentBrowserPanel::ContentBrowserPanel() : mCurrDir("assets")
	{
		// Load by serialisation in the future
		mThumbnails[DirectoryIcon] = Texture2D::Create("resources/Icons/directoryIcon.png");
		mThumbnails[TTFIcon] = Texture2D::Create("resources/Icons/file-ttf.png");
		mThumbnails[SCIcon] = Texture2D::Create("resources/Icons/file-sc.png");
		mThumbnails[TXTIcon] = Texture2D::Create("resources/Icons/file-txt.png");
		mThumbnails[CSIcon] = Texture2D::Create("resources/Icons/file-cs.png");
		mAssetsDir = "assets";
	}

	void ContentBrowserPanel::ImGuiRender() 
	{
		ImGui::Begin("Content Browser");

		ImVec2 windowSize = ImGui::GetWindowSize();
		float scrollableHeight = windowSize.y - 100; // Adjust for the fixed bottom row
		ImGui::BeginChild("ScrollableRegion", ImVec2(windowSize.x, scrollableHeight), true);

		// Begin the upper scrollable section


		if (mCurrDir != std::filesystem::path(mAssetsDir))
		{
			if (ImGui::Button("<-"))
			{
				mCurrDir = mCurrDir.parent_path();
			}
		}

		// Right click
		{
			ImGuiPopupFlags popupFlagsItem = ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems;
			if (ImGui::BeginPopupContextWindow(0, popupFlagsItem))
			{
				if (ImGui::MenuItem("Create Folder"))
				{
					// Create a folder
				}
				if (ImGui::MenuItem("Create Scene"))
				{
					// Create a Scene
					isCreatingScene = true;
					latestMousePos = ImGui::GetMousePos();
				}
				ImGui::EndPopup();
			}
		}

		if (isCreatingScene)
		{
			ImGui::SetNextWindowPos(latestMousePos);
			ImGui::Begin("Create File", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize);
			ImGui::InputText("##Filename", textBuffer, sizeof(textBuffer));

			if (ImGui::IsKeyPressed(ImGuiKey_Enter)) {
				isCreatingScene = false; // Exit rename mode
				// Create a Scene
				SceneManager::CreateScene(textBuffer, mCurrDir.string());
			}

			if (ImGui::IsKeyPressed(ImGuiKey_Escape)) {
				isCreatingScene = false; // Cancel rename
			}
			ImGui::End();
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
		
			const std::filesystem::path& path = entry.path();
			std::string filenameStr = path.filename().string();
			std::string extension = path.extension().string();
			if (extension == ".meta") // Skip meta files
			{
				continue;
			}
			ImGui::PushID(filenameStr.c_str());

			
			

			uint64_t screenID = 0;
			if (entry.is_directory())
			{
				screenID = static_cast<uint64_t>(mThumbnails[DirectoryIcon]->GetRendererID());
			}
			else
			{
				if (extension == ".png" || extension == ".jpg" || extension == ".tiff" || extension == ".jpeg")
				{

				}
				else if (extension == ".txt")
				{
					screenID = static_cast<uint64_t>(mThumbnails[TXTIcon]->GetRendererID());
				}
				else if (extension == ".sc")
				{
					screenID = static_cast<uint64_t>(mThumbnails[SCIcon]->GetRendererID());
				}
				else if (extension == ".glsl")
				{

				}
				else if (extension == ".ttf")
				{
					screenID = static_cast<uint64_t>(mThumbnails[TTFIcon]->GetRendererID());
				}
				else if (extension == ".prefab")
				{

				}
				else if (extension == ".cs")
				{
					screenID = static_cast<uint64_t>(mThumbnails[CSIcon]->GetRendererID());
				}
				else
				{
					// default case
				}
			}
			
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
				if (ImGui::BeginPopupContextItem())
				{
					if (ImGui::MenuItem("Delete"))
					{
					}

					if (ImGui::MenuItem("Rename"))
					{
					}
					ImGui::EndPopup();
				}
			}
			if (ImGui::BeginDragDropSource())
			{
				auto relativePath = std::filesystem::relative(path, mAssetsDir);
				std::string itemPath = relativePath.string();
				const char* itemPathcStr = itemPath.c_str();

				std::string payloadName;
				if (entry.is_directory())
				{

				}
				else
				{
					// convert extension to all lower case
					std::transform(extension.begin(), extension.end(), extension.begin(), [](unsigned char c) { return std::tolower(c); });
					if (extension == ".png" || extension == ".jpg" || extension == ".jpeg")
					{
						payloadName = "DragDropImageItem";
					}
					else if (extension == ".sc")
					{
						payloadName = "DragDropSceneItem";
					}
					else if (extension == ".fbx" || extension == ".obj")
					{
						payloadName = "DragDropMeshItem";
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
	void ContentBrowserPanel::SetCurrDir(std::string path)
	{
		mCurrDir = std::filesystem::path(path);
		mAssetsDir = path;
	}
}