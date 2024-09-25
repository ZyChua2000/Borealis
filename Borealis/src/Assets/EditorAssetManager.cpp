/******************************************************************************
/*!
\file       EditorAssetManager.cpp
\author     Chan Guo Geng Gordon
\par        email: g.chan/@digipen.edu
\date       September 23, 2024
\brief      Defines

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include <BorealisPCH.hpp>

#include <Core/LoggerSystem.hpp>
#include <Assets/EditorAssetManager.hpp>
#include <Assets/MetaSerializer.hpp>

#include <yaml-cpp/yaml.h>

namespace Borealis
{
	Ref<Asset> EditorAssetManager::GetAsset(AssetHandle assetHandle)
	{
		return Ref<Asset>();
	}

	void EditorAssetManager::LoadRegistry(ProjectInfo projectInfo)
	{
		//open registry database file
		//if !file create file
		if (!std::filesystem::exists(projectInfo.AssetsRegistryPath)) {
			BOREALIS_CORE_INFO("Registry file not found. Creating a new one");

			std::ofstream registry(projectInfo.AssetsRegistryPath);
			if (registry) {
				BOREALIS_CORE_INFO("Registry file created successfully.");
			}
			else {
				BOREALIS_CORE_ASSERT("Failed to create registry file.");
				return;
			}
			registry.close();
		}

		mAssetRegistryPath = projectInfo.AssetsRegistryPath;

		std::ifstream registryFile(projectInfo.AssetsRegistryPath);
		std::stringstream registryStream;
		registryStream << registryFile.rdbuf();
		registryFile.close();

		DeserializeRegistry(registryStream.str());

		MetaFileSerializer::SetAssetFolderPath(projectInfo.AssetsRegistryPath);

		//read files in assets folder and compare it with file
		// - check if the asset have a .meta file
		// - verify the version of the assets
		// - verify that asset have a cached if needed
		// - if every check is true, add to registry
		RegisterAllAssets(projectInfo.AssetsPath);

		SerializeRegistry();
	}

	void EditorAssetManager::Clear()
	{
	}

	void EditorAssetManager::SerializeRegistry()
	{
		MetaFileSerializer::SerialzeRegistry(mAssetRegistryPath, mAssetRegistry);
	}

	void EditorAssetManager::DeserializeRegistry(std::string const& registryFileString)
	{
		YAML::Node registryRoot = YAML::Load(registryFileString);
	}

	void EditorAssetManager::RegisterAsset(std::filesystem::path path)
	{
		AssetMetaData meta = MetaFileSerializer::CreateAssetMetaFile(path);
		mAssetRegistry.insert({ meta.Handle, meta });
	}

	void EditorAssetManager::RegisterAllAssets(std::filesystem::path path)
	{
		if (!std::filesystem::exists(path))
		{
			BOREALIS_CORE_ASSERT("No such directory");
		}

		for (const auto& entry : std::filesystem::directory_iterator(path))
		{
			if (std::filesystem::is_directory(entry))
			{
				AssetMetaData meta = MetaFileSerializer::CreateAssetMetaFile(entry);
				mAssetRegistry.insert({ meta.Handle, meta });
				RegisterAllAssets(entry.path());
			}
			else if (std::filesystem::is_regular_file(entry))
			{
				RegisterAsset(entry.path());
			}
		}
	}
}

