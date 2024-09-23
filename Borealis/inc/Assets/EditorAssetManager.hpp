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

#include <Assets/AssetManager.hpp>
#include <Assets/AssetMetaData.hpp>

namespace Borealis
{
	class EditorAssetManager : public AssetManager
	{
	public:
		Ref<Asset> GetAsset(AssetHandle assetHandle) override;

		//Load all available assets into Registry
		void LoadRegistry(std::filesystem::path assetPath, std::filesystem::path assetRegistryPath);

		//clear Registry and loaded assets
		void Clear();
	private:
		//void RegisterAsset(std::filesystem::path path);

		//void RegisterAllAssets(std::filesystem::path path);


	private:
		std::unordered_map<AssetHandle, AssetMetaData> mAssetRegistry;
		std::unordered_map<AssetHandle, Ref<Asset>> mLoadedAssets;
	};
}

#endif
