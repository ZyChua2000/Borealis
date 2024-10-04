/******************************************************************************
/*!
\file       ProjectInfo.hpp
\author     Chan Guo Geng Gordon
\par        email: g.chan/@digipen.edu
\date       September 15, 2024
\brief      Declares

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef ProjectInfo_HPP
#define ProjectInfo_HPP

#include <string>
#include <filesystem>

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
}

#endif
