#include "ResourceManager.hpp"
/******************************************************************************
/*!
\file       ResourceManager.cpp
\author     Chua Zheng Yang
\par        email: c.zhengyang@digipen.edu
\date       October 02, 2024
\brief      Defines Resource manager class for the editor's resources

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

namespace Borealis
{
	std::unordered_map<FileIcon, Ref<Texture2D>> ResourceManager::mFileIcons;

	void Borealis::ResourceManager::LoadResources()
	{
		// Load Icons
		mFileIcons[FileIcon::Directory] = Texture2D::Create("resources/icons/directoryIcon.png");
		mFileIcons[FileIcon::Scene] = Texture2D::Create("resources/icons/file-sc.png");
		mFileIcons[FileIcon::Script] = Texture2D::Create("resources/icons/file-cs.png");
		mFileIcons[FileIcon::Font] = Texture2D::Create("resources/icons/file-ttf.png");
		mFileIcons[FileIcon::Text] = Texture2D::Create("resources/icons/file-txt.png");
	}
	void ResourceManager::Init()
	{
		LoadResources();
	}
	Ref<Texture2D> ResourceManager::GetFileIcon(FileIcon icon)
	{
		return mFileIcons[icon];
	}
	void ResourceManager::UnloadResource(FileIcon icon)
	{
		mFileIcons.erase(icon);
	}
	void ResourceManager::Free()
	{
		UnloadResources();
	}
	void ResourceManager::UnloadResources()
	{
		mFileIcons.clear();
	}
}

