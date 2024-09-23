/******************************************************************************
/*!
\file       Asset.hpp
\author     Chan Guo Geng Gordon
\par        email: g.chan/@digipen.edu
\date       September 23, 2024
\brief      Holds the asset class

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef Asset_HPP
#define Asset_HPP

#include <Core/UUID.hpp>

namespace Borealis
{
	using AssetHandle = UUID;

	enum class AssetType
	{
		Audio,
		Mesh,
		Shader,
		Texture,
	};

	class Asset
	{
	public:
		AssetHandle mAssetHandle;
		AssetType mAssetType;
	};
}

#endif
