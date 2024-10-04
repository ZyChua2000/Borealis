/******************************************************************************
/*!
\file       AssetManager.hpp
\author     Chan Guo Geng Gordon
\par        email: g.chan/@digipen.edu
\date       September 23, 2024
\brief      Declares

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef IAssetManager_HPP
#define IAssetManager_HPP

#include <Core/Core.hpp>
#include <Assets/Asset.hpp>

namespace Borealis
{
	class IAssetManager
	{
	public:
		virtual Ref<Asset> GetAsset(AssetHandle Handle) = 0;
	};
}

#endif
