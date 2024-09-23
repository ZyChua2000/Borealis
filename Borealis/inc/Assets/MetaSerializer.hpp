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
		static AssetMetaData CreateAssetMetaFile(std::filesystem::path path);

	private:
		static std::time_t GetLastWriteTime(const std::filesystem::path& path);
		static AssetMetaData GetAssetMetaData(std::filesystem::path path);
	};
}

#endif
