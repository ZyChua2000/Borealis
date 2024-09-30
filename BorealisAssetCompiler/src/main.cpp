/******************************************************************************
/*!
\file       main.cpp
\author     Chan Guo Geng Gordon
\par        email: g.chan/@digipen.edu
\date       September 27, 2024
\brief      Defines

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include <fstream>
#include <iostream>

#include "Importer/AssetImporter.hpp"
#include "MetaSerializer.hpp"

int main(int argc, char** argv)
{
    if (argc != 2) 
    {
        std::cerr << "Usage: " << argv[0] << " <filepath>" << std::endl;
        return -1;
    }

    std::filesystem::path filePath = argv[1];
    filePath.replace_extension(".meta");

    BorealisAssetCompiler::AssetMetaData data = BorealisAssetCompiler::MetaSerializer::GetAssetMetaDataFile(filePath);

    {
        std::ofstream registry("lol.txt");
        registry << "File Path: " << data.SourcePath.string() << std::endl;
        registry << "File Name: " << data.name << std::endl;
        registry << "Asset Type: " << BorealisAssetCompiler::Asset::AssetTypeToString(data.Type) << std::endl;
        registry.close();
    }

    BorealisAssetCompiler::AssetMetaData finalData = BorealisAssetCompiler::AssetImporter::ImportAsset(data);

    BorealisAssetCompiler::MetaSerializer::SaveMetaFile(finalData, filePath);

	return 1;
}

