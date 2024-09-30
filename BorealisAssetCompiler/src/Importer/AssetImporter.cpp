/******************************************************************************
/*!
\file       AssetImporter.cpp
\author     Chan Guo Geng Gordon
\par        email: g.chan/@digipen.edu
\date       September 30, 2024
\brief      Defines

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "Importer/AssetImporter.hpp"
#include "Importer/TextureImporter.hpp"
#include "Importer/FontImporter.hpp"

namespace BorealisAssetCompiler
{
	AssetMetaData AssetImporter::ImportAsset(AssetMetaData metaData)
	{
		std::string cacheString = metaData.SourcePath.string();

		std::string toReplace = "Assets";
		std::string replacement = "Cache";

		size_t pos = cacheString.find(toReplace);
		if (pos != std::string::npos)
		{
			cacheString.replace(pos, toReplace.length(), replacement);
		}

		std::filesystem::path cachePath = cacheString;

		std::filesystem::path directoryPath = cachePath.parent_path();

		// Create the directories if they don't exist
		if (!std::filesystem::exists(directoryPath))
		{
			if (!std::filesystem::create_directories(directoryPath))
			{
				//Error check
			}
		}

		switch (metaData.Type)
		{
		case AssetType::Texture2D:
			TextureImporter::SaveFile(metaData.SourcePath, cachePath);
			break;
		case AssetType::Font:
			FontImporter::SaveFile(metaData.SourcePath, cachePath);
			break;
		case AssetType::None:
		default:
			break;
		}

		metaData.CachePath = cachePath;
		return metaData;
	}
}

