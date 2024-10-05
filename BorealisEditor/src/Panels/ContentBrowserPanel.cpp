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
#include <imgui_internal.h>
#include <Panels/ContentBrowserPanel.hpp>
#include <Core/LoggerSystem.hpp>
#include <Scene/SceneManager.hpp>
#include <Scene/Serialiser.hpp>
#include <Scene/Scene.hpp>
#include <Prefab.hpp>

namespace ImGui
{
	static bool BeginDrapDropTargetWindow(const char* payload_type)
	{
		using namespace ImGui;
		ImRect inner_rect = GetCurrentWindow()->InnerRect;
		if (BeginDragDropTargetCustom(inner_rect, GetID("##WindowBgArea")))
			if (const ImGuiPayload* payload = AcceptDragDropPayload(payload_type, ImGuiDragDropFlags_AcceptBeforeDelivery | ImGuiDragDropFlags_AcceptNoDrawDefaultRect))
			{
				if (payload->IsPreview())
				{
					ImDrawList* draw_list = GetForegroundDrawList();
					draw_list->AddRectFilled(inner_rect.Min, inner_rect.Max, GetColorU32(ImGuiCol_DragDropTarget, 0.05f));
					draw_list->AddRect(inner_rect.Min, inner_rect.Max, GetColorU32(ImGuiCol_DragDropTarget), 0.0f, 0, 2.0f);
				}
				if (payload->IsDelivery())
					return true;
				EndDragDropTarget();
			}
		return false;
	}
}
namespace Borealis
{
	static ImVec2 latestMousePos;
	ContentBrowserPanel::ContentBrowserPanel() : mCurrDir("assets")
	{
		mDirectoryIcon = Texture2D::Create("resources/Icons/directoryIcon.png");
		mAssetsDir = "assets";
	}


	void ContentBrowserPanel::ImGuiRender() 
	{
		ImGui::Begin("Content Browser");



		ImVec2 windowSize = ImGui::GetWindowSize();
		float scrollableHeight = windowSize.y - 100; // Adjust for the fixed bottom row
		ImGui::BeginChild("ScrollableRegion", ImVec2(windowSize.x, scrollableHeight), true);
		
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DragDropEntity"))
			{
				const char* data = (const char*)payload->Data;
				
			}

			ImGui::EndDragDropTarget();
		}

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
					else if (extension == ".prefab")
					{
						// Correct the assignment of payloadName
						payloadName = "DragPrefab";

						auto relativePath = std::filesystem::relative(path, mAssetsDir);
						std::string itemPath = relativePath.string();

						// Set the DragPrefab payload with the file path of the prefab
						ImGui::SetDragDropPayload("DragPrefab", itemPath.c_str(), itemPath.size() + 1);

						// Store the filename string into a local variable
						std::string filenameStr = relativePath.filename().string();

						// Display the filename as the drag text
						ImGui::Text("%s", filenameStr.c_str());
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

		//WORK IN PROGRESS
//Dragged Prefab
// Content Browser panel drop target for creating prefabs
		if (ImGui::BeginDrapDropTargetWindow("DragCreatePrefab"))
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DragCreatePrefab"))
			{
				UUID droppedEntityID = *(const UUID*)payload->Data; // Retrieve the dragged entity ID

				// Retrieve the entity using the dropped entity ID
				Entity droppedEntity = SceneManager::GetActiveScene()->GetEntityByUUID(droppedEntityID); // Assuming you have a function to get an entity by UUID

				Ref<Prefab> prefab = MakeRef<Prefab>(droppedEntity);
				prefab->AddChild(MakeRef<Entity>(droppedEntity));

				Entity makePrefab(prefab->GetPrefabID(), PrefabManager::GetScenePtr());
				std::string dir = mCurrDir.string();
				dir += +"/" + droppedEntity.GetName() + ".prefab";
				Serialiser::SerialisePrefab(dir.c_str(), makePrefab);
				PrefabManager::Register(prefab);


				// You might want to add some feedback or a log message here to indicate success
				std::cout << "Prefab created at: " << mCurrDir.string() << std::endl;
			}
			ImGui::EndDragDropTarget();
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