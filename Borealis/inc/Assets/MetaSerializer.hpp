/******************************************************************************
/*!
\file       MetaSerializer.hpp
\author     Chan Guo Geng Gordon
\par        email: g.chan/@digipen.edu
\date       September 23, 2024
\brief      Declares

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef MetaSerializer_HPP
#define MetaSerializer_HPP

#include <Assets/AssetMetaData.hpp>

namespace Borealis
{
	class MetaFileSerializer
	{
	public:
		static void SetAssetFolderPath(std::filesystem::path path);
		static AssetMetaData CreateAssetMetaFile(std::filesystem::path path);

		static void SerialzeRegistry(std::filesystem::path assetRegistryPath, std::unordered_map<AssetHandle, AssetMetaData> const& assetRegistry);

	private:
		static void SaveAsFile(const std::filesystem::path& path, const char* outputFile);
		static std::time_t GetLastWriteTime(const std::filesystem::path& path);
		static AssetMetaData GetAssetMetaData(std::filesystem::path path);

	private:
		inline static std::filesystem::path PathToAssetFolder;
	};
}

#endif
