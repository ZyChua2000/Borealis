/******************************************************************************
/*!
\file       MetaSerializer.cpp
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
#include <Assets/MetaSerializer.hpp>

namespace Borealis
{
	AssetMetaData MetaFileSerializer::CreateAssetMetaFile(std::filesystem::path path)
	{
		AssetMetaData metaData = GetAssetMetaData(path);

		std::filesystem::path metaFilePath;

		if (std::filesystem::is_directory(path))
		{
			metaFilePath = path.string() + ".meta";
		}
		else
		{
			metaFilePath = path;
			metaFilePath.replace_extension(".meta");
		}

		std::ofstream meta(metaFilePath);
		if (meta)
		{
			meta << "Name: " << metaData.name << "\n";
			meta << "UUID: " << metaData.Handle << "\n";
			meta << Asset::AssetTypeToString(metaData.Type) << "\n";
			meta << metaData.SourcePath.string() << "\n";
			meta << metaData.importDate << "\n";
		}
		else
		{
			BOREALIS_CORE_ASSERT("Failed to create meta file for: {}", path.string());
			return AssetMetaData();
		}

		meta.close();

		return metaData;
	}

	std::time_t MetaFileSerializer::GetLastWriteTime(const std::filesystem::path& path)
	{
		auto ftime = std::filesystem::last_write_time(path);

		auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
			ftime - std::filesystem::file_time_type::clock::now() +
			std::chrono::system_clock::now());

		return std::chrono::system_clock::to_time_t(sctp);
	}

	AssetMetaData MetaFileSerializer::GetAssetMetaData(std::filesystem::path path)
	{
		AssetMetaData metaData;

		metaData.name = path.filename().string();
		metaData.Handle = UUID();

		metaData.Type = Asset::GetAssetTypeFromExtention(path);

		metaData.SourcePath = path;

		metaData.importDate = GetLastWriteTime(path);

		return metaData;
	}
}

