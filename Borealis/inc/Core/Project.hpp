/******************************************************************************/
/*!
\file		Project.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	September 09, 2024
\brief		Declares the class for the Project Management

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 *
 /******************************************************************************/

#include <string>
#include <filesystem>

#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <memory>

#include <Assets/AssetManager.hpp>
#include <Assets/EditorAssetManager.hpp>

namespace Borealis
{
	struct ProjectInfo
	{
		std::string ProjectName;
		std::filesystem::path ProjectPath;
		std::filesystem::path AssetsPath;
		std::filesystem::path AssetsRegistryPath;

		std::string AssetsDirectoryName = "\\Assets";
		std::string AssetsRegistryName = "\\AssetRegistry.brdb";
	};

	class Project
	{
	public:
		static void CreateProject(std::string name, std::string path);
		static void SetProjectPath(std::string path);
		static std::string GetProjectPath();
		static std::string GetProjectName();

		static std::string GetAssetsPath();
		static void SaveProject();

		static void BuildExportSettings(std::string buildPath, std::string buildName);
		static void CopyFolder(const std::filesystem::path& source, const std::filesystem::path& destination);
		static void CopyIndividualFile(const std::filesystem::path& source, const std::filesystem::path& destination);

		static std::shared_ptr<EditorAssetManager> GetEditorAssetsManager();
	private:
		static ProjectInfo mProjectInfo;

		static std::shared_ptr<AssetManager> mAssetManager;
	};

}
#endif