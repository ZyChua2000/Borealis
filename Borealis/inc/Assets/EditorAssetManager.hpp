/******************************************************************************
/*!
\file       EditorAssetManager.hpp
\author     Chan Guo Geng Gordon
\par        email: g.chan/@digipen.edu
\date       September 23, 2024
\brief      class for Editor Asset Manager

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef EditorAssetManager_HPP
#define EditorAssetManager_HPP

#include <unordered_map>
#include <filesystem>

#include <Core/ProjectInfo.hpp>
#include <Assets/IAssetManager.hpp>
#include <Assets/AssetMetaData.hpp>

namespace Borealis
{
	using AssetRegistry = std::unordered_map<AssetHandle, AssetMetaData>;
	class EditorAssetManager : public IAssetManager
	{
	public:
		Ref<Asset> GetAsset(AssetHandle assetHandle) override;
		AssetMetaData const& GetMetaData(AssetHandle assetHandle);
		AssetRegistry& GetAssetRegistry();

		//Load all available assets into Registry
		//void LoadRegistry(ProjectInfo projectInfo);

		//clear Registry and loaded assets
		void Clear();

	private:
		Ref<Asset> LoadAsset(AssetHandle assetHandle);
		//void SerializeRegistry();
		//void DeserializeRegistry(std::string const& registryFileString);

		//void RegisterAsset(std::filesystem::path path);
		//void RegisterAllAssets(std::filesystem::path path);

		//bool VerifyMetaFile(std::filesystem::path path);

	private:
		std::filesystem::path mAssetRegistryPath;
		AssetRegistry mAssetRegistry;
		std::unordered_map<AssetHandle, Ref<Asset>> mLoadedAssets;
	};
}

#endif
