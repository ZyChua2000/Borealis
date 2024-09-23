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

	void RegisterAsset(std::filesystem::path path, YAML::Node& registryNode)
	{
		//Add to registry
		AssetMetaData meta = MetaFileSerializer::CreateAssetMetaFile(path);
	}

	void RegisterAllAssets(std::filesystem::path path, YAML::Node& registryNode)
	{
		if (!std::filesystem::exists(path))
		{
			BOREALIS_CORE_ASSERT("No such directory");
		}

		for (const auto& entry : std::filesystem::directory_iterator(path))
		{
			if (std::filesystem::is_directory(entry))
			{
				//Add to registry
				AssetMetaData meta = MetaFileSerializer::CreateAssetMetaFile(entry);
				RegisterAllAssets(entry.path(), registryNode);
			}
			else if (std::filesystem::is_regular_file(entry))
			{
				RegisterAsset(entry.path(), registryNode);
			}
		}
	}

	void EditorAssetManager::LoadRegistry(std::filesystem::path assetPath, std::filesystem::path assetRegistryPath)
	{
		//open registry database file
		//if !file create file
		if (!std::filesystem::exists(assetRegistryPath)) {
			BOREALIS_CORE_INFO("Registry file not found. Creating a new one");

			std::ofstream registry(assetRegistryPath);
			if (registry) {
				BOREALIS_CORE_INFO("Registry file created successfully.");
			}
			else {
				BOREALIS_CORE_ASSERT("Failed to create registry file.");
				return;
			}
			registry.close();
		}

		std::ifstream registryFile(assetRegistryPath);
		std::stringstream registryStream;
		registryStream << registryFile.rdbuf();
		registryFile.close();

		YAML::Node registryRoot = YAML::Load(registryStream.str());

		//read files in assets folder and compare it with file
		// - check if the asset have a .meta file
		// - verify the version of the assets
		// - verify that asset have a cached if needed
		// - if every check is true, add to registry
		RegisterAllAssets(assetPath, registryRoot);
	}

	void EditorAssetManager::Clear()
	{
	}
}

