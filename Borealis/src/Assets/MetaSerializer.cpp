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

#include <yaml-cpp/yaml.h>


namespace Borealis
{
	void MetaFileSerializer::SetAssetFolderPath(std::filesystem::path path)
	{
		PathToAssetFolder = path;
	}

	void SerializeMetaFile(YAML::Emitter& out, AssetMetaData const& assetMetaData)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Name" << YAML::Value << assetMetaData.name;
		out << YAML::Key << "EntityID" << YAML::Value << assetMetaData.Handle;
		out << YAML::Key << "AssetType" << YAML::Value << Asset::AssetTypeToString(assetMetaData.Type);
		out << YAML::Key << "SourcePath" << YAML::Value << assetMetaData.SourcePath.string();
		out << YAML::Key << "LastModifiedDate" << YAML::Value << assetMetaData.importDate;
		out << YAML::EndMap;
	}

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

		//std::ofstream meta(metaFilePath);
		//if (meta)
		//{
		//	meta << "Name: " << metaData.name << "\n";
		//	meta << "UUID: " << metaData.Handle << "\n";
		//	meta << Asset::AssetTypeToString(metaData.Type) << "\n";
		//	meta << metaData.SourcePath.string() << "\n";
		//	meta << metaData.importDate << "\n";
		//}
		//else
		//{
		//	BOREALIS_CORE_ASSERT("Failed to create meta file for: {}", path.string());
		//	return AssetMetaData();
		//}

		//meta.close();

		YAML::Emitter out;
		SerializeMetaFile(out, metaData);

		SaveAsFile(metaFilePath, out.c_str());

		return metaData;
	}

	void MetaFileSerializer::SerialzeRegistry(std::filesystem::path assetRegistryPath, std::unordered_map<AssetHandle, AssetMetaData> const& assetRegistry)
	{
		YAML::Emitter out;
		out << YAML::BeginMap
			<< YAML::Key << "Assets" << YAML::Value << YAML::BeginSeq;

		for (auto metaData : assetRegistry)
		{
			SerializeMetaFile(out, metaData.second);
		}

		out << YAML::EndSeq
			<< YAML::EndMap;

		SaveAsFile(assetRegistryPath, out.c_str());
	}

	void MetaFileSerializer::SaveAsFile(const std::filesystem::path& path, const char* outputFile)
	{
		std::ofstream outStream(path);
		outStream << outputFile;
		outStream.close();
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

		metaData.SourcePath = path.lexically_relative(PathToAssetFolder);

		metaData.importDate = GetLastWriteTime(path);

		return metaData;
	}
}

